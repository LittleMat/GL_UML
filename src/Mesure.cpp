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
#include<cstring>
using namespace std;

//------------------------------------------------------ Personnal include

#include "Mesure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes


// Algorithm :
//
{

    

}//-----End of 



//-------------------------------------------- Constructors - destructor

Mesure::Mesure (Date t, Attribut a, int v, string sid )
// Algorithm :
//
{

#ifdef MAP
		cout << "Appel au constructeur de <Mesure>" << endl;
#endif
}//-----End of Mesure

Mesure::~Mesure ()
// Algorithm :
//
{
#ifdef MAP
cout << "Appel au destructeur de <Mesure>" << endl;
#endif

}//-----End of Mesure

//----- End of ~Mesure 