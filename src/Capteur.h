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

#include <string>
#include "Point.h"

//------------------------------------------------------------------------
// Goal of the <Capteur> class
// Représente un capteur, avec un id, une position et une description
//------------------------------------------------------------------------


class Capteur
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods

//-------------------------------------------- Constructor - destructor

	//Retourne l'id du capteur
	const std :: string getSensorID ( ) const;

	//Retourne sa position
	const Point * getPosition ( ) const;

	//Retourne sa description
	const std :: string getDescription ( ) const;
	
	/*
	 *	
	 */
	Capteur ( const std :: string sensorID, Point * position, const std :: string description );
	
	Capteur ( );

	/*s
	 *	
	 */
	~Capteur ( );

protected :

//----------------------------------------------------- Protected attributes
	std :: string sensorID;
	Point * position;
	std :: string description;
};

#endif // CAPTEUR_H