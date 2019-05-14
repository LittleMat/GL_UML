/*************************************************************************
Service  -  description
-------------------
beginning            : 14/05
copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Service> (file Service.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include
#include <iostream>
using namespace std;

//------------------------------------------------------ Personnal include
#include "Service.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methods

bool Service::surveillerComportementCapteur(string capteurID)
{
	return true;
}//----- End of surveillerComportementCapteur 
list<Capteur> * Service::surveillerComportementCapteurs(list<string> capteursID)
{

}//----- End of surveillerComportementCapteurs
list<pair<Capteur, Capteur>> * Service:: obtenirCapteursSimilaires(struct tm Date, int nbMesures)
{

}//----- End of obtenirCapteursSimilaires
tuple<int, list<float>, int> *  Service::calculerQualite(struct tm tempsInf, struct tm tempsSup)
{

}//----- End of calculerQualite

 //-------------------------------------------- Constructor - destructor
Service::Service(FileReader & f)
// Algorithm : 
{
#ifdef MAP
	cout << "Appel au constructeur de <Service>" << endl;
#endif
	fileReader = f;

}//----- End of Service 

Service::~Service()
// Algorithm : 
{
#ifdef MAP
	cout << "Appel au destructeur de <Service>" << endl;
#endif
}//----- End of ~Service 


 //------------------------------------------------------------------ PRIVE

 //----------------------------------------------------- Protected methods

