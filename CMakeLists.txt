# Projenin minimum CMake sürümünü belirtir
cmake_minimum_required(VERSION 3.16)

# Projenin adını belirler
project(simulation)

# ROOT'un derleme dizinini belirtir
set(ROOT_DIR "/home/hexon/root_install/root-build")

# Geant4'ü bulur ve gerekli değişkenleri tanımlar
find_package(Geant4 REQUIRED)

# ROOT kütüphanesini bulur ve gerekli değişkenleri tanımlar
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

# Başlık dosyalarının yolunu ekler
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Kaynak dosyalarını tanımlar
file(GLOB SOURCES
      src/main.cc
      src/DetectorConstruction.cc
      src/PrimaryGeneratorAction.cc
      src/ActionInitialization.cc
      src/RunAction.cc
      src/EventAction.cc
      src/SteppingAction.cc)

# Yürütülebilir dosyayı oluşturur
add_executable(${PROJECT_NAME} ${SOURCES})

# Gerekli kütüphaneleri bağlar
target_link_libraries(${PROJECT_NAME}
                      ${Geant4_LIBRARIES}
                      ${ROOT_LIBRARIES})