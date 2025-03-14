#include "ScoutingModule.h"
#include "../Data.h"
#include <iostream>
ScoutingModule::ScoutingModule() {
    foundEnemyBase = false;
    targetLocation = BWAPI::TilePosition(-1, -1);  // Initialize with an invalid position
}

BWAPI::Position convert(BWAPI::TilePosition tp){
    return BWAPI::Position(tp.x*32,tp.y*32);
}
ScoutingModule::~ScoutingModule() {
    // Cleanup if needed, currently no dynamic memory allocation to clean
}

void ScoutingModule::SendScoutToExplore(BWAPI::Unit scout, BWAPI::TilePosition target) {
    if (scout && scout->getPosition().getDistance(convert(target)) > 20) {  // Ensure scout is moving
        scout->move(BWAPI::Position(target));
    }
}

BWAPI::TilePosition ScoutingModule::FindEnemyBase() {
    // Search for enemy base using various methods:
    // 1. Start location (can be derived from the map or spawning points)
    // 2. Known enemy activity (worker, building, etc.)
    
    for (auto& base : BWAPI::Broodwar->getStartLocations()) {
        if (!BWAPI::Broodwar->isExplored(base)) {
            return base;
        }
    }

    // If no known start location found, look for a random unexplored area (for larger maps)
    BWAPI::TilePosition potentialBase = BWAPI::TilePosition(rand() % 100, rand() % 100);
    return potentialBase;
}

void ScoutingModule::UpdateScouting(Blackboard* bb) {
    // Iterate through all scouting units and update their state
    for (auto scout : bb->pData->unitsScouting) {
        if (!scout) continue;

        // If the scout hasn't found the enemy base yet, continue exploration
        if (!foundEnemyBase) {
            // Try to find the enemy base location
            BWAPI::TilePosition enemyBase = FindEnemyBase();
            if (enemyBase != BWAPI::TilePosition(-1, -1)) {
                SendScoutToExplore(scout, enemyBase);  // Send scout to explore that location
                targetLocation = enemyBase;  // Update the target location
            }
        }

        // Check if the scout has reached its target and found the enemy base
        if (scout->getPosition().getDistance(convert(targetLocation)) < 10) {
            foundEnemyBase = true;
            ScoutFoundEnemyBase();  // Take action after finding the enemy base
        }
    }
}

void ScoutingModule::ScoutFoundEnemyBase() {
    // When the enemy base is found, update the strategy
    // For example: report the enemy base location or transition to another behavior like attack or expand

    // Update behavior to react to enemy base discovery
    std::cout<<"Enemy base found"<<std::endl;
    
    // You could trigger other actions here, like attack, report, or transition the state to further steps.
}
