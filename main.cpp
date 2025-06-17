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
float camDistance = 15.0f;  // Distancia aumentada para ver toda la escena expandida
int mouseX, mouseY;        // Para almacenar posici�n previa del mouse
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
            iEstiloVisualizacion = 0; // Visualizacion solida
            break;
        case VIS_ALAMBRE:
            iEstiloVisualizacion = 1; // Visualizacion en alambre
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
    
    // Menu para estilo de visualizaci�n
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
    glutAddSubMenu("Visualizacion", menuVisualizacion);
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

// **Funcion para dibujar una silla individual con rotacion**
void drawSilla(float posX, float posY, float posZ, const GLfloat* colorAsiento, const GLfloat* colorRespaldo, float rotacionY = 0.0f) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);  // Rotacion alrededor del eje Y

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

// **Funcion para dibujar una mesa individual (reutilizada y mejorada)**
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
    for(int i = 0; i < 4; i++) {  
        glPushMatrix();  
        glTranslatef(-1.0f + i * 1.1f, 1.5f, -3.7f);  
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
    glTranslatef(2.4f, -0.15f, 0.0f);  
    drawCube(9.8f, 0.7f, 1.2f, COLOR_MADERA_OSCURA);  
    glPopMatrix();  

    // Encimera  
    glPushMatrix();  
    glTranslatef(2.4f, 0.2f, 0.0f);  
    drawCube(9.8f, 0.1f, 1.2f, COLOR_GRIS);  
    glPopMatrix();  

    // Cajones  
    for(int i = 0; i < 8; i++) {  
        glPushMatrix();  
        glTranslatef(-1.8f + i * 1.2f, 0.0f, -0.6f);  
        drawCube(1.0f, 0.3f, 0.05f, COLOR_MADERA);  

        // Manija del cajon  
        glTranslatef(0.0f, 0.0f, -0.05f);  
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
    }      // Sillas de la cocina
    for (int i = 0; i < 2; i++) {  
        for (int j = 0; j < 2; j++) {  
            float posX = -1.0f + i * 2.0f;  
            float posZ = -0.8f + j * 1.6f;  
            drawSilla(posX, -0.1f, posZ, COLOR_MADERA, COLOR_MADERA, 0.0f);
        }  
    }
    glPopMatrix();  
}  

// =============================================  
// **NUEVO: COMEDOR DE RESTAURANTE**  
// =============================================  
void drawComedorRestaurante() {
    // **MESAS PARA 2 PERSONAS (rectangulares peque�as)**
    // Fila 1 - Mesas para 2
    for(int i = 0; i < 5; i++) {
        float posX = -1.8f + i * 2.0f;
        float posZ = 2.0f;
        
        // Mesa rectangular peque�a
        drawMesaIndividual(posX, -0.3f, posZ, 1.2f, 0.8f, COLOR_MADERA);
          // 2 sillas por mesa cara a cara
        drawSilla(posX, -0.1f, posZ - 0.8f, COLOR_AZUL, COLOR_MADERA, 0.0f);   // Silla frontal (normal)
        drawSilla(posX, -0.1f, posZ + 0.8f, COLOR_AZUL, COLOR_MADERA, 180.0f); // Silla trasera (volteada)
    }
    
    // **MESAS PARA 4 PERSONAS (cuadradas)**
    // Fila 2 - Mesas para 4
    for(int i = 0; i < 4; i++) {
        float posX = -1.5f + i * 2.5f;
        float posZ = 5.0f;
        
        // Mesa cuadrada
        drawMesaIndividual(posX, -0.3f, posZ, 1.4f, 1.4f, COLOR_MADERA);
          // 4 sillas alrededor de la mesa cara a cara
        drawSilla(posX - 0.9f, -0.1f, posZ, COLOR_ROJO, COLOR_MADERA, 90.0f);   // Izquierda (mirando hacia la mesa)
        drawSilla(posX + 0.9f, -0.1f, posZ, COLOR_ROJO, COLOR_MADERA, 270.0f);  // Derecha (mirando hacia la mesa)
        drawSilla(posX, -0.1f, posZ - 0.9f, COLOR_ROJO, COLOR_MADERA, 0.0f);    // Frente (normal)
        drawSilla(posX, -0.1f, posZ + 0.9f, COLOR_ROJO, COLOR_MADERA, 180.0f);  // Atras (volteada)
    }
    
}

// =============================================  
// **NUEVO: ALMACEN DE COMIDA**  
// =============================================  

void drawCajaComida(float posX, float posY, float posZ, float width, float height, float depth, const GLfloat* colorPrincipal, const GLfloat* colorEtiqueta) {
    // Caja principal
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    drawCube(width, height, depth, colorPrincipal);
    
    // Etiqueta frontal
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, (depth/2) + 0.01f);
    drawCube(width * 0.7f, height * 0.4f, 0.01f, colorEtiqueta);
    glPopMatrix();
    
    glPopMatrix();
}

void drawBotella(float posX, float posY, float posZ, float altura, const GLfloat* colorLiquido) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // **HABILITAR TRANSPARENCIA**
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // **PRIMERO DIBUJAR EL LIQUIDO (mas opaco y visible)**
    glColor4f(colorLiquido[0], colorLiquido[1], colorLiquido[2], 0.9f);  // Liquido casi opaco
    glPushMatrix();
    glTranslatef(0.0f, altura/2 - 0.05f, 0.0f);
    glScalef(0.08f, altura - 0.1f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // **LUEGO LA BOTELLA (mas transparente)**
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Vidrio muy transparente
    glPushMatrix();
    glTranslatef(0.0f, altura/2, 0.0f);
    glScalef(0.1f, altura, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // **FINALMENTE LA TAPA (opaca)**
    glColor4f(COLOR_METAL[0], COLOR_METAL[1], COLOR_METAL[2], 1.0f);  // Completamente opaca
    glPushMatrix();
    glTranslatef(0.0f, altura - 0.02f, 0.0f);
    glScalef(0.12f, 0.04f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // **DESHABILITAR TRANSPARENCIA**
    glDisable(GL_BLEND);
    
    glPopMatrix();
}

void drawSaco(float posX, float posY, float posZ, const GLfloat* colorSaco) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // Saco base (forma irregular usando esferas deformadas)
    glColor3fv(colorSaco);
    glPushMatrix();
    glScalef(0.4f, 0.6f, 0.3f);
    glutSolidSphere(0.5f, 12, 8);
    glPopMatrix();
    
    // Parte superior del saco (mas estrecha)
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    glScalef(0.25f, 0.2f, 0.2f);
    glutSolidSphere(0.5f, 12, 8);
    glPopMatrix();
    
    glPopMatrix();
}

void drawEstanteria(float posX, float posY, float posZ) {
    // Estructura principal de la estanteria
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // Postes verticales
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.8f + i * 0.8f, 0.0f, 0.0f);
        drawCube(0.1f, 2.0f, 0.1f, COLOR_METAL);
        glPopMatrix();
    }
    
    // Estantes horizontales (4 niveles)
    for(int nivel = 0; nivel < 4; nivel++) {
        glPushMatrix();
        glTranslatef(0.0f, -0.7f + nivel * 0.5f, 0.0f);
        drawCube(1.6f, 0.05f, 0.6f, COLOR_METAL);
        glPopMatrix();
    }
    
    glPopMatrix();
}

void drawCongelador() {
    glPushMatrix();
    glTranslatef(5.5f, 0.0f, -2.0f);
    
    // Cuerpo principal del congelador
    drawCube(1.2f, 1.6f, 0.8f, COLOR_BLANCO);
    
    // Tapa superior
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    drawCube(1.25f, 0.1f, 0.85f, COLOR_GRIS);
    glPopMatrix();
    
    // Manija de la tapa
    glPushMatrix();
    glTranslatef(0.4f, 0.9f, 0.0f);
    drawCube(0.2f, 0.05f, 0.1f, COLOR_NEGRO);
    glPopMatrix();
    
    // Rejilla de ventilacion
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.3f + i * 0.3f, -0.5f, 0.41f);
        drawCube(0.1f, 0.3f, 0.02f, COLOR_NEGRO);
        glPopMatrix();
    }
    
    glPopMatrix();
}

void drawAlmacenComida() {
    // **OFFSET PARA MOVER TODO EL ALMACEN**
    float offsetX = 0.5f; // Gente cambien este valor pa mover las cosas del almacen a la derecha/izquierda
    float offsetZ = -1.45f; // y este para atras o adelante
    
    // **ESTANTERIAS CON COMIDA**
    
    // Estanteria 1 - Izquierda
    drawEstanteria(4.0f + offsetX, 0.3f, -1.0f + offsetZ);
      // Productos en estanteria 1
    // Nivel inferior - Sacos de harina y azucar
    drawSaco(3.4f + offsetX, -0.4f, -2.3f + offsetZ, COLOR_BLANCO);     // Saco de harina
    drawSaco(3.8f + offsetX, -0.4f, -2.3f + offsetZ, COLOR_MARRON);     // Saco de azucar morena
    drawSaco(4.2f + offsetX, -0.4f, -2.3f + offsetZ, COLOR_BLANCO);     // Otro saco de harina
    
    // Nivel 2 - Cajas de cereales y productos secos
    drawCajaComida(3.5f + offsetX, 0.3f, -1.0f + offsetZ, 0.3f, 0.4f, 0.2f, COLOR_ROJO, COLOR_BLANCO);
    drawCajaComida(3.5f + offsetX, -0.2f, -1.1f + offsetZ, 0.25f, 0.35f, 0.15f, COLOR_AZUL, COLOR_BLANCO);
    drawCajaComida(4.3f + offsetX, -0.2f, -0.9f + offsetZ, 0.28f, 0.38f, 0.18f, COLOR_ROJO, COLOR_BLANCO);
    drawCajaComida(4.3f + offsetX, 0.3f, -0.9f + offsetZ, 0.28f, 0.38f, 0.18f, COLOR_VERDE, COLOR_BLANCO);    // Nivel 3 - Latas y conservas
    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(3.4f + offsetX + i * 0.25f, 0.6f, -1.0f + offsetZ + (i%2) * 0.1f);
        glColor3fv(COLOR_METAL);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  // Rotar para que esten verticales
        glutSolidCylinder(0.08f, 0.2f, 12, 8);
        // Etiqueta de la lata
        glColor3fv((i%2 == 0) ? COLOR_ROJO : COLOR_VERDE);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // Compensar rotacion para la etiqueta
        glTranslatef(0.0f, 0.08f, 0.1f);
        glScalef(0.1f, 0.05f, 0.01f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    
    // Nivel superior - Botellas de aceites y vinagres
    drawBotella(3.5f + offsetX, 1.1f, -1.0f + offsetZ, 0.3f, COLOR_VERDE);     // Aceite de oliva
    drawBotella(3.8f + offsetX, 1.1f, -1.1f + offsetZ, 0.25f, COLOR_ROJO);     // Vinagre
    drawBotella(4.1f + offsetX, 1.1f, -0.9f + offsetZ, 0.28f, COLOR_VERDE);    // Otro aceite
    
    // Estanteria 2 - Centro
    drawEstanteria(6.5f + offsetX, 0.3f, -0.5f + offsetZ);
      // Productos en estanteria 2
    // Nivel inferior - Cajas grandes de productos
    drawCajaComida(6.0f + offsetX, 0.35f, -0.5f + offsetZ, 0.4f, 0.5f, 0.3f, COLOR_MARRON, COLOR_BLANCO);
    drawCajaComida(6.9f + offsetX, 0.35f, -0.5f + offsetZ, 0.35f, 0.45f, 0.25f, COLOR_AZUL, COLOR_BLANCO);
    drawCajaComida(7.0f + offsetX, -0.2f, -0.45f + offsetZ, 0.38f, 0.48f, 0.28f, COLOR_VERDE, COLOR_BLANCO);
    
    // Nivel 2 - Paquetes medianos
    for(int i = 0; i < 3; i++) {
        drawCajaComida(2.7f + offsetX + i * 0.3f, 0.4f, 1.4f + offsetZ + i * 0.15f, 0.2f, 0.3f, 0.15f, 
                      (i == 0) ? COLOR_ROJO : (i == 1) ? COLOR_AZUL : COLOR_VERDE, COLOR_BLANCO);
    }      // Nivel 3 - Mas latas
    for(int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(6.0f + offsetX + i * 0.2f, 0.6f, -0.5f + offsetZ + (i%3) * 0.1f);
        glColor3fv(COLOR_METAL);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  // Rotar para que esten verticales
        glutSolidCylinder(0.06f, 0.18f, 10, 6);
        // Etiqueta de la lata
        glColor3fv((i%3 == 0) ? COLOR_ROJO : (i%3 == 1) ? COLOR_VERDE : COLOR_AZUL);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // Compensar rotacion para la etiqueta
        glTranslatef(0.0f, 0.06f, 0.09f);
        glScalef(0.08f, 0.04f, 0.01f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    
    // **CONGELADOR** (tambien se modifica la funcion drawCongelador)
    glPushMatrix();
    glTranslatef(5.5f + offsetX, 0.0f, -2.0f + offsetZ);
    
    // Cuerpo principal del congelador
    drawCube(1.2f, 1.6f, 0.8f, COLOR_BLANCO);
    
    // Tapa superior
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    drawCube(1.25f, 0.1f, 0.85f, COLOR_GRIS);
    glPopMatrix();
    
    // Manija de la tapa
    glPushMatrix();
    glTranslatef(0.4, 0.9f, 0.0f);
    drawCube(0.2f, 0.05f, 0.1f, COLOR_NEGRO);
    glPopMatrix();
    
    // Rejilla de ventilacion
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.3f + i * 0.3f, -0.5f, 0.41f);
        drawCube(0.1f, 0.3f, 0.02f, COLOR_NEGRO);
        glPopMatrix();
    }
    
    glPopMatrix();
      // **CAJAS EN EL TECHO**
    // Cajas apiladas cerca del congelador
    drawCajaComida(6.2f + offsetX, 1.4f, -0.5f + offsetZ, 0.5f, 0.4f, 0.4f, COLOR_MARRON, COLOR_BLANCO);
    drawCajaComida(6.2f + offsetX, -0.2f, -0.45f + offsetZ, 0.45f, 0.35f, 0.35f, COLOR_ROJO, COLOR_BLANCO);
    
    // Mas cajas dispersas (sobre la barra ya q estamos xdd)
    drawCajaComida(4.5f + offsetX, 0.4f, 1.7f + offsetZ, 0.4f, 0.3f, 0.3f, COLOR_AZUL, COLOR_BLANCO);
    drawCajaComida(5.8f + offsetX, 0.4f, 1.7f + offsetZ, 0.35f, 0.35f, 0.25f, COLOR_VERDE, COLOR_BLANCO);
    
    // **SACOS ADICIONALES EN EL SUELO**
    for(int i=0; i<2; i++) {
        drawSaco(6.5f + offsetX + i, -0.5f, -2.3f + offsetZ, COLOR_BLANCO);      // Saco de arroz
        drawSaco(6.8f + offsetX + i, -0.5f, -2.3f + offsetZ, COLOR_MARRON);     // Saco de frijoles
    }
    
    
    // **BOTELLAS EN LA BARRA**
    for(int i = 0; i < 9; i++) {
        drawBotella(4.2f + offsetX + i * 0.2f, 0.25f, 1.0f + offsetZ, 0.4f, 
                   (i == 0) ? COLOR_VERDE : (i == 1) ? COLOR_ROJO : COLOR_AZUL);
    }
}



// =============================================  
// **INTEGRADOR (GERARDO): ENTORNO, CAMARA Y ESCENA**  
// ============================================= 
void drawPiso() {  
    // Piso principal de la cocina extendido hasta la pared derecha
    glPushMatrix();  
    glTranslatef(2.25f, -0.7f, -1.5f);  // Recentrado para cubrir hasta pared derecha
    drawCube(12.5f, 0.1f, 5.0f, COLOR_GRIS);  // Ancho aumentado para llegar a X=8.5
    glPopMatrix();  
    
    // Piso del comedor extendido hasta la pared derecha
    glPushMatrix();  
    glTranslatef(2.25f, -0.7f, 4.0f);  // Recentrado para cubrir hasta pared derecha
    drawCube(12.5f, 0.1f, 6.0f, COLOR_GRIS);  // Ancho aumentado para llegar a X=8.5
    glPopMatrix();
}

void drawParedes() {  
    // Pared trasera de la cocina (extendida para cubrir tambien el almacen)
    glPushMatrix();  
    //el primer float 
    glTranslatef(2.2f, 0.6f, -4.0f);  // Centrada para cubrir cocina + almacen
    drawCube(12.5f, 2.6f, 0.1f, COLOR_BLANCO);  // Mas anchaW
    glPopMatrix();  

    // Pared lateral IZQUIERDA de la cocina (extendida para incluir el comedor)
    glPushMatrix();  
    glTranslatef(-4.0f, 0.6f, 1.5f);  // Solo la pared izquierda
    drawCube(0.1f, 2.6f, 11.0f, COLOR_BLANCO); // Extendida hacia adelante
    glPopMatrix();  
      // Pared lateral derecha del almacen (ajustada al mismo tamaño que la izquierda)
    glPushMatrix();
    glTranslatef(8.5f, 0.6f, 1.5f);  // Misma posicion Z que la pared izquierda
    drawCube(0.1f, 2.6f, 11.0f, COLOR_BLANCO);  // Misma profundidad que la pared izquierda
    glPopMatrix();

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
        if (camDistance < 5.0f) camDistance = 5.0f; // M�nimo ajustado
        glutPostRedisplay();
    }
    else if (button == 4 && state == GLUT_DOWN) { // Rueda abajo
        camDistance += 0.5f;
        if (camDistance > 25.0f) camDistance = 25.0f; // M�ximo aumentado
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
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
    }
    
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  

	// Calcula posicion de camara con coordenadas esfericas
    float camX = camDistance * cos(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);
    float camY = camDistance * sin(camAngleX * M_PI/180);
    float camZ = camDistance * sin(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);    // Vista (punto de mira ajustado para centrar toda la escena expandida)
    gluLookAt(  
        camX, camY, camZ,  // Posicion de la camara
        2.25f, 0.0f, 0.5f,  // Punto al que mira (centrado en la escena completa)
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

    // Dibujar el nuevo almacen de comida
    drawAlmacenComida();
    
    glutSwapBuffers();  
}  

void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // Ajusta el viewport al nuevo tama�o
    glMatrixMode(GL_PROJECTION);  // Selecciona la matriz de proyecci�n
    glLoadIdentity();  // Reinicia la matriz
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);  // Proyeccion en perspectiva
    glMatrixMode(GL_MODELVIEW);  // Vuelve a la matriz de modelo-vista
}  

int main(int argc, char** argv) {  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(1024, 768);  // Ventana m�s grande para ver mejor la escena expandida
    glutCreateWindow("Cocina 3D con Comedor de Restaurante - Grupo 10");      // Configuracion OpenGL  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);  
    glEnable(GL_COLOR_MATERIAL);  
    glEnable(GL_NORMALIZE);
    
    // **CONFIGURACION PARA TRANSPARENCIA**
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);  // Deshabilitado por defecto, se activa solo cuando se necesita
    
    creacionMenu();

    // Callbacks  
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);  
    glutMouseFunc(onMouse);      // Para clics del mouse
    glutMotionFunc(onMotion);    // Para movimiento con boton presionado

    glutMainLoop();  
    return 0;  
}
