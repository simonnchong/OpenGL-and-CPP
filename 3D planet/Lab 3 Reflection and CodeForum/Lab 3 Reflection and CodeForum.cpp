/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 /*
  *  planet.c
  *  This program shows how to composite modeling transformations
  *  to draw translated and rotated models.
  *  Interaction:  pressing the d and y keys (day and year)
  *  alters the rotation of the planet around the sun.
  */
#include <GL/glut.h>
#include <stdlib.h>

static int year = 0, day = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.4, 1.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //sun
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef((GLfloat)year, 0.0, 0.5, 0.2);
    glutSolidSphere(1.3, 5, 5);//(radius of sphere, line connected to circumference from origin, line connected with every radius line)    
    
    //earth
    //glRotatef((GLfloat)year, 0.7, 0.3, 0.3);
    glTranslatef(3.0, 0.0, 10.0);
    //glRotatef((GLfloat)day, 1.0, 0.3, 0.0);
    glColor3f(0.2, 0.2, 1.0);
    glutSolidSphere(0.4, 35, 15);
    glPopMatrix();

    //moon
    glPushMatrix();
    glColor3f(0.5, 1.0, 1.0);
    //glRotatef((GLfloat)year, 0.75, 0.5, 0.7); //revolution (combine with translation)
    glTranslatef(0.8, 0.0, 0.0); //distance between sun and moon
    glutSolidSphere(0.2, 20, 8);    /* draw smaller planet */
    glPopMatrix();
    
    //Meteorite    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    //glRotatef((GLfloat)year, 0.0, 0.0, 0.0); 
    glTranslatef(2.3, 2.3, 0.0); 
    glutSolidSphere(0.1, 5, 3);    

    glColor3f(1.0, 1.0, 1.0);
   // glRotatef((GLfloat)year, 0.0, 0.0, 0.0); 
    glTranslatef(2.3, 5.4, 0.0); 
    glutSolidSphere(0.05, 5, 3);    

    glColor3f(1.0, 1.0, 1.0);
    //glRotatef((GLfloat)year, 0.0, 0.0, 0.0); 
    glTranslatef(2.48, 4.4, 0.0); 
    glutSolidSphere(0.1, 5, 3);    

    glColor3f(1.0, 1.0, 1.0);
    //glRotatef((GLfloat)year, 0.0, 0.0, 0.0); 
    glTranslatef(3.2, 5.2, 0.0); 
    glutSolidSphere(0.03, 4, 2);    

    glColor3f(1.0, 1.0, 1.0);
    //glRotatef((GLfloat)year, 0.0, 0.0, 0.0); 
    glTranslatef(3.4, 3.5, 0.0); 
    glutSolidSphere(0.015, 5, 3);    
    glutSwapBuffers();    
    glPopMatrix();

}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'd':
        day = (day + 10) % 360;
        glutPostRedisplay();
        break;
    case 'D':
        day = (day - 10) % 360;
        glutPostRedisplay();
        break;
    case 'y':
        year = (year + 5) % 360;
        glutPostRedisplay();
        break;
    case 'Y':
        year = (year - 5) % 360;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
