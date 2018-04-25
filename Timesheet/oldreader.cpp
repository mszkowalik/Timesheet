#include "oldreader.h"


QList<Job> OldReader::readFile(const QString &fileName)
{
	Jobs.clear();
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "Error: Cannot read file " << qPrintable(fileName)
			<< ": " << qPrintable(file.errorString())
			;
		return Jobs;
	}
	reader.setDevice(&file);
	reader.readNext();
	while (!reader.atEnd()) {
		if (reader.isStartElement()) {
			if (reader.name() == "bookindex") {
				readBookindexElement();
			}
			else {
				reader.raiseError(QObject::tr("Not a bookindex file"));
			}
		}
		else {
			reader.readNext();
		}
	}
	file.close();
	if (reader.hasError()) {
		qDebug() << "Error: Failed to parse file "
			<< qPrintable(fileName) << ": "
			<< qPrintable(reader.errorString());
		return Jobs;
	}
	else if (file.error() != QFile::NoError) {
		qDebug() << "Error: Cannot read file " << qPrintable(fileName)
			<< ": " << qPrintable(file.errorString());
		return Jobs;
	}
	return Jobs;
}
void OldReader::readBookindexElement()
{
	reader.readNext();
	while (!reader.atEnd()) {
		if (reader.isEndElement()) {
			reader.readNext();
			break;
		}

		if (reader.isStartElement()) {
			if (reader.name() == "entry") {
				readEntryElement();
			}
			else {
				skipUnknownElement();
			}
		}
		else {
			reader.readNext();
		}
	}
}
void OldReader::readEntryElement()
{

	QString Text = reader.attributes().value("term").toString();
	if (Text.indexOf(" to ") == -1 && Text != "Sum")
	{
		Day = QDateTime::fromString(Text, "dd MM yyyy");
	}
	else if (Text.indexOf(" to ") != -1)
	{
		CurrentJob = new Job;
		start = true;
		
		CurrentJob->setFrom(Day);
		CurrentJob->setTo(Day);

		QDateTime Time = CurrentJob->getTo();
		QTime From = QTime::fromString(Text.mid(0, 8), "hh:mm:ss");
		QTime To = QTime::fromString(Text.mid(12, 8), "hh:mm:ss");
		Time.setTime(From);
		CurrentJob->setFrom(Time);
		Time.setTime(To);
		CurrentJob->setTo(Time);
	}

	reader.readNext();

	while (!reader.atEnd()) {
		if (reader.isEndElement()) {
			if (start)
			{
				start = false;
				if (CurrentJob)
				{
					Jobs.append(*CurrentJob);
					delete CurrentJob;
				}
			}

			reader.readNext();
			break;
		}

		if (reader.isStartElement())
		{
			if (reader.name() == "entry")
			{
				readEntryElement();
			}
			else if (reader.name() == "page1")
			{
				readPage1Element();
			}
			else if (reader.name() == "page2")
			{
				readPage2Element();
			}
			else if (reader.name() == "page3")
			{
				readPage3Element();
			}
			else if (reader.name() == "page4")
			{
				readPage4Element();
			}
			else if (reader.name() == "page0")
			{
				readPage0Element();
			}
			else {
				skipUnknownElement();
			}
		}
		else {
			reader.readNext();
		}
	}
}
void OldReader::readPage1Element()
{
	QString page = reader.readElementText();
	if (reader.isEndElement())
		reader.readNext();

}
void OldReader::readPage2Element()
{
	QString page = reader.readElementText();
	if (reader.isEndElement())
		reader.readNext();
	CurrentJob->setCompany(page);
}
void OldReader::readPage3Element()
{
	QString page = reader.readElementText();
	if (reader.isEndElement())
		reader.readNext();
	CurrentJob->setProject(page);
}
void OldReader::readPage4Element()
{
	QString page = reader.readElementText();
	if (reader.isEndElement())
		reader.readNext();
	if (page == "Set")
	{
		CurrentJob->setStatus(1);
	}

	else
	{
		CurrentJob->setStatus(0);
	}


}
void OldReader::readPage0Element()
{
	QString page = reader.readElementText();
	if (reader.isEndElement())
		reader.readNext();

	CurrentJob->setComment(page);
}
void OldReader::skipUnknownElement()
{
	reader.readNext();
	while (!reader.atEnd()) {
		if (reader.isEndElement()) {
			reader.readNext();
			break;
		}

		if (reader.isStartElement()) {
			skipUnknownElement();
		}
		else {
			reader.readNext();
		}
	}
}
