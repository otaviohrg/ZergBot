# STARTcraft

Get started with Starcraft: BroodWar AI Development as fast as possible. 

New to StarCraft or AI Programming? Watch the tutorial video(s): 
* Starcraft AI Intro: https://www.youtube.com/watch?v=czhNqUxmLks
* STARTcraft Tutorial: https://www.youtube.com/watch?v=FEEkO6__GKw

Currently Supported (more coming soon):
* Windows / C++ Development using BWAPI

# Setup Instructions:

## Windows / C++

STARTcraft comes with a StarterBot written in C++ using BWAPI 4.4.0. This repo comes with BWAPI, and uses Injectory to launch StarCraft with BWAPI, so Chaoslauncher is not required.

1. Download / Clone this repo to your computer
2. Download and unzip [Starcraft Broodwar 1.16.1](http://www.cs.mun.ca/~dchurchill/startcraft/scbw_bwapi440.zip) to the included `windows/starcraft` folder
3. Run `windows/RunC++BotAndStarcraft.bat` which will launch the bot executable and Starcraft / BWAPI
4. Open `windows/visualstudio/StartCraft.sln` in Visual Studio 2022 to modify / recompile the code

# Project

## General 

We split the code into five main modules : Base, Economy, Combat strategy, Micro tactics, Scouting.
Each module validates its tasks and lists its needs. Each need is stored in a global list with a priority indicator.

### Scouting

For now, our scouting method consists of sending our first overlord to the opposite corner of the map.
There are 3 possible positions for the enemy base, we chose to check the furthest one first.
To do : Train 2 zerglings outside of squads to go scout and check the map for the other spawn point if necessary, of for hidden buildings and secondary bases in any case.

### Economy

Our current economy is pretty basic : we do not concentrate on gas yet and focus on maximizing the number of workers on the nearby crystals.

### Combat

### Base

### Micro 

### To do :

- Fix the logic of mining.
- Scouting : take two Zerglings to scout for secondary bases.
- 4-pool strategy / base construction. (All races to start with)
- Split the strategies depending on the enemy's race.
   - 3 build orders.
   - 3 base growths.
