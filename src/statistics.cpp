#include "../include/statistics.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "TCanvas.h"
#include "TH1D.h"

Statistics::Statistics() : mean_dist{0.}, dev_dist{0.}, mean_speed{0.}, dev_speed{0.} {};
Statistics::Statistics(double m_dist, double d_dist, double m_speed, double d_speed)
    : mean_dist{m_dist}, dev_dist{d_dist}, mean_speed{m_speed}, dev_speed{d_speed} {};

// evito di chiamare 4 volte accumulate

std::array<TH1D, 2> Statistics::histogram(Flock& f) {
  const std::vector<std::unique_ptr<Boid>>& flock = f.get_flock();  // alias

  TH1D h_dist;
  TH1D h_speed;
  double speedMax{0.};
  double distMax{0.};

  for (std::vector<std::unique_ptr<Boid>>::const_iterator it = flock.begin(); it != flock.end(); ++it) {
    std::for_each(it, flock.end(), [&it, &h_dist, &distMax](const std::unique_ptr<Boid>& boid) {
      if (distMax <= boid->get_position().distance((*it)->get_position())) {
        distMax = boid->get_position().distance((*it)->get_position());
      }
      h_dist.Fill(boid->get_position().distance((*it)->get_position()));
    });
  }

  std::for_each(flock.begin(), flock.end(), [&h_speed, &speedMax](const std::unique_ptr<Boid>& boid) {
    if (speedMax <= boid->get_velocity().module()) {
      speedMax = boid->get_velocity().module();
    }
    h_speed.Fill(boid->get_velocity().module());
  });

  h_dist.SetTitle("Distances");
  h_dist.SetBins(50, 0, distMax);

  h_speed.SetTitle("Speeds");
  h_speed.SetBins(50, 0, speedMax);

  std::array<TH1D, 2> h{h_dist, h_speed};

  TCanvas c1("c1", "Distances");
  c1.cd();
  h_dist.Draw();
  c1.SaveAs("histo_distances.png");

  TCanvas c2("c2", "Speeds");
  c2.cd();
  h_speed.Draw();
  c2.SaveAs("histo_speeds.png");

  return h;
};
std::array<sf::Sprite, 2> Statistics::drawHisto(float textHeight) {
  sf::Texture t1, t2;
  sf::Sprite s1, s2;

  if (!t1.loadFromFile("../build/histo_distances.png")) {
    std::cerr << "Cannot load histo_distances.png";
  }
  if (!t2.loadFromFile("../build/histo_speeds.png")) {
    std::cerr << "Cannot load histo_speeds.png";
  }
  s1.setTexture(t1);
  s2.setTexture(t2);

  s1.setPosition(0, textHeight + 20);
  s2.setPosition(0, textHeight + 20 + t1.getSize().y + 10);

  return {s1, s2};
};

Statistics Statistics::flockStatistics(Flock& f) {
  double mean_dist{this->histogram(f)[0].GetMean()};
  double dev_dist{this->histogram(f)[0].GetMeanError()};

  double mean_speed{this->histogram(f)[1].GetMean()};
  double dev_speed{this->histogram(f)[1].GetMeanError()};

  return Statistics(mean_dist, dev_dist, mean_speed, dev_speed);
};
