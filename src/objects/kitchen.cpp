#include "objects/kitchen.h"

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
    glTranslatef(2.0f, -0.15f, 0.0f);  
    drawCube(9.0f, 0.7f, 1.2f, COLOR_MADERA_OSCURA);  
    glPopMatrix();  

    // Encimera  
    glPushMatrix();  
    glTranslatef(2.0f, 0.2f, 0.0f);  
    drawCube(9.1f, 0.1f, 1.3f, COLOR_GRIS);  
    glPopMatrix();  

    // Cajones  
    for(int i = 0; i < 7; i++) {  
        glPushMatrix();  
        glTranslatef(-1.7f + i * 1.2f, -0.1f, -0.6f);  
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
    drawCube(1.0f, 1.8f, 0.8f, COLOR_METAL);  

    // Manija  
    glPushMatrix();  
    glTranslatef(0.4f, 0.0f, 0.45f);  
    drawCube(0.1f, 0.3f, 0.05f, COLOR_GRIS);  
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
            drawSilla(posX, -0.1f, posZ, COLOR_MADERA, COLOR_MADERA, 0.0f);
        }  
    }
    glPopMatrix();  
}

// Funcion principal para dibujar toda la cocina
void drawKitchen() {
    drawGabinetesSuperiores();  
    drawEncimera();  
    drawRefrigerador();  
    drawEstufa();  
    drawMesa();
    drawFregadero();  
}

// =============================================  
// **SEGUNDO PISO - COCINA EXTENSION**  
// =============================================  

// Altura constante del segundo piso (3.2 metros sobre el primer piso)
const float ALTURA_SEGUNDO_PISO = 3.2f;

void drawSegundoPisoParedes() {
    // Pared trasera del segundo piso (mismas dimensiones que primer piso)
    glPushMatrix();  
    glTranslatef(2.2f, 0.6f + ALTURA_SEGUNDO_PISO, -4.0f);  
    drawCube(12.5f, 2.6f, 0.1f, COLOR_BLANCO);  
    glPopMatrix();  

    // Pared lateral IZQUIERDA del segundo piso
    glPushMatrix();  
    glTranslatef(-4.0f, 0.6f + ALTURA_SEGUNDO_PISO, 1.5f);  
    drawCube(0.1f, 2.6f, 11.0f, COLOR_BLANCO); 
    glPopMatrix();  
    
    // Pared lateral derecha del segundo piso
    glPushMatrix();
    glTranslatef(8.5f, 0.6f + ALTURA_SEGUNDO_PISO, 1.5f);  
    drawCube(0.1f, 2.6f, 11.0f, COLOR_BLANCO);  
    glPopMatrix();
}
//Segundo piso piso xddddddd
void drawSegundoPisoPiso() {
    // Piso del segundo piso
    glPushMatrix();  
    glTranslatef(1.45f, -0.7f + ALTURA_SEGUNDO_PISO, -1.5f);  
    drawCube(10.9f, 0.1f, 5.0f, COLOR_GRIS);  
    glPopMatrix();  
    
    // Extension del piso hacia el area del comedor
    glPushMatrix();  
    glTranslatef(2.25f, -0.7f + ALTURA_SEGUNDO_PISO, 4.0f);  
    drawCube(12.5f, 0.1f, 6.0f, COLOR_GRIS);  
    glPopMatrix();
}

void drawSegundoPisoFregadero() {  
    // CONVERTIDO A: Barra principal del bar (30% del espacio)
    // Mostrador lineal orientado hacia escaleras
    glPushMatrix();  
    glTranslatef(3.5f, -0.1f + ALTURA_SEGUNDO_PISO, -3.5f);  

    // Base del mostrador (estructura principal)
    glPushMatrix();  
    glTranslatef(0.0f, 0.0f, 0.0f);  
    drawCube(6.0f, 0.8f, 0.8f, COLOR_MADERA_OSCURA);  
    glPopMatrix();

    // Superficie superior del bar
    glPushMatrix();  
    glTranslatef(0.0f, 0.45f, 0.0f);  
    drawCube(6.2f, 0.1f, 1.0f, COLOR_NEGRO);  // Superficie elegante negra
    glPopMatrix();

    // Repisa inferior para vasos
    glPushMatrix();  
    glTranslatef(0.0f, -0.2f, 0.3f);  
    drawCube(5.8f, 0.05f, 0.4f, COLOR_MADERA);  
    glPopMatrix();

    glPopMatrix();  
}

void drawSegundoPisoGabinetesSuperiores() {  
    // CONVERTIDO A: Estanteria para botellas detras del bar
    for(int i = 0; i < 6; i++) {  
        glPushMatrix();  
        glTranslatef(1.0f + i * 1.0f, 1.2f + ALTURA_SEGUNDO_PISO, -3.9f);  
        
        // Estante principal para botellas
        drawCube(0.8f, 1.2f, 0.3f, COLOR_MADERA);  

        // Divisiones para botellas (3 niveles)
        for(int j = 0; j < 3; j++) {
            glPushMatrix();
            glTranslatef(0.0f, -0.3f + j * 0.3f, 0.0f);  
            drawCube(0.75f, 0.03f, 0.25f, COLOR_MADERA_OSCURA);  
            glPopMatrix();
        }

        // Marco decorativo frontal
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.16f);  
        drawCube(0.78f, 1.15f, 0.02f, COLOR_MADERA_OSCURA);  
        glPopMatrix();

        glPopMatrix();  
    }  
}

void drawSegundoPisoEncimera() {  
    // CONVERTIDO A: Taburetes del bar (6 taburetes)
    for(int i = 0; i < 6; i++) {  
        glPushMatrix();  
        glTranslatef(1.5f + i * 1.0f, ALTURA_SEGUNDO_PISO -0.6f, -2.5f);  
        
        // Asiento del taburete
        glPushMatrix();  
        glTranslatef(0.0f, 0.6f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  
        glColor3fv(COLOR_MARRON);  
        glutSolidCylinder(0.25f, 0.05f, 16, 8);  
        glPopMatrix();

        // Pata central del taburete
        glPushMatrix();  
        glTranslatef(0.0f, 0.3f, 0.0f);  
        drawCube(0.08f, 0.6f, 0.08f, COLOR_METAL);  
        glPopMatrix();

        // Base del taburete
        glPushMatrix();  
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  
        glColor3fv(COLOR_METAL);  
        glutSolidCylinder(0.25f, 0.05f, 16, 8);  
        glPopMatrix();

        // Reposapies
        glPushMatrix();  
        glTranslatef(0.0f, 0.25f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  
        glColor3fv(COLOR_METAL);  
        glutSolidTorus(0.02f, 0.15f, 8, 16);  
        glPopMatrix();

        glPopMatrix();  
    }  
}

void drawSegundoPisoRefrigerador() {  
    // CONVERTIDO A: Estacion de cafe/maquina expendedora
    glPushMatrix();  
    glTranslatef(-2.5f, 0.25f + ALTURA_SEGUNDO_PISO, -3.5f);  
    
    // Base de la maquina de cafe
    drawCube(1.0f, 1.8f, 0.8f, COLOR_NEGRO);  

    // Panel frontal metalico
    glPushMatrix();  
    glTranslatef(0.0f, 0.2f, 0.41f);  
    drawCube(0.8f, 1.0f, 0.02f, COLOR_METAL);  
    glPopMatrix();

    // Pantalla de la maquina
    glPushMatrix();  
    glTranslatef(0.0f, 0.5f, 0.42f);  
    drawCube(0.3f, 0.2f, 0.02f, COLOR_NEGRO);  
    glPopMatrix();

    // Botones de seleccion (3 botones)
    for(int i = -1; i <= 1; i++) {
        glPushMatrix();  
        glTranslatef(i * 0.15f, 0.0f, 0.42f);  
        glColor3fv(COLOR_ROJO);  
        glutSolidCylinder(0.03f, 0.02f, 8, 4);  
        glPopMatrix();
    }

    // Bandeja de salida
    glPushMatrix();  
    glTranslatef(0.0f, -0.3f, 0.3f);  
    drawCube(0.4f, 0.1f, 0.2f, COLOR_METAL);  
    glPopMatrix();

    glPopMatrix();  
}

void drawVIPSquareTable() {  
    // CONVERTIDO A: Zona VIP - Mesa cuadrada para 4 personas (area privilegiada)
    glPushMatrix();  
    glTranslatef(4.0f, -0.3f + ALTURA_SEGUNDO_PISO, 0.2f);  
    
    // Mesa VIP cuadrada grande
    drawMesaIndividual(0.0f, 0.0f, 0.0f, 1.6f, 1.6f, COLOR_MADERA);

    // 4 sillas VIP (color azul para diferenciacion)
    drawSilla(-1.0f, -0.2f, 0.0f, COLOR_AZUL, COLOR_MADERA, 90.0f);   // Izquierda
    drawSilla(1.0f, -0.2f, 0.0f, COLOR_AZUL, COLOR_MADERA, 270.0f);   // Derecha
    drawSilla(0.0f, -0.2f, -1.0f, COLOR_AZUL, COLOR_MADERA, 0.0f);    // Frente
    drawSilla(0.0f, -0.2f, 1.0f, COLOR_AZUL, COLOR_MADERA, 180.0f);   // Atras

    glPopMatrix();  
}

void drawSegundoPisoMesonCentral() {
    // CONVERTIDO A: Area de espera cerca de escaleras (2 bancos largos)
    // Posicionado estrategicamente para no bloquear circulacion
    
    // Banco largo 1 (paralelo a escaleras)
    glPushMatrix();  
    glTranslatef(6.0f, -0.3f + ALTURA_SEGUNDO_PISO, -1.0f);  
    
    // Base del banco
    glPushMatrix();  
    glTranslatef(0.0f, 0.0f, 0.0f);  
    drawCube(0.6f, 0.8f, 2.5f, COLOR_MADERA_OSCURA);  
    glPopMatrix();

    // Superficie del banco
    glPushMatrix();  
    glTranslatef(0.0f, 0.45f, 0.0f);  
    drawCube(0.8f, 0.1f, 2.7f, COLOR_MARRON);  
    glPopMatrix();

    // Respaldo del banco
    glPushMatrix();  
    glTranslatef(-0.35f, 0.8f, 0.0f);  
    drawCube(0.1f, 0.7f, 2.5f, COLOR_MADERA);  
    glPopMatrix();

    glPopMatrix();

    // Banco largo 2 (perpendicular al primero)
    glPushMatrix();  
    glTranslatef(4.5f, -0.3f + ALTURA_SEGUNDO_PISO, -2.0f);  
    
    // Base del banco
    glPushMatrix();  
    glTranslatef(0.0f, 0.0f, 0.0f);  
    drawCube(2.0f, 0.8f, 0.6f, COLOR_MADERA_OSCURA);  
    glPopMatrix();

    // Superficie del banco
    glPushMatrix();  
    glTranslatef(0.0f, 0.45f, 0.0f);  
    drawCube(2.2f, 0.1f, 0.8f, COLOR_MARRON);  
    glPopMatrix();

    // Respaldo del banco
    glPushMatrix();  
    glTranslatef(0.0f, 0.8f, -0.35f);  
    drawCube(2.0f, 0.7f, 0.1f, COLOR_MADERA);  
    glPopMatrix();

    glPopMatrix();
}

void drawEscaleras() {
    // Escaleras para conectar primer y segundo piso
    // Ubicadas en el lateral derecho del area de cocina
    
    const int NUM_ESCALONES = 16;  // 16 escalones para subir 3.2m (20cm cada escalon)
    const float ALTURA_ESCALON = ALTURA_SEGUNDO_PISO / NUM_ESCALONES;
    const float PROFUNDIDAD_ESCALON = 0.25f;
    const float ANCHO_ESCALON = 1.0f;
    
    for(int i = 0; i < NUM_ESCALONES; i++) {
        glPushMatrix();
        
        // Posicion de cada escalon
        float posX = 7.4f;  // Al lado de la pared derecha
        float posY = -0.6f + (i * ALTURA_ESCALON);
        float posZ = -3.0f + (i * PROFUNDIDAD_ESCALON);
        
        glTranslatef(posX, posY, posZ);
        drawCube(ANCHO_ESCALON, 0.1f, PROFUNDIDAD_ESCALON, COLOR_MADERA_OSCURA);
        
        glPopMatrix();
    }
    
    // Barandilla de las escaleras
    // Lado izquierdo de las escaleras
    glPushMatrix();
    glTranslatef(6.9f, ALTURA_SEGUNDO_PISO * 0.5f, -3.0f + (NUM_ESCALONES * PROFUNDIDAD_ESCALON * 0.5f));
    drawCube(0.05f, 4.5f, NUM_ESCALONES * PROFUNDIDAD_ESCALON, COLOR_METAL);
    glPopMatrix();
}

// Funcion principal para dibujar el segundo piso completo (BAR Y COMEDOR)
void drawSecondFloorKitchen() {
    // === ESTRUCTURA ARQUITECTONICA ===
    drawSegundoPisoParedes();   // Paredes blancas
    drawSegundoPisoPiso();      // Piso gris original
    drawEscaleras();            // Escaleras en posicion original
    
    // === ZONA DEL BAR ===
    drawSegundoPisoFregadero();         // Barra principal orientada a escaleras
    drawSegundoPisoGabinetesSuperiores(); // Estanteria para botellas
    drawSegundoPisoEncimera();          // Taburetes del bar (6 unidades)
    drawSegundoPisoRefrigerador();      // Maquina de cafe/expendedora
    
    // === ZONA DE COMENSALES ===
    drawVIPSquareTable();            // Mesa VIP p xddd
    drawMesasComensalesSecundoPiso();   // Distribucion principal de mesas
    
    // === AREA DE ESPERA ===
    drawSegundoPisoMesonCentral();      // Bancos largos cerca de escaleras
}

void drawMesasComensalesSecundoPiso() {
    // ZONA PRINCIPAL DE COMENSALES
    // Distribucion estrategica con pasillos de servicio de 0.8m minimo
    
    // === ZONA ESTANDAR - MESAS PARA 4 PERSONAS ===
    // Fila 1 - Area central izquierda
    for(int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-2.0f + i * 3.0f, -0.3f + ALTURA_SEGUNDO_PISO, -0.8f);
        drawMesaIndividual(0.0f, 0.0f, 0.0f, 1.4f, 1.4f, COLOR_MADERA);
        
        // 4 sillas por mesa (color rojo estandar)
        drawSilla(-0.9f, -0.2f, 0.0f, COLOR_ROJO, COLOR_MADERA, 90.0f);
        drawSilla(0.9f, -0.2f, 0.0f, COLOR_ROJO, COLOR_MADERA, 270.0f);
        drawSilla(0.0f, -0.2f, -0.9f, COLOR_ROJO, COLOR_MADERA, 0.0f);
        drawSilla(0.0f, -0.2f, 0.9f, COLOR_ROJO, COLOR_MADERA, 180.0f);
        glPopMatrix();
    }
    
    // Fila 2 - Area posterior central
    for(int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-1.0f + i * 3.0f, -0.3f + ALTURA_SEGUNDO_PISO, 1.8f);
        drawMesaIndividual(0.0f, 0.0f, 0.0f, 1.4f, 1.4f, COLOR_MADERA);
        
        // 4 sillas por mesa
        drawSilla(-0.9f, -0.2f, 0.0f, COLOR_ROJO, COLOR_MADERA, 90.0f);
        drawSilla(0.9f, -0.2f, 0.0f, COLOR_ROJO, COLOR_MADERA, 270.0f);
        drawSilla(0.0f, -0.2f, -0.9f, COLOR_ROJO, COLOR_MADERA, 0.0f);
        drawSilla(0.0f, -0.2f, 0.9f, COLOR_ROJO, COLOR_MADERA, 180.0f);
        glPopMatrix();
    }
    
    // === ZONA DE PAREJAS - MESAS PARA 2 PERSONAS ===
    // Area lateral derecha
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(5.9f, -0.3f + ALTURA_SEGUNDO_PISO, 1.6f + i * 2.0f);
        drawMesaIndividual(0.0f, 0.0f, 0.0f, 1.2f, 0.8f, COLOR_MADERA);
        
        // 2 sillas enfrentadas (color verde para diferenciacion)
        drawSilla(0.0f, -0.2f, -0.7f, COLOR_VERDE, COLOR_MADERA, 0.0f);
        drawSilla(0.0f, -0.2f, 0.7f, COLOR_VERDE, COLOR_MADERA, 180.0f);
        glPopMatrix();
    }
    
    // === MESA COMUNAL GRANDE - GRUPOS/EVENTOS ===
    // Area frontal amplia para grupos grandes
    glPushMatrix();
    glTranslatef(1.5f, -0.3f + ALTURA_SEGUNDO_PISO, 4.9f);
    drawMesaIndividual(0.0f, 0.0f, 0.0f, 3.0f, 1.4f, COLOR_MADERA);
    
    // 8 sillas alrededor de mesa comunal (color azul p)
    // Lados largos
    drawSilla(-1.2f, -0.2f, -1.1f, COLOR_AZUL, COLOR_MADERA, 0.0f);
    drawSilla(0.0f, -0.2f, -1.1f, COLOR_AZUL, COLOR_MADERA, 0.0f);
    drawSilla(1.2f, -0.2f, -1.1f, COLOR_AZUL, COLOR_MADERA, 0.0f);
    
    drawSilla(-1.2f, -0.2f, 1.1f, COLOR_AZUL, COLOR_MADERA, 180.0f);
    drawSilla(0.0f, -0.2f, 1.1f, COLOR_AZUL, COLOR_MADERA, 180.0f);
    drawSilla(1.2f, -0.2f, 1.1f, COLOR_AZUL, COLOR_MADERA, 180.0f);
    
    // Extremos
    drawSilla(-1.8f, -0.2f, 0.0f, COLOR_AZUL, COLOR_MADERA, 90.0f);
    drawSilla(1.8f, -0.2f, 0.0f, COLOR_AZUL, COLOR_MADERA, 270.0f);
    glPopMatrix();
}