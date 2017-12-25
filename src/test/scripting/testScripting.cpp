#include "testScripting.hpp"

#include <cassert>
#include <iosfwd>

#include <Python.h>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/python.hpp>

#include "../testing.hpp"
#include "../../core/scripting.hpp"
#include "../../core/audiolysis.hpp"

namespace al
{

bool test_s1()
{
	char const* ver; // Extract version from script

	// This is the standard way of executing a python script.
	try
	{
		using namespace boost::python;
		object result = eval("al.version()", mainDict());

		ver = extract<char const*>(result);
	}
	catch (boost::python::error_already_set&)
	{
		std::cerr << traceback();
		PyErr_Clear();
		return false;
	}

	// Compare version obtained and actual version.
	if (strcmp(ver, AUDIOLYSIS_VERSION) == 0)
	{
		std::cout << "Version from script matches Audiolysis version\n";
		return true;
	}
	else
	{
		std::cout << "Version " << ver << " does not match Audiolysis version\n";
		return false;
	}
}
bool test_s2()
{
	namespace bio = boost::iostreams;

	// Custom stream sink
	class testSink final
	{
	public:
		typedef char char_type;
		typedef bio::sink_tag category;

		testSink(int) {}

		std::streamsize write(char_type const* s, std::streamsize n)
		{
			for (std::streamsize i = 0; i < n; ++i)
			{
				if (s[i] == '\n')
				{
					std::cout << "[Linea] " << buf << std::endl;;
					buf.clear();
				}
				else
				{
					buf += s[i];
				}
			}
			return n;
		}

	private:
		std::string buf;
	};

	int dummy;
	bio::stream<testSink> out(dummy);

	// Output some random text
	out << "Arma";
	out << " Virumque";
	out << " Cano" << std::endl;
	out << "Troiae ab primis oris\n";

	return true;
}

bool testScripting(std::string id)
{
	bool flag = initScripting();
	if (!flag)
	{
		std::cerr << "Scripting Initialisation failed\n";
		return false;
	}

	TEST_FUNC(s1);
	TEST_FUNC(s2);

	TEST_FINAL;
}

} // namespace al
