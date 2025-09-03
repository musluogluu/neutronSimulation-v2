#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TSystem.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

// This ROOT macro processes simulation outputs to create professional-looking energy and angle distribution plots.
void draw_hists() {

    // Set a clean, professional plotting style
    gStyle->SetOptStat(0); // Disable the statistics box
    gStyle->SetPalette(kRainBow); // Set a pleasant color palette
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetFrameLineColor(kBlack);
    gStyle->SetFrameLineWidth(2);
    gStyle->SetPadTopMargin(0.08);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.05);

    // Set font styles for titles and labels
    gStyle->SetTitleFont(42, "xyz");
    gStyle->SetTitleSize(0.045, "xyz");
    gStyle->SetLabelFont(42, "xyz");
    gStyle->SetLabelSize(0.04, "xyz");
    gStyle->SetTitleOffset(1.2, "x");
    gStyle->SetTitleOffset(1.2, "y");

    // Neutron Energy Distribution Plot
    //-------------------------
    TFile *energyFile = new TFile("neutron_energy.root");
    if (energyFile->IsZombie()) {
        std::cerr << "Error: 'neutron_energy.root' file could not be opened." << std::endl;
        return;
    }

    TTree *energyTree = (TTree*)energyFile->Get("NeutronEnergy");
    if (!energyTree) {
        std::cerr << "Error: 'NeutronEnergy' tree not found." << std::endl;
        energyFile->Close();
        return;
    }

    // Create the histogram with a descriptive title and axis labels
    TH1F *hEnergy = new TH1F("hEnergy", "Neutron Energy Distribution;Kinetic Energy (MeV);Number of Events", 100, 0, 1000);
    hEnergy->SetLineColor(kRed + 1);
    hEnergy->SetFillColor(kRed - 9);
    hEnergy->SetLineWidth(2);
    hEnergy->SetFillStyle(1001);

    // Draw the data from the tree into the histogram
    energyTree->Draw("energy>>hEnergy", "", "goff");

    TCanvas *c1 = new TCanvas("c1", "Neutron Energy Distribution", 800, 600);
    c1->SetGrid(); // Add a grid for better readability
    
    hEnergy->Draw("HIST");
    gPad->SetLogy(); // Set Y-axis to a logarithmic scale

    c1->SaveAs("neutron_energy_distribution.png");

    // Clean up memory
    delete c1;
    delete hEnergy;
    energyFile->Close();
    delete energyFile;

    // Neutron Angle Distribution Plot
    //---------------------
    TFile *angleFile = new TFile("neutron_angle.root");
    if (angleFile->IsZombie()) {
        std::cerr << "Error: 'neutron_angle.root' file could not be opened." << std::endl;
        return;
    }

    TTree *angleTree = (TTree*)angleFile->Get("NeutronAngle");
    if (!angleTree) {
        std::cerr << "Error: 'NeutronAngle' tree not found." << std::endl;
        angleFile->Close();
        return;
    }

    // Create the histogram with a descriptive title and axis labels
    TH1F *hAngle = new TH1F("hAngle", "Neutron Angle Distribution;Exit Angle (rad);Number of Events", 100, 0, 1.6);
    hAngle->SetLineColor(kBlue + 1);
    hAngle->SetFillColor(kBlue - 9);
    hAngle->SetLineWidth(2);
    hAngle->SetFillStyle(1001);

    // Draw the data from the tree into the histogram
    angleTree->Draw("angle>>hAngle", "", "goff");
    
    TCanvas *c2 = new TCanvas("c2", "Neutron Angle Distribution", 800, 600);
    c2->SetGrid(); // Add a grid
    
    hAngle->Draw("HIST");

    c2->SaveAs("neutron_angle_distribution.png");

    // Clean up memory
    delete c2;
    delete hAngle;
    angleFile->Close();
    delete angleFile;
}