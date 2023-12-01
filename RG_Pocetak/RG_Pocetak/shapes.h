const float PI = 3.14159265358979323846; 
const unsigned int oneTriangleSize = 18;
const unsigned int circleFillSize = oneTriangleSize * 2;
const unsigned int circleVerticesSize = 360 * oneTriangleSize;
const unsigned int rectSize = oneTriangleSize * 2;
const unsigned int lineSize = 12;
const unsigned int circleSize = circleVerticesSize + circleFillSize;

unsigned int drawCircle(float vertices[], unsigned int startingIndex, float cx, float cy, float radiusX, float radiusY, float color[]);
unsigned int drawRect(float vertices[], unsigned int startingIndex, float x, float y, float width, float height, float color[]);
unsigned int drawTriangle(float vertices[], unsigned int startingIndex, float point1[], float point2[], float point3[], float color[]);
unsigned int drawLine(float vertices[], unsigned int startingIndex, float point1[], float point2[], float color[]);
