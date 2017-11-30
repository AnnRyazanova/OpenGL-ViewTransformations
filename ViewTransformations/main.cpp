#include <windows.h>
#include <glew.h>
#include <freeglut.h>

float angleX = 0.0f;

static int w = 0, h = 0;


// Ф-ия вызываемая перед вхождением в главный цикл
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


// Ф-ия построения куба
void solidCube(double size)
{
	glutSolidCube(size);
	//glutWireCube(size);
}


// Ф-ия, вызываемая каждый кадр
void update()
{
	angleX += 0.007;

	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);

	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glColor3f(0.75f, 0.63f, 0.0f);
	solidCube(0.3);
	
	glPushMatrix();
	glTranslatef(-0.25f, -0.05f, 0.0f);
	glColor3f(0.75f, 0.75f, 0.75f);
	solidCube(0.2);
	glPopMatrix();
		
	glTranslatef(0.24f, -0.06f, 0.0f);
	glColor3f(0.62f, 0.39f, 0.16f);
	solidCube(0.18);
	glPopMatrix();

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
	gluPerspective(65.0f, w / h, 0.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW); 

}


int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("ViewTransformations");

	glutDisplayFunc(update);
	glutIdleFunc(update);

	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}
