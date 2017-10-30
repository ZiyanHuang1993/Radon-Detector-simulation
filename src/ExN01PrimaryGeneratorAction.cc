#include "ExN01DetectorConstruction.hh"
#include "ExN01PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include  "G4IonTable.hh"
//#include<string>
#include<fstream>
using namespace std;

ExN01PrimaryGeneratorAction::ExN01PrimaryGeneratorAction(ExN01DetectorConstruction* DetCons)
:fDetectorConstruction(DetCons)
{
 
 // G4int i=(int)(1000.*G4UniformRand());
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
 
  //switch(i)
  //
      
      
 }//

ExN01PrimaryGeneratorAction::~ExN01PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN01PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	G4ParticleTable* particleTable =G4ParticleTable::GetParticleTable();
	 G4String particleName;
 
  //G4cout<<"alpha generation"<<G4endl;
  
  G4double rndm, rndm2;
  G4double px, py, pz;
  G4double Phi;
  G4double MinPhi =0, MaxPhi=2*M_PI;
  G4double MinTheta=0, MaxTheta=M_PI;
  G4double sintheta, sinphi, costheta, cosphi;
  rndm = G4UniformRand();
  costheta = std::cos(MinTheta) - rndm * (std::cos(MinTheta) - std::cos(MaxTheta));
  sintheta = std::sqrt(1. - costheta*costheta);
  
  rndm2 = G4UniformRand();
  Phi = MinPhi + (MaxPhi - MinPhi) * rndm2; 
  sinphi = std::sin(Phi);
  cosphi = std::cos(Phi);

  px = -sintheta * cosphi;
  py = -sintheta * sinphi;
  pz = -costheta;

  G4double ResMag = std::sqrt((px*px) + (py*py) + (pz*pz));
  px = px/ResMag;
  py = py/ResMag;
  pz = pz/ResMag;
 

  //fParticleGun->SetParticleEnergy(5.59*MeV);
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  G4double r,theta,phi;
 
 G4double x,y,z;
 do{
  phi=G4UniformRand()*M_PI;
  theta=G4UniformRand()*2*M_PI;
  r=sqrt((G4UniformRand()*10));

  z=r*cos(phi);
  x=r*sin(phi)*cos(theta);
  y=r*sin(phi)*sin(theta);
 } 
  while(z>=fDetectorConstruction->Window_Position||y<=(-1)*fDetectorConstruction->Window_Position);
  
  //background position
  G4double r_background,theta_background;
  
  G4double backgroundparticle_x,backgroundparticle_y,backgroundparticle_z;
  do{
  r_background=sqrt((G4UniformRand()*10));
  theta_background=G4UniformRand()*2*M_PI;
  
  backgroundparticle_x=30;
  backgroundparticle_y=r_background*cos(theta_background);
  backgroundparticle_z=r_background*sin(theta_background);
  }
  while(backgroundparticle_z>=fDetectorConstruction->Window_Position||backgroundparticle_y<=(-1)*fDetectorConstruction->Window_Position);
  
  
  randombackground=1;
  //randombackground=G4UniformRand();
   //G4cout<<randombackground<<"-------------"<<G4endl;
 if(randombackground==1)
	 /*if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {  
    G4int Z = 86, A = 222;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;
    
    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
	 fParticleGun->SetParticleCharge(ionCharge);}*/
	 {  G4ParticleDefinition* particle=particleTable->FindParticle(particleName="alpha");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(5.59*MeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  fParticleGun->SetParticlePosition(G4ThreeVector(x*cm,y*cm,z*cm));
  //create vertex
  //   
  
  fParticleGun->GeneratePrimaryVertex(anEvent);
  }
  else if(randombackground==2)
  {
	  
  G4ParticleDefinition* particle=particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(5.59*MeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,0,0));
  fParticleGun->SetParticlePosition(G4ThreeVector(backgroundparticle_x*cm,backgroundparticle_y*cm,backgroundparticle_z*cm));
  //create vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
  } 
  else
  {
  G4ParticleDefinition* particle=particleTable->FindParticle(particleName="gamma");
   fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(5.59*MeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,0,0));
  fParticleGun->SetParticlePosition(G4ThreeVector(backgroundparticle_x*cm,backgroundparticle_y*cm,backgroundparticle_z*cm));
  //create vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
  }
}
	 
	 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 




