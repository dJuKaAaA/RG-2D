//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//const char* vertexShaderSource = R"(
//    #version 330 core
//    layout (location = 0) in vec2 aPos;
//    layout (location = 1) in vec4 aColor;
//
//    out vec4 color;
//
//    void main()
//    {
//        gl_Position = vec4(aPos, 0.0, 1.0);
//        color = aColor;
//    }
//)";
//
//const char* fragmentShaderSource = R"(
//    #version 330 core
//    in vec4 color;
//
//    out vec4 FragColor;
//
//    void main()
//    {
//        FragColor = color;
//    }
//)";
//
//void createVAO(float* vertices, int size, unsigned int stride, unsigned int* VAO, unsigned int* VBO)
//{
//    glGenVertexArrays(1, VAO);
//    glBindVertexArray(*VAO);
//
//    glGenBuffers(1, VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
//    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//int main()
//{
//    // Initialize GLFW
//    if (!glfwInit())
//    {
//        std::cerr << "Failed to initialize GLFW" << std::endl;
//        return -1;
//    }
//
//    // Set GLFW to use the core profile without deprecated functions
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // Create a GLFW window
//    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Shapes", nullptr, nullptr);
//    if (!window)
//    {
//        std::cerr << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    // Make the context of the window the main context for this thread
//    glfwMakeContextCurrent(window);
//
//    // Initialize GLEW
//    if (glewInit() != GLEW_OK)
//    {
//        std::cerr << "Failed to initialize GLEW" << std::endl;
//        return -1;
//    }
//
//    // Set the viewport size and register the callback for window resize
//    int width, height;
//    glfwGetFramebufferSize(window, &width, &height);
//    glViewport(0, 0, width, height);
//
//    // Vertex data for a triangle and a square
//    float vertices[] = {
//        // Triangle
//        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
//         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
//         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
//
//        // Square
//        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
//         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
//         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
//        -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f
//    };
//
//    unsigned int VAO, VBO;
//
//    // Call the function to create VAO and VBO
//    createVAO(vertices, sizeof(vertices), 6 * sizeof(float), &VAO, &VBO);
//
//    // Shader compilation and linking
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    unsigned int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // Main rendering loop
//    while (!glfwWindowShouldClose(window))
//    {
//        // Input handling
//        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//            glfwSetWindowShouldClose(window, true);
//
//        // Rendering code
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);
//
//        // Bind VAO
//        glBindVertexArray(VAO);
//
//        // Draw the triangle
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        // Draw the square
//        glDrawArrays(GL_QUADS, 3, 4);
//
//        // Unbind VAO
//        glBindVertexArray(0);
//
//        // Swap front and back buffers
//        glfwSwapBuffers(window);
//
//        // Poll for and process events
//        glfwPollEvents();
//    }
//
//    // Clean up
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteProgram(shaderProgram);
//
//    // Terminate GLFW
//    glfwTerminate();
//    return 0;
//}
