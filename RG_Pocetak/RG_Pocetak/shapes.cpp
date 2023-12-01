#include <iostream>
#include "shapes.h"
#include <cmath>


unsigned int drawCircle(float vertices[], unsigned int startingIndex, float cx, float cy, float radiusX, float radiusY, float color[]) {
    std::cout << "Started with index: " << startingIndex << "\n";

    float offsetX = cx;
    float offsetY = cy;
    for (int i = 0; i < circleVerticesSize / oneTriangleSize; ++i) {
        float radians = i * PI / 180.0;
        float x = radiusX * cos(radians) + offsetX;
        float y = radiusY * sin(radians) + offsetY;
        float restX = 0.0f + offsetX;
        float restY = 0.0f + offsetY;
        vertices[startingIndex + i * oneTriangleSize + 0] = x;    // x
        vertices[startingIndex + i * oneTriangleSize + 1] = y;    // y
        vertices[startingIndex + i * oneTriangleSize + 2] = color[0];  // R
        vertices[startingIndex + i * oneTriangleSize + 3] = color[1];  // G
        vertices[startingIndex + i * oneTriangleSize + 4] = color[2];  // B
        vertices[startingIndex + i * oneTriangleSize + 5] = color[3];  // A
        vertices[startingIndex + i * oneTriangleSize + 6] = x;   // x
        vertices[startingIndex + i * oneTriangleSize + 7] = restY;  // y
        vertices[startingIndex + i * oneTriangleSize + 8] = color[0];  // R
        vertices[startingIndex + i * oneTriangleSize + 9] = color[1];  // G
        vertices[startingIndex + i * oneTriangleSize + 10] = color[2]; // B
        vertices[startingIndex + i * oneTriangleSize + 11] = color[3]; // A
        vertices[startingIndex + i * oneTriangleSize + 12] = restX; // x
        vertices[startingIndex + i * oneTriangleSize + 13] = y;   // y
        vertices[startingIndex + i * oneTriangleSize + 14] = color[0]; // R
        vertices[startingIndex + i * oneTriangleSize + 15] = color[1]; // G
        vertices[startingIndex + i * oneTriangleSize + 16] = color[2]; // B
        vertices[startingIndex + i * oneTriangleSize + 17] = color[3]; // A
    }
	float radiansForFillSquare1 = 0 * PI / 180.0;
	float x1 = radiusX * cos(radiansForFillSquare1) + offsetX;
	float y1 = radiusY * sin(radiansForFillSquare1) + offsetY;
	float radiansForFillSquare2 = 90 * PI / 180.0;
	float x2 = radiusX * cos(radiansForFillSquare2) + offsetX;
	float y2 = radiusY * sin(radiansForFillSquare2) + offsetY;
	float radiansForFillSquare3 = 180 * PI / 180.0;
	float x3 = radiusX * cos(radiansForFillSquare3) + offsetX;
	float y3 = radiusY * sin(radiansForFillSquare3) + offsetY;
	float radiansForFillSquare4 = 270 * PI / 180.0;
	float x4 = radiusX * cos(radiansForFillSquare4) + offsetX;
	float y4 = radiusY * sin(radiansForFillSquare4) + offsetY;
	vertices[startingIndex + circleVerticesSize + 0] = x1;
	vertices[startingIndex + circleVerticesSize + 1] = y1;
	vertices[startingIndex + circleVerticesSize + 2] = color[0];
	vertices[startingIndex + circleVerticesSize + 3] = color[1];
	vertices[startingIndex + circleVerticesSize + 4] = color[2];
	vertices[startingIndex + circleVerticesSize + 5] = color[3];
	vertices[startingIndex + circleVerticesSize + 6] = x2;
	vertices[startingIndex + circleVerticesSize + 7] = y2;
	vertices[startingIndex + circleVerticesSize + 8] = color[0];
	vertices[startingIndex + circleVerticesSize + 9] = color[1];
	vertices[startingIndex + circleVerticesSize + 10] = color[2];
	vertices[startingIndex + circleVerticesSize + 11] = color[3];
	vertices[startingIndex + circleVerticesSize + 12] = x3;
	vertices[startingIndex + circleVerticesSize + 13] = y3;
	vertices[startingIndex + circleVerticesSize + 14] = color[0];
	vertices[startingIndex + circleVerticesSize + 15] = color[1];
	vertices[startingIndex + circleVerticesSize + 16] = color[2];
	vertices[startingIndex + circleVerticesSize + 17] = color[3];
	vertices[startingIndex + circleVerticesSize + 18] = x3;
	vertices[startingIndex + circleVerticesSize + 19] = y3;
	vertices[startingIndex + circleVerticesSize + 20] = color[0];
	vertices[startingIndex + circleVerticesSize + 21] = color[1];
	vertices[startingIndex + circleVerticesSize + 22] = color[2];
	vertices[startingIndex + circleVerticesSize + 23] = color[3];
	vertices[startingIndex + circleVerticesSize + 24] = x4;
	vertices[startingIndex + circleVerticesSize + 25] = y4;
	vertices[startingIndex + circleVerticesSize + 26] = color[0];
	vertices[startingIndex + circleVerticesSize + 27] = color[1];
	vertices[startingIndex + circleVerticesSize + 28] = color[2];
	vertices[startingIndex + circleVerticesSize + 29] = color[3];
	vertices[startingIndex + circleVerticesSize + 30] = x1;
	vertices[startingIndex + circleVerticesSize + 31] = y1;
	vertices[startingIndex + circleVerticesSize + 32] = color[0];
	vertices[startingIndex + circleVerticesSize + 33] = color[1];
	vertices[startingIndex + circleVerticesSize + 34] = color[2];
	vertices[startingIndex + circleVerticesSize + 35] = color[3];

	unsigned int endingIndex = startingIndex + circleVerticesSize + circleFillSize;
    std::cout << "Ended with index: " << endingIndex << "\n\n";
	return endingIndex;
}

// x and y are bottom left coordinates
unsigned int drawRect(float vertices[], unsigned int startingIndex, float x, float y, float width, float height, float color[]) {
    std::cout << "Started with index: " << startingIndex << "\n";

	vertices[startingIndex + 0] = x;
	vertices[startingIndex + 1] = y;
	vertices[startingIndex + 2] = color[0];
	vertices[startingIndex + 3] = color[1];
	vertices[startingIndex + 4] = color[2];
	vertices[startingIndex + 5] = color[3];
	vertices[startingIndex + 6] = x + width;
	vertices[startingIndex + 7] = y;
	vertices[startingIndex + 8] = color[0];
	vertices[startingIndex + 9] = color[1];
	vertices[startingIndex + 10] = color[2];
	vertices[startingIndex + 11] = color[3];
	vertices[startingIndex + 12] = x + width;
	vertices[startingIndex + 13] = y + height;
	vertices[startingIndex + 14] = color[0];
	vertices[startingIndex + 15] = color[1];
	vertices[startingIndex + 16] = color[2];
	vertices[startingIndex + 17] = color[3];
	vertices[startingIndex + 18] = x + width;
	vertices[startingIndex + 19] = y + height;
	vertices[startingIndex + 20] = color[0];
	vertices[startingIndex + 21] = color[1];
	vertices[startingIndex + 22] = color[2];
	vertices[startingIndex + 23] = color[3];
	vertices[startingIndex + 24] = x;
	vertices[startingIndex + 25] = y + height;
	vertices[startingIndex + 26] = color[0];
	vertices[startingIndex + 27] = color[1];
	vertices[startingIndex + 28] = color[2];
	vertices[startingIndex + 29] = color[3];
	vertices[startingIndex + 30] = x;
	vertices[startingIndex + 31] = y;
	vertices[startingIndex + 32] = color[0];
	vertices[startingIndex + 33] = color[1];
	vertices[startingIndex + 34] = color[2];
	vertices[startingIndex + 35] = color[3];

	unsigned int endingIndex = startingIndex + oneTriangleSize * 2;
    std::cout << "Ended with index: " << endingIndex << "\n\n";
	return endingIndex;
}

unsigned int drawTriangle(float vertices[], unsigned int startingIndex, float point1[], float point2[], float point3[], float color[]) {
    std::cout << "Started with index: " << startingIndex << "\n";

	vertices[startingIndex + 0] = point1[0];
    vertices[startingIndex + 1] = point1[1];
	vertices[startingIndex + 2] = color[0];
	vertices[startingIndex + 3] = color[1];
	vertices[startingIndex + 4] = color[2];
	vertices[startingIndex + 5] = color[3];
	vertices[startingIndex + 6] = point2[0];
	vertices[startingIndex + 7] = point2[1];
	vertices[startingIndex + 8] = color[0];
	vertices[startingIndex + 9] = color[1];
	vertices[startingIndex + 10] = color[2];
	vertices[startingIndex + 11] = color[3];
	vertices[startingIndex + 12] = point3[0];
	vertices[startingIndex + 13] = point3[1];
	vertices[startingIndex + 14] = color[0];
	vertices[startingIndex + 15] = color[1];
	vertices[startingIndex + 16] = color[2];
	vertices[startingIndex + 17] = color[3];

	unsigned int endingIndex = startingIndex + oneTriangleSize;
    std::cout << "Ended with index: " << endingIndex << "\n\n";
	return endingIndex;
}

unsigned int drawLine(float vertices[], unsigned int startingIndex, float point1[], float point2[], float color[]) {
	std::cout << "Started with index: " << startingIndex << "\n";

	vertices[startingIndex + 0] = point1[0];
    vertices[startingIndex + 1] = point1[1];
	vertices[startingIndex + 2] = color[0];
	vertices[startingIndex + 3] = color[1];
	vertices[startingIndex + 4] = color[2];
	vertices[startingIndex + 5] = color[3];
	vertices[startingIndex + 6] = point2[0];
	vertices[startingIndex + 7] = point2[1];
	vertices[startingIndex + 8] = color[0];
	vertices[startingIndex + 9] = color[1];
	vertices[startingIndex + 10] = color[2];
	vertices[startingIndex + 11] = color[3];

	unsigned int endingIndex = startingIndex + oneTriangleSize;
    std::cout << "Ended with index: " << endingIndex << "\n\n";
	return endingIndex;

}
