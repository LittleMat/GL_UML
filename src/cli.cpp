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
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

int menu ( ) 
{
	std::string lecture;
	cout << "Menu Principal" << endl;
	cout << "[1] Obtenir la qualite moyenne de l�air" << endl;
	cout << "[2] Obtenir capteurs similaires" << endl;
	cout << "[3] Verifier comportement capteurs" << endl;
	cout << "[4] Quitter application" << endl;
	do {
		cin >> lecture;

	} while (std::stoi(lecture) != 1 && std::stoi(lecture) != 2 && std::stoi(lecture) != 3 && std::stoi(lecture) != 4);
	cout << "Option["<<lecture<<"] selectionnee " << endl;

	return 0;
} // End of menu