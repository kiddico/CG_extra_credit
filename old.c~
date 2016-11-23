// Nicholas Chirico @ 10-11-16 -> Conputer Graphics - Shamal AL-Dohuki
/* !!!!!!!!!!!!!!!!!!!!! */

/*
   I've just finished this, and it works correctly, but it's...bad. 
   I originally had it so you could have multiple activities from the menu running at once.
   Turns out the expected output is one at a time. My bad.
   Also I completely ignored the idle function callback.
   For some reason it wouldn't actually do anything.
*/

#include <GL/glut.h>
#include <cstdio>
#include <math.h>


/////////////////////////////
// Global Declarations     //
/////////////////////////////

GLsizei wh = 500, ww = 500;
GLfloat size = 15.0;
GLfloat C1,C2,C3;

/* ------ Current Activities Tracker */
bool activities[3] = {false,false,false};
bool tracking = false;


/* ------ Rectangle Position ------- */
int RECT_X=-250;
int RECT_Y=-250;

/* ------ Idle Circle Position ----- */
int CIRC_X=-8;
int CIRC_Y=-8;

/* ------ Rubber Banded Circle ----- */
int RUBBER_X=0;
int RUBBER_Y=0;
int END_RUBBER_X=0;
int END_RUBBER_Y=0;

/* ------ Mathematics Constants ---- */
const float DEG2RAD = 3.14159/180;
const float PI = 3.14159;




// Function declarations
// I like to have main at the top
void mainMenu(int);
void myReshape(GLsizei,GLsizei);
void myinit();
void mouse(int btn, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void display();
void activeRect(int,int);
void passiveRect(int,int);
void idle();
void drawCircle(float x, float y, float radius);
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);


int main(int argc, char** argv){
	// GL Preperations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Assignment 1");
	myinit();
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(activeRect);
	glutPassiveMotionFunc(passiveRect);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	// Menu and default color
	glutCreateMenu(mainMenu);
		glutAddMenuEntry("RectangleWithMouse", 1);
		glutAddMenuEntry("AutoMovingCircle", 2);
		glutAddMenuEntry("RubberbandingCircle", 3);
		glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	C1=1.0,C2=1.0,C3=0.0; // Set default color for the square

	glutMainLoop(); // vroom vroom
}

void display(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	if(activities[0]==true){
		glColor3f(C1,C2,C3);
		glBegin(GL_POLYGON);
		glVertex2f(RECT_X + size, RECT_Y + size);
		glVertex2f(RECT_X - size, RECT_Y + size);
		glVertex2f(RECT_X - size, RECT_Y - size);
		glVertex2f(RECT_X + size, RECT_Y - size);
		glEnd();
	}
	if( activities[1]==true ){
		glColor3f(0.0,0.0,1.0);
		drawCircle(CIRC_X,CIRC_Y, 20);
	}

	if( activities[2] ){
		// 2d distance formula to find the outer radius
		GLfloat distance = sqrt( pow((END_RUBBER_X-RUBBER_X),2) + pow(( END_RUBBER_Y-RUBBER_Y),2) );
		if( tracking ){
			glColor3f(1.0,1.0,1.0);
			drawFilledCircle(RUBBER_X,RUBBER_Y,2);
			drawCircle(RUBBER_X,RUBBER_Y,distance);
		}
		if( !tracking ){
			glColor3f(0.0,1.0,0.0);
			drawFilledCircle(RUBBER_X,RUBBER_Y,distance);
		}
	}

	glutSwapBuffers();
}

////////////////////////////////////////////
// Used to draw the Rectangle on mouse
////////////////////////////////////////////
void passiveRect(int x, int y){
	if(activities[0]==true){
		RECT_X = x;
		RECT_Y = wh - y;
		C1=1.0,C2=1.0,C3=0.0;
	}
	glutPostRedisplay();
}

void activeRect(int x, int y){
	if(activities[0]==true){
		RECT_X = x;
		RECT_Y = wh - y;
		C1=1.0,C2=0.0,C3=0.0;
	}
	if(activities[2] == true){
		if (! tracking ){
			RUBBER_X = x;
			RUBBER_Y = wh -y;
			tracking = true;
		}
		else{
			END_RUBBER_X = x;
			END_RUBBER_Y = wh - y;
		}
	}

	glutPostRedisplay();
}

///////////////////////////////////////////////////////
// IDLE                                              //
// Well, my idle never seems to do anything          //
// I think it's always got something to do elsewhere //
///////////////////////////////////////////////////////
void idle(){};

////////////////////////////////////////////
// Different Circle drawing algorithms
//

//// This is the one you gave us in the instructions
void drawCircle(float x, float y, float radius)
{
	CIRC_X = CIRC_X + 1;
	CIRC_Y = CIRC_Y + 1;
	if( CIRC_X > ww+15 || CIRC_Y > wh+15 ){
		CIRC_X =0;
		CIRC_Y =0;
	}
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i < 360; i++)
	{
		float degInRad = i*DEG2RAD;
		glVertex2f(x+cos(degInRad)*radius,y+sin(degInRad)*radius);
	}
	glEnd();
	glutPostRedisplay();
}

//// This is one that I found online. Uses a bunch of triangles
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	CIRC_X = CIRC_X + 1;
	CIRC_Y = CIRC_Y + 1;

	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for(i = 0; i <= triangleAmount;i++) { 
		glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
	glutPostRedisplay();
}

////////////////////////////////////////////
// Init Func
////////////////////////////////////////////
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);

	/* set clear color to black and clear window */

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

////////////////////////////////////////////
// KEYBOARD
// Used to exit on ESC KB event.
////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y){
	switch (key){
		case 27: // Escape key
		//glutDestroyWindow (  );
		exit (0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

////////////////////////////////////////////
// MOUSE
// Listens for and responds to mouse events
////////////////////////////////////////////
void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(activities[0] == true){
			C1=1.0,C2=0.0,C3=0.0;
			RECT_X = x;
			RECT_Y = wh - y;	
		}
	}

	// fixes the color of the rect if it doesn't move, and the mouse is released
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP && activities[0] ){
			C1=1.0,C2=1.0,C3=0.0;
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP && activities[2] ){
			tracking=false;
	}

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && activities[2] ){
		if(activities[2] == true){
			RUBBER_X = x;
			RUBBER_Y = wh -y;
			tracking = true;
		}
	}

	glutPostRedisplay();
}


////////////////////////////////////////////
// Handler Function for the menu
////////////////////////////////////////////
void mainMenu(int id){

	// I had it set up before so each one was a toggle,
	// the expected ouput only does one at a time though.
	switch(id){
		// Rectangle Following Mouse
		case 1:
			activities[0] = true;
			activities[1] = false;
			activities[2] = false;
			break;

		// Idle Circle Movement
		case 2:
			activities[1] = true;
			activities[0] = false;
			activities[2] = false;
			break;

		// Rubber Band Circle Creation
		case 3:
			activities[2] = true;
			activities[0] = false;
			activities[1] = false;
			break;

		// Exit from menu
		case 4:
			exit(0);
			break;

		default:
			break;
	}
	// Old way of swapping the activities around
	/*
	switch(id){
		// Rectangle Following Mouse
		case 1:
			activities[0] = !activities[0];
			break;

		// Idle Circle Movement
		case 2:
			activities[1] = !activities[1];
			break;

		// Rubber Band Circle Creation
		case 3:
			activities[2] = !activities[2];
			break;

		// Exit from menu
		case 4:
			exit(0);
			break;

		default:
			break;
	}
	*/
}

////////////////////////////////////////////
// Reshaping Handler
////////////////////////////////////////////
void myReshape(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers(); // Swapped from glflush, to work with double buffers
	ww = w;
	wh = h;
}
