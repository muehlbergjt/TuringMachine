#include "Tape.h"

Tape::Tape()
{

}

Tape::~Tape()
{

}

Tape::Tape(std::string t)
{
    _readHeadPosition = 0;

    _tape = std::map<int, char>();
    for (int i = 0; i < t.length(); i++)
    {
        _tape.insert(std::pair<int, char>(i, t.at(i)));
    }
}

char Tape::readFromTape()
{
    if (_tape.find(_readHeadPosition) == _tape.end())
    {
        return '_';
    }
    else
    {
        return _tape.at(_readHeadPosition);
    }
}

void Tape::writeToTape(char c)
{
    if (_tape.find(_readHeadPosition) == _tape.end())
    {
        _tape.insert(std::pair<int, char>(_readHeadPosition, c));
    }
    else
    {
        _tape.at(_readHeadPosition) = c;
    }
}

void Tape::moveHead(int offset)
{
    _readHeadPosition += offset;
}

int Tape::getReadHeadPosition()
{
    return _readHeadPosition;
}

int Tape::getTapeLength()
{
    return _tape.size();
}

std::map<int, char>::iterator Tape::getTapeFront()
{
    return _tape.begin();
}

std::map<int, char>::iterator Tape::getTapeEnd()
{
    return _tape.end();
}