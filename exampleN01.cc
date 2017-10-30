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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  G4MPImanager* g4MPI = new G4MPImanager(argc, argv);
  G4MPIsession* session = g4MPI-> GetMPIsession();


  //Set the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  G4int rank_ = MPI::COMM_WORLD.Get_rank(); //获取并行进程号
  time_t systime = time(NULL);
  G4long seed =systime; // rank_*10.0;
   G4Random::setTheSeed(seed);
  //G4cout<<seed<<"_____________________"<<G4endl;
  

  //
  G4RunManager * runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  //
  ExN01DetectorConstruction* detector = new ExN01DetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  G4VUserPhysicsList* physics = new ExN02PhysicsList;
  runManager->SetUserInitialization(physics);
   
  // User Action classes
  //
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

 

  // Initialize G4 kernel
  //
  runManager->Initialize();
      
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif    
     
  // Get the pointer to the User Interface manager
  //
  G4UImanager * UImanager = G4UImanager::GetUIpointer(); 
  UImanager->ApplyCommand("/run/verbose 0");
  UImanager->ApplyCommand("/event/verbose 0");	 
  UImanager->ApplyCommand("/tracking/verbose 0");

  if (argc!=1)   // batch mode  
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
  else           // interactive mode : define UI session
    { 
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

  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete runManager;


  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


