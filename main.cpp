#include <stdio.h>
#include <stdint.h>
#include <linux/version.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <iostream>

float touch_x =0.0;
float touch_y =0.0;
float max_x = 4475.0;
float max_y = 3606.0;
float min_x =1264;
float min_y =1075;
int fd; // File descriptor for trackpad
int first[2] = {0,0};
int second[2] = {0,0};

float valToPercent(float,float,float);
static void getTouchpadData(int);

void init(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	// int x = ( (1920 * valToPercent(touch_x,min_x,max_x)) ) 
	// int y =( 1080 - (1080  * valToPercent(touch_y,min_y,max_y) ))




	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
	}
}

void passiveTrack(int x,int y){
	getTouchpadData(fd);
	/*
	if(!first)
		first = true;
*/
	glutPostRedisplay();
}

void idle(){
	/*
	if (first){
		lift=true;
		first=false;
	}*/
}



static void getTouchpadData (int fd)
{
	// used to know when we've made it to the second event (aka already read the first)
	bool one_done = false;
	// things from evtest
	struct input_event ev[64];
	int i, rd;
	fd_set rdfs;
	FD_ZERO(&rdfs);
	FD_SET(fd, &rdfs);
	select(fd + 1, &rdfs, NULL, NULL, NULL);
	rd = read(fd, ev, sizeof(ev));
	
	for (i = 0; i < rd / sizeof(struct input_event); i++) {
		unsigned int type, code;
		type = ev[i].type;
		code = ev[i].code;
		// if the type is either abs_x, or abs_y
		if( code == 0 || code == 1)
			if( ev[i].value != 0 ){
				// make sure we don't get nonsense
				// might be useful later for when hand is lifted off pad
				if( !one_done){
					touch_x = float(ev[i].value);
					one_done = true;
				}
				else
					touch_y = float(ev[i].value);
			}

	}
	// give the device back to the system
	ioctl(fd, EVIOCGRAB, (void*)0);
}

float valToPercent(float value,float min, float max){
	return ( ( value - min ) / max );
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 0");
	glutSetCursor(GLUT_CURSOR_NONE); 
	


	// this is where we'll make the file descriptor to pass into the
	// print events function
	const char *device = "/dev/input/event1";
	fd = open(device, O_RDONLY);
	
	init();
	glutPassiveMotionFunc(passiveTrack);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}


