#include "TimesheetWizard.h"
#include <QWizardPage>
#include <qfiledialog.h>
#include "Constants.h"
TimesheetWizard::TimesheetWizard(QWidget *parent)
	: QWizard(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.Online_checkBox, SIGNAL(clicked(bool)), ui.Offline_checkBox, SLOT(toggle()));
	QObject::connect(ui.Offline_checkBox, SIGNAL(clicked(bool)), ui.Online_checkBox, SLOT(toggle()));
	QObject::connect(ui.choose_pushButton, SIGNAL(clicked(bool)), this, SLOT(getNewFilename()));

	QObject::connect(ui.DataRetention_dial, SIGNAL(valueChanged(int)), ui.DataRetention_spinBox, SLOT(setValue(int)));
	QObject::connect(ui.DataRetention_spinBox, SIGNAL(valueChanged(int)), ui.DataRetention_dial, SLOT(setValue(int)));
	setOption(QWizard::NoCancelButton, true);
}

TimesheetWizard::~TimesheetWizard()
{
}

int TimesheetWizard::nextId() const
{
	switch (currentId()) {
	case Type:
		if (ui.Online_checkBox->isChecked())
			return Online;
		else
			return Offline;
	case Intro:
		return Type;
	case Online:
		if (!ui.Username_lineEdit->text().isEmpty() && !ui.ServerAdress_lineEdit->text().isEmpty() && !ui.Port_lineEdit->text().isEmpty())
			return Path;
		else
			return Online;
	case Offline:
		if (!ui.Owner_lineEdit->text().isEmpty())
			return Path;
		else
			return Offline;
	case Path:
		if (ui.Path_lineEdit->text().isEmpty())
			return Path;
		else 
			return End;
	case End:
	default:
		return -1;
	}
}

Settings TimesheetWizard::getSettings()
{
	Settings s;
	s.SyncWithServer = ui.Online_checkBox->isChecked();
	if (s.SyncWithServer)
	{
		s.MySQL_Port = ui.Port_lineEdit->text().toInt();
		s.MySQL_Server = ui.ServerAdress_lineEdit->text();
		s.MySQL_Username = ui.Username_lineEdit->text();
	}
	else
	{
		s.MySQL_Port = 0;
		s.MySQL_Server = "";
		s.MySQL_Username = "";
		s.Owner = ui.Owner_lineEdit->text();
		s.lastOpenedFile = ui.Path_lineEdit->text();
	}


	return s;
}

void TimesheetWizard::getNewFilename()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		SAVE, "Data/", tr("dat Files (*.dat)"));
	ui.Path_lineEdit->setText(fileName);
}