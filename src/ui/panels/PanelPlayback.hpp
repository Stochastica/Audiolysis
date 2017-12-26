#ifndef AUDIOLYSIS_UI_PANELS_PANELPLAYBACK_HPP__
#define AUDIOLYSIS_UI_PANELS_PANELPLAYBACK_HPP__

#include "Panel.hpp"

namespace al
{

class PanelPlayback final: public Panel
{
	Q_OBJECT
public:
	PanelPlayback(QWidget* parent = nullptr);

Q_SIGNALS:
	void play();
	void stop();
	void pause();
};

} // namespace al

#endif // !AUDIOLYSIS_UI_PANELS_PANELPLAYBACK_HPP__
