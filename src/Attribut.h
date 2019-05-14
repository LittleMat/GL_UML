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
using namespace std;
#include "Mesure.h"


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

protected :  
		
		Attribut (string aid, string u, string des);
		// Mode d'emploi :
		//
    	// Contrat :
    	//

 		~Attribut (string aid, string u, string des);
 		// Mode d'emploi :
		//
    	// Contrat :
    	//



//----------------------------------------------------- Protected attributes
protected :

    string attributID;
    string unit;
    string description;

};

#endif // ATTRIBUT_H