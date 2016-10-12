#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <vector>

const int width = 800;
const int height = 580;

float* pixels = new float[width*height * 3];


class GeometricObjectInterface
{
public:
	virtual void draw() = 0;
	// implement here
};

template<class T_HOW_TO_DRAW>
class GeometricObject : public GeometricObjectInterface
{
public:
	void draw()
	{
		T_HOW_TO_DRAW draw_object;
		draw_object.draw();
	}
};

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
   pixels[(i + width* j) * 3 + 0] = red;
   pixels[(i + width* j) * 3 + 1] = green;
   pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1) {
		for (int l = j0; l <= j1; l++)
		{
			drawPixel(i0, l, red, green, blue);
		}
	}
	else {
		for (int i = i0; i <= i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);

		}
	}

}
void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing



	//TODO: try moving object
}


class Box 
{
public:
	// some variables
	void draw()
	{
		drawLine(350, 150, 350, 250, 1.0f, 0.0f, 0.0f);
		drawLine(350, 250, 450, 250, 1.0f, 0.0f, 0.0f);
		drawLine(450, 150, 450, 250, 1.0f, 0.0f, 0.0f);
		drawLine(350, 150, 450, 150, 1.0f, 0.0f, 0.0f);
		// draw box here
	}
};


class Circle 
{
public:
	
	double c1=400, c2 =450 ;
	int r1 = 50, r2 = 48;
	void draw()
	{
		for (int a = 0; a < width; a++)
		{
			for (int b = 0; b < height; b++)
			{

				if (sqrt((c1 - a)*(c1 - a) + (c2 - b)*(c2 - b)) < r1)
					drawPixel(a, b, 1.0f, 0.0f, 0.0f);
				if (sqrt((c1 - a)*(c1 - a) + (c2 - b)*(c2 - b)) < r2)
					drawPixel(a, b, 1.0f, 1.0f, 1.0f);
			}

		}

	}
};



// And implement an templatized GeometricObject class.
int main()
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glClearColor(1, 1, 1, 1); // while background
	drawOnPixelBuffer();

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
	std::vector<GeometricObjectInterface*> obj_list;
	obj_list.push_back(new GeometricObject<Box>);
	obj_list.push_back(new GeometricObject<Circle>);
	for (auto itr : obj_list)
		itr->draw();

	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();


	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
