 
#define GLEW_STATE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
 
#include <assert.h> 

#define REQUIRED(stm)  
 


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

float pos_x,pos_y ;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE  ) {
		std::cout << "Key ESC is pressed" << std::endl;
		  exit(0);
	}
}

int main(void)
{
	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit())
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", glfwGetPrimaryMonitor(), NULL);



	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "GLEW is not working" << std::endl;
		return -1;
	}
	if (!GLEW_VERSION_2_1)
	{
		std::cout << "GLEW 2.1 dose not support" << std::endl;
		return -1;
	}

	const GLubyte* glversion = glGetString(GL_VERSION);
	std::cout << "Graphic driver:" << glversion << std::endl;

	const GLubyte* glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "glsl version:" << glslversion << std::endl;

	if (GLEW_ARB_vertex_array_object)
	{
		std::cout << "Vertex array is supported" << std::endl;
	}



	glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 600); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment


	GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
	GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

	GLfloat halfSideLength = 200;
	//assert function 

	REQUIRED(halfSideLength == 200);


	GLfloat vertices[] =
	{
		halfScreenWidth, halfScreenHeight + halfSideLength, 0.0, // top center vertex
		halfScreenWidth - halfSideLength, halfScreenHeight - halfSideLength, 0.0, // bottom left corner
		halfScreenWidth + halfSideLength, halfScreenHeight - halfSideLength, 0.0 // bottom right corner
	};


	 

	GLfloat colour[] =
	{

		255, 0, 0,
		0, 255, 0,
		0, 0, 255
	};


	
	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		 

		glClearColor(0.2f,0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

 
		

		// Render OpenGL here
		glEnableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're using a vertex array for fixed-function attribute
		glEnableClientState(GL_COLOR_ARRAY);

		glPushMatrix();
	
		glVertexPointer(3, GL_FLOAT, 0, vertices); // point to the vertices to be used

		glColorPointer(3, GL_FLOAT, 0, colour);	

		glRotatef(0.3f, 0, 1, 0);
		glTranslatef(pos_x, pos_y, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3); // draw the vertixes
 
		glPopMatrix();

		
		
		

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're finished using the vertex array attribute

		
	

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}

