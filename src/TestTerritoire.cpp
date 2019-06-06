#include <iostream>
#include "Territoire.h"
#include <ctime>
using namespace std;

typedef struct
{
	// Pour filtrageMesure
	struct tm dateInf;
	struct tm dateSup;
	//Pour filtrageCapteur
	Territoire territoire;
	string capteurId;
} paramFiltrage2;

int main()
{

	cout << "Test Territoire == pointeur" << endl;
	cout << "**************************" << endl;
	cout << "init direct" << endl;
	
	paramFiltrage2 filtre = { tm(), tm(), Territoire(new Point(0, 0), 10), "111" };
	cout << "Latitude = " << filtre.territoire.getCentre()->getLatitude() << endl;
	cout << "Longitude = " << filtre.territoire.getCentre()->getLongitude() << endl;
	
	cout << "**************************" << endl;
	cout << "**************************" << endl;
	cout << "copy - destructeur" << endl;
	/*
	paramFiltrage2 filtre;	
	Territoire t = Territoire(new Point(0.031123, 0.155656), 10);
	filtre.territoire = t;
	cout << "Latitude = " << filtre.territoire.getCentre()->getLatitude() << endl;
	cout << "Longitude = " << filtre.territoire.getCentre()->getLongitude() << endl;
	*/
	cout << "**************************" << endl;

	int a;
	cin >> a;

	return 0;
}