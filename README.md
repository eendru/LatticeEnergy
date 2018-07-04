# LatticeEnergy
We are going to generate Lattice and calculate Lattice Energy.


* libyaml-cpp - for parse YAML configuration file.
* libgsl0ldbl - for build histogram.

Dependencies:
```sudo apt-get install libyaml-cpp-dev libgsl0ldbl```

Build steps:

```
mkdir .build
cd .build
cmake ..
make
```

Run step:

```
./LatticeEnergy ./config.yaml
```
