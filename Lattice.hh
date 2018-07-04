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
   * Конструктор решетки.
   * @param[in] N Количество точек решетки.
   * @param[in] L Граница по осям координат.
   * @param[in] sigma Толщина кольца.
   * @param[in] r Радиус кольца.
   */
    Lattice(uint64_t N = 1000, double L = 20.0, double sigma = 0.05, double r = 1);
  /*!
   * Генерирует N точек в интервале (0, L).
   * Будет заполнен вектор std::vector<double>_points.
   */
    void GeneratePoints();

  /*!
   * Находит соседей(номера) для каждой точки из вектора std::vector<double> _points.
   */
    void BuildNeighbors();

  /*!
   * Генерирует случайное double число в интервале от min до max.
   */
    static double RandomNumberInRange(double min, double max);

  /*!
   * Проверяет, являются ли две точки соседями.
   * (distance > _r - _sigma/2) && (distance < _r + _sigma/2)
   */
    bool IsNeighbor(point_t &p1, point_t &p2);

  /*!
   * Вычисляет расстояние между двумя точками(евклидово).
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
