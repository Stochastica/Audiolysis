#include "test.hpp"

#include "testing.hpp"
#include "scripting/testScripting.hpp"

namespace al
{

std::map<std::string, std::string> testInfo()
{
	std::map<std::string, std::string> info;

	info["0"] = "Dummy test object";
	info["s1"] = "Scripting Interface";
	info["s2"] = "Stdout, Stderr redirector";

	return info;
}

bool test_0()
{
	std::cout << "Test 0\n";
	return true;
}

bool test(std::string id)
{
	if (id.at(0) == 's')
		return testScripting(id);

	TEST_FUNC(0);

	TEST_FINAL;
}

} // namespace al
