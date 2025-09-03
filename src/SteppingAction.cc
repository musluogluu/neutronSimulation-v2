#include "SteppingAction.hh"
#include "RunAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction(RunAction* runAction)
    : G4UserSteppingAction(), fRunAction(runAction)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4Track* track = step->GetTrack();
    G4String particleName = track->GetDefinition()->GetParticleName();

    // Nötronun hedeften çıktığını kontrol eder
    if (particleName == "neutron" && step->GetPreStepPoint()->GetPhysicalVolume() && step->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Target" && step->GetPostStepPoint()->GetPhysicalVolume() && step->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "World") {
        
        G4double energy = track->GetKineticEnergy();
        G4ThreeVector momentumDirection = track->GetMomentumDirection();

        // Nötronun çıkış açısını hesaplar (z eksenine göre)
        G4double angle = momentumDirection.angle(G4ThreeVector(0,0,1));

        // Verileri RunAction'a gönderir
        if (fRunAction) {
            fRunAction->AddNeutronData(energy, angle);
            fRunAction->AddTotalNeutron();
        }
    }
}