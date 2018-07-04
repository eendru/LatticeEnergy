#pragma once

#include "Lattice.hh"

class Histogram {
  public:
    Histogram(const Lattice &l);
    Histogram(const Lattice &&) = delete;

  /*!
   * See example:
   * https://www.gnu.org/software/gsl/manual/html_node/Example-programs-for-histograms.html
   * Build histogram numbers of neighbors using GNU Scientific Library.
   *
   * To visualize results you can use:
   * awk '{print $1, $3 ; print $2, $3}' histogram.dat | graph -T X
   */
    void Build(std::string &prefix, std::string &postfix);

  private:
    /*!
     * Generate filename with given prefix and postfix, also using current timestamp
     * with milliseconds. Example:
     *   histogram_Wed_Jul_04_2018_18:32:43.837_N_100000_L_20.000000_sigma_1.000000_r_0.050000.dat
     *
     * @param[in] prefix
     * @param[in] postfix
     * @return filename
     */
    std::string Filename(std::string &prefix, std::string &postfix);

  private:
    const Lattice &_l;
};
