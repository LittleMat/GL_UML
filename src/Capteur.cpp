/*************************************************************************
                           Capteur  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Capteur> (file Capteur.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include

//------------------------------------------------------ Personnal include
#include "Capteur.h"

using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes
const string Capteur :: getSensorID ( ) const
{
	return sensorID;

} //----- End of getSensorID

const Point * Capteur :: getPosition ( ) const
{
	return position;

} //----- End of getPosition

const string Capteur :: getDescription ( ) const
{
	return description;

} //----- End of getDescription

//-------------------------------------------- Constructors - destructor

Capteur :: Capteur ( const string sensorID, Point * position, const string description )
{
	#ifdef MAP
		cout << "Appel au constructeur de <Capteur>" << endl;
	#endif
	
	if (sensorID.empty() || position == nullptr)
		throw "Illegal Argument Exception";

	this -> sensorID = sensorID;
	this -> position = position;
	this -> description = description;
	
} //----- End of Capteur

Capteur::Capteur ( )
{
	#ifdef MAP
		cout << "Appel au constructeur par défaut de <Capteur>" << endl;
	#endif
	this -> sensorID = string ( );
	this -> position = nullptr;
	this -> description = string ( );

} //----- End of Capteur

Capteur :: ~Capteur ( )
{
	#ifdef MAP
		cout << "Appel au destructeur de <Capteur>" << endl;
	#endif
	delete position;

} //----- End of ~Capteur