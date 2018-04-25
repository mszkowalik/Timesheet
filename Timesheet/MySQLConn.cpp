#include "MySQLConn.h"
#include <qDebug>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QTextCodec>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QNetworkCookieJar>
#include <QNetworkCookie>


MySQLConn::MySQLConn(Settings* s)
{
	settings = s;
}


MySQLConn::~MySQLConn()
{
	disconnect(timer, SIGNAL(timeout()), this, SLOT(checkQueue()));
	delete timer;
	while (Queue.length())
	{
		Queue.takeLast(); // not deleting jobs, because theu point to data used in treeview
	}
}
void MySQLConn::runThread()
{
	/*nam = new QNetworkAccessManager(this);
	QNetworkCookieJar* cj = new QNetworkCookieJar(nam);
	nam->setCookieJar(cj);*/
	timer = new QTimer(this);
	//timer->setInterval(1000); //update every second;
	timer->start(10);
	//status - Statuses::Idle;
	//if (status == Statuses::Idle)
	//{
	//	status = Statuses::Busy;
	//	if (connectToDatabase(nam, CSRF)) // connect to database and gather CSRF
	//	{
	//		status = Statuses::Idle;
	//		qDebug() << CSRF;
	//	}
	//}
	connect(timer, SIGNAL(timeout()), this, SLOT(checkQueue()));
	//connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(serverResponded(QNetworkReply*)));

}
bool MySQLConn::connectToDatabase(QNetworkAccessManager* NetAccMan, QString &csrf)
{
	QString text = settings->MySQL_Server;
	text.prepend("http://");
	text.append(":");
	text.append(QString::number(settings->MySQL_Port, 10));
	QUrl url(text);
	url.setPath("/phprestsql/api.php");

	QNetworkRequest req(url);
	req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

	QByteArray postData;

	QUrlQuery q;
	q.addQueryItem("username", settings->MySQL_Username);
	q.addQueryItem("password", settings->MySQL_Password);
	postData = q.toString(QUrl::FullyEncoded).toUtf8();

	QNetworkReply* netReply = NetAccMan->post(req, postData);
	QEventLoop loop;
	connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
	loop.exec();

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	if (netReply->error() == QNetworkReply::NoError)
	{
		QString str = netReply->readAll();
		csrf = QString(str).remove(QRegExp("[^a-zA-Z\\d\\s]")).trimmed();
		//qDebug() << "No Error" << csrf;
		QUrlQuery  query;
		query.addQueryItem("csrf", csrf);
		req.setRawHeader("HTTP_X_XSRF_TOKEN", csrf.toUtf8());
		url.setQuery(query);
		req.setUrl(url);
		QNetworkReply* netReply = NetAccMan->get(req);
		connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
		loop.exec();

		if (netReply->error() == QNetworkReply::NoError)
		{
			//qDebug() << "Auth success";
			//emit(setMessage(AUTH_SUCCES));
			return true;
		}
		else
		{
			qDebug() << "Auth Err" << netReply->errorString();
			emit(setMessage(AUTH_ERROR));
			return false;
		}
	}
	else
	{
		qDebug() << "Error while connecting";
		emit(setMessage(CONN_ERROR));
		return false;
	}

	return false;

}
QUrlQuery MySQLConn::createQuery(Job job)
{
	QUrlQuery query;
	if (!job.getCompany().isEmpty())
		query.addQueryItem("filter[]", "company,eq," + job.getCompany());
	if (!job.getProject().isEmpty())
		query.addQueryItem("filter[]", "project,eq," + job.getProject());
	if (job.getFrom() != QDateTime())
		query.addQueryItem("filter[]", "start,eq," + job.getFrom().toString(MYSQLDATETIME));
	if (job.getTo() != QDateTime())
		query.addQueryItem("filter[]", "end,eq," + job.getTo().toString(MYSQLDATETIME));
	if (!job.getComment().isEmpty())
		query.addQueryItem("filter[]", "Comment,eq," + job.getComment());
	if (!job.getOwner().isEmpty())
		query.addQueryItem("filter[]", "Owner,eq," + job.getOwner());
	//if (!QString::number(job.getStatus().toInt(), 10).isEmpty())
	//	query.addQueryItem("filter[]", "Status,eq," + QString::number(job.getStatus().toInt(), 10));

	query.addQueryItem("satisfy", "all");

	return query;
}
QNetworkAccessManager * MySQLConn::createConnection(QString & CSRF)
{
	QNetworkAccessManager* NAM = new QNetworkAccessManager(this);
	QNetworkCookieJar* cj = new QNetworkCookieJar(NAM);
	NAM->setCookieJar(cj);
	connectToDatabase(NAM, CSRF);
	//qDebug() << CSRF;
	return NAM;
}
void MySQLConn::addToQueue(Job* job)
{
	// if jobs ID is invalid send it to server
	//if (job->getID() == 0 || job->getStatus().toInt() != 0)
	{
		Queue.append(job);
		checkQueue();
	}

}
void MySQLConn::checkQueue()
{
	if (Queue.isEmpty())
	{
		timer->stop(); // no data, no need to update;
	}
	else if (settings->SyncWithServer && communication == Statuses::Enabled)
	{
		if (!timer->isActive())
			timer->start(10);
		sendRequest(Queue.last());
	}

}
void MySQLConn::checkComm()
{
	QNetworkAccessManager* nam = new QNetworkAccessManager(this);
	QNetworkCookieJar* cj = new QNetworkCookieJar(nam);
	QString csrf;
	nam->setCookieJar(cj);
	emit(connSuccesfull(connectToDatabase(nam, csrf)));
	delete nam;
}
void MySQLConn::updateJobs()
{
	if (communication == Statuses::Enabled)
	{
		QNetworkAccessManager* nam = new QNetworkAccessManager(this);
		QNetworkCookieJar* cj = new QNetworkCookieJar(nam);
		QString csrf;
		nam->setCookieJar(cj);
		connectToDatabase(nam, csrf);
		//qDebug() << "CSRF: " << csrf;
		QNetworkRequest req;
		req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

		QString text = settings->MySQL_Server;
		text.prepend("//");
		text.append(":");
		text.append(QString::number(settings->MySQL_Port, 10));
		QUrl url(text);
		url.setPath("/phprestsql/api.php/" + MYSQLJobsTableName);
		url.setScheme("http");
		QDateTime upTo;
		upTo = QDateTime::currentDateTime().addDays(settings->UpdatePeriod);
		QList<Job*> Jobs;
		QUrlQuery query;
		
		for (int i = 0; i <= settings->UpdatePeriod; i++)
		{
			query.clear();
			query.addQueryItem("filter[]", "Owner,eq," + settings->MySQL_Username);

			query.addQueryItem("filter[]", "Start,cs," + QDateTime::currentDateTime().addDays(-i).toString(MYSQLDATE));

			query.addQueryItem("&satisfy=", "all");
			query.addQueryItem("csrf", csrf);

			url.setQuery(query);
			req.setUrl(url);
			//qDebug() << url.toEncoded(QUrl::FullyEncoded);

			QNetworkReply* netReply = nam->get(req);

			QEventLoop loop;
			connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
			loop.exec();

			if (netReply->error() == QNetworkReply::NoError)
			{

				QString str(netReply->readAll());
				//qDebug() << str;
				QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
				if (jsonResponse.isObject())
				{
					QJsonObject obj = jsonResponse.object();
					QList<Job*> jobs = parseJsontoJobs(obj);
					QString s = JOBS_TO_UPDATE;
					
					//qDebug() << "Jobs to update";
					Jobs.append(jobs);
				}

			}
			else
			{
				qDebug() << "Proj" << netReply->errorString();
			}
		}
		delete nam;
		QList<Job> ret;
		
		for (int i= 0; i < Jobs.length(); i++)
		{
			ret.append(*Jobs.at(i));
		}
		emit(updatedJobs(ret));
		while (Jobs.length())
		{
			delete Jobs.takeFirst();
		}
	}
	

	return;
}
void MySQLConn::sendRequest(Job* job)
{
	QString CSRF;
	QNetworkAccessManager* nam = createConnection(CSRF);
	QNetworkRequest req;

	//qDebug() << CSRF;
	req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

	QString text = "http://" + settings->MySQL_Server + ":" + QString::number(settings->MySQL_Port, 10);
	QUrl url(text);
	url.setPath("/phprestsql/api.php/" + MYSQLJobsTableName);
	url.setScheme("http");

	QUrlQuery query;
	query = createQuery(*job);
	query.addQueryItem("csrf", CSRF);

	url.setQuery(query);
	req.setUrl(url);
	//qDebug() << url.toEncoded(QUrl::FullyEncoded);

	QNetworkReply* netReply = nam->get(req);

	QEventLoop loop;
	connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
	loop.exec();

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	if (netReply->error() == QNetworkReply::NoError)
	{
		QString str(netReply->readAll());
		QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
		if (jsonResponse.isObject())
		{
			QJsonObject obj = jsonResponse.object();
			QList<Job*> jobs = parseJsontoJobs(obj);
			QString s = JOBS_TO_UPDATE;
			//qDebug() << "received :" + QString::number(jobs.length()) + " indexes";
			//qDebug() << str;
			if (jobs.isEmpty())// there is no same row, 
			{
				if (storeJob(job)); // send job to server
				{
					Queue.removeAll(job);
				}
			}
			else // there is copy of that job already
			{
				QDateTime Server, Local;
				Server = jobs.at(0)->getModDate();
				Local = job->getModDate();
				//qDebug() << "Job Exists, check which is more up-to-date";
				//qDebug() << Server;
				//qDebug() << Local;
				if (Server >= Local)
				{
					//qDebug() << "Server is more up-to-date or same";
					Job TempJob = *jobs.at(0);
					job->UpdateValues(TempJob.getFrom(), TempJob.getTo(), TempJob.getModDate(), TempJob.getCompany(), TempJob.getProject(), TempJob.getComment(), TempJob.getStatus(), TempJob.getOwner(), TempJob.getID());
					// save more updated info to local sotrage
				}
				else
				{
					//qDebug() << "Local is more up-to-date, send update to  server";
					if (modifyJob(job)); // send job to server
					{
						Queue.removeAll(job);
					}
				}

				job->setID(jobs.takeFirst()->getID());
				while (jobs.length())
				{
					delete jobs.takeFirst();
				}
				Queue.removeAll(job);
			}


			s.append(QString::number(Queue.length()));
			if (Queue.length() == 0)
				s = JOBS_UP_TO_DATE;

			emit(setMessage(s));
		}
	}
	else
	{
		qDebug() << "Error: " << netReply->errorString();
	}

	status = Statuses::Idle;
	delete nam;

}
bool MySQLConn::storeJob(Job* job)
{
	QString CSRF;
	QNetworkAccessManager* nam = createConnection(CSRF);
	QNetworkRequest req;

	//qDebug() << CSRF;
	req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

	QString text = "http://" + settings->MySQL_Server + ":" + QString::number(settings->MySQL_Port, 10);
	QUrl url(text);
	url.setPath("/phprestsql/api.php/" + MYSQLJobsTableName);
	url.setScheme("http");

	QByteArray postData;

	QUrlQuery postQuery;
	postQuery.addQueryItem("Company", job->getCompany());
	postQuery.addQueryItem("Project", job->getProject());
	postQuery.addQueryItem("Comment", job->getComment());
	postQuery.addQueryItem("Owner", job->getOwner());
	postQuery.addQueryItem("Status", QString::number(job->getStatus().toInt()));
	postQuery.addQueryItem("Start", job->getFrom().toString(Qt::ISODate));
	postQuery.addQueryItem("End", job->getTo().toString(Qt::ISODate));
	postQuery.addQueryItem("ModDate", job->getModDate().toString(Qt::ISODate));

	postData = postQuery.toString(QUrl::FullyEncoded).toUtf8();

	QUrlQuery getQuery;
	getQuery.addQueryItem("csrf", CSRF);

	url.setQuery(getQuery);
	req.setUrl(url);

	QNetworkReply* netReply = nam->post(req, postData);


	QEventLoop loop;
	connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
	loop.exec();

	if (netReply->error() == QNetworkReply::NoError)
	{
		QString str(netReply->readAll());
		job->setID(str.toInt());
		status = Statuses::Idle;
		delete nam;
		return true;
	}
	else
	{
		QString str = netReply->errorString();
		qDebug() << str;
	}

	delete nam;
	return false;

}
bool MySQLConn::modifyJob(Job* job)
{
	QString CSRF;
	QNetworkAccessManager* nam = createConnection(CSRF);

	QString text = "http://" + settings->MySQL_Server + ":" + QString::number(settings->MySQL_Port, 10);
	QUrl url(text);
	url.setPath("/phprestsql/api.php/" + MYSQLJobsTableName + "/" + QString::number(job->getID()));

	QNetworkRequest req(url);
	req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");


	QByteArray putData;
	QUrlQuery putQuery;
	//query.addQueryItem("filter[]", "company,eq,KowalikLabs");
	putQuery.addQueryItem("Company", job->getCompany());
	putQuery.addQueryItem("Project", job->getProject());
	putQuery.addQueryItem("Comment", job->getComment());
	putQuery.addQueryItem("Owner", job->getOwner());
	putQuery.addQueryItem("Status", QString::number(job->getStatus().toInt()));
	putQuery.addQueryItem("Start", job->getFrom().toString(Qt::ISODate));
	putQuery.addQueryItem("End", job->getTo().toString(Qt::ISODate));
	putQuery.addQueryItem("ModDate", job->getModDate().toString(Qt::ISODate));

	putData = putQuery.toString(QUrl::FullyEncoded).toUtf8();

	QUrlQuery getQuery;
	getQuery.addQueryItem("csrf", CSRF);


	url.setQuery(getQuery);

	QNetworkReply* netReply = nam->put(req, putData);

	QEventLoop loop;
	connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
	loop.exec();

	if (netReply->error() == QNetworkReply::NoError)
	{
		QString str(netReply->readAll());
		status = Statuses::Idle;
		delete nam;
		return true;
	}
	delete nam;
	return false;

}
QList<Job*> MySQLConn::parseJsontoJobs(QJsonObject Obj)
{
	/*
	-Jobs
		-columns
		-records
	*/
	QList<Job*> Jobs;
	QJsonObject jobs = Obj.value(MYSQLJobsTableName).toObject();
	if (!jobs.isEmpty())
	{
		QJsonArray records = jobs.value("records").toArray();
		QJsonArray columns = jobs.value("columns").toArray();
		//qDebug() << columns;
		if (!columns.isEmpty())
		{
			QStringList List;
			foreach(QVariant s, columns.toVariantList()) {
				List << s.toString();
			}

			if (!records.isEmpty())
			{
				foreach(QJsonValue JobArray, records)
				{
					QJsonArray Array = JobArray.toArray();
					Job* job = new Job();
					QString temp;
					int index;
					index = List.indexOf("ID");
					if (index >= 0) // if there is ID, 
					{
						job->setID(Array.at(index).toInt());
					}
					index = List.indexOf("Start");
					if (index >= 0)
					{
						job->setFrom(QDateTime::fromString(Array.at(index).toVariant().toString(), Qt::ISODate));
					}
					index = List.indexOf("End");
					if (index >= 0)
					{
						job->setTo(QDateTime::fromString(Array.at(index).toVariant().toString(), Qt::ISODate));
					}
					index = List.indexOf("Company");
					if (index >= 0)
					{
						job->setCompany(Array.at(index).toString());
					}
					index = List.indexOf("Project");
					if (index >= 0)
					{
						job->setProject(Array.at(index).toString());
					}
					index = List.indexOf("Status");
					if (index >= 0)
					{
						job->setStatus(Array.at(index).toInt());
					}
					index = List.indexOf("Comment");
					if (index >= 0)
					{
						job->setComment(Array.at(index).toString());
					}
					index = List.indexOf("Owner");
					if (index >= 0)
					{
						job->setOwner(Array.at(index).toString());
					}
					index = List.indexOf("ModDate");
					if (index >= 0)
					{
						job->setModDate(QDateTime::fromString(Array.at(index).toVariant().toString(), Qt::ISODate));
					}
					Jobs.append(job);
				}
			}
		}

	}
	else
	{
	}
	return Jobs;

}

void MySQLConn::updateProjects(QString Company)
{
	if (communication == Statuses::Enabled)
	{
		QNetworkAccessManager* nam = new QNetworkAccessManager(this);
		QNetworkCookieJar* cj = new QNetworkCookieJar(nam);
		QString csrf;
		nam->setCookieJar(cj);
		connectToDatabase(nam, csrf);
		//qDebug() << "CSRF: " << csrf;
		QNetworkRequest req;
		req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

		QString text = settings->MySQL_Server;
		text.prepend("//");
		text.append(":");
		text.append(QString::number(settings->MySQL_Port, 10));
		QUrl url(text);
		url.setPath("/phprestsql/api.php/" + MYSQLJobsTableName);
		url.setScheme("http");

		QUrlQuery query;
		query.addQueryItem("filter[]", "company,eq," + Company);
		query.addQueryItem("columns", "Project");
		query.addQueryItem("csrf", csrf);

		url.setQuery(query);
		req.setUrl(url);
		qDebug() << url.toEncoded(QUrl::FullyEncoded);

		QNetworkReply* netReply = nam->get(req);

		QEventLoop loop;
		connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
		loop.exec();

		if (netReply->error() == QNetworkReply::NoError)
		{
			QString str(netReply->readAll());
			qDebug() << str;
			QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
			QJsonObject Projects = jsonResponse.object().value(MYSQLJobsTableName).toObject();
			QStringList ProjectsList;
			if (!Projects.isEmpty())
			{
				QJsonArray records = Projects.value("records").toArray();
				QJsonArray columns = Projects.value("columns").toArray();
				//qDebug() << columns;
				if (!columns.isEmpty())
				{
					QStringList List;
					foreach(QVariant s, columns.toVariantList()) {
						List << s.toString();
					}

					if (!records.isEmpty())
					{
						foreach(QJsonValue ProjArray, records)
						{
							QJsonArray Array = ProjArray.toArray();
							int index;
							index = List.indexOf("Project");
							if (index >= 0) // if there is ID, 
							{
								ProjectsList.append(Array.at(index).toString());

							}

						}
					}
				}

			}
			emit(projectsUpdated(ProjectsList));
		}
		else
		{
			qDebug() << "Proj" << netReply->errorString();
		}
		delete nam;
	}
	return;
}
void MySQLConn::getUser()
{
	if (communication == Statuses::Enabled)
	{
		QNetworkAccessManager* nam = new QNetworkAccessManager(this);
		QNetworkCookieJar* cj = new QNetworkCookieJar(nam);
		QString csrf;
		nam->setCookieJar(cj);
		connectToDatabase(nam, csrf);
		//qDebug() << "CSRF: " << csrf;
		QNetworkRequest req;
		req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

		QString text = settings->MySQL_Server;
		text.prepend("//");
		text.append(":");
		text.append(QString::number(settings->MySQL_Port, 10));
		QUrl url(text);
		url.setPath("/phprestsql/api.php/" + MYSQLUsersTableName);
		url.setScheme("http");

		QUrlQuery query;
		query.addQueryItem("filter[]", "username,eq," + settings->MySQL_Username);
		query.addQueryItem("exclude", "password");
		query.addQueryItem("csrf", csrf);

		url.setQuery(query);
		req.setUrl(url);
		//qDebug() << url.toEncoded(QUrl::FullyEncoded);

		QNetworkReply* netReply = nam->get(req);

		QEventLoop loop;
		connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));// wait until reply
		loop.exec();

		if (netReply->error() == QNetworkReply::NoError)
		{
			QString str(netReply->readAll());
			//qDebug() << str;
			QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
			QJsonObject Users = jsonResponse.object().value(MYSQLUsersTableName).toObject();
			if (!Users.isEmpty())
			{
				QJsonArray records = Users.value("records").toArray();
				QJsonArray columns = Users.value("columns").toArray();
				//qDebug() << columns;
				if (!columns.isEmpty())
				{
					QStringList List;
					foreach(QVariant s, columns.toVariantList()) {
						List << s.toString();
					}
					if (!records.isEmpty())
					{
						QJsonValue val = records.at(0);
						QJsonArray Array = val.toArray();
						int index;
						index = List.indexOf("ID");
						if (index >= 0) // if there is ID, 
						{
							settings->ID = Array.at(index).toInt();
						}
						index = List.indexOf("credentials");
						if (index >= 0) // if there is ID, 
						{
							settings->Credentials = Array.at(index).toString();
						}
						index = List.indexOf("authority");
						if (index >= 0) // if there is ID, 
						{
							settings->Authority = Array.at(index).toInt();
						}
					}
				}
			}
			//qDebug() << u.Username;

			emit(gotUser());
		}
		else
		{
			qDebug() << "User" << netReply->errorString();
		}
		delete nam;
	}
	return;
}