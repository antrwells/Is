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
	void filterAdd(std::string name) {
		if (name.find(mFilter) != std::string::npos) {
			listWidget->addItem(name.c_str());
			//std::cout << "Substring found!" << std::endl;
		}
		else {
			
			//std::cout << "Substring not found." << std::endl;
		}
	}
	void SetClassFilter(std::string filter)
	{
		if (filter != mClassFilter) {
			mClassFilter = filter;
			mClsFilter = nullptr;
		}

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
	ZClassNode* mClsFilter = nullptr;
};
