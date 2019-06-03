#include <limits>
using namespace std;
#include "gtest/gtest.h"
#include "Point.h"
#include "Capteur.h"
#include "Territoire.h"
#include "FileReader.h"
#include "Service.h"

namespace {
    TEST(PointUnitTest, Constructor) {
        Point p0(123, 49);
        EXPECT_FLOAT_EQ(p0.getLongitude(), 123);
        EXPECT_FLOAT_EQ(p0.getLatitude(), 49);

        Point p1(-54, -16);
        EXPECT_FLOAT_EQ(p1.getLongitude(), -54);
        EXPECT_FLOAT_EQ(p1.getLatitude(), -16);
    }
    TEST(PointUnitTest, ConstructorIllegalArgument) {
        EXPECT_ANY_THROW(Point p(-181, 0));
        EXPECT_ANY_THROW(Point p(181, 0));
        EXPECT_ANY_THROW(Point p(0, 91));
        EXPECT_ANY_THROW(Point p(0, -91));
    }
    TEST(PointUnitTest, DistanceIllegalArgument) {
        Point p(0, 0);
        EXPECT_ANY_THROW(p.distance(nullptr));
    }
    TEST(PointUnitTest, Distance_ZERO) {
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
    TEST(PointUnitTest, Distance) {
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

    TEST(CapteurUnitTest, ConstructorIllegalArgument) {
        EXPECT_ANY_THROW(Capteur c0("", new Point(0, 0), ""));
        EXPECT_ANY_THROW(Capteur c1("c1", nullptr, ""));
    }
    TEST(CapteurUnitTest, Constructor) {
        Capteur c0("c0", new Point(10, -10), "Description");
        EXPECT_EQ(c0.getSensorID(), "c0");
        EXPECT_FLOAT_EQ(c0.getPosition()->getLatitude(), -10);
        EXPECT_FLOAT_EQ(c0.getPosition()->getLongitude(), 10);
        EXPECT_EQ(c0.getDescription(), "Description");
    }

    TEST(TerritoireUnitTest, ConstructorIllegalArgument) {
        EXPECT_ANY_THROW(Territoire t0(new Point(0, 0), -10));
        EXPECT_ANY_THROW(Territoire t1(nullptr, 10));
    }
    TEST(TerritoireUnitTest, Constructor) {
        Territoire t0(new Point(0.14, 0.59), 125);
        EXPECT_FLOAT_EQ(t0.getRayon(), 125);
        EXPECT_FLOAT_EQ(t0.getCentre()->getLongitude(), 0.14);
        EXPECT_FLOAT_EQ(t0.getCentre()->getLatitude(), 0.59);
    }
    TEST(TerritoireUnitTest, ContientIllegalArgument) {
        Territoire t0(new Point(0, 0), 10);
        EXPECT_ANY_THROW(t0.contient(nullptr));
    }
    TEST(TerritoireUnitTest, Contient) {
        Territoire t0(new Point(0, 0), 10);
        Point p0(0, 0);
        EXPECT_TRUE(t0.contient(&p0));
        Point p1(0, 90);
        EXPECT_FALSE(t0.contient(&p1));
    }

    TEST(AttributUnitTest, ConstructorIllegalArgument) {
        EXPECT_ANY_THROW(Attribut("", "unit", "description"));
        EXPECT_ANY_THROW(Attribut("id", "", "description"));
    }
    TEST(AttributUnitTest, Constructor) {
        Attribut attribut("id", "unit", "description");
        EXPECT_EQ(attribut.getAttributID(), "id");
        EXPECT_EQ(attribut.getUnit(), "unit");
        EXPECT_EQ(attribut.getDescription(), "description");
    }

    TEST(MesureUnitTest, ConstructorIllegalArgument) {
        time_t now = time(NULL);
        time_t future = now + 86400;
        struct tm *now_t = localtime(&now);
        struct tm *future_t = localtime(&future);
        struct tm empty;
        Attribut attribut("id", "unit", "description");
        Capteur capteur("sensorId", new Point(0, 0), "");
        EXPECT_ANY_THROW(Mesure(&empty, &attribut, 0, "sensorId", &capteur));
        EXPECT_ANY_THROW(Mesure(now_t, nullptr, 0, "sensorId", &capteur));
        EXPECT_ANY_THROW(Mesure(now_t, &attribut, -100, "sensorId", &capteur));
        EXPECT_ANY_THROW(Mesure(now_t, &attribut, 0, "", &capteur));
        EXPECT_ANY_THROW(Mesure(now_t, &attribut, 0, "meaningless", &capteur));
        EXPECT_ANY_THROW(Mesure(now_t, &attribut, 0, "sensorId", nullptr));
        EXPECT_ANY_THROW(Mesure(future_t, &attribut, 0, "sensorId", &capteur));
    }

    TEST(FileReaderUnitTest, ConstructorIllegalArgument) {
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
    TEST(FileReaderUnitTest, ConstructorIllegalFile) {
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
        EXPECT_ANY_THROW(FileReader reader("resources/BrokenSensor.csv", "resources/AttributeType.csv", listS));
        EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "resources/BrokenAttributeType.csv", listS));
        listS.clear();
        listS.push_back("resources/BrokenData.csv");
        EXPECT_ANY_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));

    }
    TEST(FileReaderUnitTest, Constructor) {
        list<string> listS;
        listS.push_back("resources/Data10.csv");
        EXPECT_NO_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
    }
    TEST(FileReaderUnitTest, LireAttributs) {
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
    TEST(FileReaderUnitTest, LireCapteur) {
        list<string> listS;
        listS.push_back("resources/Data10.csv");
        FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
        paramFiltrage passAll;
        unordered_map<string, Capteur *> capteurs;

        EXPECT_ANY_THROW(capteurs = reader.lireCapteurs(passAll, NULL));

        capteurs = reader.lireCapteurs(passAll, Service::filtrageCapteur);
        EXPECT_EQ(10, capteurs.size());
        Capteur *capteur = nullptr;
        ASSERT_NO_THROW(capteur = capteurs.at("Sensor0"));
        capteur = capteurs.at("Sensor0");
        EXPECT_FLOAT_EQ(-34.7692487876719, capteur->getPosition()->getLongitude());
        EXPECT_FLOAT_EQ(-8.15758888291083, capteur->getPosition()->getLatitude());
        EXPECT_TRUE(capteur->getDescription().empty());
        ASSERT_NO_THROW(capteur = capteurs.at("Sensor9"));
        capteur = capteurs.at("Sensor9");
        EXPECT_FLOAT_EQ(36.2756694672982, capteur->getPosition()->getLongitude());
        EXPECT_FLOAT_EQ(1.33005024461543, capteur->getPosition()->getLatitude());
        EXPECT_TRUE(capteur->getDescription().empty());
    }
    TEST(FileReaderUnitTest, ProchaineMesure) {
        list<string> listS;
        listS.push_back("resources/Data10.csv");
        FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
        paramFiltrage passAll;
        Mesure *mesure = nullptr;

        EXPECT_ANY_THROW(mesure = reader.prochaineMesure(passAll, NULL));

        mesure = reader.prochaineMesure(passAll, Service::filtrageMesure);
        EXPECT_EQ(2017, mesure->getTimestamp()->tm_year);
        EXPECT_EQ("Sensor0", mesure->getCapteur()->getSensorID());
        EXPECT_FLOAT_EQ(17.8902017543936, mesure->getValue());

        for (int i = 0; i < 9; i++)
        {
            EXPECT_TRUE(reader.prochaineMesure(passAll, Service::filtrageMesure) != nullptr);
        }
        mesure = reader.prochaineMesure(passAll, Service::filtrageMesure);
        EXPECT_EQ(2017, mesure->getTimestamp()->tm_year);
        EXPECT_EQ("Sensor0", mesure->getCapteur()->getSensorID());
        EXPECT_FLOAT_EQ(17.8902017543936, mesure->getValue());
    }

    TEST(ServiceUnitTest, Constructor) {
        EXPECT_ANY_THROW(Service service(nullptr));
    }
    TEST(ServiceUnitTest, FiltrageMesure) {
        time_t now = time(NULL);
        time_t yesterday = now - 86400;
        time_t tomorrow = now + 86400;
        struct tm empty_tm;
        struct tm now_tm = *localtime(&now);
        struct tm yesterday_tm = *localtime(&yesterday);
        struct tm tomorrow_tm = *localtime(&tomorrow);
        Attribut attribut("id", "unit", "description");
        Capteur capteur("sensorId", new Point(0, 0), "description");
        Mesure mesureNow(&now_tm, &attribut, 10, "sensorId", &capteur);
        Mesure mesureYesterday(&yesterday_tm, &attribut, 10, "sensorId", &capteur);
        Mesure mesureTomorrow(&tomorrow_tm, &attribut, 10, "sensorId", &capteur);

        EXPECT_TRUE(Service::filtrageMesure(mesureNow, yesterday_tm, tomorrow_tm));
        EXPECT_TRUE(Service::filtrageMesure(mesureYesterday, empty_tm, tomorrow_tm));
        EXPECT_TRUE(Service::filtrageMesure(mesureTomorrow, now_tm, empty_tm));
        EXPECT_TRUE(Service::filtrageMesure(mesureNow, empty_tm, empty_tm));

        EXPECT_FALSE(Service::filtrageMesure(mesureNow, tomorrow_tm, empty_tm));
        EXPECT_FALSE(Service::filtrageMesure(mesureNow, empty_tm, yesterday_tm));
    }
    TEST(ServiceUnitTest, FiltrageCapteur) {
        Capteur capteurOrigin("sensorId", new Point(0, 0), "description");
        Capteur capteurParis("sensorId", new Point(2.21, 48.51), "descrption");

        Territoire empty(new Point(0, 0), 0);
        Territoire point(new Point(2.21, 48.51), 0);
        Territoire circle(new Point(2, 48), 100);

        EXPECT_TRUE(Service::filtrageCapteur(capteurOrigin, empty, "sensorId"));
        EXPECT_TRUE(Service::filtrageCapteur(capteurParis, empty, "sensorId"));
        EXPECT_TRUE(Service::filtrageCapteur(capteurParis, point, "sensorId"));
        EXPECT_TRUE(Service::filtrageCapteur(capteurParis, circle, "sensorId"));

        EXPECT_FALSE(Service::filtrageCapteur(capteurOrigin, point, "sensorId"));
        EXPECT_FALSE(Service::filtrageCapteur(capteurOrigin, circle, "sensorId"));
        EXPECT_FALSE(Service::filtrageCapteur(capteurParis, point, "meaningless"));
        EXPECT_FALSE(Service::filtrageCapteur(capteurParis, circle, "meaningless"));
    }
    TEST(ServiceUnitTest, DateNull){
        struct tm empty;
        time_t now = time(NULL);
        struct tm *today = localtime(&now);
        EXPECT_TRUE(Service::dateNull(empty));
        EXPECT_FALSE(Service::dateNull(*today));
    }
    TEST(ServiceUnitTest, PlusOuMoins) {
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
    TEST(ServiceUnitTest, SurveillerComportementCapteur) {
        list<string> listS;
        listS.push_back("resources/ServiceTestData.csv");
        FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
        Service service(&reader);
        paramFiltrage passAll;
        EXPECT_TRUE(service.surveillerComportementCapteur("Sensor0", passAll));
        EXPECT_TRUE(service.surveillerComportementCapteur("Sensor1", passAll));
        EXPECT_FALSE(service.surveillerComportementCapteur("Sensor2", passAll));
        EXPECT_FALSE(service.surveillerComportementCapteur("Sensor3", passAll));
    }
    TEST(ServiceUnitTest, SurveillerComportementCapteurs) {
        list<string> listS;
        listS.push_back("resources/ServiceTestData.csv");
        FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
        Service service(&reader);
        paramFiltrage passAll;
        list<string> capteurs;
        capteurs.push_back("Sensor0");
        capteurs.push_back("Sensor1");
        capteurs.push_back("Sensor2");
        capteurs.push_back("Sensor3");
        capteurs.push_back("Sensor4");
        EXPECT_NO_THROW(service.surveillerComportementCapteurs(capteurs, passAll));
        list<Capteur>* listCapteur = service.surveillerComportementCapteurs(capteurs, passAll);
        EXPECT_TRUE(find_if(listCapteur->begin(), listCapteur->end(), [](Capteur capteur)-> bool {return capteur.getSensorID() == "Sensor0";}) == listCapteur->end());
        EXPECT_TRUE(find_if(listCapteur->begin(), listCapteur->end(), [](Capteur capteur)-> bool {return capteur.getSensorID() == "Sensor1";}) == listCapteur->end());
        EXPECT_TRUE(find_if(listCapteur->begin(), listCapteur->end(), [](Capteur capteur)-> bool {return capteur.getSensorID() == "Sensor2";}) != listCapteur->end());
        EXPECT_TRUE(find_if(listCapteur->begin(), listCapteur->end(), [](Capteur capteur)-> bool {return capteur.getSensorID() == "Sensor3";}) != listCapteur->end());
    }
    TEST(ServiceUnitTest, ObtenirCapteursSimilaires) {
        list<string> listS;
        listS.push_back("resources/ServiceTestData.csv");
        FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
        Service service(&reader);
        struct tm time;
        time.tm_year = 117;
        time.tm_yday = 1;
        time.tm_mon = 0;
        list<pair<Capteur, Capteur>> * similar = service.obtenirCapteursSimilaires(time, 2);
        ASSERT_TRUE(similar->size() == 2);
        if (similar->front().first.getSensorID() == "Sensor0") {
            EXPECT_EQ("Sensor1", similar->front().second.getSensorID());
        }
        if (similar->front().first.getSensorID() == "Sensor1") {
            EXPECT_EQ("Sensor0", similar->front().second.getSensorID());
        }
        similar->pop_front();
        if (similar->front().first.getSensorID() == "Sensor0") {
            EXPECT_EQ("Sensor1", similar->front().second.getSensorID());
        }
        if (similar->front().first.getSensorID() == "Sensor1") {
            EXPECT_EQ("Sensor0", similar->front().second.getSensorID());
        }
    }
    TEST(ServiceUnitTest, CalculerQualite) {
        list<string> listS;
        listS.push_back("resources/ServiceTestData.csv");
        FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS);
        Service service(&reader);
    }
} // namespace
