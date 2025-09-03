# Neutron Simulation

This project is a Geant4 simulation developed as part of the CERN BL4S (Beamline for Schools) competition. Its purpose is to study neutron production caused by a particle beam (such as electrons, pions, kaons, and protons) striking a cylindrical target, 60 cm in length and 10 cm in diameter. The simulation records the energy and angular distributions of the neutrons exiting the target and stores this data in `.root` files for analysis.

## Project Structure

The project includes the following core Geant4 classes and files:

- `CMakeLists.txt`: The CMake build file used to compile the project.
- `src/main.cc`: The main entry point for the simulation.
- `src/DetectorConstruction.cc`: Defines the experimental setup, specifically the cylindrical target.
- `src/PrimaryGeneratorAction.cc`: Generates the particle beam and implements the "particle train" logic.
- `src/src/RunAction.cc`: Collects neutron data throughout the simulation and saves it to files on disk.
- `src/SteppingAction.cc`: Tracks each particle's step, identifies neutrons, and passes their data to `RunAction`.
- `src/ActionInitialization.cc`: Initializes all user action classes (`RunAction`, `SteppingAction`, `PrimaryGeneratorAction`).
- `include/`: Contains all the class header (`.hh`) files.

## Setup and Compilation

To run this project, you must have **Geant4 v11.3.0** and **ROOT** installed on your system.

1.  **Create the Folder Structure:**
    Set up the following folder structure for your project.
    ```
    neutron-simulation/
    ├── CMakeLists.txt
    ├── src/
    └── include/
    ```

2.  **Copy the Files:**
    Copy all source (`.cc`) and header (`.hh`) files into their respective folders.

3.  **Compile the Project:**
    Navigate to the project's root directory (e.g., `neutron-simulation/`), create a `build` folder, and enter it.
    ```bash
    mkdir build
    cd build
    ```
    Then, run the CMake and `make` commands to compile the project.
    ```bash
    cmake ..
    make -j$(nproc)
    ```
    These commands will create an executable file named `geant4-proje` inside the `build` directory.

## Running the Simulation

To run the simulation, use the following command from the `build` directory:

```bash
./simulation