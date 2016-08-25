#include "RdTest.h"

#include "Rail.h"

TEST(Position, advanceSimple)
{
    Rail rail(115, 97, 1204, 858);
    Position pos(&rail, 97);

    pos.advance(103);

    ASSERT_EQ(pos.rail, &rail);
    ASSERT_EQ(pos.offset, 200);

    pos.advance(-92);

    ASSERT_EQ(pos.offset, 108);
}

TEST(Position, advanceNull)
{
    Position pos(nullptr, 97);

    pos.advance(103);
    ASSERT_NULL(pos.rail);
    pos.advance(-92);
    ASSERT_NULL(pos.rail);
}

TEST(Position, advanceOverrun)
{
    Rail rail(0, 0, 3, 4);
    Position pos(&rail, 3);

    pos.advance(3);
    ASSERT_NULL(pos.rail);

    pos = {&rail, 3};

    pos.advance(-4);
    ASSERT_NULL(pos.rail);
}

/*
 *  ---|---->x---|---->
 *      -------->
 */
TEST(Position, advanceRRF)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(3, 4, 7, 7);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railA, 2);

    pos.advance(6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 3);
}

/*
 *  ---|---->x---|---->
 *      <--------
 */
TEST(Position, advanceRRB)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(3, 4, 7, 7);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railB, 2);

    pos.advance(-6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railA);
    ASSERT_EQ(pos.offset, 1);
}

/*
 *  ---|---->x<---|----
 *      <---------
 */
TEST(Position, advanceRLB)
{
    Rail railA(0, 0, 3, 4);
    Rail railB(7, 7, 3, 4);
    bool ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);

    Position pos(&railB, 2);

    pos.advance(6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railA);
    ASSERT_EQ(pos.offset, 2);
}

/*
 *  <---|----x---|---->
 *       -------->
 */
TEST(Position, advanceLRF)
{
    Rail railA(3, 4, 0, 0);
    Rail railB(3, 4, 7, 7);
    Rail::connect(&railA, &railB);

    Position pos(&railA, 2);

    pos.advance(-6);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 4);
}

TEST(Position, advanceSquare)
{
    Rail railA( 0,  0,  6,  8);
    Rail railB( 6,  8, 14, 14);
    Rail railC( 8,  6, 14, 14);
    Rail railD( 0,  0,  8,  6);
    bool ret;
    ret = Rail::connect(&railA, &railB);
    ASSERT_TRUE(ret);
    ret = Rail::connect(&railC, &railB);
    ASSERT_TRUE(ret);
    ret = Rail::connect(&railC, &railD);
    ASSERT_TRUE(ret);
    ret = Rail::connect(&railA, &railD);
    ASSERT_TRUE(ret);

    Position pos(&railA, 4);
    pos.advance(40);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railA);
    ASSERT_EQ(pos.offset, 4);

    pos.advance(-9);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railD);
    ASSERT_EQ(pos.offset, 5);

    pos.advance(-42);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railD);
    ASSERT_EQ(pos.offset, 3);

    pos.advance(20);
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.rail, &railB);
    ASSERT_EQ(pos.offset, 7);
}

/*
TEST(Position, advanceFloat)
{
    Rail rail(0, 0, 7, 4);
    Position pos(&rail, 0);
    pos.advance(-0.5*Point::error());
    ASSERT_NOTNULL(pos.rail);
    ASSERT_EQ(pos.offset, 0);
}
*/

/*
 * TODO:
 *  - 3 rail test
 *  - advance to endpoint test
 */


