

# File AccessArray.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**risesets**](dir_3852194babc4edab798292ba09c53d6d.md) **>** [**AccessArray.hpp**](AccessArray_8hpp.md)

[Go to the documentation of this file](AccessArray_8hpp.md)


```C++

#pragma once

#include <gtl/btree.hpp>

#include <trace/risesets/RiseSetArray.hpp>
#include <trace/types/IdPair.hpp>

namespace astrea {
namespace trace {

class AccessArray {

    friend std::ostream& operator<<(std::ostream& os, const AccessArray& accessarray);

  public:
    AccessArray() = default;

    ~AccessArray() = default;

    RiseSetArray& operator[](const std::size_t& senderId, const std::size_t& receiverId);

    const RiseSetArray& at(const std::size_t& senderId, const std::size_t& receiverId) const;

    bool contains(const IdPair& idPair) const;

    void erase(const std::size_t& senderId, const std::size_t& receiverId);

    std::size_t size() const;

    RiseSetArray get_all_accesses_to_receiver(const std::size_t& receiverId) const;

    RiseSetArray get_all_accesses_from_sender(const std::size_t& senderId) const;

    bool operator==(const AccessArray& other) const;

    AccessArray& operator|=(const AccessArray& other);

    AccessArray operator|(const AccessArray& other) const;

    AccessArray& operator&=(const AccessArray& other);

    AccessArray operator&(const AccessArray& other) const;

    using iterator = gtl::btree_map<IdPair, RiseSetArray>::iterator;

    using const_iterator = gtl::btree_map<IdPair, RiseSetArray>::const_iterator;

    iterator begin() { return _accesses.begin(); }

    iterator end() { return _accesses.end(); }

    const_iterator begin() const { return _accesses.begin(); }

    const_iterator end() const { return _accesses.end(); }

    const_iterator cbegin() const { return _accesses.cbegin(); }

    const_iterator cend() const { return _accesses.cend(); }

  private:
    gtl::btree_map<IdPair, RiseSetArray> _accesses; 
};

} // namespace trace
} // namespace astrea
```


