#include "Service.h"
#include "FileReader.h"
#include <iostream>


int main(int argc, char ** argv)
{
	
	list <string> args;
	for (int i = 3; i < argc; i++)
	{
		args.push_back(string(argv[i]));
	}
	cout << "fichier capteur " << string(argv[1]) << endl;
	Service *service = new Service(string(argv[1]), string(argv[2]), args);
	paramFiltrage p = { tm() ,tm() , Territoire(new Point(0.0, 0.0), 0)  ,"" };
	cout << service->surveillerComportementCapteur("Sensor1", p) << endl;

	tuple<int, list<pair<string, float>>, float> res = service->calculerQualite(p);

	cout << "indice ATMO = " << get <0> (res) << endl;
	for (auto const i : get <1>(res)) {
		std::cout << "AttributID = " << i.first << " ; " << "Valeur = " << i.second << endl;
	}
	cout << "fiabilité = " << get <2>(res) << endl;
	
	//test.push_back("data/data_test_2.csv");
	//test.push_back("data/data_test_3.csv");
	/*
	FileReader * fl = new FileReader("../data/Sensors.csv", "../data/AttributeType.csv", test);

	string input;

	Service service = Service(fl);

	paramFiltrage p = { NULL, NULL, NULL, NULL };

	bool capteurOk = service.surveillerComportementCapteur("Sensor999", p);

	cout << capteurOk << endl;
	*/

	// Test filtrageCapteur
	// trouver 1 capteur = OK
	// Capteur/AireTotale = OK
	// Capteur/territoire = OK si distance fonctionne
	// Capteur/Point = OK si distance fonctionne

	//trouver un capteur
	/*
	Capteur c1 = Capteur("Sensor0", new Point(-34.7692487876719, -8.15758888291083), "ras");
	
	paramFiltrage param;
	param.dateInf = tm();// dateNull retourne bien false
	param.dateSup = tm(); // dateNull retourne bien false
	param.territoire = Territoire();
	param.capteurId = "Sensor0";
	
	cout << Service::filtrageCapteur(c1, param.territoire, param.capteurId) << endl
	*/

	// Capteur/AireTotale
	/*
	Capteur c1 = Capteur("Sensor0", new Point(-34.7692487876, -8.1575888829), "ras");

	paramFiltrage param;
	param.dateInf = tm();// dateNull retourne bien false
	param.dateSup = tm(); // dateNull retourne bien false
	Territoire t = Territoire();
	param.territoire = t;
	
	cout << "Affichage après init Territoire" << endl;
	cout << param.territoire.getRayon() << endl;
	cout << param.territoire.getCentre()->getLatitude() << endl;
	cout << param.territoire.getCentre()->getLongitude() << endl;
	param.capteurId = "";

	cout << Service::filtrageCapteur(c1, param.territoire, param.capteurId) << endl;
	
	*/
	//Point
	/*
	Capteur c1 = Capteur("Sensor0", new Point(-34.7692487876, -8.1575888829), "ras");

	paramFiltrage param;
	param.dateInf = tm();// dateNull retourne bien false
	param.dateSup = tm(); // dateNull retourne bien false
	Territoire t = Territoire(new Point(-34.779013, -8.149297), 2);
	param.territoire = t;

	cout << "Affichage après init Territoire" << endl;
	cout << param.territoire.getRayon() << endl;
	cout << param.territoire.getCentre()->getLatitude() << endl;
	cout << param.territoire.getCentre()->getLongitude() << endl;
	param.capteurId = "";


	cout << "distance en km = "<< c1.getPosition()->distance(param.territoire.getCentre()) << endl;
	cout << "distance en km = " << param.territoire.getCentre()->getLongitude() << endl;
	cout << Service::filtrageCapteur(c1, param.territoire, param.capteurId) << endl;

	*/

	/*
	unordered_map < string, Capteur * > map = fl->lireCapteurs(param, Service::filtrageCapteur);
	for (unordered_map < string, Capteur * >::iterator it = map.begin(); it != map.end(); it++)
	{
		cout << "Capteur trouvé " << it->first << endl;
	}
	while (1)
	{
		Mesure * m = fl->prochaineMesure(param, Service::filtrageMesure);
		if (m == nullptr)
		{
			cout << "fin lecture " << endl;
			break;
		}
		else

		{
			cout << "trouvé" << endl;
			cout << m->getCapteur()->getSensorID() << endl;
			cout << m->getTimestamp()->tm_hour << " : " << m->getTimestamp()->tm_min << " : " << m->getTimestamp()->tm_sec << endl;
		}

	}
	*/



	//// TEST FILTRAGE MESURE
	// 	Mesure ( struct tm * timestamp, Attribut * const attribut, float value, const std :: string sensorID, Capteur * capteur );
	/*
	struct tm * time1 = new tm();
	time1->tm_year = 2017 - 1900;
	time1->tm_mon = 1;
	time1->tm_mday = 1;
	time1->tm_hour = 0;
	time1->tm_min = 1;
	time1->tm_sec = 20;

	// pour m2 normalement pris si instant t + 60 ou si période entre dateInf et dateSup
	struct tm * time2 = new tm();
	time2->tm_year = 2017 - 1900;
	time2->tm_mon = 1;
	time2->tm_mday = 1;
	time2->tm_hour = 1;
	time2->tm_min = 0;
	time2->tm_sec = 20;

	// pour m3 normalement non si periode
	struct tm * time3 = new tm();
	time3->tm_year = 2016 - 1900;
	time3->tm_mon = 12;
	time3->tm_mday = 31;
	time3->tm_hour = 23;
	time3->tm_min = 5;
	time3->tm_sec = 20;

	// pour m4 normalement pris si instant t - 60
	struct tm * time4 = new tm();
	time4->tm_year = 2016 - 1900;
	time4->tm_mon = 12;
	time4->tm_mday = 31;
	time4->tm_hour = 23;
	time4->tm_min = 59;
	time4->tm_sec = 20;
	

	//	Attribut ( std :: string attributID, std :: string unit, std :: string description );
	Attribut * att = new Attribut ("02", "ug/m3", "concentration d'ozone");
	float value = 17.8902017543936;

	//	Capteur ( const std :: string sensorID, Point * position, const std :: string description );

	Capteur * c = new Capteur("Sensor0", new Point(-34.76, -8.16), "ras");

	Mesure m1 = Mesure(time1, att, 1, "Sensor0", c);
	Mesure m2 = Mesure(time2, att, 2, "Sensor0", c);
	Mesure m3 = Mesure(time3, att, 3, "Sensor0", c);
	Mesure m4 = Mesure(time4, att, 4, "Sensor0", c);
	*/

	//Période :
	/*
	paramFiltrage parametre;

	struct tm dateInf;
	dateInf.tm_year = 2017 - 1900;
	dateInf.tm_mon = 1;
	dateInf.tm_mday = 1;
	dateInf.tm_hour = 0;
	dateInf.tm_min = 0;
	dateInf.tm_sec = 20;
	parametre.dateInf = dateInf;

	struct tm dateSup;
	dateSup.tm_year = 2017 - 1900;
	dateSup.tm_mon = 1;
	dateSup.tm_mday = 1;
	dateSup.tm_hour = 1;
	dateSup.tm_min = 30;
	dateSup.tm_sec = 20;
	parametre.dateSup = dateSup;

	cout << "Si ok = 1" << endl;
	if (Service::filtrageMesure(m1, parametre.dateInf, parametre.dateSup) == true)
	{
		cout << "vrai" << endl;
		cout << endl;
	}
	else
	{
		cout << "faux" << endl;
		cout << endl;
	}
	cout << Service::filtrageMesure(m1, parametre.dateInf, parametre.dateSup) << endl;
	cout << Service::filtrageMesure(m2, parametre.dateInf, parametre.dateSup) << endl;
	cout << "Si ok = 0" << endl;
	cout << Service::filtrageMesure(m3, parametre.dateInf, parametre.dateSup) << endl;
	*/

	// instant t
	/*
	paramFiltrage parametre;
	struct tm dateInf;
	dateInf.tm_year = 2017 - 1900;
	dateInf.tm_mon = 1;
	dateInf.tm_mday = 1;
	dateInf.tm_hour = 0;
	dateInf.tm_min = 0;
	dateInf.tm_sec = 20;
	parametre.dateInf = dateInf;
	parametre.dateSup = tm();

	cout << "normalement == 1" << endl;
	cout << Service::filtrageMesure(m1, parametre.dateInf, parametre.dateSup) <<endl;
	cout << Service::filtrageMesure(m2, parametre.dateInf, parametre.dateSup) << endl;
	cout << Service::filtrageMesure(m4, parametre.dateInf, parametre.dateSup) << endl;

	cout << "normalement == 0 " << endl;
	cout << Service::filtrageMesure(m3, parametre.dateInf, parametre.dateSup) << endl;
	*/

	//Tout l'histo
	/*
	paramFiltrage parametre;
	parametre.dateInf = tm();
	parametre.dateSup = tm();

	cout << "normalement == 1" << endl;
	cout << Service::filtrageMesure(m1, parametre.dateInf, parametre.dateSup) << endl;
	cout << Service::filtrageMesure(m2, parametre.dateInf, parametre.dateSup) << endl;
	cout << Service::filtrageMesure(m4, parametre.dateInf, parametre.dateSup) << endl;
	cout << Service::filtrageMesure(m3, parametre.dateInf, parametre.dateSup) << endl;
	*/

	// Test distance
	/*
	Point * p1 = new Point(4.874190, 45.781654); // 21 avenue Jean Caoelle

	Point * p2 = new Point(4.875440, 45.782021); // 29 avenue Jean Caoelle

	cout << p1->distance(p2) << endl;
	*/
	


	string a;
	cin >> a;
	return 0;


} // End of main