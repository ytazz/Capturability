#include "gnuplot.h"

namespace Capt {

Gnuplot::Gnuplot() {
  gp = popen("gnuplot -persist", "w");

  if (!gp) {
    std::cerr << ( "gnuplot not found" );
  }
  color = {{1, "grey80"}, {2, "grey50"}, {3, "grey20"}, {4, "black"},
           {5, "gold"},   {6, "cyan"},   {7, "violet"}, {8, "purple"}};
}

Gnuplot::~Gnuplot() {
  fprintf(gp, "exit\n");
  pclose(gp);
}

void Gnuplot::operator()(const std::string &command) {
  fprintf(gp, "%s\n", command.c_str() );
  fflush(gp);
}

}