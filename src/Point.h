/*************************************************************************
Point  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Point> (file Point.h) ----------------
#if ! defined ( POINT_H )
#define POINT_H

//--------------------------------------------------- Interfaces used
#include <iostream>
#include <math.h>
using namespace std;
const static double RAYON_TERRE = 6378;
//------------------------------------------------------------------------
// Goal of the <Point> class
// Un objet <Point> représente un point aux coordonnées latitude longitude
//------------------------------------------------------------------------


class Point
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Public methods

	/*
	* Retourne la longitude
	*/
	float getLongitude ( ) const;

	/*
	* Retourne la latitude
	*/
	float getLatitude ( ) const;
	
	/*
	* Retourne la distance
	*/
	float distance ( const Point * p ) const;

//-------------------------------------------- Constructor - destructor
	Point ( float longt, float lat );

	Point();

	~Point ( );
	
//----------------------------------------------------------------- PROTECTED

protected:

//----------------------------------------------------- Protected attributes
	float longitude;
	float latitude;

};

#endif // POINT_H
