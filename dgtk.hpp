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
	// This class manage the basic type used in cppdas dataset.
	class cppdas_basic_type
	{
		friend class cppdas_data_element;
		friend class cppdas_dataset;
		protected:
			enum cppdas_type
			{
				pd_int,   // Integer type: long long
				pd_float, // Float   type: double
				pd_string // String  type: std::string
			};
	};
	
	// cppdas_data_element is the base class can storage a data
	// we use _type to identifier each type, and each type was
	// storaged by byte-stream using std::string.
	class cppdas_data_element
	{
		friend class cppdas_dataset;
		public:
			cppdas_data_element() = default;
			cppdas_data_element(const cppdas_data_element&) = default;
			cppdas_data_element(cppdas_data_element&&) = default;
			cppdas_data_element& operator=(const cppdas_data_element&) =
				default;
			~cppdas_data_element();
		private:
			std::string _data;
	};
	
	// cppdas_dataset is a class that storage linear dataset.
	class cppdas_dataset
	{
		friend class cppdas;
		public:
			cppdas_dataset() = default;
			cppdas_dataset(const cppdas_dataset&) = default;
			cppdas_dataset(cppdas_dataset&&) = default;
			cppdas_dataset& operator=(const cppdas_dataset&) = default;
			~cppdas_dataset() = default;
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
	
	// The default character used in string split.
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
	
	template <typename _ElemType>
	class matrix_base
	{
		
	};
}