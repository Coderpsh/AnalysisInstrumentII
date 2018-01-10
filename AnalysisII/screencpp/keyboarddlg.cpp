#include "screeninclu/keyboarddlg.h"
#include "ui_keyboarddlg.h"

#include "QGroupBox"



//extern QString context;

keyboardDlg::keyboardDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keyboardDlg)
{
    ui->setupUi(this);

   setWindowFlags(Qt::FramelessWindowHint); //设置窗体边框透明，以便于自定义窗体的边框
   // setFixedSize(255,235);
    inputTxt="";
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->charDot->setFocusPolicy(Qt::NoFocus);
    ui->charMinus->setFocusPolicy(Qt::NoFocus);
    ui->Enter->setFocusPolicy(Qt::NoFocus);
    ui->EXP->setFocusPolicy(Qt::NoFocus);
    ui->num0->setFocusPolicy(Qt::NoFocus);
    ui->num1->setFocusPolicy(Qt::NoFocus);
    ui->num2->setFocusPolicy(Qt::NoFocus);
    ui->num3->setFocusPolicy(Qt::NoFocus);
    ui->num4->setFocusPolicy(Qt::NoFocus);
    ui->num5->setFocusPolicy(Qt::NoFocus);
    ui->num6->setFocusPolicy(Qt::NoFocus);
    ui->num7->setFocusPolicy(Qt::NoFocus);
    ui->num8->setFocusPolicy(Qt::NoFocus);
    ui->num9->setFocusPolicy(Qt::NoFocus);
    ui->percent->setFocusPolicy(Qt::NoFocus);
    ui->plus->setFocusPolicy(Qt::NoFocus);


}

keyboardDlg::~keyboardDlg()
{
    delete ui;
}

void keyboardDlg::on_Enter_clicked()
{
    getInput(inputTxt);
    on_cleanInput_clicked();
    this->hide();
}


void keyboardDlg::on_num1_clicked()
{
    inputTxt+="1";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num2_clicked()
{
    inputTxt+="2";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num3_clicked()
{
    inputTxt+="3";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num4_clicked()
{
    inputTxt+="4";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num5_clicked()
{
    inputTxt+="5";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num6_clicked()
{
    inputTxt+="6";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num7_clicked()
{
    inputTxt+="7";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num8_clicked()
{
    inputTxt+="8";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num9_clicked()
{
    inputTxt+="9";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_charMinus_clicked()
{
    inputTxt+="-";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_num0_clicked()
{
    inputTxt+="0";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_charDot_clicked()
{
    inputTxt+=".";
    ui->showInput->setText(inputTxt);
}


void keyboardDlg::on_cleanInput_clicked()
{
    inputTxt="";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_cancel_clicked()
{
    on_cleanInput_clicked();
    this->hide();
}

void keyboardDlg::on_plus_clicked()
{
    inputTxt+="+";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_percent_clicked()
{
    inputTxt+="%";
    ui->showInput->setText(inputTxt);
}

void keyboardDlg::on_EXP_clicked()
{
    inputTxt+="e";
    ui->showInput->setText(inputTxt);
}
