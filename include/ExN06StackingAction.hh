#ifndef ExN06StackingAction_H
#define ExN06StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "ExN02RunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN06StackingAction : public G4UserStackingAction
{
  public:
    ExN06StackingAction(ExN02RunAction*);
   ~ExN06StackingAction();

  public:
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    void NewStage();
    void PrepareNewEvent();

  private:
    G4int gammaCounter;
    ExN02RunAction* fRunAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

