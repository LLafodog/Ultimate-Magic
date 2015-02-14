#ifndef MOVABLE_H
#define MOVABLE_H

#include<Positionnable.hpp>

class World;

class Movable : public Positionnable
/**
   Something that has a position can possibly move, here we do everything that regard the movement.
**/
{
public:

  Movable(World* w,float x=0, float y=0, float width=TILE_WIDTH, float height=TILE_HEIGHT);

  /// ============ METHODS =============
  void moveOn(float x, float y, bool changeOrientation=true);
  void moveOnF(int nSpeedX, int nSpeedY, bool changeOrientation=true) {moveOn(nSpeedX*m_effectiveSpeed,nSpeedY*m_effectiveSpeed,changeOrientation);}

  /// ============ GETTER =============
  const bool isMoving() {return m_isMoving;}
  const bool isMovingRight() {return m_isMoving && m_orientation=='e';}
  const bool isMovingLeft() {return m_isMoving && m_orientation=='w';}
  const bool isMovingUp() {return m_isMoving && m_orientation=='n';}
  const bool isMovingDown() {return m_isMoving && m_orientation=='s';}
  const void hasMoved() {m_isMoving=false;}
  const char getOrientation() {return m_orientation;}
  const float getSpeed() {return m_speed;}
  const float getEffectiveSpeed() {return m_speed;}
  void setSpeedFactor(float factor) {m_effectiveSpeed*=factor;}

  /// ============ SETTER =================
  void restoreSpeed() {m_effectiveSpeed=m_speed;}
  void initSpeed(float val) {m_speed=val; m_effectiveSpeed=val;}
  virtual ~Movable();

protected:

  World* m_world;
  float m_speed;
  float m_effectiveSpeed;
  bool m_isMoving;
  char m_orientation;
};

#endif // MOVABLE_H
