dgtkCoreFiles = dgtk.cpp dgtk.hpp

make: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14

compile: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14
	rm dgtk

test: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14
	./dgtk
	rm dgtk

gitminorchanges:
	git add -A .
	git commit -m "Minor changes and improvements"
	git push
