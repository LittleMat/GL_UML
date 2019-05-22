#include "gtest/gtest.h"
#include "Point.h"
#include "Capteur.h"
#include "Territoire.h"

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

	int main(int argc, char** argv) {
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
}
