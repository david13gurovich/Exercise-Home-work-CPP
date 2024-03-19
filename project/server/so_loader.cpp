#include <iostream>
#include <dlfcn.h> //dlopen, dlsym, dlclose

#include "logger_inc.hpp"
#include "so_loader.hpp"

namespace ilrd
{

namespace detail
{
static const char createFunc[] = "Create";
static const char keyFunc[] = "GetKey";
}//detail

size_t SoLoader::SoLibrariesCnt()
{
  using namespace boost::filesystem;
  using namespace boost::algorithm;

  boost::filesystem::path dir_path(m_path);
  
  for (const boost::filesystem::directory_entry& entry : 
      boost::filesystem::directory_iterator(dir_path)) 
  {
      std::string path = entry.path().string();
      if (boost::algorithm::ends_with(path, ".so")) 
      {
        ++m_soLibrariesCnt;
      }
  }

  return (m_soLibrariesCnt);
}

char** SoLoader::SoLibraries()
{
  std::cout << "SoLoader::SoLibraries" << std::endl;
  *ilrd::Logger::InstaceLogger() << ilrd::Logger::INFO << "SoLoader::SoLibraries" << std::endl;;
  
  using namespace boost::filesystem;
  using namespace boost::algorithm;

    std::cout << "SoLoader::SoLibraries - after using boost" << std::endl;
    
    m_soLibrariesCnt = 0;
    std::cout << "SoLoader::SoLibraries - m_soLibrariesCnt need be 0: " << m_soLibrariesCnt << std::endl;
    
    m_soLibrariesCnt = SoLibrariesCnt();
  std::cout << "m_soLibrariesCnt: " << m_soLibrariesCnt << std::endl;

  char **libsNames = new char*[m_soLibrariesCnt];
  //todo: change to vector and you wont need the SoLibrariesCnt
  boost::filesystem::path dir_path(m_path);
  
  std::cout << "SoLoader::SoLibraries - after boost::filesystem::path " << std::endl;
  
  size_t libraryNum = 0;
  for (const boost::filesystem::directory_entry& entry : 
      boost::filesystem::directory_iterator(dir_path))  
  {
      std::cout << "SoLoader::SoLibraries - In Loop" << std::endl;
      std::string path = entry.path().string();
      if (boost::algorithm::ends_with(path, ".so")) 
      {
        std::cout << "SoLoader::SoLibraries - In Loop - in if" << std::endl;
        
        size_t lenPlusOne = strlen(path.c_str()) + 1;
        char *libName = new char[lenPlusOne];
        memcpy(libName, path.c_str(), lenPlusOne);

        libsNames[libraryNum++] = libName;
      }
  }
  m_libsNames = libsNames;

  return (libsNames);
}

void SoLoader::Load()
{
  m_soLibrariesCnt = 0;
  m_soLibrariesCnt = SoLibrariesCnt();

  std::cout << m_soLibrariesCnt << std::endl;
  for (size_t i = 0; i < m_soLibrariesCnt; ++i)
  {
    std::cout << i << "        " << m_soLibrariesCnt << std::endl;
    m_nameHandler[i] = dlopen(m_libsNames[i],  RTLD_LAZY); 
    if(NULL == m_nameHandler[i])
    {
        *Logger::InstaceLogger() << Logger::ERROR << "dlopen failed";
        //throw!
    }
    
    createFunc func = reinterpret_cast<createFunc>(dlsym(m_nameHandler[i], detail::createFunc));
    if(NULL == func)
    {
        *Logger::InstaceLogger() << Logger::ERROR << "dlsym failed" << dlerror();
    }
    
    keyFunc key = reinterpret_cast<keyFunc>(dlsym(m_nameHandler[i], detail::keyFunc));
    if(NULL == key)
    {
        *Logger::InstaceLogger() << Logger::ERROR << "dlsym failed" << dlerror();
    }

    std::cout << "key:" << key() << std::endl;
    m_msgType->Teach(key(),func);  
  }
  std::cout << "after loop:"  << std::endl;
}

void SoLoader::OnNotify()
{
  *Logger::InstaceLogger() << Logger::INFO << "SoLoader::OnNotify before SoLibraries\n";
  SoLibraries();
  *Logger::InstaceLogger() << Logger::INFO << "SoLoader::OnNotify after SoLibraries\n";
  Load(); 
}

SoLoader::~SoLoader()
{
  for(size_t i = 0; i < m_soLibrariesCnt; ++i)
  {
    delete[] m_libsNames[i];
  }

  delete[] m_libsNames;
}

}//ilrd


