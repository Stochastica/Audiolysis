#include "Panel.hpp"

#include <QCloseEvent>

namespace al
{

Panel::Panel(QString const& title, QWidget* parent):
	QDockWidget(title, parent, Qt::Tool)
{
	setFocusPolicy(Qt::NoFocus);
	setAllowedAreas(Qt::AllDockWidgetAreas);
}
void Panel::closeEvent(QCloseEvent* event)
{
	hide();
	event->ignore();

	Q_EMIT visibilityChanged(false);
}
void Panel::showHide(bool flag)
{
	if (flag)
	{ // Show
		show();
	}
	else
	{ // Hide
		hide();
	}
}

} // namespace al
