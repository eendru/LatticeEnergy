#include "Lattice.hh"
#include <cmath>
#include <ctime>

const double PI  = 3.141592653589793238463;

double Lattice::RandomNumberInRange(double min, double max)
{
    double f = (double) std::rand() / RAND_MAX;
    return min + f * (max  - min);
}

uint16_t IntRandomNumberInRange(uint16_t min, uint16_t max)
{
    return (min + (rand() % (uint16_t)(max - min + 1)));
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

Lattice::Lattice(uint64_t N, double L, double sigma, double r, uint16_t q, double energy)
            : _N(N), _L(L), _sigma(sigma), _r(r), _q(q), _energy(0.0)
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
        point._color = std::vector<uint16_t>(_q, 0);
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

int Lattice::Coloring()
{
    for (uint64_t i = 0; i < _points.size(); ++i) {
        uint16_t color = IntRandomNumberInRange(2, _q);
        _points[i]._color[color] = 1;
    }
}

double Lattice::CalculateEnergy()
{
    double A = (_L * _L *_q) / (2 * PI * _N * _N * _sigma);
    _energy = 0.0;
    for (uint64_t n = 0; n < _points.size(); ++n) {
        for (size_t i = 0; i < _q; ++i) {
            for (auto itb = _points[n]._neighbors.begin(), ite = _points[n]._neighbors.end();
                 itb != ite; ++itb)
            {
                _energy += _points[*itb]._color[i] * _points[n]._color[i];
            }
        }
    }
    _energy = A * _energy;
    return _energy;
}
