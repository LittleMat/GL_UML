#include <limits>
#include <cmath>
#include <tuple>
#define _USE_MATH_DEFINES
using namespace std;
#include "gtest/gtest.h"
#include "Point.h"
#include "Capteur.h"
#include "Territoire.h"
#include "FileReader.h"
#include "Service.h"

namespace
{
TEST(PointUnitTest, Constructor)
{
    Point p0(123, 49);
    EXPECT_FLOAT_EQ(p0.getLongitude(), 123);
    EXPECT_FLOAT_EQ(p0.getLatitude(), 49);

    Point p1(-54, -16);
    EXPECT_FLOAT_EQ(p1.getLongitude(), -54);
    EXPECT_FLOAT_EQ(p1.getLatitude(), -16);
}
TEST(PointUnitTest, ConstructorIllegalArgument)
{
    EXPECT_ANY_THROW(Point p(-181, 0));
    EXPECT_ANY_THROW(Point p(181, 0));
    EXPECT_ANY_THROW(Point p(0, 91));
    EXPECT_ANY_THROW(Point p(0, -91));
}
TEST(PointUnitTest, DistanceIllegalArgument)
{
    Point p(0, 0);
    EXPECT_ANY_THROW(p.distance(nullptr));
}
TEST(PointUnitTest, Distance_ZERO)
{
    Point p0(0, 0);
    Point p1(0, 0);

    EXPECT_FLOAT_EQ(0, p0.distance(&p1));

    // The Earth isn't flat
    Point p2(-180, 0);
    Point p3(180, 0);
    EXPECT_FLOAT_EQ(0, p2.distance(&p3));

    // The North Pole is a point
    Point p4(0, 90);
    Point p5(180, 90);
    EXPECT_FLOAT_EQ(0, p4.distance(&p5));

    // The South Pole is a point
    Point p6(0, -90);
    Point p7(180, -90);
    EXPECT_FLOAT_EQ(0, p6.distance(&p7));
}
TEST(PointUnitTest, Distance)
{
    Point p0(0, 0);
    Point p1(90, 0);
    EXPECT_NEAR(10010, p0.distance(&p1), 100);

    Point p2(0, 0);
    Point p3(0, 90);
    EXPECT_NEAR(10010, p2.distance(&p3), 100);

    Point p4(0, 0);
    Point p5(180, 0);
    EXPECT_NEAR(20020, p4.distance(&p5), 100);

    Point p6(35, 46);
    Point p7(97, -4);
    EXPECT_NEAR(8240, p6.distance(&p7), 100);
}

TEST(CapteurUnitTest, ConstructorIllegalArgument)
{
    Point *p = new Point(0, 0);
    EXPECT_ANY_THROW(Capteur c0("", p, ""));
    EXPECT_ANY_THROW(Capteur c1("c1", nullptr, ""));
    delete p;
}
TEST(CapteurUnitTest, Constructor)
{
    Capteur c0("c0", new Point(10, -10), "Description");
    EXPECT_EQ(c0.getSensorID(), "c0");
    EXPECT_FLOAT_EQ(c0.getPosition()->getLatitude(), -10);
    EXPECT_FLOAT_EQ(c0.getPosition()->getLongitude(), 10);
    EXPECT_EQ(c0.getDescription(), "Description");
}

TEST(TerritoireUnitTest, ConstructorIllegalArgument)
{
    Point p(0, 0);
    EXPECT_ANY_THROW(Territoire t0(p, -10));
}
TEST(TerritoireUnitTest, Constructor)
{
    Point p(0.14, 0.59);
    Territoire t0(p, 125);
    EXPECT_FLOAT_EQ(t0.getRayon(), 125);
    EXPECT_FLOAT_EQ(t0.getCentre().getLongitude(), 0.14);
    EXPECT_FLOAT_EQ(t0.getCentre().getLatitude(), 0.59);
}
TEST(TerritoireUnitTest, ContientIllegalArgument)
{
    Point p(0, 0);
    Territoire t0(p, 10);
    EXPECT_ANY_THROW(t0.contient(nullptr));
}
TEST(TerritoireUnitTest, Contient)
{
    Point p(0, 0);
    Territoire t0(p, 1000);
    Point p0(0, 0);
    EXPECT_TRUE(t0.contient(&p0));
    Point p1(0, 90);
    EXPECT_FALSE(t0.contient(&p1));
    Point p2(-3, 2.21);
    EXPECT_TRUE(t0.contient(&p2));
}

TEST(AttributUnitTest, ConstructorIllegalArgument)
{
    EXPECT_ANY_THROW(Attribut("", "unit", "description"));
    EXPECT_ANY_THROW(Attribut("id", "", "description"));
}
TEST(AttributUnitTest, Constructor)
{
    Attribut attribut("id", "unit", "description");
    EXPECT_EQ(attribut.getAttributID(), "id");
    EXPECT_EQ(attribut.getUnit(), "unit");
    EXPECT_EQ(attribut.getDescription(), "description");
}

TEST(MesureUnitTest, ConstructorIllegalArgument)
{
    time_t now = time(NULL);
    time_t future = now + 86400;
    struct tm *now_t = localtime(&now);
    struct tm *future_t = localtime(&future);
    struct tm empty;
    EXPECT_NO_THROW(Mesure(empty, "attributId", 0, "sensorId"));
    EXPECT_ANY_THROW(Mesure(*now_t, "", 0, "sensorId"));
    EXPECT_ANY_THROW(Mesure(*now_t, "attributId", 0, ""));
    EXPECT_ANY_THROW(Mesure(*future_t, "attributId", 0, "sensorId"));
}

TEST(FileReaderUnitTest, ConstructorIllegalArgument)
{
    list<string> listS;
    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(FileReader reader("", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "", listS));
    listS.clear();
    EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));

    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(FileReader reader("meaningless.csv", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "meaningless.csv", listS));
    listS.clear();
    listS.push_back("meaningless.csv");
    EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
}
TEST(FileReaderUnitTest, ConstructorIllegalFile)
{
    list<string> listS;
    // Invalid CSV
    listS.push_back("resources/InvalidCSV.csv");
    EXPECT_ANY_THROW(FileReader reader0("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
    listS.clear();
    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(FileReader reader0("resources/InvalidCSV.csv", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(FileReader reader0("resources/Sensor10.csv", "resources/InvalidCSV.csv", listS));

    // Invalid Data
    listS.clear();
    listS.push_back("resources/InvalidData.csv");
    EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
    listS.clear();
    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(FileReader reader("resources/InvalidSensor.csv", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "resources/InvalidAttributeType.csv", listS));

    // Broken File
    listS.clear();
    listS.push_back("resources/Data10.csv");
    EXPECT_NO_THROW(FileReader reader("resources/BrokenSensor.csv", "resources/AttributeType.csv", listS));
    EXPECT_NO_THROW(FileReader reader("resources/Sensor10.csv", "resources/BrokenAttributeType.csv", listS));
    listS.clear();
    listS.push_back("resources/BrokenData.csv");
    EXPECT_NO_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
}
TEST(FileReaderUnitTest, Constructor)
{
    list<string> listS;
    listS.push_back("resources/Data10.csv");
    EXPECT_NO_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
}
TEST(FileReaderUnitTest, LireAttributs)
{
    list<string> listS;
    listS.push_back("resources/Data10.csv");
    FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    unordered_map<string, Attribut *> attributs = reader.lireAttributs();
    Attribut *tmp = nullptr;
    ASSERT_NO_THROW(tmp = attributs.at("O3"));
    tmp = attributs.at("O3");
    EXPECT_EQ("µg/m3", tmp->getUnit());
    EXPECT_EQ("concentration d'ozone", tmp->getDescription());
    ASSERT_NO_THROW(tmp = attributs.at("SO2"));
    tmp = attributs.at("SO2");
    EXPECT_EQ("µg/m3", tmp->getUnit());
    EXPECT_EQ("concentration de dioxyde de soufre", tmp->getDescription());
    ASSERT_NO_THROW(tmp = attributs.at("NO2"));
    tmp = attributs.at("NO2");
    EXPECT_EQ("µg/m3", tmp->getUnit());
    EXPECT_EQ("concentration de dioxyde d'azote", tmp->getDescription());
    ASSERT_NO_THROW(tmp = attributs.at("PM10"));
    tmp = attributs.at("PM10");
    EXPECT_EQ("µg/m3", tmp->getUnit());
    EXPECT_EQ("concentration de particules fines", tmp->getDescription());
}
TEST(FileReaderUnitTest, LireCapteur)
{
    list<string> listS;
    listS.push_back("resources/Data10.csv");
    FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    function<bool(Capteur &)> passAll = [](Capteur &capteur) -> bool { return true; };
    unordered_map<string, Capteur *> capteurs;

    EXPECT_ANY_THROW(capteurs = reader.lireCapteurs(NULL));

    capteurs = reader.lireCapteurs(passAll);
    EXPECT_EQ(10, capteurs.size());
    Capteur *capteur = nullptr;
    ASSERT_NO_THROW(capteur = capteurs.at("Sensor0"));
    capteur = capteurs.at("Sensor0");
    EXPECT_FLOAT_EQ(-34.7692487876719, capteur->getPosition()->getLongitude());
    EXPECT_FLOAT_EQ(-8.15758888291083, capteur->getPosition()->getLatitude());
    EXPECT_TRUE(capteur->getDescription().empty());
    ASSERT_NO_THROW(capteur = capteurs.at("Sensor9"));
    capteur = capteurs.at("Sensor9");
    EXPECT_FLOAT_EQ(1.33005024461543, capteur->getPosition()->getLongitude());
    EXPECT_FLOAT_EQ(36.2756694672982, capteur->getPosition()->getLatitude());
    EXPECT_TRUE(capteur->getDescription().empty());
}
TEST(FileReaderUnitTest, ProchaineMesure)
{
    list<string> listS;
    listS.push_back("resources/Data10.csv");
    FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    function<bool(Capteur &)> passAllCapteur = [](Capteur &capteur) -> bool { return true; };
    function<bool(Mesure &)> passAllMesure = [](Mesure &mesure) -> bool { return true; };
    Mesure *mesure = nullptr;

    EXPECT_ANY_THROW(mesure = reader.prochaineMesure(NULL));

    reader.debutMesure();
    reader.lireCapteurs(passAllCapteur);
    reader.lireAttributs();
    mesure = reader.prochaineMesure(passAllMesure);
    ASSERT_TRUE(mesure != nullptr);
    EXPECT_EQ(2017, 1900 + mesure->getTimestamp().tm_year);
    EXPECT_EQ("Sensor0", mesure->getSensorID());
    EXPECT_FLOAT_EQ(17.8902017543936, mesure->getValue());
    delete mesure;
    for (int i = 0; i < 8; i++)
    {
        mesure = reader.prochaineMesure(passAllMesure);
        ASSERT_TRUE(mesure != nullptr);
        delete mesure;
    }
    mesure = reader.prochaineMesure(passAllMesure);
    EXPECT_EQ(nullptr, mesure);
}
// Test if two data files are used
TEST(FileReaderUnitTest, ProchaineMesure2)
{
    list<string> listS;
    listS.push_back("resources/Data10.csv");
    listS.push_back("resources/Data20.csv");
    FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    function<bool(Capteur &)> passAllCapteur = [](Capteur &capteur) -> bool { return true; };
    function<bool(Mesure &)> passAllMesure = [](Mesure &mesure) -> bool { return true; };
    Mesure *mesure = nullptr;
    FileReader reader2("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    reader.debutMesure();
    reader.lireCapteurs(passAllCapteur);
    reader.lireAttributs();
    for (int i = 0; i < 9; i++)
    {
        mesure = reader.prochaineMesure(passAllMesure);
        ASSERT_TRUE(mesure != nullptr);
        delete mesure;
    }
    mesure = reader.prochaineMesure(passAllMesure);
    ASSERT_TRUE(mesure != nullptr);
    EXPECT_EQ(2017, 1900 + mesure->getTimestamp().tm_year);
    EXPECT_EQ("Sensor2", mesure->getSensorID());
    EXPECT_FLOAT_EQ(22.1864461494123, mesure->getValue());
    delete mesure;
}

TEST(ServiceUnitTest, FiltrageMesure)
{
    time_t now = time(NULL);
    time_t halfHour = now - 1800;
    time_t yesterday = now - 86400;
    time_t beforeYesterday = now - 2 * 86400;
    struct tm empty_tm = tm();
    struct tm now_tm = *localtime(&now);
    struct tm halfHour_tm = *localtime(&halfHour);
    struct tm yesterday_tm = *localtime(&yesterday);
    struct tm beforeYesterday_tm = *localtime(&beforeYesterday);
    Mesure mesureNow(now_tm, "attributId", 10, "sensorId");
    Mesure mesureYesterday(yesterday_tm, "attributId", 10, "sensorId");
    Mesure mesureBeforeYesterday(beforeYesterday_tm, "attributId", 10, "sensorId");

    EXPECT_TRUE(Service::filtrageMesure(mesureYesterday, beforeYesterday_tm, now_tm));
    // An instant around a given time
    EXPECT_TRUE(Service::filtrageMesure(mesureNow, empty_tm, halfHour_tm));
    EXPECT_FALSE(Service::filtrageMesure(mesureYesterday, empty_tm, now_tm));

    // A periode since a given time
    EXPECT_TRUE(Service::filtrageMesure(mesureNow, halfHour_tm, empty_tm));
    EXPECT_TRUE(Service::filtrageMesure(mesureNow, yesterday_tm, empty_tm));

    // All accepted
    EXPECT_TRUE(Service::filtrageMesure(mesureBeforeYesterday, empty_tm, empty_tm));
    EXPECT_TRUE(Service::filtrageMesure(mesureYesterday, empty_tm, empty_tm));
    EXPECT_TRUE(Service::filtrageMesure(mesureNow, empty_tm, empty_tm));

    EXPECT_FALSE(Service::filtrageMesure(mesureYesterday, now_tm, empty_tm));
    EXPECT_FALSE(Service::filtrageMesure(mesureNow, empty_tm, yesterday_tm));
}
TEST(ServiceUnitTest, FiltrageCapteur)
{
    Capteur capteurOrigin("sensorId", new Point(0, 0), "description");
    Capteur capteurParis("sensorId", new Point(2.21, 48.51), "descrption");

    Territoire empty(Point(0, 0), M_PI * RAYON_TERRE); // All surface
    Territoire point(Point(2.21, 48.51), 0);           // Radius 10km
    Territoire circle(Point(2, 48), 100);              // Radius * 1.1

    EXPECT_TRUE(Service::filtrageCapteur(capteurOrigin, empty, ""));
    EXPECT_FALSE(Service::filtrageCapteur(capteurOrigin, point, ""));
    EXPECT_FALSE(Service::filtrageCapteur(capteurOrigin, circle, ""));
    EXPECT_TRUE(Service::filtrageCapteur(capteurParis, empty, ""));
    EXPECT_TRUE(Service::filtrageCapteur(capteurParis, point, ""));
    EXPECT_TRUE(Service::filtrageCapteur(capteurParis, circle, ""));

    // the territoire will be ignored in the presence of capteurId
    EXPECT_TRUE(Service::filtrageCapteur(capteurOrigin, point, "sensorId"));
    EXPECT_TRUE(Service::filtrageCapteur(capteurOrigin, circle, "sensorId"));

    EXPECT_FALSE(Service::filtrageCapteur(capteurOrigin, empty, "meaningless"));
    EXPECT_FALSE(Service::filtrageCapteur(capteurParis, point, "meaningless"));
    EXPECT_FALSE(Service::filtrageCapteur(capteurParis, circle, "meaningless"));
}
TEST(ServiceUnitTest, DateNull)
{
    struct tm empty = tm();
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    EXPECT_TRUE(Service::dateNull(empty));
    EXPECT_FALSE(Service::dateNull(*today));
}
TEST(ServiceUnitTest, PlusOuMoins)
{
    EXPECT_TRUE(Service::plusOuMoins(1, 1, 0));
    EXPECT_TRUE(Service::plusOuMoins(-10, 10, 20));
    EXPECT_TRUE(Service::plusOuMoins(10, -10, 20));
    EXPECT_TRUE(Service::plusOuMoins(1.000001, 1.000002, 0.00001));
    EXPECT_FALSE(Service::plusOuMoins(1, 10, 0));
    EXPECT_FALSE(Service::plusOuMoins(-10, 10, 5));
    EXPECT_FALSE(Service::plusOuMoins(10, -10, 5));
    EXPECT_FALSE(Service::plusOuMoins(-FLT_MAX, FLT_MAX, 100));
    EXPECT_FALSE(Service::plusOuMoins(FLT_MAX, -FLT_MAX, 100));
}
TEST(ServiceUnitTest, Fiabilite)
{
    Capteur capteurOrigin("sensorId", new Point(0, 0), "description");
    Capteur capteurParis("sensorId", new Point(2.21, 48.51), "descrption");
    Capteur capteurLondon("sensorId", new Point(-0.2416795, 51.5285582), "");

    Territoire empty(Point(0, 0), M_PI * RAYON_TERRE); // All surface
    Territoire point(Point(2.21, 48.51), 0);           // Radius 10km
    Territoire circle(Point(2, 48), 56);              // Radius * 1.1
    Territoire circle2(Point(0.983816, 50.248353), 160);

    EXPECT_FLOAT_EQ(1.0, Service::fiabilite(capteurOrigin, empty));
    EXPECT_FLOAT_EQ(0, Service::fiabilite(capteurOrigin, point));
    EXPECT_FLOAT_EQ(0, Service::fiabilite(capteurOrigin, circle));
    EXPECT_FLOAT_EQ(1.0, Service::fiabilite(capteurParis, empty));
    EXPECT_FLOAT_EQ(1.0, Service::fiabilite(capteurParis, point));
    EXPECT_FLOAT_EQ(0.49967861, Service::fiabilite(capteurParis, circle));
    EXPECT_FLOAT_EQ(0.6069622, Service::fiabilite(capteurLondon, circle2));
}
TEST(ServiceUnitTest, ConstructorIllegalArgument)
{
    list<string> listS;
    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(Service service("", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "", listS));
    listS.clear();
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS));

    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(Service service("meaningless.csv", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "meaningless.csv", listS));
    listS.clear();
    listS.push_back("meaningless.csv");
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
}
TEST(ServiceUnitTest, ConstructorIllegalFile)
{
    list<string> listS;
    // Invalid CSV
    listS.push_back("resources/InvalidCSV.csv");
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
    listS.clear();
    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(Service service("resources/InvalidCSV.csv", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "resources/InvalidCSV.csv", listS));

    // Invalid Data
    listS.clear();
    listS.push_back("resources/InvalidData.csv");
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
    listS.clear();
    listS.push_back("resources/Data10.csv");
    EXPECT_ANY_THROW(Service service("resources/InvalidSensor.csv", "resources/AttributeType.csv", listS));
    EXPECT_ANY_THROW(Service service("resources/Sensor10.csv", "resources/InvalidAttributeType.csv", listS));

    // Broken File
    listS.clear();
    listS.push_back("resources/Data10.csv");
    EXPECT_NO_THROW(Service service("resources/BrokenSensor.csv", "resources/AttributeType.csv", listS));
    EXPECT_NO_THROW(Service service("resources/Sensor10.csv", "resources/BrokenAttributeType.csv", listS));
    listS.clear();
    listS.push_back("resources/BrokenData.csv");
    EXPECT_NO_THROW(Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
}
TEST(ServiceUnitTest, Constructor)
{
    list<string> listS;
    listS.push_back("resources/ServiceTestData.csv");
    EXPECT_NO_THROW(Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
}
TEST(ServiceUnitTest, SurveillerComportementCapteurs)
{
    list<string> listS;
    listS.push_back("resources/ServiceTestData.csv");
    Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    function<bool(Mesure &)> passAllMesure = [](Mesure &mesure) -> bool { return true; };
    list<string> capteurs;
    ASSERT_ANY_THROW(service.surveillerComportementCapteurs(capteurs, passAllMesure));
    capteurs.push_back("Sensor0");
    capteurs.push_back("Sensor1");
    capteurs.push_back("Sensor2");
    capteurs.push_back("Sensor3");
    capteurs.push_back("Sensor4");
    ASSERT_ANY_THROW(service.surveillerComportementCapteurs(capteurs, NULL));

    list<string> *listCapteur = service.surveillerComportementCapteurs(capteurs, passAllMesure);
    EXPECT_TRUE(find(listCapteur->begin(), listCapteur->end(), "Sensor0") == listCapteur->end());
    EXPECT_TRUE(find(listCapteur->begin(), listCapteur->end(), "Sensor1") == listCapteur->end());
    EXPECT_TRUE(find(listCapteur->begin(), listCapteur->end(), "Sensor2") != listCapteur->end());
    EXPECT_TRUE(find(listCapteur->begin(), listCapteur->end(), "Sensor3") != listCapteur->end());
    delete listCapteur;
}
TEST(ServiceUnitTest, ObtenirCapteursSimilaires)
{
    list<string> listS;
    listS.push_back("resources/ServiceTestData.csv");
    Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    struct tm time = tm();
    time.tm_year = 117;
    time.tm_mday = 1;
    time.tm_mon = 0;
    time.tm_hour = 0;
    time.tm_min = 1;
    list<pair<string, string>> *similar = service.obtenirCapteursSimilaires(time, 1);
    cout << similar->size() << endl;
    ASSERT_TRUE(similar->size() == 2);
    if (similar->front().first == "Sensor0")
    {
        EXPECT_EQ("Sensor1", similar->front().second);
    }
    if (similar->front().first == "Sensor1")
    {
        EXPECT_EQ("Sensor0", similar->front().second);
    }
    similar->pop_front();
    if (similar->front().first == "Sensor0")
    {
        EXPECT_EQ("Sensor1", similar->front().second);
    }
    if (similar->front().first == "Sensor1")
    {
        EXPECT_EQ("Sensor0", similar->front().second);
    }
}
TEST(ServiceUnitTest, CalculerQualite)
{
    list<string> listS;
    listS.push_back("resources/ServiceTestData.csv");
    Service service("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
    function<float(Capteur &)> passCapteur = [](Capteur &capteur) -> float { return capteur.getSensorID() == "Sensor0" || capteur.getSensorID() == "Sensor1" ? 0.9 : 0; };
    function<bool(Mesure &)> passMesure = [](Mesure &mesure) -> bool { return mesure.getTimestamp().tm_hour == 0 && mesure.getTimestamp().tm_min <= 30; };
    string empty;
    tuple < int , list < pair < string , float > > , float > qualite =  service.calculerQualite ( empty, passMesure, passCapteur );
    EXPECT_EQ(3, get<0>(qualite));
    ASSERT_EQ("O3", get<1>(qualite).front().first);
    EXPECT_FLOAT_EQ(34.33498085,get<1>(qualite).front().second);
    get<1>(qualite).pop_front();
    ASSERT_EQ("NO2", get<1>(qualite).front().first);
    EXPECT_FLOAT_EQ(70.8543904,get<1>(qualite).front().second);
    get<1>(qualite).pop_front();
    ASSERT_EQ("SO2", get<1>(qualite).front().first);
    EXPECT_FLOAT_EQ(32.8982247,get<1>(qualite).front().second);
    get<1>(qualite).pop_front();
    ASSERT_EQ("PM10", get<1>(qualite).front().first);
    EXPECT_FLOAT_EQ(3.276998,get<1>(qualite).front().second);
    EXPECT_FLOAT_EQ(90, get<2>(qualite));
}
} // namespace
