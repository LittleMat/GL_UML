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
	}

	const Point * Capteur :: getPosition ( ) const
	{
		return position;
	}

	const string Capteur :: getDescription ( ) const
	{
		return description;
	}

//-------------------------------------------- Constructors - destructor

Capteur :: Capteur ( const string sensorID, Point * position, const string description )
{
	#ifdef MAP
	    cerr << "Constructor of <Capteur>" << endl;
	#endif
	
	if (sensorID.empty() || position == nullptr)
		throw "Illegal Argument Exception";

	this -> sensorID = sensorID;
	this -> position = position;
	this -> description = description;
	//Liste de point??
	
}//End of constructor

Capteur::Capteur ( )
{
	this -> sensorID = string ( );
	this -> position = nullptr;
	this -> description = string ( );
}

Capteur :: ~Capteur ( )
{
	delete position;
}// End of destructor 