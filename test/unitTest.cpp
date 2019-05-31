using namespace std;
#include "gtest/gtest.h"
#include "Point.h"
#include "Capteur.h"
#include "Territoire.h"
#include "FileReader.h"

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
        EXPECT_ANY_THROW(Territoire t1(new Point(0, 0), 0));
        EXPECT_ANY_THROW(Territoire t2(nullptr, 10));
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
        struct tm* now_t = localtime(&now);
        struct tm* future_t = localtime(&future);
        struct tm empty;
        Attribut attribut("id", "unit", "description");
        Capteur capteur("sensorId", new Point(0, 0), "");
        EXPECT_ANY_THROW(Mesure(empty, &attribut, 0, "sensorId", &capteur));
        EXPECT_ANY_THROW(Mesure(*now_t, nullptr, 0, "sensorId", &capteur));
        EXPECT_ANY_THROW(Mesure(*now_t, &attribut, -100, "sensorId", &capteur));
        EXPECT_ANY_THROW(Mesure(*now_t, &attribut, 0, "", &capteur));
        EXPECT_ANY_THROW(Mesure(*now_t, &attribut, 0, "meaningless", &capteur));
        EXPECT_ANY_THROW(Mesure(*now_t, &attribut, 0, "sensorId", nullptr));
        EXPECT_ANY_THROW(Mesure(*future_t, &attribut, 0, "sensorId", &capteur));
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
        EXPECT_NO_THROW(FileReader reader("resources/Sensor10.csv", "resources/AttributeType.csv", listS));
    }
}
