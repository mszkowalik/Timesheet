#include "MainWindow.h"
#include "CustomDelegate.h"
#include "TimesheetWizard.h"
#include <QWindowStateChangeEvent>
#include <QCoreApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QWizard>
#include "EditJob.h"
#include "Login.h"
#include "SalaryPaid.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setupUi();

	setWindowTitle(PROGRAM_NAME);
	setWindowIcon(QIcon(":/MainWindow/Timesheet"));
	ui.Company_comboBox->lineEdit()->setPlaceholderText(COMPANY);
	ui.Project_comboBox->lineEdit()->setPlaceholderText(PROJECT);
	CreateDirectories();

	contextMenu = new QMenu(ui.Timesheet_treeView);

	updateTime = new QTimer();
	updateTime->setInterval(100);
	updateTime->start();
	settings = readSettings();

	createActions();
	createTrayIcon();

	JobData = new Data(&settings, TSModel, STModel);
	


	if (settings.lastOpenedFile.isEmpty())
	{
		#ifdef PRODUCTION
		QString fileName = QFileDialog::getOpenFileName(this,
			OPEN, DataDirectory + "/", DAT_FILES);
		#else
		QString fileName = QFileDialog::getOpenFileName(this,
			OPEN, DataDirectory + "/", TIMESHEET_FILES);
		#endif
		if (fileName.isEmpty())
		{
			CreateNewTimesheet();
		}
		else
#ifdef PRODUCTION
			settings.lastOpenedFile = fileName;
			DeserializeFile(fileName);
		#else
		#endif

	}
	else
	{
		if (fileExists(settings.lastOpenedFile))
		{
			#ifdef PRODUCTION
			DeserializeFile(settings.lastOpenedFile);
			#else
			OpenFile(settings.lastOpenedFile);// thou it will be not sent to server
			#endif
		}
		else
		{
			#ifdef PRODUCTION
						QString fileName = QFileDialog::getOpenFileName(this,
							OPEN, DataDirectory + "/", DAT_FILES);
			#else
						QString fileName = QFileDialog::getOpenFileName(this,
							OPEN, DataDirectory + "/", TIMESHEET_FILES);
			#endif
			if (fileName.isEmpty())
			{
				CreateNewTimesheet();
			}
			else
			#ifdef PRODUCTION
				DeserializeFile(fileName);
			#else
				OpenFile(fileName);// thou it will be not sent to server
			#endif
		}

	}

	DBConn = new MySQLConn(&settings);
	DBConn->moveToThread(&updateService);
	updateService.start();

	createConnections();

	emit(runThread());



	if (settings.SyncWithServer)
	{
		do
		{
			if (!getCredentials())
			{
				settings.SyncWithServer = false;
				disconnectFromServer();
				break;
			}
		} while (!validateCredentials());
	}
	else
	{
		ui.Owner_lineEdit->setText(settings.Owner);
	}

	//ui.Timesheet_treeView->model()->sort(0, Qt::AscendingOrder);
	//ui.Timesheet_treeView->model()->sort(0, Qt::DescendingOrder);

}

MainWindow::~MainWindow()
{

	updateService.quit();
	updateService.wait();
	//delete DBConn;// updateService will take care
}
void MainWindow::createActions()
{
	minimizeAction = new QAction(MINIMIZE, this);
	connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));


	restoreAction = new QAction(RESTORE, this);
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

	startAction = new QAction(START, this);
	connect(startAction, SIGNAL(triggered()), this, SLOT(on_Start_pushButton_clicked()));

	stopAction = new QAction(STOP, this);
	connect(stopAction, SIGNAL(triggered()), this, SLOT(on_Stop_pushButton_clicked()));

	quitAction = new QAction(QUIT, this);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));


	deleteJob = new QAction(DELETE_LANG, this);
	contextMenu->addAction(deleteJob);

}
void MainWindow::createConnections()
{
	QObject::connect(this, SIGNAL(runThread()), DBConn, SLOT(runThread()));
	QObject::connect(this, SIGNAL(updateProjects(QString)), DBConn, SLOT(updateProjects(QString)));
	QObject::connect(DBConn, SIGNAL(projectsUpdated(QStringList)), this, SLOT(projectsUpdated(QStringList)));
	QObject::connect(DBConn, SIGNAL(setMessage(QString)), this, SLOT(SetStatusbarMessage(QString)));
	QObject::connect(DBConn, SIGNAL(gotUser()), this, SLOT(gotUser()));
	QObject::connect(this, SIGNAL(checkComm()), DBConn, SLOT(checkComm()));
	QObject::connect(DBConn, SIGNAL(connSuccesfull(bool)), this, SLOT(connSuccesfull(bool)));
	QObject::connect(JobData, SIGNAL(addToQueue(Job*)), DBConn, SLOT(addToQueue(Job*)));
	QObject::connect(this, SIGNAL(getUser()), DBConn, SLOT(getUser()));
	QObject::connect(this, SIGNAL(enableDB(bool)), DBConn, SLOT(setEnabled(bool)));
	QObject::connect(this, SIGNAL(updateJobs()), DBConn, SLOT(updateJobs()));
	QObject::connect(updateTime, SIGNAL(timeout()), this, SLOT(update()));
	QObject::connect(DBConn, SIGNAL(updatedJobs(QList<Job>)), this, SLOT(updatedJobs(QList<Job>)));
	QObject::connect(ui.Stats_treeView, SIGNAL(expanded(QModelIndex)), this, SLOT(on_Stats_treeView_expanded(QModelIndex)));
	QObject::connect(ui.Timesheet_treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(CustomContextMenu(QPoint)));
}
void MainWindow::createTrayIcon()
{
	trayIconMenu = new QMenu(this);
	trayIconMenu->insertAction(minimizeAction, startAction);
	trayIconMenu->addAction(minimizeAction);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(QIcon(":/MainWindow/Timesheet.ico"));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_trayIcon_activated(QSystemTrayIcon::ActivationReason)));
	trayIcon->setVisible(true);
}

void MainWindow::on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::DoubleClick)
		showNormal();
}
void MainWindow::addJob()
{
	Job* job = new Job(ui.Start_dateEdit->dateTime(), ui.Stop_dateEdit->dateTime(), QDateTime::currentDateTime(),
		ui.Company_comboBox->currentText(), ui.Project_comboBox->currentText(), "", 0, settings.MySQL_Username, 0);

	JobData->addJob(job);
	QString CompanyName = ui.Company_comboBox->currentText();

	ui.Company_comboBox->clear();
	ui.Company_comboBox->addItems(JobData->getCompaniesList());
	ui.Company_comboBox->setCurrentText(CompanyName);


	if (settings.SyncWithServer)
		emit(updateProjects(ui.Company_comboBox->currentText()));

	ui.Timesheet_treeView->expand(TSModel->index(0, 0));


}
void MainWindow::closeEvent(QCloseEvent *event) // in fact because you can't close the window by clicking on X, this event is being ignored
{
	this->hide();
	event->ignore();
	//also minimize to tray// you can only close app by File->close;
}

void MainWindow::update()
{
	if (ui.Stop_pushButton->isEnabled())
	{
		TimeSpan ts = TimeSpan(ui.Start_dateEdit->dateTime().secsTo(QDateTime::currentDateTime()));
		ui.workingHours_lineEdit->setText(ts.toStringSec());
	}
}
bool MainWindow::validateCredentials()
{
	connStatus = -1;
	emit(checkComm());
	setEnabled(false);
	QMessageBox msgBox;
	msgBox.setText(WAITING_FOR_CONNECTION);
	msgBox.setDefaultButton(QMessageBox::NoButton);
	msgBox.open();
	SetStatusbarMessage(WAITING_FOR_CONNECTION);
	while (connStatus == -1)
	{
		qApp->processEvents();
	}
	setEnabled(true);
	if (connStatus == 1)
	{
		SetStatusbarMessage(CONNECTION_SUCCESSFULL);
		msgBox.setText(CONNECTION_SUCCESSFULL);
		emit(enableDB(true));
		connectToServer();
	}
	else if (connStatus == 0)
	{
		SetStatusbarMessage(CONNECTION_FAILED);
		msgBox.setText(CONNECTION_FAILED);
	}
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.exec();
	if (connStatus == 1)
		return true;
	else
		return false;
}
bool MainWindow::getCredentials()
{
	Login l;
	l.setLogin(settings.MySQL_Username);
	l.exec();
	if (l.exitClick)
	{
		settings.MySQL_Password = l.getPassword();
		settings.MySQL_Username = l.getLogin();
	}

	return l.exitClick;
}
bool MainWindow::CreateDirectories()
{
	if (!QDir(DataDirectory).exists())
	{
		QDir().mkdir(DataDirectory);
	}
	if (!QDir(BackupDirectory + "/").exists())
	{
		QDir().mkdir(BackupDirectory + "/");
	}

	return true;
}
void MainWindow::CreateNewTimesheet()
{

	TimesheetWizard wizard;
	wizard.exec();
	settings = wizard.getSettings();
	ui.Owner_lineEdit->setText(settings.Owner);

}
bool MainWindow::fileExists(QString path)
{
	QFileInfo check_file(path);
	// check if file exists and if yes: Is it really a file and no directory?
	if (check_file.exists() && check_file.isFile()) {
		return true;
	}
	else {
		return false;
	}
	return false;
}
void MainWindow::closing()
{
	writeSettings(settings);
	#ifdef PRODUCTION
		SerializeFile(settings.lastOpenedFile);
		SerializeFile(QDateTime::currentDateTime().toString(FILEDATETIMEFORMAT).append(".dat").prepend(BackupDirectory + "/"));
	#else
		SaveFile(settings.lastOpenedFile);// thou it will be not sent to server
	#endif
	ui.statusBar->showMessage(FILE_SAVED);
	trayIcon->hide();
}
Settings MainWindow::readSettings()
{
	Settings s;
	QSettings set("file.ini", QSettings::IniFormat);

	set.beginGroup("MySQL");

	//s.MySQL_Password = set.value("Password", s.MySQL_Password).toString();
	s.MySQL_Username = set.value("Username", s.MySQL_Username).toString();
	s.MySQL_Server = set.value("Server Adress", s.MySQL_Server).toString();
	s.MySQL_Port = set.value("Port", s.MySQL_Port).toInt();
	s.SyncWithServer = set.value("SyncWithServer", s.SyncWithServer).toBool();
	set.endGroup();
	s.UpdatePeriod = set.value("UpdatePeriod", s.UpdatePeriod).toInt();
	s.Owner = set.value("Owner", s.Owner).toString();
	s.lastOpenedFile = set.value("lastOpenedFile", s.lastOpenedFile).toString();

	return s;
}
void MainWindow::writeSettings(Settings s)
{
	QSettings settings("file.ini", QSettings::IniFormat);
	settings.beginGroup("MySQL");
	settings.setValue("Server Adress", s.MySQL_Server);
	settings.setValue("Port", s.MySQL_Port);
	settings.setValue("Username", s.MySQL_Username);
	//settings.setValue("Password", s.MySQL_Password);
	settings.setValue("SyncWithServer", s.SyncWithServer);
	settings.endGroup();
	settings.setValue("UpdatePeriod", s.UpdatePeriod);
	settings.setValue("Owner", s.Owner);
	settings.setValue("lastOpenedFile", s.lastOpenedFile);

}

void MainWindow::on_actionPreferences_triggered()
{
	SettingsDialog Dialog(settings);
	Dialog.exec();

	settings = Dialog.settings;

	if (settings.SyncWithServer&& connStatus != 1)
	{
		do
		{
			if (!getCredentials())
			{
				settings.SyncWithServer = false;
				disconnectFromServer();
				break;
			}
		} while (!validateCredentials());
	}
	if (!settings.SyncWithServer)
	{
		disconnectFromServer();
	}
}
void MainWindow::on_actionOpen_triggered()
{
	#ifdef PRODUCTION
		QString fileName = QFileDialog::getOpenFileName(this,
			OPEN, DataDirectory + "/", DAT_FILES);
		if(!fileName.isEmpty())
			DeserializeFile(fileName);
	#else
		QString fileName = QFileDialog::getOpenFileName(this,
			OPEN, DataDirectory + "/", TIMESHEET_FILES);
		if(!fileName.isEmpty())
			OpenFile(fileName);// thou it will be not sent to server
	#endif
	settings.lastOpenedFile = fileName;
}
void MainWindow::on_actionSave_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		SAVE, DataDirectory + "/", DAT_FILES);
	SerializeFile(fileName);
}
void MainWindow::on_actionExport_Excel_triggered()
{

}
void MainWindow::on_actionExport_XML_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		EXPORT_XML, DataDirectory + "/", TIMESHEET_FILES);
	SaveFile(fileName);
}
void MainWindow::on_actionAbout_triggered()
{

}
void MainWindow::on_actionJoin_triggered()
{
	JobData->joinJobs(60);//max minute apart

}
void MainWindow::on_actionImportOld_triggered()
{

	SetStatusbarMessage(IMPORTING_FILE);
	QString filename = QFileDialog::getOpenFileName(this,
		OPEN, DataDirectory + "/", TIMESHEET_FILES);
	QMessageBox msgBox;
	msgBox.setText(ABOUT_TO_IMPORT);
	msgBox.setInformativeText(DO_REPLACE_JOBS);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);

	if (msgBox.exec() == QMessageBox::Yes)
		OpenFile(filename, true, true);
	else
		OpenFile(filename, true, false);

	SetStatusbarMessage(FILE_IMPORTED);
}
void MainWindow::on_actionImportNew_triggered()
{
	SetStatusbarMessage(IMPORTING_FILE);
	QString filename = QFileDialog::getOpenFileName(this,
		OPEN, DataDirectory + "/", DAT_FILES);
	QMessageBox msgBox;
	msgBox.setText(ABOUT_TO_IMPORT);
	msgBox.setInformativeText(DO_REPLACE_JOBS);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);

	if (msgBox.exec() == QMessageBox::Yes)
		OpenFile(filename, true, true);
	else
		OpenFile(filename, true, false);
	SetStatusbarMessage(FILE_IMPORTED);

}

void MainWindow::on_Start_pushButton_clicked()
{
	ui.Start_dateEdit->setDateTime(QDateTime::currentDateTime());
	ui.Stop_pushButton->setEnabled(true);
	ui.Start_pushButton->setEnabled(false);

	trayIconMenu->insertAction(minimizeAction, stopAction);
	trayIconMenu->removeAction(startAction);
}
void MainWindow::on_Stop_pushButton_clicked()
{

	ui.Stop_dateEdit->setDateTime(QDateTime::currentDateTime());

	addJob();


	ui.Stop_pushButton->setEnabled(false);
	ui.Start_pushButton->setEnabled(true);

	trayIconMenu->insertAction(minimizeAction, startAction);
	trayIconMenu->removeAction(stopAction);


}
void MainWindow::on_Company_comboBox_currentIndexChanged(QString index)
{
	//int ind = JobData->companyIndex(index);
	QStringList projects = JobData->getProjectsList(index);
	projects.removeDuplicates();
	projects.sort();
	ui.Project_comboBox->clear();
	ui.Project_comboBox->addItems(projects);
	if (settings.SyncWithServer)
		emit(updateProjects(index));

}
void MainWindow::on_Project_comboBox_activated(int index)
{
	qDebug() << "Here";
	if (settings.SyncWithServer)
		emit(updateProjects(ui.Company_comboBox->currentText()));
}
void MainWindow::on_actionExit_triggered()
{
	qApp->instance()->quit();
}
void MainWindow::on_actionSalary_Paid_triggered()
{
	qDebug() << "Salary Paid";
	SalaryPaid salary(JobData, this);
	salary.exec();
	JobData->updateStatistics();
}
void MainWindow::on_Owner_lineEdit_textChanged(const QString &text)
{
	settings.Owner = text;;
}
void MainWindow::on_EditJob_pushButton_clicked()
{
	QModelIndex index = ui.Timesheet_treeView->currentIndex();
	if (index.isValid())
	{
		
		QVariant received = index.data(600);
		Job*job = qvariant_cast<Job*>(received);

		EditJob * Edit = new EditJob(job, JobData, this);
		Edit->exec();


	}
}
void MainWindow::on_Timesheet_treeView_doubleClicked(const QModelIndex & index)
{
	if (index.isValid() && index.column() == 0)
	{

		QVariant received = index.data(600);
		if (received.canConvert<Job*>())
		{
			Job*job = qvariant_cast<Job*>(received);
			EditJob * Edit = new EditJob(job, JobData, this);
			Edit->exec();
		}
	}
}
// File Handling
void MainWindow::SaveFile(QString Filename)
{
	SetStatusbarMessage(SAVING_FILE);
	QFile file(Filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		qDebug() << "Error: Cannot write file "
			<< qPrintable(Filename) << ": "
			<< qPrintable(file.errorString());
	}

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement("bookindex");
	QList<Job*> save = JobData->getJobsToSave(settings.UpdatePeriod);


	for (int i = 0; i < save.length(); i++)
	{
		writeIndexEntry(&xmlWriter, save.at(i));
	}

	xmlWriter.writeEndDocument();
	file.close();
	if (file.error()) {
		qDebug() << "Error: Cannot write file "
			<< qPrintable(Filename) << ": "
			<< qPrintable(file.errorString());
		SetStatusbarMessage(ERROR_WHILE_SAVING);
	}
	else
		SetStatusbarMessage(FILE_SAVED);

}
void MainWindow::SerializeFile(QString Filename)
{
	SetStatusbarMessage(SAVING_FILE);
	QFile file(Filename);
	if (!file.open(QFile::ReadWrite)) {
		qDebug() << "Error: Cannot write file "
			<< qPrintable(Filename) << ": "
			<< qPrintable(file.errorString());
		SetStatusbarMessage(ERROR_WHILE_OPENING);

	}

	QDataStream out(&file);
	QList<Job*> save = JobData->getJobsToSave(settings.UpdatePeriod);
	Job job;
	for (int i = 0; i < save.length(); i++)
	{
		job = *save.at(i);
		out << job;
	}

	file.close();
	if (file.error()) {
		qDebug() << "Error: Cannot write file "
			<< qPrintable(Filename) << ": "
			<< qPrintable(file.errorString());
		SetStatusbarMessage(ERROR_WHILE_SAVING);
	}
	else
		SetStatusbarMessage(FILE_SAVED);
}
void MainWindow::DeserializeFile(QString Filename)
{
	SetStatusbarMessage(OPENING_FILE);
	QFile file(Filename);
	if (!file.open(QFile::ReadWrite)) {
		qDebug() << "Error: Cannot write file "
			<< qPrintable(Filename) << ": "
			<< qPrintable(file.errorString());
		SetStatusbarMessage(ERROR_WHILE_OPENING);

	}
	QDataStream in(&file);
	Job* j;
	TSModel->layoutAboutToBeChanged();
	JobData->clear(); // deletes alse all data from TeeView

	while (!in.atEnd())
	{
		j = new Job();
		in >> *j;
		JobData->addJob(j);
	}
	TSModel->layoutChanged();
	ui.Timesheet_treeView->expand(TSModel->index(0, 0));
	
	ui.Company_comboBox->clear();
	ui.Company_comboBox->addItems(JobData->getCompaniesList());
	if (settings.SyncWithServer)
		emit(updateProjects(ui.Company_comboBox->currentText()));
	ui.Timesheet_treeView->expand(TSModel->index(0, 0));


	if (file.error()) {
		qDebug() << "Error: Cannot write file "
			<< qPrintable(Filename) << ": "
			<< qPrintable(file.errorString());
		SetStatusbarMessage(ERROR_WHILE_OPENING);
	}
	else
		SetStatusbarMessage(FILE_OPENED);

}
void MainWindow::writeIndexEntry(QXmlStreamWriter *xmlWriter, Job *job)
{
	xmlWriter->writeStartElement("entry");

	xmlWriter->writeTextElement("From", job->getFrom().toString(Qt::ISODate));
	xmlWriter->writeTextElement("To", job->getTo().toString(Qt::ISODate));
	xmlWriter->writeTextElement("Company", job->getCompany());
	xmlWriter->writeTextElement("Project", job->getProject());
	xmlWriter->writeTextElement("Status", QString::number(job->getStatus().toInt()));
	xmlWriter->writeTextElement("Comment", job->getComment());
	xmlWriter->writeTextElement("Owner", job->getOwner());
	xmlWriter->writeTextElement("ModDate", job->getModDate().toString(Qt::ISODate));
	xmlWriter->writeTextElement("ID", QString::number(job->getID()));

	xmlWriter->writeEndElement();
}
void MainWindow::OpenFile(QString Filename, bool old, bool replace)
{
	if (replace)
		JobData->clear(); // deletes alse all data from TeeView

	if (old)
	{
		OldReader oldreader;
		TSModel->layoutAboutToBeChanged();
		QList<Job> jobs;
		jobs = oldreader.readFile(Filename);
		for (int i = 0; i < jobs.length(); i++)
		{
			JobData->addJob(jobs.at(i));
		}
		TSModel->layoutChanged();
		ui.Timesheet_treeView->expand(TSModel->index(0, 0));

		ui.Company_comboBox->clear();
		ui.Company_comboBox->addItems(JobData->getCompaniesList());

		if (settings.SyncWithServer)
			emit(updateProjects(ui.Company_comboBox->currentText()));
		ui.Timesheet_treeView->expand(TSModel->index(0, 0));
	}
	else
	{
		XmlStreamReader reader;

		TSModel->layoutAboutToBeChanged();
		//reader.readFile(Filename);
		QList<Job> jobs;
		jobs = reader.readFile(Filename);
		for (int i = 0; i < jobs.length(); i++)
		{
			JobData->addJob(jobs.at(i));
		}
		TSModel->layoutChanged();
		ui.Timesheet_treeView->expand(TSModel->index(0, 0));

		ui.Company_comboBox->clear();
		ui.Company_comboBox->addItems(JobData->getCompaniesList());
		if (settings.SyncWithServer)
			emit(updateProjects(ui.Company_comboBox->currentText()));
		ui.Timesheet_treeView->expand(TSModel->index(0, 0));
		qDebug() << JobData->jobsCount();
	}
}

void MainWindow::SetStatusbarMessage(QString Message)
{
	ui.statusBar->showMessage(Message);
}
void MainWindow::on_Stats_treeView_expanded(const QModelIndex &index)
{
	//qDebug() << "Expanded";
	//ui.Stats_treeView->resizeColumnToContents(index.column());
}
void MainWindow::setupUi()
{
	QTreeView* TStreeView = ui.Timesheet_treeView;
	QTreeView* STtreeView = ui.Stats_treeView;

	TSModel = new TreeModel(this, 5);
	STModel = new TreeModel(this, 2);

	TSproxyModel = new CustomSortFilterProxyModel(this);
	STproxyModel = new CustomSortFilterProxyModel(this);

	TSproxyModel->setSourceModel(TSModel);
	STproxyModel->setSourceModel(STModel);

	TStreeView->setModel(TSproxyModel);
	TStreeView->setContextMenuPolicy(Qt::CustomContextMenu);
	TStreeView->setSortingEnabled(true);

	STtreeView->setModel(STproxyModel);

	TStreeView->setColumnWidth(0, 140);
	TStreeView->setColumnWidth(1, 70);
	TStreeView->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	TStreeView->header()->setSectionResizeMode(3, QHeaderView::Stretch);
	TStreeView->setColumnWidth(4, 70);
	TStreeView->header()->setStretchLastSection(false);

	STtreeView->header()->setStretchLastSection(false);
	STtreeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
	TStreeView->setItemDelegate(new CustomDelegate);
	STtreeView->setItemDelegate(new CustomDelegate);

}
void MainWindow::projectsUpdated(QStringList Projects)
{
	SetStatusbarMessage(PROJECTS_UPDATED);
	Projects.removeDuplicates();
	for (int i = 0; i < ui.Project_comboBox->count(); i++)
	{
		Projects.append(ui.Project_comboBox->itemText(i));
	}
	Projects.removeDuplicates();
	Projects.sort();

	ui.Project_comboBox->clear();
	ui.Project_comboBox->addItems(Projects);

}
void MainWindow::gotUser()
{
	qDebug() << "gotUser()";
	ui.Owner_lineEdit->setText(settings.MySQL_Username);

}
void MainWindow::connectToServer()
{
	ui.Owner_lineEdit->setEnabled(false);
	emit(getUser());
	emit(updateProjects(ui.Company_comboBox->currentText()));
	emit(updateJobs());
}
void MainWindow::disconnectFromServer()
{
	emit(enableDB(false));
	connStatus = -1;
	ui.Owner_lineEdit->setText(settings.MySQL_Username);
	ui.Owner_lineEdit->setEnabled(true);
}
void MainWindow::connSuccesfull(bool status)
{
	if (status)
		connStatus = 1;
	else
		connStatus = 0;

}
void MainWindow::updatedJobs(QList<Job> Jobs)
{
	qDebug() << Jobs;
}

int MainWindow::getLastFileVersion(QString FileName, QString FilePath, QString type)
{
	QDir dir;
	dir.setPath(FilePath);
	qDebug() << dir.absolutePath();
	QStringList NameFilters;
	NameFilters << FileName + "_*." + type;
	QStringList list = dir.entryList(NameFilters);

	for (int i = 0; i < list.length(); i++)
	{
		list[i] = list[i].mid(list[i].lastIndexOf("_") + 1, list[i].lastIndexOf(".") - list[i].lastIndexOf("_") - 1);
	}
	list.sort(); // ascending;
	qDebug() << list;
	if (list.isEmpty())
		return -1;
	else
		return list.last().toInt();
}
void MainWindow::CustomContextMenu(const QPoint &point)
{
	QModelIndex index = ui.Timesheet_treeView->indexAt(point);
	if (index.isValid() && index.column() == 0)
	{

		QVariant received = index.data(600);
		if (received.canConvert<Job*>())
		{
			Job*job = qvariant_cast<Job*>(received);
			QAction* action = contextMenu->exec(ui.Timesheet_treeView->mapToGlobal(point));
			if (action == deleteJob)
			{
				JobData->removeJob(job);
				
			}

		}
	}
}