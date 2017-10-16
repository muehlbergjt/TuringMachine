#include "TuringMachine.h"

TuringMachine::TuringMachine()
{
    _alphabet = std::vector<char>();
    _alphabet.push_back('_');

    _transitions = std::map<std::pair<std::string, char>, std::tuple<std::string, char, char>>();
}

TuringMachine::~TuringMachine()
{

}

//Advance 1 tick and return a value to indicate success or failure
int TuringMachine::advance()
{
    //get symbol at read head
    char symbol = _tape.readFromTape();

    //check if machine is in accepting state
    if (_currentState == _acceptingState)
    {
        return 1;
    }

    //check if symbol is in alphabet, if not terminate turing machine execution
    if (std::find(_alphabet.begin(), _alphabet.end(), symbol) != _alphabet.end())
    {
        //create state input for transition
        std::pair<std::string, char> state = std::pair<std::string, char>(_currentState, symbol);

        //get the transition action
        std::tuple<std::string, char, char> action = _transitions.at(state);

        //execute the transition action
        _currentState = std::get<0>(action);
        _tape.writeToTape(std::get<1>(action));

        //get proper offset for tape
        char off = std::get<2>(action);
        if (off == '>')
        {
            _tape.moveHead(1);
        }
        else
        {
            _tape.moveHead(-1);
        }

        if (_currentState == _acceptingState)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }
}

//register the legal alphabet of the turing machine
//takes a single string of characters with no spaces
void TuringMachine::registerAlphabet(std::string a)
{
    for (int i = 0; i < a.length(); i++)
    {
        _alphabet.push_back(a.at(i));
    }
}

//register the legal states of the turing machine
//takes a single string composed of all states delimited by a space
void TuringMachine::registerStates(std::string s)
{
    _states = std::vector<std::string>();

    int lastIndex = 0;
    int index = 0;
    int length = s.length();
    std::string state;
    while (lastIndex < length + 1)
    {
        index = state.find_first_of(' ', lastIndex);
        if (index == std::string::npos)
        {
            index = length;
        }

        if (index != lastIndex)
        {
            _states.push_back(s.substr(lastIndex, index - lastIndex));
        }

        lastIndex = index + 1;
    }
}

//register legal transitions of the turing machine
//takes a vector of strings where each string describes a transition
void TuringMachine::registerTransitions(std::vector<std::string> t)
{
    //declare the temp variables used to register transitions
    std::string stateBefore;
    char symbolBefore;
    std::string stateAfter;
    char symbolAfter;
    char offset;

    std::pair<std::string, char> input;
    std::tuple<std::string, char, char> action;

    int index = 0;

    for each (std::string trans in t)
    {
        //find the first space and make a substring to get the state
        index = trans.find(' ');
        stateBefore = trans.substr(0, index);
        trans.erase(0, index + 1);

        //don't need find because this must be a 1 character symbol
        //erase extra characters because we want to get rid of the extra " = "
        symbolBefore = trans.at(0);
        trans.erase(0, 4);

        index = trans.find(' ');
        stateAfter = trans.substr(0, index);
        trans.erase(0, index + 1);

        symbolAfter = trans.at(0);
        trans.erase(0, 2);

        offset = trans.at(0);

        input = std::make_pair(stateBefore, symbolBefore);
        action = std::make_tuple(stateAfter, symbolAfter, offset);

        _transitions.insert(std::pair<std::pair<std::string, char>, std::tuple<std::string, char, char>>(input, action));
    }
}

//load the tape into the turing machine
void TuringMachine::loadTape(Tape tp)
{
    _tape = tp;
}

void TuringMachine::setAcceptingState(std::string state)
{
    _acceptingState = state;
}

void TuringMachine::setCurrentState(std::string state)
{
    _currentState = state;
}

Tape* TuringMachine::getTape()
{
    return &_tape;
}