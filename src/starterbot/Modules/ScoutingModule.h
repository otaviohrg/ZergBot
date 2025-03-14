#pragma once
#include <BWAPI.h>
#include <unordered_set>
#include "../Blackboard.h"
#include "../Tools.h"

class ScoutingModule {
private:
    std::unordered_set<BWAPI::Unit> overlordScouts;
    std::unordered_set<BWAPI::Unit> zerglingScouts;
    std::vector<BWAPI::TilePosition> scoutingPositions;
    BWAPI::TilePosition enemyBase;
    bool enemyBaseFound;

    void assignInitialOverlord();
    void updateOverlordScouting();
    void sendZerglingScouts();
    void exploreUnscoutedLocations();
    bool isEnemyBaseFound() const;

public:
    ScoutingModule();
    ~ScoutingModule();
    void update(Blackboard* bb);
};
