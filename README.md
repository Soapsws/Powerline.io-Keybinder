Runnable script that binds (L, R) keys to mouse clicks on the left and right sides of the screen. 
Made for iOS powerline.io app ran on MacOS and using local turn controls.

Advantages: local turn on PC can bridge biomechanical gaps favoring mobile players
            uses magnified view exclusive to mobile client

## Prerequisites

This application is built exclusively for **macOS** and requires:
* **Operating System:** macOS (due to Cocoa & Carbon framework dependencies)
* **Compiler:** Clang/Xcode Command Line Tools with C++20 support
* **Build System:** [CMake](https://cmake.org) (Version 3.20 or higher)

To install the required terminal tools via [Homebrew](https://brew.sh):
```bash
xcode-select --install
brew install cmake
```

## How to Build

Follow these steps to generate the macOS bundle using CMake:

```bash
# 1. Create and enter a build directory
mkdir build && cd build

# 2. Configure the project
cmake ..

# 3. Build the application
cmake --build .
```

This will output a native macOS app bundle named `Powerline Keybinder.app` inside your `build` directory.

## System Permissions (Required)

Because this app intercepts arrow keys (`CGEventTap`) and injects mouse clicks (`CGEventPost`), macOS requires manual security authorization. 

1. Launch the built app or run it via your IDE.
2. The program will attempt to start, but macOS will prompt you about **Accessibility Permissions**.
3. Open **System Settings > Privacy & Security > Accessibility**.
4. Click the **`+`** icon or toggle the switch next to **Powerline Keybinder** to enable it.
5. Restart the app if it doesn't automatically resume.
