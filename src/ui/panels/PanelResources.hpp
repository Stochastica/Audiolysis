#ifndef AUDIOLYSIS_UI_PANELS_PANELRESOURCES_HPP__
#define AUDIOLYSIS_UI_PANELS_PANELRESOURCES_HPP__

#include "Panel.hpp"

namespace al
{

class PanelResources final: public Panel
{
	Q_OBJECT
public:
	PanelResources(QWidget* parent = nullptr);

};

} // namespace al

#endif // !AUDIOLYSIS_UI_PANELS_PANELRESOURCES_HPP__
