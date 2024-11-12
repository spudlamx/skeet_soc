//
//  storage.hpp
//  skeet_07_sep_des
//
//  Created by Spencer Lamoreaux on 11/6/24.
//

#ifndef storage_hpp
#define storage_hpp

#include <stdio.h>
#include <vector>
#include "position.h"
#include "time.h"
#include "gun.h"

// Forward declarations
class InterfaceElement;
class LogicElement;
class StorageEffects;
class Velocity;
class Time;
class Gun;
int randomInt(int min, int max);
double randomFloat(double min, double max);


// Base class for game elements
class StorageElement {
protected:
   Position pt;           // Position of the element
   Velocity v;            // Velocity of the element
   double radius;          // Radius (size) of the element
   int points;
   bool dead;              // Whether the element is "dead"
   LogicElement* pLogic;  // Pointer to the logic of the element
   InterfaceElement* pInterface;  // Pointer to the interface (for rendering)

public:
   StorageElement(LogicElement* logicElement, InterfaceElement* interfaceElement, int size)
      : pLogic(logicElement), pInterface(interfaceElement), pt(), v(), radius(size), dead(false) {
         
      }

   virtual ~StorageElement() {
      // Clean up resources (if necessary)
   }
   static Position dimensions;
   // setters
   void kill()                            { dead = true; }
   void setSize(int size)                 { radius = size; }
   void setPoints(int pts)                { points = pts; }
   
   void operator=(const Position    & rhs) { pt = rhs;    }
   void operator=(const Velocity & rhs) { v = rhs;     }

   // getters
   bool isDead()                    const { return dead;   }
   int getPoints()                  const { return points; }
   int getRadius()                  const { return radius; }
   Position* getPosition()                { return &pt;    }
   Velocity* getVelocity()                { return &v;      }
   LogicElement* getLogic()               { return pLogic; }
   InterfaceElement* getInterface()      { return pInterface; }
   void multiplyVel(double num)           {v *= num;}

};

// Class for birds in the game
class StorageBird : public StorageElement {
public:
   StorageBird(LogicElement* logicElement, InterfaceElement* interfaceElement, int size, double speed)
      : StorageElement(logicElement, interfaceElement, size) {
         // set the position: standard birds start from the middle
         pt.setY(randomFloat(dimensions.getY() * 0.25, dimensions.getY() * 0.75));
         pt.setX(0.0);

         // set the velocity
         v.setDx(randomFloat(speed - 0.5, speed + 0.5));
         v.setDy(randomFloat(-speed / 5.0, speed / 5.0));

         // set the points
         this->points = points;

         // set the size
         this->radius = radius;
      }
};

// Class for bullets in the game
class StorageBullet : public StorageElement {
public:
   StorageBullet(LogicElement* logicElement, InterfaceElement* interfaceElement, double angle, double speed, double radius, int value)
      : StorageElement(logicElement, interfaceElement, radius) {
         points = value;
         // set the initial position
         pt.setX(dimensions.getX() - 1.0);
         pt.setY(1.0);
         assert(pt.getX() > 100.0);

         // set the initial velocity
         v.setDx(-speed * cos(angle));
         v.setDy(speed * sin(angle));
         assert(v.getDx() <= 0.0);
         assert(v.getDy() >= 0.0);
      }
};

// Class for other effects (e.g., explosions, special effects, etc.)
class StorageEffects : public StorageElement {
public:
   StorageEffects(LogicElement* logicElement, InterfaceElement* interfaceElement, int size)
      : StorageElement(logicElement, interfaceElement, size) {}
};




// Storage class definition
class Storage {
   std::vector<StorageElement*> elements; // Stores all elements (birds, bullets, etc.)
   std::vector<StorageElement*> birds; // Stores all elements (birds, bullets, etc.)
   std::vector<StorageElement*> bullets; // Stores all elements (birds, bullets, etc.)
   size_t numbirds;                       // To track the number of birds
   int points;
   int numKilled;
   Time time;
   Gun gun;  // Ensure the Gun object is initialized explicitly

public:
   // Constructor with explicit initialization of Gun member
   Storage() : numbirds(0), points(0), numKilled(0), gun(Position(800.0, 0.0)), time() {}

   int getPoints() { return points; }
   int getNumKilled() { return numKilled; }
   int getNumMissed()  { return 0; }// This method needs implementation
   void addKilled(int num) {numKilled += num;}
   void addPoints(int num) {points += num;};

   // General iterator methods for all elements
   std::vector<StorageElement*>::iterator begin() {
       return elements.begin();
   }

   std::vector<StorageElement*>::iterator end() {
       return elements.end();
   }


   // Iterators for birds (StorageBird only)
   std::vector<StorageElement*>::iterator beginBird() {
      return birds.begin();
   }

   std::vector<StorageElement*>::iterator endBird() {
      return birds.end();
   }

   // Iterators for bullets (StorageBullet only)
   std::vector<StorageElement*>::iterator beginBullet() {
      return bullets.begin();
   }

   std::vector<StorageElement*>::iterator endBullet() {
      return bullets.end();
   }

   void addElement(StorageElement* element) {
      elements.push_back(element);
      
      // If the element is a bird, update the bird count
      if (dynamic_cast<StorageBird*>(element)) {
         birds.push_back(element);
         updateBirdCount();  // Update the bird count
      }
      
      if (dynamic_cast<StorageBullet*>(element)) {
         bullets.push_back(element);
         updateBirdCount();  // Update the bird count
      }
      // If the element is a bullet, no specific bird handling is needed
   }
   
   Gun* getGun(){ return &gun;}

   void reset() {
      elements.clear();  // Clear all elements (birds, bullets, effects, etc.)
      numbirds = 0;
   }

   Time* getTime() { return &time; }

   size_t getNumBirds() { return numbirds; }  // Use size_t for numbirds to match vector size

   void updateBirdCount() {
      // Update numbirds based on the elements list by counting StorageBirds
      numbirds = std::count_if(elements.begin(), elements.end(), [](StorageElement* el) {
         return dynamic_cast<StorageBird*>(el);  // Count birds
      });
   }
   std::vector<StorageElement*>::iterator erase(std::vector<StorageElement*>::iterator it) {
           return elements.erase(it);  // Delegate to std::vector's erase method
       }
   void andvanceTime() { time++ ;};
};

#endif /* storage_hpp */
