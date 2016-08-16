#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/glext.h>

class OpenGLRender
{
    World * world;
    public:
    OpenGLRender(World & world, int argc, char * argv[]);
    virtual void run();
};

void NIAppIdle(void)
{
    glutPostRedisplay();
}

void NIAppDisplay(void)
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float geometry[] =
    {
        -0.5f,  0.5f, 0.0f, 1.0f,
         0.5f, -5.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 1.0f
    };
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 0, geometry);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glutSwapBuffers();
}

OpenGLRender::OpenGLRender(World & world, int argc, char * argv[]): world(&world)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("HELLO WORLD");

    // Define GLUT callbacks
    glutIdleFunc(NIAppIdle);
    glutDisplayFunc(NIAppDisplay);

}

void OpenGLRender::run()
{
    glutMainLoop();
}

