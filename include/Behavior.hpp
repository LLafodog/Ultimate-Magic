#ifndef BEHAVIOR_H
#define BEHAVIOR_H

class Object;

class Behavior
/**
    Virtual class that will consist in the core of AI.
**/
{
    public:
        Behavior(Object* o=nullptr);

        /// ======== SETTER ============
        virtual void setObject(Object* o)=0;

        /// ======== GETTER =============
        virtual Object* getObject()=0;

        /// ======== CASUALS ============
        virtual void think()=0;
        virtual void update()=0;

        virtual ~Behavior();
    protected:
    Object* m_object;
};

#endif // BEHAVIOR_H
