#pragma once

#include <QWizard>
#include "ui_TimesheetWizard.h"
#include "Settings.h"

class TimesheetWizard : public QWizard
{
	Q_OBJECT

public:
	TimesheetWizard(QWidget *parent = Q_NULLPTR);
	~TimesheetWizard();
	int nextId() const override;
	Settings getSettings();
	private slots:
	void getNewFilename();
private:
	Ui::TimesheetWizard ui;
	enum { Intro, Type, Offline, Online, Path, End };
};
