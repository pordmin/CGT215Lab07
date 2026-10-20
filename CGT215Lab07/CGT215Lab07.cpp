#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Creates a window of type video mode (so we can see anims and stuff) and name 
	// and a world with a gravity of 0, 1 (x, y)
	//
	RenderWindow window(VideoMode(800, 600), "CGT_215_Lab_07_svijayag");
	World world(Vector2f(0, 1));
	// A ball is created with origin point set in the middle of the window, with its radius set as 20 in all
	// directions
	// The ball is added as a physics object to the world
	//
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 100));
	ball.setRadius(20);
	//Changes the direction of the ball by giving it a "momentary push in a certain direction"
	ball.applyImpulse(Vector2f(0.1, 0.3));
	world.AddPhysicsBody(ball);
	//
	// 
	// All these are static physics objects that act as barriers to hold the ball in. Their size is 20 and 
	// either the width or the height of the window.
	//
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	//
	// 
	PhysicsRectangle sideWallR;
	sideWallR.setSize(Vector2f(20, 600));
	sideWallR.setCenter(Vector2f(790, 300));
	sideWallR.setStatic(true);
	world.AddPhysicsBody(sideWallR);
	//
	// 
	PhysicsRectangle sideWallL;
	sideWallL.setSize(Vector2f(20, 600));
	sideWallL.setCenter(Vector2f(10, 300));
	sideWallL.setStatic(true);
	world.AddPhysicsBody(sideWallL);
	//
	// 
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	//
	//
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(100, 20));
	obstacle.setCenter(Vector2f(400, 350));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);
	//
	//
	//
	int thudCount(0);
	//This specific thing is a lambda expression that allows changes to be made to thudcount if in that 
	//[] and will trigger the function and pass in any collision data via the result variable.
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult floorResult) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	//
	//
	int slamCount(0);
	obstacle.onCollision = [&slamCount, &window](PhysicsBodyCollisionResult obstacleResult) {
		cout << "bang " << slamCount << endl;
		slamCount++;
		if (slamCount >= 3) exit(0);
		};

	//This acts as the game loop code meaning this is what allows the game to display each frame 
	// from one to the next and then the next
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		//Calculates physics and updates lasttime ONLY if no. of ellapsed seconds is greater than 0
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		//Clears the screen of previously rendered items to update the frame. Think of this as the in between
		//per each flip through a flipbook for an animation.
		window.clear(Color(0, 0, 0));
		//Draws the ball and floor to the window and then displays it to be shown to us
		window.draw(ball);
		window.draw(floor);
		window.draw(obstacle);
		window.draw(sideWallR);
		window.draw(sideWallL);
		window.draw(ceiling);
		window.display();
	}
}