#include "model.hpp"
#include "matrix.hpp"
#include <string>
#include <fstream>
#include <iostream> // print to console (cout)



int main(/*int argc, char *argv[]*/)
{

  std::string file_name = "./../../examples/input_paper.inp";
  Model model(file_name);

  model.assembly();
  
  model.apply_bc(1.);
  
  std::cout << "Solver: setup" << std::endl;
  std::shared_ptr<NRsolver> solver;
  solver = std::make_shared<NRsolver>(500, 1e-6);
  model.registerSolver(solver);
  
  std::cout<<*model.get_K_u();
  
  model.solve();
  
  model.output_nodal("Test_output", model.get_Phase(), "Phase");
  

}
