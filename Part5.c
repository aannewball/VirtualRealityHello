#include <glut.h>
#include <stdio.h>
#include <math.h>


float moveSpeed = 0.01;

struct {
	GLfloat x,y,z; 
} Pos;

GLfloat W = 0.28, H=0.19, OriginZ=0.75;

float fieldOfView(float halfScreen, float cameraDistance)
{
	return (2*atan(halfScreen/(cameraDistance)))*(180/3.14157);
}

void view(int Eye)
{
  float left, right, bottom, top, scaling;
  
  float near = 0.1;
  scaling = near/(OriginZ+Pos.z);

  if (Eye==0) //Left
	  Pos.x= Pos.x - 0.03;
  else
	  Pos.x= Pos.x + 0.03;  


  left = -((W/2)+Pos.x)*scaling;   
  right = ((W/2)-Pos.x)*scaling;
  bottom = -(Pos.y)*scaling;
  top = ((H)-Pos.y)*scaling;


  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  glFrustum(left, right, bottom, top, near, 10); 

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  gluLookAt(Pos.x,Pos.y,Pos.z,  
	         Pos.x,Pos.y,-OriginZ, 
			 0,1,0);   
}

void init(void) 
{
  Pos.x=0;
  Pos.y=H/2;
  Pos.z=0;   
  
  glutFullScreen();  
  glEnable(GL_DEPTH_TEST);  
  glClearColor (0.0, 0.0, 0.0, 0.0);   
  glEnable(GL_DEPTH_TEST);

}

void display(void)
{  
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glColorMask(GL_TRUE,GL_FALSE,GL_FALSE,GL_TRUE); 
   view(0);



   glPushMatrix();
   glColor3f(1,1,1);
   glTranslatef(0,H/2,-0.825);
   glutWireCube(0.15);
   glPopMatrix();

   glClear (GL_DEPTH_BUFFER_BIT);
   glColorMask(GL_FALSE,GL_TRUE,GL_FALSE,GL_TRUE);
   view(1);



   glPushMatrix();
   glColor3f(1,1,1);
   glTranslatef(0,H/2,-0.825);
   glutWireCube(0.15);
   glPopMatrix();

   glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
   
   glutSwapBuffers();
}

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
   glutInitWindowSize (1600, 900); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
