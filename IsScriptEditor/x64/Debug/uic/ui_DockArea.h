/********************************************************************************
** Form generated from reading UI file 'DockArea.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKAREA_H
#define UI_DOCKAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockAreaClass
{
public:

    void setupUi(QWidget *DockAreaClass)
    {
        if (DockAreaClass->objectName().isEmpty())
            DockAreaClass->setObjectName("DockAreaClass");
        DockAreaClass->resize(600, 400);

        retranslateUi(DockAreaClass);

        QMetaObject::connectSlotsByName(DockAreaClass);
    } // setupUi

    void retranslateUi(QWidget *DockAreaClass)
    {
        DockAreaClass->setWindowTitle(QCoreApplication::translate("DockAreaClass", "DockArea", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DockAreaClass: public Ui_DockAreaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKAREA_H
