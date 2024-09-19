#ifndef THREEPASSTECHNIQUE_HPP
#define THREEPASSTECHNIQUE_HPP

#include "ILightTechnique.hpp"

class ThreePassTechnique : public ILightTechnique {
private:
  Scene *scene;

public:
  void initialize(Scene &scene) override;
  void render(Camera *camera) override;
  void cleanup() override;
};

#endif // THREEPASSTECHNIQUE_HPP
