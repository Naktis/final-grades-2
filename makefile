OFLAG = -O2

main: validation.o file.o funList.o funVector.o funDeque.o containers.o student.o
	g++ $(OFLAG) -o main main.cpp validation.o file.o funList.o funVector.o funDeque.o containers.o student.o
validation:
	g++  -c $(OFLAG) validation.cpp
file:
	g++  -c $(OFLAG) file.cpp
funList:
	g++ $(OFLAG) -c funList.cpp
funVector:
	g++ $(OFLAG) -c funVector.cpp
funDeque:
	g++ $(OFLAG) -c funDeque.cpp
containers:
	g++ $(OFLAG) -c containers.cpp
student:
	g++ $(OFLAG) -c student.cpp
clean-win:
	del *.o main
clean-unix:
	rm *.o main