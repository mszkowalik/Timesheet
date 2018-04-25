#pragma once
#include "qstring.h"
#include < QApplication.h>

const QString MYSQLDATETIME("yyyy-MM-dd HH:mm:ss"); //not used anymore - from now on using Qt::ISODate
const QString MYSQLDATE("yyyy-MM-dd");
const QString DATETIMEFORMAT("dd MM yyyy hh:mm:ss");
const QString DATEFORMAT("dd MM yy ddd");
const QString TIMEFORMAT("hh:mm:ss");
const QString TIMEFORMATSHORT("hh:mm");
const QString FILEDATETIMEFORMAT("yyyy-MM-dd_HH_mm_ss");
const QString MYSQLJobsTableName("jobsproduction");
const QString MYSQLUsersTableName("users");
const QString DataDirectory("Data");
const QString BackupDirectory("Data/Backup");

#define OPENING_FILE  QApplication::tr("Opening File", "Global")
#define FILE_OPENED QApplication::tr("File opened", "Global")
#define SAVING_FILE QApplication::tr("Saving file", "Global")
#define FILE_SAVED QApplication::tr("File saved", "Global")
#define ERROR_WHILE_SAVING QApplication::tr("Writing error", "Global")
#define ERROR_WHILE_OPENING QApplication::tr("Reading error", "Global")
#define IMPORTING_FILE QApplication::tr("Importing File", "Global")
#define FILE_IMPORTED QApplication::tr("File imported", "Global")
#define IMPORT QApplication::tr("Import", "Global")
#define OPEN QApplication::tr("Open", "Global")
#define SAVE QApplication::tr("Save", "Global")
#define PROGRAM_NAME QApplication::tr("Timesheet", "Global")
#define DELETE_LANG QApplication::tr("Delete", "Global")
#define NEXT_DAY  QApplication::tr("nd", "Global")
#define AUTH_SUCCES  QApplication::tr("Authorization: Succesfull", "Global")
#define AUTH_ERROR  QApplication::tr("Authorization: Error", "Global")
#define CONN_ERROR  QApplication::tr("Connection Error", "Global")
#define JOBS_TO_UPDATE  QApplication::tr("Jobs for Export: ", "Global")
#define JOBS_UP_TO_DATE  QApplication::tr("Jobs updated!", "Global")
#define PROJECTS_UPDATED  QApplication::tr("Projects Updated!", "Global")
#define WAITING_FOR_CONNECTION  QApplication::tr("Waiting for Connection", "Global")
#define CONNECTION_SUCCESSFULL  QApplication::tr("Connection Successfull", "Global")
#define CONNECTION_FAILED  QApplication::tr("Connection failed", "Global")
#define COMPANY QApplication::tr("Company", "Global")
#define PROJECT QApplication::tr("Project", "Global")
#define DAT_FILES QApplication::tr("dat Files (*.dat)")
#define TIMESHEET_FILES QApplication::tr("Timesheet Files (*.tsh)")
#define MINIMIZE QApplication::tr("Mi&nimize")
#define RESTORE QApplication::tr("&Restore")
#define START QApplication::tr("&Start")
#define STOP QApplication::tr("&Stop")
#define QUIT QApplication::tr("&Quit")
#define EXPORT_XML QApplication::tr("Export XML")
#define DO_REPLACE_JOBS QApplication::tr("Do You want to remove current jobs?")
#define ABOUT_TO_IMPORT QApplication::tr("Importing jobs")
#define PRODUCTION