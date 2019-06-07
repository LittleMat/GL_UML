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
TEST(SampleTest, Sample)
{
    // Redirect cin cout
    istringstream sin("Hello World\n");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());
    string buffer;
    getline(cin, buffer);
    cout << buffer;
    EXPECT_EQ("Hello World", sout.str());
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(ErrorTest, EmptyParameters)
{
    // Redirect cin cout
    istringstream sin("");
    ostringstream sout;
    streambuf *cinBuf = cin.rdbuf(sin.rdbuf());
    streambuf *coutBuf = cout.rdbuf(sout.rdbuf());
    char **parameters = (char **)malloc(4 * sizeof(char *));
    char programName[] = "./exec";
    char fileCapteur[] = "resources/Sensor10.csv";
    char fileAttribute[] = "resources/AttributeType.csv";
    char fileData[] = "resources/Data10.csv";

    parameters[0] = programName;
    EXPECT_NO_THROW(menu(1, parameters));

    //TODO: Add expected result

    cout.rdbuf(coutBuf);
    sout.flush();
    cout.rdbuf(sout.rdbuf());

    parameters[1] = fileCapteur;
    EXPECT_NO_THROW(menu(2, parameters));

    //TODO: Add expected result

    cout.rdbuf(coutBuf);
    sout.flush();
    cout.rdbuf(sout.rdbuf());

    parameters[2] = fileAttribute;
    EXPECT_NO_THROW(menu(3, parameters));

    //TODO: Add expected result

    cout.rdbuf(coutBuf);
    sout.flush();
    cout.rdbuf(sout.rdbuf());

    parameters[3] = fileData;
    sin.str("4");
    EXPECT_NO_THROW(menu(4, parameters));
    EXPECT_EQ("", sout.str());

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
    char programName[] = "./exec";
    char fileCapteur[] = "meaningless";
    char fileAttribute[] = "meaningless";
    char fileData[] = "meaningless";
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
    char programName[] = "./exec";
    char* fileCapteur = "resources/Sensor10.csv";
    char* fileAttribute = "resources/AttributeType.csv";
    char* fileData = "resources/Data10.csv";
    parameters[0] = programName;
    parameters[1] = fileCapteur;
    parameters[2] = fileAttribute;
    parameters[3] = fileData;

    fileCapteur = "InvalidCSV.csv";
    EXPECT_NO_THROW(menu(4, parameters));

    //TODO: Add expected result

    cout.rdbuf(coutBuf);
    sout.flush();
    cout.rdbuf(sout.rdbuf());

    fileCapteur = "resources/Sensor10.csv";
    fileAttribute = "resources/InvalidCSV.csv";
    EXPECT_NO_THROW(menu(4, parameters));

    //TODO: Add expected result

    cout.rdbuf(coutBuf);
    sout.flush();
    cout.rdbuf(sout.rdbuf());

    fileAttribute = "resources/AttributeType.csv";
    fileData = "resources/InvalidCSV.csv";
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
    char programName[] = "./exec";
    char* fileCapteur = "resources/Sensor10.csv";
    char* fileAttribute = "resources/AttributeType.csv";
    char* fileData = "resources/Data10.csv";
    parameters[0] = programName;
    parameters[1] = fileCapteur;
    parameters[2] = fileAttribute;
    parameters[3] = fileData;

    EXPECT_NO_THROW(menu(4, parameters));
    
    // Result
    EXPECT_EQ(string("Menu Principal\n")
        + string("[1] Obtenir la qualite moyenne de l air\n")
        + string("[2] Obtenir capteurs similaires\n")
        + string("[3] Verifier comportement capteurs\n")
        + string("[4] Quitter application\n"), sout.str());

    free(parameters);
    cin.rdbuf(cinBuf);
    cout.rdbuf(coutBuf);
}
TEST(FunctionTest, SurveillerComportementCapteur)
{

}
TEST(FunctionTest, SurveillerComportementCapteurs)
{

}
TEST(FunctionTest, ObtenirCapteursSimilaires)
{

}
TEST(FunctionTest, CalculerQualite)
{

}
} //namespace