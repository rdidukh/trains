#include "RdTest.h"

#include "Rail.h"

TEST(RailNetwork, addRail)
{
    RailNetwork railNet;

    Rail * rail = railNet.addRail(0, 0, 1, 1);
    ASSERT_NOTNULL(rail);
    ASSERT_NULL(rail->prev);
    ASSERT_NULL(rail->next);
    ASSERT_EQ(rail->start.x, 0);
    ASSERT_EQ(rail->start.y, 0);
    ASSERT_EQ(rail->end.x, 1);
    ASSERT_EQ(rail->end.y, 1);

    /*
        TODO
    */
}

