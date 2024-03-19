#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

int main(int argc, char* argv[])
{
    boost::filesystem::path dir_path(".");
    
    for (const auto& entry : boost::filesystem::directory_iterator(dir_path)) 
    {
        if (boost::filesystem::is_regular_file(entry))
        {
            std::string path = entry.path().string();
            if (boost::algorithm::ends_with(path, ".txt")) 
            {
                std::cout << path << std::endl;
            }
        }
    }

    return 0;
}