#pragma once
#include <map>
#include <string>

class Tape
{
public:
    Tape();
    ~Tape();

    Tape(std::string t);

    void writeToTape(char c);
    char readFromTape();
    void moveHead(int offset);
    int getReadHeadPosition();
    int getTapeLength();
    std::map<int, char>::iterator getTapeFront();
    std::map<int, char>::iterator getTapeEnd();

private:
    std::map<int, char> _tape;
    int _readHeadPosition;
};

