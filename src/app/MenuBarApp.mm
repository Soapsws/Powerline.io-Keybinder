#import <Cocoa/Cocoa.h>
#include "KeyListener.hpp"
#include "KeyInjector.hpp"
#include <memory>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property(nonatomic, strong) NSStatusItem *statusItem;
@property(nonatomic, strong) NSMenuItem *toggleItem;
@end

@implementation AppDelegate {
    std::unique_ptr<KeyListener> listener;
    std::unique_ptr<KeyInjector> injector;
}

- (void)applicationDidFinishLaunching:(NSNotification *)note {
    listener = std::make_unique<KeyListener>();
    injector = std::make_unique<KeyInjector>();
    auto *injectorPtr = injector.get();
    listener->registerInjector([injectorPtr](std::string command) {
        if (command == "left") injectorPtr->clickLeft();
        else if (command == "right") injectorPtr->clickRight();
    });
    listener->start();

    self.statusItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
    // Plain text is deliberately used here so the status item is visible
    // even with menu-bar icon/font rendering differences.
    self.statusItem.button.title = @"PK";
    NSMenu *menu = [[NSMenu alloc] init];
    self.toggleItem = [menu addItemWithTitle:@"Disable" action:@selector(toggle:) keyEquivalent:@""];
    self.toggleItem.target = self;
    [menu addItem:[NSMenuItem separatorItem]];
    NSMenuItem *quit = [menu addItemWithTitle:@"Quit" action:@selector(quit:) keyEquivalent:@"q"];
    quit.target = self;
    self.statusItem.menu = menu;
}

- (void)toggle:(id)sender {
    BOOL value = !listener->isEnabled();
    listener->setEnabled(value);
    self.toggleItem.title = value ? @"Disable" : @"Enable";
    self.statusItem.button.title = value ? @"PK" : @"OFF";
}

- (void)quit:(id)sender { [NSApp terminate:nil]; }
- (void)applicationWillTerminate:(NSNotification *)note { listener->stop(); }
@end

void runMenuBarApp() {
    NSApplication *app = [NSApplication sharedApplication];
    [app setActivationPolicy:NSApplicationActivationPolicyAccessory];
    AppDelegate *delegate = [[AppDelegate alloc] init];
    app.delegate = delegate;
    [app run];
}
