#ifndef PHOTONMAPPING_HPP
#define PHOTONMAPPING_HPP

#include "ILightTechnique.hpp"

class PhotonMapping : public ILightTechnique {
public:
  void initialize() override;
  void render(Scene &scene, Camera &camera) override;
  void cleanup() override;
};

#endif // PHOTONMAPPING_HPP
