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
#include<string>
using namespace std;

//------------------------------------------------------ Personnal include

#include "Mesure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

const Attribut * Mesure :: getAttribut() const
{
	return this->attribut;
}

int Mesure :: getValue() const
{
	return this->value;
}

const std::string Mesure :: getSensorID() const
{
	return this->sensorID;
}

const Capteur * Mesure :: getCapteur() const
{
	return this->capteur;
}

//-------------------------------------------- Constructors - destructor

Mesure :: Mesure (struct tm timestamp, Attribut * const attribut, int value, std ::string sensorID, Capteur * capteur)
// Algorithm :
//
{

#ifdef MAP
		cout << "Appel au constructeur de <Mesure>" << endl;
#endif

	this->timestamp = timestamp;
	this->attribut = attribut;
	this->value = value;
	this->sensorID = sensorID;
	this->capteur = capteur;
	
}//-----End of Mesure

Mesure:: ~Mesure ()
// Algorithm :
//
{
	#ifdef MAP
	cout << "Appel au destructeur de <Mesure>" << endl;
	#endif

	delete attribut;
}//----- End of ~Mesure 
