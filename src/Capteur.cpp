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
#include "Point.h"

using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

//-------------------------------------------- Constructors - destructor

Capteur :: Capteur ( const std :: string & sensorID, const Point & position, const std :: string & description)
{
	#ifdef MAP
	    cerr << "Constructor of <Capteur>" << endl;
	#endif
	    
	this.sensorID = sensorID;
	this.position = position;
	this.description = description;
}//End of constructor

Capteur :: ~Capteur ( )
{

}// End of destructor 