#pragma once

#include <unordered_map>

#include <access/time/RiseSetArray.hpp>

namespace accesslib {

struct IdPair {
    size_t sender;
    size_t receiver;

    IdPair() = default;
    IdPair(size_t sender, size_t receiver) :
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

namespace accesslib {

class AccessArray {
  public:
    AccessArray()  = default;
    ~AccessArray() = default;

    RiseSetArray& operator[](const size_t& senderId, const size_t& receiverId)
    {
        return accesses[IdPair(senderId, receiverId)];
    }

    RiseSetArray& at(const size_t& senderId, const size_t& receiverId)
    {
        return accesses.at(IdPair(senderId, receiverId));
    }

  private:
    std::unordered_map<IdPair, RiseSetArray> accesses;
};

} // namespace accesslib