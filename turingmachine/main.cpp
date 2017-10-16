#include <iostream>
#include <fstream>
#include "TuringMachine.h"

TuringMachine tm;
Tape tp;

void runMachine()
{
    int status = 0;

    while (status == 0)
    {
        status = tm.advance();
    }
}

void printTape()
{
    //print the current state of the tape
    for (std::map<int, char>::iterator it = tm.getTape()->getTapeFront(); it != tm.getTape()->getTapeEnd(); it++)
    {
        std::cout << it->second;
    }

    std::cout << std::endl;

    //print the location of the center of the tape and the read head
    for (std::map<int, char>::iterator it = tm.getTape()->getTapeFront(); it != tm.getTape()->getTapeEnd(); it++)
    {
        if (it->first == 0)
        {
            std::cout << '|';
        }
        else if (it->first == tm.getTape()->getReadHeadPosition())
        {
            std::cout << '^';
        }
        else
        {
            std::cout << ' ';
        }
    }

    std::cout << std::endl;
}

void initializeMachine(std::string alphabet, std::string states, std::string initialState, std::string acceptingState, std::vector<std::string> transitions)
{
    tm = TuringMachine::TuringMachine();

    tm.registerAlphabet(alphabet);
    tm.registerStates(states);
    tm.setCurrentState(initialState);
    tm.setAcceptingState(acceptingState);
    tm.registerTransitions(transitions);
    tm.loadTape(tp);
}

int readFile(std::string fileName)
{
    std::ifstream file(fileName);

    //read in all turing machine information from file
    if (file.is_open())
    {
        std::cout << "Reading turing machine configuration from file" << std::endl;

        std::string alphabet;
        std::getline(file, alphabet);

        std::string states;
        std::getline(file, states);

        std::string initialState;
        std::getline(file, initialState);

        std::string acceptingState;
        std::getline(file, acceptingState);

        std::string tape;
        std::getline(file, tape);

        std::vector<std::string> transitions = std::vector<std::string>();
        std::string transition;
        while (getline(file, transition))
        {
            transitions.push_back(transition);
        }

        std::cout << "Closing config file" << std::endl;
        file.close();

        //initialize tape
        std::cout << "Initializing tape." << std::endl;
        tp = Tape::Tape(tape);

        //initialize turing machine
        std::cout << "Initializing machine." << std::endl;
        initializeMachine(alphabet, states, initialState, acceptingState, transitions);
        return 0;
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
        return -1;
    }
}

int main()
{
    //get name of file with turing machine configuration
    std::string fileName;
    std::cout << "Please enter turing machine file name" << std::endl;
    std::cin >> fileName;

    //check if they input a filename with or without the .txt, if there is no .txt append it
    /**
    if (fileName.length() < 5 || fileName.compare(fileName.length() - 4, 4, ".txt") == 0)
    {
        fileName.append(".txt");
    }**/

    //std::cout << fileName << std::endl;

    int status;

    //read file
    status = readFile(fileName);

    if (status != -1)
    {
        //run turing machine
        runMachine();

        //output result tape
        printTape();
    }

    system("PAUSE");
}