/*************************************************************************
                           Capteur  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Capteur> (file Capteur.h) ----------------
#ifndef CAPTEUR_H
#define CAPTEUR_H

//--------------------------------------------------- Interfaces used
#include <string>
#include "Point.h"

//------------------------------------------------------------------------
// Goal of the <Capteur> class
// Un objet Capteur eprésente un capteur, avec un id, une position et une description
//------------------------------------------------------------------------


class Capteur
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods

	/*
	* Retourne l'id du capteur
	*/
	const std::string getSensorID() const;

	/*
	* Retourne la position du capteur
	*/
	const Point * getPosition() const;

	/*
	* Retourne la description du capteur
	*/
	const std::string getDescription() const;

//-------------------------------------------- Constructor - destructor

	Capteur ( const std :: string sensorID, Point * position, const std :: string description );
	
	Capteur ( );

	~Capteur ( );

protected :

//----------------------------------------------------- Protected attributes
	std :: string sensorID;
	Point * position;
	std :: string description;
};

#endif // CAPTEUR_H