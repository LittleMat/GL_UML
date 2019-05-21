#include "gtest/gtest.h"
#include "Point.h"

namespace {
    TEST(PointUnitTest, Constructor) {
        Point p0(123, 49);
        EXPECT_FLOAT_EQ(p0.getLongitude(), 123);
        EXPECT_FLOAT_EQ(p0.getLatitude(), 49);

        Point p1(-54, -16);
        EXPECT_FLOAT_EQ(p1.getLongitude(), -54);
        EXPECT_FLOAT_EQ(p1.getLatitude(), -16);
    }
    TEST(PointUnitTest, Constructor_IllegalArgument) {
        EXPECT_ANY_THROW(Point p(-181, 0));
        EXPECT_ANY_THROW(Point p(181, 0));
        EXPECT_ANY_THROW(Point p(0, 91));
        EXPECT_ANY_THROW(Point p(0, -91));
    }
    TEST(PointUnitTest, Distance_IllegalArgument) {
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
    }

    /* If on windows
    int main() {
        return ::RUN_ALL_TESTS();
    }
    */
}
