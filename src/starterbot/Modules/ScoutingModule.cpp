#include "ScoutingModule.h"
#include <deque>

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
                auto target = scoutingPositions.front();
                unit->move(BWAPI::Position(target));
                overlordScouts.insert(unit);
                scoutingPositions.pop_front();
                return;
            }
        }
    }
}

void ScoutingModule::updateOverlordScouting() {
    std::unordered_set<BWAPI::Unit> toRemove;
    for (auto& overlord : overlordScouts) {
        if (!overlord->exists()) {
            toRemove.insert(overlord);
            continue;
        }
        if (overlord->isIdle() && !scoutingPositions.empty()) {
            overlord->move(BWAPI::Position(scoutingPositions.front()));
            scoutingPositions.pop_front();
        }
    }
    for (auto& unit : toRemove) {
        overlordScouts.erase(unit);
    }
}

void ScoutingModule::sendZerglingScouts() {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling && zerglingScouts.find(unit) == zerglingScouts.end()) {
            if (!scoutingPositions.empty()) {
                auto target = scoutingPositions.front();
                unit->move(BWAPI::Position(target));
                zerglingScouts.insert(unit);
                scoutingPositions.pop_front();
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
                    auto target = scoutingPositions.front();
                    unit->move(BWAPI::Position(target));
                    scoutingPositions.pop_front();
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
                
                // Store enemy base in blackboard
                bb->setEnemyBase(enemyBase);
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
