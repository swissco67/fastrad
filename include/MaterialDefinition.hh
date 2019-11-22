/****************************************************************
* MaterialDefinition.hh
* Header file for class: MaterialDefinition
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

#ifndef __MATERIALDEFINITION_H__
#define __MATERIALDEFINITION_H__ 1

#include "globals.hh"
#include <map>
#include <array>

class G4Material;
class G4Element;

class MaterialDefinition
{
public:
     MaterialDefinition();
    ~MaterialDefinition();

	// Create model materials
	void DefineMaterials();

	// Retrieve a material with its UID
	G4Material* GetMaterial(size_t pMaterialUID);

private:
	// Elements sorted by Z
	std::array<G4Element*, 101> mElements; 

	// Models materials
	std::map<unsigned int, G4Material*> mMaterials; 
};
#endif
