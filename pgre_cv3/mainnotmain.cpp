//#include "pgr.h"
//
//#include "sphere.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//using namespace std;
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//// Data
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//const float ground[][3] = {
//    { -10, 0, 10 }, { 10, 0, 10 }, { 10, 0, -10 }, { -10, 0, -10 } };
//
//GLuint sphereVBO, sphereEBO;
//GLuint groundVBO;
//
//const glm::vec3 position0(0, 10, 0), speed0(0.1, 0, 0);
//
//glm::vec3 position = position0, speed = speed0;
//
//int width, height;
//float rx = 90.0f, ry = 30.0f, pz = 50.0f;
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//// Shaders
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//GLuint VS, FS, Prog;
//GLuint FS2, Prog2;
//
//GLuint positionAttrib, mvpUniform, colorUniform;
//GLuint positionAttrib2, mvpUniform2, animationUniform;
//
//float planetDistance = 2.0f;
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//// Event handlers
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//void onInit()
//{
//    // Shaders
//    VS = compileShader(GL_VERTEX_SHADER, loadFile("data\\sphere.vs").c_str());
//    FS = compileShader(GL_FRAGMENT_SHADER, loadFile("data\\sphere1.fs").c_str());
//	FS2 = compileShader(GL_FRAGMENT_SHADER, loadFile("data\\sphere2.fs").c_str());
//
//    Prog = linkShader(2, VS, FS);
//	Prog2 = linkShader(2, VS, FS2);
//
//    //Acquire attribute and uniform locations
//    positionAttrib = glGetAttribLocation(Prog, "position");
//    mvpUniform = glGetUniformLocation(Prog, "mvp");
//    colorUniform = glGetUniformLocation(Prog, "color");
//	
//    positionAttrib2 = glGetAttribLocation(Prog2, "position");
//    mvpUniform2 = glGetUniformLocation(Prog2, "mvp");
//	animationUniform = glGetUniformLocation(Prog2, "animationTime");
//
//    //Generate VBOs
//    glGenBuffers(1, &sphereVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(sphereVertices), sphereVertices, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &sphereEBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &groundVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STATIC_DRAW);
//
//}
//
//void onWindowRedraw()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glEnable(GL_DEPTH_TEST);
//
//    // t - absolute time, dt - time step
//    static float t0 = SDL_GetTicks()/1000.0f;
//    static float t = t0;
//    float t1 = SDL_GetTicks()/1000.0f;
//    float dt = t1-t;
//    t = t1;
//
//    // Simulation step
//    position += speed*dt;
//    speed += glm::vec3(0.0f, -dt*9.81, 0.0f);//g*dt
//	const float sphere_radius = 1.0f;
//    // Collision detection
//    if(position.y < sphere_radius)
//    {
//        // Bounce
//        speed = glm::vec3(speed.x, -speed.y, speed.z)*0.9f;
//        position.y = (sphere_radius-position.y) + sphere_radius;
//    }
//
//    //Setup orbital camera
//    float radx = glm::radians(rx);
//    float rady = glm::radians(ry);
//
//    float x = pz * cos(rady) * cos(radx);
//    float y = pz * sin(rady);
//    float z = pz * cos(rady) * sin(radx);
//
//    glm::vec4 camPos = glm::vec4(x, y, z, 1);
//    glm::mat4 view = glm::lookAt(glm::vec3(camPos), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
//    glm::mat4 persp = glm::perspective(45.0f, (float)width / (float)height, 1.0f, 1000.0f);
//
//    // Draw the bouncing sphere (the planet)
//    glUseProgram(Prog2);
//
//    glEnableVertexAttribArray(positionAttrib2);
//
//    glm::mat4 sphere1model = glm::translate(position);
//    glm::mat4 mvp1 = persp * view * sphere1model;
//    glUniformMatrix4fv(mvpUniform2, 1, GL_FALSE, glm::value_ptr(mvp1));
//	
//	//TODO 1
//	//update animation time in shader
//    //Uniform handle is stored in "animationUniform" variable
//	//update it with "t" variable (see line 92)
//    //use glUniform1f function
//    //check documentation for syntax: https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml
//	glUniform1f(animationUniform, t);
//	//
//    
//    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
//    glVertexAttribPointer(positionAttrib2, 3, GL_FLOAT, GL_FALSE, sizeof(SphereVertex), (void*)offsetof(SphereVertex, position));
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
//    glDrawElements(GL_TRIANGLES, sizeof(sphere)/sizeof(*sphere)*3, sphereIndexType, NULL);
//
//    // Draw second sphere rotating around (the moon)
//	glUseProgram(Prog);
//
//    glEnableVertexAttribArray(positionAttrib);
//	
//	//TODO 2 
//    // Make the red sphere rotate around the bouncing blue sphere (create a model matrix)
//	// 1 turn should be done in 1 seconds - use variable "t" which is time in seconds
//	// the red sphere should rotate around the other one (use mvp)
//	// the red sphere should be half sized than the other sphere
//	// the red sphere should rotate around the other with radius stored in "planetDistance" variable
//	// Use glm::rotate, glm::translate, glm::scale
//    // Store the resulting transform in "sphere2model" variable
//    // Hint - there are 2 possibilities how to do it, either by 2x translate or translate + rotate
//    // Hint 2 - sphere1model should be the last applied transform
//    glm::mat4 sphere2model = glm::mat4(1); //store it here
//	//
//	glm::mat4 scaleM = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
//	glm::mat4 translationM = glm::translate(glm::vec3(planetDistance, 0.0f, 0.0f));
//	glm::mat4 rotationM = glm::rotate(glm::radians(360.0f) * t, glm::vec3(0.0f, 1.0f, 0.0f));
//	sphere2model = sphere1model * rotationM * translationM * scaleM; //we scale it, offset it from the origin, rotate it, and then place it near the first planet as it should be
//	//
//	glm::mat4 mvp2 = persp * view * sphere2model;
//
//	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp2));
//    glUniform3f(colorUniform, 1, 0, 0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
//    glVertexAttribPointer(positionAttrib2, 3, GL_FLOAT, GL_FALSE, sizeof(SphereVertex), (void*)offsetof(SphereVertex, position));
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
//    glDrawElements(GL_TRIANGLES, sizeof(sphere)/sizeof(*sphere)*3, sphereIndexType, NULL);
//
//    // Draw floor
//    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(persp * view));
//    glUniform3f(colorUniform, 0, 1, 0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
//    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(ground)/sizeof(*ground));
//
//    SDL_GL_SwapBuffers();
//}
//
//void onWindowResized(int w, int h)
//{
//    width = w; height = h;
//    glViewport(0, 0, w, h);
//}
//
//void onKeyDown(SDLKey key, Uint16 /*mod*/)
//{
//    switch(key) {
//        case SDLK_ESCAPE : quit(); break;
//        case SDLK_SPACE : position = position0; speed = speed0; break;
//        default : break;//nothing-doing defaut to shut up warning
//    }
//}
//
//void onKeyUp(SDLKey /*key*/, Uint16 /*mod*/)
//{
//}
//
//void onMouseMove(unsigned /*x*/, unsigned /*y*/, int xrel, int yrel, Uint8 buttons)
//{
//    if(buttons & SDL_BUTTON_LMASK)
//    {
//        rx += xrel;
//        ry += yrel;
//        ry = glm::max(glm::min(ry, 89.0f), -89.0f);
//        redraw();
//    }
//    if(buttons & SDL_BUTTON_RMASK)
//    {
//        pz += yrel;
//        redraw();
//    }
//}
//
//void onMouseDown(Uint8 button, unsigned /*x*/, unsigned /*y*/)
//{
//	//TODO 3 
//    //Change the code so that the mouse wheel moves the moon further away or closer to the planet
//    //React to SDL_BUTTON_WHEELDOWN and SDL_BUTTON_WHEELUP
//    //Like:
//	//if(button == SDL_BUTTON_WHEELDOWN) then do something, similarly for SDL_BUTTON_WHEELUP
//
//	//use the variable "planetDistance" to change the distance
//    //=> increase/decrease it's value by 0.25f, based on the message type
//
//	if (button == SDL_BUTTON_WHEELDOWN && planetDistance>0)
//		planetDistance -= 0.25f;
//
//}
//
//void onMouseUp(Uint8 button, unsigned /*x*/, unsigned /*y*/)
//{
//	if (button == SDL_BUTTON_WHEELUP)
//		planetDistance += 0.25f;
//}
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//// Main
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//int main(int /*argc*/, char ** /*argv*/)
//{
//    try {
//        // Init SDL - only video subsystem will be used
//        if(SDL_Init(SDL_INIT_VIDEO) < 0) throw SDL_Exception();
//
//        // Shutdown SDL when program ends
//        atexit(SDL_Quit);
//
//        init(800, 600, 24, 24, 0);
//
//        mainLoop(40);//40ms == 25fps
//
//    } catch(exception & ex) {
//        cout << "ERROR : " << ex.what() << endl;
//        cout << "Press any key to exit...\n";
//        cin.get();
//
//        return EXIT_FAILURE;
//    }
//
//    return EXIT_SUCCESS;
//}
