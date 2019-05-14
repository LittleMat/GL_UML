/*************************************************************************
Point  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Point> (file Point.h) ----------------
#if ! defined ( POINT_H )
#define POINT_H

//--------------------------------------------------- Interfaces used
#include <iostream>
using namespace std;

//------------------------------------------------------------------------
// Goal of the <Point> class
//------------------------------------------------------------------------


class Point
{
	//----------------------------------------------------------------- PUBLIC

public:

	//----------------------------------------------------- Public methods
	float getLongitude();
	// Mode d'emploi :
	// 
	// Contrat :
	//

	float getLatitude();
	// Mode d'emploi :
	// 
	// Contrat :
	//

	float distance(Point p);
	// Mode d'emploi :
	// 
	// Contrat :
	//

	//-------------------------------------------- Constructor - destructor
	Point(float longt, float lat);
	// Mode d'emploi :
	// 
	// Contrat :
	//

	~Point();
	// Mode d'emploi :
	// 
	// Contrat :
	//
	

protected:
	//----------------------------------------------------- Protected attributes
	float longitude;
	float latitude;

};

#endif // POINT_H
