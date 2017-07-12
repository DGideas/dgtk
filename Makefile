dgtkCoreFiles = dgtk.cpp dgtk.hpp

make: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14

test: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14
	rm dgtk