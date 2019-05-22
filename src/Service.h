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


#include "FileReader.h"
#include <list>
#include "Capteur.h"
#include "Territoire.h"
#include <tuple>
#include <utility> 
#include <string>
#include <ctime>
using namespace std;

//------------------------------------------------------------------------
// Goals of the <Service> class
//------------------------------------------------------------------------


class Service
{
	//----------------------------------------------------------------- PUBLIC

public:

	//----------------------------------------------------- Public methods
	bool surveillerComportementCapteur(string capteurID);
	list<Capteur> * surveillerComportementCapteurs(list<string> capteursID );
	list<pair<Capteur, Capteur>> * obtenirCapteursSimilaires(struct tm Date, int nbMesures);
	tuple<int, list<float>, int> * calculerQualite(struct tm tempsInf, struct tm tempsSup);

	//-------------------------------------------- Constructor - destructor
	Service(FileReader * f);

	~Service();

protected:
	//----------------------------------------------------- Protected attributes
	FileReader * fileReader;

	//----------------------------------------------------- Protected methods
	bool filtrageCapteur(Capteur capteur, Territoire territoire = Territoire(), string capteurId = string());
	bool filtrageMesure(Mesure m, struct tm dateInf, struct tm dateSup);
	bool dateNull(struct tm date);
};

#endif // SERVICE_H
