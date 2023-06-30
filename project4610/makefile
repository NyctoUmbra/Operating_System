Myprog: main.o Sdisk.o block.o Filesys.o
	g++ main.o Sdisk.o block.o Filesys.o -o myprog

main.o: main.cpp
	g++ -c main.cpp

Sdisk.o: Sdisk.cpp
	g++ -c Sdisk.cpp

block.o: block.cpp
	g++ -c block.cpp

Filesys.o: Filesys.cpp
	g++ -c Filesys.cpp

clean:
	rm*.o
