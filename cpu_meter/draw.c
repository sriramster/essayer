#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat height = 1.0;

void create_bar_box(GLfloat , GLfloat , GLfloat );

/* struct cpu_usage: structure having cpu_t, idle_t, sys_t and wait_t */
void renderFunction() {
     glClearColor(0.2, 0.2, 0.2, 0.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3f(1.0, 1.0, 1.0);
     glOrtho(-3.0 ,3.0 ,-3.0 ,3.0 ,-1.0 ,1.0);

     /* Working on projection matrix so gluPerpective */
     glMatrixMode(GL_PROJECTION);
     gluPerspective(100.0 ,10 ,2 ,-100);
     glLoadIdentity();
     glColor3f( 1.0 ,0.0 ,0.0);
     create_bar_box(0.0 ,-2.5 ,0.2 );
     
     glPushMatrix();
     glTranslatef(0.5f,0.0f,0.0f);
     glColor3f(1.0,1.0,0.0);
     create_bar_box(0.0 ,-2.5 ,0.2 );
     glPopMatrix();

     glPushMatrix();
     glTranslatef(-0.5f,0.0f,0.0f);
     glColor3f(1.0,0.0,1.0);
     create_bar_box(0.0 ,-2.5 ,0.2 );
     glPopMatrix();

     glPushMatrix();
     glTranslatef(-1.0f,0.0f,0.0f);
     glColor3f(0.0,1.0,1.0);
     create_bar_box(0.0 ,-2.5 ,0.2 );
     glPopMatrix();

     glFlush();
     glutSwapBuffers();
}

void create_bar_box(GLfloat x, GLfloat y, GLfloat z) {
     /* y changes often, representation of cpu meter on y-axis,
      * x-axis is just a common width for the towers[factors affecting
      * cpu] , quantize the y value to a height inside the viewing
      * frame  */

     GLfloat w = 1.0;

     glBegin(GL_POLYGON);
     /* Draw the rectangle quantized to represent the cpu utilization
      * on the y-axis, 4 vertices */
     glVertex3f(x, y, z);
     glVertex3f(x, y + height, z);
     glVertex3f(x + w, y + height ,  z);
     glVertex3f(x + w, y,  z);

     glEnd();
}

float calculate_height() {
     height = height + 0.00001;
     if(height >= 5.0)
	  height = 1.0;
     return height;
}

void idleFunc(void) {
     height = calculate_height();
     glutPostRedisplay();
}

void visible(int vis)
{
     if (vis == GLUT_VISIBLE)
	  glutIdleFunc(idleFunc);
     else
	  glutIdleFunc(NULL);
}

int draw(innt argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(75,75);
     glutInitWindowPosition(100,100);
     glutCreateWindow("cpu_meter");
     glutDisplayFunc(renderFunction);
     glutVisibilityFunc(visible);
     
     glutMainLoop();

     return 0;
}

