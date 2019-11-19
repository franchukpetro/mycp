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
    if ((fs::is_directory(args.pathes[0]) && fs::is_regular_file(args.pathes.back())) ||
        (fs::is_directory(args.pathes[0]) && !fs::exists(args.pathes.back())))
    {
        std::cout<<"Can not copy directory to the file!"<<std::endl;
        exit(1);
    }


    for(int i=0; i < args.pathes.size() - 1; i++){
        std::string targ_file = args.pathes.back();
        boost::filesystem::path p(args.pathes[i]);

        if (fs::is_directory(args.pathes.back())){
            //add name of source file to path of target dir
            targ_file = args.pathes.back() + "/" + p.filename().string();
        }

        if (fs::exists(targ_file)){

            if (!args.silent_mode){
                std::string answer;

                std::cout<<"Do you want to rewrite "<<p.filename().string()<<"?"<<std::endl;
                std::cout<<"Y[es]/N[o]/A[ll]/C[ancel]"<<std::endl;
                std::cin>> answer;
                boost::algorithm::to_lower(answer);
                if (answer == "y"){
                    fs::copy_file(args.pathes[i], targ_file, fs::copy_option::overwrite_if_exists);
                }
                else if (answer == "n"){
                    continue;
                }
                else if (answer == "a"){
                    args.silent_mode = true;
                }
                else if (answer == "c"){
                    exit(0);
                }

            }
            else{
                fs::copy_file(args.pathes[i], targ_file, fs::copy_option::overwrite_if_exists);
            }
        }

        else{
            fs::copy(args.pathes[i], args.pathes.back());
        }
    }


    return 0;

}