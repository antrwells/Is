#include "IsCodePage.h"
#include <QRegularExpression>
#include "ZSource.h"
#include <QTextBlock>
#include "ZTokenizer.h"
#include "qfile.h"

IsCodePage::IsCodePage(QWidget *parent)
	: CDockWidget("Code",parent)
{
	ui.setupUi(this);
	auto page = new QTextEdit;
	mText = new QTextEdit(this);
	mText->setGeometry(0, 0, width(), height());

	QFont font = mText->font();
	font.setPointSize(font.pointSize() + 3);
	mText->setFont(font);
		update();
	connect(mText, &QTextEdit::textChanged, this, &IsCodePage::TextChange);
	//
	//mText->setTabStopWidth(42);

	mText->setTabStopDistance(32);

	mWordMap.insert(std::make_pair("class", QColor(255, 128, 0)));
	mWordMap.insert(std::make_pair("if", QColor(255, 128, 0)));
	mWordMap.insert(std::make_pair("end", QColor(255, 255, 0)));
	mWordMap.insert(std::make_pair("method", QColor(255, 255, 0)));
	mWordMap.insert(std::make_pair("void", QColor(128, 128, 0)));
	mWordMap.insert(std::make_pair("int", QColor(128, 128, 0)));
	mWordMap.insert(std::make_pair("float", QColor(128, 128, 0)));
	mWordMap.insert(std::make_pair("string", QColor(128, 128, 0)));
	mWordMap.insert(std::make_pair("list", QColor(128, 128, 0)));
	mWordMap.insert(std::make_pair("expr", QColor(0, 255, 255)));
	mWordMap.insert(std::make_pair("var", QColor(128, 128, 0)));
	mWordMap.insert(std::make_pair("(", QColor(255, 32, 0)));
	mWordMap.insert(std::make_pair(")", QColor(255, 32, 0)));
	
}

IsCodePage::~IsCodePage()
{}



void IsCodePage::resizeEvent(QResizeEvent* event)
{
	QSize size = event->size();
	int width = size.width();
	int height = size.height();

	mText->resize(width, height);

	// Perform actions based on the new size of the widget
	// ...

	// Don't forget to call the base implementation
	QWidget::resizeEvent(event);
}


std::string extractWordFromTextEdit(QTextEdit* textEdit, int lineNumber, int charPosition, int wordLength)
{
	// Move the cursor to the specified position
	QTextCursor cursor(textEdit->document());
	cursor.movePosition(QTextCursor::Start);
	cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumber - 1);
	cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, charPosition - 1);
	cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, wordLength);

	// Return the selected word
	return cursor.selectedText().toStdString();


}

void IsCodePage::SetCode(ZSource* code) {

	mText->blockSignals(true);
	auto cod = code->GetCode();
	mText->clear();
	for (int i = 0; i < cod.size(); i++) {

		mText->append(cod[i].c_str());

	}
	mSource = code;
	Tokenize();
	mText->blockSignals(false);

	//mText->setText(QString::fromStdString(code));
    //highlightText();


}

void IsCodePage::TextChange() {


	if (rehighlight != nullptr) {
		rehighlight->stop();
	
	}
	rehighlight = new QTimer(this);

	// Connect the timer to a function that will be called every time the timer ticks
	connect(rehighlight, &QTimer::timeout, this, &IsCodePage::retoken);

	// Set the interval of the timer to 2000ms (2 seconds)
	rehighlight->setInterval(3000);

	// Start the timer
	rehighlight->start();


}

void IsCodePage::retoken() {

	int a = 5;
	rehighlight->stop();

	QFile file("temp.zs");
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << mText->toPlainText();
		file.close();
	}

	QTextCursor cursor = mText->textCursor(); // get the cursor
	int cp = cursor.position(); // get the cursor position
	ZSource* src = new ZSource("temp.zs", false);
	SetCode(src);
	cursor.setPosition(cp); // set the cursor position
	mText->setTextCursor(cursor); // set the cursor in the text edit


}

void IsCodePage::highlightText() {

    mText->blockSignals(true);
//    QString text = mTextE->toPlainText();

    mText->blockSignals(false);

}
void colorizeWord(QTextEdit* textEdit, int lineNum, int charNum, int wordLength, QColor color) {
	QTextCursor cursor(textEdit->document()->findBlockByLineNumber(lineNum - 1)); // Set cursor to the line number
	cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, charNum - 1); // Move cursor to the character number
	cursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor, wordLength); // Select the specified word
	QTextCharFormat format;
	format.setForeground(QBrush(color)); // Set the color of the word
	cursor.setCharFormat(format); // Apply the color to the selected text
}

void IsCodePage::Tokenize() {

	mToker = new ZTokenizer(mSource);
	auto s = mToker->Tokenize();
	
	while (!s->EOS()) {

		auto tok = s->NextToken();
		//std::string text = "Token:" + tok.mText;
		//qDebug(text.c_str());
		int in = tok.TokenIndex;
		if (tok.mType == TokenType::TokenEndOfLine) {
			continue;
		}
		
		std::string mt = tok.mText;

		if (tok.mType == TokenType::TokenString) {

			mt = "\"" + mt + "\"";

		}
		
		std::string tex = extractWordFromTextEdit(mText, tok.TokenLineIndex,in+1,mt.size());



		if (tex != mt) {

			int rc = -2;

			int ri = in;

			for (int i = -4; i < 4; i++) {

				in = ri + i;

				tex = extractWordFromTextEdit(mText, tok.TokenLineIndex ,in,mt.size());
				if (tex == mt) {
					break;
				}

			}

		}
		else {
			in++;
		}


		int r = rand() % 255;
		QColor col(255, 255, 255);
		auto it = mWordMap.find(tex);
		if (it != mWordMap.end()) {
			QColor color = it->second;
			// Use the color here
			col = color;
		}
		
		int ms = 0;

		if (tok.mType == TokenType::TokenString)
		{
			col = QColor(255, 128, 64);
			
		}

		colorizeWord(mText, tok.TokenLineIndex, in,mt.size(), col);



	}

}