#ifndef MYCP_UTILS_H
#define MYCP_UTILS_H

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

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


#endif //MYCP_UTILS_H
