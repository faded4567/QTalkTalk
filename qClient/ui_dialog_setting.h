/********************************************************************************
** Form generated from reading UI file 'dialog_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SETTING_H
#define UI_DIALOG_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_setting
{
public:
    QLineEdit *ServerIP;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *PortNum;
    QComboBox *cb_ips;

    void setupUi(QDialog *Dialog_setting)
    {
        if (Dialog_setting->objectName().isEmpty())
            Dialog_setting->setObjectName(QString::fromUtf8("Dialog_setting"));
        Dialog_setting->resize(400, 300);
        ServerIP = new QLineEdit(Dialog_setting);
        ServerIP->setObjectName(QString::fromUtf8("ServerIP"));
        ServerIP->setGeometry(QRect(140, 140, 131, 21));
        pushButton = new QPushButton(Dialog_setting);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 210, 93, 28));
        pushButton_2 = new QPushButton(Dialog_setting);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 210, 93, 28));
        label = new QLabel(Dialog_setting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 40, 68, 15));
        label_2 = new QLabel(Dialog_setting);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 140, 101, 16));
        label_3 = new QLabel(Dialog_setting);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 90, 68, 15));
        PortNum = new QLineEdit(Dialog_setting);
        PortNum->setObjectName(QString::fromUtf8("PortNum"));
        PortNum->setGeometry(QRect(140, 90, 131, 21));
        cb_ips = new QComboBox(Dialog_setting);
        cb_ips->setObjectName(QString::fromUtf8("cb_ips"));
        cb_ips->setGeometry(QRect(140, 40, 131, 22));

        retranslateUi(Dialog_setting);

        QMetaObject::connectSlotsByName(Dialog_setting);
    } // setupUi

    void retranslateUi(QDialog *Dialog_setting)
    {
        Dialog_setting->setWindowTitle(QCoreApplication::translate("Dialog_setting", "Dialog", nullptr));
        ServerIP->setText(QCoreApplication::translate("Dialog_setting", "192.168.2.222", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog_setting", "OK", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog_setting", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("Dialog_setting", "\346\234\254\346\234\272IP", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_setting", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog_setting", "\347\253\257\345\217\243", nullptr));
        PortNum->setText(QCoreApplication::translate("Dialog_setting", "1234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_setting: public Ui_Dialog_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SETTING_H
