#ifndef ILRD_RD61_FACTORY_HPP
#define ILRD_RD61_FACTORY_HPP

#include <map> 
#include <boost/function.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "common_types.hpp"
#include "exception.hpp"
#include "logger_inc.hpp"

namespace ilrd 
{

template <typename Data, typename Identifier, typename Product>
class Factory
{
public:    
    typedef boost::shared_ptr<Product> ProductSharedPtr;
    typedef boost::function<ProductSharedPtr(Data)> createFunction;

    void Teach(const Identifier i, const createFunction Function);
    ProductSharedPtr Create(const Identifier i, Data d);
    bool DoesExist(const Identifier i);

private:
    std::map<Identifier, createFunction> m_factoryLUT; 
};

template <typename Data, typename Identifier, typename Product>
void Factory<Data, Identifier, Product>::Teach(const Identifier i, 
                                                const createFunction Function)
{
    std::cout << "Teach" << std::endl;
    if(DoesExist(i))
    {
       *Logger::InstaceLogger() << Logger::ERROR << "Already Exist" << std::endl; 
        return;
    }

    std::pair<typename std::map<Identifier, createFunction>::iterator,bool> retInsert;
    m_factoryLUT.insert(std::pair<Identifier, createFunction>(i, Function));
    *Logger::InstaceLogger() << Logger::INFO << "insert succsed" << std::endl;
}

template <typename Data, typename Identifier, typename Product>
typename Factory<Data, Identifier, Product>::ProductSharedPtr 
        Factory<Data, Identifier, Product>::Create(const Identifier i, Data d)
{
    typename std::map<Identifier, createFunction>::iterator returnFind;
    returnFind = m_factoryLUT.find(i);

    if (returnFind == m_factoryLUT.end())
    {
       *Logger::InstaceLogger() << Logger::ERROR << "Does Not Exist" << std::endl;
       throw IdentifierError();
    }
    else
    {
        *Logger::InstaceLogger() << Logger::INFO << "Create succsed" << std::endl;
    }
    
    return (returnFind->second(d));
}

template <typename Data, typename Identifier, typename Product>
bool Factory<Data, Identifier, Product>::DoesExist(const Identifier i)
{
    typename std::map<Identifier, createFunction>::iterator returnFind;
    returnFind = m_factoryLUT.find(i);

    return(returnFind != m_factoryLUT.end());
}

}//ilrd

#endif
