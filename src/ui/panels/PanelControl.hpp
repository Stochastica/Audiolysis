#ifndef AUDIOLYSIS_UI_PANELS_PANELCONTROL_HPP__
#define AUDIOLYSIS_UI_PANELS_PANELCONTROL_HPP__

#include "Panel.hpp"

namespace al
{

class PanelControl final: public Panel
{
	Q_OBJECT
public:
	PanelControl(QWidget* parent = nullptr);

};

} // namespace al

#endif // !AUDIOLYSIS_UI_PANELS_PANELCONTROL_HPP__
