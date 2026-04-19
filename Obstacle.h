#pragma once
#include<raylib.h>
#include<iostream>

class Obstacle
{
public:
	float object_x;
	float object_y;
	float width;
	float height;
	float speed;
	float jump_hitbox_height;

	Obstacle(float x,float y){
		width = 50;
		height = 20;
		jump_hitbox_height = 10;
		object_x = x;
		object_y = y + height/2;
		speed = 3;
	}

	void drawObstace() {
		DrawRectangle(object_x,object_y, width, height, RED);
		DrawRectangle(object_x, object_y - height/2, width, jump_hitbox_height, GREEN);
	}

	void moveObstacle() {
		object_x -= speed;
	}

	~Obstacle() {
		std::cout << "Object destroyed" << std::endl;
	}
};
