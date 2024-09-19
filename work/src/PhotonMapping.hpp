#ifndef PHOTONMAPPING_HPP
#define PHOTONMAPPING_HPP

#include "ILightTechnique.hpp"

class PhotonMapping : public ILightTechnique {
private:
  Scene *scene;

public:
  void initialize(Scene &scene) override;
  void render(Camera *camera) override;
  void cleanup() override;
};

#endif // PHOTONMAPPING_HPP
