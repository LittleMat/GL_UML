
/*************************************************************************
                           FileReader  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <FileReader> (file FileReader.cpp) ----------------

//---------------------------------------------------------------- INCLUDE
using namespace std;
//--------------------------------------------------------- System include

//------------------------------------------------------ Personnal include
#include "FileReader.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

	//TODO mettre paramêtre
	const list < Capteur >* lireCapteurs ( )
	{
		return nullptr;
	}

	//TODO mettre paramêtre
	const list < Attribut >* lireAttributs ( )
	{
		return nullptr;

	}

	//TODO mettre paramêtre
	const Mesure* prochaineMesure ( )
	{
		return nullptr;

	}

//-------------------------------------------- Constructors - destructor

FileReader :: FileReader ( const std :: string & nomFichierCapteurs, const string & nomFichierAttributs, const std :: list < std :: string > & nomFichiersMesures, const std :: string & fichierMesureEnCours)
{
	#ifdef MAP
	    cerr << "Constructor of <FileReader>" << endl;
	#endif

	this->nomFichierCapteurs = nomFichierCapteurs;
	this->nomFichierAttributs = nomFichierAttributs;
	this->nomFichiersMesures = nomFichiersMesures;
	this->fichierMesureEnCours = fichierMesureEnCours;
	int numLigne = 0;

} // End of constructor

FileReader :: FileReader ( )
{	
	#ifdef MAP
	    cerr << "Default constructor of <FileReader>" << endl;
	#endif

	this->nomFichierCapteurs = "";
	this->nomFichierAttributs = "";
	this->fichierMesureEnCours = "";
	int numLigne = 0;
}

FileReader :: ~FileReader ( )
{

} // End of destructor