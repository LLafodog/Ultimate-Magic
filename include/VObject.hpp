#ifndef VOBJECT_H
#define VOBJECT_H

#include<EntityGraphic.hpp>

using namespace std;
using namespace sf;

class Object;
class Animation;

class VObject : public EntityGraphic
/**
   Graphic entity specialized in objects, draws a lifebar, the different animation regarding the orientation and so on.
**/
{
public:

  VObject(Object* o, RenderWindow* w);

  /// =============== CASUAL METHODS ==============
  virtual void update();
  void draw(bool details=false);


  /// =============== GETTER ======================
  const FloatRect getHitbox();
  Object* getObject() {return m_object;}
  bool isActive() {return m_active;}
  virtual const ConvexShape* getApparence(); //redefinition

  /// =============== CONVERSION ==================
  virtual const bool isVObject() {return true;}

  virtual ~VObject();

protected:
  void changeOrientation(char c);
  const void drawAboutAlive(bool details);
  const void drawLifeBar();


  vector<Animation*> m_animations;
  Object* m_object;
  RenderWindow* m_window;
  char m_orientation;
  bool m_active;


};

#endif // VOBJECT_H
