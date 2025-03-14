#ifndef SQUAD_H
#define SQUAD_H

#include <BWAPI.h>
#include <list>

class Squad {
public:
    std::list<BWAPI::Unit> units;  // List of Zerglings in the squad

    Squad() {}

    bool isEmpty() const {
        return units.empty();
    }

    void addUnit(BWAPI::Unit unit) {
        if (unit) units.push_back(unit);
    }

    void removeDeadUnits() {
        units.remove_if([](BWAPI::Unit unit) { return !unit || !unit->exists(); });
    }
};

#endif // SQUAD_H
