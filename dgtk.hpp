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
	template <typename _T>
	void debug(const _T& _something)
	{
		std::cout<<_something<<std::endl;
		return;
	}
	
	// This class manage the basic type used in cppdas dataset.
	class cppdas_basic
	{
		friend class cppdas_data_element;
		friend class cppdas_dataset;
		protected:
			enum type
			{
				pd_int,    // Integer type: long long
				pd_float,  // Float   type: double
				pd_string, // String  type: std::string
				pd_null,   // Null    type: <empty>
				pd_auto    // for RTTI (Runtime Type Indetifier)
			};
	};
	
	// cppdas_data_element is the base class can storage a data
	// we use _type to identifier each type, and each type was
	// storaged by byte-stream using std::string.
	class cppdas_data_element
	{
		friend class cppdas_dataset;
		friend class cppdas_dataset_row;
		public:
			cppdas_data_element() = delete;
			cppdas_data_element(const std::string&,
				const cppdas_basic::type&);
			cppdas_data_element(const cppdas_data_element&) = default;
			cppdas_data_element(cppdas_data_element&&) = default;
			cppdas_data_element& operator=(const cppdas_data_element&) =
				default;
			~cppdas_data_element() = default;
		private:
			std::string _data;
			cppdas_basic::type _type;
	};
	
	cppdas_data_element::cppdas_data_element(const std::string& _data,
		const cppdas_basic::type& _type = cppdas_basic::type::pd_auto)
	{
		this->_data = _data;
		this->_type = _type;
		return;
	}
	
	class cppdas_dataset_column_attr
	{
		public:
			cppdas_dataset_column_attr() = default;
			cppdas_dataset_column_attr(const cppdas_dataset_column_attr&) =
				default;
			cppdas_dataset_column_attr(cppdas_dataset_column_attr&&) =
				default;
			cppdas_dataset_column_attr& operator=(
				const cppdas_dataset_column_attr&) = default;
			~cppdas_dataset_column_attr() = default;
		private:
			
	};
	
	class cppdas_dataset_row
	{
		public:
			void push_back(const cppdas_data_element&);
			std::vector<cppdas_data_element> data;
			size_t number;
			//typedef decltype(data.begin())&& beginIterator;
			//typedef decltype(data.rbegin())&& reverseIterator;
			typedef std::vector<cppdas_data_element>::iterator&& beginIterator;
			typedef std::vector<cppdas_data_element>::reverse_iterator&& reverseIterator;
			beginIterator begin();
			reverseIterator rbegin();
			beginIterator end();
			reverseIterator rend();
			size_t size();
			bool empty();
	};
	
	void cppdas_dataset_row::push_back(const cppdas_data_element& _ele)
	{
		this->data.push_back(_ele);
		return;
	}
	
	cppdas_dataset_row::beginIterator cppdas_dataset_row::begin()
	{
		return this->data.begin();
	}
	
	cppdas_dataset_row::reverseIterator cppdas_dataset_row::rbegin()
	{
		return this->data.rbegin();
	}
	
	cppdas_dataset_row::beginIterator cppdas_dataset_row::end()
	{
		return this->data.end();
	}
	
	cppdas_dataset_row::reverseIterator cppdas_dataset_row::rend()
	{
		return this->data.rend();
	}
	
	size_t cppdas_dataset_row::size()
	{
		return this->data.size();
	}
	
	bool cppdas_dataset_row::empty()
	{
		return this->data.empty();
	}
	
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
		private:
			typedef cppdas_dataset_row DataRow;
		private:
			std::vector<DataRow> data;
			std::vector<std::string> title;
		public:
			void setTitle(const DataRow&);
			void head(const size_t&);
			void tail(const size_t&);
			void info();
		private:
			void rbIterator(const size_t&, const bool&);
	};
	
	void cppdas_dataset::setTitle(const DataRow& _dataRow)
	{
		for (const cppdas_data_element& element: _dataRow.data)
		{
			this->title.push_back(element._data);
		}
		return;
	}
	
	// Like Python pandas.head(), cppdas_dataset::head output the
	// information of a dataset.
	void cppdas_dataset::head(const size_t& _viewRowNumber = 5)
	{
		this->rbIterator(_viewRowNumber, false);
		return;
	}
	
	// Like Python pandas.tail(), cppdas_dataset::tail output the
	// information of a dataset.
	void cppdas_dataset::tail(const size_t& _viewRowNumber = 5)
	{
		this->rbIterator(_viewRowNumber, true);
		return;
	}
	
	void cppdas_dataset::rbIterator(const size_t& _viewRowNumber,
		const bool& _reverse)
	{
		if (this->title.size())
		{
			std::cout<<"\t"; // Tab for row-number column
			for (const auto& element: this->title)
			{
				std::cout<<element<<"\t";
			}
			std::cout<<std::endl;
		}
		for (size_t iteratorDistance=0;
			iteratorDistance<_viewRowNumber;
			iteratorDistance++)
		{
			if (_reverse)
			{
				if (this->data.rbegin()+iteratorDistance != this->data.rend())
				{
					std::cout<<iteratorDistance<<"\t";
					for (const auto& element:
						*(this->data.rbegin()+iteratorDistance))
					{
						std::cout<<element._data<<"\t";
					}
					std::cout<<std::endl;
				}
			}
			else
			{
				if (this->data.begin()+iteratorDistance != this->data.end())
				{
					std::cout<<iteratorDistance<<"\t";
					for (const auto& element:
						*(this->data.begin()+iteratorDistance))
					{
						std::cout<<element._data<<"\t";
					}
					std::cout<<std::endl;
				}
			}
		}
	}
	
	// Like Python pandas, cppdas is a class about C++ data analysis.
	// If you use:
	// 	using pd = dgtk::cppdas;
	// It looks like python pandas :)
	// e.g. auto iris = pd::read_csv("iris.data");
	class cppdas
	{
		public:
			static cppdas_dataset read_csv(const std::string&,
				const std::vector<std::string>&, const bool&);
			static cppdas_dataset read_csv(const std::string&,
				const bool&);
			static cppdas_dataset read_csv(std::fstream&,
				const std::vector<std::string>&, const bool&);
			static cppdas_dataset read_csv(std::fstream&,
				const bool&);
		private:
			static const std::vector<std::string> defaultSplitCharacter;
			static const std::string ignoredCharacter;
		private:
			static cppdas_dataset read_csv_base(std::fstream&,
				const std::vector<std::string>&, const bool&);
	};
	
	// The default character used in string split.
	const std::vector<std::string> cppdas::defaultSplitCharacter = {","};
	const std::string ignoredCharacter = "\r";
	
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
	
	// This is the foundamental function for cppdas::read_csv
	cppdas_dataset cppdas::read_csv_base(std::fstream& _fsHandle,
		const std::vector<std::string>& _split,
		const bool& _haveHeader)
	{
		cppdas_dataset res;
		{
			size_t rowNumber = 0;
			std::string line;
			// For every line in csv file.
			// According to rowNumber and _haveHeader, the first line
			// of csv file would be title or header.
			while (std::getline(_fsHandle, line))
			{
				std::string row;
				cppdas_dataset::DataRow data; // DataRow is std::vector
				// Remove \r from line
				for (const auto& letter: line)
				{
					if (dgtk::ignoredCharacter.find(letter) ==
						std::string::npos)
					{
						row += letter;
					}
				}
				// Split every element from line according spliter.
				while (true)
				{
					if (row.empty())
						break;
					bool findStatus = false;
					auto findLocation = std::string::npos;
					size_t splitSize = 0;
					for (const auto& _splitUnit: _split)
					{
						findLocation = row.find(_splitUnit);
						if (findLocation != std::string::npos)
						{
							findStatus = true;
							splitSize = _splitUnit.size();
							break;
						}
					}
					if (findStatus)
					{
						std::string&& _element_data =
							row.substr(0, findLocation);
						data.push_back(cppdas_data_element(_element_data));
						row = row.substr(findLocation+splitSize);
					}
					else
					{
						if (row.size())
							data.push_back(row);
						break;
					}
				}
				if (data.size())
				{
					if (rowNumber || !_haveHeader)
						res.data.push_back(data);
					else
						// It is the first line of file
						res.setTitle(data);
					// If we meet a blank line, ignore it and row number
					// doesn't increase.
					rowNumber++;
				}
			}
		}
		return res;
	}
	
	template <typename _ElemType>
	class MatrixBase
	{
		
	};
	
	template <typename _DataType = double, typename _CategoryType = int>
	class Perceptron
	{
		public:
			Perceptron();
			Perceptron(const pair<vector<_DataType>, _CategoryType>&);
			Perceptron(const vector<pair<vector<_DataType>, _CategoryType>>&);
			bool addPoint(const pair<vector<_DataType>, _CategoryType>&);
			bool addTrainingSet(
				const vector<pair<vector<_DataType>, _CategoryType>>&);
			size_t getDimension();
			size_t size();
			string getArg();
			_CategoryType getCategory(const vector<_DataType>&);
			void learning();
		private:
			size_t dimension;
			vector<pair<vector<_DataType>, _CategoryType>> trainingSet;
			_DataType argBias;
			vector<_DataType> argWeight;
			_DataType learningStep;
		private:
			void initializeArgWeight();
			_CategoryType functionSign(const _DataType&);
			bool checkPointCategoryRight();
			bool judgePoint(const pair<vector<_DataType>, _CategoryType>&);
			void updateArgViaLearning(
				const pair<vector<_DataType>, _CategoryType>&);
	};

	template <typename _DataType, typename _CategoryType>
	Perceptron<_DataType, _CategoryType>::Perceptron()
	{
		this->dimension = 0;
		this->argBias = (_DataType)0;
		this->learningStep = (_DataType)0.1;
		return;
	}

	template <typename _DataType, typename _CategoryType>
	Perceptron<_DataType, _CategoryType>::Perceptron(
		const pair<vector<_DataType>, _CategoryType>& _point)
	{
		this->Perceptron();
		this->addPoint(_point);
		return;
	}

	template <typename _DataType, typename _CategoryType>
	Perceptron<_DataType, _CategoryType>::Perceptron(
		const vector<pair<vector<_DataType>, _CategoryType>>& _set)
	{
		this->Perceptron();
		this->addTrainingSet(_set);
		return;
	}

	template <typename _DataType, typename _CategoryType>
	bool Perceptron<_DataType, _CategoryType>::addPoint(
		const pair<vector<_DataType>, _CategoryType>& _point)
	{
		if (this->dimension)
		{
			if (this->dimension != _point.first.size())
			{
				return false;
			}
		}
		else
		{
			if (_point.first.size() == 0)
			{
				return false;
			}
			this->dimension = _point.first.size();
			this->initializeArgWeight();
		}
		this->trainingSet.push_back(_point);
		return true;
	}

	template <typename _DataType, typename _CategoryType>
	bool Perceptron<_DataType, _CategoryType>::addTrainingSet(
		const vector<pair<vector<_DataType>, _CategoryType>>& _set)
	{
		if (!_set.first.size())
		{
			return false;
		}
		size_t trainingSetDimension = _set[0].first.size();
		if (trainingSetDimension == 0)
		{
			return false;
		}
		if (this->dimension && this->dimension != trainingSetDimension)
		{
			return false;
		}
		for (const auto& _element: _set.first)
		{
			if (_element.first.size() != trainingSetDimension)
			{
				return false;
			}
		}
		if (!this->dimension)
		{
			this->dimension = trainingSetDimension;
		}
		this->initializeArgWeight();
		for (const auto& _element: _set)
		{
			this->trainingSet.push_back(_element);
		}
		return true;
	}

	template <typename _DataType, typename _CategoryType>
	size_t Perceptron<_DataType, _CategoryType>::getDimension()
	{
		return this->dimension;
	}

	template <typename _DataType, typename _CategoryType>
	size_t Perceptron<_DataType, _CategoryType>::size()
	{
		return this->trainingSet.size();
	}

	template <typename _DataType, typename _CategoryType>
	string Perceptron<_DataType, _CategoryType>::getArg()
	{
		string res = "w: [";
		for (const auto& element: this->argWeight)
		{
			res = res + to_string(element) + ", ";
		}
		res = res.substr(0, res.size()-2) + "], b: " + to_string(this->argBias);
		return res;
	}

	template <typename _DataType, typename _CategoryType>
	_CategoryType Perceptron<_DataType, _CategoryType>::getCategory(
		const vector<_DataType>& _point)
	{
		_CategoryType resCategory = (_CategoryType)0;
		_DataType judge = (_DataType)0;
		if (_point.size() != this->dimension)
		{
			cerr<<"判断用点维度不符"<<endl;
			exit(-1);
		}
		for (size_t dimensionN=0; dimensionN!=this->dimension; dimensionN++)
		{
			judge += this->argWeight[dimensionN] * _point[dimensionN];
		}
		judge += this->argBias;
		resCategory = functionSign(judge);
		return resCategory;
	}

	template <typename _DataType, typename _CategoryType>
	void Perceptron<_DataType, _CategoryType>::learning()
	{
		for (size_t i=0; i!=5; i++)
		{
			for (const auto& p: this->trainingSet)
			{
				if (!judgePoint(p))
				{
					cout<<"对于点("<<p.first[0]<<","<<p.first[1]<<"): "<<judgePoint(p)<<endl;
					this->updateArgViaLearning(p);
				}
				cout<<getArg()<<endl;
			}
		}
		return;
	}

	template <typename _DataType, typename _CategoryType>
	void Perceptron<_DataType, _CategoryType>::initializeArgWeight()
	{
		for (size_t i=0; i!=this->dimension; i++)
		{
			this->argWeight.push_back((_DataType)1);
		}
		return;
	}

	template <typename _DataType, typename _CategoryType>
	_CategoryType Perceptron<_DataType, _CategoryType>::functionSign(
		const _DataType& _var)
	{
		if (_var > 0)
		{
			return (_CategoryType)1;
		}
		else
		{
			return (_CategoryType)-1;
		}
	}

	template <typename _DataType, typename _CategoryType>
	bool Perceptron<_DataType, _CategoryType>::judgePoint(
		const pair<vector<_DataType>, _CategoryType>& _point)
	{
		_CategoryType T = (-1) * _point.second * getCategory(_point.first);
		if (T > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	template <typename _DataType, typename _CategoryType>
	void Perceptron<_DataType, _CategoryType>::updateArgViaLearning(
		const pair<vector<_DataType>, _CategoryType>& _point)
	{
		for (size_t dimensionN=0; dimensionN!=this->dimension; dimensionN++)
		{
			this->argWeight[dimensionN] = this->argWeight[dimensionN] +
				this->learningStep * _point.second * _point.first[dimensionN];
		}
		this->argBias = this->argBias + this->learningStep * _point.second;
		return;
	}
} // End of namespace dgtk.