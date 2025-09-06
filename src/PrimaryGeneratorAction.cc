#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include <algorithm>

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0), fCurrentParticleIndex(0)
{
    fParticleGun = new G4ParticleGun(1);
    
    // Işın treni partikül listesini oluşturur
    fParticleList.push_back({"e-", 600}); // elektron
    fParticleList.push_back({"pi-", 18860}); // negatif pion
    fParticleList.push_back({"kaon-", 440}); // negatif kaon

    // Kütleye göre sıralama
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    std::sort(fParticleList.begin(), fParticleList.end(),
        [&](const auto& a, const auto& b) {
            G4ParticleDefinition* pA = particleTable->FindParticle(a.first);
            G4ParticleDefinition* pB = particleTable->FindParticle(b.first);
            return pA->GetPDGMass() < pB->GetPDGMass();
        });
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    if (fCurrentParticleIndex < (G4int)fParticleList.size()) {
        const auto& particleInfo = fParticleList[fCurrentParticleIndex];
        
        G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle(particleInfo.first);
        
        if (particle) {
            fParticleGun->SetParticleDefinition(particle);
            fParticleGun->SetParticleEnergy(10.0 * GeV);
            fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -30. * cm));
            fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

            fParticleGun->GeneratePrimaryVertex(anEvent);
        }

        fParticleList[fCurrentParticleIndex].second--;
        if (fParticleList[fCurrentParticleIndex].second == 0) {
            fCurrentParticleIndex++;
        }
    }
}