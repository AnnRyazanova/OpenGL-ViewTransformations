#include <windows.h>
#include <glew.h>
#include <freeglut.h>
#include <cmath>

float angleX = 0.0f;

static int w = 0, h = 0;

// Ќачальна€ позици€ камеры:
double cameraX = 0.0, cameraY = 0.0, cameraZ = 2.0;
// –ассто€ние от камеры до центра сцены:
double distCamera = 2.0;

double cameraAngle = 0;


// ‘-и€ вызываема€ перед вхождением в главный цикл
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1);
}

// ‘-и€ построени€ куба
void solidCube(double size)
{
	glutSolidCube(size);
}

// 0 - поворот всего вокруг центра сцены
// 1 - поворот всего вокруг центра пьедестала
// 2 - поворот каждого вокруг своей оси 
int rotationType = 0;

// ‘-и€ изменени€ типа поворота
void mouseChangeRotation(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		rotationType = (rotationType + 1) % 3;
}

// точечный источник света
// убывание интенсивности с рассто€нием
// задано функцией f(d) = 1.0 / (0.4 * d * d + 0.2 * d)
void addPointLight(int light, GLfloat lightPos [], GLfloat lightDiffuse [])
{
	glLightfv(light, GL_DIFFUSE, lightDiffuse);
	glLightfv(light, GL_POSITION, lightPos);
	glLightf(light, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(light, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(light, GL_QUADRATIC_ATTENUATION, 0.4);
}

// прожектор
void addSpotlight(int light, GLfloat lightPos[], GLfloat lightDiffuse[], GLfloat lightDirection[])
{
	glLightfv(light, GL_DIFFUSE, lightDiffuse);
	glLightfv(light, GL_POSITION, lightPos);
	glLightf(light, GL_SPOT_CUTOFF, 30);
	glLightfv(light, GL_SPOT_DIRECTION, lightDirection);
	glLightf(light, GL_SPOT_EXPONENT, 15.0);
}

// ”правление камерой
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP: cameraY += 0.5;
		break;
	case GLUT_KEY_DOWN:	cameraY -= 0.5;
		break;
	case GLUT_KEY_LEFT:
		cameraAngle += 0.5;
		cameraX = distCamera * cos(cameraAngle);
		cameraZ = distCamera * sin(cameraAngle);
		break;
	case GLUT_KEY_RIGHT:
		cameraAngle -= 0.5;
		cameraX = -distCamera * cos(cameraAngle);
		cameraZ = -distCamera * sin(cameraAngle);
		break;
	}
	glutPostRedisplay();
}

// ‘-и€, вызываема€ каждый кадр
void update()
{
	angleX += 0.007;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// белый точечный источник света
	GLfloat light0Position[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light0Diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	addPointLight(GL_LIGHT0, light0Position, light0Diffuse);

	// зеленый точечный источник света
	GLfloat light1Position[] = { -1.0, 1.0, 0.0, 1.0 };
	GLfloat light1Diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	addPointLight(GL_LIGHT1, light1Position, light1Diffuse);

	// красный прожектор
	GLfloat light2Diffuse[] = { 1.0, 0.0, 0.0 };
	GLfloat light2Position[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light2Direction[] = { -1.0, 0.0, 0.0 };
	addSpotlight(GL_LIGHT2, light2Position, light2Diffuse, light2Direction);

	
	// поворот всего вокруг центра сцены
	if (rotationType == 0)
	{
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);
	}

	// поворот всего вокруг центра пьедестала
	if (rotationType == 1)
	{
		//glTranslatef(0.5f, 0.0f, 0.0f);
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	}

	glPushMatrix();
	glColor3f(0.75f, 0.63f, 0.0f);
	// поворот : золотой вокруг своей оси
	if (rotationType == 2)
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	solidCube(0.3);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.25f, -0.05f, 0.0f);
	// поворот : серебр€ный вокруг своей оси
	if (rotationType == 2)
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glColor3f(0.75f, 0.75f, 0.75f);
	solidCube(0.2);
	glPopMatrix();
		
	glTranslatef(0.24f, -0.06f, 0.0f);
	// поворот : бронзовый вокруг своей оси
	if (rotationType == 2)
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glColor3f(0.62f, 0.39f, 0.16f);
	solidCube(0.18);

	glFlush();
	glutSwapBuffers();
}

// ‘-и€, вызываема€ при изменении размера окна
void reshape(int width, int height)
{
	w = width;
	h = height;

	// ообласть дл€ отрисовки - в данном случае: всЄ окно
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluPerspective(65.0f, w / h, 0.01f, 10.0f);
	glMatrixMode(GL_MODELVIEW); 

}


int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("ViewTransformations");
	glutDisplayFunc(update);
	glutIdleFunc(update);

	glutReshapeFunc(reshape);
	glutMouseFunc(mouseChangeRotation);
	glutSpecialFunc(specialKeys);

	init();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); // точечный источник света
	glEnable(GL_LIGHT1); // точечный источник света
	glEnable(GL_LIGHT2); // прожектор
	glEnable(GL_COLOR_MATERIAL);


	glutMainLoop();
	return 0;
}
