#include "RdTest.h"

#include "Rail.h"
#include "World.h"

TEST(World, addRailPoint)
{
    World world;
    Rail * rail;
    rail = world.addRail(9, 100, 9, 100);
    ASSERT_NULL(rail);
}

TEST(World, addRailOne)
{
    World world;
    Rail * rail;
    rail = world.addRail(785, -126, 977, 15);
    ASSERT_NOTNULL(rail);
    ASSERT_NULL(rail->next(0));
    ASSERT_NULL(rail->next(1));
    ASSERT_EQ(rail->point[0].x, 785);
    ASSERT_EQ(rail->point[0].y, -126);
    ASSERT_EQ(rail->point[1].x, 977);
    ASSERT_EQ(rail->point[1].y, 15);
}

TEST(World, addRailTwoSep)
{
    World world;
    Rail * railA;
    Rail * railB;

    railA = world.addRail(115, 100, 200, 107);
    ASSERT_NOTNULL(railA);
    ASSERT_NULL(railA->next(0));
    ASSERT_NULL(railA->next(1));

    railB = world.addRail(1, 2, 30, 40);
    ASSERT_NOTNULL(railB);
    ASSERT_NE(railA, railB);
    ASSERT_NULL(railB->next(0));
    ASSERT_NULL(railB->next(1));
}

TEST(World, addRailTwoConn)
{
    World world;
    Rail * railA;
    Rail * railB;

    railA = world.addRail(3, 1, 52, 14);
    ASSERT_NOTNULL(railA);
    ASSERT_NULL(railA->next(0));
    ASSERT_NULL(railA->next(1));

    railB = world.addRail(52, 14, 115, 25);
    ASSERT_NOTNULL(railB);
    ASSERT_NE(railA, railB);

    ASSERT_NULL(railB->next(1));
    ASSERT_NOTNULL(railB->next(0));
    ASSERT_EQ(railB->next(0), railA);
    ASSERT_NULL(railA->next(0));
    ASSERT_NOTNULL(railA->next(1));
    ASSERT_EQ(railA->next(1), railB);
}

TEST(World, addRailTwoConnRev)
{
    World world;
    Rail * railA;
    Rail * railB;

    railA = world.addRail(7, 10, 115, 25);
    ASSERT_NOTNULL(railA);
    ASSERT_NULL(railA->next(0));
    ASSERT_NULL(railA->next(1));

    railB = world.addRail(1000, 1000, 115, 25);
    ASSERT_NOTNULL(railB);
    ASSERT_NE(railA, railB);

    ASSERT_NULL(railB->next(0));
    ASSERT_NOTNULL(railB->next(1));
    ASSERT_EQ(railB->next(1), railA);
    ASSERT_NULL(railA->next(0));
    ASSERT_NOTNULL(railA->next(1));
    ASSERT_EQ(railA->next(1), railB);
}

TEST(World, addRailThreeMiddle)
{
    World world;
    Rail * rail;
    Rail * rails[3];

    rail = world.addRail(0, 0, 1, 1);
    ASSERT_NOTNULL(rail);
    ASSERT_NULL(rail->next(0));
    ASSERT_NULL(rail->next(1));

    rails[0] = rail;

    rail = world.addRail(2, 2, 3, 3);
    ASSERT_NOTNULL(rail);
    ASSERT_NULL(rail->next(0));
    ASSERT_NULL(rail->next(1));

    rails[1] = rail;

    rail = world.addRail(2, 2, 1, 1);

    ASSERT_NOTNULL(rail);

    rails[2] = rail;

    ASSERT_NOTNULL(rails[0]->next(1));
    ASSERT_EQ(rails[0]->next(1), rails[2]);
    ASSERT_NULL(rails[0]->next(0));
    ASSERT_NOTNULL(rails[1]->next(0));
    ASSERT_EQ(rails[1]->next(0), rails[2]);
    ASSERT_NULL(rails[1]->next(1));

    ASSERT_NOTNULL(rails[2]->next(0));
    ASSERT_NOTNULL(rails[2]->next(1));
    ASSERT_EQ(rails[2]->next(0), rails[1]);
    ASSERT_EQ(rails[2]->next(1), rails[0]);
}
