#include "MainWindow.hpp"

#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QSplitter>

#include <QLineEdit>

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

	// Loads menus
	{
		QMenu* menuHelp = menuBar()->addMenu(tr("Help"));
		{
			QAction* actionAbout = new QAction(tr("About"), this);
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
			statusBar()->addPermanentWidget(splitterCommand);
		}

		{
			QPushButton* buttonTerminal = new QPushButton;
			buttonTerminal->setIcon(QIcon(":/icons/terminal.png"));
			connect(buttonTerminal, &QPushButton::clicked,
			        this, [this]()
			{
				this->terminal->show();
			});
			statusBar()->addPermanentWidget(buttonTerminal);
		}
		//statusBar()->show();
	}
}

} // namespace al
