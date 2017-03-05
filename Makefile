# définition des variables utilise pour la compilation
CXX= g++
SRC= main.cpp
SRC1=exp1.cpp
EXEC= main
EXEC1=f2 
SUP=rm -rf
CXXFLAGS=-lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11 -lpthread
all:	
	$(CXX) -Wall $(SRC) -o $(EXEC) $(CXXFLAGS)
	./main
compile:
	$(CXX) -Wall $(SRC1) -o $(EXEC1) $(CXXFLAGS)
	./f2

mrproper:clean
	$(SUP) *.o
clean:
	 $(SUP) *.o



