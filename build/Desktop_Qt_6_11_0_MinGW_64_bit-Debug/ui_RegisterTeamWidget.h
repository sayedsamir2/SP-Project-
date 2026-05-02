/********************************************************************************
** Form generated from reading UI file 'RegisterTeamWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERTEAMWIDGET_H
#define UI_REGISTERTEAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterTeamWidget
{
public:

    void setupUi(QWidget *RegisterTeamWidget)
    {
        if (RegisterTeamWidget->objectName().isEmpty())
            RegisterTeamWidget->setObjectName("RegisterTeamWidget");
        RegisterTeamWidget->resize(540, 600);

        retranslateUi(RegisterTeamWidget);

        QMetaObject::connectSlotsByName(RegisterTeamWidget);
    } // setupUi

    void retranslateUi(QWidget *RegisterTeamWidget)
    {
        RegisterTeamWidget->setWindowTitle(QCoreApplication::translate("RegisterTeamWidget", "\330\252\330\263\330\254\331\212\331\204 \331\201\330\261\331\212\331\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterTeamWidget: public Ui_RegisterTeamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERTEAMWIDGET_H
