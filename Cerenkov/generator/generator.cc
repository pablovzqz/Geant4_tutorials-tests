#include "../generator/generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fParticleGun = new G4ParticleGun(1);
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *proton = particleTable->FindParticle("proton");

    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0)); 
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleMomentum(100*GeV);
    fParticleGun->SetParticleDefinition(proton);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* event)
{

    fParticleGun->GeneratePrimaryVertex(event);
}
