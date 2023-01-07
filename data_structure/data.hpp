#include <string>

typedef unsigned int uint;

/**
 * Our data
*/

struct  Data
{
    std::string description;
    uint id;

    friend bool operator==(const Data& lhs, const Data& rhs) { return (lhs.id == rhs.id); };
    friend bool operator>(const Data& lhs, const Data& rhs)  { return (lhs.id > rhs.id); };
    friend bool operator<(const Data& lhs, const Data& rhs)  { return (lhs.id < rhs.id); };
    friend bool operator<=(const Data& lhs, const Data& rhs) { return (lhs.id <= rhs.id); };
    friend bool operator>=(const Data& lhs, const Data& rhs) { return (lhs.id >= rhs.id); };
    friend bool operator!=(const Data& lhs, const Data& rhs) { return (lhs.id != rhs.id); };
};
