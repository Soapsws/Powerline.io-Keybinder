#include "KeyListener.hpp"

KeyListener::KeyListener() { }
KeyListener::~KeyListener() { stop(); }

void KeyListener::registerInjector(std::function<void(std::string)> injector) {
    this->injector = injector;
}

void KeyListener::setEnabled(bool value) {
    enabled = value;
    if (eventTap) {
        CGEventTapEnable(eventTap, enabled);
    }
}

int KeyListener::getKeyCode(CGEventRef event) {
    int code = static_cast<int>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));
    if (code < 0 || code > 127) {
        return -1;
    }
    return code;
}

CGEventRef KeyListener::eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *userInfo) {

    // creates an address to the KeyListener passed in as user info, allowing us to access non-static members
    KeyListener* listener = static_cast<KeyListener*>(userInfo); // userInfo as a blueprint
    if (!listener) return event;

    // macOS can disable an event tap after a timeout. Re-enable it when the
    // system sends the corresponding notification, provided the user has not
    // disabled the keybinder.
    if (type == kCGEventTapDisabledByTimeout || type == kCGEventTapDisabledByUserInput) {
        if (listener->enabled && listener->eventTap) {
            CGEventTapEnable(listener->eventTap, true);
        }
        return event;
    }

    if (type == kCGEventKeyDown && listener->isEnabled()) {
        int code = listener->getKeyCode(event);
        if (code == 123) {
            // checking that injector is not null. 
            if (listener->injector) {
                listener->injector("left");
            }
        } else if (code == 124) {
            if (listener->injector) {
                listener->injector("right");
            }
        }
    }
        
    return event;
}

void KeyListener::listen() {
    start();
    if (eventTap) CFRunLoopRun();
}

void KeyListener::start() {
    if (eventTap) return;
    // Creates bitmask filter to tell macOS which events we want to listen for. 
    CGEventMask eventMask = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventKeyUp);

    /* EventTap establishes a communication channel with macOS to listen to events.
            Returns a CFMachPortRef (reference to kernel-level port) to emit keyboard data. */
    eventTap = CGEventTapCreate(
        kCGSessionEventTap, // Restrict scope of listening to usr input (ignoring daemons)
        kCGHeadInsertEventTap, // Positions the program at front of event queue to intercept events
        kCGEventTapOptionListenOnly, // Tells macOS we aren't modifying events (faster processing)
        eventMask, 
        eventCallback, // registers target function to run when key event occurs
        this
    );

    if (!eventTap) {
        fprintf(stderr, "Failed to create event tap\n");
        exit(1);
    }

    // Converts low-level CFMachPortRef to a higher-level CFRunLoopSourceRef to be used in the run loop.
    runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    // Attaches stream source to current thread's run loop
    CFRunLoopAddSource(CFRunLoopGetMain(), runLoopSource, kCFRunLoopCommonModes);
    // Enables the tapping to receieve events
    CGEventTapEnable(eventTap, true);
}

void KeyListener::stop() {
    if (runLoopSource) {
        CFRunLoopRemoveSource(CFRunLoopGetMain(), runLoopSource, kCFRunLoopCommonModes);
        CFRelease(runLoopSource);
        runLoopSource = nullptr;
    }
    if (eventTap) {
        CFMachPortInvalidate(eventTap);
        CFRelease(eventTap);
        eventTap = nullptr;
    }
}
