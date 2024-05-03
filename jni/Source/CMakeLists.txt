cmake_minimum_required(VERSION 3.15)
project(pluginNative VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

# Assuming JUCE is located at a specific path
set(JUCE_DIRECTORY "/Users/thomassantoni/Documents/M1/PSTL/JUCE")

# Add JUCE
add_subdirectory(${JUCE_DIRECTORY} ${CMAKE_BINARY_DIR}/JUCE)

add_library(pluginNative SHARED
    PluginEditor.cpp
    PluginEditor.h
    PluginProcessor.cpp
    PluginProcessor.h
)

# Correct path to include JuceHeader.h
target_include_directories(pluginNative PRIVATE
    "../JuceLibraryCode"  # Adjust this path based on your project setup
)

set(JAVA_AWT_LIBRARY NotNeeded)
set(JAVA_JVM_LIBRARY NotNeeded)
set(JAVA_AWT_INCLUDE_PATH NotNeeded)

find_package(JNI REQUIRED)
if(JNI_FOUND)
    message(STATUS "JNI include directories: ${JNI_INCLUDE_DIRS}")
    target_include_directories(pluginNative PRIVATE ${JNI_INCLUDE_DIRS})
endif()


# Make sure JUCE headers are included
target_include_directories(pluginNative PRIVATE
    "${JUCE_DIRECTORY}/modules"  # This assumes modules are directly in the JUCE directory
)

target_link_libraries(pluginNative
    PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_gui_extra
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags)

target_compile_definitions(pluginNative
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)
