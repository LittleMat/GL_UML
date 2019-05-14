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
	 * Lit les capteurs du fichiers contenant les capteurs et retourne une liste de capteurs
	 */
	const list < Capteur > lireCapteurs ( ); //TODO mettre parametre

	/*
	 * Lit les différents attributs du fichier contenant les attributs et retourne une liste d'attributs
	 */
	const list < Attribut > lireAttributs ( ); //TODO mettre parametre

	/*
	 * Lit la prochaine mesure des fichiers contenant les mesures
	 */
	const Mesure prochaineMesure ( ); //TODO mettre paramêtre
//-------------------------------------------- Constructor - destructor
	/*
	 *	
	 */
	FileReader ( const std :: string & nomFichierCapteurs, const string & nomFichierAttributs, const std :: list < std :: string > & nomFichiersMesures, const std :: string & fichierMesureEnCours);

	/*
	 *	
	 */
	FileReader ( );

	/*
	 *	
	 */
	~FileReader ( );

protected :

//----------------------------------------------------- Protected attributes
	std :: string nomFichierCapteurs;
	std :: string nomFichierAttributs;
	std :: list < std :: string > nomFichiersMesures;
	std :: string fichierMesureEnCours;
	int numLigne;

};

#endif // FILEREADER_H