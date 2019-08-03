#pragma once

#include <cstdint>
#include <array>
#include <limits>

#include <zenload/zTypes.h>

class Npc;
class World;
class WayPoint;

class MoveAlgo final {
  public:
    MoveAlgo(Npc& unit);

    void tick(uint64_t dt);
    void multSpeed(float s){ mulSpeed=s; }
    void clearSpeed();

    static bool isClose(const std::array<float,3>& w,const WayPoint& p);
    static bool isClose(float x,float y,float z,const WayPoint& p);

    auto aiGoTarget() -> const WayPoint* { return currentGoTo; }
    bool aiGoTo(const WayPoint* p);
    bool aiGoTo(const Npc* p, float destDist);
    void aiGoTo(const std::nullptr_t p);
    bool startClimb();
    bool hasGoTo() const;

    bool isFaling() const;
    bool isSlide()  const;
    bool isFrozen() const;
    bool isInAir()  const;
    bool isClimb()  const;

    uint8_t groundMaterial() const;

  private:
    void tickMobsi  (uint64_t dt);
    bool tickSlide  (uint64_t dt);
    void tickGravity(uint64_t dt);
    bool tryMove    (float x, float y, float z);

    enum Flags : uint32_t {
      NoFlags=0,
      Frozen =1<<1,
      InAir  =1<<2,
      Faling =1<<3,
      Slide  =1<<4,
      Climb  =1<<5
      };

    void   setAsFrozen(bool f);
    void   setInAir(bool f);
    void   setAsClimb(bool f);
    void   setAsSlide(bool f);

    bool   processClimb();
    bool   slideDir() const;
    void   onMoveFailed();
    float  dropRay  (float x, float y, float z, bool &hasCol) const;
    auto   normalRay(float x, float y, float z) const -> std::array<float,3>;
    void   applyRotation(std::array<float,3> &out, float *in) const;
    auto   animMoveSpeed(uint64_t dt) const -> std::array<float,3>;
    auto   npcMoveSpeed (uint64_t dt) -> std::array<float,3>;

    float  stepHeight()  const;
    float  slideAngle()  const;
    float  slideAngle2() const;

    Npc&                npc;
    const WayPoint*     currentGoTo   =nullptr;
    const Npc*          currentGoToNpc=nullptr;

    struct Cache {
      float x=0,y=0,z=std::numeric_limits<float>::infinity();
      float rayCastRet=0; bool hasCol=false;

      float nx=0,ny=0,nz=std::numeric_limits<float>::infinity();
      std::array<float,3> norm={};
      };
    mutable Cache       cache;

    float               mulSpeed  =1.f;
    std::array<float,3> fallSpeed ={};
    float               fallCount=0.f;
    std::array<float,3> aniSpeed  ={};

    uint64_t            climbStart=0;
    std::array<float,3> climbPos0={};
    float               climbHeight=0.f;
    Flags               flags=NoFlags;

    static const float closeToPointThreshold;
    static const float gravity;
  };
