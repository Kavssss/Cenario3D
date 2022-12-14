#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define BLOCO 20
#define TAM_CENARIO 500
#define DIST_MOVIMENTO 5

GLfloat obs_x = BLOCO, obs_z = BLOCO, obs_y = BLOCO;
GLfloat deslocamento_x = DIST_MOVIMENTO, deslocamento_z = 0, deslocamento_y = DIST_MOVIMENTO;
GLfloat angle = 90, fAspect = 1, angulo_rotacao = 0;
GLfloat corCenario[] = {0.2, 0.7, 0.1, 1.0}; //cor usada no "ch?o" do cen?rio
GLfloat corMaterial[] = {0.0, 0.0, 0.0, 1.0}; //cor usada no material
int eixo_x = 0, eixo_y = 0, eixo_z = 0;

void mudaCor(float r, float g, float b);
void circulo(int centroX, int centroY, int raioH, int raioV);
void alvo();
void desenhaFaixa();
void desenhaChao();
void desenhaTeto();
void desenhaParede();
void desenhaDivisoria();
void desenhaMesa();

void configura_iluminacao() {

    //configura a cor branca como luz ambiente
    GLfloat luzAmbiente[4]={1.0, 1.0, 1.0, 1.0};
    //configura luz difusa
    GLfloat luzDifusa[4]={0.7, 0.7, 0.7, 1.0};
    //configura brilho
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
    //configura a posi??o da luz
    GLfloat posicaoLuz[4]={-500.0, 1000.0, -500.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4]={1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 60;

    // Define a reflet?ncia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

    // Define a concentra??o do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os par?metros da luz de n?mero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}

void desenha(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    configura_iluminacao();

    glLoadIdentity();

    gluLookAt(obs_x, 25, obs_z, obs_x + deslocamento_x, obs_y + deslocamento_y, obs_z + deslocamento_z, 0, 1, 0);

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corCenario);
        glBegin (GL_QUADS);
            glVertex3f(-TAM_CENARIO, 0, -TAM_CENARIO);
            glVertex3f(-TAM_CENARIO, 0, TAM_CENARIO);
            glVertex3f(TAM_CENARIO, 0, TAM_CENARIO);
            glVertex3f(TAM_CENARIO, 0, -TAM_CENARIO);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        desenhaChao();
        desenhaTeto();
        desenhaParede();
        glTranslated(0, 0, -45);
        desenhaFaixa();
    glPopMatrix();

    glPushMatrix();
        glTranslated(99, 0, 0);
        desenhaParede();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0, 0, -180);
        glRotated(-90, 0, 1, 0);
        glScaled(1, 1, 0.555);
        desenhaParede();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, -1);
        glRotated(-90, 0, 1, 0);
        glScalef(1, 1, 0.47);
        desenhaParede();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(84.6, 35, -1);
        glRotated(-90, 0, 1, 0);
        glScalef(1, 0.3, 0.08);
        desenhaParede();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0, 0, -25);
        desenhaMesa();
        glTranslatef(19.5, 0, 0);
        desenhaDivisoria();
        glTranslatef(20, 0, 0);
        desenhaDivisoria();
        glTranslatef(20, 0, 0);
        desenhaDivisoria();
        glTranslatef(20, 0, 0);
        desenhaDivisoria();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(11, 0, -178.99);
        alvo();
        glTranslatef(19, 0, 0);
        alvo();
        glTranslatef(20, 0, 0);
        alvo();
        glTranslatef(20, 0, 0);
        alvo();
        glTranslatef(20, 0, 0);
        alvo();
    glPopMatrix();


    glPushMatrix();
        glLineWidth(5.0);
        glColor3ub(255, 255, 0);
        glBegin(GL_LINES);
            glVertex3d(0, 0, 0);
            glVertex3d(eixo_x, eixo_y, eixo_z);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void mudaCor(float r, float g, float b) {
    corMaterial[0] = r / 255;
    corMaterial[1] = g / 255;
    corMaterial[2] = b / 255;
}

void circulo(int centroX, int centroY, int raioH, int raioV) {
    float angulo;
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i++){
            angulo = i * 2 * M_PI / 360;
            glVertex2f(centroX + (cos(angulo) * raioH), centroY + (sin(angulo) * raioV));
        }
    glEnd();
}
void alvo() {
    mudaCor(255, 255, 255);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    circulo(0, 30, 5, 10);
    glTranslatef(0, 0, 0.01);
    mudaCor(0, 0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    circulo(0, 30, 4, 8);
    glTranslatef(0, 0, 0.01);
    mudaCor(0, 100, 255);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    circulo(0, 30, 3, 6);
    glTranslatef(0, 0, 0.01);
    mudaCor(220, 0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    circulo(0, 30, 2, 4);
    glTranslatef(0, 0, 0.01);
    mudaCor(255, 255, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    circulo(0, 30, 1, 2);
}
void desenhaChao() {
    mudaCor(20, 20, 20);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_QUADS);
        glVertex3f(0, 0.01, 0);
        glVertex3f(100, 0.01, 0);
        glVertex3f(100, 0.01, -180);
        glVertex3f(0, 0.01, -180);
    glEnd();
}
void desenhaTeto() {
    mudaCor(50, 50, 50);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_QUADS);
        glVertex3i(0, 50, 0);
        glVertex3i(100, 50, 0);
        glVertex3i(100, 50, -180);
        glVertex3i(0, 50, -180);
    glEnd();

    mudaCor(100, 10, 10);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_QUADS);
        glVertex3i(0, 50, 0);
        glVertex3i(50, 75, 0);
        glVertex3i(50, 75, -180);
        glVertex3i(0, 50, -180);

        glVertex3i(50, 75, 0);
        glVertex3i(100, 50, 0);
        glVertex3i(100, 50, -180);
        glVertex3i(50, 75, -180);
    glEnd();

    mudaCor(230, 165, 100);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_TRIANGLES);
        glVertex3i(0, 50, 0);
        glVertex3i(50, 75, 0);
        glVertex3i(100, 50, 0);

        glVertex3i(0, 50, -180);
        glVertex3i(50, 75, -180);
        glVertex3i(100, 50, -180);
    glEnd();
}
void desenhaParede() {
    mudaCor(188, 108, 37);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_QUADS);
        glVertex3i(0, 0, 0);
        glVertex3i(1, 0, 0);
        glVertex3i(1, 50, 0);
        glVertex3i(0, 50, 0);

        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, -180);
        glVertex3i(0, 50, -180);
        glVertex3i(0, 50, 0);

        glVertex3i(0, 0, -180);
        glVertex3i(1, 0, -180);
        glVertex3i(1, 50, -180);
        glVertex3i(0, 50, -180);

        glVertex3i(1, 0, 0);
        glVertex3i(1, 0, -180);
        glVertex3i(1, 50, -180);
        glVertex3i(1, 50, 0);
    glEnd();
}
void desenhaFaixa() {
    mudaCor(255, 230, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_QUADS);
        glVertex3f(19.5, 0.02, 0);
        glVertex3f(19.5, 0.02, -135);
        glVertex3f(20.5, 0.02, -135);
        glVertex3f(20.5, 0.02, 0);

        glVertex3f(39.5, 0.02, 0);
        glVertex3f(39.5, 0.02, -135);
        glVertex3f(40.5, 0.02, -135);
        glVertex3f(40.5, 0.02, 0);

        glVertex3f(59.5, 0.02, 0);
        glVertex3f(59.5, 0.02, -135);
        glVertex3f(60.5, 0.02, -135);
        glVertex3f(60.5, 0.02, 0);

        glVertex3f(79.5, 0.02, 0);
        glVertex3f(79.5, 0.02, -135);
        glVertex3f(80.5, 0.02, -135);
        glVertex3f(80.5, 0.02, 0);
    glEnd();
}
void desenhaDivisoria() {
    mudaCor(35, 35, 35);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_QUADS);
        glVertex3f(0.2, 0, 0);
        glVertex3f(0.8, 0, 0);
        glVertex3f(0.8, 35, 0);
        glVertex3f(0.2, 35, 0);

        glVertex3f(0.2, 0, -20);
        glVertex3f(0.8, 0, -20);
        glVertex3f(0.8, 35, -20);
        glVertex3f(0.2, 35, -20);

        glVertex3f(0.2, 0, 0);
        glVertex3f(0.2, 35, 0);
        glVertex3f(0.2, 35, -20);
        glVertex3f(0.2, 0, -20);

        glVertex3f(0.8, 0, 0);
        glVertex3f(0.8, 35, 0);
        glVertex3f(0.8, 35, -20);
        glVertex3f(0.8, 0, -20);
    glEnd();
}
void desenhaMesa() {
    mudaCor(50, 50, 50);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMaterial);
    glBegin(GL_QUADS);
        glVertex3f(0, 10, -5);
        glVertex3f(0, 10, -12);
        glVertex3f(100, 10, -12);
        glVertex3f(100, 10, -5);

        glVertex3f(0, 10, -5);
        glVertex3f(0, 11, -5);
        glVertex3f(100, 11, -5);
        glVertex3f(100, 10, -5);

        glVertex3f(0, 11, -5);
        glVertex3f(0, 11, -12);
        glVertex3f(100, 11, -12);
        glVertex3f(100, 11, -5);

        glVertex3f(0, 10, -12);
        glVertex3f(0, 11, -12);
        glVertex3f(100, 11, -12);
        glVertex3f(100, 10, -12);
    glEnd();
}

void Special_Keys(int key, int x, int y) {
    float r;

    switch (key) {
        case GLUT_KEY_PAGE_UP:
            obs_y += deslocamento_y;
        break;

        case GLUT_KEY_PAGE_DOWN:
            obs_y -= deslocamento_y;
        break;

        case GLUT_KEY_DOWN:
            obs_x -= deslocamento_x;
            obs_z -= deslocamento_z;
        break;

        case GLUT_KEY_UP:
            obs_x += deslocamento_x;
            obs_z += deslocamento_z;
        break;

        case GLUT_KEY_LEFT:
            angulo_rotacao = angulo_rotacao - 10;
            if(angulo_rotacao < 0) angulo_rotacao +=360;
                r =  (float) (3.14159 * angulo_rotacao / 180.0f);
                deslocamento_x =  cos(r) * DIST_MOVIMENTO;
                deslocamento_z =  sin(r) * DIST_MOVIMENTO;
            break;

        case GLUT_KEY_RIGHT:
            angulo_rotacao = angulo_rotacao + 10;
            if(angulo_rotacao >= 360) angulo_rotacao -=360;
                r =  (float) (3.14159 * angulo_rotacao / 180.0f);
                deslocamento_x = cos(r) * DIST_MOVIMENTO;
                deslocamento_z = sin(r) * DIST_MOVIMENTO;
            break;
 }
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key)
    {
        case  'x': //sair
            eixo_x--;
            break;
        case  'X': //sair
            eixo_x++;
            break;
        case  'y': //sair
            eixo_y--;
            break;
        case  'Y': //sair
            eixo_y++;
            break;
        case  'z': //sair
            eixo_z--;
            break;
        case  'Z': //sair
            eixo_z++;
            break;
        case  27: //sair
            exit(0);
            break;
    }

    printf("%d %d %d\n", eixo_x, eixo_y, eixo_z);

}

void init(void) {

    glClearColor(0.8, 0.8, 1.0, 0.0);

    glShadeModel (GL_SMOOTH);

    //habilita luz 0
    glEnable(GL_LIGHT0);

    //utiliza cor do objeto como material
    glEnable(GL_COLOR_MATERIAL );
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    //habilita luz
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle,fAspect,0.5,TAM_CENARIO);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cen?rio 3D");
    //habilita tela cheia
    //glutFullScreen();
    init();
    glutDisplayFunc(desenha);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Special_Keys);
    glutMainLoop();
}



