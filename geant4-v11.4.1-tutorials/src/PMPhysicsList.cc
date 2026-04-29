#include "PMPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

PMPhysicsList::PMPhysicsList()
{
    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics());

    // Radioactive devay physics
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    // Decay Physics
    RegisterPhysics(new G4DecayPhysics());
}

PMPhysicsList::~PMPhysicsList()
{
}
