#pragma once
//#define BT_DEBUG_VERBOSE
 
#include "BT_NODE.h"
#include "BT_LEAF.h"
#include "BT_ACTION.h"
#include "BT_DECORATOR.h"

//Composite notes
#include "BT_SEQUENCER.h"
#include "BT_SELECTOR.h"
#include "BT_PARALLEL_SEQUENCER.h"
#include "BT_PARALLEL_SELECTOR.h"

//Decorators
#include "BT_DECO_CONDITION.h"
#include "BT_DECO_COND_GREATER_THAN.h"
#include "BT_DECO_COND_LESSER_THAN.h"

#include "BT_DECO_INVERTER.h"
#include "BT_DECO_REPEATER.h"
#include "BT_DECO_RETURN_FAILURE.h"
#include "BT_DECO_RETURN_SUCCESS.h"
#include "BT_DECO_UNTIL_FAILURE.h"
#include "BT_DECO_UNTIL_SUCCESS.h"

// Conditions
#include "BT_CONDITION.h"
#include "BT_COND_GREATER_THAN.h"
#include "BT_COND_LESSER_THAN.h"

///Decorator Conditions
#include "BT_STARCRAFT/BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS.h"
#include "BT_STARCRAFT/BT_DECO_CONDITION_NOT_ENOUGH_WORKERS.h"
#include "BT_STARCRAFT/BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY.h"
#include "BT_STARCRAFT/BT_DECO_WAIT_FOR_CONSTRUCTION.h"
#include "BT_STARCRAFT/BT_DECO_WAIT_FOR_RESOURCES.h"
#include "BT_STARCRAFT/BT_DECO_CONDITION_SUPPLY_REACHED.h"
#include "BT_STARCRAFT/BT_ACTION_EXPAND_BASE.h"
#include "BT_STARCRAFT/BT_DECO_CONDITION_NEED_GAS.h"
#include "BT_STARCRAFT/BT_ACTION_BUILD_REFINERY.h"
#include "BT_STARCRAFT/BT_DECO_CONDITION_SUPPLY_NEEDED.h"
#include "BT_STARCRAFT/BT_ACTION_BUILD_SUPPLY_DEPOT.h"
#include "BT_STARCRAFT/BT_ACTION_TRAIN_ZERGLING.h"

///Actions
#include "BT_ACTION_IDLE.h"
#include "BT_ACTION_WAIT.h"
#include "BT_ACTION_LOG.h"

#include "BT_STARCRAFT/BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS.h"
#include "BT_STARCRAFT/BT_ACTION_TRAIN_WORKER.h"
#include "BT_STARCRAFT/BT_ACTION_BUILD_SUPPLY_PROVIDER.h"
#include "BT_STARCRAFT/BT_ACTION_BUILD_BUILDING.h"