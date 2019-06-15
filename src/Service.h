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
// La classe <Service> implemente les fonctionnalites de l'application :
// - Calculer la qualité moyenne de l'air
// - Surveiller le comportement des capteurs
// - Trouver des capteurs similaires
// Elle fournit également à la classe FileReader des fonctions de filtrage
// de capteur et de mesure.
//------------------------------------------------------------------------


class Service
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Public methods
	/*
	* A partir des criteres de filtrage, lit les mesures qui les satisfont et retourne une liste de 
	* capteurs defectueux
	*/
	list < string > * surveillerComportementCapteurs ( list < string > & capteursID, function<bool(Mesure&)> predicateMesure);

	/*
	* A partir d'un nombre de mesures et d'une date Date, 
	* compare les mesures des capteurs et retourne les couples de capteurs similaires
	*
	* Contrat :
	* Dans les fichiers de mesures utilises, les capteurs prennent leurs mesures quasi en même temps 
	* (les capteurs sont synchrones) 
	* Pour chaque mesure, les capteurs ont une valeur pour chaque attribut
	* (on ne peut pas avoir une valeur pour O3, SO2 seulement par exemple)
	*/
	list < pair < string , string > > * obtenirCapteursSimilaires (struct tm & Date , int nbMesures );

	/*
	* Retourne un tuple <Indice ATMO, liste des concentrations moyennes de chaque gaz, indice de fiabilite> 
	* en fonction des criteres de filtrage 
	*/
	tuple < int , list < pair < string , float > > , float > calculerQualite ( string& capteurId, function<bool(Mesure&)> predicateMesure, function<float(Capteur&)> fiabilite );

	/*
	* Calcul l'indice ATMO en fonction du nom du gaz et de sa concentration
	* 
	* Contrat :
	* Le nom du gaz doit faire partie de la liste suivante : O3, SO2, NO2, PM10
	*/
	static int calculIndiceATMO(string substance, float valeur);

	/*
	* Retourne true si le capteur lu (premier parametre) satisfait les criteres de selection
	* (selection par l'id du capteur si la chaine ne caractere n'est pas vide, 
	* sinon, selection spatiale)
	*/
	static function<bool(const Capteur&, const Territoire&, const string&)> filtrageCapteur;

	/*
	* Retourne true si la mesure lue (premier paramètre) satisfait les criteres de selection temporels
	*/
	static function<bool(Mesure&, struct tm&, struct tm&)> filtrageMesure;

	/*
	* Retourne l'indice de fiabilite dont le calcul est en fonction de la position d'un capteur par rapport 
	* au Territoire considéré (aire totale, territoire cible, point)
	*/
	static function<float(const Capteur&, const Territoire&)> fiabilite;

	/*
	* Retourne true si la date est null c'est-a-dire si :
	* l'annee, le mois, le jour, les heures, les minutes et les secondes sont de 0
	*/
	static bool dateNull ( struct tm & date );

	/*
	* Retourne true si la valeur absolue de v1-v2 est inferieur a ecart
	*/
	static bool plusOuMoins ( float v1 , float v2 , float ecart );
	

//-------------------------------------------- Constructor - destructor

	Service ( const string & nomFichierCapteurs , const string & nomFichierAttributs , const list < string > & nomFichiersMesures );

	~Service ( ) ;

//----------------------------------------------------------------- PROTECTED

protected:

//----------------------------------------------------- Protected attributes
	FileReader * fileReader;

};

#endif // SERVICE_H
