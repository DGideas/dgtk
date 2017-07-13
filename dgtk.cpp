#include "dgtk.hpp"

using pd = dgtk::cppdas;

int main(int argc, char* argv[])
{
	auto iris = pd::read_csv("dataset_example/iris.csv");
	iris.head();
	iris.tail();
	return 0;
}