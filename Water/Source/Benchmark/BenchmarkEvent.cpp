#include "BenchmarkEvent.h"
#include <sstream>

benchmark::Event::Event(std::initializer_list<std::pair<std::string, std::string>> attributesAndValues)
{
	// Make a stringstream to enable the use of ostream iterators
	std::stringstream stringstream;
	std::transform(attributesAndValues.begin(), attributesAndValues.end(),
		std::ostream_iterator<std::string>(stringstream, ","), [](const auto& p)
		{
			const auto&[attribute, value] = p;
			return "\"" + attribute + "\": " + value;
		});
	
	mData = stringstream.str();

	// Remove the last delimiter ","
	mData.resize(mData.size() - 1);
	mData = "{" + mData + "}";
}

const std::string& benchmark::Event::GetData() const
{
	return mData;
}