#pragma once
#include "../BT_ACTION.h"

class BT_ACTION_RESEARCH_METABOLIC_BOOST : public BT_ACTION {
public:
BT_ACTION_RESEARCH_METABOLIC_BOOST(std::string name, BT_NODE* parent);
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;

private:
    BT_NODE::State ResearchMetabolicBoost(void* data);
};

