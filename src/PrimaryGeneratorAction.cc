/****************************************************************
* PrimaryGeneratorAction.cc
* Implementation file for class: PrimaryGeneratorAction
* (Geant4 compatible class)
*
* Project: Ht
*
*
* Neither the authors of this software system, nor their employing 
* institutes,nor the agencies providing financial support for this 
* work  make  any representation or  warranty, express or implied, 
* regarding  this  software system or assume any liability for its 
* use.                                                             
*
*
* Creation: 2019/11/22 by Fastrad ((C) 2019)
* Last Modified: 
*****************************************************************/

#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"

//extern G4String particleType_;
//extern G4double incidentEnergy_;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
//    G4int n_particle = 1;
    particleGun = new G4GeneralParticleSource();
/*
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(particleType_);

    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0.000000, 0.000000, 1.000000));
    particleGun->SetParticleEnergy(incidentEnergy_*MeV);
*/}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
/*
    G4double x0 = 0.000000*mm;
    G4double y0 = 0.000000*mm;
    G4double z0 = 0.000000*mm;

    G4double GPS.posX = x0;
    G4double GPS.posY = y0;
    G4double GPS.posZ = z0;

    G4ThreeVector positionGun = G4ThreeVector(posX, posY, posZ);

    particleGun->SetParticlePosition(positionGun);
*/
//--------------------------------------------------------------------------

    particleGun->GeneratePrimaryVertex(anEvent);

//--------------------------------------------------------------------------
}
