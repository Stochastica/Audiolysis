#include "scripting.hpp"

#include "audiolysis.hpp"

namespace al
{

/**
 * Python Exception translator
 */
void exceptionTranslator(Exception const& e)
{
#define EXCEPTION_TRANSLATE(cl, py) \
	if (auto temp = dynamic_cast<cl const*>(&e)) \
	{ \
		PyErr_SetString(PyExc_##py, e.what()); \
		return; \
	}

	EXCEPTION_TRANSLATE(ExceptionIndex, IndexError);
	EXCEPTION_TRANSLATE(ExceptionValue, ValueError);
	EXCEPTION_TRANSLATE(ExceptionRuntime, RuntimeError);
	EXCEPTION_TRANSLATE(ExceptionIO, IOError);
	EXCEPTION_TRANSLATE(Exception, Exception);

#undef EXCEPTION_TRANSLATE
}

bool initialised; ///< Flag to test for initialisation

BOOST_PYTHON_MODULE(al)
{
	using namespace boost::python;

	register_exception_translator<Exception>(exceptionTranslator);

	def("version", +[](){ return AUDIOLYSIS_VERSION; });

	initialised = true; // Set initialised flag = true
}

bool initScripting()
{
	initialised = false;

	PyImport_AppendInittab("al", PyInit_al);
	Py_Initialize();
	
	{
		using namespace boost::python;

		exec("import al", mainDict());
		exec("print(\"Audiolysis \" + al.version())", mainDict());
	}

	return initialised;
}

} // namespace al
