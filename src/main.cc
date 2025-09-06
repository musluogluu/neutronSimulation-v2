#include "G4RunManagerFactory.hh"
#include "G4PhysListFactory.hh"
#include "FTFP_BERT.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main()
{
    // Rastgele sayı üretecinin tohumunu belirler
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    // Run Manager'ı oluşturur
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::SerialOnly);

    // Gerekli sınıfları ayarlar
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserInitialization(new ActionInitialization());
    
    // Simülasyonu başlatır
    runManager->Initialize();

    // Toplam parçacık sayısı
    G4int totalParticles = 440 + 18860 + 600;
    runManager->BeamOn(totalParticles);

    // Temizleme
    delete runManager;

    return 0;
}