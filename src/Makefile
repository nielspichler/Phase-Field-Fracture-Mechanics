all : Element.o PhaseElement.o DispElement.o TestClasses.o TestClasses
Element.o : element.cpp element.hpp
	echo ''step1''
	g++ -c -O -g element.cpp
PhaseElement.o : phaseelement.cpp phaseelement.hpp
	echo ''step2''
	g++ -c -O -g phaseelement.cpp
DispElement.o : dispelement.cpp dispelement.hpp
	echo ''step3''
	g++ -c -O -g dispelement.cpp
TestClasses.o : Test_classes.cpp phaseelement.hpp dispelement.hpp
	echo ''step4''
	g++ -c -O -g Test_classes.cpp
TestClasses : phaseelement.o dispelement.o Test_classes.o 
	echo ''step4''
	g++ -O -o TestClasses phaseelement.o dispelement.o Test_classes.o 
