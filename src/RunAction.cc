#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

RunAction::RunAction()
    : G4UserRunAction(), fTotalNeutronCount(0), fEnergyFile(nullptr), fEnergyTree(nullptr),
    fAngleFile(nullptr), fAngleTree(nullptr)
{}

RunAction::~RunAction()
{
    if (fEnergyFile) {
        delete fEnergyFile;
    }
    if (fAngleFile) {
        delete fAngleFile;
    }
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    fTotalNeutronCount = 0;

    fEnergyFile = new TFile("neutron_energy.root", "RECREATE");
    fEnergyTree = new TTree("NeutronEnergy", "Neutron Energy Distribution");
    fEnergyTree->Branch("energy", &fNeutronEnergy, "energy/D");

    fAngleFile = new TFile("neutron_angle.root", "RECREATE");
    fAngleTree = new TTree("NeutronAngle", "Neutron Angle Distribution");
    fAngleTree->Branch("angle", &fNeutronAngle, "angle/D");

    fTotalNeutronFile.open("total_neutrons.txt");
    if (!fTotalNeutronFile.is_open()) {
        G4cout << "UYARI: total_neutrons.txt dosyası açılamadı." << G4endl;
    }
}

void RunAction::EndOfRunAction(const G4Run*)
{
    if (fEnergyFile && fEnergyTree) {
        fEnergyFile->cd();
        fEnergyTree->Write();
    }
    if (fEnergyFile) {
        fEnergyFile->Close();
    }

    if (fAngleFile && fAngleTree) {
        fAngleFile->cd();
        fAngleTree->Write();
    }
    if (fAngleFile) {
        fAngleFile->Close();
    }

    if (fTotalNeutronFile.is_open()) {
        fTotalNeutronFile << fTotalNeutronCount << "\n";
        fTotalNeutronFile.close();
    }
}

void RunAction::AddNeutronData(G4double energy, G4double angle)
{
    fNeutronEnergy = energy;
    fEnergyTree->Fill();

    fNeutronAngle = angle;
    fAngleTree->Fill();
}

void RunAction::AddTotalNeutron()
{
    fTotalNeutronCount++;
}