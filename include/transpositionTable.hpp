#ifndef TRANSPOSITIONTABLE_HPP_HPP
#define TRANSPOSITIONTABLE_HPP_HPP
#include <concepts>
#include <vector>
#include <cmath>

namespace chess
{
namespace transposition
{
template <typename T> concept ComparableEntry = requires (const T &a, const T &b)
{
    {
        a.pushable (b)
    } -> std::convertible_to<bool>;
    {
        a.pullable (b)
    } -> std::convertible_to<bool>;
    {
        a.hash
    } -> std::convertible_to<size_t>;
    {
        a.isEmpty ()
    } -> std::convertible_to<bool>;
};

template <ComparableEntry T> class TranspositionTable
{
  private:
    std::vector<T> table;
    int tableSize;
    int tableFill;

  public:
    TranspositionTable () {}
    void
    SetSize (const int &size_mb)
    {
        int entrySize = sizeof (T);
        int size_b = size_mb * 1e6;
        int numberOfEntries = size_b / entrySize;
        while (numberOfEntries > 0)
            {
                if (std::ceil (std::log2 (numberOfEntries)) == std::floor (std::log2 (numberOfEntries)))
                    {
                        break;
                    }
                numberOfEntries--;
            }
        tableSize = numberOfEntries;
        table.resize (numberOfEntries);
    }
    int
    GetFill ()
    {
        return tableFill;
    }
    int
    GetSize ()
    {
        return tableSize;
    }
    void
    Clear ()
    {
        table.clear ();
        tableFill = 0;
    }
    void
    push (const T &entry)
    {
        size_t index = entry.hash & (tableSize - 1);
        T oldEntry = table[index];
        if (oldEntry.pushable (entry))
            {
                table[index] = entry;
                if (oldEntry.isEmpty ())
                    {
                        tableFill++;
                    }
            }
    }
    bool
    pull (T &entry)
    {
        size_t index = entry.hash & (tableSize - 1);
        T oldEntry = table[index];
        if (oldEntry.pullable (entry))
            {
                entry = oldEntry;
                return true;
            }
        else
            {
                return false;
            }
    }
};
}
}

#endif
