#include "DialogAbout.hpp"

#include <QIcon>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

#include "../core/audiolysis.hpp"

namespace al
{

DialogAbout::DialogAbout(QWidget* parent): QDialog(parent)
{
	QHBoxLayout* layout = new QHBoxLayout;

	QLabel* labelLogo = new QLabel;
	QPixmap logo(":/logo.png");
	labelLogo->setPixmap(logo);
	layout->addWidget(labelLogo);

	QLabel* labelText = new QLabel;
	labelText->setText(
			AUDIOLYSIS_NAME " " AUDIOLYSIS_VERSION "\n"
			"Created 2017, by HSV (Stochastica)."
			);

	layout->QLayout::addWidget(labelText);
	

	setLayout(layout);
	setFixedWidth(2 * logo.width());
	setFixedHeight(logo.height());
	setWindowTitle(tr("About"));
}

} // namespace al
