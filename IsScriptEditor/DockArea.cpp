#include "DockArea.h"
#include <QFile>
#include "ZSource.h"
#include <QString>

DockArea::DockArea(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	acceptDrops();

	m_DockManager = new ads::CDockManager(this);
	m_DockManager->setGeometry(0, 0, width(), height());

	w_Console = new ConsoleOutputWidget;
	m_DockManager->addDockWidget(ads::BottomDockWidgetArea, w_Console);

}

DockArea::~DockArea()
{}

IsCodePage* DockArea::AddNewPage() {

	auto code_page = new IsCodePage(this);
	code_page->setGeometry(0, 0, width(), height());

	m_DockManager->addDockWidgetTab(ads::CenterDockWidgetArea, code_page);
	
	return code_page;
}

void DockArea::LoadScript(std::string path)
{

	auto page = AddNewPage();
	page->setWindowTitle(path.c_str());

	ZSource* src = new ZSource(path.c_str(),false);

	page->SetCode(src);


	update();

}

void DockArea::NewScript() {


	auto page = AddNewPage();
	page->setWindowTitle("New Script");
	update();

}


void DockArea::resizeEvent(QResizeEvent* event)
{
	QSize size = event->size();
	int width = size.width();
	int height = size.height();

	
	m_DockManager->resize(width, height);

	// Perform actions based on the new size of the widget
	// ...

	// Don't forget to call the base implementation
	QWidget::resizeEvent(event);
}