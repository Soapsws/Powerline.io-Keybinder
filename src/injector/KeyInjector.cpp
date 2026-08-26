#include "KeyInjector.hpp"


KeyInjector::KeyInjector() {
    CGRect bounds = CGDisplayBounds(CGMainDisplayID());
    double screenWidth = bounds.size.width;
    double screenHeight = bounds.size.height;

    currTargets = std::make_pair(CGPointMake(screenWidth * 0.25, screenHeight * 0.50), CGPointMake(screenWidth * 0.75, screenHeight * 0.50));
}

void KeyInjector::clickTarget(const std::string& s) {
    CGPoint target;
    if (s == "left") {
        target = currTargets.first;
    } else if (s == "right") {
        target = currTargets.second;
    } else {
        return;
    }

    CGEventRef mouseDown = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, target, kCGMouseButtonLeft);
    CGEventRef mouseUp = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, target, kCGMouseButtonLeft);

    CGEventPost(kCGHIDEventTap, mouseDown);
    CGEventPost(kCGHIDEventTap, mouseUp);

    CFRelease(mouseDown);
    CFRelease(mouseUp);
}

void KeyInjector::clickLeft() {
    clickTarget("left");
}

void KeyInjector::clickRight() {
    clickTarget("right");
}