/****************************************************************
* VisManager.hh
* Header file for class: VisManager
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

#ifndef __VISMANAGER_H__
#define __VISMANAGER_H__ 1

#include "G4VisManager.hh"

class VisManager : public G4VisManager 
{
public:

    VisManager();

private:

    void RegisterGraphicsSystems();
    void RegisterModelFactories();
};

#endif
