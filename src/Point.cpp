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
#include <math.h>

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
	// Coordonnées des points dans le domaine cartésien
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
	
	return sqrt( x_carre + y_carre + z_carre );
		

}//----- End of distance 

//-------------------------------------------- Constructor - destructor
Point :: Point ( )
// Algorithm : 
{
	#ifdef MAP
		cout << "Appel au constructeur par défaut de <Point>" << endl;
	#endif

	longitude = 0.0;
	latitude = 0.0;
}//----- End of Point 

Point :: Point ( float longt, float lat )
// Algorithm : 
{
	#ifdef MAP
			cout << "Appel au constructeur de <Point>" << endl;
	#endif

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
