#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "shapes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "TestBed.h"

unsigned int compileShader(GLenum type, const char* source);
unsigned int createShader(const char* vsSource, const char* fsSource);
static unsigned loadImageToTexture(const char* filePath);

int main()
{
    if (!glfwInit()) {
        std::cout << "GLFW library could not be read!\n";
        return 1;
    }

    // providing a version of OpenGL (3.3, programable pipline)
    // the 3 before the dot
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // the 3 after the dot
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // setting the programable pipeline
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creating the window and it's attributes 
    GLFWwindow* window;
    unsigned int wWidth = 1200;
    unsigned int wHeight = 600;
    const char wTitle[] = "[Instrument tabla]";
    // first NULL value represents on which screen it should be opened in full screen
    // if it is NULL, then it doesn't open it in full screen
    // if you want it to open in full screen you use glfwGetPrimaryMonitor()
    // the second NULL represents which monitors will share this window
    window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);
    if (window == NULL) {
        std::cout << "Could not create window!\n";
        glfwTerminate();    // shuts off opengl
        return 2;
    }

    // setting the newly created window as the active window
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW could not be read!\n";
        return 3;
    }

    // creating variables for the things that will be shown on screen 
    //===================================================
    unsigned int unifiedShader = createShader("basic.vert", "basic.frag");
    unsigned int textureShader = createShader("texture.vert", "texture.frag");
    unsigned int uniform = glGetUniformLocation(unifiedShader, "colUniform");
    float circleColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    const unsigned int fullVerticesSize = rectSize + rectSize + rectSize + rectSize + rectSize + rectSize + circleSize + circleSize + lineSize + rectSize + rectSize + rectSize;
    float vertices[fullVerticesSize];
    std::cout << "Full size: " << fullVerticesSize << "\n\n";
    unsigned int index = 0;

    float bgColor[] = { 0.2f, 0.2f, 0.2f, 0.2f };
    float progressBarWidth = 0.5f;
    float progressBarHeight = 0.1f;

    // drawing fuel max
    //======
    float fuelMaxColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float fuelMaxPoint[] = { -0.25f, 0.1f };
    const unsigned int fuelMaxIndex = index;
    index = drawRect(vertices, index, fuelMaxPoint[0], fuelMaxPoint[1], progressBarWidth, progressBarHeight, fuelMaxColor);
    //======

    // drawing fuel left
    //======
    float fuelLeftColor[] = { 0.0f, 1.0f, 0.2f, 1.0f };
    float fuelLeftPoint[] = { -0.25f, 0.1f };
    const unsigned int fuelLeftIndex = index;
    index = drawRect(vertices, index, fuelLeftPoint[0], fuelLeftPoint[1], progressBarWidth, progressBarHeight, fuelLeftColor);
    //======

    // drawing acceleration bar
    //======
    float accelerationBarColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float accelerationBarPoint[] = { -0.25f, -0.1f };
    const float accelerationBarWidth = progressBarWidth;
    const float accelerationBarHeight = progressBarHeight;
    const unsigned int accelerationBarIndex = index;
    index = drawRect(vertices, index, accelerationBarPoint[0], accelerationBarPoint[1], progressBarWidth, progressBarHeight, accelerationBarColor);
    //======

    // drawing acceleration
    //======
    float accelerationColor[] = { 1.0f, 0.2f, 1.0f, 1.0f };
    float accelerationPoint[] = { -0.25f, -0.1f };
    const unsigned int accelerationIndex = index;
    index = drawRect(vertices, index, accelerationPoint[0], accelerationPoint[1], progressBarWidth, progressBarHeight, accelerationColor);
    //======

    // drawing cover for fuel left
    //======
    float fuelLeftCoverPoint[] = { -0.25f - progressBarWidth, 0.1f };
    const unsigned int fuelLeftCoverIndex = index;
    index = drawRect(vertices, index, fuelLeftCoverPoint[0], fuelLeftCoverPoint[1], progressBarWidth, progressBarHeight, bgColor);
    //======

    // drawing cover for acceleration
    //======
    float accelerationCoverPoint[] = { -0.25f - progressBarWidth, -0.1f };
    const unsigned int accelerationCoverIndex = index;
    index = drawRect(vertices, index, accelerationCoverPoint[0], accelerationCoverPoint[1], progressBarWidth, progressBarHeight, bgColor);
    //======

    // drawing circles
    //======
    const float radius = 0.5f;
    const float offsetX = -0.6f;
    const float offsetY = 0.4f;
    const float radiusX = wWidth < wHeight ? radius : radius * ((float)wHeight / (float)wWidth);
    const float radiusY = wWidth > wHeight ? radius : radius * ((float)wWidth / (float)wHeight);
    const float speedometerCenter[] = { offsetX, offsetY };
    const unsigned int secondCircleIndex = index;
    float secondCircleCenter[] = { -offsetX, offsetY };
    index = drawCircle(vertices, index, secondCircleCenter[0], secondCircleCenter[1], radiusX, radiusY, circleColor);
    //======

    // drawing left signal
    //======
    bool leftSignalOn = false;
    float leftSignalColor[] = { 1.0f ,1.0f, 0.0f, 1.0f };
    float leftSignalPoint1[] = { -0.8f, -0.5f };
    float leftSignalPoint2[] = { -0.5f, -0.3f };
    float leftSignalPoint3[] = { -0.5f, -0.7f };
    const unsigned int leftSignalIndex = index;
    index = drawTriangle(vertices, index, leftSignalPoint1, leftSignalPoint2, leftSignalPoint3, leftSignalColor);
    //======

    // drawing right signal
    //======
    bool rightSignalOn = false;
    float rightSignalColor[] = { 1.0f ,1.0f, 0.0f, 1.0f };
    float rightSignalPoint1[] = { 0.8f, -0.5f };
    float rightSignalPoint2[] = { 0.5f, -0.3f };
    float rightSignalPoint3[] = { 0.5f, -0.7f };
    const unsigned int rightSignalIndex = index;
    index = drawTriangle(vertices, index, rightSignalPoint1, rightSignalPoint2, rightSignalPoint3, rightSignalColor);
    //======

    // drawing gear indicator
    //======
    float gearIndicatorColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    const float firstGearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    const float secondGearColor[] = { 1.0f, 0.6f, 0.0f, 1.0f };
    const float thirdGearColor[] = { 0.5f, 0.0f, 0.5f, 1.0f };
    const float fourthGearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    const float fifthGearColor[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    const float lampPoint[] = { -0.125f, 0.4f };
    const float lampSize = 0.5f;
    const float lampWidth = wWidth < wHeight ? lampSize : lampSize * ((float)wHeight / (float)wWidth);
    const float lampHeight = wWidth > wHeight ? lampSize : lampSize * ((float)wWidth / (float)wHeight);
    std::cout << lampWidth << " " << lampHeight << "\n";
    const unsigned int gearIndicatorIndex = index;
    index = drawRect(vertices, index, lampPoint[0], lampPoint[1], lampWidth, lampHeight, gearIndicatorColor);
    //======

    // drawing speedometer arrow angles options
    //======
    const unsigned int speedometerArrowsCount = 60;
    const unsigned int speedometerArrowsSize = speedometerArrowsCount * 6 * 2;
    float speedometerArrows[speedometerArrowsSize];
    const float startingAngle = 225.0f;
    float angle = startingAngle;
    for (int i = 0; i < speedometerArrowsCount; ++i) {
        float radians = angle * PI / 180.0f;
        float x = cos(radians) * radiusX * 0.5f + offsetX;
        float y = sin(radians) * radiusY * 0.5f + offsetY;
        speedometerArrows[i * 12 + 0] = x;
        speedometerArrows[i * 12 + 1] = y;
        speedometerArrows[i * 12 + 2] = 1.0f;
        speedometerArrows[i * 12 + 3] = 1.0f;
        speedometerArrows[i * 12 + 4] = 1.0f;
        speedometerArrows[i * 12 + 5] = 1.0f;
        speedometerArrows[i * 12 + 6] = speedometerCenter[0];
        speedometerArrows[i * 12 + 7] = speedometerCenter[1];
        speedometerArrows[i * 12 + 8] = 1.0f;
        speedometerArrows[i * 12 + 9] = 1.0f;
        speedometerArrows[i * 12 + 10] = 1.0f;
        speedometerArrows[i * 12 + 11] = 1.0f;

        --angle;
    }
    //======

    // for colored shapes
    //=================================
    // 2 for XY (take the first two floats as X and Y)
    // 4 for RGBA (take the next 4 floats as R, G, B and A)
    const unsigned int vertexFormatCount = 2 + 4;
    unsigned int stride = vertexFormatCount * sizeof(float);

    // Vertex Array Object - Container for the VBO and pointer for their attributes
    unsigned int VAO[3];
    glGenVertexArrays(3, VAO); // generate 2 containers on the address of the "VAO" variable
    glBindVertexArray(VAO[0]); // connect VAO to active context - everything we do will refer to the container VAO

    // Vertex Buffer Object - figures that are going to be drawn
    unsigned int VBO[3];
    glGenBuffers(3, VBO);  // generate 2 buffers with "VBO" memory address
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // connect VBO with an active Array Buffer
    // glBufferData(which buffer, the size of the data, address of the data, drawing type)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(pointer index, number of attributes, attribute type, should normalize, steps to reaching the next component (stride), movement from the start of the first dot to component for this attribute)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);  // explain that the first 2 numbers are X and Y
    glEnableVertexAttribArray(0);   // activation of the pointer
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));  // explain that the next 4 numbers ar R, G, B and A
    glEnableVertexAttribArray(1);   // activation of the pointer second pointer
    //=================================

    // for textures
    //=================================
    float textureVertices[] = {
        // speedometer
        offsetX - radiusX, offsetY - radiusY,  0.0f, 0.0f,  // bottom left
        offsetX - radiusX, offsetY + radiusY,    0.0f, 1.0f, // top left
        offsetX + radiusX, offsetY - radiusY,   1.0f, 0.0f,  // bottom right
        offsetX + radiusX, offsetY + radiusY,    1.0f, 1.0f,   // top right

        // signature
        -1.0f, -1.0f, 0.0f, 0.0f,   // bottom left
        -1.0f, -0.8f, 0.0f, 1.0f,   // top left
        -0.6, -1.0f, 1.0f, 0.0f,    // bottom right
        -0.6f, -0.8f, 1.0f, 1.0f,   // top right

    };
    unsigned int textureStride = (2 + 2) * sizeof(float);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertices), textureVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, textureStride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, textureStride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //=================================

    // for speedometer arrows
    //=================================
    unsigned int speedometerStride = (4 + 2) * sizeof(float);
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(speedometerArrows), speedometerArrows, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, speedometerStride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, speedometerStride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //=================================

    // we unbind what we created so we don't screw something up
    // but we bind it when we want to draw stuff
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //===================================================

    unsigned int uPosLoc = glGetUniformLocation(unifiedShader, "uPos");

    // loading the texture
    unsigned textures[2];
    textures[0] = loadImageToTexture("res/speedometer.png");
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    textures[1] = loadImageToTexture("res/potpis-za-rg-p1.png");
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
    unsigned uTexLoc = glGetUniformLocation(textureShader, "uTex");
    glUniform1i(uTexLoc, 0);

    // parameters for moving the progress bars
    float fuelLeftPositionOffset[] = { 0.0f, 0.0f };
    float accelerationPositionOffset[] = { -progressBarWidth, 0.0f };
    const float progressBarMovement = 0.0001f;

    // init car 
    Car car = getCar();
    startSimulation(&car);

    // starting the loop for the window
    while (!glfwWindowShouldClose(window)) {
        // GLFW_PRESS -> button is pressed
        // GLFW_RELEASE -> button is released or it isn't pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            // closing the window
            endSimulation(&car);
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            rightSignalOn = true;
            leftSignalOn = false;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            leftSignalOn = true;
            rightSignalOn = false;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            rightSignalOn = false;
            leftSignalOn = false;
        }

        // calculating the width of progress bar that represents fuel left
        fuelLeftPositionOffset[0] = car.getFuelAmount() / car.getMaxFuelAmount() * progressBarWidth - progressBarWidth;

        // adding fuel (doesn't affect the car simulation)
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            // acceleration
            if (accelerationPositionOffset[0] < 0.0f) {
                accelerationPositionOffset[0] += progressBarMovement;
            }
        }
        else {
            // deceleration
            if (accelerationPositionOffset[0] > -progressBarWidth) {
                accelerationPositionOffset[0] -= progressBarMovement;
            }
        }

        // sets the background color
        // R, G, B, alpha
        glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);


        // Placing stuff on screen:
        //===================================================
        glUseProgram(unifiedShader);
        glBindVertexArray(VAO[0]);

        // fuel max
        glUniform4f(uniform, fuelMaxColor[0], fuelMaxColor[1], fuelMaxColor[2], fuelMaxColor[3]);
        glDrawArrays(GL_TRIANGLES, fuelMaxIndex / vertexFormatCount, rectSize / vertexFormatCount);

        // fuel left
        glUniform2f(uPosLoc, fuelLeftPositionOffset[0], fuelLeftPositionOffset[1]);
        glUniform4f(uniform, fuelLeftColor[0], fuelLeftColor[1], fuelLeftColor[2], fuelLeftColor[3]);
        glDrawArrays(GL_TRIANGLES, fuelLeftIndex / vertexFormatCount, rectSize / vertexFormatCount);
        glUniform2f(uPosLoc, 0.0f, 0.0f);

        // acceleration bar
        glUniform4f(uniform, accelerationBarColor[0], accelerationBarColor[1], accelerationBarColor[2], accelerationBarColor[3]);
        glDrawArrays(GL_TRIANGLES, accelerationBarIndex / vertexFormatCount, rectSize / vertexFormatCount);

        // acceleration
        glUniform2f(uPosLoc, accelerationPositionOffset[0], accelerationPositionOffset[1]);
        glUniform4f(uniform, accelerationColor[0], accelerationColor[1], accelerationColor[2], accelerationColor[3]);
        glDrawArrays(GL_TRIANGLES, accelerationIndex / vertexFormatCount, rectSize / vertexFormatCount);
        glUniform2f(uPosLoc, 0.0f, 0.0f);

        // fuel left cover
        glUniform4f(uniform, bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glDrawArrays(GL_TRIANGLES, fuelLeftCoverIndex / vertexFormatCount, rectSize / vertexFormatCount);

        // acceleration cover
        glUniform4f(uniform, bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glDrawArrays(GL_TRIANGLES, accelerationCoverIndex / vertexFormatCount, rectSize / vertexFormatCount);

        // speedometer texture
        glUseProgram(textureShader);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindVertexArray(VAO[1]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);

        // signature texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
        glBindTexture(GL_TEXTURE_2D, 0);

        // speedometer arrows 
        glDisable(GL_BLEND);
        glUseProgram(unifiedShader);
        glBindVertexArray(VAO[2]);
        glLineWidth(4.0);
        if (car.getSpeed() > 30) {
            glUniform4f(uniform, 1.0f, 0.0f, 0.0f, 1.0f);
        }
        else {
            glUniform4f(uniform, 0.0f, 0.0f, 1.0f, 1.0f);
        }
        float carSpeed = car.getSpeed();
        if (carSpeed <= 0) {
            carSpeed = 1;
        }
        if (carSpeed >= speedometerArrowsCount) {
            carSpeed = speedometerArrowsCount - 1;
        }
        glDrawArrays(GL_LINE_LOOP, carSpeed - 1, 2);
        glLineWidth(1.0);

        // back to shapes
        glBindVertexArray(VAO[0]);

        // second circle (graphic display)
        if (car.getSpeed() < 10) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glEnable(GL_PROGRAM_POINT_SIZE);
            glPointSize(4);
        }
        else if (car.getSpeed() >= 10 && car.getSpeed() < 30) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glDisable(GL_BLEND);
        glUniform4f(uniform, circleColor[0], circleColor[1], circleColor[2], circleColor[3]);
        glDrawArrays(GL_TRIANGLES, secondCircleIndex / vertexFormatCount, (circleFillSize + circleVerticesSize) / vertexFormatCount);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // left signal
        if (leftSignalOn) {
            float rgb = abs(sin(glfwGetTime() * 2.5f));
            glUniform4f(uniform, rgb, rgb, 0.0f, 0.0f);
        }
        else {
            glUniform4f(uniform, 0.0f, 0.0f, 0.0f, 1.0f);
        }
        glDrawArrays(GL_TRIANGLES, leftSignalIndex / vertexFormatCount, oneTriangleSize / vertexFormatCount);

        // right signal
        if (rightSignalOn) {
            float rgb = abs(sin(glfwGetTime() * 2.5f));
            glUniform4f(uniform, rgb, rgb, 0.0f, 0.0f);
        }
        else {
            glUniform4f(uniform, 0.0f, 0.0f, 0.0f, 1.0f);
        }
        glDrawArrays(GL_TRIANGLES, rightSignalIndex / vertexFormatCount, oneTriangleSize / vertexFormatCount);

        // gear indicator
        float sinRgb = abs(sin(glfwGetTime() * 2.5f));
        if (car.getGear() == 1) {
            gearIndicatorColor[0] = firstGearColor[0] * sinRgb;
            gearIndicatorColor[1] = firstGearColor[1] * sinRgb;
            gearIndicatorColor[2] = firstGearColor[2] * sinRgb;
        }
        else if (car.getGear() == 2) {
            gearIndicatorColor[0] = secondGearColor[0] * sinRgb;
            gearIndicatorColor[1] = secondGearColor[1] * sinRgb;
            gearIndicatorColor[2] = secondGearColor[2] * sinRgb;
        }
        else if (car.getGear() == 3) {
            gearIndicatorColor[0] = thirdGearColor[0] * sinRgb;
            gearIndicatorColor[1] = thirdGearColor[1] * sinRgb;
            gearIndicatorColor[2] = thirdGearColor[2] * sinRgb;
        }
        else if (car.getGear() == 4) {
            gearIndicatorColor[0] = fourthGearColor[0] * sinRgb;
            gearIndicatorColor[1] = fourthGearColor[1] * sinRgb;
            gearIndicatorColor[2] = fourthGearColor[2] * sinRgb;
        }
        else if (car.getGear() == 5) {
            gearIndicatorColor[0] = fifthGearColor[0] * sinRgb;
            gearIndicatorColor[1] = fifthGearColor[1] * sinRgb;
            gearIndicatorColor[2] = fifthGearColor[2] * sinRgb;
        }
        else {
            gearIndicatorColor[0] = 0.0f;
            gearIndicatorColor[1] = 0.0f;
            gearIndicatorColor[2] = 0.0f;
        }
        glUniform4f(uniform, gearIndicatorColor[0], gearIndicatorColor[1], gearIndicatorColor[2], gearIndicatorColor[3]);
        glDrawArrays(GL_TRIANGLES, gearIndicatorIndex / vertexFormatCount, rectSize / vertexFormatCount);

        glUseProgram(0);

        glBindVertexArray(0);
        //===================================================

        // switching the visible buffer with the background
        glfwSwapBuffers(window);

        // catching events for window edge
        glfwPollEvents();

    }

    glDeleteTextures(2, textures);
    glDeleteBuffers(3, VBO);
    glDeleteVertexArrays(3, VAO);
    glDeleteProgram(unifiedShader);
    glDeleteProgram(textureShader);
    glfwTerminate();

    return 0;
}

unsigned int compileShader(GLenum type, const char* source) {
    // reading source code from file
    std::string content = "";
    std::ifstream file(source);
    std::stringstream ss;

    if (file.is_open()) {
        ss << file.rdbuf();
        file.close();
        std::cout << "Successfully read file from path \"" << source << "\"!\n";
    }
    else {
        ss << "";
        std::cout << "Error while reading file from path \"" << source << "\"!\n";
    }

    std::string temp = ss.str();
    const char* sourceCode = temp.c_str();  // source code we read

    int shader = glCreateShader(type);  // creating an empty shader of type vertex or fragment

    int success;    // was it successful
    char infoLog[512];  // error message
    glShaderSource(shader, 1, &sourceCode, NULL);   // set the source code for the shader
    glCompileShader(shader);    // compile the shader

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if (type == GL_VERTEX_SHADER) {
            printf("VERTEX");
        }
        else if (type == GL_FRAGMENT_SHADER) {
            printf("FRAGMENT");
        }
        printf("Shader has an error! The error: \n");
        printf(infoLog);
    }

    return shader;
}

unsigned int createShader(const char* vsSource, const char* fsSource) {
    // creates a combined shader program 

    unsigned int program;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    program = glCreateProgram();    // creates an empty combined shader program
    vertexShader = compileShader(GL_VERTEX_SHADER, vsSource);   // creates vertex shader
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource);   // creates fragment shader

    glAttachShader(program, vertexShader);  // attaches vertex shader to empty shader program
    glAttachShader(program, fragmentShader);    // attaches fragment shader to empty shader program

    glLinkProgram(program); // connects them in a combined shader program
    glValidateProgram(program); // execute validation of the newly created program

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cout << "Combine shader has an error! The error: " << infoLog << "\n";
    }

    // shader codes are in the combined shader so we delete them to save memory space
    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return program;
}

static unsigned loadImageToTexture(const char* filePath) {
    int TextureWidth;
    int TextureHeight;
    int TextureChannels;
    unsigned char* ImageData = stbi_load(filePath, &TextureWidth, &TextureHeight, &TextureChannels, 0);
    if (ImageData != NULL)
    {
        //Slike se osnovno ucitavaju naopako pa se moraju ispraviti da budu uspravne
        stbi__vertical_flip(ImageData, TextureWidth, TextureHeight, TextureChannels);

        // Provjerava koji je format boja ucitane slike
        GLint InternalFormat = -1;
        switch (TextureChannels) {
        case 1: InternalFormat = GL_RED; break;
        case 3: InternalFormat = GL_RGB; break;
        case 4: InternalFormat = GL_RGBA; break;
        default: InternalFormat = GL_RGB; break;
        }

        unsigned int Texture;
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, TextureWidth, TextureHeight, 0, InternalFormat, GL_UNSIGNED_BYTE, ImageData);
        glBindTexture(GL_TEXTURE_2D, 0);
        // oslobadjanje memorije zauzete sa stbi_load posto vise nije potrebna
        stbi_image_free(ImageData);
        return Texture;
    }
    else
    {
        std::cout << "Textura nije ucitana! Putanja texture: " << filePath << std::endl;
        stbi_image_free(ImageData);
        return 0;
    }
}
