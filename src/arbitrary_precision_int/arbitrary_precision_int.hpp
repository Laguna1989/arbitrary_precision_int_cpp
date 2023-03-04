#ifndef IMPLEMENTATION_HPP_GUARD
#define IMPLEMENTATION_HPP_GUARD
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace api {

class API {
public:
    /// Constructor
    /// \param values bytes composing the number
    explicit API(std::vector<std::uint8_t> const& values);
    /// Constructor
    /// \param values bytes composing the number
    explicit API(std::vector<std::uint8_t>&& values);
    /// Get the data from the class
    /// \return bytes composing the number
    [[nodiscard]] std::vector<std::uint8_t> const& get_data() const;

private:
    std::vector<std::uint8_t> m_data;
    void trim();
};

/// Compare two arbitrary precision integers for equality
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return true if lhs is equal to rhs, false otherwise
bool operator==(API const& lhs, API const& rhs);

/// Compare tow arbitrary precision integers for unequality
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return true if lhs is unequal to rhs, false otherwise
bool operator!=(API const& lhs, API const& rhs);

/// Addition of two ArbitraryPrecisionIntegers
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return the sum of lhs and rhs
API operator+(API const& lhs, API const& rhs);

/// Subtraction of two ArbitraryPrecisionIntegers
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return difference between lhs and rhs. If rhs > lhs, the API equivalent of 0 is returned
API operator-(API const& lhs, API const& rhs);

/// Multiplication of two ArbitraryPrecisionIntegers
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return product of lhs and rhs
API operator*(API const& lhs, API const& rhs);

/// Division of two ArbitraryPrecisionIntegers
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return quotient of lhs and rhs. if rhs is 0, the API equivalent of 0 is returned
API operator/(API const& lhs, API const& rhs);

/// Modulo of two ArbitraryPrecisonIntegers
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return modulo of lhs anr rhs. if rhs is 0, the API equivalent of 0 is returned
API mod(API const& lhs, API const& rhs);

///
/// \param lhs
/// \param rhs
/// \return
std::pair<API, API> div_mod(API const& lhs, API const& rhs);

/// Comparison of two ArbitraryPrecisionIntegers
/// \param lhs first arbitrary precision integer
/// \param rhs second arbitrary precision integer
/// \return will return -1 if lhs < rhs,  will return 0 if lhs == rhs, will return +1 if lhs > rhs
int compare(API const& lhs, API const& rhs);

/// Create a ArbitraryPrecisionInteger from an uint64_t
/// \param number the number to convert to an arbitraryPrecisionInteger
/// \return the API representation of the integer
API from_uint64(std::uint64_t number);

/// Convert an ArbitraryPrecisionInteger to a decimal string
/// \param api the arbitrary precision integer
/// \return the string representation of the arbitrary precision integer
std::string to_string(API const& api);

/// Convert an ArbitraryPrecisionInteger to a uint64_t
/// \param api the arbitrary precision integer
/// \return the uint64 representation of the arbitrary precision integer. If the arbitrary precision
/// integer is bigger than what a uint64_t can hold, uint64_t::max is returned.
std::uint64_t to_uint64(API const& api);

} // namespace api

#endif
