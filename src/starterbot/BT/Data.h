#pragma once
#include <unordered_set>
#include <BWAPI.h>

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 4
#define NWANTED_WORKERS_FARMING_MINERALS 4
#define NWANTED_WORKERS_FARMING_GAS 3

class Data {
public:
	int currMinerals;
	int thresholdMinerals;
	int reservedMinerals;
	int currGas;
	int reservedGas;
	int currSupply;
	int thresholdSupply;
	int currentWorkers;
	int nWantedWorkersTotal = 5;
	int nWantedWorkersFarmingMinerals = 5;
	int nWantedWorkersFarmingGas = 0;

	BWAPI::Race enemyRace;

	std::map<std::string, int> desiredUnits = {
		{"Zerg_Zergling", 0},
		{"Zerg_Mutalisk", 0},
		{"Zerg_Hydralisk", 0},
		{"Zerg_Lurker", 0}
	};
	
	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	std::unordered_set<BWAPI::Unit> unitsFarmingGas;
	std::unordered_set<BWAPI::Unit> unitsScouting;
	BWAPI::TilePosition enemyBase;
};
