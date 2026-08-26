#include <filesystem>
#include <set>

#include <unistd.h>

#include <string>


// DEBUG FILE
#include "../include/debug.h"


extern char** environ;


// Path to subtitle directory and episodes directory
const char* base = "/home/mango/personal/anime/";


// helper for moving an iterator to an arbitrary position from begin()
template <typename T>
auto advance_iterator(const T &t, size_t n)
{
    auto it = std::begin(t);
    std::advance(it, n);
    return it;
}


// shorthands
using path = std::filesystem::path;
using dir_iterator = std::filesystem::directory_iterator;


// helper for filling a set with directory items
void fillSet(std::set<path>& s, const char* dir)
{
    for (const auto& dir_ent : dir_iterator(dir))
    {
	s.insert(dir_ent.path());
    }
}

#ifdef DEBUG
void printArgv(int argc, char** argv)
{
    printf("Args:\n");

    for (int i{0}; i < argc; i++)
    {
	printf("%s\n", argv[i]);
    }
}
#endif


struct Anime
{
    int episode;
    std::string subFileDir;
    std::string episodeFileDir;
};


bool parseArgv(int argc, char** argv, struct Anime* anime)
{
    DEBUG_LOG("Parsing Arguments...");

    bool success = true;

    for (int argIndex{1}; argIndex < argc; argIndex++)
    {
	std::string arg = argv[argIndex];
	std::string key, val;

	// separator character, in this case '='
	int sep = 0;
	while (sep < arg.length())
	{
	    sep++;
	    if (arg[sep] == '=')
	    {
		break;
	    }
	}

	// arg[i] is '='
	key = arg.substr(0, sep);
	val = arg.substr(sep + 1, arg.length());

	DEBUG_LOG(key);
	DEBUG_LOG(val);

	// Could make this a map of key-val pairs; map<std::string, std::string>
	// and then grab the value of each key and initialize the anime struct
	// directly.
	if (key == "--ep")
	{
	    anime->episode = std::stoi(val) - 1; // 0 indexed episode
	}
	else if (key == "--anime")
	{
	    anime->subFileDir = std::string(base) + val + "/subs/";
	    anime->episodeFileDir = std::string(base) + val + "/episodes/";
	}
    }

    return success;
}


int main(int argc, char** argv)
{
    if (argc == 1)
    {
	return 0;
    }

#ifdef DEBUG
    printArgv(argc, argv);
#endif

    struct Anime anime;

    if (parseArgv(argc, argv, &anime))
    {
	printf("Arguments parsed successfully.\n");
    }
    else
    {
	printf("Failed to parse all arguments");
	return -1;
    }

    int episode = anime.episode;
    
    if (episode < 0)
    {
	fprintf(stderr, "Episode must be >= 1\n");
	return -1;
    }

    std::set<path> episodes;
    std::set<path> subs;

    fillSet(subs, anime.subFileDir.c_str());
    fillSet(episodes, anime.episodeFileDir.c_str());

    auto finalSubPath = advance_iterator(subs, episode);
    auto finalEpisodePath = advance_iterator(episodes, episode);


#ifdef DEBUG
    printf("Sub file:%s\n", finalSubPath->c_str());
    printf("Episode file%s\n", finalEpisodePath->c_str());
#endif


    std::string mpvSubFileArg = "--sub-file=" + std::string(finalSubPath->c_str());
    std::string mpvInputFileArg = std::string(finalEpisodePath->c_str());


    const char* mpv_bin = "/usr/bin/mpv";

    // conventionally,
    // the first argument is the binary itself
    // the last argument is nullptr (the array is null-terminated)
    char* const mpv_args[] = {
	(char* const) mpv_bin,
	(char* const) mpvSubFileArg.c_str(),
	(char* const) mpvInputFileArg.c_str(),
	nullptr
    };


#ifdef DEBUG
    printf("running command:\n");
    printf("%s ", mpv_bin);

    for (int i = 0; i < 2; i++)
    {
	printf("%s ", mpv_args[i]);
    }

    printf("\n");
#endif


    // run mpv; start the episode
    printf("%d\n", execve(mpv_bin, mpv_args, environ));

    return 0;
}

