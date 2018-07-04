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

  /*!
   * См. пример:
   * https://www.gnu.org/software/gsl/manual/html_node/Example-programs-for-histograms.html
   * Строит гистограмму числа соседей используя GNU Scientific Library.
   *
   * Посмотреть полученную гистограмму можно так:
   * awk '{print $1, $3 ; print $2, $3}' histogram.dat | graph -T X
   */
    void Histogram(std::string &prefix, std::string &postfix);

  private:
    std::string BuildHistogramFilename(std::string &prefix, std::string &postfix);

  private:
    double _sigma;
    double _r;
    uint64_t _N;
    double _L;
    std::vector<point_t> _points;
};
