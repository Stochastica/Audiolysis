#include <iostream>

#include <boost/program_options.hpp>

#include "core/audiolysis.hpp"

#ifndef NDEBUG
	#include "test/test.hpp"
#endif

int main(int argc, char* argv[])
{
	using namespace al;

	// Parse command line options

	boost::program_options::variables_map options;
	{
		namespace bpo = boost::program_options;

#ifndef NDEBUG
		std::string testDesc = "Execute test [arg]\n";
		for (auto const& i: testInfo())
			testDesc += i.first + ": " + i.second + '\n';
#endif

		bpo::options_description desc("Options");
		desc.add_options()
		("help,h", "Show help")
#ifndef NDEBUG
		("test,t", bpo::value<std::string>(), testDesc.c_str())
#endif
		;
		bpo::store(bpo::parse_command_line(argc, argv, desc), options);

		if (options.count("help")) // Prints help message
		{
			std::cout << AUDIOLYSIS_NAME << ' '
			          << AUDIOLYSIS_VERSION
			          << std::endl
			          << desc
			          << std::endl;
			return 0;
		}
	}

	if (options.count("test"))
	{
		std::string testId = options["test"].as<std::string>();
		bool result = test(testId);

		std::cout << (result ? "Test successful\n" : "Test failed\n");

		return 0;
	}

	std::cout << "Hello, World!\n";

	return 0;
}
