#include "../generator/generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
    
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0*eV);  // ← Energía inicial
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* event)
{
    G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
    
    if(particle == G4ParticleTable::GetParticleTable()->FindParticle("geantino"))
    {
        G4int Z = 27;
        G4int A = 60;
        G4double ionCharge = 0.*eplus;
        G4double excitEnergy = 0.*keV;
        
        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, excitEnergy);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(ionCharge);
        fParticleGun->SetParticleEnergy(1.0*eV);  // ← IMPORTANTE
    }
    
    fParticleGun->GeneratePrimaryVertex(event);
}
