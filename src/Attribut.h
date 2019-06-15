/*************************************************************************
                           Attribut  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Attribut> (file Attribut.h) ----------------

#if ! defined (ATTRIBUT_H )
#define ATTRIBUT_H

//--------------------------------------------------- Interfaces used
#include <iostream>
#include <string>
#include "Attribut.h"

using namespace std;

//------------------------------------------------------------------------
// Goal of the <Attribut> class
// Un objet Attribut représente un attribut, avec un id, une unité, et une description
//------------------------------------------------------------------------


class Attribut
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods
	/*
	* Retourne l'id de l'attribut
	*/
	std::string getAttributID ( ) const;

	/*
	* Retourne l'unité
	*/
	std::string getUnit ( ) const;

	/* 
	* Retourne la description
	*/
	std::string getDescription ( ) const;

//-------------------------------------------- Constructor - destructor
	Attribut ( );

	Attribut ( std :: string attributID, std :: string unit, std :: string description );

	~Attribut ( );

//----------------------------------------------------------------- PROTECTED

protected :

//----------------------------------------------------- Protected attributes
    std :: string attributID;
    std :: string unit;
    std :: string description;

};

#endif // ATTRIBUT_H