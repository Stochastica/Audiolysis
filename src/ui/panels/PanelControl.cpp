#include "PanelControl.hpp"

#include <QGridLayout>
#include <QPushButton>

namespace al
{

PanelControl::PanelControl(QWidget* parent):
	Panel(tr("Control"), parent)
{
	QWidget* centralWidget = new QWidget;
	setWidget(centralWidget);

	QGridLayout* layout = new QGridLayout;
	centralWidget->setLayout(layout);

	layout->addWidget(new QPushButton, 0, 0);
	layout->addWidget(new QPushButton, 1, 0);
	layout->addWidget(new QPushButton, 1, 1);
	layout->addWidget(new QPushButton, 0, 1);
}


} // namespace al
