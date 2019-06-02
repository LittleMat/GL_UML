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
	while (finLecture == false)
	{
		// On sélectionne les mesures qui satisfont les critères de sélection temporelles
		const Mesure * m = fileReader->prochaineMesure(parametres, filtrageMesure);
		
		
		// !!!!! \\ Est-ce que c'est vraiment une bonne idée de passer par une ptr ?? 
		// Il y aura beaucoup beaucoup beaucoup de new/delete donc très très bof en perf 

		//Si m == nullptr, alors il n'y a plus rien à lire 
		if (m == nullptr)
		{
			finLecture = true; 
			break;
		}
		
		// On regarde si la mesure sélectionnée est concerne le capteur à surveiller
		if (capteurID.compare(m->getCapteur()->getSensorID()) == 0)
		{
			// Dossier de spé
			//Observe les données générées par le capteur pour détecter 
			// - une absence de données(capteur HS) => OK
			// - ou la présence de données aberrantes(capteur défectueux) :
			// - valeurs négatives => OK 
			// valeurs trop élevées => impossible car dépend de l'unité 
			// (rien ne dit que les unités seront toujours les mêmes)  
			// oscillations trop rapides => c'est-à-dire ??

			if (m->getValue() == NULL || m->getValue() < 0)
			{
				bonEtat = false;
				break;
			}

		}

		delete m;
		
	}

	return bonEtat;

}//----- End of surveillerComportementCapteur 


list<Capteur> * Service::surveillerComportementCapteurs(list<string> & capteursID, paramFiltrage & parametres)
{

	// Pour le mettre dans le tas sinon la liste se fait détruire à la fin de l'appel de la méthode
	list<Capteur> * liste_capteursDefectueux = new list<Capteur>;


	// id des capteurs défectueux
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
	// Pas nécessaire si géré dans lireCapteurs();

	/* A MODIFIER EN FONCTION DU FONCTIONNEMENT FINAL DE FILEREADER */

	/*
	Ci-dessous version avec list de string retournée (version précédente de lireCapteurs où il était nécessaire de faire capteur_id-> capteur)
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

	/* Version si map 
	*/

	// !!!!!!!!! \\  Quand on delete les Capteurs de la map ???
	for (unordered_map <string, Capteur*>::iterator it_map = capteurs.begin(); it_map != capteurs.end(); it_map++)
	{
		for (list<string> ::iterator it_id = liste_id_capteursDefectueux.begin(); it_id != liste_id_capteursDefectueux.end(); it_id++)
		{
			if (it_map->first.compare(*it_id) == 0
				&& find(liste_id_capteursDefectueux.begin(), liste_id_capteursDefectueux.end(), it_map->first) != liste_id_capteursDefectueux.end())
			{
				/* A décommenter quand problème avec const réglé 
				Capteur c = Capteur(it_map->second->getSensorID(), it_map->second->getPosition(), it_map->second->getDescription());

				liste_capteursDefectueux->push_back(c);
				*/

			}
		}
	}

	// delete les capteurs de la map pas possible à faire alors qu'il le faut car la map est CONST ... 
	for (unordered_map <string, Capteur*>::iterator it = capteurs.begin(); it != capteurs.end(); it++)
	{
		/* A décommenter quand problème avec const réglé */
		//delete it->second;
		// et clear() ???
	}
	
	//!\\ Attention : dans le CLI, ne pas oublier le delete
	return liste_capteursDefectueux;

}//----- End of surveillerComportementCapteurs



list<pair<Capteur, Capteur>> * Service:: obtenirCapteursSimilaires(struct tm & Date, int nbMesures)
// HYPOTHESES APPLIQUEES DANS L'ALGORITHME
// hypothèse 0 : les concentrations des particules mesurées à un instant t sont regroupées les unes à la suite des autres
// hypothèse 1 : on considère que deux capteurs ont pris leurs mesures au même moment si la différence entre leurs mesures est de +- 1 minute
// hypothèse 2 : un capteur à un instant t doit a des valeurs non null pour les 4 particules de l'air
// hypothèse 3 : en considérant l'hypothèse 1 valide, on suppose que tous les capteurs prennent leurs mesures en même temps
// (vrai dans le début du fichier .csv de mesures que j'ai lu)

// Algorithm :
{
	//On récupère tous les capteurs
	paramFiltrage param_capteurs = { NULL, NULL, NULL, NULL };
	unordered_map < std::string, Capteur * > map_capteurs = fileReader->lireCapteurs(param_capteurs, filtrageCapteur); // ne pas oublier de delete

	//On récupère tous les attributs
	unordered_map < std::string, Attribut * > map_attributs = fileReader->lireAttributs(); // ne pas oublier de delete

	unordered_map<string, unordered_map<string, vector<float> > > capteurs_mesures;
	//unordered_map<sensorID, unordered_map<AttributId, vector<value> > > capteurs_mesures;
	// AttributID = O3 etc.

	paramFiltrage parametres = { Date, NULL, NULL, NULL };

	// On classe les données pour faciliter le traitement
	for (int i = 0; i < nbMesures; i++)
	{
		Mesure * m = fileReader->prochaineMesure(parametres, filtrageMesure);

		unordered_map<string, unordered_map<string, vector<float> > >::iterator iterateur_sensorID = capteurs_mesures.find(m->getSensorID());
		
		if (iterateur_sensorID != capteurs_mesures.end())
		{			
			//unordered_map<string, vector<float>> attributId_valeur = iterateur_sensorID->second; // juste là pour m'aider à coder
			unordered_map<string, vector<float>> ::iterator iterateur_attributId = iterateur_sensorID->second.find(m->getAttribut()->getAttributID());
			
			if (iterateur_attributId != iterateur_sensorID->second.end())
			{
				//vector<float> N_valeurs = iterateur_attributId->second; // juste là pour m'aider à coder
				//N_valeurs[i] = m->getValue(); // juste là pour m'aider à coder

				iterateur_attributId->second[i] = m->getValue();
			}
			else
			{
				//A inserer
				vector <float> v;
				v[i] = m->getValue();
				iterateur_sensorID->second.insert(make_pair(m->getAttribut()->getAttributID(), v));
			}
		}
		else
		{
			//inserer
			vector <float> v;
			v[i] = m->getValue();
			unordered_map<string, vector<float> > map_a_inserer;
			map_a_inserer.insert(make_pair(m->getAttribut()->getAttributID(), v));
			capteurs_mesures.insert(make_pair(m->getCapteur()->getSensorID(), map_a_inserer));
		}

		delete m;
	}

	// Traitement
	list<pair<Capteur, Capteur>> * capteurs_similaires = new list<pair<Capteur, Capteur>>;
	//capteurs_mesures
	for (unordered_map<string, unordered_map<string, vector<float> > > ::iterator it_capteur1 = capteurs_mesures.begin(); it_capteur1 != capteurs_mesures.end(); it_capteur1++)
	{
		for (unordered_map<string, unordered_map<string, vector<float> > > ::iterator it_capteur2 = capteurs_mesures.begin(); it_capteur2 != capteurs_mesures.end(); it_capteur2++)
		{
			if (it_capteur1->first.compare(it_capteur2->first) != 0) 
			{
				unordered_map<string, vector<float> > ::iterator it_c1_O3 = it_capteur1->second.find("O3");
				unordered_map<string, vector<float> > ::iterator it_c1_NO2 = it_capteur1->second.find("NO2");
				unordered_map<string, vector<float> > ::iterator it_c1_SO2 = it_capteur1->second.find("SO2");
				unordered_map<string, vector<float> > ::iterator it_c1_PM10 = it_capteur1->second.find("PM10");

				unordered_map<string, vector<float> > ::iterator it_c2_O3 = it_capteur2->second.find("O3");
				unordered_map<string, vector<float> > ::iterator it_c2_NO2 = it_capteur2->second.find("NO2");
				unordered_map<string, vector<float> > ::iterator it_c2_SO2 = it_capteur2->second.find("SO2");
				unordered_map<string, vector<float> > ::iterator it_c2_PM10 = it_capteur2->second.find("PM10");

				bool similaire = true;
				for (int i = 0; i < nbMesures; i++)
				{

					// Que faire si les unités varient........ ?
					if (
						! (plusOuMoins(it_c1_O3->second[i], it_c2_O3->second[i], 15) &&
						plusOuMoins(it_c1_NO2->second[i], it_c2_NO2->second[i], 20) &&
						plusOuMoins(it_c1_SO2->second[i], it_c2_SO2->second[i], 15) &&
						plusOuMoins(it_c1_PM10->second[i], it_c2_PM10->second[i], 4))
						)
					{
						similaire = false;
					}

				}

				if (similaire == true)
				{
					//Vérfier si le couple n'est pas déjà présent
					for (list<pair<Capteur, Capteur>> ::iterator it_list = capteurs_similaires->begin(); it_list != capteurs_similaires->end(); it_list++)
					{
						if (
							! ((it_list->first.getSensorID().compare(it_capteur1->first) && it_list->second.getSensorID().compare(it_capteur2->first))
							||
							(it_list->first.getSensorID().compare(it_capteur2->first) && it_list->second.getSensorID().compare(it_capteur1->first))
							))
						{
							/* A décommenter dès que le problème avec les const sont réglés
							Capteur * c1_ptr = map_capteurs.find(it_capteur1->first)->second;
							Capteur c1 = Capteur(c1_ptr->getSensorID(), c1->getPosition(), c1->getDescription());
							Capteur * c2_ptr = map_capteurs.find(it_capteur2->first)->second;
							Capteur c2 = Capteur(c2_ptr->getSensorID(), c2->getPosition(), c2->getDescription());

							list.push_back(make_pair(c1, c2));
							*/
						}
					}

				}


			}

		}


	}

	// delete les capteurs de la map
	for (unordered_map <string, Capteur*>::iterator it = map_capteurs.begin(); it != map_capteurs.end(); it++)
	{
		/* A décommenter quand problème avec const réglé */
		//delete it->second;
		// et clear() ???
	}

	// delete les attributs de la map
	for (unordered_map <string, Attribut*>::iterator it = map_attributs.begin(); it != map_attributs.end(); it++)
	{
		/* A décommenter quand problème avec const réglé */
		//delete it->second;
		// et clear() ???
	}

	return capteurs_similaires;

}//----- End of obtenirCapteursSimilaires


bool Service::plusOuMoins(float v1, float v2, float ecart)
{
	if (abs(v1 - v2) <= ecart)
		return true;
	else
		return false;
}

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
		// cas 3 : aire totale considérée
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

