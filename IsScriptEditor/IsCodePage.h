#pragma once

#include <QWidget>
#include "ui_IsCodePage.h"
#include "DockManager.h"
#include "qtextedit.h"
#include <map>
#include "qtimer.h"
#include "ZProgramNode.h"
#include "CodeComplete.h"
#include <QTextBlock>
class ZTokenizer;
class ZSource;

class ConsoleWidgetOutput;

class IsCodePage : public ads::CDockWidget
{
	Q_OBJECT

public:
	IsCodePage(QWidget *parent = nullptr);
	~IsCodePage();
	void SetCode(ZSource* code);

	protected:
	void retoken();
	std::string getCurrentLine(QTextEdit* textEdit) {
		// Get the current line of text from the text edit
		QTextCursor cursor = textEdit->textCursor();
		int line_start_pos = cursor.block().position();
		cursor.movePosition(QTextCursor::StartOfLine);
		cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
		QString line = cursor.selectedText();

		// Convert the QString to a std::string and return it
		return line.toStdString();
	}
	int getCurrentPosition(QTextEdit* textEdit) {
		// Get the current cursor position within the line
		QTextCursor cursor = textEdit->textCursor();
		int line_start_pos = cursor.block().position();
		int cursor_pos = cursor.position();
		int current_pos = cursor_pos - line_start_pos - 1;

		return current_pos;
	}
	virtual void resizeEvent(QResizeEvent* event);
	void highlightText();
	void Tokenize();
	void TextChange();
	int CurrentLine();
	ZClassNode* ClassWithin();
	std::string PreviousTok();

	bool eventFilter(QObject* object, QEvent* event) override {
		if (!mComplete->isVisible()) {
			return false;
		}
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Escape) {

				mComplete->Cancel();

			}
			if (keyEvent->key() == Qt::Key_Down) {

				if (mComplete->Down())
				{
					return true;
				}
				else {
					return false;
				}

			}
			if (keyEvent->key() == Qt::Key_Up)
			{
				//auto text = mComplete->GetNow();

				if (mComplete->Up()) {

					return true;

				}
				else {
					return false;
				}
				//exit(1);

			}
			if (keyEvent->key() == Qt::Key_Tab || keyEvent->key()==Qt::Key_Return) {
				// Handle the Tab key press here
				auto text = mComplete->GetNow();
				
				if (text.size() > 0)
				{
					mComplete->SetClassFilter("");
					//QTextCursor cursor = mText->textCursor();
					//cursor.insertText(text.c_str());
					InsertSmart(text);
				}
				else {
					return false;
				}
				return true;
			}
		}

		return QObject::eventFilter(object, event);
	}
	void InsertSmart(std::string text);
private:
	QTimer* rehighlight = nullptr;
	Ui::IsCodePageClass ui;
	QTextEdit* mText;
	ZTokenizer* mToker;
	ZSource* mSource;
	std::map<std::string, QColor> mWordMap;
	ZMainNode* mNode;
	CodeComplete* mComplete;
};
