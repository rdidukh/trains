#include "OpenGL.h"

#include <GL/glew.h>
#include <GL/glut.h>

OpenGL* OpenGL::openGL = nullptr;

void OpenGL::reshape_static()
{
    glutPostRedisplay();
}

void OpenGL::display_static()
{
    openGL->display();
}

void OpenGL::display(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0f, 5.0f, -5.0, 5.0f, -1.0f, 1.0f);

    float geometry[] =
    {
         0.0f,  0.0f, //0.0f,
         0.0f,  1.0f, //0.0f,
         0.3f,  2.0f, //0.0f
         0.6f,  4.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, geometry);

    glDrawArrays(GL_LINE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

OpenGL::OpenGL(World &world): world(world)
{
    openGL = this;
    int argc = 0;
    char * argv[1];
    // Setup windwing
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Trains");

/*
    glEnable (GL_LINE_SMOOTH);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
*/

    // Define GLUT callbacks
    glutIdleFunc(OpenGL::reshape_static);
    glutDisplayFunc(OpenGL::display_static);
}

/* Once every millisec ms */
void OpenGL::timer_static(int millisec)
{
    std::cout << "Timer\n";
    glutTimerFunc(millisec, OpenGL::timer_static, millisec);
    glutPostRedisplay();
}

void OpenGL::run(unsigned int fps)
{
    glutTimerFunc(33, OpenGL::timer_static, 33);
    glutMainLoop();
}
