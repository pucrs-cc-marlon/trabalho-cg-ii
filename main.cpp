#include <stdlib.h>
#include <GL/glut.h>

// Constante com a velocidade de movimento
const float velocity = 0.03f;
// Constante de tamanho do zoom
const double scale = 0.1;

float translacaoX, translacaoY;
double left, right, bottom, top;
float panX, panY;


// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor branca
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

    // Translação
    glTranslatef(translacaoX, translacaoY, 0.0f);

    // Tamanho da Linha
    glLineWidth(2);
    // Determina a espessura da linha que será desenhada
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

// Função callback chamada para gerenciar eventos de teclas
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

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
    panX = panY = 0;

	translacaoX = 0.0f;
	translacaoY = 0.0f;

	left = -1.0;
    right = 1.0;
    bottom = -1.0;
    top = 1.0;

	// Define a janela de visualização 2D
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

// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exercício II CG - Marlon");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

	// Teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
