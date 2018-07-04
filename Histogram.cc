#include "Histogram.hh"

#include <gsl/gsl_histogram.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <ctime>

Histogram::Histogram(const Lattice &l) : _l(l)
{
}

static std::string Timestamp()
{
    const auto now = std::chrono::system_clock::now();
    const auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
    const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                                    now.time_since_epoch()) % 1000;
    std::stringstream nowss;
    nowss << std::put_time(std::localtime(&nowAsTimeT), "%a_%b_%d_%Y_%T")
          << '.' << std::setfill('0') << std::setw(3) << nowMs.count();

    return nowss.str();
}

std::string Histogram::Filename(std::string &prefix, std::string &postfix)
{
    std::string data_string = "_N_" + std::to_string(_l.N()) +
                              "_L_" + std::to_string(_l.L()) +
                              "_sigma_" + std::to_string(_l.Sigma()) +
                              "_r_" + std::to_string(_l.R());

    return prefix + "_" + Timestamp() + data_string + "." + postfix;
}

void Histogram::Build(std::string &prefix, std::string &postfix)
{
    gsl_histogram * h = gsl_histogram_alloc(_l.PointsSize());
    gsl_histogram_set_ranges_uniform (h, 0, _l.N()/(_l.L() *_l.L()));

    for (size_t i = 0; i < _l.PointsSize(); ++i)
        gsl_histogram_increment(h, _l.NeighborsSize(i));

    FILE *file;
    std::string filename = Filename(prefix, postfix);
    file = fopen(filename.c_str(), "w");

    if (!file) {
        std::cerr << "Something going bad with open '" << filename << "'" << std::endl;
        return;
    }

    gsl_histogram_fprintf(file, h, "%g", "%g");
    gsl_histogram_free(h);
    fclose(file);
}
