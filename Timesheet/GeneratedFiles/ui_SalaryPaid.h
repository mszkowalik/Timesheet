/********************************************************************************
** Form generated from reading UI file 'SalaryPaid.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALARYPAID_H
#define UI_SALARYPAID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SalaryPaid
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *Company_comboBox;
    QCheckBox *AllPaid_checkBox;
    QListWidget *Projects_listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Cancel_pushButton;
    QPushButton *OK_pushButton;

    void setupUi(QWidget *SalaryPaid)
    {
        if (SalaryPaid->objectName().isEmpty())
            SalaryPaid->setObjectName(QStringLiteral("SalaryPaid"));
        SalaryPaid->resize(454, 428);
        verticalLayout = new QVBoxLayout(SalaryPaid);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Company_comboBox = new QComboBox(SalaryPaid);
        Company_comboBox->setObjectName(QStringLiteral("Company_comboBox"));

        verticalLayout->addWidget(Company_comboBox);

        AllPaid_checkBox = new QCheckBox(SalaryPaid);
        AllPaid_checkBox->setObjectName(QStringLiteral("AllPaid_checkBox"));

        verticalLayout->addWidget(AllPaid_checkBox);

        Projects_listWidget = new QListWidget(SalaryPaid);
        Projects_listWidget->setObjectName(QStringLiteral("Projects_listWidget"));

        verticalLayout->addWidget(Projects_listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Cancel_pushButton = new QPushButton(SalaryPaid);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));

        horizontalLayout->addWidget(Cancel_pushButton);

        OK_pushButton = new QPushButton(SalaryPaid);
        OK_pushButton->setObjectName(QStringLiteral("OK_pushButton"));

        horizontalLayout->addWidget(OK_pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SalaryPaid);

        QMetaObject::connectSlotsByName(SalaryPaid);
    } // setupUi

    void retranslateUi(QWidget *SalaryPaid)
    {
        SalaryPaid->setWindowTitle(QApplication::translate("SalaryPaid", "SalaryPaid", nullptr));
        AllPaid_checkBox->setText(QApplication::translate("SalaryPaid", "All paid", nullptr));
        Cancel_pushButton->setText(QApplication::translate("SalaryPaid", "Cancel", nullptr));
        OK_pushButton->setText(QApplication::translate("SalaryPaid", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SalaryPaid: public Ui_SalaryPaid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALARYPAID_H
