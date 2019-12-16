#include "pgr.h"

#include "sphere.h"

#include <vector>
#include <numeric>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/vector_angle.hpp>

#define HEXAGONSIZE 12
#define SQUARESIZE 12
#define CUBESIZE 12

using namespace std;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Data
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const float ground[][3] = {
	{ -10, 0, 10 }, { 10, 0, 10 }, { 10, 0, -10 }, { -10, 0, -10 } };


float square[][3]{
	{-0.5* SQUARESIZE , -0.5 * SQUARESIZE, 0}, {-0.5 * SQUARESIZE, 0.5 * SQUARESIZE ,0}, {0.5 * SQUARESIZE, 0.5 * SQUARESIZE, 0},
	{0.5 * SQUARESIZE, 0.5* SQUARESIZE, 0}, {0.5 * SQUARESIZE, -0.5 * SQUARESIZE ,0}, {-0.5 * SQUARESIZE, -0.5 * SQUARESIZE, 0}};

float hexagon[][3] = {
	{0, HEXAGONSIZE, 0}, {0.866025 * HEXAGONSIZE, 0.5 * HEXAGONSIZE}, {0, 0 ,0},
	{0.866025 * HEXAGONSIZE, 0.5 * HEXAGONSIZE}, {0.866025 * HEXAGONSIZE, -0.5 * HEXAGONSIZE}, {0,0,0},
	{0.866025 * HEXAGONSIZE, -0.5 * HEXAGONSIZE}, {0, -HEXAGONSIZE,0}, {0, 0, 0},
	{0, -HEXAGONSIZE,0}, {-0.866025 * HEXAGONSIZE, -0.5 * HEXAGONSIZE}, {0, 0 ,0},
	{-0.866025 * HEXAGONSIZE, -0.5 * HEXAGONSIZE}, {-0.866025 * HEXAGONSIZE, 0.5 * HEXAGONSIZE}, {0,0,0},
	{-0.866025 * HEXAGONSIZE, 0.5 * HEXAGONSIZE}, {0, HEXAGONSIZE,0}, {0, 0, 0}
};

float hexagon2[][3] = {
	{0, HEXAGONSIZE, 0}, {0.866025 * HEXAGONSIZE, 0.5 * HEXAGONSIZE}, {0, 0 ,0},

	{0.866025 * HEXAGONSIZE, -0.5 * HEXAGONSIZE}, {0, -HEXAGONSIZE,0}, {0, 0, 0},

	//{0, -HEXAGONSIZE,0}, {-0.866025 * HEXAGONSIZE, -0.5 * HEXAGONSIZE}, {0, 0 ,0},
	//{-0.866025 * HEXAGONSIZE, -0.5 * HEXAGONSIZE}, {-0.866025 * HEXAGONSIZE, 0.5 * HEXAGONSIZE}, {0,0,0},
	{-0.866025 * HEXAGONSIZE, 0.5 * HEXAGONSIZE}, {0, HEXAGONSIZE,0}, {0, 0, 0} //imp
};

float cube[][3] = {
	{-0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE}, {-0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE}, {0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE},//plane z = -0.5
	{0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE}, {0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE}, {-0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE},//FLIP
	
	{-0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE}, {-0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE}, {0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE}, //plane z = 0.5
	{0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE}, {0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE}, {-0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE}, 
	


	{-0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE}, {-0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE}, {-0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE},//plane x = -0.5
	{-0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE}, {-0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE}, {-0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE},
	
	{0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE}, {0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE}, {0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE},//plane x = 0.5
	{0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE}, {0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE}, {0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE},//FLIP



	{-0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE}, {-0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE}, {0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE},//plane y = -0.5
	{0.5 * CUBESIZE, -0.5 * CUBESIZE, 0.5 * CUBESIZE}, {0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE}, {-0.5 * CUBESIZE, -0.5 * CUBESIZE, -0.5 * CUBESIZE},
	
	{-0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE}, {0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE}, {0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE},//plane y = 0.5
	{0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE}, {-0.5 * CUBESIZE, 0.5 * CUBESIZE, 0.5 * CUBESIZE}, {-0.5 * CUBESIZE, 0.5 * CUBESIZE, -0.5 * CUBESIZE},
	
};

float triangle[][3] = {
	{-5 ,-5, 0}, {-5, 5 ,0}, {5, 5, 0}};

unsigned triangleEbo[][3]{
	{0, 1, 2}
};

GLuint sphereVBO, sphereEBO;
GLuint squareVBO;
GLuint groundVBO;

const glm::vec3 position0(0, 10, 0), speed0(0.1, 0, 0);

glm::vec3 position = position0, speed = speed0;

int width, height;
float rx = 90.0f, ry = 30.0f, pz = 50.0f;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Shaders
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GLuint spVS, scFS, Prog;
GLuint sphere2FS, Prog2;
GLuint scelVS, scelFS, Prog3;

GLuint positionAttrib, mvpUniform, colorUniform, lightPosUniform;
GLuint positionAttrib2, mvpUniform2, animationUniform;

GLuint 	positionAttrib3, normalAttrib3, vpAttrib3, mAttrib3,
		lightPosAttrib3, cameraPosAttrib3, colorAttrib3;


float planetDistance = 2.0f;
float timespeed = 1.0f;

bool canCut = true;
bool wireframe = false;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Vertex {
public:
	Vertex(float a[3]) {
		x = a[0];
		y = a[1];
		z = a[2];
	};
	Vertex(float x1, float y1, float z1) {
		x = x1;
		y = y1;
		z = z1;
	}
	Vertex(glm::vec3 a) {
		x = (float)a.x;
		y = (float)a.y;
		z = (float)a.z;
	}

	operator glm::vec3() const{
		return glm::vec3{ x, y, z };
	}
	float x, y, z;
};

enum MeshVertexStatus
{
	INTERCEPTED = 0, LEFT, RIGHT, MID, MID_LEFT, MID_RIGHT, INCIDENTEDGE, UNNASIGNED
};

class Interception {
public:
	Interception() {
		valid = false;
		edgeType = UNNASIGNED;
	}
	bool valid;
	MeshVertexStatus edgeType;//if it can't find an interception, it sends on which side the triangle is
	glm::vec3 point;
};

class Obj {
public:
	Obj() {
		enabled = true;
		hasNormals = false;
		prog = &Prog;
		pos = { 0, 0, 0 };
		glGenBuffers(1, &VBO);
	}
	Obj(vector<Vertex> v, GLuint* program = &Prog, glm::vec3 position = { 0,0,0 }, glm::vec3 color1 = { 1, 0, 0 }) {
		vec = v;
		enabled = true;
		hasNormals = false;
		prog = program;
		color = color1;
		pos = position;
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &NormalBuffer);
	}
	Obj(vector<Vertex> v, vector<Vertex> n, GLuint* program = &Prog, glm::vec3 position = { 0,0,0 }, glm::vec3 color1 = { 1, 0, 0 }) {
		vec = v;
		normals = n;
		enabled = true;
		hasNormals = true;
		prog = program;
		color = color1;
		pos = position;
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &NormalBuffer);
	}

	vector<Vertex> vec, normals;
	GLuint VBO, NormalBuffer, *prog;
	glm::vec3 pos, color;
	bool enabled;
	bool hasNormals;
};

vector<Obj> stuff;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Event handlers
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

glm::vec4 plane;
glm::vec3 refVec;

glm::vec3 light = { 0, 0, 50 };

Vertex negativeVertex(Vertex a) {
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	return a;
}

Vertex normalize(Vertex a) {
	float w = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	a.x /= w;
	a.y /= w;
	a.z /= w;
	return a;
}

glm::vec4 createPlane(glm::vec3 speed, glm::vec3 wire = { 0, 1, 0 }, glm::vec3 point = { 0,0,0 }) { //WORK IN PROGRESS
	float n = sqrtf(pow(speed.x, 2) - pow(speed.z, 2)); //only works for wire = {0,1,0}
	glm::vec4 plane = { speed.x / n, 0, speed.z / n, 0 };
	plane.w = plane.x * point.x + plane.y * point.y + plane.z * point.z;

	return plane;
}

MeshVertexStatus vertexSide(glm::vec4 plane, glm::vec3 point) {
	float d = plane.x * point.x + plane.y * point.y + plane.z * point.z;
	if (d > plane.w)
		return RIGHT;
	else if (d < plane.w)
		return LEFT;
	else
		return MID;
}

Interception interceptionPlaneEdge(glm::vec4 plane, glm::vec3 p1, glm::vec3 p2) {
	MeshVertexStatus p1V = vertexSide(plane, p1), p2V = vertexSide(plane, p2);
	Interception i;

	if (p1V == p2V) { 
		if (p1V == MID) {//slices through the two points
			i.edgeType = INCIDENTEDGE;
		}
		else {//the two points are on one of the sides
			i.edgeType = p1V;
		}
	}
	else
	{
		if (p1V == MID) { //one point is on the middle
			i.edgeType = (p2V == LEFT) ? MID_LEFT : MID_RIGHT;
			i.point = p1;
			i.valid = true;
		}
		else if (p2V == MID){
			i.edgeType = (p1V == LEFT) ? MID_LEFT : MID_RIGHT;
			i.point = p2;
			i.valid = true;
		}
		else //normal edge
		{
			glm::vec3 v;
			v = p2 - p1;
			float k = ((plane.w - plane.x * p1.x - plane.y * p1.y - plane.z * p1.z)
				/ (plane.x * v.x + plane.y * v.y + plane.z * v.z));

			i.edgeType = INTERCEPTED;
			i.point = k * v + p1;
			i.valid = true;
		}
	}
	return i;
}

bool hasBiggerAngle(glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 planeNormal = (glm::vec3)plane;
	planeNormal = glm::normalize(planeNormal);
	v1 = glm::normalize(v1);
	v2 = glm::normalize(v2);
	return (glm::orientedAngle(refVec, v1, planeNormal) > glm::orientedAngle(refVec, v2, planeNormal));
}

void cut(Obj* obj, glm::vec4 plane1, bool filled=true) {
	plane = plane1;
	if (canCut && obj->enabled) {

		if (!obj->hasNormals) {
			obj->enabled = false;
			int workingTriangle;
			Obj leftObject, rightObject;
			leftObject.enabled = true;
			rightObject.enabled = true;
			leftObject.color = { 0, 1, 0 };
			rightObject.color = { 0, 0, 1 };
			leftObject.pos = { -5, 0, 0 };
			rightObject.pos = { 5, 0, 0 };
			leftObject.prog = obj->prog;
			rightObject.prog = obj->prog;

			vector<glm::vec3> interceptionPoints;
			short edgeSide;
			for (workingTriangle = 0; workingTriangle < obj->vec.size()/3; workingTriangle++) {
				int curr = 0;
				glm::vec3 i[3], isolated, edgeBegin, edgeEnd, tmp, leftVertex, rightVertex;
				Interception inter;

				bool invert = false, vertexEdgeException = false;

				///////////////////////
				Interception interceptions[3];
				glm::vec3 mid;
				bool leftEdges = false, rightEdges = false, intercepted = false, midLeftEdges = false, midRightEdges = false, incidentEdges = false;
				for (int j = 0; j < 3; j++)
				{
					interceptions[j] = interceptionPlaneEdge(plane, obj->vec[workingTriangle * 3 + j], obj->vec[workingTriangle * 3 + (j + 1) % 3]);
					switch (interceptions[j].edgeType)
					{
					case LEFT:
						leftEdges = true;
						edgeBegin = obj->vec[workingTriangle * 3 + j];
						edgeEnd = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						isolated = obj->vec[workingTriangle * 3 + (j + 2) % 3];
						if (j == 1) invert = true;

						break;
					case RIGHT:
						rightEdges = true;
						edgeBegin = obj->vec[workingTriangle * 3 + j];
						edgeEnd = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						isolated = obj->vec[workingTriangle * 3 + (j + 2) % 3];
						if (j == 1) invert = true;

						break;
					case INTERCEPTED:
						intercepted = true;
						i[curr] = interceptions[j].point;
						interceptionPoints.push_back(interceptions[j].point);
						curr++;
						break;
					case MID_LEFT:
						midLeftEdges = true;
						mid = interceptions[j].point;
						interceptionPoints.push_back(interceptions[j].point);
						if (mid == (glm::vec3)obj->vec[workingTriangle * 3 + j])
							leftVertex = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						else
							leftVertex = obj->vec[workingTriangle * 3 + j];
						break;
					case MID_RIGHT:
						midRightEdges = true;
						mid = interceptions[j].point;
						interceptionPoints.push_back(interceptions[j].point);
						if (mid == (glm::vec3)obj->vec[workingTriangle * 3 + j])
							rightVertex = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						else
							rightVertex = obj->vec[workingTriangle * 3 + j];
						break;
					case INCIDENTEDGE:
						incidentEdges = true;
						interceptionPoints.push_back(obj->vec[workingTriangle * 3 + j]);
						interceptionPoints.push_back(obj->vec[workingTriangle * 3 + (j+1)%3]);
						break;
					default:
						break;
					}
				}

				if (invert) {
					tmp = i[0];
					i[0] = i[1];
					i[1] = tmp;
				}

				if (leftEdges && !midLeftEdges && !intercepted || leftEdges && midLeftEdges || incidentEdges && midLeftEdges) {
					leftObject.vec.push_back(obj->vec[workingTriangle * 3 + 0]);
					leftObject.vec.push_back(obj->vec[workingTriangle * 3 + 1]);
					leftObject.vec.push_back(obj->vec[workingTriangle * 3 + 2]);
				}

				else if (rightEdges && !midRightEdges && !intercepted || rightEdges && midRightEdges || incidentEdges && midRightEdges) {
					rightObject.vec.push_back(obj->vec[workingTriangle * 3 + 0]);
					rightObject.vec.push_back(obj->vec[workingTriangle * 3 + 1]);
					rightObject.vec.push_back(obj->vec[workingTriangle * 3 + 2]);
				}

				else if (leftEdges && intercepted){
					//RIGHT SIDE
					rightObject.vec.push_back(i[1]);
					rightObject.vec.push_back(i[0]);
					rightObject.vec.push_back(isolated);
					//LEFT SIDE
					leftObject.vec.push_back(edgeBegin);
					leftObject.vec.push_back(edgeEnd);
					leftObject.vec.push_back(i[0]);

					leftObject.vec.push_back(edgeBegin);
					leftObject.vec.push_back(i[0]);
					leftObject.vec.push_back(i[1]);
				}

				else if (rightEdges && intercepted) {
					//LEFT SIDE
					leftObject.vec.push_back(i[1]);
					leftObject.vec.push_back(i[0]);
					leftObject.vec.push_back(isolated);
					//RIGHT SIDE
					rightObject.vec.push_back(edgeBegin);
					rightObject.vec.push_back(edgeEnd);
					rightObject.vec.push_back(i[0]);

					rightObject.vec.push_back(edgeBegin);
					rightObject.vec.push_back(i[0]);
					rightObject.vec.push_back(i[1]);

				}

				else if (midLeftEdges && midRightEdges) {
					leftObject.vec.push_back(leftVertex);
					leftObject.vec.push_back(i[0]);
					leftObject.vec.push_back(mid);

					rightObject.vec.push_back(rightVertex);
					rightObject.vec.push_back(mid);
					rightObject.vec.push_back(i[0]);

				}
			}


			//SECTION FACE 
			if (filled && interceptionPoints.size() > 2) {
				glm::vec3 average = { 0, 0, 0 };
				for (int i = 0; i < interceptionPoints.size(); i++)
				{
					average += interceptionPoints[i];
				}
				average /= interceptionPoints.size();

				refVec = glm::normalize(interceptionPoints[0] - average);

				sort(interceptionPoints.begin()++, interceptionPoints.end(), hasBiggerAngle);

				for (int i = 0; i < interceptionPoints.size(); i++)
				{
					leftObject.vec.push_back(average);
					leftObject.vec.push_back(interceptionPoints[i]);
					leftObject.vec.push_back(interceptionPoints[(i+1)%interceptionPoints.size()]);

					rightObject.vec.push_back(average);
					rightObject.vec.push_back(interceptionPoints[(i + 1) % interceptionPoints.size()]);
					rightObject.vec.push_back(interceptionPoints[i]);

				}
			}


			canCut = false;
			stuff.push_back(leftObject);
			stuff.push_back(rightObject);
		}

		else if (obj->hasNormals) {
			obj->enabled = false;
			int workingTriangle;
			Obj leftObject, rightObject;
			leftObject.enabled = true;
			rightObject.enabled = true;
			leftObject.color = { 0, 1, 0 };
			rightObject.color = { 0, 0, 1 };
			leftObject.pos = { -5, 0, 0 };
			rightObject.pos = { 5, 0, 0 };
			leftObject.prog = obj->prog;
			rightObject.prog = obj->prog;

			vector<glm::vec3> interceptionPoints;
			short edgeSide;
			for (workingTriangle = 0; workingTriangle < obj->vec.size() / 3; workingTriangle++) {
				int curr = 0;
				glm::vec3 i[3], isolated, edgeBegin, edgeEnd, tmp, leftVertex, rightVertex;
				Interception inter;

				bool invert = false, vertexEdgeException = false;

				///////////////////////
				Interception interceptions[3];
				glm::vec3 mid;
				bool leftEdges = false, rightEdges = false, intercepted = false, midLeftEdges = false, midRightEdges = false, incidentEdges = false;
				for (int j = 0; j < 3; j++)
				{
					interceptions[j] = interceptionPlaneEdge(plane, obj->vec[workingTriangle * 3 + j], obj->vec[workingTriangle * 3 + (j + 1) % 3]);
					switch (interceptions[j].edgeType)
					{
					case LEFT:
						leftEdges = true;
						edgeBegin = obj->vec[workingTriangle * 3 + j];
						edgeEnd = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						isolated = obj->vec[workingTriangle * 3 + (j + 2) % 3];
						if (j == 1) invert = true;

						break;
					case RIGHT:
						rightEdges = true;
						edgeBegin = obj->vec[workingTriangle * 3 + j];
						edgeEnd = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						isolated = obj->vec[workingTriangle * 3 + (j + 2) % 3];
						if (j == 1) invert = true;

						break;
					case INTERCEPTED:
						intercepted = true;
						i[curr] = interceptions[j].point;
						interceptionPoints.push_back(interceptions[j].point);
						curr++;
						break;
					case MID_LEFT:
						midLeftEdges = true;
						mid = interceptions[j].point;
						interceptionPoints.push_back(interceptions[j].point);
						if (mid == (glm::vec3)obj->vec[workingTriangle * 3 + j])
							leftVertex = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						else
							leftVertex = obj->vec[workingTriangle * 3 + j];
						break;
					case MID_RIGHT:
						midRightEdges = true;
						mid = interceptions[j].point;
						interceptionPoints.push_back(interceptions[j].point);
						if (mid == (glm::vec3)obj->vec[workingTriangle * 3 + j])
							rightVertex = obj->vec[workingTriangle * 3 + (j + 1) % 3];
						else
							rightVertex = obj->vec[workingTriangle * 3 + j];
						break;
					case INCIDENTEDGE:
						incidentEdges = true;
						interceptionPoints.push_back(obj->vec[workingTriangle * 3 + j]);
						interceptionPoints.push_back(obj->vec[workingTriangle * 3 + (j + 1) % 3]);
						break;
					default:
						break;
					}
				}

				if (invert) {
					tmp = i[0];
					i[0] = i[1];
					i[1] = tmp;
				}

				if (leftEdges && !midLeftEdges && !intercepted || leftEdges && midLeftEdges || incidentEdges && midLeftEdges) {
					leftObject.vec.push_back(obj->vec[workingTriangle * 3 + 0]);
					leftObject.vec.push_back(obj->vec[workingTriangle * 3 + 1]);
					leftObject.vec.push_back(obj->vec[workingTriangle * 3 + 2]);

					leftObject.normals.push_back(obj->normals[workingTriangle * 3 + 0]);
					leftObject.normals.push_back(obj->normals[workingTriangle * 3 + 1]);
					leftObject.normals.push_back(obj->normals[workingTriangle * 3 + 2]);
				}

				else if (rightEdges && !midRightEdges && !intercepted || rightEdges && midRightEdges || incidentEdges && midRightEdges) {
					rightObject.vec.push_back(obj->vec[workingTriangle * 3 + 0]);
					rightObject.vec.push_back(obj->vec[workingTriangle * 3 + 1]);
					rightObject.vec.push_back(obj->vec[workingTriangle * 3 + 2]);
					//normals
					rightObject.normals.push_back(obj->normals[workingTriangle * 3 + 0]);
					rightObject.normals.push_back(obj->normals[workingTriangle * 3 + 1]);
					rightObject.normals.push_back(obj->normals[workingTriangle * 3 + 2]);
				}

				else if (leftEdges && intercepted) {
					//RIGHT SIDE
					rightObject.vec.push_back(i[1]);
					rightObject.vec.push_back(i[0]);
					rightObject.vec.push_back(isolated);
					//normals
					rightObject.normals.push_back(i[1]);
					rightObject.normals.push_back(i[0]);
					rightObject.normals.push_back(isolated);

					//LEFT SIDE
					leftObject.vec.push_back(edgeBegin);
					leftObject.vec.push_back(edgeEnd);
					leftObject.vec.push_back(i[0]);

					leftObject.vec.push_back(edgeBegin);
					leftObject.vec.push_back(i[0]);
					leftObject.vec.push_back(i[1]);
					//normals
					leftObject.normals.push_back(edgeBegin);
					leftObject.normals.push_back(edgeEnd);
					leftObject.normals.push_back(i[0]);

					leftObject.normals.push_back(edgeBegin);
					leftObject.normals.push_back(i[0]);
					leftObject.normals.push_back(i[1]);
				}

				else if (rightEdges && intercepted) {
					//LEFT SIDE
					leftObject.vec.push_back(i[1]);
					leftObject.vec.push_back(i[0]);
					leftObject.vec.push_back(isolated);
					//normals
					leftObject.normals.push_back(i[1]);
					leftObject.normals.push_back(i[0]);
					leftObject.normals.push_back(isolated);
					//RIGHT SIDE
					rightObject.vec.push_back(edgeBegin);
					rightObject.vec.push_back(edgeEnd);
					rightObject.vec.push_back(i[0]);

					rightObject.vec.push_back(edgeBegin);
					rightObject.vec.push_back(i[0]);
					rightObject.vec.push_back(i[1]);
					//normals
					rightObject.normals.push_back(edgeBegin);
					rightObject.normals.push_back(edgeEnd);
					rightObject.normals.push_back(i[0]);

					rightObject.normals.push_back(edgeBegin);
					rightObject.normals.push_back(i[0]);
					rightObject.normals.push_back(i[1]);
				}

				else if (midLeftEdges && midRightEdges) {
					leftObject.vec.push_back(leftVertex);
					leftObject.vec.push_back(i[0]);
					leftObject.vec.push_back(mid);

					rightObject.vec.push_back(rightVertex);
					rightObject.vec.push_back(mid);
					rightObject.vec.push_back(i[0]);

					//normals

					leftObject.normals.push_back(leftVertex);
					leftObject.normals.push_back(i[0]);
					leftObject.normals.push_back(mid);

					rightObject.normals.push_back(rightVertex);
					rightObject.normals.push_back(mid);
					rightObject.normals.push_back(i[0]);

				}
			}


			//SECTION FACE 
			if (filled && interceptionPoints.size() > 2) {
				glm::vec3 average = { 0, 0, 0 };
				for (int i = 0; i < interceptionPoints.size(); i++)
				{
					average += interceptionPoints[i];
				}
				average /= interceptionPoints.size();

				refVec = glm::normalize(interceptionPoints[0] - average);

				sort(interceptionPoints.begin()++, interceptionPoints.end(), hasBiggerAngle);

				for (int i = 0; i < interceptionPoints.size(); i++)
				{
					leftObject.vec.push_back(average);
					leftObject.vec.push_back(interceptionPoints[i]);
					leftObject.vec.push_back(interceptionPoints[(i + 1) % interceptionPoints.size()]);

					rightObject.vec.push_back(average);
					rightObject.vec.push_back(interceptionPoints[(i + 1) % interceptionPoints.size()]);
					rightObject.vec.push_back(interceptionPoints[i]);
					//normals
					leftObject.normals.push_back(glm::vec3(plane));
					leftObject.normals.push_back(interceptionPoints[i]);
					leftObject.normals.push_back(interceptionPoints[(i + 1) % interceptionPoints.size()]);

					rightObject.normals.push_back(-glm::vec3(plane));
					rightObject.normals.push_back(-interceptionPoints[(i + 1) % interceptionPoints.size()]);
					rightObject.normals.push_back(-interceptionPoints[i]);
					

				}
			}


			canCut = false;
			stuff.push_back(leftObject);
			stuff.push_back(rightObject);
		}
	}
}

void onInit()
{
	if(wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	spVS = compileShader(GL_VERTEX_SHADER, loadFile("data\\simpleplace.vs").c_str());
	scFS = compileShader(GL_FRAGMENT_SHADER, loadFile("data\\solidColor.fs").c_str());

	scelVS = compileShader(GL_VERTEX_SHADER, loadFile("data\\celShading.vs").c_str());
	scelFS = compileShader(GL_FRAGMENT_SHADER, loadFile("data\\celShading.fs").c_str());

	Prog = linkShader(2, spVS, scFS);
	Prog3 = linkShader(2, scelVS, scelFS);

	positionAttrib = glGetAttribLocation(Prog, "position");
	mvpUniform = glGetUniformLocation(Prog, "mvp");
	colorUniform = glGetUniformLocation(Prog, "color");
	lightPosUniform = glGetUniformLocation(Prog, "lightPos");


	vpAttrib3 = glGetUniformLocation(Prog3, "vp");
	mAttrib3 = glGetUniformLocation(Prog3, "m");
	lightPosAttrib3 = glGetUniformLocation(Prog3, "lightPos");
	cameraPosAttrib3 = glGetUniformLocation(Prog3, "cameraPos");
	colorAttrib3 = glGetUniformLocation(Prog3, "color");

	//VBO 
	Obj hexagonVBO = Obj(vector<Vertex>(hexagon, hexagon + sizeof(hexagon) / sizeof(*hexagon)));
	Obj squareVBO = Obj(vector<Vertex>(square, square + sizeof(square) / sizeof(*square)));
	Obj triangleVBO = Obj(vector<Vertex>(triangle, triangle + sizeof(triangle) / sizeof(*triangle)));
	Obj cubeVBO = Obj(vector<Vertex>(cube, cube + sizeof(cube) / sizeof(*cube)));

	Obj cubeVBOWNormal = Obj(vector<Vertex>(cube, cube + sizeof(cube) / sizeof(*cube)), vector<Vertex>(cube, cube + sizeof(cube) / sizeof(*cube)), &Prog3);
	//stuff.push_back(hexagonVBO);
	stuff.push_back(cubeVBOWNormal);
	//stuff.push_back(squareVBO);
	//stuff.push_back(triangleVBO);
}

void onWindowRedraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // t - absolute time, dt - time step
    static float t0 = SDL_GetTicks()/1000.0f;
    static float t = t0;
    float t1 = SDL_GetTicks()/1000.0f;
    float dt = (t1-t)*timespeed;
    t = t1;

    // Simulation step
    //position += speed*dt;
   // speed += glm::vec3(0.0f, -dt*9.81, 0.0f);//g*dt
	const float sphere_radius = 1.0f;

    //Setup orbital camera
    float radx = glm::radians(rx);
    float rady = glm::radians(ry);

    float x = pz * cos(rady) * cos(radx);
    float y = pz * sin(rady);
    float z = pz * cos(rady) * sin(radx);

    glm::vec4 camPos = glm::vec4(x, y, z, 1);
    glm::mat4 view = glm::lookAt(glm::vec3(camPos), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 persp = glm::perspective(45.0f, (float)width / (float)height, 1.0f, 1000.0f);

	glEnableVertexAttribArray(positionAttrib);
	glEnableVertexAttribArray(positionAttrib2);


	for each (Obj var in stuff)
	{
		if (var.enabled) {

			if (*var.prog == Prog)
			{
				glUseProgram(Prog);

				glUniform3f(colorUniform, var.color.r, var.color.g, var.color.b);
				glUniform3f(lightPosUniform, light.x, light.y, light.z);


				glm::mat4 sphere1model = glm::translate(var.pos);
				glm::mat4 mvp1 = persp * view * sphere1model;
				glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp1));

				glBindBuffer(GL_ARRAY_BUFFER, var.VBO);
				glBufferData(GL_ARRAY_BUFFER, var.vec.size() * sizeof(Vertex), &var.vec.front(), GL_DYNAMIC_DRAW);

				glEnableVertexAttribArray(positionAttrib);
				glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glDrawArrays(GL_TRIANGLES, 0, var.vec.size());

				glDisableVertexAttribArray(positionAttrib);
			}

			else if (*var.prog == Prog3) {
				glUseProgram(Prog3);

				glUniform3f(colorAttrib3, var.color.r, var.color.g, var.color.b);
				glUniform3f(lightPosAttrib3, light.x, light.y, light.z);

				glm::mat4 sphere3model = glm::translate(var.pos);
				glm::mat4 vp3 = persp * view;
				glUniformMatrix4fv(vpAttrib3, 1, GL_FALSE, glm::value_ptr(vp3));
				glUniformMatrix4fv(mAttrib3, 1, GL_FALSE, glm::value_ptr(sphere3model));


				glBindBuffer(GL_ARRAY_BUFFER, var.VBO);
				glBufferData(GL_ARRAY_BUFFER, var.vec.size() * sizeof(Vertex), &var.vec.front(), GL_DYNAMIC_DRAW);

				glEnableVertexAttribArray(1);

				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				glBindBuffer(GL_ARRAY_BUFFER, var.NormalBuffer);
				glBufferData(GL_ARRAY_BUFFER, var.vec.size() * sizeof(Vertex), &var.vec.front(), GL_DYNAMIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				glBindBuffer(GL_ARRAY_BUFFER, var.NormalBuffer);
				glBufferData(GL_ARRAY_BUFFER, var.vec.size() * sizeof(Vertex), &var.vec.front(), GL_DYNAMIC_DRAW);

				glDrawArrays(GL_TRIANGLES, 0, var.vec.size());

				glDisableVertexAttribArray(positionAttrib3);
				glDisableVertexAttribArray(normalAttrib3);

			}

		}
	}

    SDL_GL_SwapBuffers();
}

void onWindowResized(int w, int h)
{
    width = w; height = h;
    glViewport(0, 0, w, h);
}

void onKeyDown(SDLKey key, Uint16 /*mod*/)
{
    switch(key) {
        case SDLK_ESCAPE : quit(); break;
        case SDLK_SPACE : position = position0; speed = speed0; break;
		case SDLK_c:cut(&stuff[0], {1, 0.5, 0.5, 0}); break; //cut
		case SDLK_w:wireframe = !wireframe; break;
		case SDLK_k:stuff[1].enabled = !stuff[1].enabled; break; //enable first slice
		case SDLK_l:stuff[2].enabled = !stuff[2].enabled; break; // enable second slice

        default : break;//nothing-doing default to shut up warning
    }



}

void onKeyUp(SDLKey /*key*/, Uint16 /*mod*/)
{
}

void onMouseMove(unsigned /*x*/, unsigned /*y*/, int xrel, int yrel, Uint8 buttons)
{
    if(buttons & SDL_BUTTON_LMASK)
    {
        rx += xrel;
        ry += yrel;
        ry = glm::max(glm::min(ry, 89.0f), -89.0f);
        redraw();
    }
    if(buttons & SDL_BUTTON_RMASK)
    {
        pz += yrel;
        redraw();
    }
}

void onMouseDown(Uint8 button, unsigned /*x*/, unsigned /*y*/)
{

}

void onMouseUp(Uint8 button, unsigned /*x*/, unsigned /*y*/)
{

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int /*argc*/, char ** /*argv*/)
{
    try {
        // Init SDL - only video subsystem will be used
        if(SDL_Init(SDL_INIT_VIDEO) < 0) throw SDL_Exception();

        // Shutdown SDL when program ends
        atexit(SDL_Quit);

        init(800, 600, 24, 24, 0);

        mainLoop(40);//40ms == 25fps

    } catch(exception & ex) {
        cout << "ERROR : " << ex.what() << endl;
        cout << "Press any key to exit...\n";
        cin.get();

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
