#pragma once
#include <BWAPI.h>
#include <unordered_set>
#include <deque>
#include "Blackboard.h"

class ScoutingModule {
public:
    ScoutingModule();
    ~ScoutingModule();

    void assignInitialOverlord();
    void updateOverlordScouting();
    void sendZerglingScouts();
    void exploreUnscoutedLocations();
    void update(Blackboard* bb);
    bool isEnemyBaseFound() const;

private:
    bool enemyBaseFound;
    BWAPI::TilePosition enemyBase;
    std::deque<BWAPI::TilePosition> scoutingPositions;
    std::unordered_set<BWAPI::Unit> overlordScouts;
    std::unordered_set<BWAPI::Unit> zerglingScouts;
};
