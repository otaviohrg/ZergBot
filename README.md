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

On separe le code en cinq modules : Base, Economy, Combat strategy, Micro tactics, Scouting.
Chaque module accomplit ses taches et transmet ses besoins dans une liste. Chaque besoin est associe a une valeur de priorite.
Ainsi, les modules economy et combat peuvent decider quels batiments et unites construire.

## Work distribution

### Scouting: Nathan

### Economie: Shu + Yingwei

Framework for Standard and Emergency modules

### Combat + Base: Otavio + Boutheina

### Micro: apres 

