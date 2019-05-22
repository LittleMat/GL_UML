
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
	const list < Capteur * > FileReader :: lireCapteurs ( ) const
	{
		std::ifstream infile(this->nomFichierCapteurs);

		list < Capteur *> list_capteurs;

		string line;

		// Première ligne de description, on passe
		getline(infile, line);

		while ( getline ( infile , line ) )
		{
			string delimiter ( ";" );

			size_t pos = line.find ( delimiter );
			string sensorID = line.substr ( 0 , pos );

			pos ++;
			size_t new_pos = line.find ( delimiter, pos );
			float latitude = stof(line.substr ( pos, new_pos - pos ) );

			pos = new_pos + 1;
			new_pos = line.find ( delimiter, pos );
			float longitude = stof ( line.substr ( pos, new_pos - pos ) );
			
			pos = new_pos + 1;
			new_pos = line.find ( delimiter , pos );
			string description = line.substr ( pos, new_pos - pos );

			Point * position = new Point ( latitude, longitude );
			Capteur * c = new Capteur ( sensorID, position, description );
			list_capteurs.push_back ( c );
		}

		return list_capteurs;
	}

	//TODO mettre paramêtre
	const list < Attribut * > FileReader :: lireAttributs ( ) const
	{
		ifstream infile(this->nomFichierAttributs);

		list < Attribut * > list_attributs;

		string line;

		// Première ligne de description, on passe
		getline(infile, line);

		while ( getline ( infile , line ) )
		{
			//AttributeID;Unit;Description;
			string delimiter ( ";" );

			size_t pos = line.find ( delimiter );
			string attributeID = line.substr ( 0 , pos );

			pos ++;
			size_t new_pos = line.find ( delimiter, pos );
			string unit = line.substr ( pos, new_pos - pos ) ;

			pos = new_pos + 1;
			new_pos = line.find ( delimiter, pos );
			string description = line.substr ( pos, new_pos - pos );
	
			Attribut * a = new Attribut ( attributeID, unit, description );

			list_attributs.push_back ( a );
		}

		return list_attributs;
	}

	//TODO mettre paramêtre
	const Mesure * FileReader :: prochaineMesure ( )
	{
		if(fichierMesureEnCours.is_open())
		{
			string line;
			getline ( fichierMesureEnCours , line );
			
			//Fin de fichier
			if(fichierMesureEnCours.eof())
			{
				cout << "Reached end of file" << endl;
				//regarde si encore fichier
				if(nomFichiersMesures.size() > 0)
				{
					fichierMesureEnCours.open(nomFichiersMesures.front());
					nomFichiersMesures.pop_front();
					getline ( fichierMesureEnCours , line );
				}
				else
				{
					cout << "End of all files" << endl;
				}
			}

			else
			{
				string delimiter ( ";" );
				size_t pos = line.find ( delimiter );
				string timestamp = line.substr ( 0 , pos );

				pos ++;
				size_t new_pos = line.find ( delimiter, pos );
				string sensorID = line.substr ( pos, new_pos - pos ) ;

				pos = new_pos + 1;
				new_pos = line.find ( delimiter, pos );
				string attributeID = line.substr ( pos, new_pos - pos );
				
				pos = new_pos + 1;
				new_pos = line.find ( delimiter, pos );
				string value = line.substr ( pos, new_pos - pos );

				cout << timestamp << " " << sensorID << " " << attributeID << " " << value << endl;
			}
		}

		return nullptr;
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

} // End of constructor

FileReader :: FileReader ( )
{	
	#ifdef MAP
	    cerr << "Default constructor of <FileReader>" << endl;
	#endif

	this->nomFichierCapteurs = "";
	this->nomFichierAttributs = "";
}

FileReader :: ~FileReader ( )
{

} // End of destructor