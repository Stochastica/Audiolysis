#include <iostream>

#include <boost/program_options.hpp>
#include <QApplication>

#include "core/audiolysis.hpp"
#include "core/Configuration.hpp"
#include "core/scripting.hpp"
#include "ui/MainWindow.hpp"

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

	// Normal execution
	
	Configuration config;
	initScripting();

	QApplication application(argc, argv);
	MainWindow window(&config);
	{ // Configure Application name and logo
		QIcon logo(":logo.png");
		application.setApplicationName(AUDIOLYSIS_NAME);
		application.setWindowIcon(logo);
		window.setWindowIcon(logo);
	}

	window.show();

	boost::python::exec("print(\"Audiolysis \" + al.version())", mainDict());

	return application.exec();
}
