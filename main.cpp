#include<iostream>
#include<raylib.h>
#include "Obstacle.h"
#include<vector>
using namespace std;

//variables
const float screenWidth = 800;
const float screenHeight = 450;
const float ZER0_X = screenWidth / 2;
const float ZER0_Y = screenHeight / 2;

float playerX = ZER0_X;
float playerY = ZER0_Y;
float playerYVelocity = 0;
float playerRotation = 0;

float playerSide = 30;
float playerGravity = 0.75;
float playerJumpSpeed = -12;
float playerRotationSpeed = 3;

int obstaclecount;

bool onGround = true;
bool onBlock = false;
bool gameOver = false;

//initialization obstacles

vector<Obstacle*> obstacles = {
	new Obstacle(1300, ZER0_Y),
	new Obstacle(1000, ZER0_Y),
	new Obstacle(600, ZER0_Y)
};

void intializeObstacles() {
	obstaclecount = obstacles.size();
	cout << "Obstacles initialized : " << obstaclecount << endl;
}

//entity functions

void drawObstacles() {
	for (Obstacle* obstacle : obstacles) {
		obstacle->drawObstace();
	}
}

//check functions

void isOnGround()
{
	onBlock = false;
	for (Obstacle* obs : obstacles) {
		if (CheckCollisionRecs(Rectangle{ obs->object_x, obs->object_y - obs->height / 2, obs->width, obs->jump_hitbox_height }, Rectangle{ playerX, playerY, playerSide, playerSide }) and !gameOver) {
			playerY = ZER0_Y - obs->height - obs->jump_hitbox_height;
			playerYVelocity = 0;
			onBlock = true;
			onGround = true;
		}
	}
	if (playerY >= ZER0_Y) {
		playerY = ZER0_Y;
		playerYVelocity = 0;
		onGround = true;
	}
	else if (playerY < ZER0_Y and !onBlock) {
		onGround = false;
	}
}

void obstacleDestroyed() {
	for (int i = 0; i < obstacles.size(); i++) {
		if (obstacles[i]->object_x + obstacles[i]->width < 0) {
			delete obstacles[i];
			obstacles.erase(obstacles.begin() + i);
		}
	}
}

void collisionCheck() {
	for (Obstacle* obs : obstacles) {
		if (CheckCollisionRecs(Rectangle{ obs->object_x, obs->object_y, obs->width, obs->height }, Rectangle{ playerX, playerY, playerSide, playerSide })) {
			cout << "Collision detected" << endl;
			playerYVelocity = 0;
			gameOver = true;
		}
	}
}

void isGameOver() {
	if (gameOver) {
		cout << "Game Over" << endl;
		for (Obstacle* obs : obstacles) {
			obs->speed = 0;
		}
	}
}


//movement functions

void gravity()
{
	if(!onGround) {
		playerYVelocity+= playerGravity;
	}
}

void jump()
{
	if (IsKeyPressed(KEY_SPACE) and onGround) {
		playerYVelocity = playerJumpSpeed;
	}
}

//testing functions

//

//loop functions

void update()
{
	if (onGround) {
		playerRotation = 0;
		cout << "Onground : True" << endl;
	}
	else {
		playerRotation += playerRotationSpeed;
		cout << "Onground : False" << endl;
	}
	collisionCheck();
	obstaclecount = obstacles.size();
	obstacleDestroyed();
	isOnGround();
	isGameOver();
	if (!gameOver) {
		gravity();
		jump();
	}
	playerY += playerYVelocity;
	for (Obstacle* obstacle : obstacles) {
		obstacle->moveObstacle();
	}
}

void draw()
{
	BeginDrawing();
	ClearBackground(SKYBLUE);
	DrawLine(0,ZER0_Y+playerSide,screenWidth,ZER0_Y+playerSide,DARKBLUE);
	drawObstacles();
	DrawRectanglePro(Rectangle{ playerX, playerY, playerSide, playerSide }, Vector2{playerSide/2-15,playerSide/2-15},playerRotation, GREEN);
	EndDrawing();
}

int main()
{
	intializeObstacles();
	InitWindow(screenWidth, screenHeight, "Cube Jump!");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		update();
		draw();
		if (gameOver) {
			break;
		}
		if (IsKeyPressed(KEY_ESCAPE)) {
			CloseWindow();
		}
	}	
}
