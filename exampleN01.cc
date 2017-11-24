#include "ExN01DetectorConstruction.hh"
#include "ExN02PhysicsList.hh"
#include "ExN01PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include "ExN02RunAction.hh"
#include "ExN06StackingAction.hh"
#include "ExN01SteppingAction.hh"
#include "ExN01EventAction.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4MPImanager.hh"
#include "G4MPIsession.hh"
#include "G4VMPIseedGenerator.hh"


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


int main(int argc,char** argv)
{
  G4MPImanager* g4MPI = new G4MPImanager(argc, argv);
  G4MPIsession* session = g4MPI-> GetMPIsession();


  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  G4int rank_ = MPI::COMM_WORLD.Get_rank(); 
  time_t systime = time(NULL);
  G4long seed =systime; 
   G4Random::setTheSeed(seed);
  
  
  G4RunManager * runManager = new G4RunManager;

  ExN01DetectorConstruction* detector = new ExN01DetectorConstruction;
  runManager->SetUserInitialization(detector);
  
  G4VUserPhysicsList* physics = new ExN02PhysicsList;
  runManager->SetUserInitialization(physics);
   
  G4VUserPrimaryGeneratorAction* gen_action = new ExN01PrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  
  ExN01PrimaryGeneratorAction* PG_action=new ExN01PrimaryGeneratorAction(detector);
  runManager->SetUserAction(PG_action);
  
  ExN02RunAction* R_action = new ExN02RunAction();
  runManager->SetUserAction(R_action);
  
  ExN01EventAction* evtAction = new ExN01EventAction(R_action,PG_action);
  runManager->SetUserAction(evtAction);
 
  runManager->SetUserAction(new ExN01SteppingAction(R_action,evtAction));

  runManager->SetUserAction(new ExN06StackingAction(R_action));
  
  runManager->Initialize();
      
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif    

  G4UImanager * UImanager = G4UImanager::GetUIpointer(); 
  UImanager->ApplyCommand("/run/verbose 0");
  UImanager->ApplyCommand("/event/verbose 0");	 
  UImanager->ApplyCommand("/tracking/verbose 0");

  if (argc!=1)  
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
  else      
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute run.mac");    
#endif
      ui->SessionStart();
      delete ui;
#endif
     
#ifdef G4VIS_USE
      delete visManager;
#endif     
    }

  delete runManager;


  return 0;
}
