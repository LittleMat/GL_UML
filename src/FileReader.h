/*************************************************************************
                           FileReader  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <FileReader> (file FileReader.h) ----------------
#ifndef FILEREADER_H
#define FILEREADER_H

#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <math.h>
#include <unordered_map> 
#include "Capteur.h"
#include "Mesure.h"
#include "Attribut.h"

//------------------------------------------------------------------------
// Goal of the <FileReader> class
//------------------------------------------------------------------------


class FileReader
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods

	/*
	 * Lit les capteurs du fichiers contenant les capteurs et retourne une map de capteurs
	 */
	const std :: unordered_map < std :: string , Capteur * > lireCapteurs ( ) const; //TODO mettre parametre

	/*
	 * Lit les différents attributs du fichier contenant les attributs et retourne une map d'attributs
	 */
	const std :: unordered_map < std :: string , Attribut * > lireAttributs ( ) const; //TODO mettre parametre

	/*
	 * Lit la prochaine mesure des fichiers contenant les mesures
	 */
	Mesure* prochaineMesure ( std :: unordered_map < std :: string, Attribut * > & map_attributs, std :: unordered_map < std :: string, Capteur * > & map_capteurs ); //TODO mettre paramêtre
//-------------------------------------------- Constructor - destructor
	/*
	 *	
	 */
	FileReader ( const std :: string & nomFichierCapteurs, const string & nomFichierAttributs, const std :: list < std :: string > & nomFichiersMesures);

	/*
	 *	
	 */
	FileReader ( );

	/*
	 *	
	 */
	~FileReader ( );

protected :
	bool fichierLisible();
	void getLineModifie ( ifstream& fichierMesureEnCours, string& line );

//----------------------------------------------------- Protected attributes
	std :: string nomFichierCapteurs;
	std :: string nomFichierAttributs;
	std :: list < std :: string > nomFichiersMesures;
	ifstream fichierMesureEnCours;

	regex reg_mesure;
	regex reg_date;
	regex reg_capt;
	regex reg_attr;

};

#endif // FILEREADER_H