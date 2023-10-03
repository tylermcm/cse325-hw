/*************************************************************
 * 1. Name:
 *      Tyler McMurtrey and Jonathan Hald
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was understanding the terminology and
 * putting it into code. The documentation was not very clear
 * to put it mildly and the formulas were confusing because of
 * not using clear English, but using more math variable names
 * that are short and not helpful to the programmer.
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: 6 hours.
 **************************************************************/
#define _USE_MATH_DEFINES
#include <iostream>  // for CIN and COUT
#include <string> // string library

#include <cmath> // for trigonometry math
#include <numbers> // for numbers library

double computeTotalComponent(double ddx, double ddy);
void displayOutput(double time, double x, double y, double dx, double dy, double velocity, double radians);

using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
* COMPUTE DISTANCE
* Apply inertia to compute a new position using the distance equation.
* The equation is:
*     s = s + v t + 1/2 a t^2
* INPUT
*     s : original position, in meters
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     s : new position, in meters
**************************************************/
double computeDistance(double position, double velocity, double acceleration, double time)
{
    return position + velocity * time + 0.5 * acceleration * time * time;
}

/**************************************************
* COMPUTE ACCELERATION
* Find the acceleration given a thrust and mass.
* This will be done using Newton's second law of motion:
*     f = m * a
* INPUT
*     f : force, in Newtons (kg * m/s^2)
*     m : mass, in kilograms
* OUTPUT
*     a : acceleration, in meters/second^2
***************************************************/
double computeAcceleration()
{
    return (THRUST / WEIGHT);
}

/***********************************************
* COMPUTE VELOCITY
* Starting with a given velocity, find the new
* velocity once acceleration is applied. This is
* called the Kinematics equation. The
* equation is:
*     v = v + a t
* INPUT
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     v : new velocity, in meters/second
***********************************************/
double computeVelocity(double velocity, double acceleration, double time)
{
    return velocity + acceleration * time;
}


/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
*     cos(radians) = y / acceleration
*     y = cos(radians) * acceleration
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double computeVerticalComponent(double totalComponent, double radians)
{
    return ((totalComponent)*cos(radians));
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double computeHorizontalComponent(double totalComponent, double radians)
{
    return (totalComponent)*sin(radians);
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double computeTotalComponent(double ddx, double ddy)
{
    return sqrt((ddx * ddx) + (ddy * ddy));
}

/*************************************************
* RADIANS FROM DEGREES
* Convert degrees to radians:
*     radians / 2pi = degrees / 360
* INPUT
*     d : degrees from 0 to 360
* OUTPUT
*     r : radians from 0 to 2pi
**************************************************/
double convertRadiansFromDegrees(double degrees)
{
    double radians = degrees * M_PI / 180;
    return radians;
}

/**************************************************
* PROMPT
* A generic function to prompt the user for a double
* INPUT
*      message : the message to display to the user
* OUTPUT
*      response : the user's response
***************************************************/
double prompt(string message)
{
    double response = 0;

    cout << message;
    cin >> response;
    return response;
}

/***************************************************
* UPDATEACCELERATION
* call radians, horizontal, and vertical functions
* to update their variables
****************************************************/
void updateAcceleration(double degrees, double accelerationThrust, double& ddx, double& ddy)
{
    double radians = convertRadiansFromDegrees(degrees);
    ddx = computeHorizontalComponent(accelerationThrust, radians);
    ddy = computeVerticalComponent(accelerationThrust, radians) + GRAVITY;
}

/***************************************************
* SIMULATION
* looping through the computations of motion for LM
****************************************************/
void simulation(double& dx, double& dy, double& ddx, double& ddy, double& degrees,
    double& x, double& y, double& velocity, double time, double startTime, double endTime)
{
    bool zeroHorizontalAcceleration = (fabs(ddx) < 1e-6);
    for (startTime; startTime < endTime; startTime++)
    {
        if (!zeroHorizontalAcceleration)
            dx = computeVelocity(dx, ddx, time);
        dy = computeVelocity(dy, ddy, time);

        x = computeDistance(x, dx, ddx, time);
        y = computeDistance(y, dy, ddy, time);

        velocity = computeTotalComponent(dx, dy);
        displayOutput(startTime, x, y, dx, dy, velocity, degrees);

    }
}


/****************************************************
* DISPLAYOUTPUT
* display output
*****************************************************/
void displayOutput(double startTime, double x, double y, double dx, double dy, double velocity, double degrees)
{
    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(2);
    cout << startTime << "s - "
        << "x,y:(" << x << ", " << y << ")m   "
        << "dx,dy:(" << dx << ", " << dy << ")m/s   "
        << "speed:" << velocity << "m/s   "
        << "angle:" << degrees << "deg" << endl;
}

/****************************************************************
* MAIN
* Prompt for input, compute new position, and display output
****************************************************************/
int main()
{
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double degrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");

    double time = 1;
    double x = 0;                   // Horizontal Position 
    double radians = 0;             // Angle in radians
    double accelerationThrust = 0;  // Acceleration due to thrust 
    double ddx = 0;                 // Total horizontal acceleration
    double ddy = 0;                 // Total vertical acceleration
    double velocity = 0;            // Total velocity
    accelerationThrust = computeAcceleration();
    updateAcceleration(degrees, accelerationThrust, ddx, ddy);

    simulation(dx, dy, ddx, ddy, degrees, x, y, velocity, time, 1, 6);
    degrees = prompt("What is the new angle of the LM where 0 is up (degrees)? ");
    updateAcceleration(degrees, accelerationThrust, ddx, ddy);
    simulation(dx, dy, ddx, ddy, degrees, x, y, velocity, time, 6, 11);


    return 0;
}