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
    glOrtho(minX - 1.0, maxX + 1.0, minY - 1.0, maxY + 1.0, -1.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, rails.data());
    glDrawArrays(GL_LINES, 0, rails.size());



    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

void OpenGL::timer(int ms)
{
    world.update(0.000001f*ms);
    glutPostRedisplay();
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

    for(auto it = world.railsBegin(); it != world.railsEnd(); ++it)
    {
        float x1 = (*it)->point[0].x;
        float y1 = (*it)->point[0].y;
        float x2 = (*it)->point[1].x;
        float y2 = (*it)->point[1].y;
        minX = std::min(minX, std::min(x1, x2));
        maxX = std::max(maxX, std::max(x1, x2));
        minY = std::min(minY, std::min(y1, y2));
        maxY = std::max(maxY, std::max(y1, y2));
        rails.push_back(x1);
        rails.push_back(y1);
        rails.push_back(x2);
        rails.push_back(y2);
    }

/*
    glEnable (GL_LINE_SMOOTH);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
*/



    // Define GLUT callbacks
    glutIdleFunc(OpenGL::reshape_static);
    glutDisplayFunc(OpenGL::display_static);
}

void OpenGL::timer_static(int ms)
{
    glutTimerFunc(ms, OpenGL::timer_static, ms);
    openGL->timer(ms);
}

void OpenGL::run(unsigned int fps)
{
    glutTimerFunc(33, OpenGL::timer_static, 33);
    glutMainLoop();
}
