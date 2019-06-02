/*************************************************************************
Territoire  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Territoire> (file Territoire.h) ----------------
#if ! defined ( TERRITOIRE_H )
#define TERRITOIRE_H

//--------------------------------------------------- Interfaces used
#include <iostream>

#include "Point.h"

using namespace std;

//------------------------------------------------------------------------
// Goal of the <Territoire> class
// Territoire représente un territoire de centre centre et de rayon rayon.
//------------------------------------------------------------------------


class Territoire
{
	//----------------------------------------------------------------- PUBLIC

public:

	//----------------------------------------------------- Public methods
	//Retourne le centre
	const Point * getCentre ( ) const;

	//Retourne le rayon
	int getRayon ( ) const;

	//Retourne vrai si le territoire contient p
	bool contient ( const Point * p ) const;

	//-------------------------------------------- Constructor - destructor
	Territoire ( Point * c, int r );

	Territoire ( );

	~Territoire ( );

protected:
	//----------------------------------------------------- Protected attributes
	Point * centre;
	int rayon;

};

#endif // TERRITOIRE_H
