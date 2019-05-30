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
#include "Attribut.h"
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

	//Faire le get du timestamp

	const Attribut * getAttribut() const;

	float getValue() const;

	const std::string getSensorID() const;

	const Capteur * getCapteur() const;


//-------------------------------------------- Constructor - destructor
		
	Mesure (struct tm * timestamp, Attribut * const attribut, float value, const std ::string sensorID, Capteur * capteur);
	// Mode d'emploi :
	//
	// Contrat :
	//

	~Mesure ();
	// Mode d'emploi :
	//
	// Contrat :
	//



//----------------------------------------------------- Protected attributes

protected :
	struct tm * timestamp;
	Attribut * attribut;
	float value;
	std ::string sensorID;
	Capteur * capteur;

};

#endif // MESURE_H