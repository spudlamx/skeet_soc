//
//  logic.hpp
//  skeet_07_sep_des
//
//  Created by Spencer Lamoreaux on 11/6/24.
//

#ifndef logic_hpp
#define logic_hpp
#include "storage.hpp"

#include <stdio.h>
#include "storage.hpp"
#include "uiInteract.h"


class Logic {
   
public:
   Storage storage;
   Logic() : storage() {}
   bool bullseye;
   bool isBullsey() { return bullseye;}
   void advance();
   void spawn();
   void input(const UserInput & ui);
   std::vector<StorageElement*>::iterator begin()                { return storage.begin();                    };   //Iterator
   std::vector<StorageElement*>::iterator end()                  { return storage.end();                      }; //Iterator
//   int getFramesLeft()                    { return storage.getTime()->framesLeft;  };
   int getScore()                         { return storage.getPoints();                }
   Time* getTime()                        { return storage.getTime();                  };
   int getLevelNumber()                   { return storage.getTime()->level();         };
   double getGunAngle()                   { return storage.getGun()->getAngle();       };
   bool isPlaying()                       { return storage.getTime()->isPlaying();     };
   bool isGameOver()                      { return getLevelNumber() == 0;              };
   double getPercentLeft()                { return storage.getTime()->percentLeft();   };
   

   
};


class LogicElement {
public:
   virtual ~LogicElement() = default; // Virtual destructor for proper cleanup of derived classes
   virtual void advance(StorageElement* se) = 0;
   virtual void turn(StorageElement* se, const UserInput & ui) {};
   bool isOutOfBounds(StorageElement* se) const
   {
      Position* pt = se->getPosition();
      int radius = se->getRadius();
      Position dimensions = se->dimensions;
      
      return (pt->getX() < -radius || pt->getX() >= dimensions.getX() + radius ||
              pt->getY() < -radius || pt->getY() >= dimensions.getY() + radius);
   }
   
};

class LogicPellet : public LogicElement {
public:
    void advance(StorageElement* se) override;
};

class LogicMissile : public LogicElement {
public:
    void advance(StorageElement* se) override;
    void turn(StorageElement* se, const UserInput & ui) override;
};

class LogicBomb : public LogicElement {
   int timeToDie = 60;
public:
    void advance(StorageElement* se) override;
};

class LogicStandard : public LogicElement {
public:
    void advance(StorageElement* se) override;
};

class LogicFloater : public LogicElement {
public:
    void advance(StorageElement* se) override;
};

class LogicSinker : public LogicElement {
public:
    void advance(StorageElement* se) override;
};

class LogicCrazy : public LogicElement {
public:
    void advance(StorageElement* se) override;
};

#endif /* logic_hpp */


