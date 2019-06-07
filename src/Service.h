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
#include <functional>

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
	list < string > * surveillerComportementCapteurs ( list < string > & capteursID, function<bool(Mesure&)> predicateMesure);
	list < pair < string , string > > * obtenirCapteursSimilaires (struct tm & Date , int nbMesures );
	// tuple <Indice ATMO , list pair < <idattribut , concentration moyenne > > , indice_fiabilit�>
	tuple < int , list < pair < string , float > > , float > calculerQualite ( string& capteurId, function<bool(Mesure&)> predicateMesure, function<float(Capteur&)> fiabilite );

	static function<bool(const Capteur&, const Territoire&, const string&)> filtrageCapteur;
	static function<bool(Mesure&, struct tm&, struct tm&)> filtrageMesure;
	static function<float(const Capteur&, const Territoire&)> fiabilite;
	static bool dateNull ( struct tm & date );
	static bool plusOuMoins ( float v1 , float v2 , float ecart );
	static int calculIndiceATMO ( string substance , float valeur );



	//-------------------------------------------- Constructor - destructor

	Service ( const string & nomFichierCapteurs , const string & nomFichierAttributs , const list < string > & nomFichiersMesures );


	~Service ( ) ;

protected:
	//----------------------------------------------------- Protected attributes
	FileReader * fileReader;

	//----------------------------------------------------- Protected methods
};

#endif // SERVICE_H
