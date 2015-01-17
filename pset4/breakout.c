//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // wait for click before exiting
    waitForClick();

    // initial velocity
    double xvelocity =  drand48() , yvelocity = drand48() * 1.5;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        //Scoreboard*/
        updateScoreboard(window, label, points);
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure circle follows top cursor
                double x = getX(event) - 25;
                double y = HEIGHT - 60;
                setLocation(paddle, x, y);
            }
        }    
        
        // move circle along
        move(ball, xvelocity, yvelocity);
       
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = - xvelocity;
        }
        // bounce off left edge of window
        if (getX(ball) <= 0)
        {
            xvelocity = - xvelocity;
        }
        // bounce off bottom edge of window
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            yvelocity = -yvelocity;
        }
        // bounce off top edge of window
        if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }
        pause(drand48());
        
        //detect Collision
         GObject object = detectCollision(window, ball);
         if (object != NULL)
            {
                if (object == paddle)
                {
                    //xvelocity = -xvelocity;
                    yvelocity = -yvelocity;
                }
            //remove block algo
                else if (strcmp(getType(object), "GRect") == 0)
                {
                    removeGWindow(window, object);
                    yvelocity = -yvelocity;
                    xvelocity = -xvelocity;
                    points++;
                    bricks--;
                }     
           } 
        //life counter algo
        if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
            lives--;
            setLocation(ball, 190, 200);
            setLocation(paddle, 160, 500);
            pause(250);
            } 
    }     
    // game over
    closeGWindow(window);  
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
            int whitespacey = 36;
        for (int i = 0; i < ROWS; i++)
        {
            whitespacey = whitespacey + 14;
            int whitespacex = 0;
            for (int j = 0; j < COLS; j++)
            {
            whitespacex = whitespacex + 4; 
            GRect dbricks = newGRect(whitespacex + 35.5 * j, whitespacey, 35.5, 10);
            setFilled(dbricks, true);
            setColor(dbricks, "BLUE");
            add(window, dbricks);
            }
        }         
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(WIDTH/2,HEIGHT/2, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "GREEN");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(WIDTH/2 - 25,HEIGHT - 50, 50, 10);
    setFilled(paddle, true);
    setColor(paddle, "RED");
    add(window, paddle);
    return paddle;
    
    //how do I bound the paddle to operated only within the size of the screen???
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-70");
    setColor(label, "GRAY");
    add(window, label);
    setLocation(label, 185, 300);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
