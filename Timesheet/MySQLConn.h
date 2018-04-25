#pragma once
#include <QObject>
#include <QTimer>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "Job.h"
#include "Project.h"
#include "Settings.h"

enum Statuses
{
	Busy = 0,
	Idle,
	Enabled,
	Disabled
};


class MySQLConn : public QObject
{
	Q_OBJECT
public:

	MySQLConn(Settings* s = new Settings());
	~MySQLConn();

signals:
	void setMessage(QString Message);
	void projectsUpdated(QStringList Projects);
	void gotUser();
	void connSuccesfull(bool);
	void updatedJobs(QList<Job>);
public slots :
	void getUser();
	void runThread();
	void setEnabled(bool enabled) { if (enabled) communication = Statuses::Enabled; else communication = Statuses::Disabled; };
	void addToQueue(Job* job);
	void checkQueue();
	void updateProjects(QString Company);
	void checkComm();
	void updateJobs();

	private slots:

private:
	void sendRequest(Job* job);
	QNetworkAccessManager* createConnection(QString&CSRF);
	bool storeJob(Job* job); 
	bool modifyJob(Job* job);
	bool connectToDatabase(QNetworkAccessManager* NetAccMan, QString &csrf);
	QList<Job*> parseJsontoJobs(QJsonObject Obj);
	QUrlQuery createQuery(Job job);


	QList<Job*> Queue;
	QTimer* timer;
	int status = Statuses::Idle;
	int communication = Statuses::Disabled;
	/*
	QNetworkAccessManager* nam;*/
	Settings* settings;
	//QString CSRF;
};

