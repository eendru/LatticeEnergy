#include "Lattice.hh"
#include <cstdlib>
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

Lattice::Lattice(uint64_t N, uint64_t L, double sigma, double r) : _N(N), _L(L), _sigma(sigma), _r(r)
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

void Lattice::BarChart()
{
     gsl_histogram * h = gsl_histogram_alloc(_points.size());
     gsl_histogram_set_ranges_uniform (h, 0, _N/(_L*_L));
     for (size_t i = 0; i < _points.size(); ++i) {
         gsl_histogram_increment(h, _points[i]._neighbors.size());
     }

     gsl_histogram_fprintf (stdout, h, "%g", "%g");
     gsl_histogram_free (h);
}
