#ifndef IMPLEMENTATION_HPP_GUARD
#define IMPLEMENTATION_HPP_GUARD
#include <cstdint>
#include <string>
#include <vector>

namespace api {

class API {
public:
    /// TODO
    explicit API(std::vector<std::uint8_t> const& values);
    explicit API(std::vector<std::uint8_t>&& values);
    /// TODO
    std::vector<std::uint8_t> const& get_data() const;

private:
    std::vector<std::uint8_t> m_data;

    void trim();
};

/// TODO
bool operator==(API const& lhs, API const& rhs);

/// TODO
bool operator!=(API const& lhs, API const& rhs);

/// addition of two ArbitraryPrecisionIntegers
/// TODO
/// \param lhs
/// \param rhs
/// \return
API operator+(API const& lhs, API const& rhs);

/// subtraction of two ArbitraryPrecisionIntegers
/// TODO
/// \param lhs
/// \param rhs
/// \return
API operator-(API const& lhs, API const& rhs);

/// multiplication of two ArbitraryPrecisionIntegers
/// TODO
/// \param lhs
/// \param rhs
/// \return
API operator*(API const& lhs, API const& rhs);

/// TODO
/// \param lhs
/// \param rhs
/// \return
API operator/(API const& lhs, API const& rhs);

///
/// \param lhs
/// \param rhs
/// \return
API mod(API const& lhs, API const& rhs);

// will return -1 if lhs < rhs
// will return 0 if lhs == rhs
// will return +1 if lhs > rhs
/// TODO
/// \param lhs
/// \param rhs
/// \return
int compare(API const& lhs, API const& rhs);

/// TODO
/// \param number
/// \return
API from_int(std::uint64_t number);

///
/// \param api
/// \return
std::string to_string(API const& api);

///
/// \param api
/// \return
std::uint64_t to_uint64(API const& api);

} // namespace api

#endif
