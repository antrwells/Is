#pragma once

#include <QWidget>
#include "ui_CodeComplete.h"
#include "qlistwidget.h"

class ZMainNode;
class ZClassNode;

enum CCMode {

	Classes,Methods,Members,LocalVars,SpecificClass

};

class CodeComplete : public QWidget
{
	Q_OBJECT

public:
	CodeComplete(QWidget *parent = nullptr);
	~CodeComplete();
	static CodeComplete* mThis;
	void SetNode(ZMainNode* node);
	void Rebuild();
	void SetMode(CCMode mode) {
		mMode = mode;
	}
	void SetClass(ZClassNode* cls) {
		mClass = cls;
	}
	std::string GetNow();
	bool Up();
	bool Down();
	void Cancel();
	void SetFilter(std::string filter) {
		mFilter = filter;
		Rebuild();
	}
	void SetClassFilter(std::string filter)
	{
		mClassFilter = filter;
		Rebuild();
	}
	ZClassNode* GetClass(std::string name);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
private:
	Ui::CodeCompleteClass ui;
	ZMainNode* mNode = nullptr;
	QListWidget* listWidget;
	CCMode mMode = CCMode::Classes;
	ZClassNode* mClass = nullptr;
	std::string mFilter = "";
	std::string mClassFilter = "";
};
