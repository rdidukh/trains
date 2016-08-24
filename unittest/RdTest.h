#pragma once

#ifndef FILE_RDTEST_H
#define FILE_RDTEST_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

namespace rdns
{
    struct RdLittleTest
    {
        RdLittleTest(const std::string & className, const std::string & testName);
        virtual void run()=0;
        std::string name;
        bool ok;
    };

    class RdBigTest
    {
        std::vector<RdLittleTest *> littleTests;
        std::string name;
    public:
        RdBigTest(const std::string & className);
        void addLittleTest(RdLittleTest * littleTest);
        static int runAll();
        int run();
    };

    static struct RdBigTestsInit
    { 
        RdBigTestsInit();
        ~RdBigTestsInit();
    } rdBigTestsInit;
    
    struct VoidReturner
    {
        void operator=(std::ostream & os) {}
    };
    
    struct Is_True
    {
        static const char * str() { return  "TRUE";  }
        static const char * opp() { return "FALSE"; }

        template<class U>
        bool operator()(const U & u)
        {
            return u == true;
        }
    };

    struct Is_Null
    {
        static const char * str() { return "NULL";     }
        static const char * opp() { return "NOT NULL"; }

        template<class U>
        bool operator()(const U & u)
        {
            return u == nullptr;
        }
    };

    template<class T>
    struct NotU
    {
        static const char * str() { return T::opp(); }
        static const char * opp() { return T::str(); }
        template<class U>
        bool operator()(const U & u)
        {
            T t;
            return !t(u);
        }
    };

    struct Cmp_Eq
    {
        template<class U, class V>
        bool operator()(const U& u, const V& v)
        {
            return u == v;
        }
    };


    template<class T>
    struct NotB
    {
        template<class U, class V>
        bool operator()(const U& u, const V& v)
        {
            T t;
            return !t(u, v);
        }
    };

    template<typename U, typename V, typename Compare>
    bool expect_b_common(const U & actual, const V & expected, const char * actStr, const char * expStr, const char * file, unsigned line, Compare comp, const char * cmpName)
    {
        bool res = comp(actual, expected);

        if(!res)
        {
            std::string cmpNameStr = std::string("To be ") + cmpName + ": ";
            int width = cmpNameStr.length() < 10 ? 10 : cmpNameStr.length();
            std::cout << file << ":" << line << ": Failure" << '\n';
            std::cout << std::setw(width) << "Expected: " << actStr << '\n';
            std::cout << std::setw(width) << "Which is: " << actual << '\n';
            std::cout << std::setw(width) << cmpNameStr << expStr << '\n';
            std::cout << std::setw(width) << "Which is: " << expected << '\n';
            return false;
        }

        return true;
    }

    template<typename U, typename Pred>
    bool expect_u_common(const U & actual, const char * actStr, const char * file, unsigned line, Pred pred)
    {
        bool res = pred(actual);

        if(!res)
        {
            std::string predNameStr = std::string("To be: ");
            int width = predNameStr.length() < 10 ? 10 : predNameStr.length();
            std::cout << file << ":" << line << ": Failure" << '\n';
            std::cout << std::setw(width) << "Expected: " << actStr << '\n';
            std::cout << std::setw(width) << "Which is: " << Pred::opp() << '\n';
            std::cout << std::setw(width) << predNameStr << Pred::str() << '\n';
            return false;
        }

        return true;
    }

}

#define CALL_EXPECT_U_COMMON(actual, pred) \
(this->ok = rdns::expect_u_common(actual, #actual, __FILE__, __LINE__, pred))

#define CALL_EXPECT_B_COMMON(actual, expected, comp, cmpName) \
(this->ok = rdns::expect_b_common(actual, expected, #actual, #expected, __FILE__, __LINE__, comp, cmpName))

#define EXPECT_SUFFIX() || std::cout
#define ASSERT_SUFFIX() ; if(!this->ok) return VoidReturner() = std::cout

#define EXPECT_U_COMMON(actual, pred) \
CALL_EXPECT_U_COMMON(actual, pred) EXPECT_SUFFIX()

#define ASSERT_U_COMMON(actual, pred) \
CALL_EXPECT_U_COMMON(actual, pred) ASSERT_SUFFIX()

#define EXPECT_B_COMMON(actual, expected, comp, cmpName) \
CALL_EXPECT_B_COMMON(actual, expected, comp, cmpName) EXPECT_SUFFIX()

#define ASSERT_B_COMMON(actual, expected, comp, cmpName) \
CALL_EXPECT_B_COMMON(actual, expected, comp, cmpName) ASSERT_SUFFIX()

#define EXPECT_EQ(actual, expected) EXPECT_B_COMMON(actual, expected, rdns::Cmp_Eq(), "equal to")
#define ASSERT_EQ(actual, expected) ASSERT_B_COMMON(actual, expected, rdns::Cmp_Eq(), "equal to")

#define EXPECT_NE(actual, expected) EXPECT_B_COMMON(actual, expected, rdns::NotB<rdns::Cmp_Eq>(), "not equal to")
#define ASSERT_NE(actual, expected) ASSERT_B_COMMON(actual, expected, rdns::NotB<rdns::Cmp_Eq>(), "not equal to")

#define EXPECT_TRUE(actual) EXPECT_U_COMMON(actual, rdns::Is_True())
#define ASSERT_TRUE(actual) ASSERT_U_COMMON(actual, rdns::Is_True())

#define EXPECT_FALSE(actual) EXPECT_U_COMMON(actual, rdns::NotU<rdns::Is_True>())
#define ASSERT_FALSE(actual) ASSERT_U_COMMON(actual, rdns::NotU<rdns::Is_True>())

#define EXPECT_NULL(actual) EXPECT_U_COMMON(actual, rdns::Is_Null())
#define ASSERT_NULL(actual) ASSERT_U_COMMON(actual, rdns::Is_Null())

#define EXPECT_NOTNULL(actual) EXPECT_U_COMMON(actual, rdns::NotU<rdns::Is_Null>())
#define ASSERT_NOTNULL(actual) ASSERT_U_COMMON(actual, rdns::NotU<rdns::Is_Null>())

#define TEST(className, testName)                                                                   \
namespace rdns {                                                                                    \
struct className##_##testName##_Test : RdLittleTest                                                 \
{                                                                                                   \
    className##_##testName##_Test(const char * a, const char * b):RdLittleTest(a, b) {}             \
    void run();                                                                                     \
}; }                                                                                                \
static rdns::className##_##testName##_Test className##_##testName##_TestObj(#className, #testName); \
void rdns::className##_##testName##_Test::run()

#define RUN_ALL_TESTS() rdns::RdBigTest::runAll();

#endif // FILE_RDTEST_H
