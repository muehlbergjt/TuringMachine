#pragma once

#include "Tape.h"
#include <vector>
#include <tuple>
#include <utility>

class TuringMachine
{
public:
    TuringMachine();
    ~TuringMachine();

    void registerAlphabet(std::string a);
    void registerStates(std::string states);
    void registerTransitions(std::vector<std::string> t);
    void setAcceptingState(std::string state);
    void setCurrentState(std::string state);
    void loadTape(Tape tp);
    int advance();

    Tape* getTape();

private:
    Tape _tape;
    std::vector<char> _alphabet;
    std::vector<std::string> _states;
    std::map<std::pair<std::string, char>, std::tuple<std::string, char, char>> _transitions;
    std::string _currentState;
    std::string _acceptingState;
};