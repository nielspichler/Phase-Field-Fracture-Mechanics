#include "model.hpp"
#include "matrix.cpp"

int main(int argc, char *argv[])
{

  // read simulation name and output directory from arguments
  std::string fname;
  std::string odir;
  if(argc<3) {
    std::cerr << "Not enough arguments:" 
	      << " ./basic_example <sim-name> <output-directory>" << std::endl;
    return 0;
  }
  else {
    fname = argv[1];
    odir = argv[2];
  }

    
  Model model(fname); // constructs the model from input file
  
  for (int step = 0; step < maxiter; step++)
	{
		model.assembly(); // assembles the 2 stifness matrices
		model.apply_bc(); // reduces the stifness matrices
		model.solve(); // solves the equation
		model.update(); // updates the variables
		model.output(odir); // stores the phase field variable in an output directory
	}
	
	std::cout<< "Run sucessful"<< std::endl;


return 0;
}
