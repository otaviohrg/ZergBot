#include "ScoutingModule.h"

ScoutingModule::ScoutingModule() : enemyBaseFound(false), enemyBase(BWAPI::TilePositions::None) {
    // Initialize scouting positions (potential enemy spawn locations)
    for (const auto& startLocation : BWAPI::Broodwar->getStartLocations()) {
        if (startLocation != BWAPI::Broodwar->self()->getStartLocation()) {
            scoutingPositions.push_back(startLocation);
        }
    }
}

ScoutingModule::~ScoutingModule() {}

void ScoutingModule::assignInitialOverlord() {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Overlord && overlordScouts.find(unit) == overlordScouts.end()) {
            if (!scoutingPositions.empty()) {
                unit->move(BWAPI::Position(scoutingPositions.front()));
                overlordScouts.insert(unit);
                scoutingPositions.erase(scoutingPositions.begin());
                return;
            }
        }
    }
}

void ScoutingModule::updateOverlordScouting() {
    for (auto& overlord : overlordScouts) {
        if (overlord->exists() && overlord->isIdle()) {
            if (!scoutingPositions.empty()) {
                overlord->move(BWAPI::Position(scoutingPositions.front()));
                scoutingPositions.erase(scoutingPositions.begin());
            }
        }
    }
}

void ScoutingModule::sendZerglingScouts() {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling && zerglingScouts.find(unit) == zerglingScouts.end()) {
            if (!scoutingPositions.empty()) {
                unit->move(BWAPI::Position(scoutingPositions.front()));
                zerglingScouts.insert(unit);
                scoutingPositions.erase(scoutingPositions.begin());
                return;
            }
        }
    }
}

void ScoutingModule::exploreUnscoutedLocations() {
    if (!enemyBaseFound) {
        for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
            if (unit->getType().isWorker() || unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) {
                if (!scoutingPositions.empty()) {
                    unit->move(BWAPI::Position(scoutingPositions.front()));
                    scoutingPositions.erase(scoutingPositions.begin());
                }
            }
        }
    }
}

bool ScoutingModule::isEnemyBaseFound() const {
    return enemyBaseFound;
}

void ScoutingModule::update(Blackboard* bb) {
    if (!enemyBaseFound) {
        for (auto& unit : BWAPI::Broodwar->enemy()->getUnits()) {
            if (unit->getType().isResourceDepot()) {
                enemyBase = unit->getTilePosition();
                enemyBaseFound = true;
                BWAPI::Broodwar->printf("Enemy base found at (%d, %d)", enemyBase.x, enemyBase.y);
                return;
            }
        }
    }

    if (overlordScouts.empty()) {
        assignInitialOverlord();
    }

    updateOverlordScouting();
    sendZerglingScouts();
    exploreUnscoutedLocations();
}
