#include "screeninclu/logindlg.h"
#include "ui_logindlg.h"
#include "QMessageBox"

#include"global.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDlg)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    keyboarddlg=new keyboardDlg;
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->input->setFocusPolicy(Qt::NoFocus);

}

LoginDlg::~LoginDlg()
{
    delete ui;
    delete keyboarddlg;
}

void LoginDlg::on_input_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->passward_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
}

void LoginDlg::on_passward_lineEdit_textChanged(const QString &arg1)
{
    QString a= ui->passward_lineEdit->text();

    if(a=="208")
    {
        this->hide();
        permit_flag=0;
        QObject::disconnect(ui->passward_lineEdit,SIGNAL(textChanged(QString)),0,0);
        ui->passward_lineEdit->clear();
        QObject::connect(ui->passward_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_passward_lineEdit_textChanged(QString)));
       tocalibration();


    }
    else if (a=="222")
    {
        this->hide();
        permit_flag=1;
        QObject::disconnect(ui->passward_lineEdit,SIGNAL(textChanged(QString)),0,0);
        ui->passward_lineEdit->clear();
        QObject::connect(ui->passward_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_passward_lineEdit_textChanged(QString)));
        tocalibration();

    }
    else
      {
        QObject::disconnect(ui->passward_lineEdit,SIGNAL(textChanged(QString)),0,0);
        ui->passward_lineEdit->clear();
        QObject::connect(ui->passward_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_passward_lineEdit_textChanged(QString)));
        QMessageBox::information(this,"error","please input correct password");

      }

}

void LoginDlg::on_back_clicked()
{
   set_mode(0,0);
   set_mode(1,0);
   backMainWindow();
   this->hide();
}


