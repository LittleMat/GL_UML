
/*************************************************************************
                           FileReader  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <FileReader> (file FileReader.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include

//------------------------------------------------------ Personnal include
#include "FileReader.h"
//------------------------------------------------------------- Constantes
regex FileReader::reg_mesure = regex("(.*);(.*);(.*);(.*[0-9]+.*);");
regex FileReader::reg_date = regex("([0-9]*)-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2}.[0-9]*)");
regex FileReader::reg_capt = regex("(.*);(.*[0-9]+);(.*[0-9]+);(.*);");
regex FileReader::reg_attr = regex("(.*);(.*/.*);(.*);");

string FileReader::enteteFicherCapteurs = "SensorID;Latitude;Longitude;Description;";
string FileReader::enteteFichierAttributs = "AttributeID;Unit;Description;";
string FileReader::enteteFichierMesures = "Timestamp;SensorID;AttributeID;Value;";
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

unordered_map<string, Capteur *> FileReader ::lireCapteurs( function<bool(Capteur&)> predicateCapteur )
{
	if (predicateCapteur == NULL)
	{
		throw "Illegal Argument Exception: parameter is nullptr";
	}
	ifstream infile(this->nomFichierCapteurs);

	//Si la map n'est pas vide, on la vide et on détruit tous les éléments contenus dans celle ci
	if (this->map_capteurs.size() != 0)
	{
		for (auto it : this->map_capteurs)
		{
			delete it.second;
		}
		this->map_capteurs.clear();
	}

	string line;

	//Lit les lignes du fichiers
	while (getline(infile, line))
	{
		smatch matches;
		regex_search(line, matches, reg_capt);

		//Regex pour extraires les informations d'une ligne + ne pas lire la première ligne d'information
		if (regex_match(line, reg_capt))
		{
			string sensorID = matches[1].str();
			float latitude = stof(matches[2].str());
			float longitude = stof(matches[3].str());
			string description = matches[4].str();

			Point *position = new Point(longitude, latitude);
			Capteur *c = new Capteur(sensorID, position, description);

			//Filtre permetant de filtrer les capteurs selon le choix de l'utilisateur
			if (predicateCapteur(*c))
			{
				this->map_capteurs[sensorID] = c;
			}
			else
			{
				delete c;
			}
		}
	}

	return this->map_capteurs;

} //----- End of lireCapteurs

unordered_map<string, Attribut *> FileReader ::lireAttributs()
{
	ifstream infile(this->nomFichierAttributs);

	//Idem que lireCapteurs
	if (this->map_attributs.size() != 0)
	{
		for (auto it : this->map_attributs)
		{
			delete it.second;
		}

		this->map_attributs.clear();
	}

	string line;

	while (getline(infile, line))
	{
		smatch matches;
		regex_search(line, matches, reg_attr);

		if (regex_match(line, reg_attr))
		{
			string attributeID = matches[1].str();
			string unit = matches[2].str();
			string description = matches[3].str();

			Attribut *a = new Attribut(attributeID, unit, description);

			this->map_attributs[attributeID] = a;
			//Pas besoin de filtrer ici
		}
	}

	return this->map_attributs;

} //----- End of lireAttributs

//Revient au début des mesures
void FileReader ::debutMesure()
{
	idFichierMesures = 0;
	fichierMesureEnCours.clear();
	fichierMesureEnCours.close();
	fichierMesureEnCours.open(nomFichiersMesures[idFichierMesures]);

} //----- End of debutMesure

bool FileReader ::fichierLisible()
{
	bool res = true;

	if (fichierMesureEnCours.eof())
	{
		//Regarde s'il reste encore un fichier de mesure
		idFichierMesures++;
		if (idFichierMesures < nomFichiersMesures.size())
		{
			fichierMesureEnCours.clear();
			fichierMesureEnCours.close();

			fichierMesureEnCours.open(nomFichiersMesures[idFichierMesures]);
		}
		else // On est arrivé à la fin de tous les fichiers de mesure
		{
			res = false;
		}
	}

	return res;

} //----- End of fichierLisible

void FileReader ::getLineModifie(ifstream &fichierMesureEnCours, string &line)
{
	string line_read;
	line = "";
	getline(fichierMesureEnCours, line_read);

	for (string ::iterator it = line_read.begin(); it < line_read.end(); ++it)
	{
		if ((*it) != 0 && (*it) != 13) // Filtrage d'un caractère fantome et du caractère saut de ligne
		{
			line += *it;
		}
	}

} //----- End of getLineModifie

Mesure *FileReader ::prochaineMesure(function<bool(Mesure&)> predicateMesure)
{
#ifdef MAP
	cout << "Appel prochaineMesure" << endl;
#endif

	if (predicateMesure == NULL)
	{
		throw "Illegal Argument Exception: parameter is null";
	}
	Mesure *m = nullptr;

	string line;
	smatch matches;
	smatch time_match;
	bool continuer; //2 conditions pour s'arreter : on a trouver une mesure ou il n'y a plus de mesure à lire

	//Premier test si le fichier est lisible
	if (fichierMesureEnCours.is_open())
	{
		if (fichierLisible())
		{
			do
			{
				continuer = true;
				//Obtient la ligne
				getline(fichierMesureEnCours, line);

				if (regex_match(line, reg_mesure))
				{
					//Extraction des informations de la ligne
					regex_search(line, matches, reg_mesure);
					string timestamp = matches[1].str();
					string sensorID = matches[2].str();
					string attributeID = matches[3].str();
					float value = stof(matches[4].str());

					//Search for the date
					regex_search(timestamp, time_match, reg_date);
					//Test et extraction de la date
					if (regex_match(timestamp, reg_date))
					{
						struct tm *time = new tm();
						time->tm_year = stoi(time_match[1].str()) - 1900; //tm_year == nombres d'années entre 1900 et l'année réelle de la date
						time->tm_mon = stoi(time_match[2].str());
						time->tm_mday = stoi(time_match[3].str());
						time->tm_hour = stoi(time_match[4].str());
						time->tm_min = stoi(time_match[5].str());
						time->tm_sec = floor(stof(time_match[6].str()));

						if (this->map_attributs.find(attributeID) != this->map_attributs.end() && this->map_capteurs.find(sensorID) != this->map_capteurs.end())
						{
							//Le sensorID et l'attributID existent et sont dans les map
							m = new Mesure(*time, attributeID, value, sensorID);

							//Filtre la mesure avec les paramètres de l'utilisateur
							if (!predicateMesure(*m))
							{
								delete m;
								m = nullptr;
							}
							else
							{
								continuer = false;
							}
						}
						delete time;
					}
				}

				//Plus de mesure à lire
				if (!fichierLisible())
				{
					continuer = false;
				}
			} while (continuer);
		}
	}

	return m;

} //----- End of prochaineMesure

//-------------------------------------------- Constructors - destructor

FileReader ::FileReader(const string &nomFichierCapteurs, const string &nomFichierAttributs, const list<string> &nomFichiersMesures)
{
#ifdef MAP
	cout << "Appel au constructeur de <FileReader>" << endl;
#endif

	this->nomFichierCapteurs = nomFichierCapteurs;
	this->nomFichierAttributs = nomFichierAttributs;

	if (nomFichiersMesures.size() == 0)
	{
		throw "Illegal Argument Exception: no file containg mesures";
	}
	for (auto it : nomFichiersMesures)
	{
		this->nomFichiersMesures.push_back(it);
	}

	//Tester les fichiers : première ligne définit si le fichier est conforme.

	string line;

	//Capteurs
	ifstream testCapteurs;
	testCapteurs.open(this->nomFichierCapteurs);
	getline(testCapteurs, line);
	if (line != enteteFicherCapteurs)
	{
		throw "Illegal Argument Exception : the file containing the sensors was corrupted";
	}
	testCapteurs.close();

	//Attributs
	ifstream testAttributs;
	testAttributs.open(this->nomFichierAttributs);
	getline(testAttributs, line);
	if (line != enteteFichierAttributs)
	{
		throw "Illegal Argument Exception : the file containing the attributes was corrupted";
	}
	testAttributs.close();

	//Fichiers de mesures
	for (auto it : nomFichiersMesures)
	{
		ifstream testMesures;
		testMesures.open(it);
		getline(testMesures, line);
		if (line != enteteFichierMesures)
		{
			throw "Illegal Argument Exception : the file containing the measures was corrupted";
		}

		testMesures.close();
	}

	idFichierMesures = 0;

#ifdef MAP
	//Ouvre le premier fichier de mesure
	if (this->nomFichiersMesures.size() > 0)
	{
		cout << "ouverture de " << this->nomFichiersMesures[idFichierMesures] << endl;
		this->fichierMesureEnCours.open(this->nomFichiersMesures[idFichierMesures]);
		cout << "ouverture fichier : " << fichierMesureEnCours.is_open() << endl;
	}
	else
	{
		cerr << "List nomFichiersMesures vide" << endl;
	}
#endif

} //----- End of FileReader

FileReader ::~FileReader()
{
	#ifdef MAP
		cout << "Appel au destructeur de <FileReader>" << endl;
	#endif

	//Ferme le dernier fichier de mesure
	fichierMesureEnCours.clear();
	fichierMesureEnCours.close();

	//Détruit les objets contenus dans les deux unorderedmap
	if (map_capteurs.size() != 0)
	{
		for (auto it : map_capteurs)
		{
			delete it.second;
		}
		map_capteurs.clear();
	}

	if (map_attributs.size() != 0)
	{
		for (auto it : map_attributs)
		{
			delete it.second;
		}
		map_attributs.clear();
	}

} //----- End of ~FileReader