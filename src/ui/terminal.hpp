#ifndef AUDIOLYSIS_UI_TERMINAL_HPP__
#define AUDIOLYSIS_UI_TERMINAL_HPP__

#include <iostream>
#include <sstream>

#include <QLineEdit>
#include <QMainWindow>
#include <QTextEdit>
#include <QPlainTextEdit>

#include "../core/Configuration.hpp"

namespace al
{

/*
 * This .hpp file provides the following widgets
 * 1. {@code LineEditCommand}: A LineEdit for inputting commands
 * 2. {@code LineTerminal}: A LineEdit (Read-only) for output
 * 3. {@code Terminal}: The main Terminal.
 *
 * Instances for the above classes should be created via the function
 * {@code createTerminalWidgets}. This should be executed only once.
 */


/**
 * @brief Redirects python output and prints it to cout or cerr.
 */
class OutputRedirector final
{
public:
	/**
	 * @param[in] prefix Prefix for every line of output.
	 *  E.g.
	 *   aaa     [Out] aaa
	 *   bbb  -> [Out] bbb
	 *   ccc     [Out] ccc
	 * @param[in] out Output function.
	 */
	OutputRedirector(std::string prefix,
	                 std::function<void (std::string)> out):
		prefix(prefix), out(out), newline(true)
	{
	}

	void write(std::string const& str)
	{
		if (str == "") return;

		out(str);

		std::string result;
		std::stringstream ss(str);
		std::string item;
		std::getline(ss, item, '\n');
		if (newline)
			result += prefix;
		result += item;
		while (std::getline(ss, item, '\n'))
			result += '\n' + prefix + item;

		newline = str.back() == '\n';
		if (newline) result += '\n';

		std::cout << result;
	}
private:
	std::string prefix;
	std::function<void (std::string)> out;

	bool newline; ///< If false, continue from last line.
};

/**
 * QLineEdit that emits a signal upon Shift-Enter
 */
class LineEditCommand final: public QLineEdit
{
	Q_OBJECT
public:
	explicit LineEditCommand(QWidget* parent = nullptr);

	/**
	 * Set foreground and background colors.
	 */
	void setColors(QColor const& front, QColor const& back);
Q_SIGNALS:
	void execute(std::string);

protected:
	virtual void keyPressEvent(QKeyEvent*) override;
};

class LineTerminal final: public QLineEdit
{
	Q_OBJECT
public:
	explicit LineTerminal(QWidget* parent = nullptr);

	void setColors(QColor const& cOF,
	               QColor const& cOB,
	               QColor const& cEF,
	               QColor const& cEB);

	void clearText();
	void setLineOut(std::string); // Set contents with output style
	void setLineErr(std::string); // Set contents with error style
private:
	QPalette paletteOut;
	QPalette paletteErr;
	std::string bufferOut;
	std::string bufferErr;
};

class TerminalFieldOut final: public QTextEdit
{
	Q_OBJECT
public:
	explicit TerminalFieldOut(QWidget* parent = nullptr);

	void onStdOutFlush(std::string);
	void onStdErrFlush(std::string);
};
class TerminalFieldIn final: public QPlainTextEdit
{
	Q_OBJECT
public:
	explicit TerminalFieldIn(QWidget* parent = nullptr);
Q_SIGNALS:
	void execute(std::string);
protected:
	virtual void keyPressEvent(QKeyEvent*) override;
public Q_SLOTS:
	void onPreserveInputToggled(bool);
private:
	bool preserveInput;
};

// Inheriting from QMainWindow to have a menubar.
class Terminal final: public QMainWindow
{
	Q_OBJECT
public:
	explicit Terminal(QWidget* parent = nullptr);

private:

	TerminalFieldOut* fieldOut;
	TerminalFieldIn* fieldIn;

	friend void createTerminalWidgets(LineEditCommand** const lec,
	                                  LineTerminal** const lt,
	                                  Terminal** const t,
	                                  QWidget* const parent,
	                                  Configuration const& config);
};

/**
 * @brief Initialises the terminal widgets
 * @warning Only intended to be initialised once.
 * @param[out] lec
 * @param[out] lt
 * @param[in] parent
 * @param[in] config
 */
void createTerminalWidgets(LineEditCommand** const lec,
                           LineTerminal** const lt,
                           Terminal** const t,
                           QWidget* const parent,
                           Configuration const& config);

} // namespace al

#endif // !AUDIOLYSIS_UI_TERMINAL_HPP__
