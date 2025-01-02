#include "../include/statistics.hpp"

Statistics::Statistics() : mean_dist{0.}, dev_dist{0.}, mean_speed{0.}, dev_speed{0.} {}
Statistics::Statistics(const double m_dist, const double d_dist, const double m_speed, const double d_speed)
    : mean_dist{m_dist}, dev_dist{d_dist}, mean_speed{m_speed}, dev_speed{d_speed} {}