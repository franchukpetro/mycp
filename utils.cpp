#include "utils.h"


Args parse_arguments ( int argc, char * argv[] ){

    Args args;

    try{
        od desc {"Options"};
        desc.add_options()
                ("pathes", po::value<VecStr>()->multitoken()->zero_tokens()->composing())
                (",-", po::value<VecStr>()->multitoken()->zero_tokens()->composing())
                ("help,h", po::bool_switch())
                (",f", po::bool_switch())
                (",R", po::bool_switch());
        po::positional_options_description pos_desc;
        pos_desc.add("pathes", -1);
        po::command_line_parser parser {argc, argv};
        auto parsed_options = parser
                .options(desc)
                .positional(pos_desc)
                .allow_unregistered()
                .run();

        po::variables_map vm;
        store(parsed_options, vm);
        notify(vm);


        if ( vm.count("pathes"))
            args.pathes = vm["pathes"].as<VecStr>();


        args.help = vm["help"].as<bool>();

        args.silent_mode = vm["-f"].as<bool>();

        args.recursive = vm["-R"].as<bool>();

    }
    catch ( const po::error & ex )
    {
        std::cerr << ex.what() << '\n';
        throw ex;
    }

    return args;

}

void CopyRecursive(const fs::path& src, const fs::path& target) {
    try {
        for (const auto &dirEntry : fs::recursive_directory_iterator(src)) {
            std::cout<<dirEntry<<std::endl;
            const auto &p = dirEntry.path();

            // Create path in target, if not existing.
            const auto relativeSrc = fs::relative(p, src);
            const auto targetParentPath = target / relativeSrc.parent_path();
            std::cout<<targetParentPath<<std::endl;
            if (!fs::exists(targetParentPath)){
                fs::create_directories(targetParentPath);
            }

            // Copy to the targetParentPath which we just created.
            if (fs::is_regular_file(p)){
                fs::copy(p, targetParentPath);

            } else if (fs::is_directory(p)){
                fs::copy_directory(p, targetParentPath);
            }

        }
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }

}

void copy_dir(std::string source, std::string target, bool rec){
    if (rec){
        CopyRecursive(source, target);
    }
    else {
        fs::copy_directory(source, target);
    }
}

void recursive_copy(const fs::path &src, const fs::path &dst){
    if (fs::is_directory(src)) {
        fs::create_directories(dst);
        for (fs::directory_entry& item : fs::directory_iterator(src)) {
            recursive_copy(item.path(), dst/item.path().filename());
        }
    }
    else if (fs::is_regular_file(src)) {
        fs::copy(src, dst);
    }
}