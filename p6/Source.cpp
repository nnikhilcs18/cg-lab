#include<stdio.h>
#include<gl/glut.h>

float x1 = 200, y1 = 300, x2 = 100, y2 = 200, x3 = 200, y3 = 100, x4 = 300, y4 = 200;

void edgedetect(float x1, float y1, float x2, float y2, int* le, int* re)
{
	float mx, x, temp;
	int i;
	if ((y2 - y1) < 0)
	{
		temp = x1; x1 = x2; x2 = temp;
		temp = y1; y1 = y2; y2 = temp;
	}

	if ((y2 - y1) != 0)
		mx = (y2 - y1) / (x2 - x1);
	else mx = x2 - x1;

	x = x1;

	for (i = y1; i < y2; i++)
	{
		if (x < le[i])
			le[i] = x;
		if (x > re[i])
			re[i] = x;
		x += mx;
	}

}

void draw_pixel(int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	int le[500], re[500];
	int i, y;
	for (i = 0; i < 500; i++)
	{
		le[i] = 500;
		re[i] = 0;
	}

	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x1, y1, le, re);

	for (y = 0; y < 500; y++)
	{
		if (le[y] <= re[y])
			for (i = le[y]; i < re[y]; i++)
				draw_pixel(i, y);
	}
}

void display_filled_polygon()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();

	scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
	glFlush();
}


void myinit()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 1);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("original");
	glutDisplayFunc(display);
	myinit();

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("filled");
	glutDisplayFunc(display_filled_polygon);
	myinit();

	glutMainLoop();
}