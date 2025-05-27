#include <GL/freeglut.h>
#include <cmath>
#include <windows.h>
#include "mmsystem.h"

// =============================================  
// **SECCION COMPARTIDA (TODOS)**  
// =============================================  

int iFondo = 0;
int iEstiloVisualizacion = 0; // 0=solido, 1=alambre

float camAngleX = 20.0f;   // Inclinacion vertical inicial (grados)
float camAngleY = 45.0f;   // Rotacion horizontal inicial (grados)
float camDistance = 12.0f;  // Distancia aumentada para ver toda la escena
int mouseX, mouseY;        // Para almacenar posición previa del mouse
bool mouseLeftDown = false; // Estado del boton izquierdo

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
const GLfloat COLOR_VERDE[] = {0.2f, 0.6f, 0.2f};
const GLfloat COLOR_MARRON[] = {0.4f, 0.2f, 0.1f};

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

// **Función para dibujar una silla individual (reutilizada y mejorada)**
void drawSilla(float posX, float posY, float posZ, const GLfloat* colorAsiento, const GLfloat* colorRespaldo) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);

    // Asiento
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    drawCube(0.4f, 0.05f, 0.4f, colorAsiento);
    glPopMatrix();

    // Respaldo
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, -0.2f);
    drawCube(0.4f, 0.6f, 0.05f, colorRespaldo);
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

// **Función para dibujar una mesa individual (reutilizada y mejorada)**
void drawMesaIndividual(float posX, float posY, float posZ, float width, float depth, const GLfloat* colorSuperficie) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);

    // Superficie de la mesa
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    drawCube(width, 0.1f, depth, colorSuperficie);
    glPopMatrix();

    // Patas de la mesa
    float offsetX = (width - 0.1f) * 0.5f * 0.8f; // Un poco hacia adentro
    float offsetZ = (depth - 0.1f) * 0.5f * 0.8f;
    
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * offsetX, 0.0f, j * offsetZ);
            drawCube(0.1f, 0.8f, 0.1f, COLOR_MADERA_OSCURA);
            glPopMatrix();
        }
    }
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
// **Angello: MESA Y SILLAS (COCINA)**  
// =============================================  
void drawMesa() {  
    // Mesa de la cocina (mesa original)
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

    // Sillas de la cocina
    for (int i = 0; i < 2; i++) {  
        for (int j = 0; j < 2; j++) {  
            float posX = -1.0f + i * 2.0f;  
            float posZ = -0.8f + j * 1.6f;  
            drawSilla(posX, -0.1f, posZ, COLOR_MADERA, COLOR_MADERA);
        }  
    }  
    glPopMatrix();  
}  

// =============================================  
// **NUEVO: COMEDOR DE RESTAURANTE**  
// =============================================  
void drawComedorRestaurante() {
    // **MESAS PARA 2 PERSONAS (rectangulares pequeñas)**
    // Fila 1 - Mesas para 2
    for(int i = 0; i < 3; i++) {
        float posX = -2.0f + i * 2.0f;
        float posZ = 2.0f;
        
        // Mesa rectangular pequeña
        drawMesaIndividual(posX, -0.3f, posZ, 1.2f, 0.8f, COLOR_MADERA);
        
        // 2 sillas por mesa (una en cada extremo del lado corto)
        drawSilla(posX, -0.1f, posZ - 0.8f, COLOR_AZUL, COLOR_MADERA); // Silla frontal
        drawSilla(posX, -0.1f, posZ + 0.8f, COLOR_AZUL, COLOR_MADERA); // Silla trasera
    }
    
    // **MESAS PARA 4 PERSONAS (cuadradas)**
    // Fila 2 - Mesas para 4
    for(int i = 0; i < 2; i++) {
        float posX = -1.0f + i * 2.5f;
        float posZ = 5.0f;
        
        // Mesa cuadrada
        drawMesaIndividual(posX, -0.3f, posZ, 1.4f, 1.4f, COLOR_MADERA);
        
        // 4 sillas alrededor de la mesa
        drawSilla(posX - 0.9f, -0.1f, posZ, COLOR_ROJO, COLOR_MADERA);     // Izquierda
        drawSilla(posX + 0.9f, -0.1f, posZ, COLOR_ROJO, COLOR_MADERA);     // Derecha
        drawSilla(posX, -0.1f, posZ - 0.9f, COLOR_ROJO, COLOR_MADERA);     // Frente
        drawSilla(posX, -0.1f, posZ + 0.9f, COLOR_ROJO, COLOR_MADERA);     // Atrás
    }
    
}

// =============================================  
// **INTEGRADOR (GERARDO): ENTORNO, CAMARA Y ESCENA**  
// ============================================= 
void drawPiso() {  
    // Piso de la cocina
    glPushMatrix();  
    glTranslatef(0.0f, -0.7f, -1.5f);  
    drawCube(8.0f, 0.1f, 5.0f, COLOR_GRIS);  
    glPopMatrix();  
    
    // Piso del comedor (extendido hacia adelante)
    glPushMatrix();  
    glTranslatef(0.0f, -0.7f, 4.0f);  
    drawCube(8.0f, 0.1f, 6.0f, COLOR_GRIS);  
    glPopMatrix();
}  

void drawParedes() {  
    // Pared trasera de la cocina
    glPushMatrix();  
    glTranslatef(0.0f, 0.6f, -4.0f);  
    drawCube(8.0f, 2.6f, 0.1f, COLOR_BLANCO);  
    glPopMatrix();  

    // Paredes laterales (extendidas para incluir el comedor)
    for (int i = -1; i <= 1; i += 2) {  
        glPushMatrix();  
        glTranslatef(i * 4.0f, 0.6f, 1.5f);  // Extendidas y reposicionadas
        drawCube(0.1f, 2.6f, 11.0f, COLOR_BLANCO); // Más largas  
        glPopMatrix();  
    }
}  

// **MOVIMIENTO CON EL MOUSE**
void onMouse(int button, int state, int x, int y) {
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) {
	mouseX = x;
	mouseY = y;
	}
	
    // Zoom con rueda del mouse
    else if (button == 3 && state == GLUT_DOWN) { // Rueda arriba
        camDistance -= 0.5f;
        if (camDistance < 5.0f) camDistance = 5.0f; // Mínimo ajustado
        glutPostRedisplay();
    }
    else if (button == 4 && state == GLUT_DOWN) { // Rueda abajo
        camDistance += 0.5f;
        if (camDistance > 25.0f) camDistance = 25.0f; // Máximo aumentado
        glutPostRedisplay();
    }
}
void onMotion(int x, int y) {
	camAngleX = (camAngleX + (y - mouseY));
	camAngleY = (camAngleY + (x - mouseX));
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
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
    
    // Configura el estilo de visualizacion
    if(iEstiloVisualizacion == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Alambre
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Sólido
    }
    
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  

	// Calcula posicion de camara con coordenadas esféricas
    float camX = camDistance * cos(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);
    float camY = camDistance * sin(camAngleX * M_PI/180);
    float camZ = camDistance * sin(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);

    // Vista (punto de mira ajustado para centrar toda la escena)
    gluLookAt(  
        camX, camY, camZ,  // Posicion de la camara
        0.0f, 0.0f, 1.0f,  // Punto al que mira (más hacia adelante)
        0.0f, 1.0f, 0.0f    // Vector "arriba"  
    );  

    // Dibujar elementos de la cocina
    drawParedes();  
    drawPiso();  
    drawGabinetesSuperiores();  
    drawEncimera();  
    drawRefrigerador();  
    drawEstufa();  
    drawMesa(); // Mesa original de la cocina
    drawFregadero();  
    
    // Dibujar el nuevo comedor de restaurante
    drawComedorRestaurante();
    
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
    glutInitWindowSize(1024, 768);  // Ventana más grande para ver mejor la escena expandida
    glutCreateWindow("Cocina 3D con Comedor de Restaurante - Grupo 10");  

    // Configuracion OpenGL  
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
    glutMouseFunc(onMouse);      // Para clics del mouse
    glutMotionFunc(onMotion);    // Para movimiento con boton presionado

    glutMainLoop();  
    return 0;  
}
