#include <filesystem>
#include <set>

#include <unistd.h>

#include <string>


extern char** environ;


// Path to subtitle directory and episodes directory
const char* subs_path = "/home/mango/personal/anime/NGNL/JP_Subs/";
const char* episodes_path = "/home/mango/personal/anime/NGNL/Episodes/";


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


int main(int argc, char** argv)
{
    if (argc == 1)
    {
	return 0;
    }

    int episode = std::stoi(argv[1]) - 1;
    
    if (episode < 0)
    {
	fprintf(stderr, "Episode must be >= 1\n");
	return -1;
    }

    std::set<path> episodes;
    std::set<path> subs;

    fillSet(subs, subs_path);
    fillSet(episodes, episodes_path);

    auto finalSubPath = advance_iterator(subs, episode);
    auto finalEpisodePath = advance_iterator(episodes, episode);


    printf("Sub file:%s\n", finalSubPath->c_str());
    printf("Episode file%s\n", finalEpisodePath->c_str());


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


    printf("running command:\n");
    printf("%s ", mpv_bin);

    for (int i = 0; i < 2; i++)
    {
	printf("%s ", mpv_args[i]);
    }

    printf("\n");


    // run mpv
    printf("%d\n", execve(mpv_bin, mpv_args, environ));

    return 0;
}

