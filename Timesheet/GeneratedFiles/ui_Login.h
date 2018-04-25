/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *login_lineEdit;
    QLabel *label_2;
    QLineEdit *password_lineEdit;
    QPushButton *Cancel_pushButton;
    QPushButton *Login_pushButton;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(232, 117);
        formLayout = new QFormLayout(Login);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(Login);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        login_lineEdit = new QLineEdit(Login);
        login_lineEdit->setObjectName(QStringLiteral("login_lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, login_lineEdit);

        label_2 = new QLabel(Login);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        password_lineEdit = new QLineEdit(Login);
        password_lineEdit->setObjectName(QStringLiteral("password_lineEdit"));
        password_lineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, password_lineEdit);

        Cancel_pushButton = new QPushButton(Login);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));

        formLayout->setWidget(5, QFormLayout::LabelRole, Cancel_pushButton);

        Login_pushButton = new QPushButton(Login);
        Login_pushButton->setObjectName(QStringLiteral("Login_pushButton"));

        formLayout->setWidget(5, QFormLayout::FieldRole, Login_pushButton);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", nullptr));
        label->setText(QApplication::translate("Login", "Login", nullptr));
        label_2->setText(QApplication::translate("Login", "Password", nullptr));
        Cancel_pushButton->setText(QApplication::translate("Login", "Cancel", nullptr));
        Login_pushButton->setText(QApplication::translate("Login", "Log In!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
