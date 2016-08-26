#include <iostream>
#include <fstream>

#include "World.h"
#include "Train.h"
#include "OpenGL.h"
#include "Parser.h"

struct Error
{

} error;

template<typename T>
Error & operator<<(Error & err, const T & t)
{
    std::cout << t;
    return err;
}

template<>
Error & operator<<(Error & err, const Error & r)
{
    std::cout << std::endl;
    exit(1);
}

int main(int argc, char * argv[])
{
    if(argc != 2)
        error << "Usage: " << argv[0] << " file.cfg\n" << error;

    std::ifstream file(argv[1]);

    if(!file)
        error << "Error: could not open file: \'" << argv[1] << "\'\n" << error;

    World world;

    Parser parser(world);

    bool ret = parser.parse(file);

    if(!ret)
    {
        error << "Error: could not parse file: \'" << argv[1] << "\'\n" \
              << parser.error() << "\n" << error;
    }

    OpenGL openGL(world);

    openGL.run(10);

    return 0;
}
