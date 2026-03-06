

# File AccessObject.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**AccessObject.hpp**](AccessObject_8hpp.md)

[Go to the documentation of this file](AccessObject_8hpp.md)


```C++

#pragma once

#include <memory>

#include <trace/risesets/AccessArray.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

class AccessObject {

  protected:
    AccessObject() = default;

    virtual ~AccessObject() = default;

  public:
    void add_access(const std::size_t& receiverId, const RiseSetArray& access)
    {
        if (_accesses.contains({ get_id(), receiverId })) {
            _accesses[get_id(), receiverId] = (_accesses[get_id(), receiverId] | access);
        }
        else {
            _accesses[get_id(), receiverId] = access;
        }
    }

    void drop_access(const std::size_t& receiverId, const RiseSetArray& access)
    {
        _accesses.erase(get_id(), receiverId);
    }

    AccessArray& get_accesses() { return _accesses; }

    const AccessArray& get_accesses() const { return _accesses; }

    virtual std::size_t get_id() const = 0;

  private:
    AccessArray _accesses; 
};

} // namespace trace
} // namespace astrea
```


