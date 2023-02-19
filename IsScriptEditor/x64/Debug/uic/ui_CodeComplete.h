/********************************************************************************
** Form generated from reading UI file 'CodeComplete.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODECOMPLETE_H
#define UI_CODECOMPLETE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CodeCompleteClass
{
public:

    void setupUi(QWidget *CodeCompleteClass)
    {
        if (CodeCompleteClass->objectName().isEmpty())
            CodeCompleteClass->setObjectName("CodeCompleteClass");
        CodeCompleteClass->resize(600, 400);

        retranslateUi(CodeCompleteClass);

        QMetaObject::connectSlotsByName(CodeCompleteClass);
    } // setupUi

    void retranslateUi(QWidget *CodeCompleteClass)
    {
        CodeCompleteClass->setWindowTitle(QCoreApplication::translate("CodeCompleteClass", "CodeComplete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CodeCompleteClass: public Ui_CodeCompleteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODECOMPLETE_H
