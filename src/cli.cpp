/*************************************************************************
                           Cli  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Cli> (file Cli.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include
#include <iostream>

using namespace std;
//------------------------------------------------------ Personnal include
#include "Service.h"
#include "cli.h"
#include <regex>
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes
using namespace std;



bool is_number(string s) {

	regex e("[-\\+]?([0-9]*\\\.[0-9]+|[0-9]+)");

	return regex_match(s, e);
	
}

int menu ( ) 
{
	std::string lecture = "-1";
	std::string longitude;
	std::string latitude;
	int index;
	bool flag = true;

	while (std::stoi(lecture) != 4) {

		cout << "Menu Principal" << endl;
		cout << "[1] Obtenir la qualite moyenne de l’air" << endl;
		cout << "[2] Obtenir capteurs similaires" << endl;
		cout << "[3] Verifier comportement capteurs" << endl;
		cout << "[4] Quitter application" << endl;
		do {
			cin >> lecture;
			index = std::stoi(lecture);

		} while (index != 1 && index != 2 && index != 3 && index != 4);
		cout << "Option[" << lecture << "] selectionnee " << endl;
		cout <<  endl;

		switch (index)
		{

			case 1 :
				std::string type_zone = "-1";
				int valeur;
				cout << "Choississez le type de zone a etudier" << endl;
				cout << "[1] Point precis (lat, long)" << endl;
				cout << "[2] Territoire (Point, rayon)" << endl;
				cout << "[3] Aire totale" << endl;
				cout << "[4] Capteur" << endl;
				cout << "[5] Retour" << endl;
				
				do {
					
					cin >> type_zone;
					valeur = std::stoi(type_zone);

				} while (valeur != 1 && valeur != 2 && valeur != 3 && valeur != 4 && valeur != 5);
				cout << "Option[" << type_zone << "] selectionnee " << endl;
				cout << endl;
				switch (valeur) {

					case 1:
						
						cout << "Rentrez une latitude et une longitude" << endl;
						flag = false;
						

						do {

							if(flag)cout << "Donnees invalides" << endl;
							cin >> longitude >> latitude;
							
							flag = !is_number(longitude) || !is_number(latitude);
						} while (flag);
						cout << "Point selectionne : "<<longitude << "," << latitude  << endl;

						

						break;

					case 2:
						break;

					case 3:
						break;

					case 4:
						break;

				}



		}
	}
	

	return 0;
} // End of menu

