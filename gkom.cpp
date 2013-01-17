/*
 * GKOM Lab. 3: OpenGL
 *
 * Program stanowi zaadaptowana wersje przykladu accnot.c.
 */
//Karol jest mistrzem Javy
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"

void init()
{
    GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );
    
    glShadeModel( GL_SMOOTH );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );
	glEnable( GL_NORMALIZE );


}

void displayObjects(int frame_no)
{
    GLfloat torus_diffuse[]  = { 0.7, 0.7, 0.0, 1.0 };
    GLfloat cube_diffuse[]   = { 0.0, 0.7, 0.7, 1.0 };
    GLfloat sphere_diffuse[] = { 0.7, 0.0, 0.7, 1.0 };
    GLfloat octa_diffuse[]   = { 0.7, 0.4, 0.4, 1.0 };

    glPushMatrix();

		

		glRotatef( 30.0, 1.0, 0.0, 0.0 );

	     glPushMatrix();
			glRotatef( (float)frame_no, 0,1.0,0);
			glPushMatrix();
				glTranslatef( -0.80, 0.35, 0.0 ); 
				glRotatef( (float)frame_no, 1.0, 0.0, 0.0 );
				glMaterialfv( GL_FRONT, GL_DIFFUSE, torus_diffuse );
				glScalef(0.5,0.5,0.5);
				glutSolidTorus( 0.275, 0.85, 10, 10 );
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef( 0.75, 0.60, 0.0 ); 
				glRotatef( 30.0, 1.0, 0.0, 0.0 );
				glMaterialfv( GL_FRONT, GL_DIFFUSE, sphere_diffuse );
				glScalef(0.5,0.5,0.5);
				glutSolidSphere( 1.0, 10, 10 );
			glPopMatrix();

         
		 glPopMatrix();

		 glPushMatrix();
			glRotatef(-(float)frame_no,0,1.0,0);
			glPushMatrix();
				glTranslatef( -0.75, -0.50, 0.0 ); 
				glRotatef( 45.0, 0.0, 0.0, 1.0 );
				glRotatef( 45.0, 1.0, 0.0, 0.0 );
				glMaterialfv( GL_FRONT, GL_DIFFUSE, cube_diffuse );
				glScalef(0.5,0.5,0.5);
				glutSolidCube( 1.5 );
			glPopMatrix();

			glPushMatrix();
				glTranslatef( 0.70, -0.90, 0.25 ); 
				glMaterialfv( GL_FRONT, GL_DIFFUSE, octa_diffuse );
				glScalef(0.5,0.5,0.5);
				glutSolidTeapot( 1.0 );
			glPopMatrix();
		 glPopMatrix();

   glPopMatrix();	 
}

void display()
{
    static int frame_no = 0;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if(frame_no<360) frame_no++; else frame_no=0;
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glRotatef((float)frame_no*2.0,0,1,0);
	glMatrixMode( GL_MODELVIEW );
    displayObjects(frame_no);
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
    glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	if( h > 0 && w > 0 ) {
		glViewport( 0, 0, w, h );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		if( w <= h ) {
			//glOrtho( -2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0 );
			glFrustum( -2.25*w/h, 2.25*w/h, -2.25, 2.25, 1, 10.0 );
		}
		else {
			//glOrtho( -2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0 );
			glFrustum( -2.25*w/h, 2.25*w/h, -2.25, 2.25, 1, 10.0 );
		}
		glTranslatef(0,0,-2.5);
		glMatrixMode( GL_MODELVIEW );
		
	}
}

int main(int argc, char** argv)
{
   glutInit( &argc, argv );

   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

   glutInitWindowPosition( 50, 50 );
   glutInitWindowSize( 500, 500 );

   glutCreateWindow( "GPOB: OpenGL" );

   glutDisplayFunc( display );
   glutReshapeFunc( reshape );
   glutIdleFunc( display );

   init();

   glutMainLoop();

   return 0;
}

