#ifndef AUDIOLYSIS_UI_MAINWINDOW_HPP__
#define AUDIOLYSIS_UI_MAINWINDOW_HPP__

#include <QMainWindow>

#include "terminal.hpp"
#include "../core/Configuration.hpp"

namespace al
{

class MainWindow final: public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(Configuration* const config);

private Q_SLOTS:

private:
	Configuration* const config;

	// Persistent widgets
	Terminal* terminal;
};

} // namespace al

#endif // !AUDIOLYSIS_UI_MAINWINDOW_HPP__
