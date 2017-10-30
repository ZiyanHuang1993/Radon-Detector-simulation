#include "ExN02RunAction.hh"
#include "G4Run.hh"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
//#include <string>
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02RunAction::ExN02RunAction()
{
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02RunAction::~ExN02RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  
  		
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02RunAction::EndOfRunAction(const G4Run*)
{ 
	fstream dataFile,file;
    dataFile.open("DetectEfficiency.txt",ios::app|ios::out);
	//file.open("psd.txt",ios::app|ios::out);
    dataFile<<"PMT1:"<<fNum_Pmt1<<G4endl;
    dataFile<<"PMT2:"<<fNum_Pmt2<<G4endl;
    dataFile<<"total count:"<<gammaCounter<<G4endl;
    dataFile<<"detect efficiency="<<fNum_Pmt1*1.0/gammaCounter<<" "<<fNum_Pmt2*1.0/gammaCounter<<" "<<fNum_Pmt1*1.0/gammaCounter+fNum_Pmt2*1.0/gammaCounter<<G4endl;

	dataFile.close();
	
	/*int n = 0;
	int count[110][110];
	for (int i = 0; i < 110; i++)
		for (int j = 0; j < 110; j++)
			count[i][j] = 0;
	fstream f1, f2;
	double num[2];
	f1.open("PSD.txt", ios::app | ios::in);
	f2.open("count.txt", ios::app | ios::out);
	while (!f1.eof())
	{
		f1 >> num[0];
		f1 >> num[1];
		int a = (int)(num[0] / 0.01) + 1;
		int b = (int)(num[1]/ 0.01) + 1;
		count[a][b]++;
		n++;
	}
	f1.close();
	for (int i = 0; i < 110; i++)
		for (int j = 0; j < 110; j++)
			f2 << 0.001*(double)i<<" " <<0.001*double(j) << " " << count[i][j] << endl;
	f2.close();*/
	
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



