//
//  interface.cpp
//  skeet_07_sep_des
//
//  Created by Spencer Lamoreaux on 11/6/24.
//

#include "interface.hpp"
#include "storage.hpp"  // Include the StorageElement class


#include <string>
#include <sstream>
#include "skeet.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__
#include <cmath>  // For M_PI and math functions if needed for drawing
using namespace std;



/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void drawDisk(const Position& center, int radius, double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
      glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
      glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
   glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine( Position& begin, Position& end, double red, double green, double blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void drawDot(Position& point, double radius, double red, double green, double blue)
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}


/************************************************************************
 * INTERFACE ELEMENT DRAW IMPLEMENTATION
 * Draws the different elements in the game
 *************************************************************************/
// Standard bird draw implementation
void InterfaceStandard::draw(StorageElement* se)
{
   if (!se->isDead())
   {
      // Access position and radius from StorageElement
      Position* pt = se->getPosition();
      double radius = se->getRadius();
      
      // Example drawing (you can adjust this with your drawing logic)
      drawDisk(*pt, radius - 0.0, 1.0, 1.0, 1.0);  // White outline
      drawDisk(*pt, radius - 3.0, 0.0, 0.0, 1.0);  // Blue center
   }
}

// Floater bird draw implementation
void InterfaceFloater::draw(StorageElement* se)
{
   if (!se->isDead())
   {
      Position* pt = se->getPosition();
      double radius = se->getRadius();
      
      drawDisk(*pt, radius - 0.0, 0.0, 0.0, 1.0);  // Blue outline
      drawDisk(*pt, radius - 4.0, 1.0, 1.0, 1.0);  // White center
   }
}

// Sinker bird draw implementation
void InterfaceSinker::draw(StorageElement* se)
{
   if (!se->isDead())
   {
      Position* pt = se->getPosition();
      double radius = se->getRadius();
      
      drawDisk(*pt, radius - 0.0, 0.0, 0.0, 0.8);  // Dark blue outline
      drawDisk(*pt, radius - 4.0, 0.0, 0.0, 0.0);  // Black center
   }
}

// Crazy bird draw implementation
void InterfaceCrazy::draw(StorageElement* se)
{
   if (!se->isDead())
   {
      Position* pt = se->getPosition();
      double radius = se->getRadius();
      
      drawDisk(*pt, radius * 1.0, 0.0, 0.0, 1.0);  // Bright blue outside
      drawDisk(*pt, radius * 0.8, 0.2, 0.2, 1.0);
      drawDisk(*pt, radius * 0.6, 0.4, 0.4, 1.0);
      drawDisk(*pt, radius * 0.4, 0.6, 0.6, 1.0);
      drawDisk(*pt, radius * 0.2, 0.8, 0.8, 1.0);  // Almost white inside
   }
}

// Pellet bullet draw implementation
void InterfacePellet::draw(StorageElement* se)
{
   if (!se->isDead())
   {
      Position* pt = se->getPosition();
      drawDot(*pt, 3.0, 1.0, 1.0, 0.0);
      
   }
}

// Bomb bullet draw implementation
void InterfaceBomb::draw(StorageElement* se)
{
   Position* pt = se->getPosition();
   double radius = se->getRadius();
   if (!se->isDead())
   {
      // Bomb actually has a gradient to cut out the harsh edges
      drawDot(*pt, radius + 2.0, 0.50, 0.50, 0.00);
      drawDot(*pt, radius + 1.0, 0.75, 0.75, 0.00);
      drawDot(*pt, radius + 0.0, 0.87, 0.87, 0.00);
      drawDot(*pt, radius - 1.0, 1.00, 1.00, 0.00);
   }
}

// Shrapnel bullet draw implementation
void InterfaceShrapnel::draw(StorageElement* se)
{
   if (!se->isDead())
   {
      Position* pt = se->getPosition();
      double radius = se->getRadius();
      drawDot(*pt, radius, 1.0, 1.0, 0.0);
   }
}

// Missile bullet draw implementation
void InterfaceMissile::draw(StorageElement* se)
{
   if (!se->isDead())
   {
      Position* pt = se->getPosition();
      Velocity* v = se->getVelocity();
      
      // missile is a line with a dot at the end so it looks like fins.
      Position ptNext(*pt);
      ptNext.add(*v);
      drawLine(*pt, ptNext, 1.0, 1.0, 0.0);
      drawDot(*pt, 3.0, 1.0, 1.0, 1.0);
    }
}

Position rotate(const Position& origin,
   double x, double y, double rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(rotation);
   double sinA = sin(rotation);

   // start with our original point
   Position ptReturn(origin);

   // find the new values
   ptReturn.addX(x * cosA - y * sinA);
   ptReturn.addY(y * cosA + x * sinA /*center of rotation*/);

   return ptReturn;
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen from the beginning to the end.
 *************************************************************************/
void drawRectangle(const Position& pt,
                   double angle = 0.0,
                   double width = 10.0,
                   double height = 100.0,
                   double red = 1.0,
                   double green = 1.0,
                   double blue = 1.0)
{
   // Get ready...
   glBegin(GL_QUADS);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(rotate(pt,  width / 2.0,  height / 2.0, angle));
   glVertexPoint(rotate(pt,  width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate(pt, -width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate(pt, -width / 2.0,  height / 2.0, angle));
   glVertexPoint(rotate(pt,  width / 2.0,  height / 2.0, angle));

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

 /*********************************************
  * GUN : DISPLAY
  * Display the gun on the screen
  *********************************************/


void Interface::input(const UserInput & ui)
{
   logic.input(ui);
}

void Interface::processing()
{
   logic.spawn();
   logic.advance();
}

void Interface::drawBackground(double redBack, double greenBack, double blueBack) const
{
   glBegin(GL_TRIANGLE_FAN);

   // two rectangles is the fastest way to fill the screen.
   glColor3f((GLfloat)redBack /* red % */, (GLfloat)greenBack /* green % */, (GLfloat)blueBack /* blue % */);
   glVertex2f((GLfloat)0.0, (GLfloat)0.0);
   glVertex2f((GLfloat)StorageBird::dimensions.getX(), (GLfloat)0.0);
   glVertex2f((GLfloat)StorageBird::dimensions.getX(), (GLfloat)StorageBird::dimensions.getY());
   glVertex2f((GLfloat)0.0, (GLfloat)StorageBird::dimensions.getY());

   glEnd();
}

void Interface::drawTimer(double percent,
                     double redFore, double greenFore, double blueFore,
                     double redBack, double greenBack, double blueBack) const
{
   double radians;

   GLfloat length = (GLfloat)StorageBird::dimensions.getX();
   GLfloat half = length / (GLfloat)2.0;

   // do the background stuff
   drawBackground(redBack, greenBack, blueBack);

   // foreground stuff
   radians = percent * M_PI * 2.0;
   GLfloat x_extent = half + length * (GLfloat)sin(radians);
   GLfloat y_extent = half + length * (GLfloat)cos(radians);

   // get read to draw the triangles
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)redFore /* red % */, (GLfloat)greenFore /* green % */, (GLfloat)blueFore /* blue % */);
   glVertex2f(half, half);

   // fill in the triangles, one eight at a time
   switch ((int)(percent * 8.0))
   {
   case 7: // 315 - 360
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, length);
      break;
   case 6: // 270 - 315
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, half);
      break;
   case 5: // 225 - 270
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      break;
   case 4: // 180 - 225
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(half, 0.0);
      break;
   case 3: // 135 - 180
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      glVertex2f(length, 0.0);
      break;
   case 2: // 90 - 135 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      break;
   case 1: // 45 - 90 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      break;
   case 0: // 0 - 45 degrees
      glVertex2f(half, length);
      break;
   }
   glVertex2f(x_extent, y_extent);

   // complete drawing
   glEnd();

   // draw the red line now
   glBegin(GL_LINES);
   glColor3f((GLfloat)0.6, (GLfloat)0.0, (GLfloat)0.0);
   glVertex2f(half, half);
   glVertex2f(x_extent, y_extent);
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Position& topLeft, const char* text)
{
   void* pFont = GLUT_TEXT;
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);

   // prepare to output the text from the top-left corner
   glRasterPos2f((GLfloat)topLeft.getX(), (GLfloat)topLeft.getY());

   // loop through the text
   for (const char* p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}
void drawText(const Position & topLeft, const string & text)
{
   drawText(topLeft, text.c_str());
}

/************************
 * DRAW BULLSEYE
 * Put a bullseye on the screen
 ************************/
void Interface::drawBullseye(double angle) const
{
   // find where we are pointing
   double distance = StorageBird::dimensions.getX();
   GLfloat x = StorageBird::dimensions.getX() - distance * cos(angle);
   GLfloat y = distance * sin(angle);

   // draw the crosshairs
   glBegin(GL_LINES);
   glColor3f((GLfloat)0.6, (GLfloat)0.6, (GLfloat)0.6);

   // Draw the actual lines
   glVertex2f(x - 10.0, y);
   glVertex2f(x + 10.0, y);

   glVertex2f(x, y - 10.0);
   glVertex2f(x, y + 10.0);

   glColor3f((GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);
   glVertex2f(StorageBird::dimensions.getX(), 0.0);
   glVertex2f(x, y);

   // Complete drawing
   glEnd();
}

/************************
 * SKEET DRAW LEVEL
 * output everything that will be on the screen
 ************************/
void Interface::drawLevel()
{
   // output the background
   drawBackground(logic.getLevelNumber() * .1, 0.0, 0.0);
   
   // draw the bullseye
   if (logic.isBullsey())
      drawBullseye(logic.getGunAngle());

   // output the gun
      
   drawRectangle(Position(800.0, 0.0), M_PI_2 - logic.getGunAngle(), 10.0, 100.0, 1.0, 1.0, 1.0);
   
         
   // output the birds, bullets, and fragments
//   for (auto& pts : points)
//      pts.show();
   for (auto elem = logic.begin(); elem != logic.end(); ++elem) {
       (*elem)->getInterface()->draw(*elem);  // Dereference elem to get the object
   }
   


   
   // status
   drawText(Position(10, StorageBird::dimensions.getY() - 30), "Score " + std::to_string(logic.getScore()));
   drawText(Position(StorageBird::dimensions.getX() / 2 - 30, StorageBird::dimensions.getY() - 30), logic.getTime()->getText()   );
   drawText(Position(StorageBird::dimensions.getX() - 110,    StorageBird::dimensions.getY() - 30), "Birds:   " + std::to_string(logic.storage.getNumKilled() * 100 / (logic.storage.getNumMissed() + logic.storage.getNumKilled())) + "%");
}

/************************
 * SKEET DRAW STATUS
 * place the status message on the center of the screen
 ************************/
void Interface::drawStatus()
{
   // output the text information
   Time* time = logic.getTime();
   ostringstream sout;
   if (time->isGameOver())
   {
      // draw the end of game message
      drawText(Position(StorageBird::dimensions.getX() / 2 - 30, StorageBird::dimensions.getY() / 2 + 10),
               "Game Over");

      // draw end of game status
      drawText(Position(StorageBird::dimensions.getX() / 2 - 30, StorageBird::dimensions.getY() / 2 - 10),
               &"Score: " [ logic.getScore()]);
   }
   else
   {
      // output the status timer
      drawTimer(1.0 - time->percentLeft(),
                     (time->level() - 0.0) * .1, 0.0, 0.0,
                     (time->level() - 1.0) * .1, 0.0, 0.0);

      // draw the message giving a countdown
      sout << "Level " << time->level()
           << " begins in " << time->secondsLeft() << " seconds";
      drawText(Position(StorageBird::dimensions.getX() / 2 - 110, StorageBird::dimensions.getY() / 2 - 10),
         sout.str());
   }
}

