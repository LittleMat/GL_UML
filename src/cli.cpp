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

bool is_date(string s) {

	int jour, mois, annee;
	regex e("([0-3][0-9])/([0-1][0-9])/([0-9][0-9][0-9][0-9])");
	std::smatch matches;
	/*
	cout << "rapport REGEX " << endl;
	if (regex_search(s, matches, e)) {
		cout << "Match found\n";

		for (size_t i = 0; i < matches.size(); ++i) {
			cout << i << ": '" << matches[i].str() << "'\n";
		}
	}
	else {
		cout << "Match not found\n";
	}*/


	regex_search(s, matches, e);
	if (regex_match(s, e)) {
		jour = stoi(matches[1].str());
		mois = stoi(matches[2].str());
		annee = stoi(matches[3].str());

		return jour <= 31 && mois <= 12 && jour > 0 && mois > 0 && annee > 0;

	}
	else {
		return false;
	}
}

bool is_heure(string s) {

	int heures, minutes;
	regex e("([0-2][0-9]):([0-9][0-9])");
	std::smatch matches;
	/*
	cout << "rapport REGEX " << endl;
	if (regex_search(s, matches, e)) {
		cout << "Match found\n";

		for (size_t i = 0; i < matches.size(); ++i) {
			cout << i << ": '" << matches[i].str() << "'\n";
		}
	}
	else {
		cout << "Match not found\n";
	}*/


	regex_search(s, matches, e);
	if (regex_match(s, e)) {
		heures = stoi(matches[1].str());
		minutes = stoi(matches[2].str());


		return heures <= 23 && minutes < 60;

	}
	else {
		return false;
	}
}

int menu ( ) 
{
	std::string lecture = "-1";
	std::string longitude, latitude;;
	std::string date1, date2,heure;
	std::string rayon,nb_mesures;
	std::string captorId,list_captorID;
	std::string type_date, type_zone;
	int index;
	bool flag = true;

	while (std::stoi(lecture) != 4) {

		cout << "Menu Principal" << endl;
		cout << "[1] Obtenir la qualite moyenne de l air" << endl;
		cout << "[2] Obtenir capteurs similaires" << endl;
		cout << "[3] Verifier comportement capteurs" << endl;
		cout << "[4] Quitter application" << endl;
		do {
			cin >> lecture;
			if(is_number(lecture))index = std::stoi(lecture);

		} while (!is_number(lecture) || index != 1 && index != 2 && index != 3 && index != 4);
		//cout << "Option[" << lecture << "] selectionnee " << endl;
		cout <<  endl;

		switch (index)
		{

			case 1 :
				
				int valeur;
				cout << "Choississez le type de zone a etudier" << endl;
				cout << "[1] Point precis (lat, long)" << endl;
				cout << "[2] Territoire (Point, rayon)" << endl;
				cout << "[3] Aire totale" << endl;
				cout << "[4] Capteur" << endl;
				cout << "[5] Retour" << endl;
				
				do {
					
					cin >> type_zone;
					if(is_number(lecture))valeur = std::stoi(type_zone);

				} while (!is_number(type_zone) || valeur != 1 && valeur != 2 && valeur != 3 && valeur != 4 && valeur != 5);
				cout << "Option[" << type_zone << "] selectionnee " << endl;
				cout << endl;
				if (valeur == 5)break;
				switch (valeur) {

					case 1:
						
						cout << "Rentrez une latitude et une longitude" << endl;
						flag = false;
						
						do {
							if(flag)cout << "Donnees invalides" << endl;
							cin >> longitude >> latitude;
							
							flag = (!is_number(longitude) || !is_number(latitude) || abs(stoi(longitude)) > 90 || abs(stoi(latitude)) > 90);
						} while (flag);
						cout << "Point selectionne : "<<longitude << "," << latitude  << endl;
						break;

					case 2:

						cout << "Rentrez une latitude et une longitude" << endl;
						flag = false;

						do {

							if (flag)cout << "Donnees invalides" << endl;
							cin >> longitude >> latitude;
							flag = (!is_number(longitude) || !is_number(latitude) || abs(stoi(longitude)) > 90 || abs(stoi(latitude)) > 90);

						} while (flag);

						cout << "Point selectionne : " << longitude << "," << latitude << endl;
						cout << "Rentrez un rayon" << endl;
						flag = false;
						do {

							if (flag)cout << "Donnees invalides" << endl;
							cin >> rayon;
							flag = (!is_number(rayon) || stoi(rayon) < 0); 
						} while (flag);
						break;

					case 3:
						cout << "Aire totale selectionnee" << endl;
						break;

					case 4:

						cout << "Rentrez l'id d'un capteur" << endl;
						flag = false;


						do {

							if (flag)cout << "Rentrez un id non vide" << endl;
							cin >> captorId;
							flag = (captorId.empty());
						} while (flag);

						break;

				}
				cout << endl;
				cout << "Indiquer la periode temporelle" << endl;
				cout << "[1]Depuis la mise en place des capteurs jusqu a une date donnee : date" << endl;
				cout << "[2]Sur une plage de temps donnee delimitee par deux dates : date1 date2" << endl;
				cout << "[*]Sur l integralite des mesures  * " << endl;
				
				flag = false;
				do {
					if(flag)cout << "entree invalide" << endl;
					cin >> type_date;
					flag = (!is_number(type_date) );

				} while (flag || type_date != "*" && std::stoi(type_date) != 1 && std::stoi(type_date) != 2 );

				if (type_date == "*")valeur = 0;
				else valeur = std::stoi(type_date);

				switch (valeur) 
				{

				case 0:
					break;

				case 1:

					cout << "Rentrez une date au format : JJ/MM/AAAA" << endl;
					flag = false;


					do {

						if (flag)cout << "date invalide" << endl;
						cin >> date1 ;

						flag = (!is_date(date1) );
					} while (flag);
					cout << "date selectionnee : " << date1 << endl;
					cout << endl;

					break;

				case 2:

					cout << "Rentrez deux dates au format : JJ/MM/AAAA" << endl;
					flag = false;


					do {

						if (flag)cout << "date invalide" << endl;
						cin >> date1 >> date2;

						flag = (!is_date(date1) || !is_date(date2));
					} while (flag);
					cout << "date selectionnee : " << date1 << " " << date2 << endl;
					cout << endl;

					break;

				}
				break;

			case 2 :
				//cout << "Obtenir capteurs similaires" << endl;
				cout << "Rentrez l'id du capteur de reference" << endl;
				flag = false;


				do {

					if (flag)cout << "Rentrez un id non vide" << endl;
					cin >> captorId;
					flag = (captorId.empty());
				} while (flag);

				cout << "Rentrez une date de depart au format : JJ/MM/AAAA HH:MM" << endl;
				cout << "exemple : 02/06/1996 16:30" << endl;
				flag = false;


				do {

					if (flag)cout << "date invalide" << endl;
					cin >> date1 >> heure;

					flag = (!is_date(date1) || !is_heure(heure));
				} while (flag);
				cout << "date selectionnee : " << date1 << " " << heure << endl;


				cout << "Rentrez le nombre de mesures pour la comparaison" << endl;
				flag = false;
				do {

					if (flag)cout << "entree invalide" << endl;
					cin >> nb_mesures;

					flag = (!is_number(nb_mesures) ||stoi( nb_mesures) <= 0 || (std::floor(stof(nb_mesures)) != stof( nb_mesures)) );
				} while (flag);
				cout << "nombre de mesures demandees : " << nb_mesures << endl;
				cout << endl;
				break;

			case 3:
				cout << "Listez les id des capteurs que vous voulez surveiller" << endl;
				cout << "Le caractere * designe l integralite des capteurs" << endl;


				list_captorID = "";
				captorId = "";
				flag = false;
				do {
					do {

						if (flag)cout << "Rentrez un id non vide" << endl;
						cin >> captorId;
						flag = (captorId.empty());
					} while (flag);
					if (captorId != "-1") {
						if (!list_captorID.empty())list_captorID.append(" ");
						list_captorID.append(captorId);
					}
					

				} while (captorId != "*" && captorId != "-1");
				if (captorId == "*")list_captorID = "*";
				cout << "liste des id : " << list_captorID << endl;
				cout << endl;
				

				break;
		}
	}
	

	return 0;
} // End of menu

