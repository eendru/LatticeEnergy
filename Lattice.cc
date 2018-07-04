#include "Lattice.hh"
#include <cmath>
#include <ctime>

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

