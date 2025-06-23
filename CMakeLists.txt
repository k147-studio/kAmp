cmake_minimum_required(VERSION 3.22)

project(kAmp VERSION 0.0.1)

# If you've installed JUCE to your system
# find_package(JUCE CONFIG REQUIRED)
# or if JUCE is a subdirectory
add_subdirectory(JUCE)

juce_add_gui_app(kAmp
        BUNDLE_ID "eu.k-147.kAmp"
        COMPANY_NAME "K-147"
        PRODUCT_NAME "kAmp"
        ICON_BIG "resources/images/kamp_logo_with_background.png"
        ICON_SMALL "resources/images/kamp_logo_with_background.png"
)

juce_generate_juce_header(kAmp)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

juce_add_binary_data(ResourcesBinary
        SOURCES
        resources/images/background.png
        resources/icons/account.png
        resources/icons/export.png
        resources/icons/mute.png
        resources/icons/power.png
)

target_include_directories(kAmp PRIVATE "${CMAKE_BINARY_DIR}/juce_binarydata_ResourcesBinary/JuceLibraryCode")

file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_SOURCE_DIR}/resources/*.*")

foreach(RESOURCE_FILE IN LISTS RESOURCE_FILES)
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/resources" "${RESOURCE_FILE}")
    set(DEST_PATH "${CMAKE_BINARY_DIR}/resources/${REL_PATH}")
    add_custom_command(
            TARGET kAmp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RESOURCE_FILE}" "${DEST_PATH}"
    )
endforeach()

target_sources(kAmp PRIVATE ${SOURCES})

target_include_directories(kAmp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(kAmp
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_IOS=1
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:kAmp,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:kAmp,JUCE_VERSION>"
)

target_link_libraries(kAmp
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_utils
        juce::juce_gui_extra
        juce::juce_dsp
        ResourcesBinary
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)


