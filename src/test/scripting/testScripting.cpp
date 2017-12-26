#include "testScripting.hpp"

#include <cassert>
#include <iosfwd>

#include "../testing.hpp"
#include "../../core/scripting.hpp"
#include "../../core/audiolysis.hpp"
#include "../../ui/terminal.hpp"

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
	try
	{
		using namespace boost::python;

		mainDict()["al_OutputRedirector"] =
		  boost::python::class_<OutputRedirector>("OutputRedirector",
		      boost::python::no_init)
		  .def("write", &OutputRedirector::write);

		boost::python::import("sys").attr("stdout") =
		  OutputRedirector("[Out] ",
		                   [](std::string str)
		{
			// Actual raw input are processed here...
		});

		sprintl("Arma Virumque Cano");
		sprintl("Troiae ab primis oris");
	}
	catch (boost::python::error_already_set&)
	{
		std::cerr << traceback();
		PyErr_Clear();
		return false;
	}

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
