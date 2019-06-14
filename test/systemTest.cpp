#include <limits>
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES
using namespace std;
#include "gtest/gtest.h"
#include "Point.h"
#include "Capteur.h"
#include "Territoire.h"
#include "FileReader.h"
#include "Service.h"
#include "cli.h"

namespace
{
TEST(ErrorTest, EmptyParameters)
{
    // Redirect cin cout
    istringstream sin("");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());
    char **parameters = (char **)malloc(4 * sizeof(char *));
    char *programName = (char *)"./exec";
    char *fileCapteur = (char *)"resources/Sensor10.csv";
    char *fileAttribute = (char *)"resources/AttributeType.csv";

    parameters[0] = programName;
    ASSERT_NO_THROW(menu(1, parameters));

    EXPECT_EQ("Nombre d'arguments insuffisant\n", sout.str());

    cout.rdbuf(coutBuf);
    sout.clear();
    sout.str("");
    cout.rdbuf(sout.rdbuf());

    parameters[1] = fileCapteur;
    ASSERT_NO_THROW(menu(2, parameters));

    EXPECT_EQ("Nombre d'arguments insuffisant\n", sout.str());

    cout.rdbuf(coutBuf);
    sout.clear();
    sout.str("");
    cout.rdbuf(sout.rdbuf());

    parameters[2] = fileAttribute;
    ASSERT_NO_THROW(menu(3, parameters));

    EXPECT_EQ("Nombre d'arguments insuffisant\n", sout.str());

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(ErrorTest, InvalidParameters)
{
    // Redirect cin cout
    istringstream sin("");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());
    char **parameters = (char **)malloc(4 * sizeof(char *));
    char *programName = (char *)"./exec";
    char *fileCapteur = (char *)"meaningless";
    char *fileAttribute = (char *)"meaningless";
    char *fileData = (char *)"meaningless";
    parameters[0] = programName;
    parameters[1] = fileCapteur;
    parameters[2] = fileAttribute;
    parameters[3] = fileData;
    EXPECT_NO_THROW(menu(4, parameters));

    //TODO: Add expected result

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(ErrorTest, WrongParameters)
{
    // Redirect cin cout
    istringstream sin("");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());
    char **parameters = (char **)malloc(4 * sizeof(char *));
    parameters[0] = (char *)"./exec";
    parameters[1] = (char *)"resources/Sensor10.csv";
    parameters[2] = (char *)"resources/AttributeType.csv";
    parameters[3] = (char *)"resources/Data10.csv";

    parameters[1] = (char *)"InvalidCSV.csv";
    EXPECT_NO_THROW(menu(4, parameters));

    //TODO: Add expected result

    cout.rdbuf(coutBuf);
    sout.clear();
    sout.str("");
    cout.rdbuf(sout.rdbuf());

    parameters[1] = (char *)"resources/Sensor10.csv";
    parameters[2] = (char *)"resources/InvalidCSV.csv";
    EXPECT_NO_THROW(menu(4, parameters));

    //TODO: Add expected result

    cout.rdbuf(coutBuf);
    sout.clear();
    sout.str("");
    cout.rdbuf(sout.rdbuf());

    parameters[2] = (char *)"resources/AttributeType.csv";
    parameters[3] = (char *)"resources/InvalidCSV.csv";
    EXPECT_NO_THROW(menu(4, parameters));

    //TODO: Add expected result

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(FunctionTest, Exit)
{
    // Redirect cin cout
    istringstream sin("4\n");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());

    // Parameters for the program
    char **parameters = (char **)malloc(4 * sizeof(char *));
    parameters[0] = (char *)"./exec";
    parameters[1] = (char *)"resources/Sensor10.csv";
    parameters[2] = (char *)"resources/AttributeType.csv";
    parameters[3] = (char *)"resources/Data10.csv";

    EXPECT_NO_THROW(menu(4, parameters));

    // Result
    EXPECT_EQ(string("Menu Principal\n") + string("[1] Obtenir la qualite moyenne de l air\n") + string("[2] Obtenir capteurs similaires\n") + string("[3] Verifier comportement capteurs\n") + string("[4] Quitter application\n\n"), sout.str());

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(FunctionTest, SurveillerComportementCapteurs)
{
    // Redirect cin cout
    istringstream sin("3\n*\n4\n");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());

    // Parameters for the program
    char **parameters = (char **)malloc(4 * sizeof(char *));
    parameters[0] = (char *)"./exec";
    parameters[1] = (char *)"resources/Sensor10.csv";
    parameters[2] = (char *)"resources/AttributeType.csv";
    parameters[3] = (char *)"resources/ServiceTestData.csv";

    EXPECT_NO_THROW(menu(4, parameters));

    // Result
    EXPECT_EQ(string("Menu Principal\n") 
            + string("[1] Obtenir la qualite moyenne de l air\n") 
            + string("[2] Obtenir capteurs similaires\n") 
            + string("[3] Verifier comportement capteurs\n") 
            + string("[4] Quitter application\n\n") 
            + string("Listez les id des capteurs que vous voulez surveiller\n") 
            + string("Rentrez -1 pour arreter la saisie\n") 
            + string("Le caractere * designe l integralite des capteurs\n") 
            + string("Liste capteurs defaillants : \n") 
            + string("Sensor2\n") 
            + string("Sensor3\n\n") 
            + string("Menu Principal\n") 
            + string("[1] Obtenir la qualite moyenne de l air\n") 
            + string("[2] Obtenir capteurs similaires\n")
            + string("[3] Verifier comportement capteurs\n") 
            + string("[4] Quitter application\n\n")
            , sout.str());

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(FunctionTest, SurveillerComportementCapteurs2)
{
    // Redirect cin cout
    istringstream sin("3\nSensor3\nSensor4\n-1\n4\n");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());

    // Parameters for the program
    char **parameters = (char **)malloc(4 * sizeof(char *));
    parameters[0] = (char *)"./exec";
    parameters[1] = (char *)"resources/Sensor10.csv";
    parameters[2] = (char *)"resources/AttributeType.csv";
    parameters[3] = (char *)"resources/ServiceTestData.csv";

    EXPECT_NO_THROW(menu(4, parameters));

    // Result
    EXPECT_EQ(string("Menu Principal\n") 
            + string("[1] Obtenir la qualite moyenne de l air\n") 
            + string("[2] Obtenir capteurs similaires\n") 
            + string("[3] Verifier comportement capteurs\n") 
            + string("[4] Quitter application\n\n") 
            + string("Listez les id des capteurs que vous voulez surveiller\n") 
            + string("Rentrez -1 pour arreter la saisie\n") 
            + string("Le caractere * designe l integralite des capteurs\n") 
            + string("Liste capteurs defaillants : \n") 
            + string("Sensor3\n\n") 
            + string("Menu Principal\n") 
            + string("[1] Obtenir la qualite moyenne de l air\n") 
            + string("[2] Obtenir capteurs similaires\n") 
            + string("[3] Verifier comportement capteurs\n") 
            + string("[4] Quitter application\n\n"), sout.str());

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(FunctionTest, ObtenirCapteursSimilaires)
{
}
TEST(FunctionTest, CalculerQualite)
{
    // Redirect cin cout
    istringstream sin("1\n4\nSensor0\n*\n4\n");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());

    // Parameters for the program
    char **parameters = (char **)malloc(4 * sizeof(char *));
    parameters[0] = (char *)"./exec";
    parameters[1] = (char *)"resources/Sensor10.csv";
    parameters[2] = (char *)"resources/AttributeType.csv";
    parameters[3] = (char *)"resources/ServiceTestData.csv";

    EXPECT_NO_THROW(menu(4, parameters));

    // Result
    EXPECT_EQ(string("Menu Principal\n") 
            + string("[1] Obtenir la qualite moyenne de l air\n") 
            + string("[2] Obtenir capteurs similaires\n") 
            + string("[3] Verifier comportement capteurs\n") 
            + string("[4] Quitter application\n\n") 
            + string("Choississez le type de zone a etudier\n")
            + string("[1] Point precis (lat, long)\n")
            + string("[2] Territoire (Point, rayon)\n")
            + string("[3] Aire totale\n")
            + string("[4] Capteur\n")
            + string("[5] Retour\n")
            + string("\nRentrez l'id d'un capteur\n") 
            + string("\nIndiquer la periode temporelle\n")
            + string("[1]A une date donnee plus ou moins une heure : date\n")
            + string("[2]Sur une plage de temps donnee delimitee par deux dates : date1 date2\n")
            + string("[*]Sur l integralite des mesures  * \n")
            + string("Indice ATMO 3\n")
            + string("Indice fiabilite 100%\n")
            + string("O3,49.2417\n")
            + string("NO2,82.5779\n")
            + string("SO2,52.2821\n")
            + string("PM10,5.96786\n")
            + string("\nMenu Principal\n") 
            + string("[1] Obtenir la qualite moyenne de l air\n") 
            + string("[2] Obtenir capteurs similaires\n") 
            + string("[3] Verifier comportement capteurs\n") 
            + string("[4] Quitter application\n\n"), sout.str());

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
} //namespace