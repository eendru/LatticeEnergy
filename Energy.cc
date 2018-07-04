#include "Lattice.hh"
#include "Histogram.hh"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << "./config.yaml" << std::endl;
        return 0;
    }

    YAML::Node config = YAML::LoadFile(argv[1]);
    if (!config) {
        std::cerr << "YAML have returned null configuration file" << std::endl;
        return 0;
    }

    uint64_t N = config["parameters"]["N"].as<uint64_t>();
    double L = config["parameters"]["L"].as<double>();
    double r = config["parameters"]["r"].as<double>();
    double sigma = config["parameters"]["sigma"].as<double>();

    std::string prefix = config["parameters"]["histogram_filename_prefix"].as<std::string>();
    std::string postfix = config["parameters"]["histogram_filename_postfix"].as<std::string>();

    Lattice lattice(N, L, r, sigma);
    lattice.GeneratePoints();
    lattice.BuildNeighbors();

    Histogram h(lattice);
    h.Build(prefix, postfix);

    return 0;
}
