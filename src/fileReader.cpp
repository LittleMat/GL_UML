
/*************************************************************************
                           FileReader  -  description
                             -------------------
    beginning            : 14/05
    copyright            : (C) 2019 by CERBA Guilhem, YE Zihang, YE Linda, MONTGOMERY Mathieu, ZHANG Tianyu
    e-mail               : guilhem.cerba@insa-lyon.fr, zihang.ye@insa-lyon.fr, linda.ye@insa-lyon.fr , mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <FileReader> (file FileReader.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include

//------------------------------------------------------ Personnal include

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

//-------------------------------------------- Constructors - destructor

FileReader :: FileReader ( const std :: string & nomFichierCapteurs, const string & nomFichierAttributs, const std :: list < std :: string > & nomFichiersMesures, const std :: string & fichierMesureEnCours)
{
	#ifdef MAP
	    cerr << "Constructor of <Capteur>" << endl;
	#endif

} // End of constructor

FileReader :: ~FileReader ( )
{

} // End of destructor