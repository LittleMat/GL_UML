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
#include <ctime>

using namespace std;

//------------------------------------------------------------------------
// Goal of the <Mesure> class
// Un objet <Mesure> représente une mesure, avec un attribut, une valeur, un capteur et un timestamp
//------------------------------------------------------------------------


class Mesure
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods

	/*
	* Retourne l'attribut
	*/
	string getAttributID () const;

	/*
	* Retourne la valeur
	*/
	float getValue ( ) const;

	/* 
	* Retourne l'id du capteur de la mesure
	*/
	string getSensorID ( ) const;

	/*
	* Retourne le timestamp
	*/
	struct tm getTimestamp ( ) const;


//-------------------------------------------- Constructor - destructor
		
	Mesure ( const struct tm& timestamp, const string& attributID, float value, const string& sensorID);

	Mesure ( );

	~Mesure ( );

//----------------------------------------------------------------- PROTECTED

protected :

//----------------------------------------------------- Protected attributes
	struct tm timestamp;
	string attributID;
	float value;
	string sensorID;
};

#endif // MESURE_H