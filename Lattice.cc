#include "Lattice.hh"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <cmath>

#include <gsl/gsl_histogram.h>

double Lattice::RandomNumberInRange(double min, double max)
{
    double f = (double) std::rand() / RAND_MAX;
    return min + f * (max  - min);
}

double Lattice::Distance(const point_t &p1, const point_t &p2)
{
    double distance_x = p1._x * p1._x - 2 * p1._x * p2._x + p2._x * p2._x;
    double distance_y = p1._y * p1._y - 2 * p1._y * p2._y + p2._y * p2._y;
    return std::sqrt(distance_x + distance_y);
}

bool Lattice::IsNeighbor(point_t &p1, point_t &p2)
{
    double distance = Distance(p1, p2);
    if (distance > _r + _sigma/2 || distance < _r - _sigma/2)
        return false;
    return true;
}

Lattice::Lattice(uint64_t N, double L, double sigma, double r) : _N(N), _L(L), _sigma(sigma), _r(r)
{
    std::srand(std::time(nullptr));
}

void Lattice::GeneratePoints()
{
    for (uint64_t i = 0; i < _N; ++i)
    {
        point_t point;
        point._x = Lattice::RandomNumberInRange(0, _L);
        point._y = Lattice::RandomNumberInRange(0, _L);

        _points.push_back(point);
    }
}

void Lattice::BuildNeighbors()
{
   for (uint64_t i = 0; i < _points.size(); ++i)
   {
       for (uint64_t j = 0; j < _points.size(); ++j)
       {
           if (i != j)
               if (IsNeighbor(_points[i], _points[j]))
                   _points[i]._neighbors.insert(j);
       }
   }
}

static std::string GetTimestamp()
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

std::string Lattice::BuildHistogramFilename(std::string &prefix, std::string &postfix)
{
    std::string data_string = "_N_" + std::to_string(_N) +
                              "_L_" + std::to_string(_L) +
                              "_sigma_" + std::to_string(_sigma) +
                              "_r_" + std::to_string(_r);

    std::string result = prefix + "_" + GetTimestamp() + data_string + "." + postfix;

    return result;
}

void Lattice::Histogram(std::string &prefix, std::string &postfix)
{
    gsl_histogram * h = gsl_histogram_alloc(_points.size());
    gsl_histogram_set_ranges_uniform (h, 0, _N/(_L*_L));

    for (size_t i = 0; i < _points.size(); ++i)
        gsl_histogram_increment(h, _points[i]._neighbors.size());

    FILE *file;
    std::string filename = BuildHistogramFilename(prefix, postfix);
    file = fopen(filename.c_str(), "w");

    if (!file) {
        std::cerr << "Something going bad with open '" << filename << "'" << std::endl;
        return;
    }

    gsl_histogram_fprintf(file, h, "%g", "%g");
    gsl_histogram_free(h);
    fclose(file);
}
