#ifndef IMPLEMENTATION_HPP_GUARD
#define IMPLEMENTATION_HPP_GUARD
#include <cstdint>
#include <vector>

namespace api {

class API {
public:
    /// TODO
    API(std::vector<std::uint8_t> const& values);
    API(std::vector<std::uint8_t>&& values);
    /// TODO
    std::vector<std::uint8_t> const& get_data() const;

private:
    std::vector<std::uint8_t> m_data;
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

/// multipication of two ArbitraryPrecisionIntegers
/// TODO
/// \param lhs
/// \param rhs
/// \return
API operator*(API const& lhs, API const& rhs);

// will return -1 if lhs < rhs
// will return 0 if lhs == rhs
// will return +1 if lhs > rhs
int compare(API const& lhs, API const& rhs);

/// TODO
API from_int(std::uint64_t number);

} // namespace api

#endif
