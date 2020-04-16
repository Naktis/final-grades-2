main: validation.o file.o funList.o funVector.o funDeque.o containers.o student.o
	g++ -o main main.cpp validation.o file.o funList.o funVector.o funDeque.o containers.o student.o
validation:
	g++ -c validation.cpp
file:
	g++ -c file.cpp
funList:
	g++ -c funList.cpp
funVector:
	g++ -c funVector.cpp
funDeque:
	g++ -c funDeque.cpp
containers:
	g++ -c containers.cpp
student:
	g++ -c student.cpp
clean-win:
	del *.o main
clean-unix:
	rm *.o main