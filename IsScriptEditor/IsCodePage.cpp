#include "IsCodePage.h"
#include <QRegularExpression>
#include "ZSource.h"

#include "ZTokenizer.h"
#include "qfile.h"
#include "ZParser.h"
#include "ZClassNode.h"
#include "ZMethodNode.h"
#include "ConsoleOutputWidget.h"
#include "IsScriptEditor.h"


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

	mComplete = new CodeComplete(this);
	mComplete->setGeometry(300, 60, 180, 220);
	
	mText->installEventFilter(this);

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
void replaceHalfWord(std::string& line, int pos, const std::string& replacement)
{
	// Find the beginning and end of the half-word
	int start = pos;
	while (start >= 0 && isalnum(line[start])) {
		start--;
	}
	start++;

	int end = pos;
	while (end < line.length() && isalnum(line[end])) {
		end++;
	}

	// Replace the half-word with the replacement string
	if (end - start < replacement.length()) {
		// The replacement word is longer than the half-word, so replace the whole word
		int wordStart = start;
		while (wordStart >= 0 && !isspace(line[wordStart])) {
			wordStart--;
		}
		wordStart++;

		int wordEnd = end;
		while (wordEnd < line.length() && !isspace(line[wordEnd])) {
			wordEnd++;
		}

		if (wordEnd - wordStart >= replacement.length()) {
			// The word is long enough to fit the replacement word
			line.replace(wordStart, wordEnd - wordStart, replacement);
		}
		else {
			// The word is too short to fit the replacement word, so insert it
			line.insert(end, " " + replacement);
		}
	}
	else {
		// The replacement word is shorter than or equal to the half-word, so replace the half-word
		line.replace(start, end - start, replacement);
	}
}

std::string getPreviousToken(const std::string& text, int pos)
{
	// Initialize the token string
	std::string token = "";

	// Traverse backwards from the given position until a viable token is found
	for (int i = pos - 1; i >= 0; i--) {
		char c = text[i];
		if (isspace(c) || ispunct(c)) {
			if (token.empty()) {
				// Skip leading spaces and operators
				continue;
			}
			else {
				// A viable token has been found
				return token;
			}
		}
		else {
			// Add the character to the token string
			token = c + token;
		}
		if (i == 0) {
			// The beginning of the string has been reached
			if (!token.empty()) {
				// A viable token has been found
				return token;
			}
			else {
				// No viable token was found
				return "";
			}
		}
	}

	// No viable token was found
	return "";
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

	std::string msg = "Script:" + windowTitle().toStdString();

	msg = msg + " Line:" + std::to_string(CurrentLine());

	IsScriptEditor::mThis->SetStatus(msg);

	QRect cursorRect = mText->cursorRect();
	int cursorY = cursorRect.top();
	int cursorX = cursorRect.right();
	mComplete->setGeometry(cursorX+30, cursorY, mComplete->width(), mComplete->height());
	
	QTextCursor cursor = mText->textCursor();
	QTextBlock block = cursor.block();
	QString lineText = block.text();

	std::string line = lineText.toStdString();
	
	if (line.size() == 0) {
		mComplete->setVisible(false);
	}
	else {
		QTextCursor cursor = mText->textCursor();
		int blockPosition = cursor.block().position();
		int cursorPosition = cursor.position();
		int currentCharX = cursorPosition - blockPosition;


		auto lt = getPreviousToken(lineText.toStdString(), currentCharX);
		if (lt.size() > 0) {
			ConsoleOutputWidget::LogMessage(lt);
		}
		mComplete->SetFilter(lt);
	}
	


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

	ConsoleOutputWidget::LogMessage("Compiling/testing code...");
	mToker = new ZTokenizer(mSource);
	auto s = mToker->Tokenize();
	auto parser = new ZParser(s);
	 mNode = parser->Parse();
	std::string c_msg = "Compiled. Classes found:" + std::to_string(mNode->GetClasses().size());
	ConsoleOutputWidget::LogMessage(c_msg);

	auto classes = mNode->GetClasses();

	for (int i = 0; i < classes.size(); i++) {
		
		auto cls = classes[i];
		
		std::string msg = "Class:" + cls->GetName();

		ConsoleOutputWidget::LogMessage(msg);

		msg = "Method Count:" + std::to_string(cls->GetMethods().size());

		ConsoleOutputWidget::LogMessage(msg);

		for (int j = 0; j < cls->GetMethods().size(); j++) {

			auto meth = cls->GetMethods()[j];
			msg = "Method:" + meth->GetName();

			ConsoleOutputWidget::LogMessage(msg);

		}


	}
	mComplete->SetMode(CCMode::Classes);
	
	auto ci = ClassWithin();

	if (ci != nullptr) {

		mComplete->SetMode(CCMode::SpecificClass);
		std::vector<ZContextVar*> pars = {};
		mComplete->SetClass(ci->CreateInstance("CC", pars));
	}

	mComplete->SetNode(mNode);


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

int IsCodePage::CurrentLine() {

	

	auto cursor = mText->textCursor();
	return cursor.blockNumber();


}

ZClassNode* IsCodePage::ClassWithin() {

	ZClassNode* r = nullptr;

	auto line = CurrentLine();

	auto classes = mNode->GetClasses();

	for (int i = 0; i < classes.size(); i++) {

		auto cls = classes[i];

		if (cls->GetLineStart() <= line && cls->GetLineEnd() >= line) {

			r = cls;

			break;

		}

	}

	return r;

}

void insertStringAtCurrentPosition(QTextEdit* textEdit, std::string str) {
	// Get the current cursor position within the line
	QTextCursor cursor = textEdit->textCursor();
	int line_start_pos = cursor.block().position();
	int cursor_pos = cursor.position();
	int current_pos = cursor_pos - line_start_pos - 1;

	// Insert the string at the current position
	cursor.insertText(QString::fromStdString(str));
	cursor.setPosition(line_start_pos + current_pos + str.length() + 1);
	textEdit->setTextCursor(cursor);
}

int find_substring(std::string word, std::string substring) {
	int pos = word.find(substring); // find the position of the substring in the word
	if (pos == std::string::npos) { // if substring is not found, return -1
		return -1;
	}
	else { // otherwise, return the starting position of the substring
		return pos;
	}
}

std::string getCurrentLine(QTextEdit* textEdit) {
	QTextCursor cursor = textEdit->textCursor(); // get the cursor of the text edit
	cursor.movePosition(QTextCursor::StartOfLine); // move the cursor to the start of the current line
	int startPos = cursor.position();
	cursor.movePosition(QTextCursor::EndOfLine); // move the cursor to the end of the current line
	int endPos = cursor.position();
	QString line = textEdit->toPlainText().mid(startPos, endPos - startPos); // get the current line of text as a QString
	return line.toStdString(); // convert the QString to a std::string and return it
}

void replaceCurrentLine(QTextEdit* textEdit, const QString& newLine) {
	QTextCursor cursor = textEdit->textCursor(); // get the cursor of the text edit
	cursor.movePosition(QTextCursor::StartOfLine); // move the cursor to the start of the current line
	int startPos = cursor.position();
	cursor.movePosition(QTextCursor::EndOfLine); // move the cursor to the end of the current line
	int endPos = cursor.position();
	cursor.setPosition(startPos, QTextCursor::KeepAnchor); // select the current line
	cursor.insertText(newLine); // replace the current line with the new line
}

int getXPosition(QTextEdit *textEdit) {
    QTextCursor cursor = textEdit->textCursor(); // get the cursor of the text edit
    cursor.movePosition(QTextCursor::StartOfLine); // move the cursor to the start of the line
    int startPos = cursor.position();
    int x = cursor.positionInBlock(); // get the x position (in characters) of the cursor
    return x; // return the total x position (in characters)
}

void IsCodePage::InsertSmart(std::string word) {


	QTextCursor cursor = mText->textCursor();
	QTextBlock block = cursor.block();
	QString lineText = block.text();

	std::string line = lineText.toStdString();

	//replaceCurrentHalfWord(mText, word);
	cursor = mText->textCursor();
	int blockPosition = cursor.block().position();
	int cursorPosition = cursor.position();
	int currentCharX = cursorPosition - blockPosition;


	auto lt = getPreviousToken(lineText.toStdString(), currentCharX);
	
	if (lt.size() > 0) {

		auto ss = find_substring(word, lt);
		if (ss > -1)
		{

			std::string curLine = getCurrentLine(mText);

			int sa = find_substring(curLine,lt);
			
			std::string pre = curLine.substr(0, sa);
			std::string post = curLine.substr(sa+lt.size(),curLine.size()-(sa+lt.size()));
			
			replaceCurrentLine(mText, QString::fromStdString(pre + word + post));

			int a = 5;
		}

	}
	else {

		std::string curLine = getCurrentLine(mText);

		int sa = getXPosition(mText);

		std::string pre = curLine.substr(0, sa+1);
		std::string post = curLine.substr(sa+2, curLine.size() - sa-1);

		replaceCurrentLine(mText, QString::fromStdString(pre + word + post));

	}


	int a = 5;


}