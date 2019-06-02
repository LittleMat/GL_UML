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
#include <string>
#include "Attribut.h"
#include "Capteur.h"

using namespace std;

//------------------------------------------------------------------------
// Goal of the <Mesure> class
// Représente une mesure, avec un attribut, une valeur, un capteur et un timestamp
//------------------------------------------------------------------------


class Mesure
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods

	//Retourne l'attribut
	const Attribut * getAttribut ( ) const;

	//Retourne la valeur
	float getValue ( ) const;

	//Retourne l'id du capteur de la mesure
	const std :: string getSensorID ( ) const;

	//Retourne le capteur
	const Capteur * getCapteur ( ) const;

	//Retourne le timestamp
	struct tm * getTimestamp ( ) const;


//-------------------------------------------- Constructor - destructor
		
	Mesure ( struct tm * timestamp, Attribut * const attribut, float value, const std :: string sensorID, Capteur * capteur );

	Mesure ( );

	~Mesure ( );


//----------------------------------------------------- Protected attributes

protected :
	struct tm * timestamp;
	Attribut * attribut;
	float value;
	std :: string sensorID;
	Capteur * capteur;

};

#endif // MESURE_H