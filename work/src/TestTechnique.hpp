#ifndef TESTTECHNIQUE_HPP
#define TESTTECHNIQUE_HPP

#include "ILightTechnique.hpp"

class TestTechnique : public ILightTechnique {
public:
  void initialize() override;
  void render(Scene &scene, Camera &camera) override;
  void cleanup() override;
};

#endif // TESTTECHNIQUE_HPP
