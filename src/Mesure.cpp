/*************************************************************************
                           Mesure  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Mesure> (file Mesure.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include

#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------ Personnal include

#include "Mesure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

string Mesure :: getAttributID ( ) const
{
	return this -> attributID;

} //----- End of getAttributID

float Mesure :: getValue ( ) const
{
	return this -> value;

} //----- End of getValue

string Mesure :: getSensorID ( ) const
{
	return this -> sensorID;

} //----- End of getSensorID

struct tm Mesure :: getTimestamp ( ) const
{
	return this -> timestamp;

} //----- End of getTimestamp

//-------------------------------------------- Constructors - destructor

Mesure :: Mesure (const struct tm& timestamp, const string& attributID, float value, const string& sensorID) :
		timestamp(timestamp), attributID(attributID), value(value), sensorID(sensorID)
{

	#ifdef MAP
		cout << "Appel au constructeur de <Mesure>" << endl;
	#endif

	if (this->attributID.empty() || this->sensorID.empty() || mktime(&this->timestamp) > time(NULL)) {
		throw "Illegal Argument Exception";
	}
	
} //----- End of Mesure

Mesure :: Mesure ( )
{
	this -> timestamp = tm ( );
	this -> attributID = string ( );
	this -> value = 0.0;
	this -> sensorID = string ( );
} //----- End of Mesure

Mesure:: ~Mesure ( )
{
	#ifdef MAP
	cout << "Appel au destructeur de <Mesure>" << endl;
	#endif

} //----- End of ~Mesure 
