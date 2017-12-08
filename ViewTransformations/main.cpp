#include <windows.h>
#include <glew.h>
#include <freeglut.h>

float angleX = 0.0f;

static int w = 0, h = 0;


// Ф-ия вызываемая перед вхождением в главный цикл
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1);
}


// Ф-ия построения куба
void solidCube(double size)
{
	glutSolidCube(size);
}

// 0 - поворот всего вокруг центра сцены
// 1 - поворот всего вокруг центра пьедестала
// 2 - поворот каждого вокруг своей оси 
int rotationType = 0;

// Ф-ия изменения типа поворота
void mouseChangeRotation(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		rotationType = (rotationType + 1) % 3;
}

// Ф-ия, вызываемая каждый кадр
void update()
{
	angleX += 0.007;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// поворот всего вокруг центра сцены
	if (rotationType == 0)
	{
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);
	}

	// поворот всего вокруг центра пьедестала
	if (rotationType == 1)
	{
		glTranslatef(0.5f, 0.0f, 0.0f);
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
	// поворот : серебряный вокруг своей оси
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

// Ф-ия, вызываемая при изменении размера окна
void reshape(int width, int height)
{
	w = width;
	h = height;

	// ообласть для отрисовки - в данном случае: всё окно
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
	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}
