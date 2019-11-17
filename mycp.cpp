#include <iostream>
#include "utils.h"


int main(int argc, char * argv[]) {
    Args args;
    try{
        args = parse_arguments(argc, argv);
    }
    catch ( std::exception & ex )
    {
        return -1;
    }


    //boost::filesystem::is_directory(args.pathes[-1]) ? copy_files_to_dir()

    std::vector<std::string> files = std::vector<std::string>(args.pathes.begin(), args.pathes.end() - 1);
    std::string target_dir = args.pathes[args.pathes.size() - 1];

    //std::cout<<target_dir<<" ";

    copy_files_to_dir(files, target_dir);

    //copy_file(args.pathes[0], args.pathes[1]);

}