#ifndef CHANNELS_TYPE_H_
#define CHANNELS_TYPE_H_
#include <string>
namespace kdl
{

struct Variable
{
	enum Type
	{
		STRING,
		REGEX,
		BYTE_SEQUENCE
	};
	std::string searchstr;
	Type type;

};

}

#endif // CHANNELS_TYPE_H_