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
// $Id$
//
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "ExN01DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "ExN01TrackerSD.hh"
#include "G4SDManager.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


ExN01DetectorConstruction::ExN01DetectorConstruction()
 :  experimentalHall_log(0), tracker_log(0),
    calorimeterBlock_log(0), calorimeterLayer_log(0),
    experimentalHall_phys(0), calorimeterLayer_phys(0),
    calorimeterBlock_phys(0), tracker_phys(0)
{;}

ExN01DetectorConstruction::~ExN01DetectorConstruction()
{
}

G4VPhysicalVolume* ExN01DetectorConstruction::Construct()
{
  //Air
  G4bool Overlapp=true;
  G4double a, z, density;
  G4int nelements;
  //G4Material *Teflon=G4NistManager::Instance()->FindOrBuildMaterial("G4_TEFLON");

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);
  
  G4double a2,z2,density2;
  
  G4int natoms;
  
  G4Element* Si =new G4Element("Silicon","Si",z2=14,a2=28.09*g/mole);
  
  G4Material* SiO2 = new G4Material("quartz",density2=2.2*g/cm3,nelements=2);
  SiO2->AddElement(Si,natoms=1);
  SiO2->AddElement(O,natoms=2);
  
  //vacuum
  G4Material *vacuum=G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
   G4Material *Al=G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  
  const G4int nEntries = 52;
  
   G4double photonEnergy[nEntries] =
            { 2.963*eV, 3.053*eV, 3.066*eV, 3.076*eV,
             3.108*eV, 3.114*eV, 3.156*eV, 3.169*eV,
              3.178*eV, 3.189*eV, 3.208*eV, 3.267*eV,
              3.272*eV, 3.281*eV, 3.306*eV, 3.314*eV,
              3.335*eV, 3.353*eV, 3.402*eV, 3.461*eV,
              3.479*eV, 3.483*eV, 3.505*eV, 3.518*eV,
              3.526*eV, 3.554*eV, 3.593*eV, 3.687*eV,
			  3.688*eV, 3.690*eV, 3.692*eV, 3.700*eV,
			  3.725*eV, 3.746*eV, 3.776*eV, 3.792*eV,
              3.816*eV, 3.932*eV, 3.937*eV,	3.939*eV,
              3.944*eV, 3.960*eV, 3.967*eV, 3.982*eV,
              3.994*eV, 4.011*eV, 4.073*eV, 4.121*eV,
              4.166*eV, 4.198*eV, 4.214*eV, 4.291*eV};
//
// 
//
  G4double refractiveIndex1[nEntries] =
            { 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
              1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
              1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
			  1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
			  1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
			  1.0,1.0};
			
  G4double refractiveIndex2[nEntries]=
             {1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
              1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
              1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
			  1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
			  1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
			  1.49,1.49};
			
  G4double absorption[nEntries] =
           {1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,
		    1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,
			1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,
			1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,
			1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,1000*m,
		   1000*m,1000*m};
           //光子在空气中的吸收长度
  G4double scintilFast[nEntries] =
            {  0.00935,0.00234, 0.06308, 0.01168, 0.00234,0.06075,
              0.0257, 0.00701, 0.23364,0.05374, 0.00701, 0.00701, 0.20327,
              0.03738, 0.00701, 0.1285, 0.00701, 0.03271, 0.00467, 0.00234 ,
              0.73598, 0.23598, 0.00935, 0.19393, 0.06542, 0.01636, 0.01168,
			  0.10748, 0.36916, 1.00,0.57944, 0.22196, 0.0257, 0.00935,
			  0.00701, 0.02804, 0.00467, 0.00701, 0.20561, 0.37383, 0.20561,
              0.01636, 0.09579, 0.01869, 0.03972, 0.00935, 0.00467, 0.00467,
			  0.00467, 0.0257, 0.00935,0.00234};
		
  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
  myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex1, nEntries);
  myMPT1->AddProperty("FASTCOMPONENT", photonEnergy, scintilFast, nEntries);
  myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries);
		
		
  myMPT1->AddConstProperty("SCINTILLATIONYIELD",19/MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  myMPT1->AddConstProperty("YIELDRATIO",1.0);


 air->SetMaterialPropertiesTable(myMPT1);
 
 G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
 myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex2, nEntries);
  myMPT2->AddProperty("ABSLENGTH",    photonEnergy, absorption,nEntries);
 SiO2->SetMaterialPropertiesTable(myMPT2);
// 
 //G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();
// myMPT3->AddProperty("RINDEX", photonEnergy, refractiveIndex1, nEntries);
 //myMPT3->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries);
// Al->SetMaterialPropertiesTable(myMPT3);
 
 
  
  
  //world
//------------------------------------------------------ materials
   
  
  G4double x,y,z1;//world
   x=y=z1=50.0*cm;
  G4Box* exphall_Box=new G4Box("exphall_Box",x,y,z1);
  G4LogicalVolume* exphall_log=new G4LogicalVolume(exphall_Box,vacuum,"exphall_log");
  G4VPhysicalVolume* exphall_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,0),exphall_log,"exphall_phys",0,false,0,Overlapp);
    
  //Detect_sphere
  G4double sphere_R=10*cm;
  G4Sphere* Detect_exp=new G4Sphere("Detect_exp",0,sphere_R,0*deg,360*deg,0*deg,360*deg);
  
  /*&G4LogicalVolume* Detect_log
    = new G4LogicalVolume(Detect_exp,air,"Detector_log");


  G4VPhysicalVolume* Detect_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,0),Detect_log,"Detector_phys",exphall_log,false,0);
	*/

	
	
	

	
	
//Detect-Window_Position
  G4double PMT_innerRadius=0*cm;
  G4double PMT_outerRadius=2.3*cm;
  G4double PMT_halfheight=18*mm;
  G4Tubs* PMT1_exp=new G4Tubs("PMT1_exp",PMT_innerRadius,PMT_outerRadius,PMT_halfheight/2,0*deg,360*deg);//PMT1_EXP
  G4Tubs* PMT2_exp=new G4Tubs("PMT1_exp",PMT_innerRadius,PMT_outerRadius,PMT_halfheight/2,0*deg,360*deg);//PMT2_EXP
  Window_Position=sqrt(sphere_R*sphere_R-PMT_outerRadius*PMT_outerRadius);
  
  G4RotationMatrix* xRot=new G4RotationMatrix;
  xRot->rotateX(90.*deg);

  
   G4SubtractionSolid* Detect_Window1_exp=new G4SubtractionSolid("Detect_Window1",Detect_exp,PMT1_exp,0,G4ThreeVector(0,0,Window_Position+PMT_halfheight/2));
   G4SubtractionSolid* Detect_window12_exp=new G4SubtractionSolid("Detect_Window12",Detect_Window1_exp,PMT2_exp,xRot,G4ThreeVector(0,-(Window_Position+PMT_halfheight/2),0));
   
    G4LogicalVolume* Detect_window12_log
    = new G4LogicalVolume(Detect_window12_exp,air,"Detect_window12_log");
	
	G4VPhysicalVolume* Detect_window12_phys
	= new G4PVPlacement(0,G4ThreeVector(0,0,0),Detect_window12_log,"Detect_window12_phys",exphall_log,false,0,Overlapp);
	
//WINDOW1-LOG-PHYS	
  
  G4LogicalVolume* PMT1_log
    = new G4LogicalVolume(PMT1_exp,SiO2,"PMT1_log");
	
  G4VPhysicalVolume* PMT1_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,Window_Position+PMT_halfheight/2),PMT1_log,"PMT1_phys",exphall_log,false,0,Overlapp);
 

//WINDOW2-LOG-PHYS	//rotate


  
  G4LogicalVolume* PMT2_log
    = new G4LogicalVolume(PMT2_exp,SiO2,"PMT2_log");
	
  G4VPhysicalVolume* PMT2_phys
    = new G4PVPlacement(xRot,G4ThreeVector(0,-(Window_Position+PMT_halfheight/2),0),PMT2_log,"PMT2_phys",exphall_log,false,0,Overlapp);
	
	
//photocathode1
G4double photocathode_thickness=1*mm;
G4Tubs* photocathode1_exp=new G4Tubs("photocathode1_exp",PMT_innerRadius,PMT_outerRadius,photocathode_thickness/2,0*deg,360*deg);
G4LogicalVolume* photocathode1_log=new G4LogicalVolume(photocathode1_exp,Al,"photocathode1_log");
G4VPhysicalVolume* photocathode1_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,Window_Position+PMT_halfheight+photocathode_thickness/2),photocathode1_log,"photocathode1_phys",exphall_log,false,0,Overlapp);

//photocathode2
G4Tubs* photocathode2_exp=new G4Tubs("photocathode2_exp",PMT_innerRadius,PMT_outerRadius,photocathode_thickness/2,0*deg,360*deg);
G4LogicalVolume* photocathode2_log=new G4LogicalVolume(photocathode2_exp,Al,"photocathode2_log");
G4VPhysicalVolume* photocathode2_phys
    = new G4PVPlacement(xRot,G4ThreeVector(0,-(Window_Position+PMT_halfheight+photocathode_thickness/2),0),photocathode2_log,"photocathode2_phys",exphall_log,false,0,Overlapp);
  
   
//create optical surface
  G4OpticalSurface* Sphere_Surface = new G4OpticalSurface("detector_surface");
  Sphere_Surface->SetModel(unified);
  Sphere_Surface->SetType(dielectric_dielectric);
  Sphere_Surface->SetFinish(groundfrontpainted);
  
  const G4int num1 = 2;
  G4double ephoton1[num1] = {2.963*eV,4.291*eV};
  G4double reflectivity1[num1] = {0.97,0.97}; 
  G4double efficiency1[num1]={0,0};
  G4MaterialPropertiesTable *myST1 = new G4MaterialPropertiesTable();
  
  
  myST1->AddProperty("REFLECTIVITY", ephoton1, reflectivity1, num1);
  myST1->AddProperty("EFFICIENCY", ephoton1, efficiency1, num1);
  Sphere_Surface->SetMaterialPropertiesTable(myST1);
  
  new G4LogicalBorderSurface("detect_Surface",Detect_window12_phys,exphall_phys,Sphere_Surface);
  
  new G4LogicalBorderSurface("Window1_surface",PMT1_phys,exphall_phys,Sphere_Surface);
  
  new G4LogicalBorderSurface("Window2_surface",PMT2_phys,exphall_phys,Sphere_Surface);
  
  
  
 //create detect_surface 
  G4OpticalSurface* Detect=new G4OpticalSurface("detect_surface");
  Detect->SetModel(unified);
  Detect->SetType(dielectric_metal);
  Detect->SetFinish(ground);
 
  const G4int num = 6;
   //G4double ephoton[num] = {2.034*eV,4.136*eV};
  G4double ephoton[num] = {2.7131*eV, 2.7518*eV, 2.9851*eV, 3.181*eV, 3.5443*eV, 4.1265*eV};
  G4double efficiency[num]   = {0.1563, 0.1695, 0.2167, 0.2425, 0.2823, 0.2971};
 //G4double efficiency[num]   = {1, 1, 1, 1, 1, 1, 1};
  G4double reflectivity[num]   = {0, 0,0,0,0,0};
  //G4double efficiency[num]={1,1,1,1,1,1,1,1,1,1,1};
  G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();
  myST2->AddProperty("REFLECTIVITY", ephoton, reflectivity, num);
  myST2->AddProperty("EFFICIENCY", ephoton, efficiency, num);
  Detect->SetMaterialPropertiesTable(myST2);
  new G4LogicalBorderSurface("photocathode1_surface",PMT1_phys,photocathode1_phys,Detect);
  
 new G4LogicalBorderSurface("photocathode2_surface",PMT2_phys,photocathode2_phys,Detect);
  

  //SD
G4SDManager* SDman = G4SDManager::GetSDMpointer();
  //EJ-200
	G4String trackerSDname = "/mydet/tracker";
	ExN01TrackerSD * trackerSD = new ExN01TrackerSD(trackerSDname);
	SDman->AddNewDetector(trackerSD);
	Detect_window12_log->SetSensitiveDetector(trackerSD);

 
  
  
  
  G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0,1.0)); //cyan
  BoxVisAtt->SetForceSolid(true);
  Detect_window12_log->SetVisAttributes(BoxVisAtt);
  
  G4VisAttributes* BoxVisAtt1= new G4VisAttributes(G4Colour(1.0,0.0,1.0,0.5)); //magenta
  BoxVisAtt1->SetForceSolid(true);
  PMT1_log->SetVisAttributes(BoxVisAtt1);
  
  G4VisAttributes* BoxVisAtt2= new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5)); //green
  BoxVisAtt2->SetForceSolid(true);
  photocathode1_log->SetVisAttributes(BoxVisAtt2);
  
  G4VisAttributes* BoxVisAtt3= new G4VisAttributes(G4Colour(1.0,1.0,0.0,1)); //yellow
  BoxVisAtt3->SetForceSolid(true);
  PMT2_log ->SetVisAttributes(BoxVisAtt3);
  
   G4VisAttributes* BoxVisAtt4= new G4VisAttributes(G4Colour(0.0,1.0,1.0,1)); //blue
  BoxVisAtt4->SetForceSolid(true);
  photocathode2_log ->SetVisAttributes(BoxVisAtt4);
  
  
  
  
  
  
  
  
  
  
   
  //------------------------------------------------------------------

  return exphall_phys;
}

