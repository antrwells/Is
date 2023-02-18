#pragma once

#include <QWidget>
#include "ui_DockArea.h"
#include "IsCodePage.h"
#include <string>

class DockArea : public QWidget
{
	Q_OBJECT

public:
	DockArea(QWidget *parent = nullptr);
	~DockArea();
	IsCodePage* AddNewPage();
	void LoadScript(std::string path);
protected:
	virtual void resizeEvent(QResizeEvent* event);
private:
	Ui::DockAreaClass ui;
	std::vector<IsCodePage*> mCodePages;
	ads::CDockManager* m_DockManager;
};
