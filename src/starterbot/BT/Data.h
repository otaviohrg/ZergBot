#pragma once
#include <unordered_set>
#include <BWAPI.h>

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 9
#define NWANTED_WORKERS_FARMING_MINERALS 9
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
	int nWantedWorkersTotal;
	int nWantedWorkersFarmingMinerals;
	int nWantedWorkersFarmingGas;
	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	std::unordered_set<BWAPI::Unit> unitsFarmingGas;
};
