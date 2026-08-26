cmake_minimum_required(VERSION 3.20)

project(PowerlineKeybinder LANGUAGES CXX OBJCXX)

add_executable(powerline_keybinder MACOSX_BUNDLE
    src/main.mm
    src/app/MenuBarApp.mm
    src/injector/KeyInjector.cpp
    src/listener/KeyListener.cpp
)

target_include_directories (powerline_keybinder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/injector
    ${CMAKE_CURRENT_SOURCE_DIR}/src/listener
)

target_link_libraries(powerline_keybinder PRIVATE
    "-framework ApplicationServices"
    "-framework CoreFoundation"
    "-framework Cocoa"
    "-framework Carbon"
)

target_compile_features(powerline_keybinder PRIVATE cxx_std_20)
set_target_properties(powerline_keybinder PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.powerline.keybinder"
    MACOSX_BUNDLE_BUNDLE_NAME "Powerline Keybinder"
)
