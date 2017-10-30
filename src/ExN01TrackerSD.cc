#include "ExN01TrackerSD.hh"
#include "ExN01TrackerHit.hh"
#include "G4Step.hh"
#include "G4TrackStatus.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
double gaussrand(); 
ExN01TrackerSD::ExN01TrackerSD(G4String name)
:G4VSensitiveDetector(name)
{
	eventID = 0;
	G4String HCname;
	collectionName.insert(HCname="trackerCollection");

}

ExN01TrackerSD::~ExN01TrackerSD(){;}

void ExN01TrackerSD::Initialize(G4HCofThisEvent* HCE)
{
         eventID++;
         //if(eventID/1000==0)
           //G4cout<<"The No of event = "<<eventID<<G4endl;
	static int HCID = -1;

	trackerCollection = new ExN01TrackerHitsCollection(SensitiveDetectorName,collectionName[0]); 
  
					  

	if(HCID<0)
	{ HCID = GetCollectionID(0); }
	HCE->AddHitsCollection(HCID,trackerCollection);


}

G4bool ExN01TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	G4double edep = 0,gtime=0;
	G4Track * theTrack = aStep->GetTrack(); 
	G4String particleName = theTrack->GetDefinition()->GetParticleName();
	if(particleName == "alpha")
	{
		edep=aStep->GetTotalEnergyDeposit();
	 gtime=aStep->GetTrack()->GetGlobalTime();
	}

	ExN01TrackerHit* newHit = new ExN01TrackerHit();
	newHit->SetEdep( edep );
	newHit->SetGlobalTime(gtime);
	trackerCollection->insert( newHit );

  return true;
}

void ExN01TrackerSD::EndOfEvent(G4HCofThisEvent*)
{      
	fstream dataFile;
    dataFile.open("energyDeposit.txt",ios::app|ios::out);
    eventID=eventID+1;
    //dataFile<<eventID<<" ";
	//G4cout<<eventID<<G4endl;
	 if (trackerCollection)//判断是否有数据
    {
			G4double energy=0,globaltime=0;
			int numberHits= trackerCollection->entries();//取得数据个数
			for (int j= 0; j < numberHits; j++)
			{
				ExN01TrackerHit* hit= (*trackerCollection)[j];
				globaltime=hit ->GetGlobalTime();
				energy += hit ->GetEdep()/MeV;//累加各Step沉积能量
				if(globaltime==0)
				{
					if(energy>0)
						dataFile<<energy<<G4endl;
					energy = 0;		
				}				
			}
			  			
      }
   // dataFile<<G4endl;
	dataFile.close();
       
 }   


void ExN01TrackerSD::clear()
{
} 

void ExN01TrackerSD::DrawAll()
{
} 

void ExN01TrackerSD::PrintAll()
{
} 
