cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME sfml_projects_CS3A)

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Space_Fighters/Player.h Space_Fighters/Player.cpp Space_Fighters/Enemy.cpp Space_Fighters/Enemy.h
        Space_Fighters/Ammo.cpp Space_Fighters/Ammo.h Space_Fighters/SpaceFight.h Space_Fighters/SpaceFight.cpp Game/Game.h
        Game/Game.cpp Game/Thumbnail.h Game/Thumbnail.cpp Game/GameText.h Game/GameText.cpp Space_Fighters/SpaceGame.cpp
        Space_Fighters/SpaceGame.h Space_Fighters/Meteor.cpp Space_Fighters/Meteor.h DataStructures/BinarySearchTree.h
        DataStructures/BinarySearchTree.cpp DataStructures/Heap.h DataStructures/Heap.cpp DataStructures/LinkedList.h
        DataStructures/LinkedList.cpp DataStructures/Node.h DataStructures/Node.cpp DataStructures/Node_Iterator.h
        DataStructures/Node_Iterator.cpp DataStructures/Queue.h DataStructures/Queue.cpp DataStructures/Stack.h
        DataStructures/Stack.cpp DataStructures/Traversal.h DataStructures/TreeNode.h DataStructures/TreeNode.cpp
        Space_Fighters/Leaderboard.cpp Space_Fighters/Leaderboard.h Space_Fighters/MusicBackground.cpp
        Space_Fighters/MusicBackground.h Space_Fighters/asteroidRocks.cpp
        Space_Fighters/asteroidRocks.h Space_Fighters/StatsText.cpp Space_Fighters/StatsText.h Space_Fighters/Sound.h
        Space_Fighters/Sound.cpp Space_Fighters/SplashState.cpp Space_Fighters/SplashState.h)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif ()

set(SFML_ROOT D:/SFML-2.5.1)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
#set(SFML_DIR C:/SFML/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML  REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()