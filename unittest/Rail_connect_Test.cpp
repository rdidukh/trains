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
