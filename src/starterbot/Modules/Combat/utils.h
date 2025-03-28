#ifndef STARTERBOT_MODULES_COMBAT_UTILS_H
#define STARTERBOT_MODULES_COMBAT_UTILS_H
#include <BWAPI.h>

BWAPI::Position from_Tile_position(const BWAPI::TilePosition& tilePosition) {
    return BWAPI::Position(tilePosition.x * 32 + 16, tilePosition.y * 32 + 16);
}
BWAPI::TilePosition to_Tile_position(const BWAPI::Position& position) {
    return BWAPI::TilePosition(position.x / 32, position.y / 32);
}


#endif // STARTERBOT_MODULES_COMBAT_UTILS_H