#include "BT_ACTION_ATTACK_MOVE.h"
#include "../Data.h"

BWAPI::Position from_Tile_position(const BWAPI::TilePosition& tilePosition) {
    return BWAPI::Position(tilePosition.x * 32 + 16, tilePosition.y * 32 + 16);
}
BWAPI::TilePosition to_Tile_position(const BWAPI::Position& position) {
    return BWAPI::TilePosition(position.x / 32, position.y / 32);
}
BT_ACTION_ATTACK_MOVE::BT_ACTION_ATTACK_MOVE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_ATTACK_MOVE::Evaluate(void* data) {
    auto* castedData = static_cast<Data*>(data);
    BWAPI::Position targetPosition = from_Tile_position(castedData->enemyBase);
    if (!targetPosition.isValid()) {
        return BT_NODE::RUNNING;
    }

    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType().canAttack() && unit->isIdle()) {
            unit->attack(targetPosition);
        }
    }
    return BT_NODE::SUCCESS;
}

std::string BT_ACTION_ATTACK_MOVE::GetDescription() {
    return "Attack move to enemy's base or target location.";
}

BT_NODE::State BT_ACTION_ATTACK_MOVE::AttackMove(void* data) {
    return static_cast<BT_ACTION_ATTACK_MOVE*>(data)->Evaluate(data);
}
