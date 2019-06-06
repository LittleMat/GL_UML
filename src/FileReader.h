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
#include "Territoire.h"

typedef struct param
{
	// Pour filtrageMesure
	struct tm dateInf;
	struct tm dateSup;
	//Pour filtrageCapteur
	Territoire * territoire;
	string capteurId;
	~param() {
		delete territoire;
	}
} paramFiltrage;
//!\\ ne surtout pas faire parametre.territoire = Territoire () car conversions bizarres
// mais plutôt Territoire t = Territoire(); parametre.territoire = t;


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
	std :: unordered_map < std :: string , Capteur * > lireCapteurs ( paramFiltrage & parametres, bool ( * filtrageCapteur ) ( Capteur & , Territoire &, string ) ); 
	

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
	Mesure * prochaineMesure ( paramFiltrage& parametres, bool ( * filtrageMesure ) ( Mesure &, struct tm &, struct tm & ) ); 


	/*
	const list < std::string > getNomFichiersMesures ( ) const;
	*/
//-------------------------------------------- Constructor - destructor
	
	//nomFichierCapteurs : nom du fichier contenant les capteurs
	//nomFichierAttributs : nom du fichiers contenant les attributs
	//nomFichiersMesures : list des noms de fichiers de mesure

	FileReader ( const std :: string & nomFichierCapteurs, const string & nomFichierAttributs, const std :: list < std :: string > & nomFichiersMesures );

	//FileReader ( );

	~FileReader ( );

protected :
	//Renvoie vrai s'il reste des fichiers de mesure à lire
	bool fichierLisible ( );

	
	//getLine modifié pour lire de l'utf-16 (spécifique à nos fichiers en entrée, filtre les char dont le code héxadécimal est 0 ou d)
	void getLineModifie ( ifstream & fichierMesureEnCours, string & line );
	
//----------------------------------------------------- Protected attributes
	std :: string nomFichierCapteurs;
	std :: string nomFichierAttributs;
	std :: vector < std :: string > nomFichiersMesures;
	ifstream fichierMesureEnCours;

	int idFichierMesures;

	unordered_map < string, Attribut * > map_attributs;
	unordered_map < string, Capteur * > map_capteurs;

	static regex reg_mesure;
	static regex reg_date;
	static regex reg_capt;
	static regex reg_attr;

	static string enteteFicherCapteurs;
	static string enteteFichierAttributs;
	static string enteteFichierMesures;
};

#endif // FILEREADER_H