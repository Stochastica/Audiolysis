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
	QColor ui_LineEditCommand_cf;
	QColor ui_LineEditCommand_cb;
	QColor ui_LineTerminal_cof;
	QColor ui_LineTerminal_cob;
	QColor ui_LineTerminal_cef;
	QColor ui_LineTerminal_ceb;
};

} // namespace al

#endif // !AUDIOLYSIS_CORE_CONFIGURATION_HPP__
