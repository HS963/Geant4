#include "PMPrimaryGenerator.hh"
#include "G4IonTable.hh"

PMPrimaryGenerator::PMPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
    fParticleGun->SetParticleDefinition(particle);

    // Particle Position
    G4double x = 0. * cm;
    G4double y = 0. * cm;
    G4double z = -1. * cm;

    G4ThreeVector pos(x, y, z);

    // Particle Direction
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = 0.;

    G4ThreeVector mom(px, py, pz);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);

}

PMPrimaryGenerator::~PMPrimaryGenerator()
{
    delete fParticleGun;
}

void PMPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // Particle Type
    G4int Z = 9;
    G4int A = 18;
    
    G4double charge = 0. * eplus;
    G4double energy = 0. * keV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    fParticleGun->SetParticleEnergy(energy);

    // Create Vertex
    fParticleGun-> GeneratePrimaryVertex(anEvent);
}