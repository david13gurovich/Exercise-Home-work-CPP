#ifndef ILRD_RD61_SUPRISE_HPP
#define ILRD_RD61_SUPRISE_HPP

#include <iostream>
#include <cstdlib>
#include <fstream>

namespace ilrd 
{

class Surprise
{
friend Surprise *GetRandom(class Surprise& surprise);

public:
    Surprise();
    virtual ~Surprise();
    virtual void SurpriseMe() const {}

};

class Screen : public Surprise
{
public:
    Screen() {}
    ~Screen() {}
    void SurpriseMe() const { std::cout << "surprise!" << std::endl; }
};

class System : public Surprise
{
public:
    void SurpriseMe() const { system("echo -e '\\a'"); }
};

class File : public Surprise
{
public:
    void SurpriseMe() const { std::ofstream of("nothing_here.txt");  }
};
}




#endif
