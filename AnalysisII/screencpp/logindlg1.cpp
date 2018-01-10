#include "screeninclu/logindlg1.h"
#include "ui_logindlg1.h"
#include "global.h"
#include <QMessageBox>

Logindlg1::Logindlg1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logindlg1)
{
   ui->setupUi(this);
   keyboarddlg=new keyboardDlg;
   setWindowFlags(Qt::FramelessWindowHint);
   ui->back->setFocusPolicy(Qt::NoFocus);
   ui->input->setFocusPolicy(Qt::NoFocus);

}

Logindlg1::~Logindlg1()
{
    delete ui;
    delete keyboarddlg;
}

void Logindlg1::on_input_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->password_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
}


void Logindlg1::on_password_lineEdit_textChanged(const QString &arg1)
{
    QString a= ui->password_lineEdit->text();


    if(a=="222")
    {

        if(CH_Flag==0)
        {
           Debug_Flag=0;
           Re_flag = false;

           if(Debug_Flag_Ch1==0)//Ch0 against all Debug
               Debug_Flag_Ch1=1;

        }
        else
        {
          Debug_Flag_Ch1=0;  //val
          Re_flag_ch1 = false;

          if(Debug_Flag==0)//Ch1 against all Debug
              Debug_Flag=1;

        }




        this->hide();

        QObject::disconnect(ui->password_lineEdit,SIGNAL(textChanged(QString)),0,0);  //先清空内容，再重新建立连接

        ui->password_lineEdit->clear();

        QObject::connect(ui->password_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_password_lineEdit_textChanged(QString)));


        backMainWindow();

        ChangeToDebug();



    }

    else
       {

        QObject::disconnect(ui->password_lineEdit,SIGNAL(textChanged(QString)),0,0);
        ui->password_lineEdit->clear();
        QObject::connect(ui->password_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_password_lineEdit_textChanged(QString)));

        QMessageBox::information(this,"error","please input correct password");

       }
}

void Logindlg1::on_back_clicked()
{
    if(CH_Flag==0)
         RD_flag = 0;
    else
         RD_flag_ch1=0;
    this->hide();
    backMainWindow();
}
