#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "TFile.h"
#include "TTree.h"
#include <fstream>
#include "G4SystemOfUnits.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    void AddNeutronData(G4double energy, G4double angle);
    void AddTotalNeutron();
    
private:
    G4int fTotalNeutronCount;
    TFile* fEnergyFile;
    TTree* fEnergyTree;
    G4double fNeutronEnergy;

    TFile* fAngleFile;
    TTree* fAngleTree;
    G4double fNeutronAngle;

    std::ofstream fTotalNeutronFile;
};

#endif