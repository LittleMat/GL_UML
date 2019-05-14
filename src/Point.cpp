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
#include <iostream>
using namespace std;

//------------------------------------------------------ Personnal include
#include "Point.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methods
float Point::getLongitude()
{
	return longitude;
}//----- End of getLongitude 

float Point::getLatitude()
{
	return latitude;
}//----- End of getLatitude

float Point::distance(Point p)
{
	float longt2 = longitude * longitude;
	float lat2 = getLatitude() ^ 2;
	return sqrt(long2 + lat2);

}//----- End of distance 

//-------------------------------------------- Constructor - destructor
Point::Point(float longt, float lat)
// Algorithm : 
{
#ifdef MAP
		cout << "Appel au constructeur de <Point>" << endl;
#endif
	longitude = longt;
	latitude = lat;
}//----- End of Point 

Point::~Point()
// Algorithm : 
{
#ifdef MAP
	cout << "Appel au destructeur de <Point>" << endl;
#endif
}//----- End of ~Point 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Protected methods
