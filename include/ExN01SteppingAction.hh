#ifndef ExN01SteppingAction_h
#define ExN01SteppingAction_h 1
#include "ExN01EventAction.hh"
#include "ExN02RunAction.hh"
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4OpBoundaryProcess.hh"

/// Stepping action class
/// 

class ExN01SteppingAction : public G4UserSteppingAction
{
  public:
    ExN01SteppingAction(ExN02RunAction*, ExN01EventAction* );
 
    virtual ~ExN01SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    
    ExN02RunAction* fRunAction;
     G4OpBoundaryProcessStatus fExpectedNextStatus;
	 ExN01EventAction* fEventAction;
	 double Gaussian(G4double, G4double);
	 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
