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
	bool bonEtat = true;
	fileReader->prochaineMesure();

	return true;
}//----- End of surveillerComportementCapteur 
list<Capteur> * Service::surveillerComportementCapteurs(list<string> capteursID)
{
	return nullptr;
}//----- End of surveillerComportementCapteurs
list<pair<Capteur, Capteur>> * Service:: obtenirCapteursSimilaires(struct tm Date, int nbMesures)
{
	return nullptr;
}//----- End of obtenirCapteursSimilaires
tuple<int, list<float>, int> *  Service::calculerQualite(struct tm tempsInf, struct tm tempsSup)
{
	return nullptr;

}//----- End of calculerQualite

 //-------------------------------------------- Constructor - destructor
Service::Service(FileReader * f)
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

bool Service::filtrageCapteur(Capteur capteur, Territoire territoire , string capteurId )
// Algorithm :
// On regarde les attributs de mesure
// Si capteurId == null, 
	// On récupère la position du capteur avec posCapteur = capteur.getPosition()

	// Si territoire.getRayon() == 0 (point considéré)
		// On regarde si la distance entre posCapteur et territoire.getCentre <= 10 km
			// Si oui : on retourne true
			// Sinon : on retourne false

	// Si terrtoire.getRayon() != 0 et territoire.getCentre() != (0,0) (territoire considéré)
		// On regarde si la distance entre posCapteur et (territoire.getCentre() + territoire.getRayon()) <= (50 + territoire.getRayon())
			// Si oui : on retourne true
			// Sinon : on retourne false

	// Si terrtoire.getRayon() == 0 et territoire.getCentre() == (0,0) (aire totale considérée)
		// on retourne true;

// Si capteurId != null
	// On regarde si capteurId == mesure.getCapteur()->getSensorID()
		// Si oui : on retourne true
		// Sinon : on retourne false
{
	bool capteurAPrendre = false;
	if (capteurId.empty())
	{
		const Point * posCapteur = capteur.getPosition();
		
		// cas 1 : point considéré 
		if (territoire.getRayon() == 0)
		{
			Point * centre_zoneAcceptee = new Point(posCapteur->getLongitude(), posCapteur->getLatitude());
			Territoire zoneAcceptee = Territoire(centre_zoneAcceptee, territoire.getRayon() + 10);
			if (zoneAcceptee.contient(posCapteur))
			{
				capteurAPrendre = true;				
			}
			delete centre_zoneAcceptee;			
		}
		// cas 2 : territoire considéré
		else if (territoire.getRayon() != 0
			&& territoire.getCentre()->getLatitude() != 0 && territoire.getCentre()->getLongitude() != 0)
		{
			Point * centre_zoneAcceptee = new Point(posCapteur->getLongitude(), posCapteur->getLatitude());
			Territoire zoneAcceptee = Territoire(centre_zoneAcceptee, territoire.getRayon() + 50);
			if (zoneAcceptee.contient(posCapteur))
			{
				capteurAPrendre = true;
			}
			delete centre_zoneAcceptee;
		}
		// cas 3 : aire totale considée
		else if (territoire.getRayon() == 0
			&& territoire.getCentre()->getLatitude() == 0 && territoire.getCentre()->getLongitude() == 0)
		{
			capteurAPrendre = true;
		}
		
	}
	else
	{
		capteurAPrendre = true;
	}

	return capteurAPrendre;
}

bool Service::filtrageMesure(Mesure mesure, struct tm dateInf, struct tm dateSup)
// Algorithm :
// Si dateSup == null && dateInf != null
	// On regarde si mesure.getTimestamp() (à implémenter) >= dateInf
		// Si oui : on retourne true
		// Sinon : on retourne false
// Si  dateSup != null && dateInf != null
	// On regarde si mesure.getTimestamp() >= dateInf et mesure.getTimestamp() <= dateSup
		// Si oui : on retourne true
		// Sinon : on retourne false
// Si dateSup == null && dateInf == null
	// on retourne true
{
	if ((dateNull(dateSup) == true) && (dateNull(dateInf) == false))
	{

	}
	else if ((dateNull(dateSup) == false) && (dateNull(dateInf) == false))
	{
		 
	}
	else if ((dateNull(dateSup) == true) && (dateNull(dateInf) == true))
	{

	}




	return true;
}

bool Service::dateNull(struct tm date)
{
	if (date.tm_hour == 0 && date.tm_min == 0 && date.tm_sec == 0
		&& date.tm_mday == 0 && date.tm_mon == 0 && date.tm_year == 0)
		return true;
	else
		return false;

}

