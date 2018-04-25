/********************************************************************************
** Form generated from reading UI file 'TimesheetWizard.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESHEETWIZARD_H
#define UI_TIMESHEETWIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_TimesheetWizard
{
public:
    QWizardPage *Intro;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QWizardPage *Type;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *Online_checkBox;
    QCheckBox *Offline_checkBox;
    QWizardPage *Offline;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *Owner_lineEdit;
    QSpacerItem *horizontalSpacer;
    QWizardPage *Online;
    QFormLayout *formLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *Username_lineEdit;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *ServerAdress_lineEdit;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *Port_lineEdit;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_4;
    QSpinBox *DataRetention_spinBox;
    QHBoxLayout *horizontalLayout_6;
    QDial *DataRetention_dial;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_5;
    QWizardPage *Path;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Path_lineEdit;
    QPushButton *choose_pushButton;
    QSpacerItem *horizontalSpacer_7;
    QWizardPage *End;

    void setupUi(QWizard *TimesheetWizard)
    {
        if (TimesheetWizard->objectName().isEmpty())
            TimesheetWizard->setObjectName(QStringLiteral("TimesheetWizard"));
        TimesheetWizard->resize(500, 360);
        TimesheetWizard->setWizardStyle(QWizard::AeroStyle);
        Intro = new QWizardPage();
        Intro->setObjectName(QStringLiteral("Intro"));
        verticalLayout = new QVBoxLayout(Intro);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(Intro);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(250, 250));
        label->setPixmap(QPixmap(QString::fromUtf8(":/MainWindow/Gandalf.jpg")));
        label->setScaledContents(true);

        horizontalLayout_2->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_2);

        TimesheetWizard->setPage(0, Intro);
        Type = new QWizardPage();
        Type->setObjectName(QStringLiteral("Type"));
        verticalLayout_2 = new QVBoxLayout(Type);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        Online_checkBox = new QCheckBox(Type);
        Online_checkBox->setObjectName(QStringLiteral("Online_checkBox"));
        Online_checkBox->setChecked(true);

        verticalLayout_2->addWidget(Online_checkBox);

        Offline_checkBox = new QCheckBox(Type);
        Offline_checkBox->setObjectName(QStringLiteral("Offline_checkBox"));

        verticalLayout_2->addWidget(Offline_checkBox);

        TimesheetWizard->setPage(1, Type);
        Offline = new QWizardPage();
        Offline->setObjectName(QStringLiteral("Offline"));
        verticalLayout_3 = new QVBoxLayout(Offline);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        Owner_lineEdit = new QLineEdit(Offline);
        Owner_lineEdit->setObjectName(QStringLiteral("Owner_lineEdit"));

        horizontalLayout_7->addWidget(Owner_lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_7);

        TimesheetWizard->setPage(2, Offline);
        Online = new QWizardPage();
        Online->setObjectName(QStringLiteral("Online"));
        formLayout = new QFormLayout(Online);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(Online);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Username_lineEdit = new QLineEdit(Online);
        Username_lineEdit->setObjectName(QStringLiteral("Username_lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Username_lineEdit->sizePolicy().hasHeightForWidth());
        Username_lineEdit->setSizePolicy(sizePolicy);
        Username_lineEdit->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(Username_lineEdit);

        horizontalSpacer_4 = new QSpacerItem(408, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_3);

        label_3 = new QLabel(Online);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ServerAdress_lineEdit = new QLineEdit(Online);
        ServerAdress_lineEdit->setObjectName(QStringLiteral("ServerAdress_lineEdit"));
        sizePolicy.setHeightForWidth(ServerAdress_lineEdit->sizePolicy().hasHeightForWidth());
        ServerAdress_lineEdit->setSizePolicy(sizePolicy);
        ServerAdress_lineEdit->setMinimumSize(QSize(200, 0));

        horizontalLayout_4->addWidget(ServerAdress_lineEdit);

        horizontalSpacer_5 = new QSpacerItem(408, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_4);

        label_4 = new QLabel(Online);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        Port_lineEdit = new QLineEdit(Online);
        Port_lineEdit->setObjectName(QStringLiteral("Port_lineEdit"));
        sizePolicy.setHeightForWidth(Port_lineEdit->sizePolicy().hasHeightForWidth());
        Port_lineEdit->setSizePolicy(sizePolicy);
        Port_lineEdit->setMinimumSize(QSize(200, 0));

        horizontalLayout_5->addWidget(Port_lineEdit);

        horizontalSpacer_6 = new QSpacerItem(408, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_5);

        label_6 = new QLabel(Online);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        DataRetention_spinBox = new QSpinBox(Online);
        DataRetention_spinBox->setObjectName(QStringLiteral("DataRetention_spinBox"));
        DataRetention_spinBox->setMinimumSize(QSize(200, 0));
        DataRetention_spinBox->setMaximumSize(QSize(200, 16777215));
        DataRetention_spinBox->setMinimum(-1);
        DataRetention_spinBox->setMaximum(500);

        verticalLayout_4->addWidget(DataRetention_spinBox);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        DataRetention_dial = new QDial(Online);
        DataRetention_dial->setObjectName(QStringLiteral("DataRetention_dial"));
        DataRetention_dial->setMinimum(-1);
        DataRetention_dial->setMaximum(500);

        horizontalLayout_6->addWidget(DataRetention_dial);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_6);


        formLayout->setLayout(3, QFormLayout::FieldRole, verticalLayout_4);

        label_5 = new QLabel(Online);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::FieldRole, label_5);

        TimesheetWizard->setPage(3, Online);
        Path = new QWizardPage();
        Path->setObjectName(QStringLiteral("Path"));
        verticalLayout_5 = new QVBoxLayout(Path);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_7 = new QLabel(Path);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_5->addWidget(label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Path_lineEdit = new QLineEdit(Path);
        Path_lineEdit->setObjectName(QStringLiteral("Path_lineEdit"));
        Path_lineEdit->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(Path_lineEdit);

        choose_pushButton = new QPushButton(Path);
        choose_pushButton->setObjectName(QStringLiteral("choose_pushButton"));

        horizontalLayout->addWidget(choose_pushButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout_5->addLayout(horizontalLayout);

        TimesheetWizard->setPage(4, Path);
        End = new QWizardPage();
        End->setObjectName(QStringLiteral("End"));
        TimesheetWizard->setPage(5, End);

        retranslateUi(TimesheetWizard);

        QMetaObject::connectSlotsByName(TimesheetWizard);
    } // setupUi

    void retranslateUi(QWizard *TimesheetWizard)
    {
        TimesheetWizard->setWindowTitle(QApplication::translate("TimesheetWizard", "Timesheet Wizard", nullptr));
        Intro->setTitle(QApplication::translate("TimesheetWizard", "Timesheet Wizard", nullptr));
        Intro->setSubTitle(QApplication::translate("TimesheetWizard", "This Wizard will help You set up your timesheet", nullptr));
        label->setText(QString());
        Type->setTitle(QApplication::translate("TimesheetWizard", "Online or Offline?", nullptr));
        Type->setSubTitle(QApplication::translate("TimesheetWizard", "Online version gives you possibility to to store your jobs in database, but you are not allowed to change them, once they are uploaded. Offline gives you full access to data stored in *.dat file.", nullptr));
        Online_checkBox->setText(QApplication::translate("TimesheetWizard", "Online", nullptr));
        Offline_checkBox->setText(QApplication::translate("TimesheetWizard", "Offline", nullptr));
        Offline->setTitle(QApplication::translate("TimesheetWizard", "Offline", nullptr));
        Offline->setSubTitle(QApplication::translate("TimesheetWizard", "Offline it is! What is your name?", nullptr));
        Online->setTitle(QApplication::translate("TimesheetWizard", "Great! Where to store your data?", nullptr));
        label_2->setText(QApplication::translate("TimesheetWizard", "Username", nullptr));
        label_3->setText(QApplication::translate("TimesheetWizard", "Server adress", nullptr));
        label_4->setText(QApplication::translate("TimesheetWizard", "Port", nullptr));
        label_6->setText(QApplication::translate("TimesheetWizard", "Data retention", nullptr));
        label_5->setText(QApplication::translate("TimesheetWizard", "Psst! -1 will make sure to always have all data on your pc", nullptr));
        Path->setTitle(QApplication::translate("TimesheetWizard", "Everything almost Ready!", nullptr));
        Path->setSubTitle(QApplication::translate("TimesheetWizard", "Last thing, and we're done! Where to store your timesheet?", nullptr));
        label_7->setText(QApplication::translate("TimesheetWizard", "Filename:", nullptr));
        choose_pushButton->setText(QApplication::translate("TimesheetWizard", "Choose", nullptr));
        End->setTitle(QApplication::translate("TimesheetWizard", "See Ya!", nullptr));
        End->setSubTitle(QApplication::translate("TimesheetWizard", "Everything's set up, time to rock!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimesheetWizard: public Ui_TimesheetWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESHEETWIZARD_H
