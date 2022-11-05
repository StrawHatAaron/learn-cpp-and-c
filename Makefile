.PHONY=clean

pointers: Pointers.cpp
	sudo g++ -o Pointers Pointers.cpp

vs: PointersVsReferences.cpp
	g++ -o PointersVsReferences PointersVsReferences.cpp

poly: PolyPointers.cpp
	g++ -o PolyPointers PolyPointers.cpp

cherno: ChernoPointer.cpp
	g++ -o ChernoPointer ChernoPointer.cpp 

sock: sockprog_server.cpp
	g++ -o sockprog_server sockprog_server.cpp

clean:

	rm -rf Pointers PointersVsReferences PolyPointers ChernoPointer sockprog_server