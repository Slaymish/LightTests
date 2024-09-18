#ifndef TESTTECHNIQUE_HPP
#define TESTTECHNIQUE_HPP

#include "ILightTechnique.hpp"

class TestTechnique : public ILightTechnique {
private:
  Scene *scene; 

public:
  void initialize(Scene &scene) override;
  void render(Camera &camera) override;
  void cleanup() override;
};

#endif // TESTTECHNIQUE_HPP
