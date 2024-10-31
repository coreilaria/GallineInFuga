#include "../include/statistics.hpp"


Statistics::Statistics(): mean_dist{0.}, mean_speed{0.}, dev_dist{0.}, dev_speed{0.} {};
Statistics::Statistics(double m_dist, double m_speed, double d_dist, double d_speed): mean_dist{m_dist}, mean_speed{m_speed}, dev_dist{d_dist}, dev_speed{d_speed} {};