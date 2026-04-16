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

	Obstacle(float x,float y){
		width = 30;
		height = 30;
		object_x = x;
		object_y = y + height;
		speed = 3;
	}

	void drawObstace() {
		DrawRectangle(object_x,object_y, width, height, RED);
	}

	void moveObstacle() {
		object_x -= speed;
	}

	~Obstacle() {
		std::cout << "Object destroyed" << std::endl;
	}
};
