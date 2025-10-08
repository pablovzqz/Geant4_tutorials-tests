#include "../generator/generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* event)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *proton = particleTable->FindParticle("proton");

    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0)); 
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
    fParticleGun->SetParticleMomentum(100*GeV);
    fParticleGun->SetParticleDefinition(proton);

    fParticleGun->GeneratePrimaryVertex(event);
}
