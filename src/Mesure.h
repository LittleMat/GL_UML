/*************************************************************************
                           Mesure  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Mesure> (file Mesure.h) ----------------

#if ! defined (MESURE_H )
#define MESURE_H

//--------------------------------------------------- Interfaces used
#include <iostream>
using namespace std;
#include <string>
#include "Attribute.h"
#include "Capteur.h"


//------------------------------------------------------------------------
// Goal of the <Mesure> class
//------------------------------------------------------------------------


class Mesure
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
		
		Mesure (Date timestamp, Attribut attribute, int value, const std ::string sensorID)
		// Mode d'emploi :
		//
    	// Contrat :
    	//

 		~Mesure ()
 		// Mode d'emploi :
		//
    	// Contrat :
    	//



//----------------------------------------------------- Protected attributes

protected :
	Date timestamp;
	Attribut attribute;
	int value;
	std ::string sensorID;

};

#endif // MESURE_H