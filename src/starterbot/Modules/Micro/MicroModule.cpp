#include "MicroModule.h"
#include <algorithm>
#include <vector>

#define SQUAD_SIZE 6

MicroModule::MicroModule() {}

BWAPI::Position enemyBasePosition = BWAPI::Positions::None;  // Global variable


std::vector<BWAPI::Position> GetMineralPositions() {
    std::vector<BWAPI::Position> mineralPositions;

    // Iterate through all static minerals on the map
    for (auto& mineral : BWAPI::Broodwar->getStaticMinerals()) {
        mineralPositions.push_back(mineral->getPosition());
    }

    return mineralPositions;
}

struct MineralCluster {
    BWAPI::Position position;
    double distanceSum;
};

// Function to get the top 3 most probable enemy base positions
std::list<BWAPI::Position> GetTopThreePossibleEnemyBasePositions() {
    std::vector<BWAPI::Position> mineralPositions = GetMineralPositions();
    std::list<MineralCluster> mineralClusters;

    // Iterate over all mineral positions and calculate distance sums
    for (size_t i = 0; i < mineralPositions.size(); ++i) {
        BWAPI::Position currentMineral = mineralPositions[i];
        double distanceSum = 0.0;

        // Calculate the sum of distances from this mineral to all other minerals
        for (size_t j = 0; j < mineralPositions.size(); ++j) {
            if (i != j) {
                distanceSum += currentMineral.getDistance(mineralPositions[j]);
            }
        }

        // Store the mineral position and its corresponding distance sum
        mineralClusters.push_back({currentMineral, distanceSum});
    }

    // Sort the mineral clusters based on distance sum in descending order
    mineralClusters.sort([](const MineralCluster& a, const MineralCluster& b) {
        return a.distanceSum > b.distanceSum;
    });

    // Get the top 3 most probable enemy base positions and store them in a list
    std::list<BWAPI::Position> topThreePositions;
    auto it = mineralClusters.begin();
    for (size_t i = 0; i < 3 && it != mineralClusters.end(); ++i, ++it) {
        topThreePositions.push_back(it->position);
    }

    return topThreePositions;
}


BWAPI::Position GetEnemyBasePosition() {
    // If we already found the enemy base, return it

    if (enemyBasePosition.isValid()) {
        return enemyBasePosition;
    }

    // Check if we've seen an enemy Command Center, Hatchery, or Nexus
    for (auto& unit : BWAPI::Broodwar->enemy()->getUnits()) {
        if (unit->getType().isResourceDepot()) {  // Enemy main base building
            enemyBasePosition = unit->getPosition();
            return enemyBasePosition;
        }
    }

    // If no known positions, return an invalid position (fallback)
    return BWAPI::Positions::None;
}


void MicroModule::updateMicro()
{
    // Clean up dead units from squads
    for (auto& squad : squads) {
        squad.units.remove_if([](BWAPI::Unit unit) { return !unit || !unit->exists(); });
    }

    // Check if we need to form a new squad
    std::list<BWAPI::Unit> availableLings;
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) {
            bool inSquad = false;
            for (auto& squad : squads) {
                if (std::find(squad.units.begin(), squad.units.end(), unit) != squad.units.end()) {
                    inSquad = true;
                    break;
                }
            }
            if (!inSquad) availableLings.push_back(unit);
        }
    }

    // Form new squads when enough Zerglings are available
    while (availableLings.size() >= SQUAD_SIZE) {
        //std::cout << "Forming new squad" << std::endl;
        Squad newSquad (squads.size());
        for (int i = 0; i < SQUAD_SIZE; i++) {
            newSquad.units.push_back(availableLings.front());
            availableLings.pop_front();
        }
        squads.push_back(newSquad);
        //std::cout << "Number of squads: " << squads.size() << std::endl;
    }

    // Command squads to attack
    for (auto& squad : squads) {
        executeSquadAttack(squad);
    }
}

void MicroModule::executeSquadAttack(Squad& squad) {
    //std::cout << "Squad "<< squad.squadId << " getting order" << std::endl;
    if (squad.units.empty()){
        //std::cout << "Squad "<< squad.squadId << " is empty" << std::endl;
        return;
    }
    BWAPI::Position enemyBase = GetEnemyBasePosition();
    //std::cout << "Enemy base position: " << enemyBase << std::endl;
    if (!enemyBase.isValid()) {
        //std::cout << "Squad "<< squad.squadId << " dont know base" << std::endl;
        return;  // No known enemy base yet
    }

    BWAPI::Unit attackTarget = nullptr;

    // First, attack enemy offensive units
    for (auto& enemy : BWAPI::Broodwar->enemy()->getUnits()) {
        if (enemy->getType().canAttack()) {
            //std::cout << "Attacking enemy unit" << std::endl;
            attackTarget = enemy;
            break;
        }
    }

    // If no offensive units, attack workers
    if (!attackTarget) {
        for (auto& enemy : BWAPI::Broodwar->enemy()->getUnits()) {
            if (enemy->getType().isWorker()) {
                //std::cout << "Attacking enemy worker" << std::endl;
                attackTarget = enemy;
                break;
            }
        }
    }

    // If a target was found, attack it
    if (attackTarget && attackTarget->exists()) {
        for (auto& unit : squad.units) {
            if (unit && unit->exists() && attackTarget->exists()) {
                //std::cout << "Attacking " << attackTarget->getType() << std::endl;
                unit->attack(attackTarget);
            }
        }
    }
    // Otherwise, move towards the enemy base
    else {
        for (auto& unit : squad.units) {
            //std::cout << "Moving towards enemy base" << std::endl;
            if (unit && unit->exists()) {
                unit->move(enemyBase);
            }
        }
    }
}
