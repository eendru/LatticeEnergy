# LatticeEnergy
See `Task_Lattice_Energy.pdf`


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
