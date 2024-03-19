#include <iostream>       // std::cerr
#include <exception>      // std::set_terminate
#include <cstdlib>        // std::abort

void myterminate () 
{
  std::cerr << "terminate handler called\n";
  exit(0);
}

void myunexpected () 
{
  std::cerr << "unexpected called\n";
//   throw 'x';   
}

void myfunction () {
  throw 'x';   // throws char (not in exception-specification)
}

int main (void) 
{
  std::set_unexpected (myunexpected);
  std::set_terminate (myterminate);

    myfunction();


  return 0;
}
