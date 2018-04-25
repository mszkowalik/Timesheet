#pragma once

#include <QXmlStreamReader>
#include <QTreeWidget>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <Job.h>
#include <QTextEdit>
#include <QLabel>
#include "Constants.h"
#include "Data.h"

class OldReader
{
public:
	OldReader(){};
	~OldReader(){};

	QList<Job> readFile(const QString &fileName);

private:
	void readBookindexElement();
	void readEntryElement();
	void readPage1Element();
	void readPage2Element();
	void readPage3Element();
	void readPage4Element();
	void readPage0Element();
	void skipUnknownElement();

	Job* CurrentJob = Q_NULLPTR;
	QList<Job> Jobs;
	QXmlStreamReader reader;
	bool start = false;
	QDateTime Day;
};
