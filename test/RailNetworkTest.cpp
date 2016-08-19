#include "RdTest.h"

#include "Rail.h"

TEST(RailNetwork, addRailOne)
{
    RailNetwork railNet;
    Rail * rail;
    rail = railNet.addRail(785, -126, 977, 15);
    ASSERT_NOTNULL(rail);
    ASSERT_NULL(rail->next(0));
    ASSERT_NULL(rail->next(1));
    ASSERT_EQ(rail->point[0].x, 785);
    ASSERT_EQ(rail->point[0].y, -126);
    ASSERT_EQ(rail->point[1].x, 977);
    ASSERT_EQ(rail->point[1].y, 15);
}

TEST(RailNetwork, addRailTwoSep)
{
    RailNetwork railNet;
    Rail * railA;
    Rail * railB;

    railA = railNet.addRail(115, 100, 200, 107);
    ASSERT_NOTNULL(railA);
    ASSERT_NULL(railA->next(0));
    ASSERT_NULL(railA->next(1));

    railB = railNet.addRail(1, 2, 30, 40);
    ASSERT_NOTNULL(railB);
    ASSERT_NULL(railB->next(0));
    ASSERT_NULL(railB->next(1));

    ASSERT_NE(railA, railB);
}

TEST(RailNetwork, addRailTwoConn)
{
    RailNetwork railNet;
    Rail * railA;
    Rail * railB;

    railA = railNet.addRail(7, 10, 115, 25);
    ASSERT_NOTNULL(railA);
    ASSERT_NULL(railA->next(0));
    ASSERT_NULL(railA->next(1));

    railB = railNet.addRail(1000, 1000, 115, 25);
    ASSERT_NOTNULL(railB);
    ASSERT_NULL(railB->next(0));
    ASSERT_NOTNULL(railB->next(1));
    ASSERT_NULL(railA->next(0));
    ASSERT_NOTNULL(railA->next(1));

    ASSERT_NE(railA, railB);
}

TEST(RailNetwork, addRailThreeMiddle)
{
    RailNetwork railNet;
    Rail * rail;
    Rail * rails[3];

    rail = railNet.addRail(0, 0, 1, 1);
    ASSERT_NOTNULL(rail);
    ASSERT_NULL(rail->next(0));
    ASSERT_NULL(rail->next(1));

    rails[0] = rail;

    rail = railNet.addRail(2, 2, 3, 3);
    ASSERT_NOTNULL(rail);
    ASSERT_NULL(rail->next(0));
    ASSERT_NULL(rail->next(1));

    rails[1] = rail;

    rail = railNet.addRail(2, 2, 1, 1);

    ASSERT_NOTNULL(rail);

    rails[2] = rail;

    ASSERT_EQ(rails[0]->next(1), rails[2]);
    ASSERT_NULL(rails[0]->next(0));
    ASSERT_EQ(rails[1]->next(0), rails[2]);
    ASSERT_NULL(rails[1]->next(1));

    ASSERT_EQ(rails[2]->next(1), rails[0]);
    ASSERT_EQ(rails[2]->next(0), rails[1]);
}

