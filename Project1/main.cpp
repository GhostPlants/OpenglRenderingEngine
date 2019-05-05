#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <cmath>
//#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Material.h"
#include "LightDir.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
unsigned int LoadImageToGPU(const char* Filename, GLint format, GLenum enumFormat);
void ActiveTexture(const GLuint slot, int num);

#pragma region Data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

unsigned int indices[] = {
0, 1, 3, // first triangle
1, 2, 3  // second triangle
};

glm::vec3 cubePositions[] = {
	 glm::vec3(0.0f,  0.0f,  0.0f),
	 glm::vec3(2.0f,  5.0f, -15.0f),
	 glm::vec3(-1.5f, -2.2f, -2.5f),
	 glm::vec3(-3.8f, -2.0f, -12.3f),
	 glm::vec3(2.4f, -0.4f, -3.5f),
	 glm::vec3(-1.7f,  3.0f, -7.5f),
	 glm::vec3(1.3f, -2.0f, -2.5f),
	 glm::vec3(1.5f,  2.0f, -2.5f),
	 glm::vec3(1.5f,  0.2f, -1.5f),
	 glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 LightPositions[] = {
	 glm::vec3(10.0f, 10.0f, 5.0f),
	 glm::vec3(0.0f, 0.0f, 0.0f),
	 glm::vec3(1.0f, 0.0f, 0.0f),
	 glm::vec3(0.0f, 1.0f, 0.0f),
	 glm::vec3(0.0f, 0.0f, 1.0f),
	 glm::vec3(0.0f, 5.0f, 0.0f)

};
#pragma endregion

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastx = 0;
float lasty = 0;
bool firstMouse = true;

Camera camera(glm::vec3(0, 0, 4.0f), 15.0f, 180.0f, glm::vec3(0, 1.0f, 0.0f));

int main(int  argc , char* arg[] )
{
     std::string proPath = arg[0];
	 //std::cout << proPath.substr( 0 ,proPath.find_last_of("\\")) + "\\model\\nanosuit.obj" << std::endl;
     #   pragma region OpenGlfw
	// glfw: initialize and configure
// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
#pragma endregion

	glEnable(GL_DEPTH_TEST);
	Shader* textShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	Material* material = new Material(textShader,
		LoadImageToGPU("image/container2.png", GL_RGBA, GL_RGBA),
		glm::vec3(1.0f, 1.0f, 1.0f),
		LoadImageToGPU("image/container2_specular.png", GL_RGBA, GL_RGBA),
		32.0f
	);
	LightDir lightD (glm::vec3(10.0f, 10.0f, 5.0f), glm::vec3(glm::radians(45.0f), 0.0f, 0.0f));

	LightPoint lightP (glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(glm::radians(-180.0f), 0.0f, 0.0f) , glm::vec3(1.0f, 1.0f, 1.0f));
	LightPoint lightP1 (glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(glm::radians(-180.0f), 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	LightPoint lightP2 (glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(glm::radians(-180.0f), 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	LightPoint lightP3 (glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(glm::radians(-180.0f), 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));

	LightSpot lightS (glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians( -90.0f), 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	Model MyModel( proPath.substr(0, proPath.find_last_of("\\")) + "\\model\\nanosuit.obj");

	//unsigned int VBO, VAO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

 //   glBindVertexArray(VAO);

 //   glBindBuffer(GL_ARRAY_BUFFER, VBO);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

 //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
 //   glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

 //   glBindVertexArray(VAO);


	//unsigned int texture1,texture2;

	//texture1 = LoadImageToGPU("image/wall.jpg", GL_RGB , GL_RGB);
	//texture2 = LoadImageToGPU("image/flower.jpg", GL_RGB, GL_RGB);
	
	textShader->use(); // don't forget to activate/use the shader before setting uniforms!

	//glUniform1i(glGetUniformLocation(textShader->ID, "texture1"), 0);
	//textShader->setInt("texture2", 3);

	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view;
	// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	view = camera.GetViewMatrix();

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
		//glm::mat4 model;
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));

		//glm::mat4 trans;
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));D
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // input
        // -----
        processInput(window);

        // render
        // ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (unsigned int i = 0; i < 1; i++)
		{
			textShader->use();
			// be sure to activate the shader before any calls to glUniform11
			//ActiveTexture(material->diffuse , Shader::DIFFUSE);
			//ActiveTexture(material->specular, Shader::SPECULAR);


			model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			view = camera.GetViewMatrix();
			glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniform3f(glGetUniformLocation(textShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(textShader->ID, "ambientcolor"), 0.1f, 0.1f, 0.1f);

			glUniform3f(glGetUniformLocation(textShader->ID, "CameraPos"), camera.Postion.x, camera.Postion.y, camera.Postion.z);
			
			//direction
			glUniform3f(glGetUniformLocation(textShader->ID, "lightDirection.pos"), lightD.postion.x, lightD.postion.y, lightD.postion.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightDirection.color"), lightD.color.x, lightD.color.y, lightD.color.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightDirection.dirToLight"), lightD.direction.x, lightD.direction.y, lightD.direction.z);
			
			//Point
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint.pos"), lightP.postion.x, lightP.postion.y, lightP.postion.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint.color"), lightP.color.x, lightP.color.y, lightP.color.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint.dirToLight"), lightP.direction.x, lightP.direction.y, lightP.direction.z);
			material->shader->setFloat("lightPoint.constant", lightP.constant);
			material->shader->setFloat("lightPoint.linear", lightP.linear);
			material->shader->setFloat("lightPoint.quadratic", lightP.quadratic);

			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint1.pos"), lightP1.postion.x, lightP1.postion.y, lightP1.postion.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);
			material->shader->setFloat("lightPoint1.constant", lightP1.constant);
			material->shader->setFloat("lightPoint1.linear", lightP1.linear);
			material->shader->setFloat("lightPoint1.quadratic", lightP1.quadratic);

			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint2.pos"), lightP2.postion.x, lightP2.postion.y, lightP2.postion.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);
			material->shader->setFloat("lightPoint2.constant", lightP2.constant);
			material->shader->setFloat("lightPoint2.linear", lightP2.linear);
			material->shader->setFloat("lightPoint2.quadratic", lightP2.quadratic);

			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint3.pos"), lightP3.postion.x, lightP3.postion.y, lightP3.postion.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightPoint3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);
			material->shader->setFloat("lightPoint3.constant", lightP3.constant);
			material->shader->setFloat("lightPoint3.linear", lightP3.linear);
			material->shader->setFloat("lightPoint3.quadratic", lightP3.quadratic);

			//聚光灯
			glUniform3f(glGetUniformLocation(textShader->ID, "lightSpot.pos"), lightS.postion.x, lightS.postion.y, lightS.postion.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightSpot.color"), lightS.color.x, lightS.color.y, lightS.color.z);
			glUniform3f(glGetUniformLocation(textShader->ID, "lightSpot.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			material->shader->setFloat("lightSpot.constant", lightS.constant);
			material->shader->setFloat("lightSpot.linear", lightS.linear);
			material->shader->setFloat("lightSpot.quadratic", lightS.quadratic);
			material->shader->setFloat("lightSpot.cosPhyIn", lightS.cosPhyIn);
			material->shader->setFloat("lightSpot.cosPhyOut", lightS.cosPhyOut);

			//衰减值
			//material->shader->setFloat("lightPoint.constant", light.constant);
			//material->shader->setFloat("lightPoint.linear", light.linear);
			//material->shader->setFloat("lightPoint.quadratic", light.quadratic);

			material->shader->setVec3("material.ambient", material->ambient);
			material->shader->setInt("material.texture_diffuse", 0);

			material->shader->setInt("material.texture_specular", 1);
			material->shader->setFloat("material.shininess", material->shininess);
			//glUniform3f(glGetUniformLocation(textShader->ID, "material.ambient"), 1.0f, 1.0f, 1.0f);
			//glUniform3f(glGetUniformLocation(textShader->ID, "material.diffuse"), 0.1f, 0.1f, 1.0f);
			//glUniform3f(glGetUniformLocation(textShader->ID, "material.specular"), 1.0f, 1.0f, 1.0f);
			//glUniform1f(glGetUniformLocation(textShader->ID, "material.shininess"),32.0f);

			MyModel.Draw(material->shader);
			//glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//for (unsigned int i = 0; i < 6; i++)
		//{
		//	model = glm::translate(glm::mat4(1.0f), LightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//	glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//	MyModel.Draw(material->shader);
		//}


		//unsigned int transformLoc = glGetUniformLocation(textShader->ID, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // update shader uniform
		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(textShader->ID, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // render the triangle
		//glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

#pragma region Otherfunc
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.SpeedZ = 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.SpeedZ = -0.01f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.SpeedX = -0.01f;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.SpeedX = 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.SpeedY = 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.SpeedY = -0.01f;
	else
	{
		camera.SpeedZ = 0;
		camera.SpeedY = 0;
		camera.SpeedX = 0;
	}
		

	camera.UpdateCameraPos();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastx = xpos;
		lasty = ypos;
		firstMouse = false;
	}
	float deltax, deltay;
	deltax = xpos - lastx;
	deltay = ypos - lasty;

	lastx = xpos;
	lasty = ypos;

	camera.PorcessMouseMovement(deltax, deltay);

}

unsigned int LoadImageToGPU(const char* Filename ,GLint format, GLenum enumFormat )
{
	unsigned int TextureBuffer;
	glGenTextures(1, &TextureBuffer);
	glBindTexture(GL_TEXTURE_2D, TextureBuffer);
	glActiveTexture(GL_TEXTURE0 );
	// 为当前绑定的纹理对象设置环绕、过滤方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载并生成纹理
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(Filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, enumFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return TextureBuffer;
}
void ActiveTexture(unsigned int slot, int num)
{
	glActiveTexture(GL_TEXTURE0 +num);
	glBindTexture(GL_TEXTURE_2D, slot);
}

#pragma endregion



