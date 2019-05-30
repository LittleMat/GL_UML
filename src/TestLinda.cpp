#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <list>
#include "cli.h"
#include "Service.h"
#include "FileReader.h"

int main()
{
	// Noms fichiers
	const string nomFichierCapteurs = "../test/resources/DataDifferentDates.csv";
	const string nomFichierAttributs = "../test/resources/AttributeType.csv";
	const string nomFichiersMesures = "../test/resources/Sensor10.csv";
	list<string> list = { nomFichiersMesures };

	//Fichier
	FileReader f (nomFichierCapteurs, nomFichierAttributs, list);

	FILE * fichier_data = fopen(nomFichierCapteurs.c_str(), "r");
	FILE * fichier_att = fopen(nomFichierAttributs.c_str(), "r");
	FILE * fichier_capteur = fopen(nomFichiersMesures.c_str(), "r");
	
	std::string attributID;
	std::string unit;
	std::string description;


	struct tm timestamp;
	Attribut * attribut;
	int value;
	std::string sensorID;
	Capteur * capteur;

	const Mesure * mes = f.prochaineMesure();
	string id = mes->getCapteur()->getSensorID();
	cout << "Capteur = " << id << endl;
	cout << "Valeur = " << mes->getValue() << endl;
	cout << "Timestamp = " << mes->getTimestamp().tm_year << "/"
		<< mes->getTimestamp().tm_mon << "/" << mes->getTimestamp().tm_mday << ";"
		<< mes->getTimestamp().tm_hour << ":" << mes->getTimestamp().tm_min << ":" << mes->getTimestamp().tm_sec << endl;
	string a = "";
	cin >> a;
	return 0;
}