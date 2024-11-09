#ifndef NAMESPACE_HPP
#define NAMESPACE_HPP

namespace graphic_par {
const double dt = 0.7;

const float windowWidth = 1900.f;
const float windowHeight = 900.f;
const float statsWidth = 0.25 * windowWidth;

const double maxVel_x = 5.;
const double minVel_x = -maxVel_x;

const double maxVel_y = 3;
const double minVel_y = -maxVel_y;
}  // namespace graphic_par

#endif

// cmake -S ./ -B build -DBUILD_TESTING=True -DCMAKE_BUILD_TYPE=Debug
