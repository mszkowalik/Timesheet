#pragma once

#include <QDialog>
#include "ui_Login.h"

class Login : public QDialog
{
	Q_OBJECT

public:
	Login(QWidget *parent = Q_NULLPTR);
	~Login();
	void setLogin(QString login);
	QString getPassword();
	QString getLogin();
	bool exitClick = true; // if true, ok wac clicked, if false cancel
	public slots:
	void on_Login_pushButton_clicked();
	void on_Cancel_pushButton_clicked();


private:
	Ui::Login ui;
};
