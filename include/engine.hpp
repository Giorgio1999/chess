#ifndef ENGINE_ENGINE_HPP
#define ENGINE_ENGINE_HPP
#include <string>
#include <functional>

namespace chess
{
namespace engine
{
class Engine
{
  private:
    std::string name = "";
    std::string author = "";
    int version_major = 1;
    int version_minor = 0;
    int version_patch = 0;
    std::function<std::string (Engine &)> search;
    bool stop = false;
    bool ready = false;

  public:
    Engine (std::string name, std::string author)
    {
        this->name = name;
        this->author = author;
    }

    std::string Introduce ();
    void Stop ();
    void UnStop ();
    std::string
    Search ()
    {
        return search (*this);
    }

    std::string
    GetName ()
    {
        return name;
    }
    std::string
    GetAuthor ()
    {
        return author;
    }
    int
    GetVersion_Major ()
    {
        return version_major;
    }
    int
    GetVersion_Minor ()
    {
        return version_minor;
    }
    int
    GetVersion_Patch ()
    {
        return version_patch;
    }
    std::function<std::string (Engine &)>
    GetSearch ()
    {
        return search;
    }
    bool
    IsReady ()
    {
        return ready;
    }
    bool
    IsStop ()
    {
        return stop;
    }

    void
    SetName (std::string _name)
    {
        name = _name;
    }
    void
    SetAuthor (std::string _author)
    {
        author = _author;
    }
    void
    SetVersion_Major (int _version_major)
    {
        version_major = _version_major;
    }
    void
    SetVersion_Minor (int _version_minor)
    {
        version_minor = _version_minor;
    }
    void
    SetVersion_Patch (int _version_patch)
    {
        version_patch = _version_patch;
    }
    void
    SetSearch (std::function<std::string (Engine &)> _search)
    {
        search = _search;
    }
    void
    SetReady (bool _ready)
    {
        ready = _ready;
    }
};

}
}
#endif
