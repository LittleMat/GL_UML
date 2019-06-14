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

list<string> *Service ::surveillerComportementCapteurs(list<string> &capteursID, function<bool(Mesure &)> predicateMesure)
{
	if (capteursID.empty())
		throw "Illegal Argument Exception: empty list";
	if (predicateMesure == NULL)
		throw "Illegal Argument Exception";

	fileReader->lireAttributs();
	Territoire territoire(Point(0.0, 0.0), M_PI * RAYON_TERRE);
	string empty;
	using namespace placeholders;
	function<bool(Capteur &)> passAllCapteurs = bind(Service::filtrageCapteur, _1, cref(territoire), empty);
	function<bool(Capteur &)> predicateCapteurs = [passAllCapteurs, capteursID](Capteur &capteur) -> bool {
		if (capteursID.front().compare("*") == 0)
		{
			return passAllCapteurs(capteur);
		}
		else
		{
			return passAllCapteurs(capteur) && find(capteursID.begin(), capteursID.end(), capteur.getSensorID()) != capteursID.end();
		}
	};
	unordered_map<string, Capteur *> capteurs = fileReader->lireCapteurs(predicateCapteurs);
	fileReader->lireAttributs();

	//liste d'id de capteurs defectueux vide
	list<string> *liste_id_capteursDefectueux = new list<string>;

	fileReader->debutMesure();
	bool finLecture = false;
	function<bool(Mesure &)> predicateMesureWithCapteur = [predicateMesure, capteurs](Mesure &mesure) -> bool { return predicateMesure(mesure) && capteurs.find(mesure.getSensorID()) != capteurs.end(); };
	while (!finLecture)
	{
		// On selectionne les mesures qui satisfont les criteres de selection temporels
		const Mesure * m = fileReader->prochaineMesure(predicateMesureWithCapteur);

		//Si m == nullptr, alors il n'y a plus rien a lire
		if (m == nullptr)
		{
			finLecture = true;
			break;
		}

		if (m->getValue() < 0)
		{
			liste_id_capteursDefectueux->push_back(m->getSensorID());
		}
		delete m;
	}

	liste_id_capteursDefectueux->unique();
	capteursID.clear();

	return liste_id_capteursDefectueux;

} //----- End of surveillerComportementCapteurs

list<pair<string, string>> *Service ::obtenirCapteursSimilaires(struct tm & date, int nbMesures)
// HYPOTHESES APPLIQUEES DANS L'ALGORITHME
// hypothese 0 : les concentrations des particules mesurees a un instant t sont regroupees les unes a la suite des autres
// hypothese 1 : on considere que deux capteurs ont pris leurs mesures au meme moment si la difference entre leurs mesures est de +- 1 minute
// hypothese 2 : un capteur a un instant t doit a des valeurs non null pour les 4 particules de l'air
// hypothese 3 : en considerant l'hypothese 1 valide, on suppose que tous les capteurs prennent leurs mesures en meme temps
{

	fileReader->debutMesure();

	//On recupere tous les capteurs
	using namespace placeholders;
	Territoire earth(Point(0.0, 0.0), M_PI * RAYON_TERRE);
	string empty;
	function<bool(Capteur&)> predicateCapteur = bind(Service::filtrageCapteur,  _1, cref(earth), empty);
	unordered_map<std::string, Capteur *> map_capteurs = fileReader->lireCapteurs(predicateCapteur);

	//On recupere tous les attributs
	unordered_map<std::string, Attribut *> map_attributs = fileReader->lireAttributs();

	//Structure de données pour classer les mesures 
	// unordered_map<idCapteur, unordered_map <idAttribut,vector<Mesure>>> 
	unordered_map<string, unordered_map<string, vector<float>>> capteurs_mesures;

	function<bool(Mesure&)> predicateMesure = bind(Service::filtrageMesure, _1, tm(), date);

	// On classe les donnees pour faciliter le traitement
	// Initialisation avec des -1 
	for (unordered_map<std::string, Capteur *>::iterator it = map_capteurs.begin(); it != map_capteurs.end(); it++)
	{

		unordered_map<string, vector<float>> map_temp;
		vector<float> vect;
		for (int i = 0; i < nbMesures; i++)
		{
			vect.push_back(-1);
		}
		map_temp.insert(make_pair("O3", vect));
		map_temp.insert(make_pair("NO2", vect));
		map_temp.insert(make_pair("SO2", vect));
		map_temp.insert(make_pair("PM10", vect));

		capteurs_mesures.insert(make_pair(it->first, map_temp));
	}

	//Remplissage avec les mesures lues
	for (int i = 0; i < nbMesures; i++)
	{
		Mesure *m = fileReader->prochaineMesure(predicateMesure);

		if (m == nullptr)
			break;

		// Etape de selection du capteur
		// Si dans la map des capteurs selectionnes par les fonctions de filtrage spaciales
		// le capteur de la mesure est present, c'est qu'il faut anaylser ce capteur

		unordered_map<std::string, Capteur *>::iterator trouveCapteur = map_capteurs.find(m->getSensorID());
		if (trouveCapteur != map_capteurs.end())
		{
			unordered_map<string, unordered_map<string, vector<float>>>::iterator iterateur_sensorID = capteurs_mesures.find(m->getSensorID());

			if (iterateur_sensorID != capteurs_mesures.end())
			{
				unordered_map<string, vector<float>>::iterator iterateur_attributId = iterateur_sensorID->second.find(m->getAttributID());

				for (int ii = 0; ii < nbMesures; ii++)
				{
					if (iterateur_attributId->second[ii] == -1)
					{
						iterateur_attributId->second[ii] = m->getValue();
						break;
					}
				}
			}
		}

		delete m;
	}

	// Remplissage des zones vides
	/*
	for (unordered_map<string, unordered_map<string, vector<float>>>::iterator it = capteurs_mesures.begin(); it != capteurs_mesures.end(); it++)
	{
		for (unordered_map<string, vector<float>>::iterator it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
		{
			for (int ii = 0; ii < nbMesures; ii++)
			{
				if (it_2->second[ii] == -1)
				{
					it_2->second[ii] = 0;
				}
			}
		}
	}
	*/

	// Traitement
	list<pair<string, string>> *capteurs_similaires = new list<pair<string, string>>;

	for (unordered_map<string, unordered_map<string, vector<float>>>::iterator it_capteur1 = capteurs_mesures.begin(); it_capteur1 != capteurs_mesures.end(); it_capteur1++)
	{
		for (unordered_map<string, unordered_map<string, vector<float>>>::iterator it_capteur2 = capteurs_mesures.begin(); it_capteur2 != capteurs_mesures.end(); it_capteur2++)
		{
			if (it_capteur1->first.compare(it_capteur2->first) != 0)
			{
				unordered_map<string, vector<float>>::iterator it_c1_O3 = it_capteur1->second.find("O3");
				unordered_map<string, vector<float>>::iterator it_c1_NO2 = it_capteur1->second.find("NO2");
				unordered_map<string, vector<float>>::iterator it_c1_SO2 = it_capteur1->second.find("SO2");
				unordered_map<string, vector<float>>::iterator it_c1_PM10 = it_capteur1->second.find("PM10");

				unordered_map<string, vector<float>>::iterator it_c2_O3 = it_capteur2->second.find("O3");
				unordered_map<string, vector<float>>::iterator it_c2_NO2 = it_capteur2->second.find("NO2");
				unordered_map<string, vector<float>>::iterator it_c2_SO2 = it_capteur2->second.find("SO2");
				unordered_map<string, vector<float>>::iterator it_c2_PM10 = it_capteur2->second.find("PM10");

				bool similaire = true;

				for (int i = 0; i < nbMesures; i++)
				{
					if (it_c1_O3->second[i] == -1 || it_c2_O3->second[i] == -1
						|| it_c1_NO2->second[i] == -1 || it_c2_NO2->second[i] == -1
						|| it_c1_SO2->second[i] == -1 || it_c2_SO2->second[i] == -1
						|| it_c1_PM10->second[i] == -1 || it_c2_PM10->second[i] == -1)
					{
						similaire = false;
						break;
					}
					similaire = similaire && (plusOuMoins(it_c1_O3->second[i], it_c2_O3->second[i], 15) &&
											  plusOuMoins(it_c1_NO2->second[i], it_c2_NO2->second[i], 20) &&
											  plusOuMoins(it_c1_SO2->second[i], it_c2_SO2->second[i], 15) &&
											  plusOuMoins(it_c1_PM10->second[i], it_c2_PM10->second[i], 4));
				}

				if (similaire == true)
				{
					capteurs_similaires->push_back(make_pair(it_capteur1->first, it_capteur2->first));
				}
			}
		}
	}
	return capteurs_similaires;

}//----- End of obtenirCapteursSimilaires

bool Service::plusOuMoins(float v1, float v2, float ecart)
{
	return (abs(v1 - v2) <= ecart);
}//----- End of plusOuMoins

tuple<int, list<pair<string, float>>, float> Service::calculerQualite(string &capteurId, function<bool(Mesure &)> predicateMesure, function<float(Capteur &)> fiabilite)
{

	fileReader->debutMesure();

	function<bool(Capteur &)> predicateCapteur = [capteurId, fiabilite](Capteur &capteur) -> bool { return fiabilite(capteur) > 0 && (capteurId.empty() || capteur.getSensorID() == capteurId); };

	unordered_map<string, Attribut *> attributs = fileReader->lireAttributs();
	unordered_map<string, Capteur *> capteurs = fileReader->lireCapteurs(predicateCapteur);
	function<bool(Mesure &)> predicateMesures = [capteurs, predicateMesure](Mesure &mesure) -> bool { return predicateMesure(mesure) && capteurs.find(mesure.getSensorID()) != capteurs.end(); };
	int nbMes_O3 = 0;
	int nbMes_NO2 = 0;
	int nbMes_SO2 = 0;
	int nbMes_PM10 = 0;

	float somme_concentrations_O3 = 0;
	float somme_concentrations_NO2 = 0;
	float somme_concentrations_SO2 = 0;
	float somme_concentrations_PM10 = 0;

	float fiabilite_O3 = 0;
	float fiabilite_NO2 = 0;
	float fiabilite_SO2 = 0;
	float fiabilite_PM10 = 0;

	bool finLecture = false;
	while (finLecture == false)
	{
		// On recupere et lit une mesure
		const Mesure *m = fileReader->prochaineMesure(predicateMesures);

		if (m == nullptr)
		{
			finLecture = true;
			break;
		}
		Capteur *capteur = capteurs[m->getSensorID()];
		// On calule l'indice de fiabilite
		float fiab = fiabilite(*capteur);

		// Analyse de la donnee lue
		if (m->getAttributID().compare("O3") == 0)
		{
			somme_concentrations_O3 += m->getValue();
			fiabilite_O3 += fiab;
			nbMes_O3++;
		}
		else if (m->getAttributID().compare("NO2") == 0)
		{
			somme_concentrations_NO2 += m->getValue();
			fiabilite_NO2 += fiab;
			nbMes_NO2++;
		}
		else if (m->getAttributID().compare("SO2") == 0)
		{
			somme_concentrations_SO2 += m->getValue();
			fiabilite_SO2 += fiab;
			nbMes_SO2++;
		}
		else if (m->getAttributID().compare("PM10") == 0)
		{
			somme_concentrations_PM10 += m->getValue();
			fiabilite_PM10 += fiab;
			nbMes_PM10++;
		}
		delete m;
	}

	// On calcule les moyennes
	float moyenne_concentrations_O3 = -1;
	float moyenne_concentrations_NO2 = -1;
	float moyenne_concentrations_SO2 = -1;
	float moyenne_concentrations_PM10 = -1;

	float moyenne_fiabilite_O3 = -1;
	float moyenne_fiabilite_NO2 = -1;
	float moyenne_fiabilite_SO2 = -1;
	float moyenne_fiabilite_PM10 = -1;

	if (nbMes_O3 != 0)
	{
		moyenne_concentrations_O3 = somme_concentrations_O3 / nbMes_O3;
		moyenne_fiabilite_O3 = fiabilite_O3 / nbMes_O3;
	}
	if (nbMes_NO2 != 0)
	{
		moyenne_concentrations_NO2 = somme_concentrations_NO2 / nbMes_NO2;
		moyenne_fiabilite_NO2 = fiabilite_NO2 / nbMes_NO2;
	}
	if (nbMes_SO2 != 0)
	{
		moyenne_concentrations_SO2 = somme_concentrations_SO2 / nbMes_SO2;
		moyenne_fiabilite_SO2 = fiabilite_SO2 / nbMes_SO2;
	}
	if (nbMes_PM10 != 0)
	{
		moyenne_concentrations_PM10 = somme_concentrations_PM10 / nbMes_PM10;
		moyenne_fiabilite_PM10 = fiabilite_PM10 / nbMes_PM10;
	}

	list<pair<string, float>> concentrations;
	concentrations.push_back(make_pair("O3", moyenne_concentrations_O3));
	concentrations.push_back(make_pair("NO2", moyenne_concentrations_NO2));
	concentrations.push_back(make_pair("SO2", moyenne_concentrations_SO2));
	concentrations.push_back(make_pair("PM10", moyenne_concentrations_PM10));

	//Calcul Indice ATMO
	float indiceMax = -1.0;
	int indiceATMO;
	for (list<pair<string, float>>::iterator it = concentrations.begin(); it != concentrations.end(); it++)
	{
		indiceATMO = calculIndiceATMO(it->first, it->second);
		if (indiceATMO > indiceMax)
		{
			indiceMax = indiceATMO;
		}
	}
	indiceATMO = indiceMax;

	//Calcul fiabilité minimale
	float fiabilites[4] = {moyenne_fiabilite_O3, moyenne_fiabilite_NO2, moyenne_fiabilite_SO2, moyenne_fiabilite_PM10};
	float fiabiliteMin = 1;
	for (int i = 0; i < 4; i++)
	{
		if (fiabiliteMin >= fiabilites[i])
		{
			fiabiliteMin = fiabilites[i];
		}
	}

	tuple<int, list<pair<string, float>>, float> resultat_final = make_tuple(indiceATMO, concentrations, fiabiliteMin * 100);

	return resultat_final;

} //----- End of calculerQualite

//-------------------------------------------- Constructor - destructor
Service ::Service(const std::string &nomFichierCapteurs, const string &nomFichierAttributs, const std::list<std::string> &nomFichiersMesures)
// Algorithm :
{
#ifdef MAP
	cout << "Appel au constructeur de <Service>" << endl;
#endif
	fileReader = new FileReader(nomFichierCapteurs, nomFichierAttributs, nomFichiersMesures);

} //----- End of Service

Service::~Service()
// Algorithm :
{
#ifdef MAP
	cout << "Appel au destructeur de <Service>" << endl;
#endif
	delete fileReader;
} //----- End of ~Service

int Service :: calculIndiceATMO (string substance, float valeur)
{
	int indiceATMO = -1;
	if (substance.compare("O3") == 0)
	{
		if (valeur >= 0 && valeur <= 29)
		{
			indiceATMO = 1;
		}
		else if (valeur >= 30 && valeur <= 54)
		{
			indiceATMO = 2;
		}
		else if (valeur >= 55 && valeur <= 79)
		{
			indiceATMO = 3;
		}
		else if (valeur >= 80 && valeur <= 104)
		{
			indiceATMO = 4;
		}
		else if (valeur >= 105 && valeur <= 129)
		{
			indiceATMO = 5;
		}
		else if (valeur >= 130 && valeur <= 149)
		{
			indiceATMO = 6;
		}
		else if (valeur >= 150 && valeur <= 179)
		{
			indiceATMO = 7;
		}
		else if (valeur >= 180 && valeur <= 209)
		{
			indiceATMO = 8;
		}
		else if (valeur >= 210 && valeur <= 239)
		{
			indiceATMO = 9;
		}
		else if (valeur >= 240)
		{
			indiceATMO = 10;
		}
	}
	else if (substance.compare("NO2") == 0)
	{
		if (valeur >= 0 && valeur <= 29)
		{
			indiceATMO = 1;
		}
		else if (valeur >= 30 && valeur <= 54)
		{
			indiceATMO = 2;
		}
		else if (valeur >= 55 && valeur <= 84)
		{
			indiceATMO = 3;
		}
		else if (valeur >= 85 && valeur <= 109)
		{
			indiceATMO = 4;
		}
		else if (valeur >= 110 && valeur <= 134)
		{
			indiceATMO = 5;
		}
		else if (valeur >= 135 && valeur <= 164)
		{
			indiceATMO = 6;
		}
		else if (valeur >= 165 && valeur <= 199)
		{
			indiceATMO = 7;
		}
		else if (valeur >= 200 && valeur <= 274)
		{
			indiceATMO = 8;
		}
		else if (valeur >= 275 && valeur <= 399)
		{
			indiceATMO = 9;
		}
		else if (valeur >= 400)
		{
			indiceATMO = 10;
		}
	}
	else if (substance.compare("SO2") == 0)
	{
		if (valeur >= 0 && valeur <= 39)
		{
			indiceATMO = 1;
		}
		else if (valeur >= 40 && valeur <= 79)
		{
			indiceATMO = 2;
		}
		else if (valeur >= 80 && valeur <= 119)
		{
			indiceATMO = 3;
		}
		else if (valeur >= 120 && valeur <= 159)
		{
			indiceATMO = 4;
		}
		else if (valeur >= 160 && valeur <= 199)
		{
			indiceATMO = 5;
		}
		else if (valeur >= 200 && valeur <= 249)
		{
			indiceATMO = 6;
		}
		else if (valeur >= 250 && valeur <= 299)
		{
			indiceATMO = 7;
		}
		else if (valeur >= 300 && valeur <= 399)
		{
			indiceATMO = 8;
		}
		else if (valeur >= 400 && valeur <= 499)
		{
			indiceATMO = 9;
		}
		else if (valeur >= 500)
		{
			indiceATMO = 10;
		}
	}
	else if (substance.compare("PM10") == 0)
	{
		if (valeur >= 0 && valeur <= 6)
		{
			indiceATMO = 1;
		}
		else if (valeur >= 7 && valeur <= 13)
		{
			indiceATMO = 2;
		}
		else if (valeur >= 14 && valeur <= 20)
		{
			indiceATMO = 3;
		}
		else if (valeur >= 21 && valeur <= 27)
		{
			indiceATMO = 4;
		}
		else if (valeur >= 28 && valeur <= 34)
		{
			indiceATMO = 5;
		}
		else if (valeur >= 35 && valeur <= 41)
		{
			indiceATMO = 6;
		}
		else if (valeur >= 42 && valeur <= 49)
		{
			indiceATMO = 7;
		}
		else if (valeur >= 50 && valeur <= 64)
		{
			indiceATMO = 8;
		}
		else if (valeur >= 65 && valeur <= 79)
		{
			indiceATMO = 9;
		}
		else if (valeur >= 80)
		{
			indiceATMO = 10;
		}
	}
	return indiceATMO;
}//----- End of calculIndiceATMO

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Protected methods

/* Algorithm :
 * Si capteurId == null,
 * On voit si fiabilite est 0.
 * Sinon, on voit si le capteurId est correcte.
 */

function<bool(const Capteur &, const Territoire &, const string &)> Service::filtrageCapteur = [](const Capteur &capteur, const Territoire &territoire, const string &capteurId) -> bool {
	return (!capteurId.empty() && capteur.getSensorID().compare(capteurId) == 0) || (capteurId.empty() && fiabilite(capteur, territoire) > 0);
};

function<float(const Capteur &, const Territoire &)> Service::fiabilite = [](const Capteur &capteur, const Territoire &territoire) -> float {
	// On calule l'indice de fiabilite
	float fiabilite = 1.0; //il est de 1 pour l'aire totale ou un capteur en particulier

	// Un point
	if (territoire.getRayon() == 0)
	{

		fiabilite = 1 - territoire.getCentre().distance(capteur.getPosition()) / 10;
	}
	// Un territoire cible
	else
	{
		float distance = territoire.getCentre().distance(capteur.getPosition());
		fiabilite = distance < territoire.getRayon() ? 1 : 1 - (distance - territoire.getRayon()) / (0.1 * territoire.getRayon());
	}
	if (fiabilite < 0)
		fiabilite = 0;
	return fiabilite;
};

// Algorithm :
// Si dateInf != null && dateSup == null (a partir de l'instant t)
// On regarde si mesure.getTimetamp() > dateInf
// Si oui : on retourne true
// Sinon : on retourne false

// Si dateInf == null && dateSup != null (a un instant t)
// On regarde alors si mesure.getTimestamp() appartient a l'intervalle  [dateInf (en sec) - 60 (min) * 60 sec, dateInf (en sec) + 60 (min) * 60 sec]
// Si oui : on retourne true
// Sinon : on retourne false

// Si  dateSup != null && dateInf != null (periode)
// On regarde si mesure.getTimestamp() >= dateInf et mesure.getTimestamp() <= dateSup
// Si oui : on retourne true
// Sinon : on retourne false

// Si dateSup == null && dateInf == null (tout l'historique)
// on retourne true

function<bool(Mesure &, struct tm &, struct tm &)> Service::filtrageMesure = [](Mesure &mesure, struct tm &dateInf, struct tm &dateSup) -> bool {
	bool mesureAPrendre = false;
	struct tm time = mesure.getTimestamp();
	time_t timeMes = mktime(&time);

	// A un instant t
	if ((dateNull(dateSup) == false) && (dateNull(dateInf) == true))
	{
		time_t timeSup = mktime(&dateSup);

		if ((timeMes >= timeSup - 3600) && (timeMes <= timeSup + 3600))
			mesureAPrendre = true;
	}
	// Une periode
	else if ((dateNull(dateSup) == false) && (dateNull(dateInf) == false))
	{
		time_t timeInf = mktime(&dateInf);
		time_t timeSup = mktime(&dateSup);
		if (timeMes >= timeInf && timeMes <= timeSup)
		{
			mesureAPrendre = true;
		}
	}
	// Tout l'historique
	else if ((dateNull(dateSup) == true) && (dateNull(dateInf) == true))
	{
		mesureAPrendre = true;
	}

	// A partir d'un instant t
	else if ((dateNull(dateInf) == false) && (dateNull(dateSup) == true))
	{
		time_t timeInf = mktime(&dateInf);
		if (timeMes >= timeInf)
			mesureAPrendre = true;
	}
	return mesureAPrendre;
};

bool Service::dateNull(struct tm &date)
{
	if (date.tm_hour == 0 && date.tm_min == 0 && date.tm_sec == 0 && date.tm_mday == 0 && date.tm_mon == 0 && date.tm_year == 0)
		return true;
	else
		return false;
}
