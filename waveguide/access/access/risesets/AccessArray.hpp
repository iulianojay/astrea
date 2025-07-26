#pragma once

#include <parallel_hashmap/btree.h>

#include <access/risesets/RiseSetArray.hpp>

namespace waveguide {
namespace accesslib {

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

} // namespace accesslib
} // namespace waveguide

template <>
struct std::hash<waveguide::accesslib::IdPair> {
    std::size_t operator()(const waveguide::accesslib::IdPair& k) const
    {
        return (std::hash<std::size_t>()(k.sender)) ^ (std::hash<std::size_t>()(k.receiver));
    }
};

template <>
struct std::less<waveguide::accesslib::IdPair> {
    bool operator()(const waveguide::accesslib::IdPair& lhs, const waveguide::accesslib::IdPair& rhs) const
    {
        if (lhs.sender == rhs.sender) { return lhs.receiver < rhs.receiver; }
        else {
            return lhs.sender < rhs.sender;
        }
    };
};

namespace waveguide {
namespace accesslib {
class AccessArray {
  public:
    AccessArray()  = default;
    ~AccessArray() = default;

    RiseSetArray& operator[](const std::size_t& senderId, const std::size_t& receiverId)
    {
        return _accesses[IdPair(senderId, receiverId)];
    }

    const RiseSetArray& at(const std::size_t& senderId, const std::size_t& receiverId) const
    {
        return _accesses.at(IdPair(senderId, receiverId));
    }

    bool contains(const IdPair& idPair) const { return _accesses.contains(idPair); }

    void erase(const std::size_t& senderId, const std::size_t& receiverId)
    {
        _accesses.erase(IdPair(senderId, receiverId));
    }

    std::size_t size() const { return _accesses.size(); }

    // Union
    void operator|(const AccessArray& other)
    {
        for (const auto& [ids, risesets] : other) {
            if (contains(ids)) {
                _accesses[ids] = (risesets | _accesses[ids]);
            } // TODO: Should this modify in place? Copy?
        }
    }

    // Intersection
    void operator&(const AccessArray& other)
    {
        for (const auto& [ids, risesets] : other) {
            if (contains(ids)) { _accesses[ids] = (risesets & _accesses[ids]); }
        }
    }

    using iterator       = phmap::btree_map<IdPair, RiseSetArray>::iterator;
    using const_iterator = phmap::btree_map<IdPair, RiseSetArray>::const_iterator;

    iterator begin() { return _accesses.begin(); }
    iterator end() { return _accesses.end(); }
    const_iterator begin() const { return _accesses.begin(); }
    const_iterator end() const { return _accesses.end(); }
    const_iterator cbegin() const { return _accesses.cbegin(); }
    const_iterator cend() const { return _accesses.cend(); }

  private:
    phmap::btree_map<IdPair, RiseSetArray> _accesses;
};

} // namespace accesslib
} // namespace waveguide