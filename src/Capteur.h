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
//
//------------------------------------------------------------------------


class Capteur
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods

//-------------------------------------------- Constructor - destructor
	/*
	 *	
	 */
	Capteur ( const std :: string & sensorID, const Point & position, const std :: string & description);

	/*
	 *	
	 */
	~Capteur ( );

protected :

//----------------------------------------------------- Protected attributes
	std :: string sensorID;
	Point position;
	std :: string description;
};

#endif // CAPTEUR_H