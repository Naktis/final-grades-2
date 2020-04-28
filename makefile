OFLAG = -O2

main: validation.o iodata.o modification.o utility.o student.o
	g++ $(OFLAG) -o main main.cpp validation.o iodata.o modification.o utility.o student.o
validation:
	g++ $(OFLAG) -c  validation.cpp
iodata:
	g++ $(OFLAG) -c  file.cpp
modification:
	g++ $(OFLAG) -c modification.cpp
utility:
	g++ $(OFLAG) -c utility.cpp
student:
	g++ $(OFLAG) -c student.cpp
clean-win:
	del *.o main
clean-unix:
	rm *.o main