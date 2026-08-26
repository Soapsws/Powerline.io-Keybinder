#include <CoreGraphics/CoreGraphics.h>
#include <utility>
#include <string>

class KeyInjector {
    public:
        KeyInjector();
        KeyInjector(const KeyInjector&) = delete;

        void clickLeft();
        void clickRight();

    private:
        std::pair<CGPoint, CGPoint> currTargets;

        void clickTarget(const std::string& s);

};
