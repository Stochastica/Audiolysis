// Entry point of the application
#include <iostream>

#include <boost/program_options.hpp>
#include <QApplication>
#include <QSplashScreen>

#include "core/Configuration.hpp"
#include "core/audiolysis.hpp"
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

		if (result)
			std::cout << "----- Test successful -----\n";
		else
			std::cout << "----- Test failed -----\n";

		return 0;
	}

	// Normal execution
	
	QApplication application(argc, argv);

	QSplashScreen splash(QPixmap(":logo.png"));
	splash.show();

#define SPLASH_STAGE(text) \
	QApplication::processEvents(); \
	splash.showMessage(application.tr(text), \
	                   Qt::AlignBottom | Qt::AlignHCenter, \
	                   Qt::white)

	SPLASH_STAGE("Loading Configurations");
	Configuration config;

	SPLASH_STAGE("Loading Scripting Interface");
	initScripting();

	SPLASH_STAGE("Initialising Main Window");
	MainWindow window(&config);
	{ // Configure Application name and logo
		QIcon logo(":logo.png");
		application.setApplicationName(AUDIOLYSIS_NAME);
		window.setWindowTitle(AUDIOLYSIS_NAME);

		application.setWindowIcon(logo);
		window.setWindowIcon(logo);
	}

	SPLASH_STAGE("Welcome!");
	window.show();
	splash.finish(&window);

	boost::python::exec("print(\"Audiolysis \" + al.version())", mainDict());

	return application.exec();
}
