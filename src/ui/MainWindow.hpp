#ifndef AUDIOLYSIS_UI_MAINWINDOW_HPP__
#define AUDIOLYSIS_UI_MAINWINDOW_HPP__

#include <QMainWindow>

#include "panels/PanelControl.hpp"
#include "panels/PanelPlayback.hpp"
#include "panels/PanelResources.hpp"

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
	void resetLayout();

private:
	Configuration* const config;

	// Persistent widgets
	Terminal* terminal;

	PanelControl* pControl;
	PanelPlayback* pPlayback;
	PanelResources* pResources;
};

} // namespace al

#endif // !AUDIOLYSIS_UI_MAINWINDOW_HPP__
