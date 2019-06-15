/*************************************************************************
                           FileReader  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <FileReader> (file FileReader.h) ----------------
#define _USE_MATH_DEFINES
#ifndef FILEREADER_H
#define FILEREADER_H

//--------------------------------------------------- Interfaces used
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
#include "Territoire.h"
#include <functional>

//------------------------------------------------------------------------
// Goal of the <FileReader> class
// FileReader permet de lire les différents type de fichiers et de retourner une map de capteurs
// d'attributs et de mesures, en fonction des paramètres choisis par l'utilisateur dans le menu (cli)
//------------------------------------------------------------------------


class FileReader
{
//----------------------------------------------------------------- PUBLIC

public :

//----------------------------------------------------- Public methods

	/*
	 * Lit les capteurs valides du fichiers contenant les capteurs et retourne une map de capteurs, met à jour l'attribut map_capteurs
	 */
	std :: unordered_map < std :: string , Capteur * > lireCapteurs ( function<bool(Capteur&)> ); 
	

	/*
	 * Lit les différents attributs du fichier contenant les attributs et retourne une map d'attributs, met à jour map_attributs
	 */
	std :: unordered_map < std :: string , Attribut * > lireAttributs ( ); 

	/*
	 * Revient au début des mesures
	 */
	void debutMesure ( );

	/*
	 * Lit la prochaine mesure valide des fichiers contenant les mesures,
	 */
	Mesure * prochaineMesure (function<bool(Mesure&)> predicateMesure ); 

//-------------------------------------------- Constructor - destructor
	
	//nomFichierCapteurs : nom du fichier contenant les capteurs
	//nomFichierAttributs : nom du fichiers contenant les attributs
	//nomFichiersMesures : liste des noms de fichiers de mesure
	FileReader ( const std :: string & nomFichierCapteurs, const string & nomFichierAttributs, const std :: list < std :: string > & nomFichiersMesures );

	~FileReader ( );

//----------------------------------------------------------------- PROTECTED

protected :
	
//----------------------------------------------------- Protected attributes
	std :: string nomFichierCapteurs; 					//Nom du fichier contenant les capteurs
	std :: string nomFichierAttributs; 					//Nom du fichier contenant les attributs
	std :: vector < std :: string > nomFichiersMesures; //Liste des noms des fichiers contenant les mesures
	ifstream fichierMesureEnCours; 						//Fichier de mesure actuellement ouvert

	unsigned long idFichierMesures;						//Id du fichier dans la liste nomFichiersMesures actuellement ouvert

	unordered_map < string, Attribut * > map_attributs;	//Map des attributs 
	unordered_map < string, Capteur * > map_capteurs;	//Map des capteurs

	static regex reg_mesure;							//Regex de filtrage des mesures
	static regex reg_date;								//Regex de filtrage des dates
	static regex reg_capt;								//Regex de filtrage des capteurs
	static regex reg_attr;								//Regex de filtrage des attributs

	static string enteteFicherCapteurs;					//Entête des fichiers contenant les capteurs (pour filtrer les bons/mauvais fichiers)
	static string enteteFichierAttributs;				//Entête des fichiers contenant les capteurs (pour filtrer les bons/mauvais fichiers)
	static string enteteFichierMesures;					//Entête des fichiers contenant les mesures (pour filtrer les bons/mauvais fichiers)

//----------------------------------------------------- Protected methods
	/*
	* Renvoie vrai s'il reste des fichiers de mesure à lire
	*/
	bool fichierLisible();
};

#endif // FILEREADER_H