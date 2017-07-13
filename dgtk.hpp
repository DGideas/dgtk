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
	
	// Like Python pandas, cppdas is a class about C++ data analysis.
	// If you use:
	// using pd = dgtk::cppdas;
	// It looks like python pandas :)
	class cppdas
	{
		public:
			static const std::vector<std::string> defaultSplitCharacter;
			static cppdas_dataset read_csv(const std::string&,
				const std::vector<std::string>&, const bool&);
			static cppdas_dataset read_csv(const std::string&,
				const bool&);
			static cppdas_dataset read_csv(std::fstream&,
				const std::vector<std::string>&, const bool&);
			static cppdas_dataset read_csv(std::fstream&,
				const bool&);
			static cppdas_dataset read_csv_base(std::fstream&,
				const std::vector<std::string>&, const bool&);
	};
	
	const std::vector<std::string> cppdas::defaultSplitCharacter = {","};
	
	cppdas_dataset cppdas::read_csv(const std::string& _string,
		const std::vector<std::string>& _split = {","},
		const bool& _haveHeader = true)
	{
		std::fstream fileHandle(_string, std::ios::in);
		return read_csv_base(fileHandle, _split, _haveHeader);
	}
	
	cppdas_dataset cppdas::read_csv(const std::string& _string,
		const bool& _haveHeader)
	{
		std::fstream fileHandle(_string, std::ios::in);
		return read_csv_base(fileHandle, defaultSplitCharacter, _haveHeader);
	}
	
	cppdas_dataset cppdas::read_csv(std::fstream& _fsHandle,
		const std::vector<std::string>& _split = {","},
		const bool& _haveHeader = true)
	{
		return read_csv_base(_fsHandle, _split, _haveHeader);
	}
	
	cppdas_dataset cppdas::read_csv(std::fstream& _fsHandle,
		const bool& _haveHeader)
	{
		return read_csv_base(_fsHandle, defaultSplitCharacter, _haveHeader);
	}
	
	cppdas_dataset cppdas::read_csv_base(std::fstream& _fsHandle,
		const std::vector<std::string>& _split,
		const bool& _haveHeader)
	{
		
	}
}