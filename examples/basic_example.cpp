#include "model.hpp"
#include "matrix.hpp"
#include <string>
#include <fstream>
#include <iostream> // print to console (cout)



int main(int argc, char *argv[])
{

  // read simulation name and output directory from arguments
  std::string sname;
  std::string fname;
  std::string odir;
  if(argc<4) {
    std::cerr << "Not enough arguments:" 
	      << " ./basic_example <sim-name> <input-file-name> <output-directory>" << std::endl;
    return 0;
  }
  else {
    sname = argv[1];
    fname = argv[2];
    odir = argv[3];
  }

	Model model(fname);
	
	model.iterate(sname, odir);
	
}
