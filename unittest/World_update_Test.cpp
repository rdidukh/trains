#include "RdTest.h"

#include "World.h"
#include "Train.h"

TEST(World_update, TrainMove_Simple)
{
    World world;
    Rail * rail = world.addRail(0, 0, 5, 5);

    Train train;
    train.head.rail = rail;
    train.head.offset = 3;
    train.length = 2;
    train.speed = 1;

    world.addTrain(train);

    world.update(1);
    ASSERT_EQ(train.head.offset, 4);
    ASSERT_EQ(train.head.rail, rail);
    ASSERT_EQ(train.speed, 1);
    ASSERT_EQ(train.length, 2);

    world.update(1);
    ASSERT_EQ(train.head.offset, 5);
    ASSERT_EQ(train.head.rail, rail);
    ASSERT_EQ(train.speed, 1);
    ASSERT_EQ(train.length, 2);

    world.update(0.5);
    ASSERT_EQ(train.head.offset, 5.5);
    ASSERT_EQ(train.head.rail, rail);
    ASSERT_EQ(train.speed, 1);
    ASSERT_EQ(train.length, 2);

    world.update(1.5);
    ASSERT_EQ(train.head.offset, 7);
    ASSERT_EQ(train.head.rail, rail);
    ASSERT_EQ(train.speed, 1);
    ASSERT_EQ(train.length, 2);
}

TEST(World_update, TrainMove_FF)
{
    World world;

    Rail * railA = world.addRail(0, 0,  6,  8);
    Rail * railB = world.addRail(6, 8, 14, 14);
    Train train;

    float speed = 3;
    float offset = 9;
    float length = 3;
    float dTime = 0.1f;

    train.head.rail = railA;
    train.head.offset = offset;
    train.speed = speed;
    train.length = length;

    world.addTrain(train);

    std::vector<Rail*> expRails;
    std::vector<float> expOffset;

    for(int i = 0; i < 3; i++)
    {
        expRails.push_back(railA);
        expOffset.push_back(offset + dTime*speed*(i+1));
    }

    for(int i = 0; i < 15; i++)
    {
        expRails.push_back(railB);
        expOffset.push_back(0.2 + dTime*speed*(i));
    }

    int n = expOffset.size();
    for(int i = 0; i < n; i++)
    {
        world.update(dTime);
        ASSERT_NOTNULL(train.head.rail);
        ASSERT_EQ(train.head.rail, expRails[i]) << "i = " << i << "\n";
        ASSERT_EQ(train.speed, speed);
        ASSERT_EQ(train.length, length);
        ASSERT_NEAR(train.head.offset, expOffset[i], Point::error()) << "i = " << i << "\n";
    }
}


TEST(World_update, TrainMove_FB)
{
    World world;

    Rail * railA = world.addRail( 0,  0, 6, 8);
    Rail * railB = world.addRail(14, 14, 6, 8);
    Train train;

    float speed = 3;
    float offset = 9;
    float length = 3;
    float dTime = 0.1f;

    train.head.rail = railA;
    train.head.offset = offset;
    train.speed = speed;
    train.length = length;

    world.addTrain(train);

    std::vector<Rail*> expRails;
    std::vector<float> expOffset;
    std::vector<float> expSpeed;
    std::vector<float> expLength;

    for(int i = 0; i < 3; i++)
    {
        expRails.push_back(railA);
        expOffset.push_back(offset + dTime*speed*(i+1));
        expSpeed.push_back(speed);
        expLength.push_back(length);
    }

    for(int i = 0; i < 15; i++)
    {
        expRails.push_back(railB);
        expOffset.push_back(railB->length - 0.2 - dTime*speed*(i));
        expSpeed.push_back(-speed);
        expLength.push_back(-length);
    }

    int n = expOffset.size();
    for(int i = 0; i < n; i++)
    {
        world.update(dTime);
        ASSERT_NOTNULL(train.head.rail);
        ASSERT_EQ(train.head.rail, expRails[i]) << "i = " << i << "\n";
        ASSERT_EQ(train.speed, expSpeed[i]) << "i = " << i << "\n";;
        ASSERT_EQ(train.length, expLength[i]) << "i = " << i << "\n";;
        ASSERT_NEAR(train.head.offset, expOffset[i], Point::error()) << "i = " << i << "\n";
    }
}


TEST(World_update, TrainMove_BF)
{
    World world;

    Rail * railA = world.addRail( 6,  8,  0,  0);
    Rail * railB = world.addRail( 6,  8, 14, 14);
    Train train;

    float speed = 3;
    float offset = 1;
    float length = 3;
    float dTime = 0.1f;

    train.head.rail = railA;
    train.head.offset = offset;
    train.speed = -speed;
    train.length = -length;

    world.addTrain(train);

    std::vector<Rail*> expRails;
    std::vector<float> expOffset;
    std::vector<float> expSpeed;
    std::vector<float> expLength;

    for(int i = 0; i < 3; i++)
    {
        expRails.push_back(railA);
        expOffset.push_back(offset - dTime*speed*(i+1));
        expSpeed.push_back(-speed);
        expLength.push_back(-length);
    }

    for(int i = 0; i < 15; i++)
    {
        expRails.push_back(railB);
        expOffset.push_back(0.2 + dTime*speed*(i));
        expSpeed.push_back(speed);
        expLength.push_back(length);
    }

    int n = expOffset.size();
    for(int i = 0; i < n; i++)
    {
        world.update(dTime);
        ASSERT_NOTNULL(train.head.rail);
        ASSERT_EQ(train.head.rail, expRails[i]) << "i = " << i << "\n";
        ASSERT_EQ(train.speed, expSpeed[i]) << "i = " << i << "\n";;
        ASSERT_EQ(train.length, expLength[i]) << "i = " << i << "\n";;
        ASSERT_NEAR(train.head.offset, expOffset[i], Point::error()) << "i = " << i << "\n";
    }
}


TEST(World_update, TrainMove_BB)
{
    World world;

    Rail * railA = world.addRail( 6,  8,  0,  0);
    Rail * railB = world.addRail( 14, 14, 6, 8);
    Train train;

    float speed = 3;
    float offset = 1;
    float length = 3;
    float dTime = 0.1f;

    train.head.rail = railA;
    train.head.offset = offset;
    train.speed = -speed;
    train.length = -length;

    world.addTrain(train);

    std::vector<Rail*> expRails;
    std::vector<float> expOffset;
    std::vector<float> expSpeed;
    std::vector<float> expLength;

    for(int i = 0; i < 3; i++)
    {
        expRails.push_back(railA);
        expOffset.push_back(offset - dTime*speed*(i+1));
        expSpeed.push_back(-speed);
        expLength.push_back(-length);
    }

    for(int i = 0; i < 15; i++)
    {
        expRails.push_back(railB);
        expOffset.push_back(railB->length - 0.2 - dTime*speed*(i));
        expSpeed.push_back(-speed);
        expLength.push_back(-length);
    }

    int n = expOffset.size();
    for(int i = 0; i < n; i++)
    {
        world.update(dTime);
        ASSERT_NOTNULL(train.head.rail);
        ASSERT_EQ(train.head.rail, expRails[i]) << "i = " << i << "\n";
        ASSERT_EQ(train.speed, expSpeed[i]) << "i = " << i << "\n";;
        ASSERT_EQ(train.length, expLength[i]) << "i = " << i << "\n";;
        ASSERT_NEAR(train.head.offset, expOffset[i], Point::error()) << "i = " << i << "\n";
    }
}
