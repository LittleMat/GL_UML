/*************************************************************************
Territoire  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Territoire> (file Territoire.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include
#include <iostream>

using namespace std;

//------------------------------------------------------ Personnal include
#include "Territoire.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methods
Point * Territoire :: getCentre ( ) const
// Algorithm : 
{
	return centre;
}//----- End of getCentre 

int Territoire :: getRayon ( ) const
// Algorithm : 
{
	return rayon;
}//----- End of getRayon 

bool Territoire :: contient ( const Point * p ) const
// Algorithm : 
{
	if (p == nullptr)
		throw "Illegal Argument Exception";
	if ( p-> distance ( centre ) <= this->rayon )
	{
		return true;
	}
	else
	{
		return false;
	}

}//----- End of contient 

 //-------------------------------------------- Constructor - destructor
Territoire :: Territoire ( Point * c, int r )
// Algorithm : 
{
	#ifdef MAP
		cout << "Appel au constructeur de <Territoire>" << endl;
	#endif

	if (c == nullptr || r < 0)
		throw "Illegal Argument Exception";
	centre = c;
	//c = new Point(c->getLongitude(), c->getLatitude());
	rayon = r;
}//----- End of Territoire 

Territoire :: Territoire ( )
// Algorithm : 
{
	#ifdef MAP
		cout << "Appel au constructeur par d�faut de <Territoire>" << endl;
	#endif

	rayon = 0;
	centre = new Point (0, 0);
}


Territoire :: ~Territoire ( )
// Algorithm : 
{
	#ifdef MAP
		cout << "Appel au destructeur de <Territoire>" << endl;
	#endif

	delete centre;
}//----- End of ~Territoire 


 //------------------------------------------------------------------ PRIVE

 //----------------------------------------------------- Protected methods
