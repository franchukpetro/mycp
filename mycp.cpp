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

    //exit if in sources there is directory, but target is file

    // !!! works only if target file exists
    if ((fs::is_directory(args.pathes[0]) && fs::is_regular_file(args.pathes.back())))
    {
        std::cout<<"Can not copy directory to the file!"<<std::endl;
        exit(1);
    }


    for(int i=0; i < args.pathes.size() - 1; i++){
        std::string targ_file = args.pathes.back();
        fs::path p(args.pathes[i]);

        if (fs::is_directory(args.pathes.back()) && fs::is_regular_file(args.pathes[i])){
            //add name of source file to path of target dir
            targ_file = args.pathes.back() + "/" + p.filename().string();
        }

        if (fs::is_directory(args.pathes[i])){
            if (args.recursive){

                fs::create_directory((fs::path) args.pathes.back()/p.filename());
                recursive_copy(args.pathes[i], args.pathes.back()/p.filename(), args.silent_mode);
                continue;
            }
            else {
                return -1;
            }

        }

        args.silent_mode = my_copy_file(p, targ_file, args.silent_mode);
    }


    return 0;

}