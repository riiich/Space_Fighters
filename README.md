# Space Fighters

Space Fighters is an arcade-style game built with C++14 and SFML. I originally
created it in Fall 2020 for a Data Structures & Algorithms course and have since
expanded it with persistent player profiles, named leaderboard scores, settings,
audio controls, and improved menu and game-over flows.

The goal is to survive while destroying incoming enemy ships. Enemy collisions
and ships reaching the bottom of the screen reduce the player's health. Mini
quests and score progression unlock stronger laser attacks.

You do not need to install SFML separately. The CMake build downloads the pinned
SFML 2.6.2 source and builds a compiler-compatible copy automatically.

Then open PowerShell and run:

```powershell
git clone https://github.com/riiich/Space_Fighters.git
cd Space_Fighters
cmake -S "Space_Fighters_(SFML)" -B "Space_Fighters_(SFML)/build"
cmake --build "Space_Fighters_(SFML)/build" --config Debug
& ".\Run Space Fighters.bat"
```

## Controls

- Move and shoot to destroy enemies while protecting your health.
- Complete mini quests to upgrade the laser attack.
- Use the main menu for the leaderboard, settings, and player name.
