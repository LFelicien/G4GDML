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
// $Id: G01SteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file G01SteppingAction.cc
/// \brief Implementation of the G01SteppingAction class

#include "G01SteppingAction.hh"
#include "G01EventAction.hh"
#include "G01DetectorConstruction.hh"
#include "HistoManager.hh"
#include <G4Gamma.hh>
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G01SteppingAction::G01SteppingAction(G01EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G01SteppingAction::~G01SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G01SteppingAction::UserSteppingAction(const G4Step* step)
{
G4Track* track = step -> GetTrack();
  G4ParticleDefinition* particule =track -> GetDefinition();//Cette trace correspon da une particule 
 
  if (!fScoringVolume) { 
    const G01DetectorConstruction* detectorConstruction
      = static_cast<const G01DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
   G4double Positiony = step->GetTrack()->GetPosition().y();
   G4double Positionz = step->GetTrack()->GetPosition().z();
    // G4cout<<volume->GetName()<<G4endl;
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //////////////////////////////////////////////////////////////////////
  //secondaries
  //
   //On determine la trace responsable de ce step
  
  G4String Nom =particule -> GetParticleName();
  G4int id = 1;
  
  const std::vector<const G4Track*>* secondary 
                                    = step->GetSecondaryInCurrentStep();    
  for (size_t lp=0; lp<(*secondary).size(); lp++) {
    G4double charge = (*secondary)[lp]->GetDefinition()->GetPDGCharge();
    if (step->GetTrack()->GetParentID()==1 && step->GetTrack()->GetCurrentStepNumber()==1 ){
    
    if (charge != 0.) { id = 6;} else if ((*secondary)[lp]->GetDefinition() == G4Gamma::Definition() ) { id = 7;
   // G4cout<<Nom<<particule->GetPDGCharge()<<G4endl;
     }
    G4double energy = (*secondary)[lp]->GetKineticEnergy();
   //G4double energy =step->GetPreStepPoint()->GetKineticEnergy();
    analysisManager->FillH1(id,energy);
    }}
   

 
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep); 
  //G4cout<<Positiony<<Positionz<<G4endl; 
   analysisManager->FillH1(5,edepStep); 
   analysisManager->FillH2(6,Positiony,Positionz); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

