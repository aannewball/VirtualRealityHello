
//#include <conio.h>
#include <glut.h>
#include <math.h>
#include <stdio.h>
//#include <iostream>

//#include <MathsVM/Vector3d.h>


float moveSpeed = 0.01;

struct {
    GLfloat x, y, z;
} Pos;


GLfloat W=0.28, H=0.19, OriginZ=0.75;

float angle = 45;


void init(void) 
{
  Pos.x=0;
  Pos.y=H/2;
  Pos.z=0;   
  
  glutFullScreen();
  glClearColor (0.2, 0.2, 0.2, 0.0);  

  glEnable(GL_DEPTH_TEST);   
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

}

void idle() {
	angle += 0.5;
	glutPostRedisplay();
}//OnIdle

float fieldOfView(float halfScreen, float cameraDistance)
{
	return 2*atan(halfScreen/cameraDistance) * 180/3.14257; 
}

void view(int left_eye)
{
   
   if (left_eye==1) Pos.x -= 0.03;
   else Pos.x += 0.03;
    
   float mynear = 0.1;
   float left = -((W/2)+Pos.x)*(mynear/(OriginZ+Pos.z)); 
   float right = ((W/2)-Pos.x)*(mynear/(OriginZ+Pos.z));
   float bottom = -(Pos.y)*(mynear/(OriginZ+Pos.z));
   float top = (H-Pos.y)*(mynear/(OriginZ+Pos.z));


   glMatrixMode (GL_PROJECTION);

   glLoadIdentity ();
   
   glFrustum(left, right, bottom, top, mynear, 10);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt(Pos.x,Pos.y,Pos.z,
			 Pos.x,Pos.y,-OriginZ, 
			 0,1,0);  

   if (left_eye==1) Pos.x += 0.03;
   else Pos.x -= 0.03;
    

}

void display(void)
{  
   int left=1, right=0;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColorMask(GL_TRUE,GL_FALSE,GL_FALSE,GL_TRUE);
   view(left);
	glFrontFace(GL_CW);             // gizmo to correct teapot vertex order
   	glPushMatrix();
		glTranslatef(0.05,H/2,-(OriginZ + 0.09));
		glRotatef(angle,0,1,0);
		glutSolidTeapot(0.05f);         // white teapot at eye level behind the screen
	glPopMatrix();
   	glPushMatrix();
		glTranslatef(-0.05,H/2,-(OriginZ - 0.09));
		glRotatef(-angle,0,1,0);       
		glutSolidTeapot(0.05f);         // white teapot in front
	glPopMatrix();
	glFrontFace(GL_CCW);


   glClear(GL_DEPTH_BUFFER_BIT);
   glColorMask(GL_FALSE,GL_TRUE,GL_TRUE,GL_TRUE);
   view(right);
	glFrontFace(GL_CW);             // gizmo to correct teapot vertex order
	glPushMatrix();
		glTranslatef(0.05,H/2,-(OriginZ + 0.09));
		glRotatef(angle,0,1,0);
		glutSolidTeapot(0.05f);         // white teapot at eye level behind the screen
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.05,H/2,-(OriginZ - 0.09));
		glRotatef(-angle,0,1,0);       
		glutSolidTeapot(0.05f);         // white teapot in front 
	glPopMatrix();
	glFrontFace(GL_CCW);

   glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE); 
   glutSwapBuffers();
}

	/* ARGSUSED1 */
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {

      case 'a':
         Pos.x += moveSpeed;
		 glutPostRedisplay();
         break;
      case 'd':
         Pos.x -= moveSpeed;
         glutPostRedisplay();
         break;
      case 'w':
         Pos.z += moveSpeed;
         glutPostRedisplay();
         break;
      case 's':
         Pos.z -= moveSpeed;
         glutPostRedisplay();
         break;
      case 'z':
         Pos.y += moveSpeed;
         glutPostRedisplay();
         break;
      case 'x':
         Pos.y -= moveSpeed;
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
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
