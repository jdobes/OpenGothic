#pragma once

#include <Tempest/Event>
#include <Tempest/Matrix4x4>
#include <Tempest/Point>
#include <array>
#include <daedalus/DaedalusStdlib.h>

class World;
class Npc;
class Gothic;

class Camera final {
  public:
    Camera(Gothic& gothic);

    void setWorld(const World* w);

    void changeZoom(int delta);
    Tempest::PointF getSpin() const { return spin; }

    void rotateLeft ();
    void rotateRight();

    void moveForward();
    void moveBack();
    void moveLeft();
    void moveRight();

    void follow(const Npc& npc, uint64_t dt, bool includeRot);

    void setPosition(float x,float y,float z);
    void setSpin(const Tempest::PointF& p);

    Tempest::Matrix4x4 view() const;
    Tempest::Matrix4x4 viewShadow(const std::array<float,3> &ldir) const;

  private:
    Gothic&               gothic;
    std::array<float,3>   camPos={};
    std::array<float,3>   camBone={};
    Tempest::PointF       spin;
    float                 zoom=1.f;
    float                 dist=0.f;

    const World*          world=nullptr;
    bool                  hasPos=false;

    void implMove(Tempest::KeyEvent::KeyType t);
    Tempest::Matrix4x4 mkView(float dist) const;

    const Daedalus::GEngineClasses::CCamSys& cameraDef() const;
  };
