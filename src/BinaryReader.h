#pragma once

#include <algorithm>
#include <type_traits>

#include "common.h"
#include "Errors.h"


class BinaryReader {
public:
	explicit BinaryReader(std::istream& in) : _in(in) {}

	template<typename T>
	T Read()
	{
		T value;

		_in.read(reinterpret_cast<char*>(&value), sizeof(T));

		if (_in.fail())
			throw Error("I/O Error while reading from file.");

		return value;
	}

	WordT ReadWord()
	{
		return Read<WordT>();
	}

	UWordT ReadUWord()
	{
		return Read<UWordT>();
	}

	void Read(void* buffer, UWordT size)
	{
		if (size < 1)
			return;

		_in.read(reinterpret_cast<char*>(buffer), size);

		if (_in.fail())
			throw Error("I/O Error while reading from file.");
	}

	std::streampos position()
	{
		return _in.tellg();
	}

	void ConfirmOnPart()
	{
		if (ReadWord() != 'PART') {
			std::cout << "Uh oh! Part NOT confirmed!" << std::endl;
			throw Error("Bad format of source binary file (PART marker was not match).");
		}
	}

	void ReadSQString(std::string& str)
	{
		auto len = ReadUWord();
		str.clear();
		str.reserve((size_t) len);

		while(len > 0)
		{
			char buffer[128];
			auto chunk = std::min(static_cast<UWordT>(128), len);

			Read(buffer, chunk);

			str.append(buffer, static_cast<size_t>(chunk));
			len -= chunk;
		}
	}


	void ReadSQStringObject(std::string& str)
	{
		constexpr int StringObjectType = 0x10 | 0x08000000;
		constexpr int NullObjectType = 0x01 | 0x01000000;

		int type = ReadWord();

		if (type == StringObjectType)
			ReadSQString(str);
		else if (type == NullObjectType)
			str.clear();
		else
			throw Error("Expected string object not found in source binary file.");
	}

private:
	std::istream& _in;

	// Delete default methods
	BinaryReader();
	BinaryReader(const BinaryReader&);
	BinaryReader& operator = (const BinaryReader&);
};
