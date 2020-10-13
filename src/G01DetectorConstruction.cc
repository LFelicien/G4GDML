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
// $Id: G04DetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file G04DetectorConstruction.cc
/// \brief Implementation of the G04DetectorConstruction class
 
#include "G01DetectorConstruction.hh"
//#include "G4SDManager.hh"
#include "G4GDMLParser.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G01DetectorConstruction::G01DetectorConstruction(const G4GDMLParser& parser)
: G4VUserDetectorConstruction(),
  fScoringVolume(0),
   fParser(parser)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* G01DetectorConstruction::Construct()
{
  const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
  G4GDMLAuxMapType::const_iterator sv;
  G4cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;
  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++) 
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end(); vit++)
    {
      G4cout << "--> Type: " << (*vit).type
                << " Value: " << (*vit).value << G4endl;
    }
    if (((*iter).first)->GetName() == "Tracker" ) {//"Tracker"
      sv = iter;
      G4cout << "Scoring Volume set to " << ((*sv).first)->GetName() << G4endl;
    }
  }
  G4cout << G4endl;

  // Set Shape2 as scoring volume
  //
  fScoringVolume = (*sv).first;

  //
  //always return the physical World
  //
  return fParser.GetWorldVolume();                
}




