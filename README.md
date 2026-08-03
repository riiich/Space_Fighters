# Space Fighters

Space Fighters is an arcade-style game built with C++14 and SFML. I originally
created it in Fall 2020 for a Data Structures & Algorithms course and have since
expanded it with persistent player profiles, named leaderboard scores, settings,
audio controls, and improved menu and game-over flows.

The goal is to survive while destroying incoming enemy ships. Enemy collisions
and ships reaching the bottom of the screen reduce the player's health. Mini
quests and score progression unlock stronger laser attacks.

## Fresh Windows setup

You do not need to install SFML separately. The CMake build downloads the pinned
SFML 2.6.2 source and builds a compiler-compatible copy automatically.

Install these prerequisites on the new computer:

- [Git](https://git-scm.com/download/win)
- [CMake 3.16 or newer](https://cmake.org/download/), with CMake added to `PATH`
- A C++ compiler. The easiest Windows option is Visual Studio 2022 or Build Tools
  with the **Desktop development with C++** workload.

Then open PowerShell and run:

```powershell
git clone https://github.com/riiich/Space_Fighters.git
cd Space_Fighters
cmake -S "Space_Fighters_(SFML)" -B "Space_Fighters_(SFML)/build"
cmake --build "Space_Fighters_(SFML)/build" --config Debug
& ".\Run Space Fighters.bat"
```

The first configure/build requires an internet connection and takes longer
because CMake downloads and compiles SFML. Later builds reuse the local build
folder.

## VS Code

Open the cloned repository folder in VS Code and install the recommended C/C++
and CMake Tools extensions. Press `Ctrl+Shift+B` to configure and build. Use the
`Run Space Fighters` task to launch it, or select the Visual Studio/GDB debug
configuration that matches your compiler.

## Local files

The build output, runtime DLLs, player profile, leaderboard history, `.codex`,
and `.agents` folders are ignored by Git. Playing or building the game will not
publish those computer-specific files.

## Controls

- Move and shoot to destroy enemies while protecting your health.
- Complete mini quests to upgrade the laser attack.
- Use the main menu for the leaderboard, settings, and player name.
