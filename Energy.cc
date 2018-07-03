#include "Lattice.hh"

int main()
{
    Lattice lattice(100000);
    lattice.GeneratePoints();
    lattice.BuildNeighbors();
    lattice.BarChart();

    return 0;
}
