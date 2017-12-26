#include "PanelResources.hpp"

#include <QTableWidget>

namespace al
{

PanelResources::PanelResources(QWidget* parent):
	Panel(tr("Resources"), parent)
{
	QTableWidget* table = new QTableWidget;
	setWidget(table);

	{
		table->insertRow(0);
		QTableWidgetItem* item00 = new QTableWidgetItem("aaa");
		table->setItem(0, 0, item00);
		QTableWidgetItem* item01 = new QTableWidgetItem("01");
		table->setItem(0, 1, item01);

		table->insertRow(1);
		QTableWidgetItem* item10 = new QTableWidgetItem("bbb");
		table->setItem(1, 0, item10);
		QTableWidgetItem* item11 = new QTableWidgetItem("02");
		table->setItem(1, 1, item11);
	}
}

} // namespace al
