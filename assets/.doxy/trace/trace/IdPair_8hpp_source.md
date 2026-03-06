

# File IdPair.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**types**](dir_99d9bc6205d35ba61d9e386839c646c4.md) **>** [**IdPair.hpp**](IdPair_8hpp.md)

[Go to the documentation of this file](IdPair_8hpp.md)


```C++

#pragma once

#include <cstdint>
#include <functional>

namespace astrea {
namespace trace {

struct IdPair {
    std::size_t sender;   
    std::size_t receiver; 

    IdPair() = default;

    IdPair(std::size_t sender, std::size_t receiver) :
        sender(sender),
        receiver(receiver)
    {
    }

    IdPair(const IdPair& other) :
        sender(other.sender),
        receiver(other.receiver)
    {
    }

    ~IdPair() = default;

    bool operator==(const IdPair& other) const { return (sender == other.sender && receiver == other.receiver); }
};

} // namespace trace
} // namespace astrea

template <>
struct std::hash<astrea::trace::IdPair> {
    std::size_t operator()(const astrea::trace::IdPair& k) const
    {
        return (std::hash<std::size_t>()(k.sender)) ^ (std::hash<std::size_t>()(k.receiver));
    }
};

template <>
struct std::less<astrea::trace::IdPair> {
    bool operator()(const astrea::trace::IdPair& lhs, const astrea::trace::IdPair& rhs) const
    {
        if (lhs.sender == rhs.sender) { return lhs.receiver < rhs.receiver; }
        else {
            return lhs.sender < rhs.sender;
        }
    };
};
```


