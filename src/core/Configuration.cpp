#include "Configuration.hpp"

#include <iostream>

#include <QFontDatabase>
#include <QFontMetrics>

namespace al
{

Configuration::Configuration():
	ui_monospace("Liberation Mono"), // QFontDatabase::systemFont(QFontDatabase::FixedFont)),
	ui_LineTerminal_cof(0,0,0),
	ui_LineTerminal_cob(200,200,200),
	ui_LineTerminal_cef(0,0,0),
	ui_LineTerminal_ceb(200,80,80),
	ui_terminal_cb(60, 60, 60),
	ui_terminal_cfOut(200, 200, 200),
	ui_terminal_cfErr(175, 0, 0),
	ui_python_cb(30, 30, 30),
	ui_python_cf(200, 200, 200),
	ui_python_chKey(86, 156, 217)
{
	ui_monospace.setStyleHint(QFont::Monospace);
	ui_monospace.setFixedPitch(true);

	ui_monospace_tabwidth = 4 * QFontMetrics(ui_monospace).width('\t');
#ifndef NDEBUG
	std::cout << "Monospace Font: "
	          << ui_monospace.family().toStdString()
	          << std::endl;;
#endif

}

} // namespace al
