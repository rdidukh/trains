#include "RdTest.h"

#include "Rail.h"

TEST(Rail, connectRR)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(3, 4, 7, 7);

    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    ASSERT_NULL(railA.next(0));
    ASSERT_NOTNULL(railA.next(1));
    ASSERT_NOTNULL(railB.next(0));
    ASSERT_NULL(railB.next(1));
    ASSERT_EQ(railA.next(1), &railB);
    ASSERT_EQ(railB.next(0), &railA);
}

TEST(Rail, connectNeg)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(4, 3, 7, 7);

    bool ret = Rail::connect(&railA, &railB);
    ASSERT_FALSE(ret);

    ASSERT_NULL(railA.next(0));
    ASSERT_NULL(railA.next(1));
    ASSERT_NULL(railB.next(0));
    ASSERT_NULL(railB.next(1));
}

TEST(Rail, connectFloat)
{
    float e = 0.2*Point::error;
    Rail railA(0, 0, 3+e, 4-e);
    Rail railB(3-e, 4+e, 7, 7);

    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    ASSERT_NULL(railA.next(0));
    ASSERT_NOTNULL(railA.next(1));
    ASSERT_NOTNULL(railB.next(0));
    ASSERT_NULL(railB.next(1));
}

TEST(Rail, connectFloatNeg)
{
    float e = 0.5*Point::error;
    Rail railA(0, 0, 3+e, 4-e);
    Rail railB(3-e, 4+e, 7, 7);

    bool ret = Rail::connect(&railA, &railB);
    ASSERT_FALSE(ret);

    ASSERT_NULL(railA.next(0));
    ASSERT_NULL(railA.next(1));
    ASSERT_NULL(railB.next(0));
    ASSERT_NULL(railB.next(1));
}

/*
 * TODO:
 * - Middle rail test
 */
