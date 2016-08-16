#include "World.h"
#include "Rail.h"
#include "Render.h"

void World::init()
{
    
}

bool World::read(std::istream & is)
{
    std::string line;

    while(!is.eof())
    {
        std::getline(is, line);
        if(is.eof()) return false;
        std::istringstream iss(line);

        if(line.empty() || line[0] == '#') continue;

        std::string cmd;
        iss >> cmd;
        if(is.eof()) return false;

        if(cmd == "line")
        {
            Rail rail;
            iss >> rail;
            addRail(rail);
        }

    }

    return true;
}

void World::addRail(const Rail & rail)
{
    rails.push_back(rail);
}

void World::update(int frame)
{
    std::cout << "World.update " << frame << '\n';
}
