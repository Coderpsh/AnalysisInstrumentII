#ifndef CALIBRATIONDLG_H
#define CALIBRATIONDLG_H

#include <QWidget>

#include "alamdlg.h"
#include "alamdlg2.h"
#include "alamdlg3.h"
#include "alamdlg4.h"
#include  "iddlg.h"
#include "iddlg2.h"
#include  "lddlg.h"
#include "lddlg2.h"
#include  "demodulationdlg.h"
#include "interfaceandcommunicationdlg.h"
#include "interfaceandcommunicationdlg2.h"
#include "spectrumselfregulatedlg1.h"
#include "spectrumselfregulatedlg.h"
#include "spectrumselfregulatedlg2.h"
#include "spectrumselfregulatedlg3.h"
#include "spectrumselfregulatedlg4.h"
#include "algorithmdlg.h"
#include "algorithmdlg2.h"
#include "algorithmdld3.h"
#include "verifydlg.h"
#include "verifydlg2.h"
#include "calibrationparameterdlg.h"
#include "calibrationparameterdlg2.h"
#include "plsdlg.h"
#include"referencecurvedlg.h"
#include "referencecurvedlg2.h"
#include "referencecurvedlg3.h"



namespace Ui {
class calibrationDlg;
}

class calibrationDlg : public QWidget
{
    Q_OBJECT

public:
    explicit calibrationDlg(QWidget *parent = 0);
    ~calibrationDlg();

signals:
    void backMainWindow();

private slots:
    void showRealTime();

     void backCalibrationdlg();

     void showch();

     void on_ID_clicked();

     void on_LD_clicked();

     void on_demodulation_clicked();

     void on_algorithm_clicked();

     void on_spectrumselfregulate_clicked();

     void on_alarm_clicked();

     void on_interfaceandcommunication_clicked();

     void on_verify_clicked();

     void on_calibrationparameter_clicked();

     void on_PLS_clicked();

     void on_back_clicked();

     void on_referencecurve_clicked();

     void  tocalibration();
private:
    Ui::calibrationDlg *ui;
    alamDlg*alamdlg1;
    alamDlg2*alamdlg2;
    alamDlg3*alamdlg3;
    alamDlg4*alamdlg4;
    IDDlg*iddlg1;
    IDDlg2*iddlg2;
    LDDlg*lddlg1;
    LDDlg2*lddlg2;
    demodulationDlg*demodulationDlg1;
    interfaceAndCommunicationDlg*interfaceAndCommunicationDlg1;
    interfaceandcommunicationDlg2*interfaceandcommunicationdlg2;
    spectrumSelfRegulateDlg*spectrumselfregulatedlg;
    spectrumselfregulateDlg1*spectrumselfregulatedlg1;
    spectrumSelfRegulateDlg2*spectrumselfregulatedlg2;
    spectrumSelfRegulateDlg3*spectrumselfregulatedlg3;
    spectrumselfregulateDlg4*spectrumselfregulatedlg4;
    algorithmDlg*algorithmdlg;
    algorithmDlg2*algorithmdlg2;
    algorithmDld3*algorithmdld3;
    verifyDlg*verifyDlg1;
    verifyDlg2*verifydlg2;
    calibrationParameterDlg*calibrationParameterDlg1;
    calibrationParameterDlg2*calibrationParameterdlg2;
    plsDlg*plsdlg;
    referenceCurvedlg*referencecurvedlg;
    referenceCurvedlg2*referencecurvedlg2;
    referencecurvedlg3*referencecCurvedlg3;

};

#endif // CALIBRATIONDLG_H
