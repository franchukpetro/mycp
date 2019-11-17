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

int copy_file(std::string source, std::string target){
    //char *src, *dst;
    int fdSrc, fdDst;
    struct stat sb;


    fdSrc = open(source.c_str(), O_RDONLY);
    if (fdSrc == -1){
        //TODO: error handling here
    }

    if (fstat(fdSrc, &sb) == -1){
        //TODO: error handling here
    }

    if (sb.st_size == 0)
        exit(EXIT_SUCCESS);

    const auto src = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fdSrc, 0);
    if (src == MAP_FAILED){
        //TODO: error handling here
    }


    fdDst = open(target.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdDst == -1){
        //TODO: error handling here
    }

    if (ftruncate(fdDst, sb.st_size) == -1){
        //TODO: error handling here
    }

    auto dst = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdDst, 0);
    if (dst == MAP_FAILED){
        //TODO: error handling here
    }

    memcpy(dst, src, sb.st_size);       /* Copy bytes between mappings */
    if (msync(dst, sb.st_size, MS_SYNC) == -1){
        //TODO: error handling here
    }

    exit(EXIT_SUCCESS);
}

int copy_files_to_dir(std::vector<std::string> files, std::string target_dir){
    for (int i=0; i < files.size(); i++){
        boost::filesystem::path p(files[i]);
        std::string targ_file = target_dir + "/" + p.filename().string();
        copy_file(files[i], targ_file);
    }
}