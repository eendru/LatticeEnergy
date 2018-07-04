#pragma once

#include "Lattice.hh"

class Histogram {
  public:
    Histogram(const Lattice &l);
    Histogram(const Lattice &&) = delete;

  /*!
   * См. пример:
   * https://www.gnu.org/software/gsl/manual/html_node/Example-programs-for-histograms.html
   * Строит гистограмму числа соседей используя GNU Scientific Library.
   *
   * Посмотреть полученную гистограмму можно так:
   * awk '{print $1, $3 ; print $2, $3}' histogram.dat | graph -T X
   */
    void Build(std::string &prefix, std::string &postfix);

  private:
    /*!
     * Генерирует имя файла с данным префиксом и постфиксом.
     * Пример:
     * histogram_Wed_Jul_04_2018_18:32:43.837_N_100000_L_20.000000_sigma_1.000000_r_0.050000.dat
     * @param[in] prefix Строка префикса
     * @param[in] postfix Строка постфикса
     * @return Имя файла(можно считать уникальное).
     */
    std::string Filename(std::string &prefix, std::string &postfix);

  private:
    const Lattice &_l;
};
