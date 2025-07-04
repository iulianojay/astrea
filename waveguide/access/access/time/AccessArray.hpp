#pragma once

#include <map>

#include <access/time/RiseSetArray.hpp>

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

template <>
struct std::hash<accesslib::IdPair> {
    std::size_t operator()(const accesslib::IdPair& k) const
    {
        return (std::hash<std::size_t>()(k.sender)) ^ (std::hash<std::size_t>()(k.receiver));
    }
};

template <>
struct std::less<accesslib::IdPair> {
    bool operator()(const accesslib::IdPair& lhs, const accesslib::IdPair& rhs) const
    {
        if (lhs.sender == rhs.sender) { return lhs.receiver < rhs.receiver; }
        else {
            return lhs.sender < rhs.sender;
        }
    };
};

namespace accesslib {
class AccessArray {
  public:
    AccessArray()  = default;
    ~AccessArray() = default;

    RiseSetArray& operator[](const std::size_t& senderId, const std::size_t& receiverId)
    {
        return _accesses[IdPair(senderId, receiverId)];
    }

    RiseSetArray& at(const std::size_t& senderId, const std::size_t& receiverId)
    {
        return _accesses.at(IdPair(senderId, receiverId));
    }

    std::size_t size() const { return _accesses.size(); }

    using iterator       = std::map<IdPair, RiseSetArray>::iterator;
    using const_iterator = std::map<IdPair, RiseSetArray>::const_iterator;

    iterator begin() { return _accesses.begin(); }
    iterator end() { return _accesses.end(); }
    const_iterator begin() const { return _accesses.begin(); }
    const_iterator end() const { return _accesses.end(); }
    const_iterator cbegin() const { return _accesses.cbegin(); }
    const_iterator cend() const { return _accesses.cend(); }

  private:
    std::map<IdPair, RiseSetArray> _accesses;
};

} // namespace accesslib