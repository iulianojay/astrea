#include <access/risesets/AccessArray.hpp>

namespace waveguide {
namespace accesslib {

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

void AccessArray::operator|(const AccessArray& other)
{
    for (const auto& [ids, risesets] : other) {
        if (contains(ids)) { _accesses[ids] = (risesets | _accesses[ids]); } // TODO: Should this modify in place? Copy?
    }
}

void AccessArray::operator&(const AccessArray& other)
{
    for (const auto& [ids, risesets] : other) {
        if (contains(ids)) { _accesses[ids] = (risesets & _accesses[ids]); }
    }
}

/**
 * @brief Overloads the output stream operator for the AccessArray.
 *
 * @param os The output stream.
 * @param accessArray The AccessArray to output.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const AccessArray& accessArray)
{
    for (const auto& [idPair, riseSetArray] : accessArray) {
        os << "(" << idPair.sender << ", " << idPair.receiver << ") -> " << riseSetArray << "\n";
    }
    return os;
}

} // namespace accesslib
} // namespace waveguide