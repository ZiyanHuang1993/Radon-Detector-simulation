#ifndef ExN01PrimaryGeneratorAction_h
#define ExN01PrimaryGeneratorAction_h 1

#include "ExN01DetectorConstruction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class ExN01PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    G4double randombackground;
    ExN01PrimaryGeneratorAction(ExN01DetectorConstruction*);
    ~ExN01PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() { return fParticleGun;} ;
    

  private:
     G4ParticleGun*  fParticleGun;
	 ExN01DetectorConstruction* fDetectorConstruction;
};

#endif


