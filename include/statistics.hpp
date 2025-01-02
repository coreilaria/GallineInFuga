#ifndef STATISTICS_HPP
#define STATISTICS_HPP
namespace statistics {
struct Statistics {
  double mean_dist;
  double dev_dist;
  double mean_speed;
  double dev_speed;

  Statistics();
  Statistics(double, double, double, double);
};
}  // namespace statistics

#endif