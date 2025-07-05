#pragma once

#include <unordered_map>

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

  private:
    std::unordered_map<IdPair, RiseSetArray> _accesses;
};

} // namespace accesslib