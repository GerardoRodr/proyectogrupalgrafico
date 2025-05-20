#include <GL/freeglut.h>
#include <cmath>
#include <windows.h>
#include "mmsystem.h"

// =============================================  
// **SECCION COMPARTIDA (TODOS)**  
// =============================================  

int iFondo = 0;
int iEstiloVisualizacion = 0; // 0=solido, 1=alambre

typedef enum {
    FONDO1, FONDO2, FONDO3,
    VIS_SOLIDO, VIS_ALAMBRE,
    SONIDO_ON, SONIDO_OFF
} opcionesMenu;

// **Paleta de colores**
const GLfloat COLOR_BLANCO[] = {1.0f, 1.0f, 1.0f};  
const GLfloat COLOR_NEGRO[] = {0.1f, 0.1f, 0.1f};  
const GLfloat COLOR_GRIS[] = {0.6f, 0.6f, 0.6f};  
const GLfloat COLOR_MADERA[] = {0.8f, 0.5f, 0.2f};  
const GLfloat COLOR_MADERA_OSCURA[] = {0.6f, 0.3f, 0.1f};  
const GLfloat COLOR_METAL[] = {0.8f, 0.8f, 0.9f};  
const GLfloat COLOR_AZUL[] = {0.0f, 0.4f, 0.8f};  
const GLfloat COLOR_ROJO[] = {0.8f, 0.1f, 0.1f};  

// **MENU**
void onMenu(int opcion) {
    switch(opcion) {
        case FONDO1:
            iFondo = 0; // Color de fondo 1
            break;
        case FONDO2:
            iFondo = 1; // Color de fondo 2
            break;
        case FONDO3:
            iFondo = 2; // Color de fondo 3
            break;
        case VIS_SOLIDO:
            iEstiloVisualizacion = 0; // Visualización sólida
            break;
        case VIS_ALAMBRE:
            iEstiloVisualizacion = 1; // Visualización en alambre
            break;
        case SONIDO_ON:
            PlaySound(TEXT("Revolution-909.wav"), NULL, SND_LOOP | SND_ASYNC);
            break;
        case SONIDO_OFF:
            PlaySound(NULL, 0, 0); // Detiene el sonido
            break;
    }
    glutPostRedisplay();
}

void creacionMenu(void) {
    int menuFondo, menuVisualizacion, menuSonido, menuPrincipal;
    
    // Menu para color de fondo
    menuFondo = glutCreateMenu(onMenu);
    glutAddMenuEntry("Gris claro", FONDO1);
    glutAddMenuEntry("Blanco", FONDO2);
    glutAddMenuEntry("Beige", FONDO3);
    
    // Menu para estilo de visualización
    menuVisualizacion = glutCreateMenu(onMenu);
    glutAddMenuEntry("Solido", VIS_SOLIDO);
    glutAddMenuEntry("Alambre", VIS_ALAMBRE);
    
    // Menu para sonido ambiente
    menuSonido = glutCreateMenu(onMenu);
    glutAddMenuEntry("Sonido ON", SONIDO_ON);
    glutAddMenuEntry("Sonido OFF", SONIDO_OFF);
    
    // Menu principal que agrupa los submenus
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Color de fondo", menuFondo);
    glutAddSubMenu("Visualización", menuVisualizacion);
    glutAddSubMenu("Sonido", menuSonido);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON); // menu con clic derecho
}

// **Funcion basica para dibujar cubos (compartida)**  
void drawCube(GLfloat width, GLfloat height, GLfloat depth, const GLfloat* color) {  
    glPushMatrix();  
    glColor3fv(color);  
    glScalef(width, height, depth);  

    // Frente  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, 0.0f, 1.0f);  
    glVertex3f(-0.5f, -0.5f, 0.5f);  
    glVertex3f(0.5f, -0.5f, 0.5f);  
    glVertex3f(0.5f, 0.5f, 0.5f);  
    glVertex3f(-0.5f, 0.5f, 0.5f);  
    glEnd();  

    // Atras  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, 0.0f, -1.0f);  
    glVertex3f(-0.5f, -0.5f, -0.5f);  
    glVertex3f(-0.5f, 0.5f, -0.5f);  
    glVertex3f(0.5f, 0.5f, -0.5f);  
    glVertex3f(0.5f, -0.5f, -0.5f);  
    glEnd();  

    // Arriba  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, 1.0f, 0.0f);  
    glVertex3f(-0.5f, 0.5f, -0.5f);  
    glVertex3f(-0.5f, 0.5f, 0.5f);  
    glVertex3f(0.5f, 0.5f, 0.5f);  
    glVertex3f(0.5f, 0.5f, -0.5f);  
    glEnd();  

    // Abajo  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, -1.0f, 0.0f);  
    glVertex3f(-0.5f, -0.5f, -0.5f);  
    glVertex3f(0.5f, -0.5f, -0.5f);  
    glVertex3f(0.5f, -0.5f, 0.5f);  
    glVertex3f(-0.5f, -0.5f, 0.5f);  
    glEnd();  

    // Derecha  
    glBegin(GL_QUADS);  
    glNormal3f(1.0f, 0.0f, 0.0f);  
    glVertex3f(0.5f, -0.5f, -0.5f);  
    glVertex3f(0.5f, 0.5f, -0.5f);  
    glVertex3f(0.5f, 0.5f, 0.5f);  
    glVertex3f(0.5f, -0.5f, 0.5f);  
    glEnd();  

    // Izquierda  
    glBegin(GL_QUADS);  
    glNormal3f(-1.0f, 0.0f, 0.0f);  
    glVertex3f(-0.5f, -0.5f, -0.5f);  
    glVertex3f(-0.5f, -0.5f, 0.5f);  
    glVertex3f(-0.5f, 0.5f, 0.5f);  
    glVertex3f(-0.5f, 0.5f, -0.5f);  
    glEnd();  

    glPopMatrix();  
}  

// =============================================  
// **Jheferson: FREGADERO**  
// =============================================  
void drawFregadero() {  
    // Base del fregadero  
    glPushMatrix();  
    glTranslatef(-1.5f, 0.1f, 0.0f);  

    // Grifo  
    glPushMatrix();  
    glTranslatef(0.0f, 0.3f, 0.0f);  
    glColor3fv(COLOR_METAL);  
    glutSolidCylinder(0.03f, 0.3f, 8, 8);  

    glTranslatef(0.0f, 0.0f, 0.15f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  
    glutSolidCylinder(0.03f, 0.3f, 8, 8);  
    glPopMatrix();  

    glPopMatrix();  
}  

// =============================================  
// **Brenda: GABINETES SUPERIORES**  
// =============================================  
void drawGabinetesSuperiores() {  
    for(int i = 0; i < 3; i++) {  
        glPushMatrix();  
        glTranslatef(-1.0f + i * 1.1f, 1.5f, -0.8f);  
        drawCube(1.0f, 0.6f, 0.4f, COLOR_MADERA);  

        // Puerta del gabinete  
        glTranslatef(0.0f, 0.0f, 0.21f);  
        drawCube(0.9f, 0.5f, 0.02f, COLOR_MADERA_OSCURA);  

        // Manija  
        glTranslatef(0.35f, 0.0f, 0.03f);  
        drawCube(0.08f, 0.08f, 0.04f, COLOR_METAL);  

        glPopMatrix();  
    }  
}  

// =============================================  
// **Bryan: ENCIMERA Y BASE**  
// =============================================  
void drawEncimera() {  
    // Base de los gabinetes  
    glPushMatrix();  
    glTranslatef(0.0f, -0.15f, 0.0f);  
    drawCube(5.0f, 0.7f, 1.2f, COLOR_MADERA_OSCURA);  
    glPopMatrix();  

    // Encimera  
    glPushMatrix();  
    glTranslatef(0.0f, 0.2f, 0.0f);  
    drawCube(5.0f, 0.1f, 1.2f, COLOR_GRIS);  
    glPopMatrix();  

    // Cajones  
    for(int i = 0; i < 4; i++) {  
        glPushMatrix();  
        glTranslatef(-1.8f + i * 1.2f, 0.0f, 0.65f);  
        drawCube(1.0f, 0.3f, 0.05f, COLOR_MADERA);  

        // Manija del cajón  
        glTranslatef(0.0f, 0.0f, 0.05f);  
        drawCube(0.2f, 0.04f, 0.04f, COLOR_METAL);  
        glPopMatrix();  
    }  
}  

// =============================================  
// **Jose: REFRIGERADOR Y ESTUFA**  
// =============================================  
void drawRefrigerador() {  
    // Cuerpo principal  
    glPushMatrix();  
    glTranslatef(-2.5f, 0.25f, -3.5f);  
    drawCube(1.0f, 1.8f, 0.8f, COLOR_GRIS);  

    // Manija  
    glPushMatrix();  
    glTranslatef(0.4f, 0.0f, 0.45f);  
    drawCube(0.1f, 0.3f, 0.05f, COLOR_METAL);  
    glPopMatrix();  

    glPopMatrix();  
}  

void drawEstufa() {  
    // Base de la estufa  
    glPushMatrix();  
    glTranslatef(1.8f, 0.25f, 0.0f);  
    drawCube(1.4f, 0.1f, 1.0f, COLOR_NEGRO);  

    // Quemadores (usando glutSolidTorus)  
    for (int i = -1; i <= 1; i += 2) {  
        for (int j = -1; j <= 1; j += 2) {  
            glPushMatrix();  
            glTranslatef(i * 0.4f, 0.06f, j * 0.3f);  
            glColor3fv(COLOR_NEGRO);  
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  
            glutSolidTorus(0.05f, 0.15f, 16, 16);  
            glPopMatrix();  
        }  
    }  
    glPopMatrix();  
}  

// =============================================  
// **Angello: MESA Y SILLAS**  
// =============================================  
void drawMesa() {  
    // Mesa  
    glPushMatrix();  
    glTranslatef(0.0f, -0.3f, -2.5f);  

    // Superficie  
    glPushMatrix();  
    glTranslatef(0.0f, 0.4f, 0.0f);  
    drawCube(1.6f, 0.1f, 1.0f, COLOR_MADERA);  
    glPopMatrix();  

    // Patas  
    for (int i = -1; i <= 1; i += 2) {  
        for (int j = -1; j <= 1; j += 2) {  
            glPushMatrix();  
            glTranslatef(i * 0.7f, 0.0f, j * 0.4f);  
            drawCube(0.1f, 0.8f, 0.1f, COLOR_MADERA_OSCURA);  
            glPopMatrix();  
        }  
    }  

    // Sillas  
    for (int i = 0; i < 2; i++) {  
        for (int j = 0; j < 2; j++) {  
            float posX = -1.0f + i * 2.0f;  
            float posZ = -0.8f + j * 1.6f;  

            glPushMatrix();  
            glTranslatef(posX, -0.1f, posZ);  

            // Asiento  
            glPushMatrix();  
            glTranslatef(0.0f, 0.2f, 0.0f);  
            drawCube(0.4f, 0.05f, 0.4f, COLOR_MADERA);  
            glPopMatrix();  

            // Respaldo  
            glPushMatrix();  
            glTranslatef(0.0f, 0.5f, -0.2f);  
            drawCube(0.4f, 0.6f, 0.05f, COLOR_MADERA);  
            glPopMatrix();  

            // Patas  
            for (int k = -1; k <= 1; k += 2) {  
                for (int l = -1; l <= 1; l += 2) {  
                    glPushMatrix();  
                    glTranslatef(k * 0.15f, 0.0f, l * 0.15f);  
                    drawCube(0.05f, 0.4f, 0.05f, COLOR_MADERA_OSCURA);  
                    glPopMatrix();  
                }  
            }  
            glPopMatrix();  
        }  
    }  
    glPopMatrix();  
}  

// =============================================  
// **INTEGRADOR (GERARDO): ENTORNO, CAMARA Y ESCENA**  
// ============================================= 
void drawPiso() {  
    glPushMatrix();  
    glTranslatef(0.0f, -0.7f, -1.5f);  
    drawCube(6.0f, 0.1f, 5.0f, COLOR_GRIS);  
    glPopMatrix();  
}  

void drawParedes() {  
    // Pared trasera  
    glPushMatrix();  
    glTranslatef(0.0f, 0.6f, -4.0f);  
    drawCube(6.0f, 2.6f, 0.1f, COLOR_BLANCO);  
    glPopMatrix();  

    // Paredes laterales  
    for (int i = -1; i <= 1; i += 2) {  
        glPushMatrix();  
        glTranslatef(i * 3.0f, 0.6f, -1.5f);  
        drawCube(0.1f, 2.6f, 5.0f, COLOR_BLANCO);  
        glPopMatrix();  
    }  
}  

// =============================================  
// **FUNCIONES PRINCIPALES (RENDER Y CONFIG)**  
// =============================================  
void display() {  
    // Colores de fondo posibles
    float coloresFondo[3][3] = {
        {0.8f, 0.8f, 0.8f}, // Gris claro
        {1.0f, 1.0f, 1.0f}, // Blanco
        {0.96f, 0.96f, 0.86f} // Beige
    };
    
    glClearColor(coloresFondo[iFondo][0], 
                coloresFondo[iFondo][1], 
                coloresFondo[iFondo][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Configura el estilo de visualización
    if(iEstiloVisualizacion == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Alambre
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Sólido
    }
    
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  

    // Vista
    gluLookAt(  
        5.0f, 3.0f, 5.0f,  // Posicion de la cámara (vista en diagonal)
        0.0f, 0.0f, -1.5f,  // Punto al que mira  
        0.0f, 1.0f, 0.0f    // Vector "arriba"  
    );  

    // Dibujar elementos  
    drawParedes();  
    drawPiso();  
    drawGabinetesSuperiores();  
    drawEncimera();  
    drawRefrigerador();  
    drawEstufa();  
    drawMesa();  
    drawFregadero();  
    glutSwapBuffers();  
}  

void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // Ajusta el viewport al nuevo tamaño
    glMatrixMode(GL_PROJECTION);  // Selecciona la matriz de proyección
    glLoadIdentity();  // Reinicia la matriz
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);  // Proyeccion en perspectiva
    glMatrixMode(GL_MODELVIEW);  // Vuelve a la matriz de modelo-vista
}  

int main(int argc, char** argv) {  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Cocina 3D - Grupo 10");  

    // Configuración OpenGL  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);  
    glEnable(GL_COLOR_MATERIAL);  
    glEnable(GL_NORMALIZE);    
    
    creacionMenu();

    // Callbacks  
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);  

    glutMainLoop();  
    return 0;  
}
