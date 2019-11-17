#ifndef MYCP_UTILS_H
#define MYCP_UTILS_H

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


namespace fs = boost::filesystem;
namespace po = boost::program_options;
using od = po::options_description;
using VecStr = std::vector<std::string>;



struct Args
{
    VecStr pathes;
    bool help;
    bool silent_mode;
    bool recursive;
};

Args parse_arguments ( int argc, char * argv[] );

int copy_file(std::string source, std::string target);

int copy_files_to_dir(std::vector<std::string> files, std::string target_dir);

#endif //MYCP_UTILS_H
