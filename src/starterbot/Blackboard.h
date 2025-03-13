#pragma once

#include <BWAPI.h>
#include <unordered_set>
#include "BT/Data.h"

class Blackboard
{
public:
    Data* pData;
    Blackboard();
    void reserveResources(int minerals, int gas);
    void unreserveResources(int minerals, int gas);
    void updateResources();
};
