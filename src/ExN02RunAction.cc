//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN02RunAction.cc 69899 2013-05-17 10:05:33Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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



