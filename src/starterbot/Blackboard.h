#pragma once

#include <BWAPI.h>
#include <unordered_set>
#include "BT/Data.h"

class Blackboard
{
private:
    BWAPI::TilePosition enemyBase;
public:
    Data* pData;

    Blackboard();
    void reserveResources(int minerals, int gas);
    void unreserveResources(int minerals, int gas);
    void updateResources();
    void setEnemyBase(const BWAPI::TilePosition& position) {
        enemyBase = position;
    }

    BWAPI::TilePosition getEnemyBase() const {
        return enemyBase;
    }

};
