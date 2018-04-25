/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QFormLayout *formLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *Sync_checkBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *Adress_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *Port_lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *Username_lineEdit;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *updatePeriod_spinBox;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *cancel_pushButton;
    QPushButton *ok_pushButton;

    void setupUi(QWidget *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(472, 257);
        formLayout = new QFormLayout(SettingsDialog);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        groupBox = new QGroupBox(SettingsDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Sync_checkBox = new QCheckBox(groupBox);
        Sync_checkBox->setObjectName(QStringLiteral("Sync_checkBox"));
        Sync_checkBox->setEnabled(false);
        Sync_checkBox->setCheckable(true);
        Sync_checkBox->setChecked(false);

        verticalLayout->addWidget(Sync_checkBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Adress_lineEdit = new QLineEdit(groupBox);
        Adress_lineEdit->setObjectName(QStringLiteral("Adress_lineEdit"));

        horizontalLayout->addWidget(Adress_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        Port_lineEdit = new QLineEdit(groupBox);
        Port_lineEdit->setObjectName(QStringLiteral("Port_lineEdit"));

        horizontalLayout_2->addWidget(Port_lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        Username_lineEdit = new QLineEdit(groupBox);
        Username_lineEdit->setObjectName(QStringLiteral("Username_lineEdit"));

        horizontalLayout_3->addWidget(Username_lineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        formLayout->setWidget(0, QFormLayout::LabelRole, groupBox);

        groupBox_2 = new QGroupBox(SettingsDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        updatePeriod_spinBox = new QSpinBox(groupBox_2);
        updatePeriod_spinBox->setObjectName(QStringLiteral("updatePeriod_spinBox"));
        updatePeriod_spinBox->setMinimum(1);
        updatePeriod_spinBox->setMaximum(1825);
        updatePeriod_spinBox->setValue(90);

        horizontalLayout_5->addWidget(updatePeriod_spinBox);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(18, 121, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        formLayout->setWidget(0, QFormLayout::FieldRole, groupBox_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        cancel_pushButton = new QPushButton(SettingsDialog);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));

        horizontalLayout_6->addWidget(cancel_pushButton);

        ok_pushButton = new QPushButton(SettingsDialog);
        ok_pushButton->setObjectName(QStringLiteral("ok_pushButton"));

        horizontalLayout_6->addWidget(ok_pushButton);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_6);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QWidget *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", nullptr));
        groupBox->setTitle(QApplication::translate("SettingsDialog", "Database", nullptr));
        Sync_checkBox->setText(QApplication::translate("SettingsDialog", "Connect to Server", nullptr));
        label->setText(QApplication::translate("SettingsDialog", "Rest Server", nullptr));
        Adress_lineEdit->setText(QString());
        label_2->setText(QApplication::translate("SettingsDialog", "Server Port", nullptr));
        Port_lineEdit->setText(QString());
        label_3->setText(QApplication::translate("SettingsDialog", "Username", nullptr));
        Username_lineEdit->setText(QString());
        groupBox_2->setTitle(QApplication::translate("SettingsDialog", "Display Options", nullptr));
        label_5->setText(QApplication::translate("SettingsDialog", "Import data for", nullptr));
        label_6->setText(QApplication::translate("SettingsDialog", "days.", nullptr));
        cancel_pushButton->setText(QApplication::translate("SettingsDialog", "Cancel", nullptr));
        ok_pushButton->setText(QApplication::translate("SettingsDialog", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
