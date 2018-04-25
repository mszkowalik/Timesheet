/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionInfo;
    QAction *actionPreferences;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExport_Excel;
    QAction *actionJoin;
    QAction *actionExit;
    QAction *actionExport_XML;
    QAction *actionImportNew;
    QAction *actionImportOld;
    QAction *actionSalary_Paid;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *Frame;
    QVBoxLayout *verticalLayout_2;
    QComboBox *Company_comboBox;
    QComboBox *Project_comboBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QDateEdit *Start_dateEdit;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QDateEdit *Stop_dateEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLineEdit *workingHours_lineEdit;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *Start_pushButton;
    QPushButton *Stop_pushButton;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QLineEdit *Owner_lineEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *EditJob_pushButton;
    QFrame *MainView;
    QVBoxLayout *verticalLayout_4;
    QTreeView *Timesheet_treeView;
    QFrame *Stats;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *StatS_tab;
    QVBoxLayout *verticalLayout;
    QTreeView *Stats_treeView;
    QWidget *queryBuilder_tab;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *QB_scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuExport;
    QMenu *menuImport;
    QMenu *menuEdit;
    QMenu *menuCompany;
    QMenu *menuHelo;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1189, 518);
        MainWindowClass->setDocumentMode(false);
        actionInfo = new QAction(MainWindowClass);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionPreferences = new QAction(MainWindowClass);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindowClass);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionExport_Excel = new QAction(MainWindowClass);
        actionExport_Excel->setObjectName(QStringLiteral("actionExport_Excel"));
        actionJoin = new QAction(MainWindowClass);
        actionJoin->setObjectName(QStringLiteral("actionJoin"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExport_XML = new QAction(MainWindowClass);
        actionExport_XML->setObjectName(QStringLiteral("actionExport_XML"));
        actionImportNew = new QAction(MainWindowClass);
        actionImportNew->setObjectName(QStringLiteral("actionImportNew"));
        actionImportOld = new QAction(MainWindowClass);
        actionImportOld->setObjectName(QStringLiteral("actionImportOld"));
        actionSalary_Paid = new QAction(MainWindowClass);
        actionSalary_Paid->setObjectName(QStringLiteral("actionSalary_Paid"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Frame = new QFrame(centralWidget);
        Frame->setObjectName(QStringLiteral("Frame"));
        Frame->setMaximumSize(QSize(175, 16777215));
        verticalLayout_2 = new QVBoxLayout(Frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        Company_comboBox = new QComboBox(Frame);
        Company_comboBox->setObjectName(QStringLiteral("Company_comboBox"));
        Company_comboBox->setEditable(true);

        verticalLayout_2->addWidget(Company_comboBox);

        Project_comboBox = new QComboBox(Frame);
        Project_comboBox->setObjectName(QStringLiteral("Project_comboBox"));
        Project_comboBox->setEditable(true);

        verticalLayout_2->addWidget(Project_comboBox);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_5 = new QLabel(Frame);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_8->addWidget(label_5);

        Start_dateEdit = new QDateEdit(Frame);
        Start_dateEdit->setObjectName(QStringLiteral("Start_dateEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Start_dateEdit->sizePolicy().hasHeightForWidth());
        Start_dateEdit->setSizePolicy(sizePolicy);
        Start_dateEdit->setMinimumSize(QSize(120, 20));
        Start_dateEdit->setMaximumSize(QSize(120, 20));
        Start_dateEdit->setReadOnly(true);
        Start_dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Start_dateEdit->setCurrentSection(QDateTimeEdit::NoSection);

        horizontalLayout_8->addWidget(Start_dateEdit);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_6 = new QLabel(Frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_9->addWidget(label_6);

        Stop_dateEdit = new QDateEdit(Frame);
        Stop_dateEdit->setObjectName(QStringLiteral("Stop_dateEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Stop_dateEdit->sizePolicy().hasHeightForWidth());
        Stop_dateEdit->setSizePolicy(sizePolicy1);
        Stop_dateEdit->setMinimumSize(QSize(120, 20));
        Stop_dateEdit->setMaximumSize(QSize(120, 20));
        Stop_dateEdit->setReadOnly(true);
        Stop_dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Stop_dateEdit->setCurrentSection(QDateTimeEdit::NoSection);

        horizontalLayout_9->addWidget(Stop_dateEdit);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_4 = new QLabel(Frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_7->addWidget(label_4);

        workingHours_lineEdit = new QLineEdit(Frame);
        workingHours_lineEdit->setObjectName(QStringLiteral("workingHours_lineEdit"));
        sizePolicy1.setHeightForWidth(workingHours_lineEdit->sizePolicy().hasHeightForWidth());
        workingHours_lineEdit->setSizePolicy(sizePolicy1);
        workingHours_lineEdit->setMaximumSize(QSize(100, 20));
        workingHours_lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(workingHours_lineEdit);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        Start_pushButton = new QPushButton(Frame);
        Start_pushButton->setObjectName(QStringLiteral("Start_pushButton"));

        horizontalLayout_6->addWidget(Start_pushButton);

        Stop_pushButton = new QPushButton(Frame);
        Stop_pushButton->setObjectName(QStringLiteral("Stop_pushButton"));
        Stop_pushButton->setEnabled(false);

        horizontalLayout_6->addWidget(Stop_pushButton);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_7 = new QLabel(Frame);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_11->addWidget(label_7);

        Owner_lineEdit = new QLineEdit(Frame);
        Owner_lineEdit->setObjectName(QStringLiteral("Owner_lineEdit"));

        horizontalLayout_11->addWidget(Owner_lineEdit);


        verticalLayout_2->addLayout(horizontalLayout_11);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        EditJob_pushButton = new QPushButton(Frame);
        EditJob_pushButton->setObjectName(QStringLiteral("EditJob_pushButton"));

        verticalLayout_2->addWidget(EditJob_pushButton);


        horizontalLayout->addWidget(Frame);

        MainView = new QFrame(centralWidget);
        MainView->setObjectName(QStringLiteral("MainView"));
        verticalLayout_4 = new QVBoxLayout(MainView);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        Timesheet_treeView = new QTreeView(MainView);
        Timesheet_treeView->setObjectName(QStringLiteral("Timesheet_treeView"));
        Timesheet_treeView->setMinimumSize(QSize(500, 0));
        Timesheet_treeView->setAlternatingRowColors(true);
        Timesheet_treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
        Timesheet_treeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        Timesheet_treeView->setIndentation(20);
        Timesheet_treeView->setUniformRowHeights(true);
        Timesheet_treeView->setSortingEnabled(true);
        Timesheet_treeView->setAnimated(false);
        Timesheet_treeView->setAllColumnsShowFocus(true);
        Timesheet_treeView->setHeaderHidden(false);

        verticalLayout_4->addWidget(Timesheet_treeView);


        horizontalLayout->addWidget(MainView);

        Stats = new QFrame(centralWidget);
        Stats->setObjectName(QStringLiteral("Stats"));
        Stats->setMaximumSize(QSize(400, 16777215));
        verticalLayout_3 = new QVBoxLayout(Stats);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tabWidget = new QTabWidget(Stats);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        StatS_tab = new QWidget();
        StatS_tab->setObjectName(QStringLiteral("StatS_tab"));
        verticalLayout = new QVBoxLayout(StatS_tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Stats_treeView = new QTreeView(StatS_tab);
        Stats_treeView->setObjectName(QStringLiteral("Stats_treeView"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Stats_treeView->sizePolicy().hasHeightForWidth());
        Stats_treeView->setSizePolicy(sizePolicy2);
        Stats_treeView->setAlternatingRowColors(true);

        verticalLayout->addWidget(Stats_treeView);

        tabWidget->addTab(StatS_tab, QString());
        queryBuilder_tab = new QWidget();
        queryBuilder_tab->setObjectName(QStringLiteral("queryBuilder_tab"));
        verticalLayout_5 = new QVBoxLayout(queryBuilder_tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        QB_scrollArea = new QScrollArea(queryBuilder_tab);
        QB_scrollArea->setObjectName(QStringLiteral("QB_scrollArea"));
        QB_scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 98, 28));
        QB_scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_5->addWidget(QB_scrollArea);

        tabWidget->addTab(queryBuilder_tab, QString());

        verticalLayout_3->addWidget(tabWidget);


        horizontalLayout->addWidget(Stats);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1189, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuExport = new QMenu(menuFile);
        menuExport->setObjectName(QStringLiteral("menuExport"));
        menuImport = new QMenu(menuFile);
        menuImport->setObjectName(QStringLiteral("menuImport"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuCompany = new QMenu(menuBar);
        menuCompany->setObjectName(QStringLiteral("menuCompany"));
        menuHelo = new QMenu(menuBar);
        menuHelo->setObjectName(QStringLiteral("menuHelo"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuCompany->menuAction());
        menuBar->addAction(menuHelo->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(menuExport->menuAction());
        menuFile->addAction(menuImport->menuAction());
        menuFile->addAction(actionExit);
        menuExport->addAction(actionExport_Excel);
        menuExport->addAction(actionExport_XML);
        menuImport->addAction(actionImportNew);
        menuImport->addAction(actionImportOld);
        menuEdit->addAction(actionPreferences);
        menuEdit->addAction(actionJoin);
        menuCompany->addAction(actionSalary_Paid);
        menuHelo->addAction(actionInfo);

        retranslateUi(MainWindowClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QString());
        actionInfo->setText(QApplication::translate("MainWindowClass", "Info", nullptr));
        actionPreferences->setText(QApplication::translate("MainWindowClass", "Preferences", nullptr));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", nullptr));
        actionSave->setText(QApplication::translate("MainWindowClass", "Save", nullptr));
        actionSave_As->setText(QApplication::translate("MainWindowClass", "Save As", nullptr));
        actionExport_Excel->setText(QApplication::translate("MainWindowClass", "Excel", nullptr));
        actionJoin->setText(QApplication::translate("MainWindowClass", "Join", nullptr));
#ifndef QT_NO_WHATSTHIS
        actionJoin->setWhatsThis(QApplication::translate("MainWindowClass", "Join indexes divided into two days", nullptr));
#endif // QT_NO_WHATSTHIS
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", nullptr));
        actionExport_XML->setText(QApplication::translate("MainWindowClass", "XML", nullptr));
        actionImportNew->setText(QApplication::translate("MainWindowClass", "DAT", nullptr));
        actionImportOld->setText(QApplication::translate("MainWindowClass", "XML", nullptr));
        actionSalary_Paid->setText(QApplication::translate("MainWindowClass", "Salary Paid", nullptr));
        label_5->setText(QApplication::translate("MainWindowClass", "Start:", nullptr));
        Start_dateEdit->setDisplayFormat(QApplication::translate("MainWindowClass", "HH:mm:ss  dd-MM-yyyy", nullptr));
        label_6->setText(QApplication::translate("MainWindowClass", "Stop:", nullptr));
        Stop_dateEdit->setDisplayFormat(QApplication::translate("MainWindowClass", "HH:mm:ss  dd-MM-yyyy", nullptr));
        label_4->setText(QApplication::translate("MainWindowClass", "Time:", nullptr));
        Start_pushButton->setText(QApplication::translate("MainWindowClass", "Start", nullptr));
        Stop_pushButton->setText(QApplication::translate("MainWindowClass", "Stop", nullptr));
        label_7->setText(QApplication::translate("MainWindowClass", "Owner", nullptr));
        Owner_lineEdit->setText(QString());
        EditJob_pushButton->setText(QApplication::translate("MainWindowClass", "Edit Job", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(StatS_tab), QApplication::translate("MainWindowClass", "Statistics", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(queryBuilder_tab), QApplication::translate("MainWindowClass", "Query Builder", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", nullptr));
        menuExport->setTitle(QApplication::translate("MainWindowClass", "Export", nullptr));
        menuImport->setTitle(QApplication::translate("MainWindowClass", "Import", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindowClass", "Edit", nullptr));
        menuCompany->setTitle(QApplication::translate("MainWindowClass", "Company", nullptr));
        menuHelo->setTitle(QApplication::translate("MainWindowClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
