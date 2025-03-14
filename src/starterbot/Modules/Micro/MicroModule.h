#include <BWAPI.h>
#include <list>
#include "Squad.h"  // Include the Squad definition

class MicroModule {
private:
    std::list<Squad> squads;  // List of squads

public:
    MicroModule();

    void updateMicro();
    void executeSquadAttack(Squad& squad);

    std::list<Squad>& GetSquads() { return squads; }  // Allows external access to squads
};