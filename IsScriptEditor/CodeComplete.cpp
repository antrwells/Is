#include "CodeComplete.h"
#include "qpainter.h"
#include "qpainterpath.h"

#include <QResizeEvent>
#include "ZProgramNode.h"
#include "ZClassNode.h"
#include "ZContextVar.h"
#include "ZMethodNode.h"

CodeComplete::CodeComplete(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setStyleSheet("border: 1px solid white;");
	setStyleSheet("border: 2px dotted red;");
	setStyleSheet("QWidget { border: 1px solid black; }");
	listWidget = new QListWidget(this);
	listWidget->setGeometry(0, 0, width(), height());
	setVisible(false);

}

CodeComplete::~CodeComplete()
{}


void CodeComplete::paintEvent(QPaintEvent* event) {


	//CDockWidget::paintEvent(event);

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, false);
	p.setRenderHint(QPainter::TextAntialiasing, false);
	p.setRenderHint(QPainter::VerticalSubpixelPositioning, false);

	QPainterPath path;
	path.addRect(QRectF(0, 0, width()-1, height()-1));
	p.setPen(QPen(QColor(255, 255, 255), 1));
	//p.setPen(pen);

	p.fillPath(path, QColor(30, 30, 30));
	p.drawPath(path);


}

void CodeComplete::resizeEvent(QResizeEvent* event)
{
	QSize size = event->size();
	int width = size.width();
	int height = size.height();

	listWidget->resize(width, height);

	// Perform actions based on the new size of the widget
	// ...

	// Don't forget to call the base implementation
	QWidget::resizeEvent(event);
}


CodeComplete* CodeComplete::mThis = nullptr;

void CodeComplete::SetNode(ZMainNode* node) {

	mNode = node;
	Rebuild();

}

ZClassNode* CodeComplete::GetClass(std::string name) {

	auto cls = mNode->GetClass(name);

	return cls;
}

void CodeComplete::Rebuild() {

	if (mNode == nullptr) return;
	listWidget->clear();

	filterAdd("method");
	filterAdd("class");
	filterAdd("var");
	filterAdd("if");
	filterAdd("else");
	filterAdd("for");
	filterAdd("while");
	filterAdd("return");
	filterAdd("break");
	filterAdd("continue");
	filterAdd("switch");
	filterAdd("case");
	filterAdd("default");
	filterAdd("true");
	filterAdd("false");
	filterAdd("foreach");
	filterAdd("in");
	filterAdd("void");
	filterAdd("int");
	filterAdd("float");
	filterAdd("double");
	filterAdd("string");
	filterAdd("bool");
	filterAdd("null");
	filterAdd("this");
	filterAdd("new");
	filterAdd("delete");



	if (mClassFilter!="")
	{
		auto cls = GetClass(mClassFilter);

		if (mClsFilter == nullptr) {
			mClsFilter = cls->CreateInstance("CC", {});
		
		}

		auto meths = mClsFilter->GetMethods();

		for (int i = 0; i < meths.size(); i++) {

			auto meth = meths[i];
			std::string text = meth->GetName();// "V
			if (text.find(mFilter) != std::string::npos) {

				//std::cout << "Substring found!" << std::endl;
			}
			else {
				continue;
				//std::cout << "Substring not found." << std::endl;
			}

			listWidget->addItem(meth->GetName().c_str());

			

		}

		for (int i = 0; i < mClsFilter->GetVars().size(); i++) {

			auto var = mClsFilter->GetVars()[i];

			std::string type = "Unknown";

			switch (var->GetType()) {
			case VarType::VarInteger:
				type = "Integer";
				break;
			case VarType::VarFloat:
				type = "Float";
				break;
			case VarType::VarString:
				type = "String";
				break;
			case VarType::VarBool:
				type = "Bool";
				break;
			case VarType::VarList:
				type = "List";
				break;

			}

			std::string text = var->GetName();// "Var:" + var->GetName() + " Type:" + type;



			if (text.find(mFilter) != std::string::npos) {

				//std::cout << "Substring found!" << std::endl;
			}
			else {
				continue;
				//std::cout << "Substring not found." << std::endl;
			}

			listWidget->addItem(text.c_str());

		}

		if (listWidget->count() > 0) {
			setVisible(true);
		}
		else {
			setVisible(false);
		}
		return;
	}

//	if (mMode == CCMode::Classes) {
		for (int i = 0; i < mNode->GetClasses().size(); i++) {

			auto cls = mNode->GetClasses()[i];

			auto text = cls->GetName();//"Class:" + cls->GetName();

			if (text.find(mFilter) != std::string::npos) {
				
				//std::cout << "Substring found!" << std::endl;
			}
			else {
				continue;
				//std::cout << "Substring not found." << std::endl;
			}
			
			listWidget->addItem(cls->GetName().c_str());

		}

//	else {
		for (int i = 0; i < mClass->GetVars().size(); i++) {

			auto var = mClass->GetVars()[i];

			std::string type = "Unknown";

			switch (var->GetType()) {
			case VarType::VarInteger:
				type = "Integer";
				break;
			case VarType::VarFloat:
				type = "Float";
				break;
				case VarType::VarString:
					type = "String";
					break;
				case VarType::VarBool:
					type = "Bool";
					break;
				case VarType::VarList:
						type = "List";
					break;

			}

			std::string text = var->GetName();// "Var:" + var->GetName() + " Type:" + type;

			if (text.find(mFilter) != std::string::npos) {

				//std::cout << "Substring found!" << std::endl;
			}
			else {
				continue;
				//std::cout << "Substring not found." << std::endl;
			}

			listWidget->addItem(text.c_str());

		}
		for (int i = 0; i < mClass->GetMethods().size(); i++) {

			std::string text = mClass->GetMethods()[i]->GetName();// "Meth:" + mClass->GetMethods()[i]->GetName();
			

			if (text.find(mFilter) != std::string::npos) {

				//std::cout << "Substring found!" << std::endl;
			}
			else {
				continue;
				//std::cout << "Substring not found." << std::endl;
			}
			
			listWidget->addItem(text.c_str());



		}

	//}

	if (listWidget->count() > 0) {
		setVisible(true);
	}
	else {
		setVisible(false);
	}

}

std::string CodeComplete::GetNow() {

	if (listWidget->currentItem() != nullptr) {
		auto text = listWidget->currentItem()->text();
		if (text.length() > 0) {
			return text.toStdString();
		}
		else {
			return "";
		}
	}
	return "";
}

bool  CodeComplete::Up() {

	if (listWidget->count() == 0)
	{
		return false;
	}
	if (listWidget->count() == 1) {
		listWidget->setCurrentRow(0);
		return true;
	}

	int index = listWidget->currentRow();
	if (index > 0) {
		listWidget->setCurrentRow(index - 1);
	}
	else if(index<0) {

		listWidget->setCurrentRow(listWidget->count() - 1);

	}
	return true;


}

bool CodeComplete::Down() {

	if (listWidget->count() == 0)
	{
		return false;
	}
	if (listWidget->count() == 1) {
		listWidget->setCurrentRow(0);
		return true;
	}
	int index = listWidget->currentRow() + 1;
	if (index >= listWidget->count()) {
	//	listWidget->setCurrentRow(index - 1);
		listWidget->setCurrentRow(0);
	}
	else {
		listWidget->setCurrentRow(index);
	}
	return true;


	return false;

}

void CodeComplete::Cancel() {

	setVisible(false);

}