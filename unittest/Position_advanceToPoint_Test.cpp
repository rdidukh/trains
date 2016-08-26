#include "RdTest.h"

#include "Rail.h"

TEST(Position, advanceToPoint_Simple)
{
    Rail rail(0, 0, 3, 4);
    Position pos(&rail, 1);

    float left = pos.advanceToPoint(2);

    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &rail);
    ASSERT_EQ(pos.offset, 3);
    ASSERT_EQ(left, 0);
}

TEST(Position, advanceToPoint_Null)
{
    Position pos(nullptr, 1);

    float left = pos.advanceToPoint(100);

    ASSERT_NULL(pos.rail);
    ASSERT_EQ(left, 0);
}

TEST(Position, advanceToPoint_Overrun)
{
    Rail rail(0, 0, 3, 4);
    Position pos(&rail, 2);

    float left = pos.advanceToPoint(4);

    ASSERT_NULL(pos.rail);
    ASSERT_EQ(left, 0);
}

TEST(Position, advanceToPoint_RR)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(3, 4, 7, 7);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railA, 2);

    float left = pos.advanceToPoint(6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    Point point = pos.point();
    ASSERT_EQ(point.x, 3);
    ASSERT_EQ(point.y, 4);

    ASSERT_EQ(left, 3);

    left = pos.advanceToPoint(left);

    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 3);
    ASSERT_EQ(left, 0);
}

TEST(Position, advanceToPoint_LL)
{
    Rail railA(3, 4, 0, 0);
    Rail railB(7, 7, 3, 4);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railA, 2);

    float left = pos.advanceToPoint(-6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    Point point = pos.point();
    ASSERT_EQ(point.x, 3);
    ASSERT_EQ(point.y, 4);

    ASSERT_EQ(left, -4);

    left = pos.advanceToPoint(left);

    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 1);
    ASSERT_EQ(left, 0);
}

TEST(Position, advanceToPoint_LR)
{
    Rail railA(3, 4, 0, 0);
    Rail railB(3, 4, 7, 7);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railA, 2);

    float left = pos.advanceToPoint(-6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    Point point = pos.point();
    ASSERT_EQ(point.x, 3);
    ASSERT_EQ(point.y, 4);

    ASSERT_EQ(left, 4);

    left = pos.advanceToPoint(left);

    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 4);
    ASSERT_EQ(left, 0);
}

TEST(Position, advanceToPoint_RL)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(7, 7, 3, 4);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railA, 2);

    float left = pos.advanceToPoint(6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    Point point = pos.point();
    ASSERT_EQ(point.x, 3);
    ASSERT_EQ(point.y, 4);

    ASSERT_EQ(left, -3);

    left = pos.advanceToPoint(left);

    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 2);
    ASSERT_EQ(left, 0);
}

TEST(Position, advanceToPoint_Endpoint)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(3, 4, 7, 7);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railA, 2);

    float left = pos.advanceToPoint(3);

    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 0);
    ASSERT_EQ(left, 0);

}
