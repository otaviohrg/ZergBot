#include "ScoutingModule.h"
#include <deque>

//ScoutingModule::ScoutingModule() : enemyBaseFound(false), moreBaseFound(false), enemyBase(BWAPI::TilePositions::None), moreBase(BWAPI::TilePositions::None) {
//    for (const auto& startLocation : BWAPI::Broodwar->getStartLocations()) {
//        if (startLocation != BWAPI::Broodwar->self()->getStartLocation()) {
//            scoutingPositions.push_back(startLocation);
//        }
//    }
//    BWAPI::TilePosition myBase = BWAPI::Broodwar->self()->getStartLocation();
//    for (const auto& startLocation : BWAPI::Broodwar->getStartLocations()) {
//        if (startLocation != myBase) {
//            expansionPositions.push_back(startLocation);
//        }
//    }
//}
//ScoutingModule::~ScoutingModule() {}
//
//
//void ScoutingModule::assignInitialOverlord() {
//    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
//        if (unit->getType() == BWAPI::UnitTypes::Zerg_Overlord && overlordScouts.find(unit) == overlordScouts.end()) {
//            if (!scoutingPositions.empty()) {
//                auto target = scoutingPositions.front();
//                unit->move(BWAPI::Position(target));
//                overlordScouts.insert(unit);
//                scoutingPositions.pop_front();
//                return;
//            }
//        }
//    }
//}
//
//void ScoutingModule::updateOverlordScouting() {
//    std::unordered_set<BWAPI::Unit> toRemove;
//    for (auto& overlord : overlordScouts) {
//        if (!overlord->exists()) {
//            toRemove.insert(overlord);
//            continue;
//        }
//        if (overlord->isIdle() && !scoutingPositions.empty()) {
//            overlord->move(BWAPI::Position(scoutingPositions.front()));
//            scoutingPositions.pop_front();
//        }
//    }
//    for (auto& unit : toRemove) {
//        overlordScouts.erase(unit);
//    }
//}
//
//void ScoutingModule::sendZerglingScouts() {
//    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
//        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling && zerglingScouts.find(unit) == zerglingScouts.end()) {
//            if (!scoutingPositions.empty()) {
//                auto target = scoutingPositions.front();
//                unit->move(BWAPI::Position(target));
//                zerglingScouts.insert(unit);
//                scoutingPositions.pop_front();
//                return;
//            }
//        }
//    }
//}
//
//void ScoutingModule::exploreUnscoutedLocations() {
//    if (!enemyBaseFound) {
//        for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
//            if (unit->getType().isWorker() || unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) {
//                if (!scoutingPositions.empty()) {
//                    auto target = scoutingPositions.front();
//                    unit->move(BWAPI::Position(target));
//                    scoutingPositions.pop_front();
//                }
//            }
//        }
//    }
//}
//
//bool ScoutingModule::isEnemyBaseFound() const {
//    return enemyBaseFound;
//}
//
//void ScoutingModule::exploreMoreBase() {
//    if (enemyBaseFound && !moreBaseFound) {
//        for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
//            if (unit->getType().isWorker() || unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) {
//                if (!expansionPositions.empty()) {
//                    auto target = expansionPositions.front();
//                    unit->move(BWAPI::Position(target));
//                    expansionPositions.pop_front();
//                }
//            }
//        }
//        moreBaseFound = true;  
//}
//
//void ScoutingModule::update(Blackboard* bb) {
//    if (!enemyBaseFound) {
//        for (auto& unit : BWAPI::Broodwar->enemy()->getUnits()) {
//            if (unit->getType().isResourceDepot()) {
//                enemyBase = unit->getTilePosition();
//                enemyBaseFound = true;
//                BWAPI::Broodwar->printf("Enemy base found at (%d, %d)", enemyBase.x, enemyBase.y);
//                
//                 Store enemy base in blackboard
//                bb->setEnemyBase(enemyBase);
//                return;
//            }
//        }
//    }
//
//    if (ennemyBaseFound && !moreBaseFound) {
//        for (auto& unit : BWAPI::Broodwar->self()) {
//            if(unit->getPosition())
//        }
//    }
//        
//    if (overlordScouts.empty()) {
//        assignInitialOverlord();
//    }
//
//    updateOverlordScouting();
//    sendZerglingScouts();
//    exploreUnscoutedLocations();
//}


ScoutingModule::ScoutingModule() :
    enemyBaseFound(false), moreBaseFound(false),
    enemyBase(BWAPI::TilePositions::None), moreBase(BWAPI::TilePositions::None) {

    initializeScoutingPositions();
    initializeExpansionPositions();

    //// ��ʼ�����Ŀ�꣨�з�����λ�ã�
    //for (const auto& startLocation : BWAPI::Broodwar->getStartLocations()) {
    //    if (startLocation != BWAPI::Broodwar->self()->getStartLocation()) {
    //        scoutingPositions.push_back(startLocation);
    //    }
    //}

    //// ��ʼ��Ǳ����չ���أ�����Ŀ�����
    //BWAPI::TilePosition myBase = BWAPI::Broodwar->self()->getStartLocation();
    //BWAPI::TilePosition closestExpansion = BWAPI::TilePositions::None;
    //double minDistance = std::numeric_limits<double>::max();

    //for (const auto& base : BWAPI::Broodwar->getStartLocations()) {
    //    if (base != myBase) {
    //        double distance = myBase.getDistance(base);
    //        if (distance < minDistance) {
    //            minDistance = distance;
    //            closestExpansion = base;
    //        }
    //    }
    //}

    //if (closestExpansion != BWAPI::TilePositions::None) {
    //    expansionPositions.push_back(closestExpansion);
    //}
}

ScoutingModule::~ScoutingModule() {}

void ScoutingModule::initializeScoutingPositions() {
    // ֻ��ӵз����ܵ���ʼ��
    std::cout << "1" << std::endl;
    for (const auto& startLocation : BWAPI::Broodwar->getStartLocations()) {
        if (startLocation != BWAPI::Broodwar->self()->getStartLocation()) {
            scoutingPositions.push_back(startLocation);
        }
    }
}

void ScoutingModule::initializeExpansionPositions() {
    std::cout << "2" << std::endl;
    expansionPositions.clear();

    // �������п���ҵ������Ŀ�����չ����
    std::unordered_set<BWAPI::TilePosition> potentialBases;
    for (auto& unit : BWAPI::Broodwar->getStaticNeutralUnits()) {
        if (unit->getType().isMineralField()) {
            BWAPI::TilePosition mineralPos = unit->getTilePosition();

            // �ҵ����︽���ĺ��ʻ���λ�ã������ظ���
            BWAPI::TilePosition basePos = BWAPI::TilePosition(mineralPos.x - 4, mineralPos.y - 2);
            potentialBases.insert(basePos);
        }
    }

    // ���˵��Լ���������
    for (auto& base : potentialBases) {
        if (base != BWAPI::Broodwar->self()->getStartLocation()) {
            expansionPositions.push_back(base);
        }
    }
}


void ScoutingModule::update(Blackboard* bb) {
    // 1. ���ֵз�����
    if (!enemyBaseFound) {
        for (auto& unit : BWAPI::Broodwar->enemy()->getUnits()) {
            if (unit->getType().isResourceDepot()) {
                enemyBase = unit->getTilePosition();
                enemyBaseFound = true;
                BWAPI::Broodwar->printf("Enemy base found at (%d, %d)", enemyBase.x, enemyBase.y);

                // ����ڰ�
                bb->setEnemyBase(enemyBase);
                break;
            }
        }
    }

    // 2. ������ֵз����أ���ʼ̽����չ����
    if (enemyBaseFound && !moreBaseFound) {
        exploreExpansions();
    }

    // 3. ����ִ�г������
    assignScouts();
    updateScouts();
}

bool ScoutingModule::isEnemyBaseFound() const {
    return enemyBaseFound;
}

bool ScoutingModule::isSecondBaseFound() const {
    return moreBaseFound;
}

void ScoutingModule::assignScouts() {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if ((unit->getType() == BWAPI::UnitTypes::Zerg_Overlord || unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) &&
            scoutTargets.find(unit) == scoutTargets.end()) {

            if (!scoutingPositions.empty()) {
                BWAPI::TilePosition target = scoutingPositions.front();
                unit->move(BWAPI::Position(target));
                scoutTargets[unit] = target;
                scoutingPositions.pop_front();
            }
        }
    }
}

void ScoutingModule::updateScouts() {
    std::unordered_set<BWAPI::Unit> toRemove;
    for (auto& [unit, target] : scoutTargets) {
        if (!unit->exists() || unit->isIdle()) {
            toRemove.insert(unit);
        }
    }

    for (auto& unit : toRemove) {
        scoutTargets.erase(unit);
        assignScouts(); // ���·���Ŀ��
    }
}

void ScoutingModule::exploreExpansions() {
    if (!expansionPositions.empty()) {
        BWAPI::TilePosition target = expansionPositions.front();
        expansionPositions.pop_front();

        for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
            if (unit->getType() == BWAPI::UnitTypes::Zerg_Overlord || unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) {
                unit->move(BWAPI::Position(target));
            }
        }
        moreBase = target;
        BWAPI::Broodwar->printf("Exploring expansion at (%d, %d)", target.x, target.y);
        moreBaseFound = true;
    }
}
