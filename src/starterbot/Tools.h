﻿#pragma once
#include <BWAPI.h>
#include <vector>
#include <algorithm>
#include <limits>
#include "MapTools.h"
namespace Tools
{
    BWAPI::Unit GetClosestUnitTo(BWAPI::Position p, const BWAPI::Unitset& units);
    BWAPI::Unit GetClosestUnitTo(BWAPI::Unit unit, const BWAPI::Unitset& units);
    BWAPI::TilePosition findOptimizedPositionNexus(BWAPI::TilePosition closestGeyser, const std::vector<BWAPI::Position> unitsMineralPositions);
    int CountUnitsOfType(BWAPI::UnitType type, const BWAPI::Unitset& units);
    BWAPI::Unit GetUnitOfType(BWAPI::UnitType type);
    BWAPI::Unit GetDepot();
    BWAPI::Unit GetAvailableLarva();

    bool BuildBuilding(BWAPI::UnitType type);
    BWAPI::Unit GetBuilderUnit();

    void DrawUnitBoundingBoxes();
    void DrawUnitCommands();

    void SmartRightClick(BWAPI::Unit unit, BWAPI::Unit target);

    int GetUnusedSupply(bool inProgress = false);
    int GetTotalSupply(bool inProgress = false);

    void DrawUnitHealthBars();
    void DrawHealthBar(BWAPI::Unit unit, double ratio, BWAPI::Color color, int yOffset);

    bool IsEnemyZerg(void *data);
    bool IsEnemyProtoss(void *data);
    bool IsEnemyTerran(void *data);
}   