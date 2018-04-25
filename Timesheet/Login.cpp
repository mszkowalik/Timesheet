#include "Login.h"

Login::Login(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.password_lineEdit->setText("password");
}

Login::~Login()
{
}
void Login::setLogin(QString login)
{
	ui.login_lineEdit->setText(login);
}
QString Login::getPassword()
{
	return ui.password_lineEdit->text();
}
QString Login::getLogin()
{
	return ui.login_lineEdit->text();
}


void Login::on_Login_pushButton_clicked()
{
	exitClick = true;
	close();
}
void Login::on_Cancel_pushButton_clicked()
{
	exitClick = false;
	close();
}