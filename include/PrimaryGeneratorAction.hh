#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include <vector>
#include <string>
#include <utility>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* anEvent) override;

private:
    G4ParticleGun* fParticleGun;
    std::vector<std::pair<std::string, G4int>> fParticleList;
    G4int fCurrentParticleIndex;
};

#endif