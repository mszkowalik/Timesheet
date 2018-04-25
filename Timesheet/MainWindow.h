#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QSettings>
#include <qDebug>
#include <qstandarditemmodel.h>
#include "TreeModel.h"
#include "oldreader.h"
#include "Job.h"
#include "SettingsDialog.h"
#include <QFileDialog>
#include "Settings.h"
#include "Xmlstreamreader.h"
#include <Statistics.h>
#include <Data.h>
#include "CustomSortFilterProxyModel.h"
#include <QThread>
#include <QSystemTrayIcon>
#include <QMenu>
#include "MySQLConn.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
	void addJob();
signals:

	void runThread();
	void addToQueue(Job*);
	void enableDB(bool);
	void updateProjects(QString);
	void getUser();
	void updateJobs();
	void checkComm();

public slots:
	void closeEvent(QCloseEvent *event);
	void writeSettings(Settings s);
	Settings readSettings();
	void OpenFile(QString Filename, bool old = false, bool replace = true);
	void SaveFile(QString Filename);
	void SerializeFile(QString Filename);
	void DeserializeFile(QString Filename);
	void writeIndexEntry(QXmlStreamWriter *xmlWriter, Job *job);
	void projectsUpdated(QStringList Projects);
	void gotUser();
	void connectToServer();
	void disconnectFromServer();
	void connSuccesfull(bool);
	void updatedJobs(QList<Job> Jobs);
	int getLastFileVersion(QString FileName, QString FilePath,QString type);
	// builders
	void setupUi();
	void createTrayIcon();
	void createActions();
	void createConnections();

	// Actions
	void on_actionOpen_triggered();
	void on_actionJoin_triggered();
	void on_actionSave_triggered();
	void on_actionExport_Excel_triggered();
	void on_actionAbout_triggered();
	void on_actionPreferences_triggered();
	void on_actionImportNew_triggered();
	void on_actionImportOld_triggered();
	void on_actionExport_XML_triggered();
	void on_actionExit_triggered();
	void on_actionSalary_Paid_triggered();
	//Gui 
	void on_Company_comboBox_currentIndexChanged(QString index);
	void on_Project_comboBox_activated(int index);
	void on_Start_pushButton_clicked();
	void on_Owner_lineEdit_textChanged(const QString &text);
	void on_Stop_pushButton_clicked();
	void on_Stats_treeView_expanded(const QModelIndex &index);
	void on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
	void on_EditJob_pushButton_clicked();
	void CustomContextMenu(const QPoint &point);
	void on_Timesheet_treeView_doubleClicked(const QModelIndex &index);
	//
	void SetStatusbarMessage(QString Message);
	void closing();
	void update();
	bool validateCredentials();
	bool getCredentials();
	bool CreateDirectories();
private:
	void CreateNewTimesheet();
	bool fileExists(QString path);

	Ui::MainWindowClass ui;

	Settings settings;
	TreeModel* TSModel = Q_NULLPTR;
	TreeModel* STModel = Q_NULLPTR;
	CustomSortFilterProxyModel* STproxyModel = Q_NULLPTR;
	CustomSortFilterProxyModel* TSproxyModel = Q_NULLPTR;
	QSystemTrayIcon *trayIcon;
	QMenu* trayIconMenu;
	QAction *minimizeAction;
	QAction *startAction;
	QAction *stopAction;
	QAction *restoreAction;
	QAction *quitAction;
	QAction* deleteJob;
	Data *JobData;
	QTimer *updateTime;
	MySQLConn* DBConn;
	QThread updateService;
	int connStatus = -1;
	QMenu* contextMenu;

};
