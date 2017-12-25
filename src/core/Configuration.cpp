#include "Configuration.hpp"

#include <iostream>

#include <QFontDatabase>

namespace al
{

Configuration::Configuration():
	ui_monospace("Liberation Mono"), // QFontDatabase::systemFont(QFontDatabase::FixedFont)),
	ui_LineEditCommand_cf(255,255,255),
	ui_LineEditCommand_cb(0,0,0),
	ui_LineTerminal_cof(0,0,0),
	ui_LineTerminal_cob(200,200,200),
	ui_LineTerminal_cef(0,0,0),
	ui_LineTerminal_ceb(200,80,80)
{
	ui_monospace.setStyleHint(QFont::Monospace);
#ifndef NDEBUG
	std::cout << "Monospace Font: "
	          << ui_monospace.family().toStdString()
	          << std::endl;;
#endif

}

} // namespace al
