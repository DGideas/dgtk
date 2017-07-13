#include "dgtk.hpp"

using pd = dgtk::cppdas;

int main(int argc, char* argv[])
{
	auto iris = pd::read_csv("dataset_example/iris.csv");
	iris.head(10);
	iris.tail(10);
	return 0;
}