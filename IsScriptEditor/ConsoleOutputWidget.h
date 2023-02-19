#pragma once

#include <QWidget>
#include "ui_ConsoleOutputWidget.h"
#include "DockManager.h"
#include "qtextedit.h"

class ConsoleOutputWidget : public ads::CDockWidget
{
	Q_OBJECT

public:
	ConsoleOutputWidget(QWidget *parent = nullptr);
	~ConsoleOutputWidget();
	static ConsoleOutputWidget* sThis;
	static void LogMessage(std::string msg);
	void LogMsg(std::string msg);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	Ui::ConsoleOutputWidgetClass ui;
	QTextEdit* w_Text;
};
