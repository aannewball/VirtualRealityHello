#include <glut.h>
#include <stdio.h>
#include <math.h>

#define LEFT_EYE 1
#define RIGHT_EYE 2


float moveSpeed = 0.01;

int EYE;

struct {
	GLfloat x,y,z; 
} Pos;

GLfloat W = 0.51, H=0.29, OriginZ=0.75;
GLfloat myNear = 10.0, myFar;
GLfloat frTopP, frLeftP, frRightP, frBottomP, scaleFactor;

//Parámetros gluLookAt:
GLfloat eyeX, eyeY;
GLfloat centerX, centerY;

  GLfloat eyeShift = 0.03;

//Parámetros glFrustum:
GLfloat frLeft,frRight,frBottom,frTop;


float fieldOfView(float halfScreen, float cameraDistance)
{
	return (2*atan(halfScreen/(cameraDistance)))*(180/3.14157);
}

void view(int pEye)
{

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
     
  if(pEye == LEFT_EYE)  
	  Pos.x -= eyeShift;  
  else  
	  Pos.x += eyeShift;
  

  //Cambio de gluPerspective por glFrustum:
  //gluPerspective(fieldOfView(H/2,OriginZ+Pos.z), W / H,OriginZ+Pos.z, 10.0); 

  frLeft = -(W/2+Pos.x);
  frRight = (W/2-Pos.x);
  frTop = H-Pos.y;
  frBottom = -(Pos.y);

  //glFrustum(frLeft,frRight,frBottom,frTop,OriginZ+Pos.z,10.0); //Works

  //Test:
  myFar = 10.0;  
  myNear = 0.2;
  scaleFactor = (myNear/(OriginZ+Pos.z));

  frTopP = frTop * scaleFactor;
  frRightP = frRight * scaleFactor;
  frLeftP = frLeft * scaleFactor;
  frBottomP = frBottom * scaleFactor;

  glFrustum(frLeftP,frRightP,frBottomP,frTopP,myNear,myFar);
  //

  glMatrixMode(GL_MODELVIEW);
  
  glLoadIdentity();

  gluLookAt(Pos.x,Pos.y,Pos.z,  
	  Pos.x,Pos.y,-(OriginZ), 
			 0,1,0);   

   if(pEye == LEFT_EYE)  
	  Pos.x += eyeShift;  
  else  
	  Pos.x -= eyeShift;
}

//void view()
//{
//
//  glMatrixMode (GL_PROJECTION);
//  glLoadIdentity ();
//
//  //Cambio de gluPerspective por glFrustum:
//  //gluPerspective(fieldOfView(H/2,OriginZ+Pos.z), W / H,OriginZ+Pos.z, 10.0); 
//
//  frLeft = -(W/2+Pos.x);
//  frRight = (W/2-Pos.x);
//  frTop = H-Pos.y;
//  frBottom = -(Pos.y);
//
//  //glFrustum(frLeft,frRight,frBottom,frTop,OriginZ+Pos.z,10.0); //Works
//
//  //Test:
//  myFar = 10.0;  
//  myNear = 0.2;
//  scaleFactor = (myNear/(OriginZ+Pos.z));
//
//  frTopP = frTop * scaleFactor;
//  frRightP = frRight * scaleFactor;
//  frLeftP = frLeft * scaleFactor;
//  frBottomP = frBottom * scaleFactor;
//
//  glFrustum(frLeftP,frRightP,frBottomP,frTopP,myNear,myFar);
//  //
//
//  glMatrixMode(GL_MODELVIEW);
//  
//  glLoadIdentity();
//
//  gluLookAt(Pos.x,Pos.y,Pos.z,  
//	  Pos.x,Pos.y,-(OriginZ), 
//			 0,1,0);   
//}

void init(void) 
{
  Pos.x=0;
  Pos.y=H/2;
  Pos.z=0; 
  
  
  glutFullScreen();  
  glEnable(GL_DEPTH_TEST);  
  glClearColor (0.1, 0.1, 0.1, 0.0);   
  glEnable(GL_DEPTH_TEST);

}

void display(void)
{  
 
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glColorMask(GL_TRUE,GL_FALSE,GL_FALSE,GL_TRUE);
   view(LEFT_EYE);

   //Dibujo Cubos:
   glPushMatrix();
   glColor3f(1,1,1);
   glTranslatef(0,H/2,-(OriginZ+0.1));
   glutWireCube(0.2);

   glTranslatef(0,0,0.15);
   glutWireCube(0.1);

   //   glTranslatef(0,0,0.15);
   //glutWireTeapot(0.05);

     
   glClear (GL_DEPTH_BUFFER_BIT);
   glColorMask(GL_FALSE,GL_TRUE,GL_TRUE,GL_FALSE);
   view(RIGHT_EYE);

   //Dibujo Cubos:
   glPushMatrix();
   glColor3f(1,1,1);

   glTranslatef(0,H/2,-(OriginZ+0.1));
   glutWireCube(0.2);

   glTranslatef(0,0,0.15);
   glutWireCube(0.1);

   //Tetera:
  // glTranslatef(0,0,0.15);
   //glutWireTeapot(0.05);

   glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

   glPopMatrix();
   
   glutSwapBuffers();
}

//void display(void)
//{  
// 
//   view();
//   
//   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//   glPushMatrix();
//   glColor3f(1,1,1);
//
//   glTranslatef(0,H/2,-(OriginZ+0.1));
//   glutWireCube(0.2);
//
//    glTranslatef(0,0,0.15);
//   glutWireCube(0.1);
//
//   //DrawCubes(0);
//
//   glPopMatrix();
//   
//   glutSwapBuffers();
//}

void DrawCubes(GLfloat dx)
{
   glTranslatef(0,H/2,-(OriginZ+0.1+dx));
   glutWireCube(0.2);

   glTranslatef(0,0,0.15+dx);
   glutWireCube(0.1);
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
