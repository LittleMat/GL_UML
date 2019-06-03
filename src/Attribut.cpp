/*************************************************************************
                           Attribut  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Attribut> (file Attribut.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include

//------------------------------------------------------ Personnal include
#include "Attribut.h"
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes
string Attribut :: getAttributID ( ) const
{
	return this -> attributID;
}

string Attribut :: getUnit ( ) const
{
	return this -> unit;
}

string Attribut :: getDescription ( ) const
{
	return this -> description;
}

//-------------------------------------------- Constructors - destructor
Attribut :: Attribut ( )
{
	#ifdef MAP
		cerr << "Constructor of <Attribut>" << endl;
	#endif

	this -> attributID = "";
	this -> unit = "";
	this -> description = "";


}//End of constructor

Attribut :: Attribut ( string attributID, string unit, string description )
{
	#ifdef MAP
	    cerr << "Constructor of <Attribut>" << endl;
	#endif
	if (attributID.empty() || unit.empty())
		throw "Illegal Argument Exception";
	this -> attributID = attributID;
	this -> unit = unit;
	this -> description = description;
}//End of constructor

Attribut :: ~Attribut ( )
{

}// End of destructor 