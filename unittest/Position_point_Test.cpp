#include "RdTest.h"

#include "Rail.h"

TEST(Position, pointZero)
{
    Rail rail(3, 7, 7, 10);
    Position pos(&rail, 0);
    Point point = pos.point();

    ASSERT_NEAR(point.x, 3, Point::error());
    ASSERT_NEAR(point.y, 7, Point::error());
}

TEST(Position, pointLength)
{
    Rail rail(3, 7, 7, 10);
    Position pos(&rail, 5);
    Point point = pos.point();

    ASSERT_NEAR(point.x,  7, Point::error());
    ASSERT_NEAR(point.y, 10, Point::error());
}

TEST(Position, pointX)
{
    Rail rail(-5, 0, 7, 0);
    Position pos(&rail, 6.34);
    Point point = pos.point();
    ASSERT_NEAR(point.x, 1.34, Point::error());
    ASSERT_NEAR(point.y, 0, Point::error());
}

TEST(Position, pointY)
{
    Rail rail(0, 1.54, 0, 1.47);
    Position pos(&rail, 0.03);
    Point point = pos.point();
    ASSERT_NEAR(point.x,   0, Point::error());
    ASSERT_NEAR(point.y, 1.51, Point::error());
}

TEST(Position, pointXY)
{
    Rail rail(0, 0, 7, 7);
    Position pos(&rail, 2*std::sqrt(2));
    Point point = pos.point();
    ASSERT_NEAR(point.x, 2.0, Point::error());
    ASSERT_NEAR(point.y, 2.0, Point::error());
}
