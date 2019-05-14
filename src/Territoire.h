/*************************************************************************
Territoire  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Territoire> (file Territoire.h) ----------------
#if ! defined ( TERRITOIRE_H )
#define TERRITOIRE_H

//--------------------------------------------------- Interfaces used
#include <iostream>
using namespace std;

#include "Point.h"

//------------------------------------------------------------------------
// Goal of the <Territoire> class
//------------------------------------------------------------------------


class Territoire
{
	//----------------------------------------------------------------- PUBLIC

public:

	//----------------------------------------------------- Public methods
	Point * getCentre();
	// Mode d'emploi :
	// 
	// Contrat :
	//

	int getRayon();
	// Mode d'emploi :
	// 
	// Contrat :
	//

	bool contient(Point * p);
	// Mode d'emploi :
	// 
	// Contrat :
	//

	//-------------------------------------------- Constructor - destructor
	Territoire(Point * c, int r);
	// Mode d'emploi :
	// 
	// Contrat :
	//

	~Territoire();
	// Mode d'emploi :
	// 
	// Contrat :
	//


protected:
	//----------------------------------------------------- Protected attributes
	Point * centre;
	int rayon;

};

#endif // TERRITOIRE_H
