// DGideas Cognitive Toolkit
// https://github.com/DGideas/dgtk
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <cstdlib>

namespace dgtk
// All components in DGTK are defined in dgtk namespace.
// In order to avoid look-up ambiguous, using std:: prefix
// when you use standard library components.
{
	// cppdas_dataset is a class that storage linear dataset.
	class cppdas_dataset
	{
		public:
			cppdas_dataset()
			{
				std::cout<<"Construct"<<std::endl;
			}
			~cppdas_dataset()
			{
				std::cout<<"distruct"<<std::endl;
			}
	};
	
	class cppdas
	{
		public:
			static cppdas_dataset read_csv(const std::string&,
				const std::vector<std::string>&);
			static cppdas_dataset read_csv(std::ifstream&,
				const std::vector<std::string>&);
	};
	
	cppdas_dataset cppdas::read_csv(const std::string& _string,
		const std::vector<std::string>& _split)
	{
		cppdas_dataset a;
		return a;
	}
	
	cppdas_dataset cppdas::read_csv(std::ifstream&,
		const std::vector<std::string>& _split)
	{
		cppdas_dataset a;
		return a;
	}
}