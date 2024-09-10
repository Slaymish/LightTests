#ifndef THREEPASSTECHNIQUE_HPP
#define THREEPASSTECHNIQUE_HPP

#include "ILightTechnique.hpp"

class ThreePassTechnique : public ILightTechnique {
public:
  void initialize() override;
  void render(Scene &scene, Camera &camera) override;
  void cleanup() override;
};

#endif // THREEPASSTECHNIQUE_HPP
