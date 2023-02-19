#include "ConsoleOutputWidget.h"

ConsoleOutputWidget::ConsoleOutputWidget(QWidget *parent)
	: CDockWidget("Console Output",parent)
{
	ui.setupUi(this);
	sThis = this;
	w_Text = new QTextEdit(this);
	w_Text->setGeometry(0, 0, width(), height());

	w_Text->setAutoFillBackground(true);

	// Create a palette and set the background color
	QPalette pal = w_Text->palette();
	pal.setColor(QPalette::Base, Qt::darkCyan);
	pal.setColor(QPalette::Text, Qt::white);
	w_Text->setPalette(pal);
	


}

ConsoleOutputWidget::~ConsoleOutputWidget()
{}

ConsoleOutputWidget* ConsoleOutputWidget::sThis = nullptr;


void ConsoleOutputWidget::resizeEvent(QResizeEvent* event) {

	w_Text->resize(width(), height());


}

void ConsoleOutputWidget::LogMessage(std::string msg) {

	sThis->LogMsg(msg);

}

void ConsoleOutputWidget::LogMsg(std::string msg) {

	msg = msg + "\n";
	w_Text->insertPlainText(QString(msg.c_str()));

}