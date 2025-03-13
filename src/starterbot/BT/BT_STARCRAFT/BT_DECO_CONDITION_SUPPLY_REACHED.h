#ifndef BT_DECO_CONDITION_SUPPLY_REACHED_H
#define BT_DECO_CONDITION_SUPPLY_REACHED_H

#include "../BT_DECO_CONDITION.h"

class BT_DECO_CONDITION_SUPPLY_REACHED : public BT_DECO_CONDITION {
public:
    BT_DECO_CONDITION_SUPPLY_REACHED(std::string name, BT_NODE* parent, int threshold);
    std::string GetDescription() override;
    static bool IsSupplyReached(void *data);

private:
    int m_threshold;  // Minimum supply needed to trigger the action
};

#endif // BT_DECO_CONDITION_SUPPLY_REACHED_H
