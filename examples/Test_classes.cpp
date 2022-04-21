#include "matrix.cpp"
//#include "phaseelement.cpp"
//#include "dispelement.cpp"

int main(/*int argc, char *argv[]*/) {

	Matrix A(2,2);
	
	
	std::cout<<"A = \n"<<A<<"\n";

	std::vector<double> x={1,2};
	
	A(0,0)=1.;
	A(1,0)=2.;
	A(1,1)=3.;
	A(0,1)=4.;
	
	std::vector<double> B = A*x;
	
	std::cout<<"A = \n"<<A<<"\n";
	std::cout<<"B = \n"<<B<<"\n";
	
	Matrix C(1,2);
	C(0,0) = 1; 
	C(0,1) = 4; 
	
	std::cout<<"cb = \n"<<C*B<<"\n";

	Matrix C1(1,3);
	C1(0,0) = 1; 
	C1(0,1) = 2;
	C1(0,2) = 3; 
	std::vector<double> x1={1,2,3};
	std::cout<<"C1 = \n"<<C1<<"\n";
	std::cout<<"c1x1 = \n"<<(C1*x1)[0]<<"\n";
	
	A*=3.;
	std::cout<<"A = \n"<<A<<"\n";
	Matrix A1 = A*3.;
	std::cout<<"A1 = \n"<<A1<<"\n";
	Matrix A1A = A1 + A;
	std::cout<<"A1 + A = \n"<<A1A<<"\n";
	
	Matrix A1mA = A1 - A;
	std::cout<<"A1 - A = \n"<<A1mA<<"\n";
	A += A1;
	std::cout<<"A = \n"<<A<<"\n";
	
	std::cout<<"c1+x1 = \n"<<(C1+x1)<<"\n";
	
	Matrix productA = A*A1;
	std::cout<<"A*A1 = \n"<<productA<<"\n";
	
	A.resize(2,3);
	A(0,0) = 1; A(0, 1) = 0.5; A(0, 2) = -0.5; 
	A(1,0) = 1; A(1, 1) = 2; A(1, 2) = -1;
	
	A1.resize(3,4); 
	A1(0,0) = 1; A1(0, 1) = 0.5; A1(0, 2) = 0; A1(0,3) = -1; 
	A1(1,0) = 0; A1(1, 1) = 0; A1(1, 2) = 0; A1(1,3) = 1; 
	A1(2,0) = -1; A1(2, 1) = -0.5; A1(2, 2) = 2; A1(2,3) = 0; 
	
	std::cout<<"A = \n"<<A<<"\n";
	std::cout<<"A1 = \n"<<A1<<"\n";
	
	Matrix product2A = A*A1;
	std::cout<<"A*A1 = \n"<<product2A<<"\n";
	
	std::cout<<"A*x1 = \n"<<A*x1<<"\n";
	
	Matrix C2;
	
	C1.transpose(C2);
	std::cout<<"C2 = \n"<<C2<<"\n";
	std::cout<<"c2+x1 = \n"<<C2+x1<<"\n";
	std::cout<<"C1+x1 = \n"<<(C1+x1)<<"\n";
	std::cout<<"toVect= \n"<<C1.toVector()<<"\n";
	
	// test element constructors
	/*
	Matrix loc_coordinates(4,2);
	loc_coordinates(0,0) = 0.; loc_coordinates(0,1) = 0.;
	loc_coordinates(1,0) = 1.; loc_coordinates(1,1) = 0.;
	loc_coordinates(2,0) = 1.; loc_coordinates(2,1) = 1.;
	loc_coordinates(3,0) = 0.; loc_coordinates(3,1) = 1.;
	
	std::vector<double> loc_d = {0., 0., 0., 0.};
	std::vector<double> loc_H = {0., 0., 0., 0.};
	std::vector<double> loc_u = {0., 0., 0., 0., 0., 0., 0., 0.};
	
	Matrix Ke_d(4,4);
	std::vector<double> res_d;
	res_d.resize(4);
	Matrix Ke_u(8,8);
	std::vector<double> res_u;
	res_u.resize(8);
	
	// the element is created
	PhaseElement el_d(loc_coordinates, loc_d, loc_H);
	DispElement el_u(loc_coordinates, loc_d, loc_u);
	// Local stiffness matrices
	el_d.GetStiffnessAndRes(Ke_d, res_d);
	el_u.GetStiffnessAndRes(Ke_u, res_u);
	
	std::cout<<"Ke_d = \n"<<Ke_d<<"\n";
	std::cout<<"res_d = \n"<<res_d<<"\n";
	std::cout<<"Ke_u = \n"<<Ke_u<<"\n";
	std::cout<<"res_u = \n"<<res_u<<"\n";
*/
	
return 0;
}
