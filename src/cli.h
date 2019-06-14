/*************************************************************************
                           Capteur  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <cli> (file cli.h) ----------------

#ifndef CLI_H
#define CLI_H

//--------------------------------------------------- Interfaces used
#include <iostream>
#include <string>
#include "Service.h"
//------------------------------------------------------------------------
// Goal of the <cli> class
// La classe cli g�re les interactions avec l'utilisateur et appelle 
// les services r�pondant � ses demandes.
//------------------------------------------------------------------------


//----------------------------------------------------------------- PUBLIC

/*
 * main function
 */
int menu ( int argc , char ** argv );

#endif // CLI_H
