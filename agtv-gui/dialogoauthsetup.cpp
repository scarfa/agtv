#include "dialogoauthsetup.h"
#include "ui_dialogoauthsetup.h"

dialogOauthSetup::dialogOauthSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogOauthSetup)
{
    ui->setupUi(this);
     
    this->ui->pushButtonSave->setEnabled(false);
    
}


void dialogOauthSetup::onAuthNok()
{
    this->ui->pushButtonSave->setEnabled(false);        
}

void dialogOauthSetup::onAuthOk()
{  
    this->ui->pushButtonSave->setEnabled(true);
    this->ui->pushButtonRevoke->setEnabled(true);
}

dialogOauthSetup::~dialogOauthSetup()
{
    delete ui;
}

void dialogOauthSetup::setDialogShown()
{
    dialogShown = true;
    
}

bool dialogOauthSetup::getDialogShown()
{
    return dialogShown;
    
}

void dialogOauthSetup::setCurrentStoredAuthToken(QString currentStoredAuthToken)
{
   
    this->ui->lineEditOAuthToken->setText(currentStoredAuthToken);
}

void dialogOauthSetup::on_pushButtonAuthorizeOnTwitch_clicked()
{

    emit onAuthorizeRequested();
    
}


void dialogOauthSetup::on_pushButtonRevoke_clicked()
{
    QString link = "http://www.twitch.tv/settings/applications";
    QDesktopServices::openUrl(QUrl(link));
}

void dialogOauthSetup::on_pushButtonCancel_clicked()
{
    this->hide();
}

void dialogOauthSetup::on_pushButtonVerify_clicked()
{
    emit authTokenChanged(this->ui->lineEditOAuthToken->text());
}

void dialogOauthSetup::on_pushButtonSave_clicked()
{
    emit saveAuthTokenRequested(this->ui->lineEditOAuthToken->text());  
    this->hide();    
}
