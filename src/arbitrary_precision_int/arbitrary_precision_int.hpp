#ifndef IMPLEMENTATION_HPP_GUARD
#define IMPLEMENTATION_HPP_GUARD
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace api {

class API {
public:
    /// Default constructor
    API();

    /// Destructor
    ~API() = default;

    /// Copy constructor
    API(API const&) = default;
    /// Move constructor
    API(API&&) noexcept = default;

    /// Copy assignment operator
    API& operator=(const API& other) = default;
    /// Move assignment operator
    API& operator=(API&& other) noexcept = default;

    /// Constructor
    /// \param values bytes composing the number
    explicit API(std::vector<std::uint16_t> const& values);
    /// Constructor
    /// \param values bytes composing the number
    explicit API(std::vector<std::uint16_t>&& values);
    /// Get the data from the class
    /// \return bytes composing the number
    [[nodiscard]] std::vector<std::uint16_t> const& get_data() const;

    /// Convert the arbitrary precision integer to a string. Uses internal cache to avoid
    /// re-calculation of string.
    /// \return string representation of the arbitrary precision integer
    std::string to_string() const;

    /// Convert the arbitrary precision integer to a si string. Uses an internal cache to avoid
    /// recalculation of the string.
    /// \return si string representation of the arbitrary precision integer
    std::string to_exp_string() const;

private:
    std::vector<std::uint16_t> m_data;

    mutable std::string m_string_representation;
    mutable std::string m_exp_string_representation;
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
API operator%(API const& lhs, API const& rhs);

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

/// Convert an ArbitraryPrecisionInteger to a uint64_t
/// \param api the arbitrary precision integer
/// \return the uint64 representation of the arbitrary precision integer. If the arbitrary precision
/// integer is bigger than what a uint64_t can hold, uint64_t::max is returned.
std::uint64_t to_uint64(API const& api);

} // namespace api

#endif
