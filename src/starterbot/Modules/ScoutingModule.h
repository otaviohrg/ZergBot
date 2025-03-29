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

    // ��������߼���ÿ֡����
    void update(Blackboard* bb);

    // ��ȡ�з������Ƿ����ҵ�
    bool isEnemyBaseFound() const;

    bool isSecondBaseFound() const;

private:
    // ��鵥λ����
    void assignScouts();        // �����ʼ��鵥λ��Overlord / Zergling��
    void updateScouts();        // ������鵥λ״̬
    void exploreExpansions();   // �����չ����

    void initializeScoutingPositions();  // ��ʼ���з���������
    void initializeExpansionPositions(); // ��ʼ����չ��������

    // ���Ŀ�����
    std::deque<BWAPI::TilePosition> scoutingPositions;   // ���Ŀ��㣨Ǳ�ڵз����أ�
    std::deque<BWAPI::TilePosition> expansionPositions;  // ��չ����Ŀ���

    // ��¼�������鵥λ
    std::unordered_set<BWAPI::Unit> overlordScouts;      // ��¼���ɳ��� Overlord
    std::unordered_set<BWAPI::Unit> zerglingScouts;      // ��¼���ɳ��� Zergling
    std::unordered_map<BWAPI::Unit, BWAPI::TilePosition> scoutTargets; // ��¼��λ��ǰĿ��

    // ���״̬
    bool enemyBaseFound;
    bool moreBaseFound;
    BWAPI::TilePosition enemyBase;
    BWAPI::TilePosition moreBase;
};
