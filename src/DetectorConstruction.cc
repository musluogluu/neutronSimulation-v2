#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Maddeleri tanımlar
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* worldMaterial = nistManager->FindOrBuildMaterial("G4_Galactic"); // Vakum
    G4Material* targetMaterial = nistManager->FindOrBuildMaterial("G4_Cu"); // Hedef materyal

    // Dünya hacmini oluşturur
    G4Box* worldSolid = new G4Box("World", 1*m, 1*m, 1*m);
    G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, worldMaterial, "World");
    G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0, G4ThreeVector(), worldLogical, "World", 0, false, 0);

    // Silindiri oluşturur
    G4double innerRadius = 0. * cm;
    G4double outerRadius = 5. * cm; // 10 cm çap
    G4double halfLength = 30. * cm; // 60 cm uzunluk
    G4Tubs* targetSolid = new G4Tubs("Target", innerRadius, outerRadius, halfLength, 0., 360.*deg);
    G4LogicalVolume* targetLogical = new G4LogicalVolume(targetSolid, targetMaterial, "Target");

    // Silindiri dünyaya yerleştirir
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), targetLogical, "Target", worldLogical, false, 0);

    return worldPhysical;
}