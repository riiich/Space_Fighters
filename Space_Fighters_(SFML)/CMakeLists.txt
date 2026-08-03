cmake_minimum_required(VERSION 3.16)

project(SpaceFighters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Keep the game and SFML's runtime libraries together for every generator.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
foreach(config Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER "${config}" config_upper)
    set("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper}" "${CMAKE_BINARY_DIR}/bin")
endforeach()

include(FetchContent)

# This project uses the SFML 2.x API. Fetching a pinned release makes a fresh
# clone independent of compiler-specific SFML installations on a developer's PC.
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "Build SFML examples" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "Build SFML documentation" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build SFML networking" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "Build SFML tests" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SFML)

# SFML's optional Windows entry-point helper is not linked by this game. Older
# MinGW releases cannot compile that helper, so keep it out of the default build.
if(TARGET sfml-main)
    set_target_properties(sfml-main PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

set(SPACE_FIGHTERS_SOURCES
    main.cpp
    DataStructures/BinarySearchTree.cpp
    DataStructures/Heap.cpp
    DataStructures/LinkedList.cpp
    DataStructures/Node.cpp
    DataStructures/Node_Iterator.cpp
    DataStructures/Queue.cpp
    DataStructures/Stack.cpp
    DataStructures/TreeNode.cpp
    Game/Game.cpp
    Game/GameText.cpp
    Game/Thumbnail.cpp
    Space_Fighters/Ammo.cpp
    Space_Fighters/Enemy.cpp
    Space_Fighters/Leaderboard.cpp
    Space_Fighters/Meteor.cpp
    Space_Fighters/MusicBackground.cpp
    Space_Fighters/Player.cpp
    Space_Fighters/Sound.cpp
    Space_Fighters/SpaceFight.cpp
    Space_Fighters/SpaceGame.cpp
    Space_Fighters/SplashState.cpp
    Space_Fighters/StatsText.cpp
    Space_Fighters/asteroidRocks.cpp
)

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(SpaceFighters WIN32 ${SPACE_FIGHTERS_SOURCES})
else()
    add_executable(SpaceFighters ${SPACE_FIGHTERS_SOURCES})
endif()

target_link_libraries(
    SpaceFighters
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
)

if(WIN32)
    target_link_libraries(SpaceFighters PRIVATE winmm)

    # SFML audio dynamically loads OpenAL on Windows. Put the matching bundled
    # DLL next to the executable so the game runs outside a compiler terminal.
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(SFML_OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll")
    else()
        set(SFML_OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x86/openal32.dll")
    endif()

    add_custom_command(
        TARGET SpaceFighters
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "${SFML_OPENAL_DLL}"
                "$<TARGET_FILE_DIR:SpaceFighters>"
        VERBATIM
    )
endif()

set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT SpaceFighters)
set_property(TARGET SpaceFighters PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
