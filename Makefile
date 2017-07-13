dgtkCoreFiles = dgtk.cpp dgtk.hpp

make: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14

test: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14
	rm dgtk

run: $(dgtkCoreFiles)
	g++ dgtk.cpp -o dgtk --std=c++14
	./dgtk
	rm dgtk

gitminorchanges:
	git add -A .
	git commit -m "Minor changes and improvements"
	git push

gitpush:
	git add -A .
	git commit
	git push

gitstash:
	git stash
