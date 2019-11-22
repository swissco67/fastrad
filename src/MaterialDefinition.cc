/****************************************************************
* MaterialDefinition.cc
* Implementation file for class: MaterialDefinition
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


#include "MaterialDefinition.hh"

#include "G4ios.hh"
#include "G4Element.hh"
#include "G4Material.hh"
 
MaterialDefinition::MaterialDefinition()
{
	// Instanciate elements list
	this->mElements = { nullptr, 
		new G4Element("hydrogen", "H", 1, 1.007940*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("helium", "He", 2, 4.002602*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("lithium", "Li", 3, 6.941000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("beryllium", "Be", 4, 9.012182*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("boron", "B", 5, 10.811000*CLHEP::g/CLHEP::mole),
		new G4Element("carbon", "C", 6, 12.010700*CLHEP::g/CLHEP::mole),
		new G4Element("nitrogen", "N", 7, 14.007000*CLHEP::g/CLHEP::mole),
		new G4Element("oxygen", "O", 8, 15.999400*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("fluorine", "F", 9, 18.998403*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("neon", "Ne", 10, 20.179700*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("sodium", "Na", 11, 22.989769*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("magnesium", "Mg", 12, 24.305000*CLHEP::g/CLHEP::mole),
		new G4Element("aluminum", "Al", 13, 26.981539*CLHEP::g/CLHEP::mole),
		new G4Element("silicon", "Si", 14, 28.085500*CLHEP::g/CLHEP::mole),
		new G4Element("phosphorus", "P", 15, 30.973760*CLHEP::g/CLHEP::mole),
		new G4Element("sulfur", "S", 16, 32.065000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("chlorine", "Cl", 17, 35.453000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("argon", "Ar", 18, 39.948000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("potassium", "K", 19, 39.098300*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("calcium", "Ca", 20, 40.078000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("scandium", "Sc", 21, 44.955912*CLHEP::g/CLHEP::mole),
		new G4Element("titanium", "Ti", 22, 47.867000*CLHEP::g/CLHEP::mole),
		new G4Element("vanadium", "V", 23, 50.941500*CLHEP::g/CLHEP::mole),
		new G4Element("chromium", "Cr", 24, 51.996100*CLHEP::g/CLHEP::mole),
		new G4Element("manganese", "Mn", 25, 54.938045*CLHEP::g/CLHEP::mole),
		new G4Element("iron", "Fe", 26, 55.845000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("cobalt", "Co", 27, 58.933195*CLHEP::g/CLHEP::mole),
		new G4Element("nickel", "Ni", 28, 58.693400*CLHEP::g/CLHEP::mole),
		new G4Element("copper", "Cu", 29, 63.546000*CLHEP::g/CLHEP::mole),
		new G4Element("zinc", "Zn", 30, 65.380000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("gallium", "Ga", 31, 69.723000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("germanium", "Ge", 32, 72.640000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("arsenic", "As", 33, 74.921600*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("selenium", "Se", 34, 78.960000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("bromine", "Br", 35, 79.904000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("krypton", "Kr", 36, 83.798000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("rubidium", "Rb", 37, 85.467800*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("strontium", "Sr", 38, 87.620000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("yttrium", "Y", 39, 88.905850*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("zirconium", "Zr", 40, 91.224000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("niobium", "Nb", 41, 92.906380*CLHEP::g/CLHEP::mole),
		new G4Element("molybdenum", "Mo", 42, 95.960000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("technetium", "Tc", 43, 98.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("ruthenium", "Ru", 44, 101.070000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("rhodium", "Rh", 45, 102.905500*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("palladium", "Pd", 46, 106.420000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("silver", "Ag", 47, 107.868200*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("cadmium", "Cd", 48, 112.411000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("indium", "In", 49, 114.818000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("tin", "Sn", 50, 118.710000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("antimony", "Sb", 51, 121.760000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("tellurium", "Te", 52, 127.600000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("iodine", "I", 53, 126.904470*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("xenon", "Xe", 54, 131.293000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("cesium", "Cs", 55, 132.905452*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("barium", "Ba", 56, 137.327000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("lanthanum", "La", 57, 138.905470*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("cerium", "Ce", 58, 140.116000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("praseodymium", "Pr", 59, 140.907650*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("neodymium", "Nd", 60, 144.242000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("promethium", "Pm", 61, 145.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("samarium", "Sm", 62, 150.360000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("europium", "Eu", 63, 151.964000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("gadolinium", "Gd", 64, 157.250000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("terbium", "Tb", 65, 158.925350*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("dysprosium", "Dy", 66, 162.500000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("holmium", "Ho", 67, 164.930320*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("erbium", "Er", 68, 167.259000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("thulium", "Tm", 69, 168.934100*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("ytterbium", "Yb", 70, 173.054000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("lutetium", "Lu", 71, 174.966800*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("hafnium", "Hf", 72, 178.490000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("tantalum", "Ta", 73, 180.947880*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("wolfram", "W", 74, 183.840000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("rhenium", "Re", 75, 186.207000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("osmium", "Os", 76, 190.230000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("iridium", "Ir", 77, 192.217000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("platinum", "Pt", 78, 195.084000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("gold", "Au", 79, 196.966569*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("mercury", "Hg", 80, 200.590000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("thallium", "Tl", 81, 204.383300*CLHEP::g/CLHEP::mole),
		new G4Element("lead", "Pb", 82, 207.200000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("bismuth", "Bi", 83, 208.980400*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("polonium", "Po", 84, 209.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("astatine", "At", 85, 210.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("radon", "Rn", 86, 222.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("francium", "Fr", 87, 223.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("radium", "Ra", 88, 226.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("actinium", "Ac", 89, 227.000000*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("thorium", "Th", 90, 232.038060*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("protactinium", "Pa", 91, 231.035880*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("uranium", "U", 92, 238.028910*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("neptunium", "Np", 93, 237.048166*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("plutonium", "Pu", 94, 244.064197*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("americium", "Am", 95, 243.061372*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("curium", "Cm", 96, 247.070346*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("berkelium", "Bk", 97, 247.070298*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("californium", "Cf", 98, 251.079579*CLHEP::g/CLHEP::mole),
		nullptr, // new G4Element("einsteinium", "Es", 99, 252.082970*CLHEP::g/CLHEP::mole),
	}; 
}; 


MaterialDefinition::~MaterialDefinition()
{
	// Delete elements list
 	for (size_t lIdx = 1; lIdx < 100; ++lIdx)
 	{
 		delete this->mElements[lIdx] ;
	}
 }

void MaterialDefinition::DefineMaterials()
{
	G4Material* lMaterial = nullptr;

//-------------------------------------------------------------------------
// Define vacuum

	lMaterial = new G4Material("Vacuum", 1., 1.000000*CLHEP::g/CLHEP::mole, 1.0e-25*CLHEP::g/CLHEP::cm3);
	this->mMaterials[0] = lMaterial; 

//-------------------------------------------------------------------------
// Define materials

	// Material : silicon, UID : 1
	lMaterial = new G4Material("silicon", 2.330000*CLHEP::g/CLHEP::cm3, 1);
	lMaterial->AddElement(this->mElements[14], 100.000000*CLHEP::perCent); // Si 
	this->mMaterials[1] = lMaterial; 

	// Material : NICKEL-IRON (Invar), UID : 2
	lMaterial = new G4Material("NICKEL-IRON (Invar)", 8.100000*CLHEP::g/CLHEP::cm3, 2);
	lMaterial->AddElement(this->mElements[28], 36.000000*CLHEP::perCent); // Ni 
	lMaterial->AddElement(this->mElements[26], 64.000000*CLHEP::perCent); // Fe 
	this->mMaterials[2] = lMaterial; 

	// Material : SiC, UID : 3
	lMaterial = new G4Material("SiC", 3.000000*CLHEP::g/CLHEP::cm3, 2);
	lMaterial->AddElement(this->mElements[6], 29.954700*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[14], 70.045300*CLHEP::perCent); // Si 
	this->mMaterials[3] = lMaterial; 

	// Material : Fused SILICA, UID : 4
	lMaterial = new G4Material("Fused SILICA", 2.200000*CLHEP::g/CLHEP::cm3, 2);
	lMaterial->AddElement(this->mElements[8], 53.256500*CLHEP::perCent); // O 
	lMaterial->AddElement(this->mElements[14], 46.743500*CLHEP::perCent); // Si 
	this->mMaterials[4] = lMaterial; 

	// Material : STEEL_STAINLESS_316, UID : 5
	lMaterial = new G4Material("STEEL_STAINLESS_316", 8.000000*CLHEP::g/CLHEP::cm3, 9);
	lMaterial->AddElement(this->mElements[6], 0.041000*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[14], 0.507000*CLHEP::perCent); // Si 
	lMaterial->AddElement(this->mElements[15], 0.023000*CLHEP::perCent); // P 
	lMaterial->AddElement(this->mElements[16], 0.015000*CLHEP::perCent); // S 
	lMaterial->AddElement(this->mElements[24], 17.000000*CLHEP::perCent); // Cr 
	lMaterial->AddElement(this->mElements[25], 1.014000*CLHEP::perCent); // Mn 
	lMaterial->AddElement(this->mElements[26], 66.900000*CLHEP::perCent); // Fe 
	lMaterial->AddElement(this->mElements[28], 12.000000*CLHEP::perCent); // Ni 
	lMaterial->AddElement(this->mElements[42], 2.500000*CLHEP::perCent); // Mo 
	this->mMaterials[5] = lMaterial; 

	// Material : Aluminium_Alloy 6061-T651, UID : 6
	lMaterial = new G4Material("Aluminium_Alloy 6061-T651", 2.700000*CLHEP::g/CLHEP::cm3, 1);
	lMaterial->AddElement(this->mElements[13], 100.000000*CLHEP::perCent); // Al 
	this->mMaterials[6] = lMaterial; 

	// Material : TITANIUM_ALLOY_GRADE_5, UID : 7
	lMaterial = new G4Material("TITANIUM_ALLOY_GRADE_5", 4.430000*CLHEP::g/CLHEP::cm3, 8);
	lMaterial->AddElement(this->mElements[1], 0.011000*CLHEP::perCent); // H 
	lMaterial->AddElement(this->mElements[6], 0.057000*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[7], 0.021000*CLHEP::perCent); // N 
	lMaterial->AddElement(this->mElements[8], 0.141000*CLHEP::perCent); // O 
	lMaterial->AddElement(this->mElements[13], 6.125000*CLHEP::perCent); // Al 
	lMaterial->AddElement(this->mElements[22], 89.363000*CLHEP::perCent); // Ti 
	lMaterial->AddElement(this->mElements[23], 4.000000*CLHEP::perCent); // V 
	lMaterial->AddElement(this->mElements[26], 0.283000*CLHEP::perCent); // Fe 
	this->mMaterials[7] = lMaterial; 

	// Material : KAPTON_FILM, UID : 8
	lMaterial = new G4Material("KAPTON_FILM", 1.420000*CLHEP::g/CLHEP::cm3, 4);
	lMaterial->AddElement(this->mElements[1], 2.636200*CLHEP::perCent); // H 
	lMaterial->AddElement(this->mElements[6], 69.113300*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[7], 7.327000*CLHEP::perCent); // N 
	lMaterial->AddElement(this->mElements[8], 20.923500*CLHEP::perCent); // O 
	this->mMaterials[8] = lMaterial; 

	// Material : POLYIMIDE, UID : 9
	lMaterial = new G4Material("POLYIMIDE", 1.420000*CLHEP::g/CLHEP::cm3, 4);
	lMaterial->AddElement(this->mElements[1], 2.636000*CLHEP::perCent); // H 
	lMaterial->AddElement(this->mElements[6], 69.113000*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[7], 7.733000*CLHEP::perCent); // N 
	lMaterial->AddElement(this->mElements[8], 20.518000*CLHEP::perCent); // O 
	this->mMaterials[9] = lMaterial; 

	// Material : STEEL_STAINLESS_409, UID : 10
	lMaterial = new G4Material("STEEL_STAINLESS_409", 7.800000*CLHEP::g/CLHEP::cm3, 8);
	lMaterial->AddElement(this->mElements[6], 0.079000*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[14], 0.983000*CLHEP::perCent); // Si 
	lMaterial->AddElement(this->mElements[15], 0.044000*CLHEP::perCent); // P 
	lMaterial->AddElement(this->mElements[16], 0.044000*CLHEP::perCent); // S 
	lMaterial->AddElement(this->mElements[22], 0.737000*CLHEP::perCent); // Ti 
	lMaterial->AddElement(this->mElements[24], 11.130000*CLHEP::perCent); // Cr 
	lMaterial->AddElement(this->mElements[25], 0.983000*CLHEP::perCent); // Mn 
	lMaterial->AddElement(this->mElements[26], 86.000000*CLHEP::perCent); // Fe 
	this->mMaterials[10] = lMaterial; 

	// Material : MOLYBDENUM, UID : 11
	lMaterial = new G4Material("MOLYBDENUM", 10.220000*CLHEP::g/CLHEP::cm3, 1);
	lMaterial->AddElement(this->mElements[42], 100.000000*CLHEP::perCent); // Mo 
	this->mMaterials[11] = lMaterial; 

	// Material : BRASS, UID : 12
	lMaterial = new G4Material("BRASS", 8.489000*CLHEP::g/CLHEP::cm3, 3);
	lMaterial->AddElement(this->mElements[29], 61.500000*CLHEP::perCent); // Cu 
	lMaterial->AddElement(this->mElements[30], 35.240000*CLHEP::perCent); // Zn 
	lMaterial->AddElement(this->mElements[82], 3.252000*CLHEP::perCent); // Pb 
	this->mMaterials[12] = lMaterial; 

	// Material : Polybutylene Terephthalate, UID : 13
	lMaterial = new G4Material("Polybutylene Terephthalate", 1.310000*CLHEP::g/CLHEP::cm3, 3);
	lMaterial->AddElement(this->mElements[1], 5.492300*CLHEP::perCent); // H 
	lMaterial->AddElement(this->mElements[6], 65.447100*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[8], 29.060600*CLHEP::perCent); // O 
	this->mMaterials[13] = lMaterial; 

	// Material : Ryton, UID : 14
	lMaterial = new G4Material("Ryton", 1.440000*CLHEP::g/CLHEP::cm3, 3);
	lMaterial->AddElement(this->mElements[1], 3.727600*CLHEP::perCent); // H 
	lMaterial->AddElement(this->mElements[6], 66.626800*CLHEP::perCent); // C 
	lMaterial->AddElement(this->mElements[16], 29.645600*CLHEP::perCent); // S 
	this->mMaterials[14] = lMaterial; 

//-------------------------------------------------------------------------
// Print all the materials defined.
/*
    G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
*/
}

G4Material* MaterialDefinition::GetMaterial(size_t pMaterialUID)
{
	// Search in hash map
	std::map<unsigned int, G4Material*>::iterator lMatIt = this->mMaterials.find(pMaterialUID);
	// Valid entry ?
	if (lMatIt != this->mMaterials.end())
	{
		return lMatIt->second;
	}
	return nullptr;}
