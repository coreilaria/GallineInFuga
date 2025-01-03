#include "../include/statistics.hpp"

namespace statistics {

Statistics::Statistics() : meanDist{0.}, devDist{0.}, meanSpeed{0.}, devSpeed{0.} {}
Statistics::Statistics(const double m_dist, const double d_dist, const double m_speed, const double d_speed)
    : meanDist{m_dist}, devDist{d_dist}, meanSpeed{m_speed}, devSpeed{d_speed} {}
}  // namespace statistics