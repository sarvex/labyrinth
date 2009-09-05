#include <iostream>
using namespace std;

#include "GL/glut.h"
#include "ImathVec.h"
using namespace Imath;

#include "Maze.h"
#include "MazeView.h"
#include "Camera.h"

int main(int argc, char *argv[]);
void init();
void reshape(GLint w, GLint h);
void mouse(GLint button, GLint action, GLint x, GLint y);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void specialKeyDown(int key, int x, int y);
void specialKeyUp(int key, int x, int y);
void display();
void nextFrame();

Maze * maze;
MazeView * mazeView;
Camera * camera;

bool keyState[256] = {0};
bool specialKeyState[256] = {0};

int formWidth = 800, formHeight = 600;

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(formWidth, formHeight);
    glutCreateWindow("Labyrinth");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutIdleFunc(nextFrame);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);

    glutMainLoop();
    return 0;
}

void init() {
    // initialize opengl
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutIgnoreKeyRepeat(true);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    // initialize program
    // create maze object
    maze = new Maze(10, 10);
    mazeView = new MazeView(*maze, Vec3<float>(0, 0, 0),
        Vec3<float>(200,200,10));

    // create camera
    camera = new Camera(Vec3<float>(10, 10, 1),
        Vec3<float>(0,0,1),
        Vec3<float>(1,-1,0));

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Build Camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera->applyTransformations();

    // Transform and Render Objects
    mazeView->display();
    
    glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
    keyState[key] = true;
    switch(key){
        case 'p':
            maze->print();
            break;
    }
}

void keyUp(unsigned char key, int x, int y) {
    keyState[key] = false;
}

void specialKeyDown(int key, int x, int y) {
    specialKeyState[key] = true;
}

void specialKeyUp(int key, int x, int y) {
    specialKeyState[key] = false;
}

void nextFrame() {
    if( keyState[','] ) {
        // move camera forward in the direction it is facing
        camera->moveForward(0.3);
    } else if( keyState['o'] ) {
        // move camera backward in the direction it is facing
        camera->moveBackward(0.3);
    }

    if( keyState['-'] ) {
        camera->moveDown(0.3);
    } else if( keyState['+'] ) {
        camera->moveUp(0.3);
    }

    if( keyState['a'] ) {
        // strafe camera left
        camera->moveLeft(0.3);
    } else if( keyState['e'] ) {
        // strafe camera right
        camera->moveRight(0.3);
    }

    if( specialKeyState[GLUT_KEY_LEFT] ) {
        // rotate camera to the left
        camera->pointLeft(0.03);
    } else if( specialKeyState[GLUT_KEY_RIGHT] ) {
        // rotate camera to the right
        camera->pointRight(0.03);
    }

    if( specialKeyState[GLUT_KEY_UP] ) {
        // rotate camera up
        camera->pointUp(0.03);
    } else if( specialKeyState[GLUT_KEY_DOWN] ) {
        // rotate camera down
        camera->pointDown(0.03);
    }
    
    glutPostRedisplay();
}

void reshape(GLint w, GLint h) {
    formWidth = w;
    formHeight = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    // build projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, (float)formWidth / (float)formHeight, 1, 1000);
}

void mouse(GLint button, GLint action, GLint x, GLint y) {
    switch(button){
        case GLUT_LEFT_BUTTON:
            if( action == GLUT_DOWN )
                cout << "left down" << endl;
            else
                cout << "left up" << endl;
            break;
        case GLUT_RIGHT_BUTTON:
            if( action == GLUT_DOWN )
                cout << "right down" << endl;
            else
                cout << "right up" << endl;
            break;
        case GLUT_MIDDLE_BUTTON:
            if( action == GLUT_DOWN )
                cout << "middle down" << endl;
            else
                cout << "middle up" << endl;
            break;
    }
}

