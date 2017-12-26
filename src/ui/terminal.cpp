#include "terminal.hpp"

#include <iosfwd>

#include <QKeyEvent>
#include <QSplitter>
#include <QVBoxLayout>
#include <QMenuBar>

#include "../core/scripting.hpp"

namespace al
{

LineEditCommand::LineEditCommand(QWidget* parent): QLineEdit(parent)
{
}
void LineEditCommand::setColors(QColor const& front,
                                QColor const& back)
{
	QPalette palette;
	palette.setColor(QPalette::Text, front);
	palette.setColor(QPalette::Base, back);
	setPalette(palette);
}
void LineEditCommand::keyPressEvent(QKeyEvent* event)
{
	if ((event->key() == Qt::Key_Enter ||
	     event->key() == Qt::Key_Return) &&
	    event->modifiers() == Qt::ShiftModifier)
	{
		Q_EMIT execute(text().toStdString());
		this->clear();
	}
	else
	{
		// Forward the key to {@code QLineEdit}
		QLineEdit::keyPressEvent(event);
	}
}




LineTerminal::LineTerminal(QWidget* parent):
	QLineEdit(parent)
{
	setReadOnly(true); // Edit not allowed
}

void LineTerminal::setColors(QColor const& cOF,
                             QColor const& cOB,
                             QColor const& cEF,
                             QColor const& cEB)
{
	paletteOut.setColor(QPalette::Base, cOB);
	paletteOut.setColor(QPalette::Text, cOF);

	paletteErr.setColor(QPalette::Base, cEB);
	paletteErr.setColor(QPalette::Text, cEF);
}
void LineTerminal::clearText()
{
	setPalette(paletteOut);
	clear();
}

/**
 * @brief Process the buffer for LineTerminal
 */
std::string processLTBuffer(std::string* const out,
		std::string buffer,
		std::string in)
{
	// Find last newline character
	int n = in.size();
	int index = n - 1;
	while (index >= 0 && in[index] != '\n') --index;

	if (index == -1) // No newline found. Output nothing.
	{
		return buffer + in;
	}
	else if (index == 0)
	{
		// Newline found at beginning

		*out = buffer;

		// Set buffer to rest of input.
		return in.substr(1);
	}
	else
	{
		// Newline found in middle

		// Find second last newline
		std::streamsize index2 = index - 1;
		while (index2 >= 0 && in[index2] != '\n') --index2;

		if (index2 == -1)
		{ // Only one newline exists
			*out = buffer + in.substr(0, index);

			return in.substr(index + 1);
		}
		else
		{ // Found a second newline
			*out = in.substr(index2 + 1, index);

			return in.substr(index + 1);
		}
	}
}

void LineTerminal::setLineOut(std::string in)
{
	std::string output;
	bufferOut = processLTBuffer(&output, bufferOut, in);
	setPalette(paletteOut);
	setText(QString::fromStdString(output));
}
void LineTerminal::setLineErr(std::string in)
{
	std::string output;
	bufferOut = processLTBuffer(&output, bufferErr, in);
	setPalette(paletteErr);
	setText(QString::fromStdString(output));
}



TerminalFieldOut::TerminalFieldOut(QWidget* parent): QTextEdit(parent)
{
	setReadOnly(true);
}
void TerminalFieldOut::onStdOutFlush(std::string str)
{
	moveCursor(QTextCursor::End);
	insertHtml("<span style=\"color:#000000;\">" +
			QString::fromStdString(str).replace('\n', "<br>") +
			"</span>");
	moveCursor(QTextCursor::End);
}
void TerminalFieldOut::onStdErrFlush(std::string str)
{
	moveCursor(QTextCursor::End);
	insertHtml("<span style=\"color:#FF0000;\">" +
			QString::fromStdString(str).replace('\n', "<br>") +
			"</span>");
	moveCursor(QTextCursor::End);
}
TerminalFieldIn::TerminalFieldIn(QWidget* parent): QPlainTextEdit(parent)
{
}
void TerminalFieldIn::keyPressEvent(QKeyEvent* event)
{
	if ((event->key() == Qt::Key_Enter ||
	     event->key() == Qt::Key_Return) &&
	    event->modifiers() == Qt::ShiftModifier)
	{
		Q_EMIT execute(document()->toPlainText().toStdString());

		if (!preserveInput)
			clear();
	}
	else
	{
		// Forward the key to {@code QLineEdit}
		QPlainTextEdit::keyPressEvent(event);
	}
}
void TerminalFieldIn::onPreserveInputToggled(bool flag)
{
	preserveInput = flag;
}

Terminal::Terminal(QWidget* parent):
	QMainWindow(parent),
	fieldOut(new TerminalFieldOut), fieldIn(new TerminalFieldIn)
{
	setWindowTitle(tr("Terminal"));
	{ // Loads menus
		QMenu* menuFile = menuBar()->addMenu(tr("File"));

		QAction* aLoadScript = new QAction(tr("Load Script..."));
		menuFile->addAction(aLoadScript);
		

		QMenu* menuEdit = menuBar()->addMenu(tr("Edit"));

		QAction* aPreserveInput = new QAction(tr("Preserve Input"));
		aPreserveInput->setCheckable(true);
		aPreserveInput->setChecked(true);
		connect(aPreserveInput, &QAction::toggled,
		        fieldIn, &TerminalFieldIn::onPreserveInputToggled);
		menuEdit->addAction(aPreserveInput);
	}
	{ // Loads core widgets
		QSplitter* splitter = new QSplitter(Qt::Vertical);

		splitter->addWidget(fieldOut);
		splitter->addWidget(fieldIn);

		setCentralWidget(splitter);
	}
}


void createTerminalWidgets(LineEditCommand** const lec,
                           LineTerminal** const lt,
                           Terminal** const t,
                           QWidget* const parent,
                           Configuration const& config)
{
	*lec = new LineEditCommand(parent);
	(*lec)->setFont(config.ui_monospace);
	(*lec)->setColors(
	  config.ui_LineEditCommand_cf,
	  config.ui_LineEditCommand_cb);
	*lt = new LineTerminal(parent);
	(*lt)->setFont(config.ui_monospace);
	(*lt)->setColors(
	  config.ui_LineTerminal_cof,
	  config.ui_LineTerminal_cob,
	  config.ui_LineTerminal_cef,
	  config.ui_LineTerminal_ceb
	);
	*t = new Terminal(parent);
	(*t)->fieldOut->setFont(config.ui_monospace);
	(*t)->fieldIn->setFont(config.ui_monospace);

	LineTerminal* lineTerminal = *lt;
	Terminal* terminal = *t;
	// Binds redirectors
	mainDict()["al_OutputRedirector"] =
	  boost::python::class_<OutputRedirector>("OutputRedirector",
	      boost::python::no_init)
	  .def("write", &OutputRedirector::write);

	boost::python::import("sys").attr("stdout") =
	  OutputRedirector("[Out] ",
	                   [lineTerminal, terminal](std::string str)
	{
		lineTerminal->setLineOut(str);
		terminal->fieldOut->onStdOutFlush(str);
	}
	                  );
	boost::python::import("sys").attr("stderr") =
	  OutputRedirector("[Err] ",
	                   [lineTerminal, terminal](std::string str)
	{
		lineTerminal->setLineErr(str);
		terminal->fieldOut->onStdErrFlush(str);
	}
	                  );

	// Lambda for executing python
	auto lExec = [lineTerminal, terminal](std::string script)
	{
		namespace py = boost::python;

		lineTerminal->clearText();

		try
		{
			py::object result = py::exec(script.c_str(), mainDict());
			if (!result.is_none())
			{
				char const* r = py::extract<char const*>(result);
				lineTerminal->setLineOut(std::string(r) + '\n');
				terminal->fieldOut->onStdOutFlush(std::string(r) + '\n');
			}
		}
		catch (py::error_already_set&)
		{
			std::string tb = traceback();
			lineTerminal->setLineErr(tb);
			terminal->fieldOut->onStdErrFlush(tb);
			PyErr_Clear();
		}
	};

	parent->connect(*lec, &LineEditCommand::execute,
	                parent, lExec);
	parent->connect((*t)->fieldIn, &TerminalFieldIn::execute,
	                parent, lExec);

	/*
	// Redirect cout and cerr to terminals


	typedef bio::tee_device<std::ostream, decltype(ltOut)> TeeLTOut;
	typedef bio::tee_device<std::ostream, decltype(ltErr)> TeeLTErr;

	static std::ostream pureCOut(std::cout.rdbuf());
	static std::ostream pureCErr(std::cerr.rdbuf());

	static TeeLTOut teeLTOut(pureCOut, ltOut);
	static TeeLTErr teeLTErr(pureCErr, ltErr);

	static bio::stream<TeeLTOut> streamLTOut(teeLTOut);
	static bio::stream<TeeLTErr> streamLTErr(teeLTErr);

	std::cout.rdbuf(streamLTOut.rdbuf());
	std::cerr.rdbuf(streamLTErr.rdbuf());
	*/
}

} // namespace al
