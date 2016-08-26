#include "Parser.h"
#include "Assert.h"

Parser::Parser(World &world): world(world)
{

}


bool Parser::parse(std::istream &is)
{
    try
    {
        is >> root;
    }
    catch(std::runtime_error & re)
    {
        errStr << re.what();
        return false;
    }

    Json::Value & rails = root["rails"];

    std::vector<ParserRail> parserRails;

    bool ret = parseRails(rails, parserRails);
    if(!ret) return false;


    return true;
}

std::string Parser::error()
{
    return errStr.str();
}

bool Parser::parseRails(Json::Value obj, std::vector<ParserRail> & parserRails)
{
    if(!obj.isNull())
    {
        if(!obj.isArray())
        {
            errStr << "rails is not an Array";
            return false;
        }

        for(auto it = obj.begin(); it != obj.end(); ++it)
        {
            parserRails.emplace_back();
            if(!parseRail(*it, parserRails.back()))
            {
                parserRails.clear();
                return false;
            }
            if(!parserRails.back().id.empty() && parserRails.back().points.size() != 4)
            {
                std::cout << "Rail with id " << parserRails.back().id << " has size != 4.";
                parserRails.clear();
                return false;
            }
        }
    }

    return true;
}

bool Parser::parseRail(Json::Value obj, ParserRail &rail)
{
    ASSERT(!obj.isNull());

    std::vector<float> points;

    if(obj.isArray())
    {
        bool ret = parsePoints(obj, points);
        if(!ret) return false;
    }
    else if(obj.isObject())
    {
        if(obj.isMember("id"))
        {
            errStr << "rail is Object but has no id";
            return false;
        }

        if(!obj["id"].isString())
        {
            errStr << "rail id is not a String";
            return false;
        }

        rail.id = obj["id"].asString();

        if(!obj.isMember("points"))
        {
            errStr << "rail is Object but has no points";
            return false;
        }

        Json::Value ptsObj = obj["points"];

        if(!ptsObj.isArray())
        {
            errStr << "rail points is not an Array";
            return false;
        }

        bool ret = parsePoints(obj, rail.points);
        if(!ret)
            return false;
    }
    else
    {
        errStr << "rail is neither an Array nor an Object";
        return false;
    }

    return true;
}

bool Parser::parsePoints(Json::Value obj, std::vector<float> &points)
{
    if(!obj.isArray())
    {
        errStr << "points is not an Array";
        return false;
    }

    if(!obj.isValidIndex(0))
    {
        errStr << "points is an empty Array";
        return false;
    }

    if(obj[0].isArray())
    {
        bool ret = parsePointsArrays(obj, points);
        if(!ret) return false;
    }
    else if(obj[0].isNumeric())
    {
        bool ret = parsePointsFloats(obj, points);
        if(!ret) return false;
    }
    else
    {
        errStr << "points array must be an array of arrays or numbers";
        return false;
    }

    /* TODO: to do something with points vector */

    return true;
}

bool Parser::parsePointsFloats(Json::Value obj, std::vector<float> &points)
{
    ASSERT(obj.isArray());
    ASSERT(obj.size() > 0);
    ASSERT(obj[0].isNumeric());

    if(obj.size() < 4 || obj.size() % 2 != 0)
    {
        errStr << "points array size must be at least 4 and even";
        return false;
    }

    for(auto it = obj.begin(); it != obj.end(); ++it)
    {
        Json::Value val = *it;
        if(!val.isNumeric())
        {
            errStr << "points array must be homogeneous(Numeric)";
            points.clear();
            return false;
        }

        points.push_back(val.asFloat());
    }

    return true;
}

bool Parser::parsePointsArrays(Json::Value obj, std::vector<float> &points)
{
    ASSERT(obj.isArray());
    ASSERT(obj.size() > 0);
    ASSERT(obj[0].isArray());

    if(obj.size() < 2)
    {
        errStr << "points array must has at least size 2";
        return false;
    }

    for(auto it = obj.begin(); it != obj.end(); ++it)
    {
        Json::Value val = *it;
        if(!val.isArray())
        {
            errStr << "points array must be homogeneous(Array)";
            points.clear();
            return false;
        }

        if(val.size() != 2)
        {
            errStr << "points array inner array must has size 2";
            points.clear();
            return false;
        }

        if(!val[0].isNumeric() && !val[1].isNumeric())
        {
            errStr << "points array inner array must has numeric values";
            points.clear();
            return false;
        }

        points.push_back(val[0].asFloat());
        points.push_back(val[1].asFloat());
    }

    return true;
}
