#include "model.hpp"
#include "matrix.cpp"

int main(/*int argc, char *argv[]*/) {

  std::string ifname = "2Input.inp";
    
  Model model(ifname);
  
  for (int step = 0; step < maxiter; step++)
	{
		model.assemble();
		model.solve();
		model.update();
	}


return 0;
}
