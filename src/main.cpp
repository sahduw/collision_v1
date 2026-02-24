#include "raylib.h"
#include "resource_dir.h"
#include <iostream>

class Circle{
	public:
		float x, y;
		int speedX, speedY, radius;

		Circle(float startX, float startY){
			x = startX;
			y = startY;
			speedX = 0;
			speedY = 0;
		}

		void update(int height, int width){
			x += speedX;

			int gravity = 1;
			speedY += gravity;
			y += speedY;


			// check if circles fall out of bound vertically
			if(y - radius <= 0){
				y = radius;
				speedY = -speedY * 0.8f;
			} else if(y + radius >= height){
				y = height - radius;
				speedY = -speedY * 0.8f;
			}


			// check if circles fall out of bound horizontally
			if(x - radius <= 0){
				x = radius;
				speedX = -speedX * 0.5f;
			} else if(x + radius >= width){
				x = width - radius;
				speedX = -speedX * 0.5f;
			}
		}
};

bool isCollide(Circle c1, Circle c2);

int main ()
{	
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 800;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "holy raylib");
	SearchAndSetResourceDir("resources");

	SetTargetFPS(60);

	Circle Circle1(200.0f, 120.0f);	
	Circle1.radius = 49;
	Circle1.speedX = 5;

	Circle Circle2(800.0f, 120.0f);
	Circle2.radius = 35;
	Circle2.speedX = -5;

	while (!WindowShouldClose())
	{
		Circle1.update(SCREEN_HEIGHT, SCREEN_WIDTH);
		Circle2.update(SCREEN_HEIGHT, SCREEN_WIDTH);

		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("raylib test", 20,20,20, WHITE);
		
		DrawCircle(Circle1.x, Circle1.y, Circle1.radius, WHITE);
		DrawCircle(Circle2.x, Circle2.y, Circle2.radius, WHITE);

		if(isCollide(Circle1, Circle2)){
			Circle1.speedX *= -1;
			Circle2.speedX *= -1;
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

bool isCollide(Circle c1, Circle c2){
	float dx = c1.x - c2.x;
	float dy = c1.y - c2.y;
	int combinedRadii = c1.radius + c2.radius;
	if((dx * dx + dy * dy) <= (combinedRadii * combinedRadii)){
		return true;
	}
	else return false;
}
