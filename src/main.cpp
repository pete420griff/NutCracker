#include "common.h"
#include "Actions.h"

#include <cstring>
#include <fstream>

void Usage( void )
{
	std::cout << "NutCracker Squirrel script decompiler, ver " << NUTCRACKER_VERSION << std::endl;
	std::cout << "for binary nut file version " << TOSTRING(SQ_VERSION_MAJOR) "." TOSTRING(SQ_VERSION_MINOR) ".x" << std::endl;
	std::cout << std::endl;
	std::cout << "  Usage:" << std::endl;
	std::cout << "    nutcracker [options] <file to decompile> [output file]" << std::endl;
	std::cout << "    nutcracker -cmp <file1> <file2>" << std::endl;
	std::cout << std::endl;
	std::cout << "  Options:" << std::endl;
	std::cout << "   -h        Display usage info" << std::endl;
	std::cout << "   -cmp      Compare two binary files" << std::endl;
	std::cout << "   -d <name> Display debug decompilation for function" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}


int stricmpWrapper(char* in, const char* cmp) {
	#ifdef __linux__
		return strncasecmp(in, cmp, sizeof(cmp));
	#elif _WIN32
		return _stricmp(in, cmp);
	#endif
}

int main( int argc, char* argv[] )
{
	const char* debugFunction = nullptr;

	for( int i = 1; i < argc; ++i)
	{
		if (0 == stricmpWrapper(argv[i], "-h"))
		{
			Usage();
			return 0;
		}
		else if (0 == stricmpWrapper(argv[i], "-d"))
		{
			if ((argc - i) < 2)
			{
				Usage();
				return -1;
			}
			debugFunction = argv[i + 1];
			i += 1;
		}
		else if (0 == stricmpWrapper(argv[i], "-cmp"))
		{
			if ((argc - i) < 3)
			{
				Usage();
				return -1;
			}
			return Compare(argv[i + 1], argv[i + 2], false);
		}
		else if (0 == stricmpWrapper(argv[i], "-cmpg"))
		{
			if ((argc - i) < 3)
			{
				Usage();
				return -1;
			}
			return Compare(argv[i + 1], argv[i + 2], true);
		}
		else
		{
			if (i < argc-1)
			{
				std::ofstream file(argv[i+1]);

				if (!file)
				{
					std::cerr << "Failed to open file\n";
					return -1;
				}

				return Decompile(argv[i], debugFunction, file);
			}
			else
			{
				return Decompile(argv[i], debugFunction, std::cout);
			}
		}
	}


	Usage();
	return -1;
}
