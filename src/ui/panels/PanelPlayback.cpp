#include "PanelPlayback.hpp"

#include <QHBoxLayout>
#include <QPushButton>

namespace al
{

PanelPlayback::PanelPlayback(QWidget* parent):
	Panel(tr("Playback"), parent)
{
	QWidget* centralWidget = new QWidget;
	setWidget(centralWidget);

	QHBoxLayout* layout = new QHBoxLayout;
	centralWidget->setLayout(layout);

	QPushButton* buttonPlay = new QPushButton;
	buttonPlay->setIcon(QIcon(":/icons/play.png"));
	connect(buttonPlay, &QPushButton::clicked,
	        this, [this]()
	{
		Q_EMIT this->play();
	});
	layout->addWidget(buttonPlay);

	QPushButton* buttonPause = new QPushButton;
	buttonPause->setIcon(QIcon(":/icons/pause.png"));
	connect(buttonPause, &QPushButton::clicked,
	        this, [this]()
	{
		Q_EMIT this->pause();
	});
	layout->addWidget(buttonPause);

	QPushButton* buttonStop = new QPushButton;
	buttonStop->setIcon(QIcon(":/icons/stop.png"));
	connect(buttonPause, &QPushButton::clicked,
	        this, [this]()
	{
		Q_EMIT this->stop();
	});
	layout->addWidget(buttonStop);
}

} // namespace al
