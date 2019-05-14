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
Point Territoire::getCentre()
// Algorithm : 
{
	return centre;
}//----- End of getCentre 

int Territoire::getRayon()
// Algorithm : 
{
	return rayon;
}//----- End of getRayon 

bool Territoire::contient(Point p)
// Algorithm : 
{
	if (p.distance(centre) <= rayon)
		return true;
	else
		return false;

}//----- End of contient 

 //-------------------------------------------- Constructor - destructor
Territoire::Territoire(Point c, int r)
// Algorithm : 
{
#ifdef MAP
	cout << "Appel au constructeur de <Territoire>" << endl;
#endif
	centre = c;
	rayon = r;
}//----- End of Territoire 

Point::~Point()
// Algorithm : 
{
#ifdef MAP
	cout << "Appel au destructeur de <Territoire>" << endl;
#endif
}//----- End of ~Territoire 


 //------------------------------------------------------------------ PRIVE

 //----------------------------------------------------- Protected methods
