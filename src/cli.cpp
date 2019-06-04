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
#include <cmath>
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes



bool is_number ( string s )
{

	regex e ( "[-\\+]?([0-9]*\\\.[0-9]+|[0-9]+)" );

	return regex_match ( s , e );
	
}

bool is_date ( string s )
{

	int jour, mois, annee;
	regex e ( "([0-3][0-9])/([0-1][0-9])/([0-9][0-9][0-9][0-9])" );
	smatch matches;
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


	regex_search ( s , matches , e );
	if ( regex_match ( s , e ) ) {
		jour = stoi ( matches[1].str ( ) );
		mois = stoi( matches[2].str ( ) );
		annee = stoi ( matches[3].str ( ) );

		return jour <= 31 && mois <= 12 && jour > 0 && mois > 0 && annee > 0;

	}
	else {
		return false;
	}
}

bool is_heure ( string s )
{
	int heures, minutes;
	regex e ( "([0-2][0-9]):([0-9][0-9])" );
	smatch matches;

	regex_search ( s , matches , e );
	if ( regex_match ( s , e ) ) 
	{
		heures = stoi ( matches [ 1 ].str ( ) );
		minutes = stoi ( matches [ 2 ].str ( ) );
		return heures <= 23 && minutes < 60;
	}
	else 
	{
		return false;
	}
}

bool check_dates ( string sA , string sB ) {

//Post condition : sA est plus ancienne que sB
	int jourA , moisA , anneeA;
	int jourB , moisB , anneeB;
	regex e ( "([0-3][0-9])/([0-1][0-9])/([0-9][0-9][0-9][0-9])" );
	smatch matchesA;
	smatch matchesB;
	regex_search ( sA , matchesA , e );
	regex_search ( sB , matchesB , e );
	if ( regex_match ( sA , e ) && regex_match ( sB , e ) ) 
	{
		jourA = stoi ( matchesA [ 1 ].str ( ) );
		moisA = stoi ( matchesA [ 2 ].str ( ) );
		anneeA = stoi ( matchesA [ 3 ].str ( ) );

		jourB = stoi ( matchesB [ 1 ].str ( ) );
		moisB = stoi ( matchesB [ 2 ].str ( ) );
		anneeB = stoi ( matchesB [ 3 ].str ( ) );

		if ( anneeB >= anneeA ) return true;
		if  (moisB >= moisA ) return true;
		if ( jourB <= jourA ) return false;
		return true;

	}
	else 
	{
		return false;
	}
	return false;
}

struct tm stringToDate( string date )
{

	struct tm result = tm ( ) ;

	regex e( "([0-3][0-9])/([0-1][0-9])/([0-9][0-9][0-9][0-9])" );
	smatch matches;
	regex_search ( date , matches , e );
	if ( regex_match ( date , e ) )
	{
		result.tm_mday = stoi ( matches[ 1 ].str ( ) );
		result.tm_mon = stoi ( matches[ 2 ].str ( ) );
		result.tm_year = stoi ( matches[ 3 ].str ( ) ) - 1900; // Linda
		result.tm_hour = 0;
		result.tm_min = 0;
	}
	return result;
}

void afficherDate(struct tm date)
{

	cout << date.tm_mday << "\\" << date.tm_mon << "\\" << date.tm_year << " " << date.tm_hour << ":" << date.tm_min << endl;
}

struct tm stringToDateDetailed( string date )
{

	struct tm result = tm ( );
	regex e( "([0-3][0-9])/([0-1][0-9])/([0-9][0-9][0-9][0-9]) ([0-2][0-9]):([0-5][0-9])" );
	smatch matches;
	regex_search ( date , matches , e );
	if ( regex_match ( date , e ) )
	{
		result.tm_mday = stoi ( matches[ 1 ].str ( ) );
		result.tm_mon = stoi ( matches[ 2 ].str ( ) );
		result.tm_year = stoi ( matches[ 3 ].str ( ) ) - 1900; // Linda
		result.tm_hour = stoi ( matches[ 4 ].str ( ) );
		result.tm_min = stoi ( matches[ 5 ].str ( ));

	}
	return result;
}

int menu ( int argc , char ** argv)
{
	list <string> args;
	for ( int i = 3 ; i < argc ; i++ )
	{
		args.push_back ( string ( argv[ i ] ) );
	}
	cout << "fichier capteur " << string(argv[1]) << endl;
	Service *service = new Service ( string ( argv[ 1 ] ) , string ( argv[ 2 ] ) , args );

	paramFiltrage paramQualite = { NULL , NULL , NULL , NULL };
	tuple < int, list < pair < string, float > > , float > resultQualite;


	string lecture = "-1";
	string nb_mesures;
	string date1, date2,heure;
	string rayon = "0";
	string longitude = "0.0";
	string latitude = "0.0";
	string captorId;
	list <string> list_captorID;
	string type_date, type_zone;
	int index;
	bool flag = true;

	while ( stoi ( lecture ) != 4 ) 
	{

		cout << "Menu Principal" << endl;
		cout << "[1] Obtenir la qualite moyenne de l air" << endl;
		cout << "[2] Obtenir capteurs similaires" << endl;
		cout << "[3] Verifier comportement capteurs" << endl;
		cout << "[4] Quitter application" << endl;
		do 
		{
			cin >> lecture;
			if ( is_number ( lecture ) ) { index = stoi ( lecture ); }

		} 
		while ( ! is_number ( lecture ) || index != 1 && index != 2 && index != 3 && index != 4 );
		//cout << "Option[" << lecture << "] selectionnee " << endl;
		cout <<  endl;

		//MENU PRINCIPAL
		switch ( index )
		{
			//Obtenir la qualite moyenne de l air
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
					if( is_number ( lecture ) ) valeur = stoi ( type_zone );

				} while ( ! is_number ( type_zone ) || valeur != 1 && valeur != 2 && valeur != 3 && valeur != 4 && valeur != 5 );
				cout << "Option[" << type_zone << "] selectionnee " << endl;
				cout << endl;
				if ( valeur == 5 ) { break; }


				switch ( valeur )
				{

					//Point Précis
					case 1:
						
						cout << "Rentrez une latitude et une longitude" << endl;
						flag = false;
						
						do 
						{
							if ( flag ) { cout << "Donnees invalides" << endl; }
							cin >> longitude >> latitude;
							
							flag = ( ! is_number(longitude) || ! is_number(latitude) || abs ( stof ( longitude ) ) > 90 || abs ( stof( latitude ) ) > 90 );
						}
						while ( flag );
						cout << "Point selectionne : "<< longitude << "," << latitude  << endl;
						break;

					//Territoire
					case 2:

						cout << "Rentrez une latitude et une longitude" << endl;
						flag = false;

						do 
						{
							if ( flag ) { cout << "Donnees invalides" << endl; }
							cin >> longitude >> latitude;
							flag = ( ! is_number ( longitude ) || ! is_number ( latitude ) || abs ( stoi ( longitude ) ) > 90 || abs ( stoi ( latitude ) ) > 90 );

						}
						while ( flag );

						cout << "Point selectionne : " << longitude << "," << latitude << endl;
						cout << "Rentrez un rayon" << endl;
						flag = false;
						do 
						{

							if ( flag ) { cout << "Donnees invalides" << endl; }
							cin >> rayon;
							flag = ( ! is_number ( rayon ) || stoi ( rayon ) < 0 ); 
						}
						while ( flag );
						break;

					//Aire totale
					case 3:
						
						cout << "Aire totale selectionnee" << endl;
						break;

					//Capteur
					case 4:
						cout << "Rentrez l'id d'un capteur" << endl;
						flag = false;

						do 
						{
							if ( flag ) cout << "Rentrez un id non vide" << endl;
							cin >> captorId;
							flag = ( captorId.empty ( ) );
						} 
						while ( flag );

						break;

				}
				cout << endl;
				cout << "Indiquer la periode temporelle" << endl;
				cout << "[1]Depuis la mise en place des capteurs jusqu a une date donnee : date" << endl;
				cout << "[2]Sur une plage de temps donnee delimitee par deux dates : date1 date2" << endl;
				cout << "[*]Sur l integralite des mesures  * " << endl;
				
				flag = false;
				do 
				{
					if ( flag ) { cout << "entree invalide" << endl; }
					cin >> type_date;
					flag = ( ( ! is_number ( type_date ) && type_date != "*" ) || ( is_number ( type_date ) && stoi ( type_date ) != 1 && stoi ( type_date ) != 2 )  );

				}
				while ( flag );
				cout << "[debug] " << "type date vaut " << type_date << endl;
				if ( type_date == "*" ) { valeur = 0; }
				else { valeur = stoi ( type_date ); }
				
				switch ( valeur ) 
				{

				case 0:

					date1 = "0";
					date2 = "0";
					break;

				case 1:

					cout << "Rentrez une date au format : JJ/MM/AAAA" << endl;
					flag = false;

					do {
						if ( flag ) { cout << "date invalide" << endl; }
						cin >> date1 ;
						flag = ( ! is_date ( date1 ) );
					} 
					while ( flag );
					cout << "date selectionnee : " << date1 << endl;
					cout << endl;
					break;

				case 2:

					cout << "Rentrez deux dates au format : JJ/MM/AAAA" << endl;
					flag = false;

					do 
					{
						if ( flag ) cout << "date invalide" << endl;
						cin >> date1 >> date2;

						flag = ( ! is_date ( date1 ) || ! is_date ( date2 ) || ! check_dates ( date1 , date2 ) );
					}
					while ( flag );
					cout << "dates selectionnees : " << date1 << " " << date2 << endl;
					cout << endl;
					break;
				}


				// tuple <Indice ATMO , list pair < <idattribut , concentration moyenne > > , indice_fiabilité>
				cout << "[Debug]" << "Calcul de la qualité moyenne" << endl;

				paramQualite = { stringToDate(date1) , stringToDate(date2) , Territoire(new Point(stof(latitude) , stof(longitude)) , stoi(rayon))  , captorId };
				resultQualite = service->calculerQualite(paramQualite);
				cout << "Indice ATMO " << get<0>(resultQualite) << endl;
				cout << "Indice fiabilite " << get<2>(resultQualite) << "%" << endl;
				for (auto const& i : (get<1>(resultQualite)))
				{

					cout << i.first << "," << i.second << endl;
				}
				break;



				


			//Obtenir capteurs similaires
			case 2 :
				cout << "Rentrez l'id du capteur de reference" << endl;
				flag = false;

				do {

					if ( flag ) { cout << "Rentrez un id non vide" << endl; }
					cin >> captorId;
					flag = (captorId.empty ( ) );
				}
				while ( flag );

				cout << "Rentrez une date de depart au format : JJ/MM/AAAA HH:MM" << endl;
				cout << "exemple : 02/06/1996 16:30" << endl;
				flag = false;

				do
				{
					if ( flag ) cout << "date invalide" << endl;
					cin >> date1 >> heure;

					flag = ( ! is_date ( date1 ) || ! is_heure ( heure ) );
				} 
				while ( flag );
				cout << "date selectionnee : " << date1 << " " << heure << endl;


				cout << "Rentrez le nombre de mesures pour la comparaison" << endl;
				flag = false;
				do 
				{

					if ( flag ) cout << "entree invalide" << endl;
					cin >> nb_mesures;

					flag = ( ! is_number ( nb_mesures ) || stoi ( nb_mesures ) <= 0 || ( floor ( stof ( nb_mesures ) ) != stof ( nb_mesures ) ) );
				} 
				while ( flag );
				cout << "nombre de mesures demandees : " << nb_mesures << endl;
				cout << endl;


				afficherDate(stringToDateDetailed(date1));
				list < pair < Capteur , Capteur > >* similaires;
				similaires = service->obtenirCapteursSimilaires ( stringToDateDetailed ( date1 ) , stoi ( nb_mesures ) );

				cout << "capteurs similaires : " << nb_mesures << endl;
				for (auto const& i : *similaires) 
				{

					cout << i.first.getSensorID ( ) << " -- " << i.second.getSensorID ( )  << endl;
				}
				break;

			//Verifier comportement capteurs
			case 3:
				cout << "Listez les id des capteurs que vous voulez surveiller" << endl;
				cout << "Rentrez -1 pour arreter la saisie" << endl;
				cout << "Le caractere * designe l integralite des capteurs" << endl;

				captorId = "";
				flag = false;
				do 
				{
					do 
					{
						if ( flag ) { cout << "Rentrez un id non vide" << endl; }
						cin >> captorId;
						flag = (captorId.empty ( ) );
					}
					while ( flag );
					if ( captorId != "-1") 
					{
						list_captorID.push_back ( captorId );
					}	
				} 
				while ( captorId != "*" && captorId != "-1" );
				if ( captorId == "*" ) 
				{ 
					list_captorID.clear();
					list_captorID.push_back( "*" ); 
				}
				
				paramFiltrage p = { tm() ,tm() , Territoire(new Point(0.0, 0.0), 0)  ,"" };

				list<string>* defaillants = service->surveillerComportementCapteurs( list_captorID , p );
				cout << "Liste capteurs defaillants : " << endl;
				for ( auto const& i : *defaillants )
				{
					cout << i << endl;
				}

				cout << endl;
				break;
		}
	}
	return 0;
} // End of menu
