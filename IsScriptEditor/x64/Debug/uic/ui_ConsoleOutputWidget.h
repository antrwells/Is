/********************************************************************************
** Form generated from reading UI file 'ConsoleOutputWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLEOUTPUTWIDGET_H
#define UI_CONSOLEOUTPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConsoleOutputWidgetClass
{
public:

    void setupUi(QWidget *ConsoleOutputWidgetClass)
    {
        if (ConsoleOutputWidgetClass->objectName().isEmpty())
            ConsoleOutputWidgetClass->setObjectName("ConsoleOutputWidgetClass");
        ConsoleOutputWidgetClass->resize(600, 400);

        retranslateUi(ConsoleOutputWidgetClass);

        QMetaObject::connectSlotsByName(ConsoleOutputWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ConsoleOutputWidgetClass)
    {
        ConsoleOutputWidgetClass->setWindowTitle(QCoreApplication::translate("ConsoleOutputWidgetClass", "ConsoleOutputWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConsoleOutputWidgetClass: public Ui_ConsoleOutputWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLEOUTPUTWIDGET_H
