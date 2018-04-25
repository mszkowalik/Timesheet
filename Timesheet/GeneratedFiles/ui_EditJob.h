/********************************************************************************
** Form generated from reading UI file 'EditJob.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITJOB_H
#define UI_EDITJOB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditJob
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDateTimeEdit *From_dateTimeEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDateTimeEdit *To_dateTimeEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *Company_comboBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *Project_comboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QTextEdit *Comment_textEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *Status_comboBox;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *Cancel_pushButton;
    QPushButton *OK_pushButton;

    void setupUi(QWidget *EditJob)
    {
        if (EditJob->objectName().isEmpty())
            EditJob->setObjectName(QStringLiteral("EditJob"));
        EditJob->resize(392, 353);
        verticalLayout = new QVBoxLayout(EditJob);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(EditJob);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        From_dateTimeEdit = new QDateTimeEdit(EditJob);
        From_dateTimeEdit->setObjectName(QStringLiteral("From_dateTimeEdit"));

        horizontalLayout->addWidget(From_dateTimeEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(EditJob);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        To_dateTimeEdit = new QDateTimeEdit(EditJob);
        To_dateTimeEdit->setObjectName(QStringLiteral("To_dateTimeEdit"));

        horizontalLayout_2->addWidget(To_dateTimeEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(EditJob);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        Company_comboBox = new QComboBox(EditJob);
        Company_comboBox->setObjectName(QStringLiteral("Company_comboBox"));
        Company_comboBox->setEditable(true);

        horizontalLayout_3->addWidget(Company_comboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(EditJob);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        Project_comboBox = new QComboBox(EditJob);
        Project_comboBox->setObjectName(QStringLiteral("Project_comboBox"));
        Project_comboBox->setEditable(true);

        horizontalLayout_4->addWidget(Project_comboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(EditJob);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        Comment_textEdit = new QTextEdit(EditJob);
        Comment_textEdit->setObjectName(QStringLiteral("Comment_textEdit"));

        horizontalLayout_5->addWidget(Comment_textEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(EditJob);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        Status_comboBox = new QComboBox(EditJob);
        Status_comboBox->setObjectName(QStringLiteral("Status_comboBox"));

        horizontalLayout_6->addWidget(Status_comboBox);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        Cancel_pushButton = new QPushButton(EditJob);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));

        horizontalLayout_7->addWidget(Cancel_pushButton);

        OK_pushButton = new QPushButton(EditJob);
        OK_pushButton->setObjectName(QStringLiteral("OK_pushButton"));

        horizontalLayout_7->addWidget(OK_pushButton);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(EditJob);

        QMetaObject::connectSlotsByName(EditJob);
    } // setupUi

    void retranslateUi(QWidget *EditJob)
    {
        EditJob->setWindowTitle(QApplication::translate("EditJob", "EditJob", nullptr));
        label->setText(QApplication::translate("EditJob", "From", nullptr));
        label_2->setText(QApplication::translate("EditJob", "To", nullptr));
        label_3->setText(QApplication::translate("EditJob", "Company", nullptr));
        label_4->setText(QApplication::translate("EditJob", "Project", nullptr));
        label_5->setText(QApplication::translate("EditJob", "Comment", nullptr));
        label_6->setText(QApplication::translate("EditJob", "Status", nullptr));
        Cancel_pushButton->setText(QApplication::translate("EditJob", "Cancel", nullptr));
        OK_pushButton->setText(QApplication::translate("EditJob", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditJob: public Ui_EditJob {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITJOB_H
