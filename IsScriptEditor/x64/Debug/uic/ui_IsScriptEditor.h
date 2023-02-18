/********************************************************************************
** Form generated from reading UI file 'IsScriptEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISSCRIPTEDITOR_H
#define UI_ISSCRIPTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IsScriptEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IsScriptEditorClass)
    {
        if (IsScriptEditorClass->objectName().isEmpty())
            IsScriptEditorClass->setObjectName("IsScriptEditorClass");
        IsScriptEditorClass->resize(600, 400);
        menuBar = new QMenuBar(IsScriptEditorClass);
        menuBar->setObjectName("menuBar");
        IsScriptEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IsScriptEditorClass);
        mainToolBar->setObjectName("mainToolBar");
        IsScriptEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(IsScriptEditorClass);
        centralWidget->setObjectName("centralWidget");
        IsScriptEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(IsScriptEditorClass);
        statusBar->setObjectName("statusBar");
        IsScriptEditorClass->setStatusBar(statusBar);

        retranslateUi(IsScriptEditorClass);

        QMetaObject::connectSlotsByName(IsScriptEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *IsScriptEditorClass)
    {
        IsScriptEditorClass->setWindowTitle(QCoreApplication::translate("IsScriptEditorClass", "IsScriptEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IsScriptEditorClass: public Ui_IsScriptEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISSCRIPTEDITOR_H
