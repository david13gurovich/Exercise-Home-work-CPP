#ifndef H_COMMAND 
#define H_COMMAND

namespace ilrd
{
class Command
{
public:
    virtual ~Command()
    {
        std::cout << "Dtor command" << std::endl;
    };
    virtual void Action() = 0;
};
}
#endif