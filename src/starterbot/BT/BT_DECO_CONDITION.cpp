#include "BT_DECO_CONDITION.h"
#include <iostream>

BT_DECO_CONDITION::BT_DECO_CONDITION(std::string name, BT_NODE* parent, CONDITION_CBK conditionCBK)
    : BT_DECORATOR(name, parent), ConditionCBK(conditionCBK) {
}

BT_NODE::State BT_DECO_CONDITION::Evaluate(void* data) {
    if (ConditionCBK(data)) {
        return Children[0]->Evaluate(data);
    }
    return BT_NODE::FAILURE;
}

std::string BT_DECO_CONDITION::GetDescription() {
    return "DECO_CONDITION";
}