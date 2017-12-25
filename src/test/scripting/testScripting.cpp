#include "testScripting.hpp"

#include <cassert>
#include <Python.h>
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

bool testScripting(std::string id)
{
	bool flag = initScripting();
	if (!flag)
	{
		std::cerr << "Scripting Initialisation failed\n";
		return false;
	}

	TEST_FUNC(s1);

	TEST_FINAL;
}

} // namespace al
