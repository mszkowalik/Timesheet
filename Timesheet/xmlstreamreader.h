#pragma once
#include <QXmlStreamReader>
#include <QTreeWidget>
#include <QFile>
#include "Constants.h"
#include "Data.h"
#include <QDebug>
#include <QTextEdit>
#include <qdatetime.h>
#include <QLabel>
class XmlStreamReader
{
public:

	XmlStreamReader(){};

    QList<Job> readFile(const QString &fileName);

private:
    void readBookindexElement();
    void readEntryElement();
	void readFromElement();
	void readToElement();
	void readCompanyElement();
	void readProjectElement();
	void readStatusElement();
	void readCommentElement();
	void readOwnerElement();
	void readModDateElement();
	void readIDElement();
    void skipUnknownElement();

    QXmlStreamReader reader;
	Job CurrentJob;
	QList<Job> Jobs;
};
