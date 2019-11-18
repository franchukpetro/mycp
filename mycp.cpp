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

    if (args.help){
        std::cout<< "Help message"<<std::endl;
        return 0;
    }


    if (fs::is_directory(args.pathes.back())){
        std::vector<std::string> files = std::vector<std::string>(args.pathes.begin(), args.pathes.end() - 1);
        std::string target_dir = args.pathes.back();
        copy_files_to_dir(files, target_dir);
    }
    else{
        copy_file(args.pathes[0], args.pathes.back());
    }

    return 0;

}