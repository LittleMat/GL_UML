/*************************************************************************
Point  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Point> (file Point.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

//------------------------------------------------------ Personnal include
#include "Point.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methods
float Point :: getLongitude ( ) const
{
	return longitude;
}//----- End of getLongitude 

float Point :: getLatitude ( ) const
{
	return latitude;
}//----- End of getLatitude

float Point :: distance( const Point * p ) const
{
	if (p == nullptr)
		throw "Illegal Argument Exception";

	double R = 6371;
	double latitude1 = this->latitude * M_PI / 180;
	double latitude2 = p->getLatitude() * M_PI / 180;
	double longitude1 = this->longitude * M_PI / 180;
	double longitude2 = p->getLongitude() * M_PI / 180;

	double distance = R * acos(sin(latitude1) * sin(latitude2) + cos(latitude1) * cos(latitude2) * cos(longitude1 - longitude2));

	return (float)distance;

}//----- End of distance 

//-------------------------------------------- Constructor - destructor
/*Point :: Point ( )
// Algorithm : 
{
	#ifdef MAP
		cout << "Appel au constructeur par d�faut de <Point>" << endl;
	#endif

	longitude = 0.0;
	latitude = 0.0;
}//----- End of Point */

Point :: Point ( float longt, float lat )
// Algorithm : 
{
	#ifdef MAP
			cout << "Appel au constructeur de <Point>" << endl;
	#endif
	if (longt < -180 || longt > 180 || lat < -90 || lat > 90)
		throw "Illegal Argument Exception";
	longitude = longt;
	latitude = lat;
}//----- End of Point 

Point :: ~Point ( )
// Algorithm : 
{
	#ifdef MAP
		cout << "Appel au destructeur de <Point>" << endl;
	#endif
}//----- End of ~Point 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Protected methods
