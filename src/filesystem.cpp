
#include "filesystem.h"
#include "tinydir.h"
#include "string_utils.h"
#include <set>
#include <string>

namespace shake {

bool exists(const char* path)
{
    struct stat info;

    if(stat( path, &info ) != 0) return false;
    else return true;
}

void make_dir(const char* path)
{
#if defined(_WIN32)
    ::_mkdir(path);
#else 
    ::mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
}

void make_path(const std::string& path)
{
    if (not exists(path))
    {
        make_path(path.substr(0, path.find_last_of('/')));
        make_dir(path);
    }

}

struct tiny_dir_handler
{
    tinydir_dir d;

    void open(const char* name)
    {
        tinydir_open(&this->d, name);
    }

    void next()
    {
        tinydir_next(&this->d);
    }

    void read(tinydir_file& f)
    {
        tinydir_readfile(&this->d, &f);
    }

    bool has_next()
    {
        return this->d.has_next;
    }

    ~tiny_dir_handler()
    {
        tinydir_close(&this->d);
    }
};

const std::set<std::string>& skip_directories()
{
    static std::set<std::string> directories = { ".", "..", "./", "../"};
    return directories;
}

void ls(const char* path, std::function<void(dir)> f)
{
    tiny_dir_handler handle;
    handle.open(path);
    while(handle.has_next())
    {
        tinydir_file tf;
        handle.read(tf);
        if (skip_directories().find(tf.name) == skip_directories().end())
        {
            dir d;
            d.name = tf.name;
            d.path = tf.path;
            d.extension = tf.extension;
            d.is_dir = tf.is_dir;
            d.is_regular = tf.is_reg;
            f(d);
        }

        handle.next();
    }
}

}
