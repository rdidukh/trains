#include "RdTest.h"

#include <string>
#include <vector>
#include <map>

#ifdef _WIN32
#define RED_COLOR       ""
#define GREEN_COLOR	    ""
#define NO_COLOR	    ""
#else
#define RED_COLOR       "\033[0;31m"
#define GREEN_COLOR     "\033[0;32m"
#define NO_COLOR	    "\033[0m"
#endif

namespace rdns
{

typedef std::map<std::string, RdBigTest> RdBigTestMap;

static int bigTestsCounter;
static std::map<std::string, RdBigTest> * bigTests;

RdBigTest & getBigTest(const std::string & name)
{
    if(bigTests->find(name) == bigTests->end())
        bigTests->insert(make_pair(name, RdBigTest(name)));
    return bigTests->find(name)->second;
}

RdLittleTest::RdLittleTest(const std::string & className, const std::string & testName):name(testName)
{
    getBigTest(className).addLittleTest(this);
}

#if 0
#ifdef __linux__
#include <sys/time.h>
#endif

int64_t RdBigTest::microseconds()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    int64_t res = static_cast<int64_t>(tv.tv_sec);
    return res*1000000 + tv.tv_usec;
}
#endif

RdBigTest::RdBigTest(const std::string & className):name(className)
{
}

void RdBigTest::addLittleTest(RdLittleTest * littleTest)
{
    littleTests.push_back(littleTest);
}

static const char * plural(int x, bool upper = false)
{
    if(x == 1) return "";
    return upper ? "S" : "s";
}

int RdBigTest::runAll()
{
    int big = bigTests->size();
    int little = 0;
    std::vector<std::string> failedTestNames;

    for(std::map<std::string, RdBigTest>::iterator it = bigTests->begin(); it != bigTests->end(); ++it)
    {
        little += it->second.littleTests.size();
    }

    std::cout << GREEN_COLOR << "[==========]" << NO_COLOR;
    std::cout << " Running " << little << " test" << plural(little) << " from " << big << " test case" << plural(big) << ".\n";
    std::cout << GREEN_COLOR << "[----------]" << NO_COLOR << " Global test environment set-up.\n";

    int failed = 0;

    for(std::map<std::string, RdBigTest>::iterator it = bigTests->begin(); it != bigTests->end(); ++it)
    {
        failed += it->second.run();
        for(std::vector<RdLittleTest*>::iterator jt = it->second.failed.begin(); jt != it->second.failed.end(); ++jt)
        {
            failedTestNames.push_back(it->second.name + "." + (*jt)->name);
        }
    }   

    std::cout << GREEN_COLOR << "[----------]" << NO_COLOR << " Global test environment tear-down\n";
    std::cout << GREEN_COLOR << "[==========] " << NO_COLOR;
    std::cout << little << " test" << plural(little) << " from " << big << " test case" << plural(big) << " ran. (n/a ms total)\n";
    std::cout << GREEN_COLOR <<  "[  PASSED  ] " << NO_COLOR << (little-failed) << " test" << plural(little-failed) << ".\n";

    if(failed > 0)
    {
        std::cout << RED_COLOR << "[  FAILED  ] " << NO_COLOR << failed << " test" << plural(failed) << ", listed below:\n";
        for(size_t i = 0; i < failedTestNames.size(); i++)
            std::cout << RED_COLOR << "[  FAILED  ]" << NO_COLOR << " " << failedTestNames[i] << "\n";
        std::cout << '\n';
        std::cout << failed << " FAILED TEST" << plural(failed, true) << "\n";
    }

    return failed;
}

int RdBigTest::run()
{
    int testCount = littleTests.size();
    std::cout << GREEN_COLOR << "[----------] " << NO_COLOR << testCount << " tests from " << name << '\n';

    // auto totalTime = microseconds();
    // totalTime = 0;

    int fail = 0;
    for(std::vector<RdLittleTest *>::iterator it = littleTests.begin(); it != littleTests.end(); ++it)
    {
        RdLittleTest & littleTest = *(*it);

        std::cout << GREEN_COLOR << "[ RUN      ] " << NO_COLOR << name << '.' << littleTest.name << '\n';

        littleTest.ok = true;
        // auto start = microseconds();
        littleTest.run();
        // auto elapsed = microseconds() - start;

        //totalTime += elapsed;

        if(littleTest.ok)
        {
            std::cout << GREEN_COLOR << "[       OK ] " << NO_COLOR;
        }
        else
        {
            fail++;
            failed.push_back(*it);
            std::cout << RED_COLOR << "[  FAILED  ] " << NO_COLOR;
        }

        std::cout << name << '.' << littleTest.name << /* " (" << elapsed << " us)"  << */ "\n";

    }
    
    std::cout << GREEN_COLOR << "[----------] " << NO_COLOR;
    std::cout << testCount << " test" << plural(testCount) << " from " << name << /* " (" << totalTime << " us total)"  << */ "\n\n";

    return fail;
}

RdBigTestsInit::RdBigTestsInit()
{
	if(bigTestsCounter++ == 0)
		bigTests = new RdBigTestMap();
}

RdBigTestsInit::~RdBigTestsInit()
{
	if(--bigTestsCounter == 0)
		delete bigTests;
}

} // namespace rdns

int main(int argc, char * argv[])
{
    return RUN_ALL_TESTS();
}


