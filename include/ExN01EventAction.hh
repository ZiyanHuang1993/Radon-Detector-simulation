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
// $Id$
//
/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef ExN01EventAction_h
#define ExN01EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "ExN02RunAction.hh"
#include "ExN01PrimaryGeneratorAction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"


#include <vector>
class ExN01SteppingAction;

using namespace std;
/// Event action class
///
/// It holds data member fEnergySum and fEnergy2Sum for accumulating 
/// the event energy deposit its square event by event.
/// These data are then used in the run action to compute the dose.
/// The accumulated energy and enrgy square sums are reset for each 
/// new run via the Reset() function from the run action.

class ExN01EventAction : public G4UserEventAction
{
  public:
	ExN01EventAction(ExN02RunAction*,ExN01PrimaryGeneratorAction*);
	virtual ~ExN01EventAction();
    


    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void Reset();
	
	vector<G4double> fTime;
	vector<G4int> PhotonTime1;
	vector<G4int> PhotonTime2;
    G4int fPriPhotonPerEvent;
	G4int fPhotonElectron_PMT1;
	G4int fPhotonElectron_PMT2;
	//G4double PhotonTime_evt;
	G4int PhotonNum_PMT1;
	G4int PhotonNum_PMT2;
	G4int evt_num;
	G4int evtID;
	//G4int T;
  
	G4int efficiency_num;
  private:
   
   G4double T_short;
	G4double T_long;
    G4double PSD1,PSD2,Q_short,Q_long;
	vector<G4double> PMT1signal;
	vector<G4double> PMT2signal;
    G4double jifen;
    G4double G0,Ce,tau,deltT;
	//G4double Time_Short,Time_Long;
	double Gaussian(G4double, G4double);
	ExN02RunAction* fRunAction;
	ExN01PrimaryGeneratorAction* fPriAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
