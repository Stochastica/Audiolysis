#ifndef AUDIOLYSIS_CORE_CONFIGURATION_HPP__
#define AUDIOLYSIS_CORE_CONFIGURATION_HPP__

#include <QColor>
#include <QFont>

namespace al
{

/**
 * @brief Core Configuration object
 */
class Configuration final
{
public:
	Configuration();

	QFont ui_monospace;
	int ui_monospace_tabwidth; ///< Tabwidth in Qt units.

	QColor ui_LineTerminal_cof;
	QColor ui_LineTerminal_cob;
	QColor ui_LineTerminal_cef;
	QColor ui_LineTerminal_ceb;
	QColor ui_terminal_cb;
	QColor ui_terminal_cfOut;
	QColor ui_terminal_cfErr;
	QColor ui_python_cb;
	QColor ui_python_cf;
	QColor ui_python_chKey; ///< Keyword Syntax Highlighting colour
};

} // namespace al

#endif // !AUDIOLYSIS_CORE_CONFIGURATION_HPP__
