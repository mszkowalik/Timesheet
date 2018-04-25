#pragma once
#include <QWidget>
class Settings
{
public:
	Settings();
	~Settings();

	QString MySQL_Server = "";
	qint64 MySQL_Port = 0;
	QString MySQL_Username = "";
	QString MySQL_Password = "";
	qint64 UpdatePeriod = 0;
	bool SyncWithServer = false;
	QString Owner = "";
	int Authority;
	int ID;
	QString Credentials;
	QString lastOpenedFile = "";
};

