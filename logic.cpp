//
//  logic.cpp
//  skeet_07_sep_des
//
//  Created by Spencer Lamoreaux on 11/6/24.
//

#include "logic.hpp"
#include "interface.hpp"
#include "storage.hpp"



void Logic::advance() {
   // Advance each element (bird, bullet, etc.)
   storage.andvanceTime();
   Time* time = storage.getTime();
   
   // if status, then do not move the game
   if (time->isStatus())
   {
      // get rid of the bullets and the birds without changing the score
      storage.reset();
      return;
   }
   
   // spawn
   spawn();
   
   // move the birds and the bullets
   for (auto elem = storage.begin(); elem != storage.end(); ++elem) {
            auto logic = (*elem)->getLogic();  // Dereference to get the StorageElement
            if (logic) {
               logic->advance(*elem);  // Call the specific advance logic for each element
            }
         }
   
   
   // hit detection
   for (auto element = storage.beginBird(); element != storage.endBird(); ++element) {
       for (auto bullet = storage.beginBullet(); bullet != storage.endBullet(); ++bullet) {
           // Dereference to access the actual object
           if (!(*element)->isDead() && !(*bullet)->isDead() &&
               (*element)->getRadius() + (*bullet)->getRadius() >
               minimumDistance(*(*element)->getPosition(), *(*element)->getVelocity(),
                               *(*bullet)->getPosition(), *(*bullet)->getVelocity())) {
               
               // Create fragments and push them to the effects vector
//               for (int i = 0; i < 25; i++) {
//                   effects.push_back(new Fragment((*bullet)->getPosition(), (*bullet)->getVelocity()));
//               }
               
               // Handle element and bullet death, points update, and hit ratio
               (*element)->kill();
               (*bullet)->kill();
              storage.addKilled(1);
               
               // Update the bullet's value and element's points
              (*bullet)->setPoints(-(*element)->getPoints());
               (*element)->setPoints(0);
           }
       }
   }

   
   // remove the zombie birds
   for (auto it = begin(); it != end();)
      if ((*it)->isDead())
      {
         storage.addPoints((*it)->getPoints());
         it = storage.erase(it);
      }
      else
         ++it;
}




/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max) 
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

int randomInt(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}
double randomFloat(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}

void Logic::spawn()
{
   double size;
   int level = storage.getTime()->level();
   
   // Now handle spawning of birds based on the level and available bird types
   switch (level)
   {
      // Level 1: Big birds
      case 1:
         size = 30.0;
         // Spawn when there are no birds on screen, with a random chance
         if (storage.getNumBirds() == 0 && random(0, 15) == 1)
               storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));

         // Spawn every 4 seconds
         if (random(0, 4 * 30) == 1)
            storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));
         break;

      // Level 2: Two kinds of birds (Standard, Sinker)
      case 2:
      size = 25.0;
         // Spawn when there are no birds on screen, with a random chance
         if (storage.getNumBirds() == 0 && random(0, 15) == 1)
               storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));

         // Spawn every 4 seconds
         if (random(0, 4 * 30) == 1)
            storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));

         // Spawn Sinkers every 3 seconds
         if (random(0, 3 * 30) == 1)
            storage.addElement(new StorageBird(new LogicSinker(), new InterfaceSinker(), size, 4.5));
         break;

      // Level 3: Three kinds of birds (Standard, Sinker, Floater)
      case 3:
         size = 20.0;
         // Spawn when there are no birds on screen, with a random chance
         if (storage.getNumBirds() == 0 && random(0, 15) == 1)
               storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));

         // Spawn every 4 seconds
         if (random(0, 4 * 30) == 1)
               storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));

         // Spawn Sinkers every 4 seconds
         if (random(0, 4 * 30) == 1)
            storage.addElement(new StorageBird(new LogicSinker(), new InterfaceSinker(), size, 4.5));

         // Spawn Floaters every 4 seconds
         if (random(0, 4 * 30) == 1)
               storage.addElement(new StorageBird(new LogicFloater(), new InterfaceFloater(), size, 5.0));
         break;

      // Level 4: Four kinds of birds (Standard, Sinker, Floater, Crazy)
      case 4:
         size = 15.0;
         // Spawn when there are no birds on screen, with a random chance
         if (storage.getNumBirds() == 0 && random(0, 15) == 1)
               storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));

         // Spawn every 4 seconds
         if (random(0, 4 * 30) == 1)
               storage.addElement(new StorageBird(new LogicStandard(), new InterfaceStandard(), size, 5.0));

         // Spawn Sinkers every 4 seconds
         if (random(0, 4 * 30) == 1)
            storage.addElement(new StorageBird(new LogicSinker(), new InterfaceSinker(), size, 4.5));

         // Spawn Floaters every 4 seconds
         if (random(0, 4 * 30) == 1)
               storage.addElement(new StorageBird(new LogicFloater(), new InterfaceFloater(), size, 5.0));

         // Spawn Crazy birds every 4 seconds
         if (random(0, 4 * 30) == 1)
               storage.addElement(new StorageBird(new LogicCrazy(), new InterfaceCrazy(), size, 4.5));
         break;

      default:
         break;
   }
}


void Logic::input(const UserInput & ui)
{
   // reset the game
   if (isGameOver() && ui.isSpace())
   {
      storage.reset();
//      time.reset();
//      score.reset();
//      hitRatio.reset();
      return;
   }

   // gather input from the interface
   Gun* gun = storage.getGun();
   gun->interact(ui.isUp() + ui.isRight(), ui.isDown() + ui.isLeft());
   StorageBullet *p = nullptr;

   // a pellet can be shot at any time
   if (ui.isSpace())
      p = new StorageBullet(new LogicPellet(), new InterfacePellet(), gun->getAngle(), 15, 1.0, 1);
   // missiles can be shot at level 2 and higher
   else if (ui.isM() && getLevelNumber() > 1)
      p = new StorageBullet(new LogicMissile(), new InterfaceMissile(), gun->getAngle(), 10, 1.0, 3);
   // bombs can be shot at level 3 and higher
   else if (ui.isB() && getLevelNumber() > 2)
      p = new StorageBullet(new LogicBomb(), new InterfaceBomb(), gun->getAngle(), 10, 4.0, 4);
   
   bullseye = ui.isShift();
//
   // add something if something has been added
   if (nullptr != p)
      storage.addElement(p);
//
   // send movement information to all the bullets. Only the missile cares.
   for (auto bullet = storage.beginBullet(); bullet != storage.endBullet(); ++bullet)
      (*bullet)->getLogic()->turn(*bullet, ui);
}





/******************************************************************
 * LOGIC ELEMENT ADVANCE FUNCTIONS
 ****************************************************************/

void LogicPellet::advance(StorageElement* se) {
   Position* pt = se->getPosition();
   Velocity* v = se->getVelocity();
   pt->add(*v);

   // out of bounds checker
   if (isOutOfBounds(se))
      se->kill();
}

void LogicMissile::advance(StorageElement* se) {
    // Logic for advance for LogicMissile
   // kill if it has been around too long
//  effects.push_back(new Exhaust(*se->getPosition(), *se->getVelocity()));

   Position* pt = se->getPosition();
   Velocity* v = se->getVelocity();
   pt->add(*v);

   // out of bounds checker
   if (isOutOfBounds(se))
      se->kill();
}

void LogicMissile::turn(StorageElement* se, const UserInput & ui) {
    // Logic for turn for LogicMissile
   Velocity* v = se->getVelocity();
   
   if (ui.isUp() + ui.isRight())
      v->turn(0.04);
   if (ui.isDown() + ui.isLeft())
      v->turn(-0.04);
}

void LogicBomb::advance(StorageElement* se) {
    // Logic for advance for LogicBomb
   timeToDie--;
   if (!timeToDie)
       se->kill();

   Position* pt = se->getPosition();
   Velocity* v = se->getVelocity();
   pt->add(*v);

   // out of bounds checker
   if (isOutOfBounds(se))
      se->kill();
}



void LogicStandard::advance(StorageElement* se) {
    // Logic for advance for LogicStandard
   // small amount of drag
   Velocity* v = se->getVelocity();
   Position* pt = se->getPosition();
   se->multiplyVel(0.995);

   // inertia
   pt->add(*v);

   // out of bounds checker
   if (isOutOfBounds(se))
   {
      se->kill();
      se->setPoints(-se->getPoints()); // points go negative when it is missed!
   }
}


void LogicFloater::advance(StorageElement* se) {
    // Logic for advance for LogicFloater
   // large amount of drag
   Velocity* v = se->getVelocity();
   Position* pt = se->getPosition();
   se->multiplyVel(0.990);

   // inertia
   pt->add(*v);

   // anti-gravity
   v->addDy(0.05);

   // out of bounds checker
   if (isOutOfBounds(se))
   {
      se->kill();
      se->setPoints(-se->getPoints()); // points go negative when it is missed!
   }
}



void LogicSinker::advance(StorageElement* se) {
    // Logic for advance for LogicSinker
   // gravity
   Velocity* v = se->getVelocity();
   Position* pt = se->getPosition();

   v->addDy(-0.07);

   // inertia
   pt->add(*v);

   // out of bounds checker
   if (isOutOfBounds(se))
   {
      se->kill();
      se->setPoints(-se->getPoints()); // points go negative when it is missed!
   }
}


void LogicCrazy::advance(StorageElement* se) {
    // Logic for advance for LogicCrazy
   // erratic turns eery half a second or so
   Velocity* v = se->getVelocity();
   Position* pt = se->getPosition();
   if (randomInt(0, 15) == 0)
   {
      v->addDy(randomFloat(-1.5, 1.5));
      v->addDx(randomFloat(-1.5, 1.5));
   }

   // inertia
   pt->add(*v);

   // out of bounds checker
   if (isOutOfBounds(se))
   {
      se->kill();
      se->setPoints(-se->getPoints()); // points go negative when it is missed!
   }
}

