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

bool Service :: surveillerComportementCapteur ( string capteurID, paramFiltrage & parametres )
{
	std :: cout << "Appel surveillerComportementCapteur" << endl;
	bool bonEtat = true;
	bool finLecture = false;
	fileReader->lireAttributs();
	fileReader->lireCapteurs(parametres, Service::filtrageCapteur);
	fileReader->debutMesure();
	while (finLecture == false)
	{
		// On s�lectionne les mesures qui satisfont les crit�res de s�lection temporelles
		const Mesure * m = fileReader->prochaineMesure( parametres, filtrageMesure );
		// std :: cout << "lecture de mesure " << endl;
		//Si m == nullptr, alors il n'y a plus rien � lire 
		if ( m == nullptr )
		{
			finLecture = true; 
			// std::cout << "fin de la lecture " << endl;
			break;
		}
		//cout << " mesure lue :" << m->getValue() << endl;
		
		// On regarde si la mesure s�lectionn�e concerne le capteur � surveiller
		if ( capteurID.compare(m-> getSensorID () ) == 0 )
		{
			//cout << " mesure du capteur lue :" << m->getValue() <<  endl;

			if ( m -> getValue () < 0)
			{
				bonEtat = false;
				delete m;
				break;
			}
		}
		delete m;		
	}

	return bonEtat;

}//----- End of surveillerComportementCapteur 


list <string> * Service :: surveillerComportementCapteurs (list <string> & capteursID)
{
	if (capteursID.empty())
		throw "Illegal Argument Exception: empty list";
	fileReader->lireAttributs();
	paramFiltrage param_capteurs{ tm() ,tm() , Territoire(new Point(0.0, 0.0), 0), "" };
	unordered_map < string, Capteur * > map_tous_les_capteurs = fileReader->lireCapteurs(param_capteurs, filtrageCapteur);
	if (capteursID.front().compare("*") == 0)
	{
		capteursID.clear();
		for (auto it : map_tous_les_capteurs)
		{
			capteursID.push_back(it.first);
		}
	}


	//liste d'id de capteurs d�fectueux
	list <string> * liste_id_capteursDefectueux = new list<string>;
	/*
	std::cout << endl;
	std::cout << "contenu liste_id_capteursDefectueux apr�s init" << endl;
	std::cout << endl;
	*/
	/*
	if (liste_id_capteursDefectueux->empty())
	{

		for (list<string> ::iterator ii = liste_id_capteursDefectueux->begin(); ii != liste_id_capteursDefectueux->end(); ii++)
		{
			// std::cout << *ii << endl;
		}
	}
	else
	{
		std::cout << "liste vide " << endl;
	}
	*/
	for (list <string> :: iterator i = capteursID.begin(); i != capteursID.end(); i++)
	{
		paramFiltrage param { tm() ,tm() , Territoire(new Point(0.0, 0.0), 0)  , *i };

		if (surveillerComportementCapteur(*i, param) == false)
		{
			liste_id_capteursDefectueux->push_back(*i);
		}
	}
	liste_id_capteursDefectueux->unique();
	capteursID.clear();
	
	return liste_id_capteursDefectueux;

}//----- End of surveillerComportementCapteurs



list <pair < string, string > > * Service :: obtenirCapteursSimilaires( struct tm & Date, int nbMesures )
// HYPOTHESES APPLIQUEES DANS L'ALGORITHME
// hypoth�se 0 : les concentrations des particules mesur�es � un instant t sont regroup�es les unes � la suite des autres
// hypoth�se 1 : on consid�re que deux capteurs ont pris leurs mesures au m�me moment si la diff�rence entre leurs mesures est de +- 1 minute
// hypoth�se 2 : un capteur � un instant t doit a des valeurs non null pour les 4 particules de l'air
// hypoth�se 3 : en consid�rant l'hypoth�se 1 valide, on suppose que tous les capteurs prennent leurs mesures en m�me temps
// (vrai dans le d�but du fichier .csv de mesures que j'ai lu)

// Algorithm :
{

	fileReader->debutMesure();

	//On r�cup�re tous les capteurs
	paramFiltrage param_capteurs{ tm() ,tm() , Territoire(new Point(0.0, 0.0), 0), "" };

	unordered_map < std::string, Capteur * > map_capteurs = fileReader->lireCapteurs(param_capteurs, filtrageCapteur);

	//On r�cup�re tous les attributs
	unordered_map < std::string, Attribut * > map_attributs = fileReader->lireAttributs(); 

	unordered_map< string, unordered_map< string, vector<float> > > capteurs_mesures;
	//unordered_map<sensorID, unordered_map<AttributId, vector<value> > > capteurs_mesures;

	paramFiltrage parametres { Date ,tm() , Territoire(new Point(0.0, 0.0), 0)  , "" };


	// On classe les donn�es pour faciliter le traitement

	//init : 
	// Pour chaque capteurs s�lectionn�s par la fonction de filtrage 
	// et on ajoute une map dont les cl�s sont les attributs possibles des capteurs et les valeurs, des vecteurs contenant nbMesures �lements � 0.0
	/*
	for (unordered_map < std::string, Capteur * > ::iterator it = map_capteurs.begin(); it != map_capteurs.end(); it++)
	{	
		unordered_map<string, vector<float>> map;
		for (unordered_map < std::string, Attribut * > ::iterator it_att = map_attributs.begin(); it_att != map_attributs.end(); it_att++)
		{
			vector <float> val;
			for (int i = 0; i < nbMesures; i++)
			{
				val.push_back(0.0);
				
			}
			map.insert(make_pair(it_att->first, val));
		}
		capteurs_mesures.insert(make_pair(it->first, map));

	}


	// Visualiser la structure 
	cout << "Visualisation de la structure apr�s init" << endl;
	cout << endl;
	cout << "**********************************************" << endl;
	for (unordered_map< string, unordered_map< string, vector<float> > > ::iterator it = capteurs_mesures.begin(); it != capteurs_mesures.end(); it++)
	{
		cout << "Capteur = " << it->first << endl;
		for (unordered_map< string, vector<float> > ::iterator it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
		{
			cout << "Attribut = " << it_2->first << endl;
			for (vector<float> ::iterator it_3 = it_2->second.begin(); it_3 != it_2->second.end(); it_3++)
			{
				cout << *it_3 << " ; ";
			}
		}
	}
	cout << "**********************************************" << endl;
	cout << endl;
	cout << endl;

	*/


	for (int i = 0; i < nbMesures; i++)
	{
		Mesure * m = fileReader->prochaineMesure(parametres, filtrageMesure);

		// �tape de s�lection du capteur
		// Si dans la map des capteurs s�lectionn�s par les fonctions de filtrage spaciaux
		// le capteur de la mesure est pr�sent, c'est qu'il faut anaylser ce capteur

		unordered_map < std::string, Capteur * > :: iterator trouveCapteur = map_capteurs.find(m->getSensorID());
		if (trouveCapteur != map_capteurs.end())
		{
			unordered_map<string, unordered_map<string, vector<float> > >::iterator iterateur_sensorID = capteurs_mesures.find(m->getSensorID());

			if (iterateur_sensorID != capteurs_mesures.end())
			{
				// On a trouv� sensorID
				//unordered_map<string, vector<float>> attributId_valeur = iterateur_sensorID->second; // juste l� pour m'aider � coder
				unordered_map<string, vector<float>> ::iterator iterateur_attributId = iterateur_sensorID->second.find(m->getAttributID());

				// On a trouv� attributID
				if (iterateur_attributId != iterateur_sensorID->second.end())
				{
					//vector<float> N_valeurs = iterateur_attributId->second; // juste l� pour m'aider � coder
					//N_valeurs[i] = m->getValue(); // juste l� pour m'aider � coder

					iterateur_attributId->second.push_back(m->getValue());
				}
				
				else
				{
					//A inserer dans la map
					vector <float> v;
					v.push_back( m->getValue());
					iterateur_sensorID->second.insert(make_pair(m->getAttributID(), v));
				}
				
			}
			
			else
			{
				//la valeur de l'id du capteur n'existe pas : A inserer dans la map
				vector <float> v;
				v.push_back(m->getValue());
				unordered_map<string, vector<float> > map_a_inserer;
				map_a_inserer.insert(make_pair(m->getAttributID(), v));
				capteurs_mesures.insert(make_pair(m->getSensorID(), map_a_inserer));
			}
		}

		delete m;
	}


	// Visualiser la structure 
	std::cout << "Visualisation de la structure avant remplissage du vide" << endl;
	std::cout << endl;
	std::cout << "*********************************************" << endl;
	for (unordered_map< string, unordered_map< string, vector<float> > > ::iterator it = capteurs_mesures.begin(); it != capteurs_mesures.end(); it++)
	{
		std::cout << "Capteur = " << it->first << endl;
		for (unordered_map< string, vector<float> > ::iterator it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
		{
			std::cout << "Attribut = " << it_2->first << endl;
			for (vector<float> ::iterator it_3 = it_2->second.begin(); it_3 != it_2->second.end(); it_3++)
			{
				std::cout << *it_3 << " ; ";
			}
		}
		std::cout << endl;
	}
	std::cout << "*********************************************" << endl;
	std::cout << endl;
	std::cout << endl;



	// Remplissage des zones vides
	for (unordered_map< string, unordered_map< string, vector<float> > > ::iterator it = capteurs_mesures.begin(); it != capteurs_mesures.end(); it++)
	{
		for (unordered_map< string, vector<float> > ::iterator it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
		{
			for (int i = 0; size(it_2->second) < nbMesures; i++)
			{
				it_2->second.push_back(0.0);
			}
			/*
			vector<float> ::iterator it_3 = it_2->second.end();
			fill(it_3, it_3 + nbMesures, 0.0); // FAUX : A CORRIGER
			*/
		}
	}




	// Visualiser la structure 
	std :: cout << "Visualisation de la structure apr�s lecture" << endl;
	std::cout << endl;
	std::cout << "----------------------------------------------" << endl;
	for (unordered_map< string, unordered_map< string, vector<float> > > ::iterator it = capteurs_mesures.begin(); it != capteurs_mesures.end(); it++)
	{
		std::cout << "Capteur = " << it->first << endl;
		for (unordered_map< string, vector<float> > ::iterator it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
		{
			std::cout << "Attribut = " << it_2->first << endl;
			for (vector<float> ::iterator it_3 = it_2->second.begin(); it_3 != it_2->second.end(); it_3++)
			{
				std::cout << *it_3 << " ; ";
			}
			std::cout << endl;
		}
		std::cout << endl;
	}
	std::cout << "----------------------------------------------" << endl;
	std::cout << endl;
	std::cout << endl;




	// Traitement
	list<pair<string, string>> * capteurs_similaires = new list<pair<string, string>>;
	
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
					similaire = similaire && (plusOuMoins(it_c1_O3->second[i], it_c2_O3->second[i], 15) &&
						plusOuMoins(it_c1_NO2->second[i], it_c2_NO2->second[i], 20) &&
						plusOuMoins(it_c1_SO2->second[i], it_c2_SO2->second[i], 15) &&
						plusOuMoins(it_c1_PM10->second[i], it_c2_PM10->second[i], 4));

				}
	

				if (similaire == true)
				{
					cout << it_capteur1->first << " et " << it_capteur2->first << " sont similaires " << endl;

					capteurs_similaires->push_back(make_pair(it_capteur1->first, it_capteur2->first));


					/*
					//V�rfier si le couple n'est pas d�j� pr�sent
					for (list<pair<Capteur, Capteur>> ::iterator it_list = capteurs_similaires->begin(); it_list != capteurs_similaires->end(); it_list++)
					{
						if (
							! ((it_list->first.getSensorID().compare(it_capteur1->first) && it_list->second.getSensorID().compare(it_capteur2->first))
							||
							(it_list->first.getSensorID().compare(it_capteur2->first) && it_list->second.getSensorID().compare(it_capteur1->first))
							))
						{

							cout << "nouveaux capteurs " << endl;
							// On instancie des nouveaux objet capteur dans la liste parce que sinon c'est ing�rable (delete)
							Capteur * c1_ptr = map_capteurs.find(it_capteur1->first)->second;
							Point * p1 = new Point(c1_ptr->getPosition()->getLongitude(), c1_ptr->getPosition()->getLatitude());
							Capteur c1 = Capteur(c1_ptr->getSensorID(), p1, c1_ptr->getDescription());

							Capteur * c2_ptr = map_capteurs.find(it_capteur2->first)->second;
							Point * p2 = new Point(c2_ptr->getPosition()->getLongitude(), c2_ptr->getPosition()->getLatitude());
							Capteur c2 = Capteur(c2_ptr->getSensorID(), p2, c2_ptr->getDescription());

							capteurs_similaires->push_back(make_pair(c1, c2));
							
						}
					}
					*/

				}


			}

		}

	}
	cout << "capteurs_similaires est de taille " << (capteurs_similaires->size()) << endl;
	return capteurs_similaires;

}//----- End of obtenirCapteursSimilaires


bool Service::plusOuMoins(float v1, float v2, float ecart)
{
	return(abs(v1 - v2) <= ecart);
}

tuple<int, list<pair<string, float>>, float>  Service::calculerQualite(paramFiltrage & parametres)
{

	cout << "Calculer qualite air" << endl;
	fileReader->debutMesure();
	unordered_map <string, Attribut *> attributs = fileReader->lireAttributs();
	unordered_map <string, Capteur *> capteurs = fileReader->lireCapteurs(parametres, filtrageCapteur);
	cout << "capteurs " << endl;
	for (auto i : capteurs) {
		cout << i.first << endl;
	}
	

	// Surveiller les capteurs et enlever de la liste les capteurs d�faillants
	/*
	list<string> liste_capteur =
	list <Capteur> * listeCapteursDefectueux = surveillerComportementCapteurs(list <string> & capteursID, paramFiltrage & parametres)
	surveillerComportementCapteurs(un)

	*/

	list <pair<float, float>> mesures_O3;
	list <pair<float, float>> mesures_NO2;
	list <pair<float, float>> mesures_SO2;
	list <pair<float, float>> mesures_PM10;

	bool finLecture = false;
	while (finLecture == false)
	{
		// On r�cup�re lit une mesure
		const Mesure * m = fileReader->prochaineMesure(parametres, filtrageMesure);
		
		if (m == nullptr)
		{
			finLecture = true;
			break;
		}

		// On calule l'indice de fiabilit� 
		float fiabilite = 1.0; //il est de 1 pour l'aire totale ou un capteur en particulier

		//On ne consid�re pas un capteur en particulier
		if (parametres.capteurId.compare("") == 0)
		{
			// Un point  
			if (parametres.territoire.getRayon() == 0
				&& !(parametres.territoire.getCentre()->getLatitude() == 0 && parametres.territoire.getCentre()->getLongitude() == 0))
			{

				fiabilite = 1 - parametres.territoire.getCentre()->distance(capteurs.at(m->getSensorID())->getPosition())/10;
			}
			// Un territoire cibl�
			else if (parametres.territoire.getRayon() > 0
				&& !(parametres.territoire.getCentre()->getLatitude() == 0 && parametres.territoire.getCentre()->getLongitude() == 0)
				)
			{
				fiabilite = 1 - (parametres.territoire.getCentre()->distance(capteurs.at(m->getSensorID())->getPosition()) - parametres.territoire.getRayon()) / 50;
			}

		}
		if (fiabilite < 0)
			fiabilite = 0;

		// On ins�re la mesure dans la liste appropri�e
		if (m->getAttributID().compare("O3") == 0)
		{
			mesures_O3.push_back(make_pair(m->getValue(), fiabilite));
		}
		else if (m->getAttributID().compare("SO2") == 0)
		{
			mesures_SO2.push_back(make_pair(m->getValue(), fiabilite));

		}
		else if (m->getAttributID().compare("NO2") == 0)
		{
			mesures_NO2.push_back(make_pair(m->getValue(), fiabilite));

		}
		else if (m->getAttributID().compare("PM10") == 0)
		{
			mesures_PM10.push_back(make_pair(m->getValue(), fiabilite));
		}

		delete m;
	}

	//Calcul des concentrations moyennes + fiabilite
	
	list<pair<string, float>> concentrations;
	list<pair<string, float>> fiabilites;
	float somme_concentrationMoyenne = 0.0;
	float concentrationMoyenne = -1.0;
	float somme_fiabiliteMoyenne = 0.0; //Ou prendre le max comme pour les incertitudes en chimie ?
	float fiabiliteMoyenne = -1.0;

	if (!mesures_O3.empty())
	{
		for (list<pair<float, float>> ::iterator it = mesures_O3.begin(); it != mesures_O3.end(); it++)
		{
			somme_concentrationMoyenne += it->first;
			somme_fiabiliteMoyenne += it->second;
		}
		concentrationMoyenne = somme_concentrationMoyenne / mesures_O3.size();
		fiabiliteMoyenne = somme_fiabiliteMoyenne / mesures_O3.size();

	}
	concentrations.push_back(make_pair("O3", concentrationMoyenne));  // Si == -1 => pas de mesures : autres solutions ??
	fiabilites.push_back(make_pair("O3", fiabiliteMoyenne));

	somme_concentrationMoyenne = 0.0;
	concentrationMoyenne = -1.0;
	if (!mesures_SO2.empty())
	{
		for (list<pair<float, float>> ::iterator it = mesures_SO2.begin(); it != mesures_SO2.end(); it++)
		{
			somme_concentrationMoyenne += it->first;
			somme_fiabiliteMoyenne += it->second;

		}
		concentrationMoyenne = somme_concentrationMoyenne / mesures_SO2.size();
		fiabiliteMoyenne = somme_fiabiliteMoyenne / mesures_SO2.size();
	}
	concentrations.push_back(make_pair("SO2", concentrationMoyenne));  // Si == -1 => pas de mesures : autres solutions ??
	fiabilites.push_back(make_pair("SO2", fiabiliteMoyenne));

	somme_concentrationMoyenne = 0.0;
	concentrationMoyenne = -1.0;
	if (!mesures_NO2.empty())
	{
		for (list<pair<float, float>> ::iterator it = mesures_NO2.begin(); it != mesures_NO2.end(); it++)
		{
			somme_concentrationMoyenne += it->first;
			somme_fiabiliteMoyenne += it->second;

		}
		concentrationMoyenne = somme_concentrationMoyenne / mesures_NO2.size();
		fiabiliteMoyenne = somme_fiabiliteMoyenne / mesures_NO2.size();
	}
	concentrations.push_back(make_pair("NO2", concentrationMoyenne));  // Si == -1 => pas de mesures : autres solutions ??
	fiabilites.push_back(make_pair("NO2", fiabiliteMoyenne));

	somme_concentrationMoyenne = 0.0;
	concentrationMoyenne = -1.0;
	if (!mesures_PM10.empty())
	{
		for (list<pair<float, float>> ::iterator it = mesures_PM10.begin(); it != mesures_PM10.end(); it++)
		{
			somme_concentrationMoyenne += it->first;
			somme_fiabiliteMoyenne += it->second;

		}
		concentrationMoyenne = somme_concentrationMoyenne / mesures_PM10.size();
		fiabiliteMoyenne = somme_fiabiliteMoyenne / mesures_PM10.size();
	}
	concentrations.push_back(make_pair("PM10", concentrationMoyenne));  // Si == -1 => pas de mesures : autres solutions ??
	fiabilites.push_back(make_pair("PM10", fiabiliteMoyenne));


	float concentrationMax = -1.0;
	string composant;
	for (list<pair<string, float>> ::iterator it = concentrations.begin(); it != concentrations.end(); it++)
	{
		if (concentrationMax <= it->second)
		{
			concentrationMax = it->second;
			composant = it->first;
		}
	}

	int indiceATMO = calculIndiceATMO(composant, concentrationMax);

	float fiabiliteMin = 100.0;
	for (list<pair<string, float>> ::iterator it = fiabilites.begin(); it != fiabilites.end(); it++)
	{
		if (fiabiliteMin >= it->second)
		{
			fiabiliteMin = it->second;
		}
	}

	tuple<int, list<pair<string, float>>, float>  resultat_final = make_tuple(indiceATMO, concentrations, fiabiliteMin * 100);

	
	return resultat_final;

}//----- End of calculerQualite

 //-------------------------------------------- Constructor - destructor
Service :: Service (const std::string & nomFichierCapteurs, const string & nomFichierAttributs, const std::list < std::string > & nomFichiersMesures)
// Algorithm : 
{
#ifdef MAP
	cout << "Appel au constructeur de <Service>" << endl;
#endif
	fileReader = new FileReader(nomFichierCapteurs, nomFichierAttributs, nomFichiersMesures);

}//----- End of Service 

Service::~Service()
// Algorithm : 
{
#ifdef MAP
	cout << "Appel au destructeur de <Service>" << endl;
#endif
	delete fileReader;
}//----- End of ~Service 

int Service :: calculIndiceATMO(string substance, float valeur)
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
	else if (substance.compare("PO10") == 0)
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

}

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

	// Si terrtoire.getRayon() == 0 et territoire.getCentre() == (0,0) (aire totale consid�r�e ou tous les capteurs) 
		// on retourne true;

// Si capteurId != null
	// On regarde si capteurId == mesure.getCapteur()->getSensorID()
		// Si oui : on retourne true
		// Sinon : on retourne false
{
	
	bool capteurAPrendre = false;

		const Point * posCapteur = capteur.getPosition();
		
		// cas 1 : point consid�r� 
		if (territoire.getRayon() == 0.0
			&& territoire.getCentre()->getLatitude() != 0.0 && territoire.getCentre()->getLongitude() != 0.0)
		{
			Point * centre_zoneAcceptee = new Point(territoire.getCentre()->getLongitude(), territoire.getCentre()->getLatitude());
			Territoire zoneAcceptee = Territoire(centre_zoneAcceptee, territoire.getRayon() + 10);
			if (zoneAcceptee.contient(posCapteur))
			{
				capteurAPrendre = true;				
			}
		}
		// cas 2 : territoire consid�r�
		else if (territoire.getRayon() != 0
			&& territoire.getCentre()->getLatitude() != 0.0 && territoire.getCentre()->getLongitude() != 0.0)
		{
			Point * centre_zoneAcceptee = new Point(territoire.getCentre()->getLongitude(), territoire.getCentre()->getLatitude());
			Territoire zoneAcceptee = Territoire(centre_zoneAcceptee, territoire.getRayon() + 50);
			if (zoneAcceptee.contient(posCapteur))
			{
				capteurAPrendre = true;
			}
		}
		// cas 3 : aire totale consid�r�e
		else if (territoire.getRayon() == 0.0
			&& territoire.getCentre()->getLatitude() == 0.0 && territoire.getCentre()->getLongitude() == 0.0)
		{
			capteurAPrendre = true;
		}

	return capteurAPrendre && (capteurId.empty() || capteur.getSensorID().compare(capteurId) == 0);
}

bool Service::filtrageMesure(Mesure & mesure, struct tm & dateInf, struct tm & dateSup)
// Algorithm :
// Si dateSup == null && dateInf != null (� un instant t)
	// On regarde si mesure.getTimestamp() appartient � l'intervalle  [dateInf (en sec) - 60 (min) * 60 sec, dateInf (en sec) + 60 (min) * 60 sec] 
		// Si oui : on retourne true
		// Sinon : on retourne false
// Si  dateSup != null && dateInf != null (p�riode)
	// On regarde si mesure.getTimestamp() >= dateInf et mesure.getTimestamp() <= dateSup
		// Si oui : on retourne true
		// Sinon : on retourne false
// Si dateSup == null && dateInf == null (tout l'historique 
	// on retourne true
{

	// cout << "Filtrage mesure appelee" << endl;
	bool mesureAPrendre = false;
	struct tm time = mesure.getTimestamp();
	time_t timeMes = mktime(&time); 
	
	// A un instant t
	if ((dateNull(dateSup) == true) && (dateNull(dateInf) == false))
	{
		time_t timeInf = mktime(&dateInf);

		if ((timeMes >= timeInf - 3600) && (timeMes <= timeInf + 3600))
			mesureAPrendre = true;

	}
	// Une p�riode
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
	else {
		time_t timeSup = mktime(&dateSup);

		if ((timeMes >= timeSup - 3600) && (timeMes <= timeSup + 3600))
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


