#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// width:height 3:2 ratio
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

using namespace std;

float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
bool mask[WINDOW_HEIGHT][WINDOW_WIDTH];
GLFWwindow *window;

int s = 1;

// Color structure. Can be used to define the brush and background color.
struct color { float r, g, b; };

struct color blackPixel = {0, 0, 0}; // 000
struct color bluePixel = {0, 0, 1.0}; // 001
struct color greenPixel = {0, 1.0, 0}; // 010
struct color cyanPixel = {1.0, 1.0, 0}; // 110
struct color redPixel = {1.0, 0, 0}; // 100
struct color magentaPixel = {1.0, 0, 1.0}; // 101
struct color yellowPixel = {1.0, 1.0, 0}; // 110
struct color whitePixel = {1.0, 1.0, 1.0};  // 111
// Brush color used for switching between colors
struct color brushColor = whitePixel;  // initialize brush color as white
struct color backColor = whitePixel; 

// A function clamping the input values to the lower and higher bounds
#define CLAMP(in, low, high) ((in) < (low) ? (low) : ((in) > (high) ? (high) : in))

// Set a particular pixel of the frameBuffer to the provided color 
void SetFrameBufferPixel(int x, int y, struct color lc) 
{
	// Origin is upper left corner. 
	// Changes the origin from the lower-left corner to the upper-left corner
	y = WINDOW_HEIGHT - 1 - y;

	x = CLAMP(x, 0, WINDOW_WIDTH - 1);
	y = CLAMP(y, 0, WINDOW_HEIGHT - 1);

	frameBuffer[y][x][0] = lc.r;
	frameBuffer[y][x][1] = lc.g;
	frameBuffer[y][x][2] = lc.b;

}

// sets frame buffer to black
void ClearFrameBuffer()
{
	memset(frameBuffer, 0.0f, sizeof(float) * WINDOW_WIDTH * WINDOW_HEIGHT * 3);
}

// Display frameBuffer on screen
void Display()
{	
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
}

// Mouse position callback function
void CursorPositionCallback(GLFWwindow* lWindow, double xpos, double ypos)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int state2 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS)
	{
		std::cout << "Mouse position is: x - " << xpos << ", y - " << ypos << std::endl;

		int x = int(xpos);
		int y = int(ypos);

		for (int i = 0; i < ::s; i++) {
			for (int j = 0; j < ::s; j++) {
				SetFrameBufferPixel(x-i, y+j, brushColor);
				SetFrameBufferPixel(x+i, y+j, brushColor);

				mask[int(y+j)][int(x-i)] = true;
				mask[int(y+j)][int(x+i)] = true;
			}

		}

	} else if (state2 == GLFW_PRESS) {
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				mask[i][j] = false;
				SetFrameBufferPixel(j, i, backColor);}
				
			}

	}
}

// Mouse callback function
void MouseCallback(GLFWwindow* lWindow, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	{
		std::cout << "Mouse left button is pressed." << std::endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) 
	{
		std::cout << "Mouse right button is pressed." << std::endl;
	}


}

// You can use "switch" or "if" to compare key to a specific character.
// for example,
// if (key == '0')
//     DO SOMETHING

// Keyboard callback function

void CharacterCallback(GLFWwindow* lWindow, unsigned int key)
{ 
	std::cout << "Key " << (char)key << " is pressed." << std::endl;

		// if (key == '-') {
		// 	int temp = (::s / 2);
		// 	if ((temp >= 1) && (temp <= 128)) {
		// 		::s /= 2;
		// 	}
		// } else if (key == '+') {
		// 	int temp = (::s * 2);
		// 	if ((temp >= 1) && (temp <= 128)) {
		// 		::s *= 2;
		// 	}
		// }
		// reestablish the pixel size using SetFramePixelBuffer	
	//std::cout << "Value of s is " << ::s << std::endl;
	// brush color corresponding to number input
	int temp1 = (::s / 2);
	int temp2 = (::s * 2);
	switch(char(key)) {
	case '-':
			if ((temp1 >= 1) && (temp1 <= 128)) {
				::s /= 2;
			}
		cout << "new s value is " << s << endl;
		break;
	case '+':
			if ((temp2 >= 1) && (temp2 <= 128)) {
				::s *= 2;
			}
		cout << "new s value is " << s << endl;
		break;
	case '0':
		brushColor = blackPixel;
		cout << "Brush color is now Black" << endl;
		break;
	case '1':
		brushColor = bluePixel;
		cout << "Brush color is now Blue" << endl;
		break;
	case '2':
		brushColor = greenPixel;
		cout << "Brush color is now Green" << endl;
		break;
	case '3':
		brushColor = cyanPixel;
		cout << "Brush color is now Cyan" << endl;
		break;
	case '4':
		brushColor = redPixel;
		cout << "Brush color is now Red" << endl;
		break;
	case '5':
		brushColor = magentaPixel;
		cout << "Brush color is now Magenta" << endl;
		break;
	case '6':
		brushColor = yellowPixel;
		cout << "Brush color is now Yellow" << endl;
		break;
	case '7':
		brushColor = whitePixel;
		cout << "Brush color is now White" << endl;
		break;
	case ')':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, blackPixel);}
				backColor = blackPixel;
			}

		}
		cout << "Background color is now Black" << endl;
		break;
	case '!':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, bluePixel);}
				backColor = bluePixel;
				
			}

		}
		cout << "Background color is now Blue" << endl;
		break;
	case '@':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, greenPixel);}
				backColor = greenPixel;
				
			}

		}
		cout << "Background color is now Green" << endl;
		break;
	case '#':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, cyanPixel);}
				backColor = cyanPixel;
			}

		}
		cout << "Background color is now Cyan" << endl;
		break;
	case '$':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, redPixel);}
				backColor = redPixel;
			}

		}
		cout << "Background color is now Red" << endl;
		break;
	case '%':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, magentaPixel);}
				backColor = magentaPixel;
			}

		}
		cout << "Background color is now Magenta" << endl;
		break;
	case '^':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, yellowPixel);}
				backColor = yellowPixel;
			}

		}
		cout << "Background color is now Yellow" << endl;
		break;
	case '&':
		for (int i = 0; i < (WINDOW_HEIGHT) ; i++) {  // row aka height

			for (int j = 0; j < (WINDOW_WIDTH); j++) {  // column aka width
				if (!mask[i][j]) {SetFrameBufferPixel(j, i, whitePixel);}
				backColor = whitePixel;
			}

		}
		cout << "Background color is now White" << endl;
		break;
	
	default:
		cout << "Nothing happened" << endl;
		break;
}

}

void Init()
{
	
	glfwInit();
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment 1 - Seth Johnston", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, MouseCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetCharCallback(window, CharacterCallback);
	glewExperimental = GL_TRUE;
	glewInit();
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	ClearFrameBuffer();  
}


int main()
{	
	Init();
	while (glfwWindowShouldClose(window) == 0)  // forever loop
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Display();
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
		// struct color testcolor = {0.5, 0.2, 0.9};
		// SetFrameBufferPixel(300, 300, testcolor); 
		
	}

	glfwTerminate();
	return 0;
}