#pragma once
#include <BWAPI.h>
#include <unordered_set>
#include <deque>
#include "../Blackboard.h"

//class ScoutingModule {
//public:
//    ScoutingModule();
//    ~ScoutingModule();
//
//    void assignInitialOverlord();
//    void updateOverlordScouting();
//    void sendZerglingScouts();
//    void exploreUnscoutedLocations();
//    void exploreMoreBase();
//    void update(Blackboard* bb);
//    bool isEnemyBaseFound() const;
//    //bool isMoreBaseFound() const;
//
//
//private:
//    bool enemyBaseFound;
//    bool moreBaseFound;
//    BWAPI::TilePosition enemyBase;
//    BWAPI::TilePosition moreBase;
//    std::deque<BWAPI::TilePosition> scoutingPositions;
//    std::deque<BWAPI::TilePosition> expansionPositions;
//    std::unordered_set<BWAPI::Unit> overlordScouts;
//    std::unordered_set<BWAPI::Unit> zerglingScouts;
//};

class ScoutingModule {
public:
    ScoutingModule();
    ~ScoutingModule();

    // 更新侦查逻辑，每帧调用
    void update(Blackboard* bb);

    // 获取敌方基地是否已找到
    bool isEnemyBaseFound() const;

    bool isSecondBaseFound() const;

private:
    // 侦查单位分配
    void assignScouts();        // 分配初始侦查单位（Overlord / Zergling）
    void updateScouts();        // 更新侦查单位状态
    void exploreExpansions();   // 侦查扩展基地

    void initializeScoutingPositions();  // 初始化敌方基地侦查点
    void initializeExpansionPositions(); // 初始化扩展基地侦查点

    // 侦查目标管理
    std::deque<BWAPI::TilePosition> scoutingPositions;   // 侦查目标点（潜在敌方基地）
    std::deque<BWAPI::TilePosition> expansionPositions;  // 扩展基地目标点

    // 记录分配的侦查单位
    std::unordered_set<BWAPI::Unit> overlordScouts;      // 记录已派出的 Overlord
    std::unordered_set<BWAPI::Unit> zerglingScouts;      // 记录已派出的 Zergling
    std::unordered_map<BWAPI::Unit, BWAPI::TilePosition> scoutTargets; // 记录单位当前目标

    // 侦查状态
    bool enemyBaseFound;
    bool moreBaseFound;
    BWAPI::TilePosition enemyBase;
    BWAPI::TilePosition moreBase;
};
