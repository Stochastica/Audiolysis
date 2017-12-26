#ifndef AUDIOLYSIS_UI_PANELS_PANEL_HPP__
#define AUDIOLYSIS_UI_PANELS_PANEL_HPP__

#include <QDockWidget>

namespace al
{

/**
 * Base class for all persistent (only one instance allowed) panels.
 */
class Panel: public QDockWidget
{
	Q_OBJECT
protected:
	Panel(QString const& title, QWidget* parent = nullptr);

	/**
	 * Override the closeEvent so this Panel hides when close button is pressed.
	 */
	virtual void closeEvent(QCloseEvent*) final override;

Q_SIGNALS:
	/**
	 * Emitted upon visibility change that is **NOT** caused by
	 * showHide().
	 */
	void visibilityChanged(bool);
public Q_SLOTS:
	/**
	 * If flag is true, show. Otherwise hides the panel
	 */
	void showHide(bool flag);
};

} // namespace al

#endif // !AUDIOLYSIS_UI_PANELS_PANEL_HPP__
