//
//  interface.hpp
//  skeet_07_sep_des
//
//  Created by Spencer Lamoreaux on 11/6/24.
//

#ifndef interface_hpp
#define interface_hpp
class Position;

#include <stdio.h>
#include "position.h"
#include "uiInteract.h"
#include "logic.hpp"
#include "gun.h"
#include "time.h"
#include "score.h"
#include "points.h"




class InterfaceElement {
public:
   virtual void draw(StorageElement* se) = 0 ;
};
class InterfacePellet : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};
class InterfaceMissile : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};
class InterfaceBomb : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};
class InterfaceShrapnel : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};
class InterfaceStandard : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};
class InterfaceFloater : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};
class InterfaceSinker : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};
class InterfaceCrazy : public InterfaceElement {
public:
   virtual void draw(StorageElement* se) override;
};



// Forward declare Logic and StorageElement to avoid circular dependency

class Interface {
   Logic logic;  // Use a pointer to Logic (no need to include logic.hpp here)
   void drawLevel();
   void drawBackground(double redBack, double greenBack, double blueBack) const;
   void drawTimer(double percent, double redFore, double greenFore, double blueFore,
                  double redBack, double greenBack, double blueBack) const;
   void drawStatus();
   void drawBullseye(double angle) const;
   
public:
   Interface(): logic(*new Logic){}
   void input(const UserInput & ui);
   void processing();
   void output() {
      
       // Render elements
      if (logic.isPlaying())
         drawLevel();
      else
          drawStatus();
   }
};

#endif /* interface_hpp */
