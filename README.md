# Neutron Simulation

This project is a Geant4 simulation developed as part of the CERN BL4S (Beamline for Schools) competition. It's designed to study neutron production caused by a particle beam striking a target. The simulation records the energy and angular distributions of neutrons exiting the target, storing the data in `.root` files for subsequent analysis.

## Features

* **Customizable Particle Beam**: Easily modify the type and number of particles in the beam.
* **Detailed Data Collection**: Records the kinetic energy and exit angle for each detected neutron.
* **ROOT Integration**: Outputs data directly to `.root` files for seamless analysis.
* **Optimized Performance**: Runs in a non-graphical mode for fast, efficient simulations.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

To compile and run this simulation, you need to have the following installed:

* **Geant4 v11.3.0**
* **ROOT**
* **CMake**
* **A C++ compiler** (e.g., g++)

### Installation

Use `git clone` to download the project to your local machine.
```bash
git clone https://github.com/musluogluu/neutronSimulation-v2.git
cd neutronSimulation-v2
```

### Running the Simulation

To run this simulation, you need the executable file.
```bash
cd build
./simulation
```
