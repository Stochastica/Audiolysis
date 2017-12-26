#include "MainWindow.hpp"

#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QSplitter>

#include <QDockWidget>

#include "DialogAbout.hpp"
#include "terminal.hpp"

#include "../core/audiolysis.hpp"

namespace al
{

MainWindow::MainWindow(Configuration* const config):
	QMainWindow(nullptr),
	config(config)
{
	setWindowTitle(AUDIOLYSIS_NAME);

	// Panels and Windows menu
	{
		QMenu* menuWindows = menuBar()->addMenu(tr("Windows"));

		QAction* aResetLayout = new QAction(tr("Reset Layout"));
		menuWindows->addAction(aResetLayout);
		connect(aResetLayout, &QAction::triggered,
		        this, &MainWindow::resetLayout);
		menuWindows->addSeparator();

		// Loads the panels and corresponding menu actions

		pControl = new PanelControl;
		QAction* apControl = new QAction(tr("Control"));
		menuWindows->addAction(apControl);
		apControl->setCheckable(true);
		connect(pControl, &PanelControl::visibilityChanged,
		        apControl, &QAction::setChecked);
		connect(apControl, &QAction::toggled,
		        pControl, &PanelControl::setVisible);

		pPlayback = new PanelPlayback;
		QAction* apPlayback = new QAction(tr("Playback"));
		menuWindows->addAction(apPlayback);
		apPlayback->setCheckable(true);
		connect(pPlayback, &PanelPlayback::visibilityChanged,
		        apPlayback, &QAction::setChecked);
		connect(apPlayback, &QAction::toggled,
		        pPlayback, &PanelPlayback::setVisible);

		pResources = new PanelResources;
		QAction* apResources = new QAction(tr("Resources"));
		menuWindows->addAction(apResources);
		apResources->setCheckable(true);
		connect(pResources, &PanelResources::visibilityChanged,
		        apResources, &QAction::setChecked);
		connect(apResources, &QAction::toggled,
		        pResources, &PanelResources::setVisible);
	}

	// Loads menus
	{
		QMenu* menuHelp = menuBar()->addMenu(tr("Help"));
		{
			QAction* actionAbout = new QAction(tr("About"));
			connect(actionAbout, &QAction::triggered,
			        this, [this](bool)
			{
				(new DialogAbout(this))->exec();
			});
			menuHelp->addAction(actionAbout);
		}
	}

	// Load status bar
	{
		// Make the line edits fill the status bar
		QSizePolicy sizePolicyFill;
		sizePolicyFill.setHorizontalPolicy(QSizePolicy::Expanding);
		sizePolicyFill.setHorizontalStretch(1);

		{
			QSplitter* splitterCommand = new QSplitter;
			statusBar()->addPermanentWidget(splitterCommand);

			{
				LineEditCommand* lec;
				LineTerminal* lt;

				createTerminalWidgets(&lec, &lt, &terminal, this, *config);

				lec->setSizePolicy(sizePolicyFill);
				splitterCommand->addWidget(lec);
				lt->setSizePolicy(sizePolicyFill);
				splitterCommand->addWidget(lt);
			}

			splitterCommand->setSizePolicy(sizePolicyFill);
		}

		{
			QPushButton* buttonTerminal = new QPushButton;
			statusBar()->addPermanentWidget(buttonTerminal);
			buttonTerminal->setIcon(QIcon(":/icons/terminal.png"));
			connect(buttonTerminal, &QPushButton::clicked,
			        this, [this]()
			{
				this->terminal->show();
			});
		}
		//statusBar()->show();
	}

	// Initialise to default
	resetLayout();
}

void MainWindow::resetLayout()
{
	pControl->setVisible(true);
	Q_EMIT pControl->visibilityChanged(true);
	addDockWidget(Qt::LeftDockWidgetArea, pControl);

	pPlayback->setVisible(true);
	Q_EMIT pPlayback->visibilityChanged(true);
	tabifyDockWidget(pControl, pPlayback);

	pResources->setVisible(true);
	Q_EMIT pResources->visibilityChanged(true);
	addDockWidget(Qt::RightDockWidgetArea, pResources);
}

} // namespace al
