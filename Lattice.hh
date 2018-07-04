#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <set>

typedef struct point_s {
    double _x;
    double _y;
    std::set<uint64_t> _neighbors;
} point_t;

class Lattice {
  public:
  /*!
   * @param[in] N Number of points
   * @param[in] L Border on XY axis
   * @param[in] sigma Depth of circle
   * @param[in] r Radius of circle
   */
    Lattice(uint64_t N = 1000, double L = 20.0, double sigma = 0.05, double r = 1);

  /*!
   * Generate N points in interval (0, L) x (0, L).
   * std::vector<double>_points will be filled.
   */
    void GeneratePoints();

  /*!
   * Find number of neighbors for each item in std::vector<double> _points.
   */
    void BuildNeighbors();

  /*!
   * Generate random double number in interval (min, max)
   */
    static double RandomNumberInRange(double min, double max);

  /*!
   * Check, if two points are neighbors
   * (distance > _r - _sigma/2) && (distance < _r + _sigma/2)
   */
    bool IsNeighbor(point_t &p1, point_t &p2);

  /*!
   * Calculate euclid distance between two points
   */
    double Distance(const point_t &p1, const point_t &p2);

  public:

    uint64_t N() const {return _N;}
    double R() const  {return _r;}
    double Sigma() const {return _sigma;}
    double L() const {return _L;}

    size_t PointsSize() const { return _points.size();}
    size_t NeighborsSize(size_t index) const {return _points[index]._neighbors.size();}

  private:
    double _sigma;
    double _r;
    uint64_t _N;
    double _L;
    std::vector<point_t> _points;
};
