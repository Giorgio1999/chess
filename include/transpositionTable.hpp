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
        a >= b
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
    SetSize (const size_t &size_mb)
    {
        size_t entrySize = sizeof (T);
        size_t size_b = size_mb * 1e6;
        size_t numberOfEntries = size_b / entrySize;
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
    size_t
    GetFill ()
    {
        return tableFill;
    }
    void
    push (const T &entry)
    {
        size_t index = entry.hash & (tableSize - 1);
        T oldEntry = table[index];
        if (entry >= oldEntry)
            {
                table[index] = entry;
                if (entry.isEmpty ())
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
        if (entry >= oldEntry)
            {
                return false;
            }
        else
            {
                entry = oldEntry;
                return true;
            }
    }
};
}
}

#endif
