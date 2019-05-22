/*************************************************************************
                           Attribut  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Attribut> (file Attribut.h) ----------------

#if ! defined (ATTRIBUT_H )
#define ATTRIBUT_H

//--------------------------------------------------- Interfaces used
#include <iostream>
#include<string>
using namespace std;
#include "Attribut.h"


//------------------------------------------------------------------------
// Goal of the <Mesure> class
//------------------------------------------------------------------------


class Attribut
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods


	// Mode d'emploi :
	//
    // Contrat :
    //


//-------------------------------------------- Constructor - destructor
	Attribut();
	// Mode d'emploi :
	//
	// Contrat :
	//

	Attribut(std::string attributID, std::string unit, std::string description);
	// Mode d'emploi :
	//
	// Contrat :
	//

	~Attribut();
	// Mode d'emploi :
	//
	// Contrat :
	//

//----------------------------------------------------- Protected attributes
protected :

    std::string attributID;
    std::string unit;
    std::string description;

};

#endif // ATTRIBUT_H