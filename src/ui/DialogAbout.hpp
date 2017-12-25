#ifndef AUDIOLYSIS_UI_DIALOGABOUT_HPP__
#define AUDIOLYSIS_UI_DIALOGABOUT_HPP__

#include <QDialog>

namespace al
{

class DialogAbout final: public QDialog
{
	Q_OBJECT
public:
	DialogAbout(QWidget* parent = nullptr);
};

} // namespace al

#endif // !AUDIOLYSIS_UI_DIALOGABOUT_HPP__
