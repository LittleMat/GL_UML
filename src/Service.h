/*************************************************************************
Service  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Service> (file Service.h) ----------------
#if ! defined ( SERVICE_H )
#define SERVICE_H

//--------------------------------------------------- Interfaces used
#include <iostream>
#include <list>
#include <tuple>
#include <utility> 
#include <string>
#include <ctime>
#include <cmath>

#include "FileReader.h"
#include "Capteur.h"
#include "Territoire.h"

using namespace std;


//------------------------------------------------------------------------
// Goals of the <Service> class
//------------------------------------------------------------------------


class Service
{
	//----------------------------------------------------------------- PUBLIC

public:

	//----------------------------------------------------- Public methods
	bool surveillerComportementCapteur(string capteurID, paramFiltrage & parametres);
	list<Capteur> * surveillerComportementCapteurs(list<string> & capteursID, paramFiltrage & parametres);
	list<pair<Capteur, Capteur>> * obtenirCapteursSimilaires(struct tm & Date, int nbMesures);
	tuple<int, list<pair<string, float>>, float> calculerQualite(paramFiltrage & parametres);

	static bool filtrageCapteur(Capteur & capteur, Territoire & territoire, string capteurId);
	static bool filtrageMesure(Mesure & m, struct tm & dateInf, struct tm & dateSup);
	static bool dateNull(struct tm & date);
	static bool plusOuMoins(float v1, float v2, float ecart);
	static int calculIndiceATMO(string substance, float valeur);



	//-------------------------------------------- Constructor - destructor
	Service(FileReader * f);

	~Service();

protected:
	//----------------------------------------------------- Protected attributes
	FileReader * fileReader;

	//----------------------------------------------------- Protected methods
};

#endif // SERVICE_H
