#include "ExN01EventAction.hh"
#include "ExN02RunAction.hh"
#include "ExN01PrimaryGeneratorAction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
//#include "mpi.h"

//#include "ExN01SteppingAction.hh"
  // use of stepping action to get and reset accumulated energy  
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
//#include "ExN01StartHit.hh"
//#include "ExN01StartSD.hh"
//#include "ExN01StartHit.hh"
//#include "ExN01StopSD.hh"
#include "G4TrackStatus.hh"//track态
#include "G4VProcess.hh"
//#include "ExN06StackingAction.hh"
#include <fstream>
#include <vector>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01EventAction::ExN01EventAction(ExN02RunAction* runAct,ExN01PrimaryGeneratorAction* PgmAct)
:fRunAction(runAct),fPriAction(PgmAct),PhotonTime1(15000,0),PhotonTime2(15000,0),PMT1signal(15000,0),PMT2signal(15000,0),fPriPhotonPerEvent(0),
fPhotonElectron_PMT1(0),fPhotonElectron_PMT2(0)
{
     
    G0=7.0E7; // gain of pmt 7.0E7                      
    Ce=1.6E-12; // factor of charge convert to voltage
    tau=2; // rise time of electron 2.0 ns
	deltT = 0.01; 
	jifen=0;
    //Time_Short=0;
	//Time_Long=50;
	evt_num=0;
	efficiency_num=0;
	 T_short=8;
	 T_long=55;
	 PSD1=0;
	 PSD2=0;
	 Q_long=0;
	 Q_short=0;

  
   
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01EventAction::~ExN01EventAction()
{ 
	
}


void ExN01EventAction::BeginOfEventAction(const G4Event* event)
{ 	
    int t0;
    PSD1=0;
	PSD2=0;
	
    //PSD=0;
	//Q_short=0;
	//Q_long=0;
    evt_num++;
	//G4cout<<evt_num<<G4endl;
	evtID = event->GetEventID();
	//G4cout<<evtID<<G4endl;
	if(evtID % 100 == 0)
		cout<<"--------Began of event : "<<evtID<<G4endl;
	fPriPhotonPerEvent=0;
	fPhotonElectron_PMT1=0;
	fPhotonElectron_PMT2=0;
	fTime.clear();
    //T=0;
	PhotonNum_PMT1=0;
	PhotonNum_PMT2=0;
	for(G4int i=0; i<15000; i++)
	{
		PhotonTime1[i]=0;
		PhotonTime2[i]=0;
		PMT1signal[i]=0;
		PMT2signal[i]=0;
	}
	
       
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN01EventAction::EndOfEventAction(const G4Event* event)
{  	 
	
	
   G4int eventNb = event->GetEventID();
   //G4cout<<"Event ID="<<" "<<eventNb<<G4endl;
   /*if(eventNb!=0&&eventNb%9999==0) 
   {fstream effi;
      effi.open("efficiency.txt",ios::app|ios::out);
   effi<<"Event ID="<<eventNb<<" "<<efficiency_num<<" "<<evt_num<<" "<<double(efficiency_num)/double(evt_num)<<G4endl;*/
   //
  
   G4double t0=0.,t_i=0;
   G4int n_PMT1=0;
   G4int n_PMT2=0;
   G4double G;
   G4double flag1=1;
   G4double flag2=flag1;
   if(eventNb == 0)
	{
		
		for(int i=0; i<4000; i++)
		{  
			t_i=i*0.01;
			t0=0;
			jifen=jifen+(t_i-t0)*(t_i-t0)*exp(-(t_i-t0)*(t_i-t0)/(tau*tau))*deltT;//G4cout<<jifen<<G4endl;
		} 
		
			
	
	 }
	for(G4int i=0; i<15000; i++)
	  {  
		if(PhotonTime1[i] > 0)
		  {
			t0=i*0.01;
			n_PMT1=PhotonTime1[i];
			for(G4int m1=i; m1<i+1000; m1++)
			{
				t_i=0.01*m1;
				do
				{G=ExN01EventAction::Gaussian(G0,G0/sqrt(fPhotonElectron_PMT1));}
				while(G<=0);
				PMT1signal[m1]=PMT1signal[m1]+n_PMT1*G*Ce*(t_i-t0)*(t_i-t0)*exp(-(t_i-t0)*(t_i-t0)/(tau*tau))/jifen;
				 
			}
		  }
		
	  }
	 for(G4int i=0; i<15000; i++)
	  {  
		if(PhotonTime2[i] > 0)
		  {
			t0=i*0.01;
			n_PMT2=PhotonTime2[i];
			//G=ExN01EventAction::Gaussian(G0,G0/sqrt(fPhotonElectron_PMT2));
			//G4cout<<G<<endl;
			for(G4int m1=i; m1<i+1000; m1++)
			{
				t_i=0.01*m1;
				do
				{G=ExN01EventAction::Gaussian(G0,G0/sqrt(fPhotonElectron_PMT2));}
				while(G<=0);
				PMT2signal[m1]=PMT2signal[m1]+n_PMT2*G*Ce*(t_i-t0)*(t_i-t0)*exp(-(t_i-t0)*(t_i-t0)/(tau*tau))/jifen;
				 
			}
		  }
		
	  }
	
	//PSD
	//fstream FF;
	//FF.open("inter.txt",ios::app|ios::out);
	if(PhotonNum_PMT1>=1&&PhotonNum_PMT2>=1)
	{
		for(G4int i=0;i<15000;i++)//find trigger
		{
			if(PMT1signal[i]>0)
			{t0=i;break;}
		}
		Q_short=0;
		Q_long=0;//for(T_short=8;T_short<=20;T_short++)
			//for(T_long=20;T_long<=50;T_long++){
				//Q_long=0;
				//Q_short=Q_long;
	for(G4double tt=t0;tt<t0+T_short*100;tt++)
	{Q_short=Q_short+deltT*PMT1signal[tt];}
	//FF<<Q_short<<" ";
	
	for(G4double tt=t0;tt<t0+T_long*100;tt++)
	{Q_long=Q_long+deltT*PMT1signal[tt];}
			
			
 
		
	PSD1=(Q_long-Q_short)/Q_long;
    
	
	
		for(G4int i=0;i<15000;i++)//find trigger
		{
			if(PMT2signal[i]>0)
			{t0=i;break;}
		}
		Q_short=0;
		Q_long=0;
	for(G4double tt=t0;tt<t0+T_short*100;tt++)
	{
		Q_short=Q_short+deltT*PMT2signal[tt];
	}
	for(G4double tt=t0;tt<t0+T_long*100;tt++)
	{
		Q_long=Q_long+deltT*PMT2signal[tt];
	}
	
	PSD2=(Q_long-Q_short)/Q_long;
	
	
	
	
	fstream File_PSD;
	File_PSD.open("PSD.txt",ios::app|ios::out);
	
		File_PSD<<PSD1<<" "<<PSD2<<" "<<G4endl;
	File_PSD.close();
	}
	
	
	
	
	
	//PSD*/
    /*fstream F1,F2;
	F1.open("signalPMT1.txt",ios::app|ios::out);
	F2.open("signalPMT2.txt",ios::app|ios::out);
	for(G4int i=0;i<15000;i++)
	{
		F1<<5.00+(double)i*0.01<<" "<<PMT1signal[i]<<G4endl;
	    F2<<5.00+(double)i*0.01<<" "<<PMT2signal[i]<<G4endl;
	}
	F1.close();
	F2.close();*/
	}
	
	
   
  
  
  
  
  
  
  
  
  
  
  

   
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ExN01EventAction::Gaussian(double mean, double sigma)
{
	static double V1, V2, S;
    static int phase = 0;
    double X;
     
    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;
             
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);
         
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
         
    phase = 1 - phase;
 
    return mean+sigma*X;
}
void ExN01EventAction::Reset()
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
