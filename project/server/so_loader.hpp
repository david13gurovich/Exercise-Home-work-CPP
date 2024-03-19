#ifndef RD61_SCAN_FOLDER_HPP
#define RD61_SCAN_FOLDER_HPP

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "factory.hpp" //Factory
#include "command.hpp"
#include "create_func_data.hpp"

namespace ilrd
{
class SoLoader
{
public:
    typedef CommandSharedPtr (*createFunc)(CreateFuncData& data);
    typedef char (*keyFunc)();

public:
    SoLoader(const char *path, Factory <CreateFuncData&, char, Command> *factory)
    :   m_path(path),
        m_soLibrariesCnt(0),
        m_msgType(factory) 
        {}

    ~SoLoader();

    virtual void OnNotify();

private:
    const char *m_path;
    size_t m_soLibrariesCnt;
    char **m_libsNames;    
    Factory <CreateFuncData&, char, Command> *m_msgType;
    void *m_nameHandler[100]; //to delete

    char **SoLibraries();
    void Load();
    size_t SoLibrariesCnt();
};
}

#endif