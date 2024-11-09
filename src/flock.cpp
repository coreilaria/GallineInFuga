
#include "../include/flock.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include "../include/boid.hpp"
#include "../include/namespace.hpp"
#include "../include/point.hpp"
#include "../include/statistics.hpp"

using namespace graphic_par;

Flock::Flock() { flock_.resize(N_); };

int Flock::get_size() const { return N_; };

std::vector<Boid*> Flock::findNear(std::unique_ptr<Boid>& target) {
  std::vector<Boid*> near;
  Boid* target_ptr = target.get();

  for (int i = 0; i < N_; ++i) {
    if (target_ptr != flock_[i].get() && target_ptr->get_position().distance(flock_[i].get()->get_position()) < d_) {
      near.push_back(flock_[i].get());
    }
  }
  return near;
};

std::unique_ptr<Boid> Flock::update_boid(std::unique_ptr<Boid>& b) {
  Point p, v;
  p = b->get_position();
  v = b->get_velocity();

  std::vector<Boid*> near{this->findNear(b)};

  if (!near.empty()) {
    v += b->separation(s_, ds_, near) + b->alignment(a_, near) + b->cohesion(c_, near);
  }
  v = b->border(margin_, turnFactor_, v);
  b->friction(maxSpeed_, v);
  b->boost(minSpeed_, v);

  p += dt * v;

  return std::make_unique<Boid>(p, v);
};

void Flock::evolve() {
  std::vector<std::unique_ptr<Boid>> flock_out;
  flock_out.reserve(N_);  // Prealloca spazio per evitare riallocazioni

  for (int i = 0; i < static_cast<int>(N_); ++i) {
    // Aggiorna il Boid esistente e crea un nuovo unique_ptr con il risultato
    std::unique_ptr<Boid> updated_boid = this->update_boid(flock_[i]);
    flock_out.push_back(std::move(updated_boid));
  }

  flock_ = std::move(flock_out);
}

void Flock::generateBoid() {
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dist_pos_x(statsWidth, windowWidth);
  std::uniform_real_distribution<double> dist_pos_y(0., windowHeight);
  std::uniform_real_distribution<double> dist_vel_x(minVel_x, maxVel_x);
  std::uniform_real_distribution<double> dist_vel_y(minVel_y, maxVel_y);

  std::generate(flock_.begin(), flock_.end(), [&]() {
    return std::make_unique<Boid>(Point(dist_pos_x(rng), dist_pos_y(rng)), Point(dist_vel_x(rng), dist_vel_y(rng)));
  });
};

void Flock::vertex(std::vector<sf::Vertex>& vertices) {
  std::for_each(flock_.begin(), flock_.end(), [&, i = 0](const std::unique_ptr<Boid>& boid) mutable {
    vertices[i] = boid->get_position()();
    // toSfmlCoord(vertices[i]);
    ++i;
  });
};

void Flock::print() {
  if (flock_.empty() == true) {
    std::cout << "E' VUOTO AAAAAAAH";
  } else {
    std::cout << "Contenuto del flock_: ";
    for (size_t i = 0; i < flock_.size(); ++i) {
      std::cout << flock_[i].get() << " ";
    }
    std::cout << std::endl;
  }
};

std::vector<sf::VertexArray> Flock::createTriangle(std::vector<sf::Vertex>& vertices) {
  this->vertex(vertices);

  sf::VertexArray triangle(sf::Triangles, 3);
  std::vector<sf::VertexArray> triangle_vec(N_);

  // Calcolo delle posizioni dei vertici
  for (int i = 0; i < N_; ++i) {
    triangle[0].position = vertices[i].position + sf::Vector2f(0, -height_ / 2);  // Vertice superiore (centrato)
    triangle[1].position =
        vertices[i].position + sf::Vector2f(-baseWidth_ / 2, height_ / 2);  // Vertice in basso a sinistra
    triangle[2].position =
        vertices[i].position + sf::Vector2f(baseWidth_ / 2, height_ / 2);  // Vertice in basso a destra

    float theta = flock_[i]->get_velocity().angle();

    // Ruota il triangolo attorno al centro
    for (int j = 0; j < 3; ++j) {
      sf::Vector2f pos = triangle[j].position - vertices[i].position;  // Posizione relativa al centro
      triangle[j].position = vertices[i].position + sf::Vector2f(pos.x * std::cos(theta) - pos.y * std::sin(theta),
                                                                 pos.x * std::sin(theta) + pos.y * std::cos(theta));
      triangle[j].color = color_;
    }
    triangle_vec[i] = triangle;
  }

  return triangle_vec;
};

// evito di chiamare 4 volte accumulate
Statistics Flock::statistics() {
  double mean_dist{0.};
  double mean_dist2{0.};

  for (std::vector<std::unique_ptr<Boid>>::iterator it = flock_.begin(); it != flock_.end(); ++it) {
    std::array<double, 2> sum = std::accumulate(it, flock_.end(), std::array<double, 2>{0., 0.},
                                                [&it](std::array<double, 2>& acc, const std::unique_ptr<Boid>& boid) {
                                                  acc[0] += (boid->get_position().distance((*it)->get_position()));
                                                  acc[1] +=
                                                      std::pow(boid->get_position().distance((*it)->get_position()), 2);
                                                  return acc;
                                                });
    mean_dist += sum[0] / (N_ * (N_ - 1) / 2);
    mean_dist2 += sum[1] / (N_ * (N_ - 1) / 2);
  }

  double dev_dist = std::sqrt((mean_dist2 - std::pow(mean_dist, 2)));

  double mean_speed{0.};
  double mean_speed2{0.};

  std::array<double, 2> sum = std::accumulate(flock_.begin(), flock_.end(), std::array<double, 2>{0., 0.},
                                              [](std::array<double, 2>& acc, const std::unique_ptr<Boid>& boid) {
                                                acc[0] += boid->get_velocity().module();
                                                acc[1] += std::pow(boid->get_velocity().module(), 2);

                                                return acc;
                                              });

  mean_speed = sum[0] / N_;
  mean_speed2 = sum[1] / N_;

  double dev_speed = std::sqrt((mean_speed2) - (std::pow(mean_speed, 2)));

  return Statistics(mean_dist, dev_dist, mean_speed, dev_speed);
};