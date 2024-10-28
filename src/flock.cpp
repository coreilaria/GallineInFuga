
#include "../include/flock.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include "../include/boid.hpp"
#include "../include/constants.hpp"
#include "../include/point.hpp"
#include "../include/sfml.hpp"

using namespace graphic_par;

Flock::Flock() {flock_.resize(N_);};
// Flock::Flock(std::vector<std::unique_ptr<Boid>> flock) { flock_.assign(flock.begin(), flock.end()); };

int Flock::get_size() const { return N_; };

// std::vector<Boid*> Flock::findNear(std::unique_ptr<Boid>& target) {
//   std::vector<Boid*> near;

//   // Usa std::copy_if per trovare i Boid vicini
//   std::copy_if(flock_.begin(), flock_.end(), std::back_inserter(near), [&](const std::unique_ptr<Boid>& other) {
//     return target != other && target->get_position().distance(other->get_position()) < d_;
//   });

//   return near;
// };

// std::vector<Boid*> Flock::findNear(std::unique_ptr<Boid>& target) {
//     std::vector<Boid*> near;

//     // Usa std::copy_if per trovare i Boid vicini
//     std::copy_if(flock_.begin(), flock_.end(), std::back_inserter(near), [&](const std::unique_ptr<Boid>& other) {
//         return target.get() != other.get() && target->get_position().distance(other->get_position()) < d_;
//     });

//     return near;
// };

// std::vector<Boid*> Flock::findNear(std::unique_ptr<Boid>& target) {
//         std::vector<Boid*> near;

//         // Usa std::copy_if per trovare i Boid vicini
//         std::copy_if(flock_.begin(), flock_.end(), std::back_inserter(near), [&](const std::unique_ptr<Boid>& other)
//         {
//             return target.get() != other.get() && target->get_position().distance(other->get_position()) < d_;
//         });

//         // Aggiungi i puntatori grezzi al vettore "near_raw"
//         std::vector<Boid*> near_raw;
//         for (const auto& boid_ptr : near) {
//             near_raw.push_back(boid_ptr.get());
//         }

//         return near_raw;
//     };
std::vector<Boid*> Flock::findNear(std::unique_ptr<Boid>& target) {
  std::vector<Boid*> near;
  // Usa std::copy_if per trovare i Boid vicini
  Boid* target_ptr = target.get();
  for (int i=0; i < N_; ++i ){
    if (target_ptr != flock_[i].get() && target_ptr->get_position().distance(flock_[i].get()->get_position()) < d_){
      near.push_back(flock_[i].get());
    }
  }
  return near;
  // Restituisce il vettore di puntatori
};

std::unique_ptr<Boid> Flock::update_boid(std::unique_ptr<Boid>& b) {
  // USARE ALGORITMO SE NON USIAMO QUAD-TREE
  Point p, v;
  p = b->get_position();
  v = b->get_velocity();

  std::vector<Boid*> near{this->findNear(b)};

  //   near = this->findNear(b);

  if (!near.empty()) {
    v += b->separation(s_, ds_, near) + b->alignment(a_, near) + b->cohesion(c_, near);
  }
  v = b->border(margin_, turnFactor_, v);
  b->friction(maxSpeed_, v);

  p += dt * v;

  //   Boid boid(p, v);
  //   std::unique_ptr<Boid> b_pointer = &boid;

  return std::make_unique<Boid>(p, v);
};

// void Flock::evolve() {
//   std::vector<std::unique_ptr<Boid>> flock_out;

//   flock_out = flock_;

//   for (int i = 0; i < static_cast<int>(N_); ++i) {
//     flock_out[i] = this->update_boid(flock_[i]);
//   }
//   flock_ = flock_out;
// // };
// void Flock::evolve() {
//   std::vector<std::unique_ptr<Boid>> flock_out;
//   flock_out.reserve(N_);  // Prealloca spazio per evitare riallocazioni

//   for (int i = 0; i < static_cast<int>(N_); ++i) {
//     // Usa std::make_unique per creare un nuovo unique_ptr per ogni Boid aggiornato
//     flock_out.push_back(std::make_unique<Boid>(this->update_boid(flock_[i].get())));
//   }

//   // Sostituisci flock_ con flock_out
//   flock_ = std::move(flock_out);
// };

void Flock::evolve() {
  std::vector<std::unique_ptr<Boid>> flock_out;
  flock_out.reserve(N_);  // Prealloca spazio per evitare riallocazioni

  for (int i = 0; i < static_cast<int>(N_); ++i) {
    // Aggiorna il Boid esistente e crea un nuovo unique_ptr con il risultato
    std::unique_ptr<Boid> updated_boid = this->update_boid(flock_[i]);
    flock_out.push_back(std::move(updated_boid));
  }

  // Sostituisci flock_ con flock_out
  flock_ = std::move(flock_out);
}

void Flock::generateBoid() {
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dist_pos_x(0., windowWidth);
  std::uniform_real_distribution<double> dist_pos_y(0., windowHeight);
  std::uniform_real_distribution<double> dist_vel(minVel, maxVel);

  std::generate(flock_.begin(), flock_.end(), [&]() {
    return std::make_unique<Boid>(Point(dist_pos_x(rng), dist_pos_y(rng)), Point(dist_vel(rng), dist_vel(rng)));
    // Boid b(Point(dist_pos_x(rng), dist_pos_y(rng)), Point(dist_vel(rng), dist_vel(rng)));
    // std::unique_ptr<Boid> pointer{&b};
    // return pointer;
  });
};

void Flock::vertex(std::vector<sf::Vertex>& vertices) {
  std::for_each(flock_.begin(), flock_.end(), [&, i = 0](const std::unique_ptr<Boid>& boid) mutable {
    vertices[i] = boid->get_position()();
    toSfmlCoord(vertices[i]);
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