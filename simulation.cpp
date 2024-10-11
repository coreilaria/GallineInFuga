#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "boid.hpp"
#include "constants.hpp"
#include "point.hpp"
#include "quadtree.hpp"

int main() {
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dist_pos(minPos, maxPos);
  std::uniform_real_distribution<double> dist_vel(minVel, maxVel);

  std::vector<Boid> flock(N);

  std::generate(flock.begin(), flock.end(),
                [&]() { return Boid(Point(dist_pos(rng), dist_pos(rng)), Point(dist_vel(rng), dist_vel(rng))); });

  int c = 0;

  do {
    for (int j = 0; j < N; ++j) {
      std::vector<Boid> near;
      flock[j].update(flock, near);
      c++;
    }
  } while (c < 100);
}