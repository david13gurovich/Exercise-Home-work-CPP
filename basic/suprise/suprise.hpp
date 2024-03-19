#ifndef ILRD_RD61_SUPRISE_HPP
#define ILRD_RD61_SUPRISE_HPP

#include <iostream> //cout
#include <cstdlib> //system
#include <fstream> //ofstream

namespace ilrd 
{

class Surprise
{
public:
    Surprise();
    virtual ~Surprise();
    virtual void SurpriseMe() const {}
};

class OnScreen : public Surprise
{
public:
    void SurpriseMe() const { std::cout << "surprise!" << std::endl; }
};

class Echo : public Surprise
{
public:
    void SurpriseMe() const { system("echo surprise with echo"); }
};

class CreateFile : public Surprise
{
public:
    void SurpriseMe() const { std::ofstream of("nothing_here.txt");  }
};

Surprise *GetRandom();
}
//ilrd
#endif//ILRD_RD61_FILESURPRISER_HPP