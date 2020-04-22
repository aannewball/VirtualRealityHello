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

void view()
{

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  gluPerspective(60, W / H, 1.0, 10.0); 

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0,H/2,0,  
	         0,H/2,-2, 
			 0,1,0);   
}

void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);  
  glutFullScreen();  
  glEnable(GL_DEPTH_TEST);  
  
  view();

}

void display(void)
{  
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   glPushMatrix();
   glColor3f(1,1,1);
   glTranslatef(Pos.x,H/2,-2);
   glutWireCube(1.0);
   glPopMatrix();
   
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
