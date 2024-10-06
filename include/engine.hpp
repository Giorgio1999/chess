#ifndef ENGINE_ENGINE_HPP
#define ENGINE_ENGINE_HPP
#include <string>

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

  public:
    Engine (std::string name, std::string author)
    {
        this->name = name;
        this->author = author;
    }

    std::string Introduce ();
    std::string Search ();

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
};

}
}
#endif
