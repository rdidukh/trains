#include "World.h"

#include <iostream>
#include <fstream>

#include "OpenGLRender.h"

#include <time.h>
#include <sys/time.h>
#include <unistd.h>

void help(int ec)
{
    std::cout << "Usage: ./trains map.txt\n";
    exit(ec);
}

int main(int argc, char * argv[])
{
    World world;

    if(argc != 2)
        help(1);

    std::ifstream ifile(argv[1]);

    if(ifile)
    {
        world.read(ifile);
    }
    else
    {
        std::cerr << "File \'" << argv[1] << "\' can\'t be opened\n";
    }

    OpenGLRender render(world, argc, argv);

    render.run();

    return 0;
}
