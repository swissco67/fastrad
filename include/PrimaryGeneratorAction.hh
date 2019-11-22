/****************************************************************
* PrimaryGeneratorAction.hh
* Header file for class: PrimaryGeneratorAction
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

#ifndef __PRIMARYGENERATORACTION_H__
#define __PRIMARYGENERATORACTION_H__ 1

#include "G4VUserPrimaryGeneratorAction.hh"

class DetectorConstruction;
class G4GeneralParticleSource;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
   ~PrimaryGeneratorAction();

public:
    void GeneratePrimaries(G4Event*);

private:
    G4GeneralParticleSource* particleGun;
};

#endif
