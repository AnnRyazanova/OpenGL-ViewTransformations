#include <windows.h>
#include <glew.h>
#include <freeglut.h>

float angleX = 0.0f;

static int w = 0, h = 0;


// �-�� ���������� ����� ���������� � ������� ����
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1);
}


// �-�� ���������� ����
void solidCube(double size)
{
	glutSolidCube(size);
}

// 0 - ������� ����� ������ ������ �����
// 1 - ������� ����� ������ ������ ����������
// 2 - ������� ������� ������ ����� ��� 
int rotationType = 0;

// �-�� ��������� ���� ��������
void mouseChangeRotation(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		rotationType = (rotationType + 1) % 3;
}

// �-��, ���������� ������ ����
void update()
{
	angleX += 0.007;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// ������� ����� ������ ������ �����
	if (rotationType == 0)
	{
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);
	}

	// ������� ����� ������ ������ ����������
	if (rotationType == 1)
	{
		glTranslatef(0.5f, 0.0f, 0.0f);
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	}

	glPushMatrix();
	glColor3f(0.75f, 0.63f, 0.0f);
	// ������� : ������� ������ ����� ���
	if (rotationType == 2)
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	solidCube(0.3);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.25f, -0.05f, 0.0f);
	// ������� : ���������� ������ ����� ���
	if (rotationType == 2)
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glColor3f(0.75f, 0.75f, 0.75f);
	solidCube(0.2);
	glPopMatrix();
		
	glTranslatef(0.24f, -0.06f, 0.0f);
	// ������� : ��������� ������ ����� ���
	if (rotationType == 2)
		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glColor3f(0.62f, 0.39f, 0.16f);
	solidCube(0.18);

	glFlush();
	glutSwapBuffers();
}

// �-��, ���������� ��� ��������� ������� ����
void reshape(int width, int height)
{
	w = width;
	h = height;

	// �������� ��� ��������� - � ������ ������: �� ����
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
