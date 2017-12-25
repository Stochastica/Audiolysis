#ifndef AUDIOLYSIS_CORE_SCRIPTING_HPP__
#define AUDIOLYSIS_CORE_SCRIPTING_HPP__

#include <string>
#include <stdexcept>

#include <Python.h>
#include <boost/python.hpp>

namespace al
{

/**
 * Loads Python. Must be called before executing python commands.
 *
 * Throwing Exceptions:
 *  1. {@class Exception}        -> Exception
 *  2. {@class ExceptionIndex}     -> IndexError
 *  3. {@class ExceptionValue} -> ValueError
 *  4. {@class ExceptionRuntime}    -> RuntimeError
 *  5. {@class ExceptionIO}         -> IOError
 */
bool initScripting();

using Exception = std::exception;
using ExceptionIndex = std::out_of_range;
using ExceptionValue = std::invalid_argument;
using ExceptionRuntime = std::runtime_error;

class ExceptionIO : public std::logic_error
{
public:
	explicit ExceptionIO(std::string const& w): logic_error(w) {}
};

/**
 * @brief Produces a traceback string of the python exception
 */
std::string traceback() noexcept;

/**
 * @brief Extracts the main dict.
 * @warning Do not call this before initialising python.
 */
boost::python::dict& mainDict();


// Implementations
inline std::string traceback() noexcept
{
	using namespace boost::python;

	PyObject* exType;
	PyObject* value;
	PyObject* traceBack;
	PyErr_Fetch(&exType, &value, &traceBack);

	// This can happen if the user entered print(
	if (exType == nullptr ||
	    value == nullptr ||
	    traceBack == nullptr)
	{
		return "Command Incomplete\n";
	}
	// Needed to prevent exception from being thrown.
	PyErr_NormalizeException(&exType, &value, &traceBack);
	// This is the Python3 way to do it;
	object oExType(handle<>(borrowed(exType)));
	object oValue(handle<>(borrowed(value)));
	object oTraceBack(handle<>(borrowed(traceBack)));
	object lines = import("traceback").attr("format_exception")
	               (oExType, oValue, oTraceBack);
	std::string result;
	for (int i = 0; i < len(lines); ++i)
		result += extract<std::string>(lines[i])();

	PyErr_Restore(exType, value, traceBack);
	return result;
}
inline boost::python::dict& mainDict()
{
	using namespace boost::python;
	static object module = import("__main__");
	static dict d = extract<dict>(module.attr("__dict__"));

	return d;
}

} // namespace al

#endif // !AUDIOLYSIS_CORE_SCRIPTING_HPP__
