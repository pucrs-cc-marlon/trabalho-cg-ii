#include <stdlib.h>
#include <GL/glut.h>

// Constante com a velocidade de movimento
const float velocity = 0.03f;
// Constante de tamanho do zoom
const double scale = 0.1;

float translacaoX, translacaoY;
double left, right, bottom, top;
float panX, panY;


// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(1.0f,1.0f,1.0f,0.0f);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha os eixos Cartesianos
	glBegin(GL_LINES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2i(-1,0);
        glVertex2i(1,0);
        glVertex2i(0,-1);
        glVertex2i(0,1);
    glEnd();


	gluOrtho2D(left+panX, right+panX, bottom+panY, top+panY);

    // Transla��o
    glTranslatef(translacaoX, translacaoY, 0.0f);

    // Tamanho da Linha
    glLineWidth(2);
    // Determina a espessura da linha que ser� desenhada
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.2f,0.1f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f,0.22f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.2f,0.1f);
    glEnd();

    // Desenha um quadrado com linhas pretas
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.2f,0.1f);
        glVertex2f(0.2f,0.1f);

        glVertex2f(0.2f,-0.2f);
        glVertex2f(-0.2f,-0.2f);
    glEnd();

	//Executa os comandos OpenGL
	glFlush();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
    switch (key){
        // Fecha a tela com a tecla ESC
        case 27:
            exit(0);
            break;
        // Movimenta a casa para cima
        case 'W':
        case 'w':
            translacaoY += velocity;
            break;
        // Movimenta a casa para baixo
        case 'S':
        case 's':
            translacaoY -= velocity;
            break;
        // Movimenta a casa para esquerda
        case 'A':
        case 'a':
            translacaoX -= velocity;
            break;
        // Movimenta a casa para direita
        case 'D':
        case 'd':
            translacaoX += velocity;
            break;
        // Diminiui o zoom
        case '-':
            if(left >= -2.2){
                left -= scale;
                right += scale;
                bottom -= scale;
                top += scale;
            }
            break;
        // Aumenta o zoom
        case '+':
            if(left <= -0.4){
                left += scale;
                right -= scale;
                bottom += scale;
                top -= scale;
            }
            break;
    }
	glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y)
{
    switch (key){
        // Diminiui o zoom
        case GLUT_KEY_HOME:
            if(left >= -2.2){
                left -= scale;
                right += scale;
                bottom -= scale;
                top += scale;
            }
            break;
        // Aumenta o zoom
        case GLUT_KEY_END:
            if(left <= -0.4){
                left += scale;
                right -= scale;
                bottom += scale;
                top -= scale;
            }
            break;
        // Movimenta a casa para cima
        case GLUT_KEY_UP:
            translacaoY += velocity;
            break;
        // Movimenta a casa para baixo
        case GLUT_KEY_DOWN:
            translacaoY -= velocity;
            break;
        // Movimenta a casa para esquerda
        case GLUT_KEY_LEFT:
            translacaoX -= velocity;
            break;
        // Movimenta a casa para direita
        case GLUT_KEY_RIGHT:
            translacaoX += velocity;
            break;
        // Pan para direita
        case GLUT_KEY_F9:
            panX -= scale;
            break;
        // Pan para esquerda
        case GLUT_KEY_F10:
            panX += scale;
            break;
        // Pan para baixo
        case GLUT_KEY_F11:
            panY += scale;
            break;
        // Pan para cima
        case GLUT_KEY_F12:
            panY -= scale;
            break;
    }
    glutPostRedisplay();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
    panX = panY = 0;

	translacaoX = 0.0f;
	translacaoY = 0.0f;

	left = -1.0;
    right = 1.0;
    bottom = -1.0;
    top = 1.0;

	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(left+panX, right+panX, bottom+panY, top+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Exerc�cio II CG - Marlon");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

	// Teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
