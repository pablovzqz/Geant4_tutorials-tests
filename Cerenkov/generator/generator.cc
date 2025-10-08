#include "../generator/generator.hh"
#include "Randomize.hh"

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

    const G4double R_max = 400*mm;       
    const G4double H     = 100*mm;      
    const G4ThreeVector center(0,0,0);  

    G4double r     = R_max * std::sqrt(G4UniformRand());
    G4double theta = 2 * CLHEP::pi * G4UniformRand();
    G4double z     = center.z() - H/2 + H * G4UniformRand();

    G4double x = center.x() + r * std::cos(theta);
    G4double y = center.y() + r * std::sin(theta);

    G4ThreeVector position(x,y,z);


    fParticleGun->SetParticlePosition(position); 
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
    fParticleGun->SetParticleMomentum(100*GeV);
    fParticleGun->SetParticleDefinition(proton);

    fParticleGun->GeneratePrimaryVertex(event);
}
