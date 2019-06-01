
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
const std::unordered_map < std::string, Capteur * > FileReader ::lireCapteurs(paramFiltrage parametres, bool(*filtrageCapteur) (Capteur &, Territoire &, string)) const //TODO mettre parametre
{
		std::ifstream infile(this->nomFichierCapteurs);

		unordered_map < string , Capteur * > map_capteurs;

		string line;

		while ( getline ( infile , line ) )
		{
			smatch matches;
			regex_search(line, matches, reg_capt);

			if(regex_match(line, reg_capt))
			{
				string sensorID = matches[1].str();
				float latitude = stof(matches[2].str());
				float longitude = stof(matches[3].str());
				string description = matches[4].str();

				Point * position = new Point ( latitude, longitude );
				Capteur * c = new Capteur ( sensorID, position, description );

				map_capteurs[sensorID] = c ;
			}
		}

		return map_capteurs;
	}

	//TODO mettre paramêtre
	const unordered_map < string , Attribut * > FileReader :: lireAttributs ( ) const
	{
		ifstream infile(this->nomFichierAttributs);

	    unordered_map < string , Attribut * > map_attributs;

		string line;

		while ( getline ( infile , line ) )
		{
			//AttributeID;Unit;Description;
			regex reg_attr( "(.*);(.*\/.*);(.*);" );

			smatch matches;
			regex_search(line, matches, reg_attr);

			if(regex_match(line, reg_attr))
			{
				string attributeID = matches[1].str();
				string unit = matches[2].str();
				string description = matches[3].str();

				Attribut * a = new Attribut ( attributeID, unit, description );

				map_attributs [ attributeID ] = a;
			}
		}

		return map_attributs;
	}


	bool FileReader :: fichierLisible() 
	{
		bool res = true;
		
		if(fichierMesureEnCours.eof())
		{
			//cout << "Reached end of file" << endl;
			//regarde si encore fichier
			if(nomFichiersMesures.size() > 0)
			{
				//cout << "Nb : " << nomFichiersMesures.size() << "  name : " << nomFichiersMesures.front() << endl;
				fichierMesureEnCours.clear();
				fichierMesureEnCours.close();
				
				fichierMesureEnCours.open(nomFichiersMesures.front());
				
				nomFichiersMesures.pop_front();
			}
			else // Arrivée à la fin de tous les fichiers 
			{
				res = false;
				cout << "fini" << endl;
			}
		}

		return res;
	}

	void FileReader :: getLineModifie ( ifstream& fichierMesureEnCours, string& line )
	{
		string line_read;
		line = "";
		getline ( fichierMesureEnCours , line_read );
		for (string::iterator it = line_read.begin(); it < line_read.end(); ++it)
		{
			if((*it) != 0 && *(it) != 13) // Filtrage d'un caractère fantome et du caractère saut de ligne
			{
				line+=*it;
			}
			//printf("%x|-|%c\n", (*it) & 0xff, (*it));
		}
	}

	//TODO mettre paramêtre
	Mesure * FileReader :: prochaineMesure(paramFiltrage parametres, bool(*filtrageMesure) (Mesure &, struct tm &, struct tm &))
	{
		Mesure * m = nullptr;

		string line;
		smatch matches;
		smatch time_match;

		if(fichierMesureEnCours.is_open())
		{
			if(fichierLisible())
			{

				do{
					getLineModifie ( fichierMesureEnCours , line );
					if(!regex_match(line, reg_mesure))
					{
						cout << "AAAAAH : " << line << endl;
					}

				}while(!regex_match(line, reg_mesure) && fichierLisible());
				
				if(regex_match(line, reg_mesure))
				{
					regex_search(line, matches, reg_mesure);
					string timestamp = matches[1].str();
					string sensorID = matches[2].str();
					string attributeID = matches[3].str();
					float value = stof(matches[4].str());

					//cout << timestamp << " - " << sensorID << " - " << attributeID << " - " << value << endl;
					
					//Search for the date
					regex_search(timestamp, time_match, reg_date);

					if(regex_match(timestamp, reg_date))
					{
						struct tm * time = new tm();
						time->tm_year = stoi(time_match[1].str());
						time->tm_mon = stoi(time_match[2].str());
						time->tm_mday = stoi(time_match[3].str());
						time->tm_hour = stoi(time_match[4].str());
						time->tm_min = stoi(time_match[5].str());
						time->tm_sec = floor(stof(time_match[6].str()));

						//cout << time->tm_year << " - " << time->tm_mon << " - " << time->tm_mday << " - " << time->tm_hour << " - " << time->tm_min << " - " << time->tm_sec << endl;
						
						if(this->map_attributs.count(attributeID) == 0)
						{
							cout << "Pb avec attributeID" << endl;
						}

						if(this->map_capteurs.count(sensorID) == 0)
						{
							cout << "Pb avec attributeID" << endl;
						}

						if(this->map_attributs.count(attributeID) == 1 && this->map_capteurs.count(sensorID) == 1)
						{
							m = new Mesure(time, this->map_attributs[attributeID], value, sensorID, this->map_capteurs[sensorID]);
						}
					}
				}
			}
		}

		return m;
	}

	const list < std::string > FileReader :: getNomFichiersMesures() const 
	{
		return this->nomFichiersMesures;
	}

//-------------------------------------------- Constructors - destructor

FileReader :: FileReader ( const std :: string & nomFichierCapteurs, const string & nomFichierAttributs, const std :: list < std :: string > & nomFichiersMesures)
{
	#ifdef MAP
	    cerr << "Constructor of <FileReader>" << endl;
	#endif

	this->nomFichierCapteurs = nomFichierCapteurs;
	this->nomFichierAttributs = nomFichierAttributs;
	this->nomFichiersMesures = nomFichiersMesures; //Fait une copie

	if(this->nomFichiersMesures.size()>0)
	{
		this->fichierMesureEnCours.open(this->nomFichiersMesures.front());
		this->nomFichiersMesures.pop_front();
	}
	else
	{
		cerr << "List nomFichiersMesures vide" << endl;
	}

	reg_mesure = regex( "(.*);(.*);(.*);(.*[0-9]+.*);" );
	reg_date = regex( "([0-9]*)-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2}.[0-9]*)" );
	reg_capt = regex( "(.*);(.*[0-9]+);(.*[0-9]+);(.*);" );
	reg_attr = regex( "(.*);(.*\/.*);(.*);" );

} // End of constructor

FileReader :: FileReader ( )
{	
	#ifdef MAP
	    cerr << "Default constructor of <FileReader>" << endl;
	#endif

	this->nomFichierCapteurs = "";
	this->nomFichierAttributs = "";

	reg_mesure = regex( "(.*);(.*);(.*);(.*[0-9]+);" );
	reg_date = regex( "([0-9]*)-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2}.[0-9]*)" );
	reg_capt = regex( "(.*);(.*[0-9]+);(.*[0-9]+);(.*);" );
	reg_attr = regex( "(.*);(.*\/.*);(.*);" );
}

FileReader :: ~FileReader ( )
{

} // End of destructor