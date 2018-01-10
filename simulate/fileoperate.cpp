#include "fileoperate.h"
#include "global.h"
extern fileoperate * files;
fileoperate::fileoperate(QObject *parent) : QObject(parent)
{
  fp = new FILE;

}
fileoperate::~fileoperate()
{
    delete fp;
}

void fileoperate::writefile(int CH)
{
    if (CH==0)
    {
    file.open("/home/parasch0.dat",ios::in|ios::out|ios::binary);
    file.write((char*)AnaParas_Ch0,sizeof(Para));
    file.close();
    }
    else
    {
      file.open("/home/parasch1.dat",ios::in|ios::out|ios::binary);
      file.write((char*)AnaParas_Ch1,sizeof(Para));
      file.close();
    }
}

void fileoperate::readfile(int CH)
{
    if(CH==0)
    {
    file.open("/home/parasch0.dat",ios::in|ios::out|ios::binary);
    file.read((char*)AnaParas_Ch0,sizeof(Para));
    file.close();
    }
    else
    {
        file.open("/home/parasch1.dat",ios::in|ios::out|ios::binary);
        file.read((char*)AnaParas_Ch1,sizeof(Para));
        file.close();
    }
}

void fileoperate::Ref_write(int CH)
{
    int i=0,j=0;
    if (CH==0)
    {
    fp=fopen("/home/refch0.txt","w");
    for(i=0;i<60;i++)
    {
        for(j=0;j<1013;j++)
        {
                fprintf(fp,"%0.2f ",data[i][j]);
        }
    }
    fclose(fp);
    }
    else
    {
        fp=fopen("/home/refch1.txt","w");
        for(i=0;i<60;i++)
        {
            for(j=0;j<1013;j++)
            {
                    fprintf(fp,"%0.2f ",data_ch1[i][j]);
            }
        }
        fclose(fp);
    }



}
void fileoperate::Ref_read(int CH)
{
    int i=0,j=0;
    if(CH==0)
    {
    fp=fopen("/home/refch0.txt","r");
    for(i=0;i<60;i++)
    {
        for(j=0;j<1013;j++)
        {
                fscanf(fp,"%G",&data[i][j]);
        }
    }
    fclose(fp);
   }
    else
    {
        fp=fopen("/home/refch1.txt","r");
        for(i=0;i<60;i++)
        {
            for(j=0;j<1013;j++)
            {
                    fscanf(fp,"%G",&data_ch1[i][j]);
            }
        }
        fclose(fp);
    }
}

void fileoperate::Ref_send(bool Ref_transmit,int CH)
{
  if(Ref_transmit)//RefCu
  {
  if(CH==0)
  {
   files->Ref_read(0);
   int j;
      for(j=0;j<1013;j++)
      {
           printf("%d\t",j);
           printf("%G\t",data[0][j]);
           printf("%G\t",data[1][j]);
           printf("%G\t",data[2][j]);
           printf("%G\t",data[3][j]);
           printf("%G\t",data[4][j]);
           printf("%G\t",data[5][j]);
           printf("%G\t",data[6][j]);
           printf("%G\t",data[7][j]);
           printf("%G\t",data[8][j]);
           printf("%G\t",data[9][j]);

           printf("%G\t",data[10][j]);
           printf("%G\t",data[11][j]);
           printf("%G\t",data[12][j]);
           printf("%G\t",data[13][j]);
           printf("%G\t",data[14][j]);
           printf("%G\t",data[15][j]);
           printf("%G\t",data[16][j]);
           printf("%G\t",data[17][j]);
           printf("%G\t",data[18][j]);
           printf("%G\t",data[19][j]);

           printf("%G\t",data[20][j]);
           printf("%G\t",data[21][j]);
           printf("%G\t",data[22][j]);
           printf("%G\t",data[23][j]);
           printf("%G\t",data[24][j]);
           printf("%G\t",data[25][j]);
           printf("%G\t",data[26][j]);
           printf("%G\t",data[27][j]);
           printf("%G\t",data[28][j]);
           printf("%G\t",data[29][j]);

           printf("%G\t",data[30][j]);
           printf("%G\t",data[31][j]);
           printf("%G\t",data[32][j]);
           printf("%G\t",data[33][j]);
           printf("%G\t",data[34][j]);
           printf("%G\t",data[35][j]);
           printf("%G\t",data[36][j]);
           printf("%G\t",data[37][j]);
           printf("%G\t",data[38][j]);
           printf("%G\t",data[39][j]);

           printf("%G\t",data[40][j]);
           printf("%G\t",data[41][j]);
           printf("%G\t",data[42][j]);
           printf("%G\t",data[43][j]);
           printf("%G\t",data[44][j]);
           printf("%G\t",data[45][j]);
           printf("%G\t",data[46][j]);
           printf("%G\t",data[47][j]);
           printf("%G\t",data[48][j]);
           printf("%G\t",data[49][j]);

           printf("%G\t",data[50][j]);
           printf("%G\t",data[51][j]);
           printf("%G\t",data[52][j]);
           printf("%G\t",data[53][j]);
           printf("%G\t",data[54][j]);
           printf("%G\t",data[55][j]);
           printf("%G\t",data[56][j]);
           printf("%G\t",data[57][j]);
           printf("%G\t",data[58][j]);
           printf("%G\n",data[59][j]);
      }
  }
else
 {
     files->Ref_read(1);
     int j;
         for(j=0;j<1013;j++)
         {
              printf("%d\t",j);
              printf("%G\t",data_ch1[0][j]);
              printf("%G\t",data_ch1[1][j]);
              printf("%G\t",data_ch1[2][j]);
              printf("%G\t",data_ch1[3][j]);
              printf("%G\t",data_ch1[4][j]);
              printf("%G\t",data_ch1[5][j]);
              printf("%G\t",data_ch1[6][j]);
              printf("%G\t",data_ch1[7][j]);
              printf("%G\t",data_ch1[8][j]);
              printf("%G\t",data_ch1[9][j]);

              printf("%G\t",data_ch1[10][j]);
              printf("%G\t",data_ch1[11][j]);
              printf("%G\t",data_ch1[12][j]);
              printf("%G\t",data_ch1[13][j]);
              printf("%G\t",data_ch1[14][j]);
              printf("%G\t",data_ch1[15][j]);
              printf("%G\t",data_ch1[16][j]);
              printf("%G\t",data_ch1[17][j]);
              printf("%G\t",data_ch1[18][j]);
              printf("%G\t",data_ch1[19][j]);

              printf("%G\t",data_ch1[20][j]);
              printf("%G\t",data_ch1[21][j]);
              printf("%G\t",data_ch1[22][j]);
              printf("%G\t",data_ch1[23][j]);
              printf("%G\t",data_ch1[24][j]);
              printf("%G\t",data_ch1[25][j]);
              printf("%G\t",data_ch1[26][j]);
              printf("%G\t",data_ch1[27][j]);
              printf("%G\t",data_ch1[28][j]);
              printf("%G\t",data_ch1[29][j]);

              printf("%G\t",data_ch1[30][j]);
              printf("%G\t",data_ch1[31][j]);
              printf("%G\t",data_ch1[32][j]);
              printf("%G\t",data_ch1[33][j]);
              printf("%G\t",data_ch1[34][j]);
              printf("%G\t",data_ch1[35][j]);
              printf("%G\t",data_ch1[36][j]);
              printf("%G\t",data_ch1[37][j]);
              printf("%G\t",data_ch1[38][j]);
              printf("%G\t",data_ch1[39][j]);

              printf("%G\t",data_ch1[40][j]);
              printf("%G\t",data_ch1[41][j]);
              printf("%G\t",data_ch1[42][j]);
              printf("%G\t",data_ch1[43][j]);
              printf("%G\t",data_ch1[44][j]);
              printf("%G\t",data_ch1[45][j]);
              printf("%G\t",data_ch1[46][j]);
              printf("%G\t",data_ch1[47][j]);
              printf("%G\t",data_ch1[48][j]);
              printf("%G\t",data_ch1[49][j]);

              printf("%G\t",data_ch1[50][j]);
              printf("%G\t",data_ch1[51][j]);
              printf("%G\t",data_ch1[52][j]);
              printf("%G\t",data_ch1[53][j]);
              printf("%G\t",data_ch1[54][j]);
              printf("%G\t",data_ch1[55][j]);
              printf("%G\t",data_ch1[56][j]);
              printf("%G\t",data_ch1[57][j]);
              printf("%G\t",data_ch1[58][j]);
              printf("%G\n",data_ch1[59][j]);
         }
    }
  }
}
void fileoperate::AnaParas_send(int CH)
{
 if(CH==0)
 {
     printf("AnaParas_Ch0\n");
    printf("AnaSN\t");
    printf("%ld\n",AnaParas_Ch0->AnaSN);
    printf("AnaModel\t");
    printf("%ld\n",AnaParas_Ch0->AnaModel);
    printf("FWRev\t");
    printf("%ld\n",AnaParas_Ch0->FWRev);
    printf("CellSN\t");
    printf("%ld\n",AnaParas_Ch0->CellSN);
    printf("CellModel\t");
    printf("%ld\n",AnaParas_Ch0->CellModel);
    printf("Analyte\t");
    printf("%d\n",AnaParas_Ch0->Analyte);
    printf("RangeMin\t");
    printf("%.2f\n",AnaParas_Ch0->RangeMin);  //for DA;
    printf("RangeMax\t");
    printf("%.2f\n",AnaParas_Ch0->RangeMax);  //for DA;4~20MA;
     //LD paras 9
    printf("IStart\t");
    printf("%.2f\n",AnaParas_Ch0->IStart);
    printf("IRange\t");
    printf("%.2f\n",AnaParas_Ch0->IRange);
    printf("Ituning\t");
    printf("%.2f\n",AnaParas_Ch0->Ituning);
    printf("ScanTime\t");
    printf("%ld\n",AnaParas_Ch0->ScanTime);
    printf("ModRange\t");
    printf("%ld\n",AnaParas_Ch0->ModRange);//
    printf("SpectrAvg\t");
    printf("%d\n",AnaParas_Ch0->SpectrAvg);//
    printf("NullWidth\t");
    printf("%d\n",AnaParas_Ch0->NullWidth);
    printf("ModFreq\t");
    printf("%.2f\n",AnaParas_Ch0->ModFreq);
    //bool Ldwork_Flag; //lineedit,
    //jie tiao  ,PCIpara 4
    printf("Phase\t");
    printf("%ld\n",AnaParas_Ch0->Phase);
    printf("Gain2f\t");
    printf("%.2f\n",AnaParas_Ch0->Gain2f);
    printf("Cent2f\t");
    printf("%.2f\n",AnaParas_Ch0->Cent2f);
    printf("BandWidth\t");
    printf("%ld\n",AnaParas_Ch0->BandWidth);
    //jie  mian; 4
    printf("Punit\t");
    printf("%d\n",AnaParas_Ch0->Punit);
    printf("ConcUnit\t");
    printf("%d\n",AnaParas_Ch0->ConcUnit);
    printf("BaudRate\t");
    printf("%d\n",AnaParas_Ch0->BaudRate);
    printf("DataFormat\t");
    printf("%d\n",AnaParas_Ch0->DataFormat);
    //puzitiao ; 8 + 9
    printf("PkTrk\t");
    printf("%d\n",AnaParas_Ch0->PkTrk);
    printf("PkTrkAvg\t");
    printf("%d\n",AnaParas_Ch0->PkTrkAvg);
    printf("PkTarget\t");
    printf("%d\n",AnaParas_Ch0->PkTarget);
    printf("ValPkTrkStart\t");
    printf("%d\n",AnaParas_Ch0->ValPkTrkStart);
    printf("AnaSN\t");
    printf("%d\n",AnaParas_Ch0->ValPkTrkEnd);
    printf("PkTrkStart\t");
    printf("%d\n",AnaParas_Ch0->PkTrkStart);
    printf("PkTrkEnd\t");
    printf("%d\n",AnaParas_Ch0->PkTrkEnd);
    printf("PkShiftLmt\t");
    printf("%d\n",AnaParas_Ch0->PkShiftLmt); //

    printf("PkTrkIdxMax\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkIdxMax);
    printf("PkTrkIdxMin\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkIdxMin);
    printf("PkTrkTLow\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkTLow);
    printf("PkTrkTHigh\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkTHigh);
    printf("PkTrkPLow\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkPLow);
    printf("PkTrkPHigh\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkPHigh);
    printf("PkTrkHgtMin\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkHgtMin);
    printf("PkTrkHgtMax\t");
    printf("%.2f\n",AnaParas_Ch0->PkTrkHgtMax);
    printf("PkWdith\t");
    printf("%.2f\n",AnaParas_Ch0->PkWdith);


    //alarm; 8+9
    printf("Alarm\t");
    printf("%d\n",AnaParas_Ch0->Alarm);
    printf("Pmax\t");
    printf("%.2f\n",AnaParas_Ch0->Pmax);
    printf("Pmin\t");
    printf("%.2f\n",AnaParas_Ch0->Pmin);
    printf("AlarmConcMax\t");
    printf("%d\n",AnaParas_Ch0->AlarmConcMax);
    printf("AlarmConcMin\t");
    printf("%d\n",AnaParas_Ch0->AlarmConcMin);
    printf("Tmax\t");
    printf("%.2f\n",AnaParas_Ch0->Tmax);
    printf("Tmin\t");
    printf("%.2f\n",AnaParas_Ch0->Tmin);
    printf("PkTrkLimit\t");
    printf("%d\n",AnaParas_Ch0->PkTrkLimit);

    printf("FitQualt\t");
    printf("%.2f\n",AnaParas_Ch0->FitQual);
    printf("DCHigh\t");
    printf("%.2f\n",AnaParas_Ch0->DCHigh);
    printf("DCLow\t");
    printf("%.2f\n",AnaParas_Ch0->DCLow);
    printf("IHigh\t");
    printf("%.2f\n",AnaParas_Ch0->IHigh);
    printf("Ilow\t");
    printf("%.2f\n",AnaParas_Ch0->Ilow);
    printf("wait\t");
    printf("%.2f\n",AnaParas_Ch0->wait);//wait
    printf("TwoFSat\t");
    printf("%.2f\n",AnaParas_Ch0->TwoFSat);
    printf("NullHigh\t");
    printf("%.2f\n",AnaParas_Ch0->NullHigh);
    printf("NullLow\t");
    printf("%.2f\n",AnaParas_Ch0->NullLow);

     // algo 13+1(guhua)
    printf("Model\t");
     printf("%d\n",AnaParas_Ch0->Model);//计算模型，PLS=1;cls=0
    // int ProValMode;//过程态校验态切换，PRO=1 VAL=0 CLS(guhua;)
     printf("SpectraStart\t");
     printf("%d\n",AnaParas_Ch0->SpectraStart);//选谱起点	输入数值（1-1000）
     printf("SpectraEnd\t");
     printf("%d\n",AnaParas_Ch0->SpectraEnd);//选谱终点	输入数值（1-1000）
     printf("DFEnable\t");
     printf("%d\n",AnaParas_Ch0->DFEnable);  //数字滤波   (0：禁用 1：启用)
     printf("DCNormStart\t");
     printf("%d\n",AnaParas_Ch0->DCNormStart);//归一化起始点(0~4000)
     printf("DCNormEnd\t");
     printf("%d\n",AnaParas_Ch0->DCNormEnd);//归一化点(0~4000)
     printf("MovAvg\t");
     printf("%d\n",AnaParas_Ch0->MovAvg);

      /********以下为CLS的参数******/
     printf("PRuse\t");
     printf("%d\n",AnaParas_Ch0->PRuse);//PR选用		选择:（0.关， 1 Pro 2. Val 3. Both）
     printf("R1use\t");
     printf("%d\n",AnaParas_Ch0->R1use);//R1选用		选择:（0.关， 1 Pro 2. Val 4. Both）
     printf("R2use\t");
     printf("%d\n",AnaParas_Ch0->R2use);//R2选用		选择:（0.关， 1 Pro 2. Val 5. Both）
     printf("R3use\t");
     printf("%d\n",AnaParas_Ch0->R3use);//R3选用		选择:（0.关， 1 Pro 2. Val 6. Both）
     printf("Baseuse\t");
     printf("%d\n",AnaParas_Ch0->Baseuse);//基线选用	选择:（0.关， 1 Pro 2. Val 7. Both）
     printf("VRuse\t");
     printf("%d\n",AnaParas_Ch0->VRuse);//VR选用		选择:（0.关， 1 Pro 2. Val 8. Both）

   /********以下为PLS的参数******/
     printf("BuildMode\t");
     printf("%d\n",AnaParas_Ch0->BuildMode);//PLS模型是否重建的标志(1:重构，0：不重构)
     printf("erref\t");
     printf("%.2f\n",AnaParas_Ch0->erref);//误差控制精度
     printf("errcirNum\t");
     printf("%d\n",AnaParas_Ch0->errcirNum);//误差控制循环次数
  /********以下为交叉检验的参数******/
     printf("PLS_K\t");
     printf("%d\n",AnaParas_Ch0->PLS_K);  //K为折数，
     printf("PLS_A\t");
     printf("%d\n",AnaParas_Ch0->PLS_A);
     printf("PLS_N\t");
     printf("%d\n",AnaParas_Ch0->PLS_N);

     //jiaoyan
     printf("PurgeTime\t");
     printf("%d\n",AnaParas_Ch0->PurgeTime);
     printf("Vconc\t");
     printf("%.2f\n",AnaParas_Ch0->Vconc);
     printf("VAllowance\t");
     printf("%.2f\n",AnaParas_Ch0->VAllowance);
     printf("VCorrection\t");
     printf("%d\n",AnaParas_Ch0->VCorrection);
     printf("SSlope\t");
     printf("%.2f\n",AnaParas_Ch0->SSlope);
     printf("SOffset\t");
     printf("%.2f\n",AnaParas_Ch0->SOffset);

     //jiaozhun
     printf("PCoeff0\t");
     printf("%.2f\n",AnaParas_Ch0->PCoeff0);
     printf("PCoeff1\t");
     printf("%.2f\n",AnaParas_Ch0->PCoeff1);
     printf("PCoeff2\t");
     printf("%.2f\n",AnaParas_Ch0->PCoeff2);
     printf("PCoeff3\t");
     printf("%.2f\n",AnaParas_Ch0->PCoeff3);
     printf("VCoeff0\t");
     printf("%.2f\n",AnaParas_Ch0->VCoeff0);
     printf("VCoeff1\t");
     printf("%.2f\n",AnaParas_Ch0->VCoeff1);
     printf("VCoeff2\t");
     printf("%.2f\n",AnaParas_Ch0->VCoeff2);
     printf("VCoeff3\t");
     printf("%.2f\n",AnaParas_Ch0->VCoeff3);
     //refcurve
     printf("CalDate\t");
     printf("%ld\n",AnaParas_Ch0->CalDate);
     printf("RefCurvAvg\t");
     printf("%d\n",AnaParas_Ch0->RefCurvAvg);
     printf("RefInd\t");
     printf("%.2f\n",AnaParas_Ch0->RefInd);
     printf("ProRCon\t");
     printf("%.2f\n",AnaParas_Ch0->ProRCon);
     printf("ValRCon\t");
     printf("%.2f\n",AnaParas_Ch0->ValRCon);
     printf("Comp1\t");
     printf("%.2f\n",AnaParas_Ch0->Comp1);
     printf("Comp2\t");
     printf("%.2f\n",AnaParas_Ch0->Comp2);
     printf("Comp3\t");
     printf("%.2f\n",AnaParas_Ch0->Comp3);
     printf("Comp4\t");
     printf("%.2f\n",AnaParas_Ch0->Comp4);
     printf("Comp5\t");
     printf("%.2f\n",AnaParas_Ch0->Comp5);
     printf("Comp6\t");
     printf("%.2f\n",AnaParas_Ch0->Comp6);
     printf("Comp7\t");
     printf("%.2f\n",AnaParas_Ch0->Comp7);
     printf("Comp8\t");
     printf("%.2f\n",AnaParas_Ch0->Comp8);
 }
 else
 {
     printf("AnaParas_Ch1\n");
     printf("AnaSN\t");
     printf("%ld\n",AnaParas_Ch1->AnaSN);
     printf("AnaModel\t");
     printf("%ld\n",AnaParas_Ch1->AnaModel);
     printf("FWRev\t");
     printf("%ld\n",AnaParas_Ch1->FWRev);
     printf("CellSN\t");
     printf("%ld\n",AnaParas_Ch1->CellSN);
     printf("CellModel\t");
     printf("%ld\n",AnaParas_Ch1->CellModel);
     printf("Analyte\t");
     printf("%d\n",AnaParas_Ch1->Analyte);
     printf("RangeMin\t");
     printf("%.2f\n",AnaParas_Ch1->RangeMin);  //for DA;
     printf("RangeMax\t");
     printf("%.2f\n",AnaParas_Ch1->RangeMax);  //for DA;4~20MA;
      //LD paras 9
     printf("IStart\t");
     printf("%.2f\n",AnaParas_Ch1->IStart);
     printf("IRange\t");
     printf("%.2f\n",AnaParas_Ch1->IRange);
     printf("Ituning\t");
     printf("%.2f\n",AnaParas_Ch1->Ituning);
     printf("ScanTime\t");
     printf("%ld\n",AnaParas_Ch1->ScanTime);
     printf("ModRange\t");
     printf("%ld\n",AnaParas_Ch1->ModRange);//
     printf("SpectrAvg\t");
     printf("%d\n",AnaParas_Ch1->SpectrAvg);//
     printf("NullWidth\t");
     printf("%d\n",AnaParas_Ch1->NullWidth);
     printf("ModFreq\t");
     printf("%.2f\n",AnaParas_Ch1->ModFreq);
     //bool Ldwork_Flag; //lineedit,
     //jie tiao  ,PCIpara 4
     printf("Phase\t");
     printf("%ld\n",AnaParas_Ch1->Phase);
     printf("Gain2f\t");
     printf("%.2f\n",AnaParas_Ch1->Gain2f);
     printf("Cent2f\t");
     printf("%.2f\n",AnaParas_Ch1->Cent2f);
     printf("BandWidth\t");
     printf("%ld\n",AnaParas_Ch1->BandWidth);
     //jie  mian; 4
     printf("Punit\t");
     printf("%d\n",AnaParas_Ch1->Punit);
     printf("ConcUnit\t");
     printf("%d\n",AnaParas_Ch1->ConcUnit);
     printf("BaudRate\t");
     printf("%d\n",AnaParas_Ch1->BaudRate);
     printf("DataFormat\t");
     printf("%d\n",AnaParas_Ch1->DataFormat);
     //puzitiao ; 8 + 9
     printf("PkTrk\t");
     printf("%d\n",AnaParas_Ch1->PkTrk);
     printf("PkTrkAvg\t");
     printf("%d\n",AnaParas_Ch1->PkTrkAvg);
     printf("PkTarget\t");
     printf("%d\n",AnaParas_Ch1->PkTarget);
     printf("ValPkTrkStart\t");
     printf("%d\n",AnaParas_Ch1->ValPkTrkStart);
     printf("AnaSN\t");
     printf("%d\n",AnaParas_Ch1->ValPkTrkEnd);
     printf("PkTrkStart\t");
     printf("%d\n",AnaParas_Ch1->PkTrkStart);
     printf("PkTrkEnd\t");
     printf("%d\n",AnaParas_Ch1->PkTrkEnd);
     printf("PkShiftLmt\t");
     printf("%d\n",AnaParas_Ch1->PkShiftLmt); //

     printf("PkTrkIdxMax\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkIdxMax);
     printf("PkTrkIdxMin\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkIdxMin);
     printf("PkTrkTLow\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkTLow);
     printf("PkTrkTHigh\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkTHigh);
     printf("PkTrkPLow\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkPLow);
     printf("PkTrkPHigh\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkPHigh);
     printf("PkTrkHgtMin\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkHgtMin);
     printf("PkTrkHgtMax\t");
     printf("%.2f\n",AnaParas_Ch1->PkTrkHgtMax);
     printf("PkWdith\t");
     printf("%.2f\n",AnaParas_Ch1->PkWdith);


     //alarm; 8+9
     printf("Alarm\t");
     printf("%d\n",AnaParas_Ch1->Alarm);
     printf("Pmax\t");
     printf("%.2f\n",AnaParas_Ch1->Pmax);
     printf("Pmin\t");
     printf("%.2f\n",AnaParas_Ch1->Pmin);
     printf("AlarmConcMax\t");
     printf("%d\n",AnaParas_Ch1->AlarmConcMax);
     printf("AlarmConcMin\t");
     printf("%d\n",AnaParas_Ch1->AlarmConcMin);
     printf("Tmax\t");
     printf("%.2f\n",AnaParas_Ch1->Tmax);
     printf("Tmin\t");
     printf("%.2f\n",AnaParas_Ch1->Tmin);
     printf("PkTrkLimit\t");
     printf("%d\n",AnaParas_Ch1->PkTrkLimit);

     printf("FitQualt\t");
     printf("%.2f\n",AnaParas_Ch1->FitQual);
     printf("DCHigh\t");
     printf("%.2f\n",AnaParas_Ch1->DCHigh);
     printf("DCLow\t");
     printf("%.2f\n",AnaParas_Ch1->DCLow);
     printf("IHigh\t");
     printf("%.2f\n",AnaParas_Ch1->IHigh);
     printf("Ilow\t");
     printf("%.2f\n",AnaParas_Ch1->Ilow);
     printf("wait\t");
     printf("%.2f\n",AnaParas_Ch1->wait);//wait
     printf("TwoFSat\t");
     printf("%.2f\n",AnaParas_Ch1->TwoFSat);
     printf("NullHigh\t");
     printf("%.2f\n",AnaParas_Ch1->NullHigh);
     printf("NullLow\t");
     printf("%.2f\n",AnaParas_Ch1->NullLow);

      // algo 13+1(guhua)
     printf("Model\t");
      printf("%d\n",AnaParas_Ch1->Model);//计算模型，PLS=1;cls=0
     // int ProValMode;//过程态校验态切换，PRO=1 VAL=0 CLS(guhua;)
      printf("SpectraStart\t");
      printf("%d\n",AnaParas_Ch1->SpectraStart);//选谱起点	输入数值（1-1000）
      printf("SpectraEnd\t");
      printf("%d\n",AnaParas_Ch1->SpectraEnd);//选谱终点	输入数值（1-1000）
      printf("DFEnable\t");
      printf("%d\n",AnaParas_Ch1->DFEnable);  //数字滤波   (0：禁用 1：启用)
      printf("DCNormStart\t");
      printf("%d\n",AnaParas_Ch1->DCNormStart);//归一化起始点(0~4000)
      printf("DCNormEnd\t");
      printf("%d\n",AnaParas_Ch1->DCNormEnd);//归一化点(0~4000)
      printf("MovAvg\t");
      printf("%d\n",AnaParas_Ch1->MovAvg);

       /********以下为CLS的参数******/
      printf("PRuse\t");
      printf("%d\n",AnaParas_Ch1->PRuse);//PR选用		选择:（0.关， 1 Pro 2. Val 3. Both）
      printf("R1use\t");
      printf("%d\n",AnaParas_Ch1->R1use);//R1选用		选择:（0.关， 1 Pro 2. Val 4. Both）
      printf("R2use\t");
      printf("%d\n",AnaParas_Ch1->R2use);//R2选用		选择:（0.关， 1 Pro 2. Val 5. Both）
      printf("R3use\t");
      printf("%d\n",AnaParas_Ch1->R3use);//R3选用		选择:（0.关， 1 Pro 2. Val 6. Both）
      printf("Baseuse\t");
      printf("%d\n",AnaParas_Ch1->Baseuse);//基线选用	选择:（0.关， 1 Pro 2. Val 7. Both）
      printf("VRuse\t");
      printf("%d\n",AnaParas_Ch1->VRuse);//VR选用		选择:（0.关， 1 Pro 2. Val 8. Both）

    /********以下为PLS的参数******/
      printf("BuildMode\t");
      printf("%d\n",AnaParas_Ch1->BuildMode);//PLS模型是否重建的标志(1:重构，0：不重构)
      printf("erref\t");
      printf("%.2f\n",AnaParas_Ch1->erref);//误差控制精度
      printf("errcirNum\t");
      printf("%d\n",AnaParas_Ch1->errcirNum);//误差控制循环次数
   /********以下为交叉检验的参数******/
      printf("PLS_K\t");
      printf("%d\n",AnaParas_Ch1->PLS_K);  //K为折数，
      printf("PLS_A\t");
      printf("%d\n",AnaParas_Ch1->PLS_A);
      printf("PLS_N\t");
      printf("%d\n",AnaParas_Ch1->PLS_N);

      //jiaoyan
      printf("PurgeTime\t");
      printf("%d\n",AnaParas_Ch1->PurgeTime);
      printf("Vconc\t");
      printf("%.2f\n",AnaParas_Ch1->Vconc);
      printf("VAllowance\t");
      printf("%.2f\n",AnaParas_Ch1->VAllowance);
      printf("VCorrection\t");
      printf("%d\n",AnaParas_Ch1->VCorrection);
      printf("SSlope\t");
      printf("%.2f\n",AnaParas_Ch1->SSlope);
      printf("SOffset\t");
      printf("%.2f\n",AnaParas_Ch1->SOffset);

      //jiaozhun
      printf("PCoeff0\t");
      printf("%.2f\n",AnaParas_Ch1->PCoeff0);
      printf("PCoeff1\t");
      printf("%.2f\n",AnaParas_Ch1->PCoeff1);
      printf("PCoeff2\t");
      printf("%.2f\n",AnaParas_Ch1->PCoeff2);
      printf("PCoeff3\t");
      printf("%.2f\n",AnaParas_Ch1->PCoeff3);
      printf("VCoeff0\t");
      printf("%.2f\n",AnaParas_Ch1->VCoeff0);
      printf("VCoeff1\t");
      printf("%.2f\n",AnaParas_Ch1->VCoeff1);
      printf("VCoeff2\t");
      printf("%.2f\n",AnaParas_Ch1->VCoeff2);
      printf("VCoeff3\t");
      printf("%.2f\n",AnaParas_Ch1->VCoeff3);
      //refcurve
      printf("CalDate\t");
      printf("%ld\n",AnaParas_Ch1->CalDate);
      printf("RefCurvAvg\t");
      printf("%d\n",AnaParas_Ch1->RefCurvAvg);
      printf("RefInd\t");
      printf("%.2f\n",AnaParas_Ch1->RefInd);
      printf("ProRCon\t");
      printf("%.2f\n",AnaParas_Ch1->ProRCon);
      printf("ValRCon\t");
      printf("%.2f\n",AnaParas_Ch1->ValRCon);
      printf("Comp1\t");
      printf("%.2f\n",AnaParas_Ch1->Comp1);
      printf("Comp2\t");
      printf("%.2f\n",AnaParas_Ch1->Comp2);
      printf("Comp3\t");
      printf("%.2f\n",AnaParas_Ch1->Comp3);
      printf("Comp4\t");
      printf("%.2f\n",AnaParas_Ch1->Comp4);
      printf("Comp5\t");
      printf("%.2f\n",AnaParas_Ch1->Comp5);
      printf("Comp6\t");
      printf("%.2f\n",AnaParas_Ch1->Comp6);
      printf("Comp7\t");
      printf("%.2f\n",AnaParas_Ch1->Comp7);
      printf("Comp8\t");
      printf("%.2f\n",AnaParas_Ch1->Comp8);
 }
}
