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

bool Service::surveillerComportementCapteur(string capteurID, paramFiltrage & parametres)
{
	bool bonEtat = true;
	bool finLecture = false;
	list <string> fichierLu; // Demander � Mathieu de retourner la liste des fichiers de mesure
	while (finLecture == false)
	{
		// On s�lectionne les mesures qui satisfont les crit�res de s�lection temporelles
		const Mesure * m = fileReader->prochaineMesure(parametres, filtrageMesure); //TODO : mettre param�tres

		// On regarde si la mesure s�lectionn�e est concerne le capteur � surveiller
		if (capteurID.compare(m->getCapteur()->getSensorID()) == 0)
		{
			// Dossier de sp�
			//Observe les donn�es g�n�r�es par le capteur pour d�tecter 
			// - une absence de donn�es(capteur HS) => OK
			// - ou la pr�sence de donn�es aberrantes(capteur d�fectueux) :
			// - valeurs n�gatives => OK 
			// valeurs trop �lev�es => impossible car d�pend de l'unit� 
			// (rien ne dit que les unit�s seront toujours les m�mes)  
			// oscillations trop rapides => c'est-�-dire ??

			if (m->getValue() == NULL || m->getValue() < 0)
			{
				bonEtat = false;
				break;
			}

		}
		
		finLecture = true; // TEMP : l� juste en attendant de trouver une solution
	}

	// Quand finLecture == true ??? 
	// Regarder quand filtrageMesure == false ?? mais comment faire pour les param ??
	// Ne fonctionne pas quand il a une date inf car filtrageMesure retourne false false ... true

	// Regarder si on est arriv� � la fin de tous les fichiers de mesure � consid�rer ??
	// Mais perf...
	// et listeFichierMesure non impl�ment� dans FileReader

	return bonEtat;

}//----- End of surveillerComportementCapteur 


list<Capteur> * Service::surveillerComportementCapteurs(list<string> & capteursID, paramFiltrage & parametres)
{

	// Pour le mettre dans le tas sinon la liste se fait d�truire � la fin de l'appel de la m�thode
	list<Capteur> * liste_capteursDefectueux = new list<Capteur>;


	// id des capteurs d�fectueux
	list<string> liste_id_capteursDefectueux;
	for (list<string>::iterator i = capteursID.begin(); i != capteursID.end(); i++)
	{
		paramFiltrage param = { NULL, NULL, NULL, NULL};
		param.capteurId = *i;
		if (surveillerComportementCapteur(*i, param) == false)
		{
			liste_id_capteursDefectueux.push_back(*i);
		}
	}

	// id -> Capteur
	unordered_map < std::string, Capteur * > capteurs = fileReader->lireCapteurs(parametres, filtrageCapteur); //TODO : param filtrageCapteur
	// Pas n�cessaire si g�r� dans lireCapteurs();
	/* A MODIFIER EN FONCTION DU FONCTIONNEMENT FINAL DE FILEREADER
	Ci-dessous version avec list de string retourn�e
	for (list <Capteur*> ::const_iterator it = capteurs.cbegin(); it != capteurs.cend(); it++)
	{
		for (list<string> ::iterator it_id = liste_id_capteursDefectueux.begin(); it_id != liste_id_capteursDefectueux.end(); it++)
		{
			if ((*it)->getSensorID().compare(*(it_id)) == 0)
			{
				liste_capteursDefectueux->push_back(**it); 
				break;
			}

		}
	}
	*/

	//!\\ Attention : dans le CLI, ne pas oublier le delete
	return liste_capteursDefectueux;

}//----- End of surveillerComportementCapteurs



list<pair<Capteur, Capteur>> * Service:: obtenirCapteursSimilaires(struct tm & Date, int nbMesures)
// Algorithm :
// On r�cup�re la liste de tous les capteurs : listeCapteurs
// On r�cup�re les mesures � traiter dans une liste : listeMesures 
// et apr�s ??
{

	paramFiltrage parametres = {Date, NULL, NULL, NULL};
	unordered_map < std::string, Capteur * > capteurs = fileReader->lireCapteurs(parametres, filtrageCapteur); //TODO : ajouter param�tre filtrageCapteur()
	list<const Mesure*> listeMesures; // parce que fileReader->prochaineMesure() retourne un const Mesure * 
	int nbMesureConsiderees = 0;
	while (nbMesureConsiderees <= nbMesures * 4) // Hyp : on a une valeur pour O3, NO2, SO2, PM10 pour chaque mesure
	{
		const Mesure * m = fileReader->prochaineMesure(parametres, filtrageMesure); //TODO : ajouter param�tre filtrageMesure()
		nbMesureConsiderees++;
		listeMesures.push_back(m);
	}

	// On fait comment apr�s ??

	return nullptr;
}//----- End of obtenirCapteursSimilaires

tuple<int, list<float>, int> *  Service::calculerQualite(struct tm & tempsInf, struct tm & tempsSup, paramFiltrage & parametres)
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

bool Service::filtrageCapteur(Capteur & capteur, Territoire & territoire , string capteurId )
// Algorithm :
// Si capteurId == null, 
	// On r�cup�re la position du capteur avec posCapteur = capteur.getPosition()

	// Si territoire.getRayon() == 0 (point consid�r�)
		// On regarde si la distance entre posCapteur et territoire.getCentre <= 10 km
			// Si oui : on retourne true
			// Sinon : on retourne false

	// Si terrtoire.getRayon() != 0 et territoire.getCentre() != (0,0) (territoire consid�r�)
		// On regarde si la distance entre posCapteur et (territoire.getCentre() + territoire.getRayon()) <= (50 + territoire.getRayon())
			// Si oui : on retourne true
			// Sinon : on retourne false

	// Si terrtoire.getRayon() == 0 et territoire.getCentre() == (0,0) (aire totale consid�r�e)
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
		
		// cas 1 : point consid�r� 
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
		// cas 2 : territoire consid�r�
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
		// cas 3 : aire totale consid�r�e
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

bool Service::filtrageMesure(Mesure & mesure, struct tm & dateInf, struct tm & dateSup)
// Algorithm :
// Si dateSup == null && dateInf != null
	// On regarde si mesure.getTimestamp() (� impl�menter) >= dateInf
		// Si oui : on retourne true
		// Sinon : on retourne false
// Si  dateSup != null && dateInf != null
	// On regarde si mesure.getTimestamp() >= dateInf et mesure.getTimestamp() <= dateSup
		// Si oui : on retourne true
		// Sinon : on retourne false
// Si dateSup == null && dateInf == null
	// on retourne true
{
	bool mesureAPrendre = false;
	time_t timeMes = mktime(mesure.getTimestamp()); 
	if ((dateNull(dateSup) == true) && (dateNull(dateInf) == false))
	{
		time_t timeInf = mktime(&dateInf);

		if (timeMes >= timeInf)
			mesureAPrendre = true;

	}
	else if ((dateNull(dateSup) == false) && (dateNull(dateInf) == false))
	{
		time_t timeInf = mktime(&dateInf);
		time_t timeSup = mktime(&dateSup);
		if (timeMes >= timeInf && timeMes <= timeSup)
			mesureAPrendre = true;
		 
	}
	else if ((dateNull(dateSup) == true) && (dateNull(dateInf) == true))
	{
		mesureAPrendre = true;

	}
	return mesureAPrendre;
}

bool Service::dateNull(struct tm & date)
{
	if (date.tm_hour == 0 && date.tm_min == 0 && date.tm_sec == 0
		&& date.tm_mday == 0 && date.tm_mon == 0 && date.tm_year == 0)
		return true;
	else
		return false;

}

