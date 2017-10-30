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
// $Id: ExN01SteppingAction.cc 71007 2013-06-09 16:14:59Z maire $
//
/// \file ExN01SteppingAction.cc
/// \brief Implementation of the ExN01SteppingAction class
#include "G4UnitsTable.hh"
#include "ExN01SteppingAction.hh"
#include "ExN02RunAction.hh"
#include "ExN01EventAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
//#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
//#include "G4OpBoundaryProcess.hh"

#include <fstream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


ExN01SteppingAction::ExN01SteppingAction(ExN02RunAction* RunAct, ExN01EventAction* EvtAct)
: fRunAction(RunAct),fEventAction(EvtAct)
{ 
fExpectedNextStatus = Undefined;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01SteppingAction::~ExN01SteppingAction()
{ ; }




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN01SteppingAction::UserSteppingAction(const G4Step* theStep)
{  
fstream dataFile1;
fstream dataFile2;
 dataFile1.open("particletime_PMT1.txt",ios::app|ios::out);
 dataFile2.open("particletime_PMT2.txt",ios::app|ios::out);
//if(fEventAction->T==0) {dataFile1<<"======================"<<G4endl;dataFile2<<"======================"<<G4endl;}
	//fEventAction->T=1;
	

  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();
  
  

 

  G4Track* track = theStep->GetTrack();

  G4String ParticleName = track->GetDynamicParticle()->
                                 GetParticleDefinition()->GetParticleName();
 
   G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4OpBoundaryProcess* boundary=NULL;

  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm
      = theStep->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    G4int i;
    for( i=0;i<nprocesses;i++){
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
        boundary = (G4OpBoundaryProcess*)(*pv)[i];
        break;
      }
    }
  }

G4ParticleDefinition* particleType = track->GetDefinition();
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
    //Optical photon only


    boundaryStatus=boundary->GetStatus();
   
   
   
    //Check to see if the partcile was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check
    if(thePostPoint->GetStepStatus()==fGeomBoundary){
    
	 
	
      fExpectedNextStatus=Undefined;
	  
	  
	  
	  /*if(thePostPV->GetName()=="photocathode1_phys")
		 G4cout<<boundaryStatus<<G4endl;*/
	 
	 
	 
    if( boundaryStatus==10)
	{
        if(thePostPV->GetName()=="photocathode1_phys")
     {
        fRunAction->fNum_Pmt1++;
	
		G4double GlobalTime1=thePostPoint->GetGlobalTime()/ns+ExN01SteppingAction::Gaussian(5,2.2/2.355);
		fEventAction->PhotonNum_PMT1++;
		G4int i1 = int(GlobalTime1/0.01)+1; 
	    fEventAction->PhotonTime1[i1]++;   
        fEventAction->fPhotonElectron_PMT1++;		
    
        dataFile1<<fEventAction->evtID<<" "<<GlobalTime1<<G4endl;
        dataFile1.close();
      
     }
     if(thePostPV->GetName()=="photocathode2_phys")
     {
        fRunAction->fNum_Pmt2++;
		
		G4double GlobalTime2=thePostPoint->GetGlobalTime()/ns+ExN01SteppingAction::Gaussian(5,2.2/2.355);
		fEventAction->PhotonNum_PMT2++;
		G4int i2 = int(GlobalTime2/0.01)+1; 
	    fEventAction->PhotonTime2[i2]++;
		fEventAction->fPhotonElectron_PMT2++;
        
        
        dataFile2<<fEventAction->evtID<<" "<<GlobalTime2<<G4endl;
		dataFile2.close();
     }
    }

    }  

}


                                                 
}
double ExN01SteppingAction::Gaussian(double mean, double sigma)
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
