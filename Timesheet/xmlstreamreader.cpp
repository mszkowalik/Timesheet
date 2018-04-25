#include "xmlstreamreader.h"

QList<Job> XmlStreamReader::readFile(const QString &fileName)
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
            } else {
                reader.raiseError(QObject::tr("Not a bookindex file"));
            }
        } else {
            reader.readNext();
        }
    }
    file.close();
    
	if (reader.hasError()) {
        qDebug() << "Error: Failed to parse file "
                 << qPrintable(fileName) << ": "
                 << qPrintable(reader.errorString()) ;
        return Jobs;
    } else if (file.error() != QFile::NoError) {
        qDebug() << "Error: Cannot read file " << qPrintable(fileName)
                 << ": " << qPrintable(file.errorString());
        return Jobs;
    }
    return Jobs;
}
void XmlStreamReader::readBookindexElement()
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) 
		{
            if (reader.name() == "entry") 
			{
				CurrentJob.clear();
				readEntryElement();
            } else 
			{
                skipUnknownElement();
            }
        } 
		else 
		{
            reader.readNext();
        }
    }
}
void XmlStreamReader::readEntryElement()
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
			if (CurrentJob.getModDate() == QDateTime())
				CurrentJob.setModDate(QDateTime::currentDateTime());
			Jobs.append(CurrentJob);

			reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            if (reader.name() == "entry")
            {
                readEntryElement();
            }
			else if (reader.name() == "From")
			{
				readFromElement();
			}
			else if (reader.name() == "To")
			{
				readToElement();
			}
			else if (reader.name() == "Company")
			{
				readCompanyElement();
			}
			else if (reader.name() == "Project")
			{
				readProjectElement();
			}
			else if (reader.name() == "Status")
			{
				readStatusElement();
			}
			else if (reader.name() == "Comment")
			{
				readCommentElement();
			}
			else if (reader.name() == "Owner")
			{
				readOwnerElement();
			}
			else if (reader.name() == "ID")
			{
				readIDElement();
			}
			else if (reader.name() == "ModDate")
			{
				readModDateElement();
			}

            else {
                skipUnknownElement();
            }
        } 
		else 
		{
            reader.readNext();
        }
    }
}
void XmlStreamReader::readFromElement()
{
    QString page = reader.readElementText();
	CurrentJob.setFrom(QDateTime::fromString(page, Qt::ISODate));
    if (reader.isEndElement())
        reader.readNext();
}
void XmlStreamReader::readToElement()
{
	QString page = reader.readElementText();
	CurrentJob.setTo(QDateTime::fromString(page, Qt::ISODate));
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::readCompanyElement()
{
	QString page = reader.readElementText();
	CurrentJob.setCompany(page);
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::readProjectElement()
{
	QString page = reader.readElementText();
	CurrentJob.setProject(page);
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::readStatusElement()
{
	QString page = reader.readElementText();
	CurrentJob.setStatus(page.toInt(0, 10));
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::readOwnerElement()
{
	QString page = reader.readElementText();
	CurrentJob.setOwner(page);
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::readCommentElement()
{
	QString page = reader.readElementText();
	CurrentJob.setComment(page);
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::readIDElement()
{
	QString page = reader.readElementText();
	CurrentJob.setID(page.toInt());
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::readModDateElement()
{
	QString page = reader.readElementText();
	CurrentJob.setModDate(QDateTime::fromString(page, Qt::ISODate));
	if (reader.isEndElement())
		reader.readNext();
}
void XmlStreamReader::skipUnknownElement()
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            skipUnknownElement();
        } else {
            reader.readNext();
        }
    }
}
