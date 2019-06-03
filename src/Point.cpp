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
	// Version 1
	/*
	// Coordonn�es des points dans le domaine cart�sien
	float rayon_Terre = 6371;
	float x = rayon_Terre * cos ( latitude ) * cos ( longitude );
	float y = rayon_Terre * cos ( latitude ) * sin ( longitude );
	float z = rayon_Terre * sin ( latitude );

	float x2 = rayon_Terre * cos ( p -> getLatitude ( ) ) * cos ( p -> getLongitude ( ) );
	float y2 = rayon_Terre * cos ( p -> getLatitude ( ) ) * sin ( p -> getLongitude ( ) );
	float z2 = rayon_Terre * sin ( p -> getLatitude ( ) );

	// Calcul distance
	float x_carre = ( x2 - x ) * ( x2 - x );
	float y_carre = ( y2 - y ) * ( y2 - y );
	float z_carre = ( z2 - z ) * ( z2 - z );
	
	return sqrt( x_carre + y_carre + z_carre);
	*/
	//Version 2
	/*
	double pi = 3.14;
	float R = 6371;
	float latitude1 = this->latitude * pi / 180;
	float latitude2 = p->getLatitude() * pi / 180;
	float longitude1 = this->longitude * pi / 180;
	float longitude2 = p->getLongitude() * pi / 180;

	float distance = R * acos(cos(latitude1)) * cos(latitude2) * cos(longitude2 - longitude1) + sin(latitude1) * sin(latitude2);
	
	return distance;
	*/

	// Version 3 => donne des val similaires que v1 mais toujours pas bonnes 
	/*
	float rayon_Terre = 6371;
	float distance = rayon_Terre * acos(sin(this->latitude) * sin(p->getLatitude()) + cos(this->latitude) * cos(p->getLatitude()) * cos(this->longitude - p->getLongitude()));
	*/
	
	// Version 4
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
	//#ifdef MAP
		cout << "Appel au destructeur de <Point>" << endl;
	//#endif
}//----- End of ~Point 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Protected methods
