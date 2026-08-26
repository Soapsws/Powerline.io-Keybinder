#include <CoreGraphics/CoreGraphics.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

class KeyListener {

    public:

        KeyListener();
        ~KeyListener();

        void listen();
        void start();
        void stop();
        void setEnabled(bool value);
        bool isEnabled() const { return enabled; }
        void registerInjector(std::function<void(std::string)> injector);

    private:

        bool enabled = true;
        CFMachPortRef eventTap = nullptr;
        CFRunLoopSourceRef runLoopSource = nullptr;

        std::unordered_map<int, std::vector<std::function<void()>>> validKeyCallbacks;
        std::function<void(std::string)> injector;

        int getKeyCode(CGEventRef event);
        static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *userInfo);
    };
