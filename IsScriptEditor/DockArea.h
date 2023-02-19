#pragma once

#include <QWidget>
#include "ui_DockArea.h"
#include "IsCodePage.h"
#include <string>
#include "ConsoleOutputWidget.h"

class DockArea : public QWidget
{
	Q_OBJECT

public:
	DockArea(QWidget *parent = nullptr);
	~DockArea();
	IsCodePage* AddNewPage();
	void LoadScript(std::string path);
	void NewScript();
protected:
	virtual void resizeEvent(QResizeEvent* event);
private:
	Ui::DockAreaClass ui;
	std::vector<IsCodePage*> mCodePages;
	ads::CDockManager* m_DockManager;
	ConsoleOutputWidget* w_Console;
};
