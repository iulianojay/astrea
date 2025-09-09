#include <trace/risesets/AccessArray.hpp>

namespace astrea {
namespace trace {

RiseSetArray& AccessArray::operator[](const std::size_t& senderId, const std::size_t& receiverId)
{
    return _accesses[IdPair(senderId, receiverId)];
}

const RiseSetArray& AccessArray::at(const std::size_t& senderId, const std::size_t& receiverId) const
{
    return _accesses.at(IdPair(senderId, receiverId));
}

bool AccessArray::contains(const IdPair& idPair) const { return _accesses.contains(idPair); }

void AccessArray::erase(const std::size_t& senderId, const std::size_t& receiverId)
{
    _accesses.erase(IdPair(senderId, receiverId));
}

std::size_t AccessArray::size() const { return _accesses.size(); }

AccessArray& AccessArray::operator|(const AccessArray& other)
{
    for (const auto& [ids, risesets] : other) {
        if (contains(ids)) { _accesses[ids] = (risesets | _accesses[ids]); } // TODO: Should this modify in place? Copy?
    }
    return *this;
}

AccessArray AccessArray::operator|(const AccessArray& other) const
{
    AccessArray result = *this;
    result | other;
    return result;
}

AccessArray& AccessArray::operator&(const AccessArray& other)
{
    for (const auto& [ids, risesets] : other) {
        if (contains(ids)) { _accesses[ids] = (risesets & _accesses[ids]); }
    }
    return *this;
}

AccessArray AccessArray::operator&(const AccessArray& other) const
{
    AccessArray result = *this;
    result & other;
    return result;
}

/**
 * @brief Overloads the output stream operator for the AccessArray.
 *
 * @param os The output stream.
 * @param accessarray The AccessArray to output.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const AccessArray& accessarray)
{
    for (const auto& [idPair, riseSetArray] : accessarray) {
        os << "(" << idPair.sender << ", " << idPair.receiver << ") -> " << riseSetArray << "\n";
    }
    return os;
}

} // namespace trace
} // namespace astrea