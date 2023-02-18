#pragma once

#include <QWidget>
#include "ui_IsCodePage.h"
#include "DockManager.h"
#include "qtextedit.h"
#include <map>
#include "qtimer.h"

class ZTokenizer;
class ZSource;

class IsCodePage : public ads::CDockWidget
{
	Q_OBJECT

public:
	IsCodePage(QWidget *parent = nullptr);
	~IsCodePage();
	void SetCode(ZSource* code);

	protected:
	void retoken();

	virtual void resizeEvent(QResizeEvent* event);
	void highlightText();
	void Tokenize();
	void TextChange();
	
private:
	QTimer* rehighlight = nullptr;
	Ui::IsCodePageClass ui;
	QTextEdit* mText;
	ZTokenizer* mToker;
	ZSource* mSource;
	std::map<std::string, QColor> mWordMap;
};
