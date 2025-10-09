/*
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

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