#include "objects/dining.h"

// =============================================  
// **COMEDOR DE RESTAURANTE**  
// =============================================  
void drawComedorRestaurante() {
    // **MESAS PARA 2 PERSONAS (rectangulares pequeñas)**
    // Fila 1 - Mesas para 2
    for(int i = 0; i < 5; i++) {
        float posX = -1.8f + i * 2.0f;
        float posZ = 2.0f;
        
        // Mesa rectangular pequeña
        drawMesaIndividual(posX, -0.3f, posZ, 1.2f, 0.8f, COLOR_MADERA);
        
        // 2 sillas por mesa cara a cara
        drawSilla(posX, -0.5f, posZ - 0.8f, COLOR_AZUL, COLOR_MADERA, 0.0f);   // Silla frontal (normal)
        drawSilla(posX, -0.5f, posZ + 0.8f, COLOR_AZUL, COLOR_MADERA, 180.0f); // Silla trasera (volteada)
    }
    
    // **MESAS PARA 4 PERSONAS (cuadradas)**
    // Fila 2 - Mesas para 4
    for(int i = 0; i < 4; i++) {
        float posX = -1.5f + i * 2.5f;
        float posZ = 5.0f;
        
        // Mesa cuadrada
        drawMesaIndividual(posX, -0.3f, posZ, 1.4f, 1.4f, COLOR_MADERA);
        
        // 4 sillas alrededor de la mesa cara a cara
        drawSilla(posX - 0.9f, -0.5f, posZ, COLOR_ROJO, COLOR_MADERA, 90.0f);   // Izquierda (mirando hacia la mesa)
        drawSilla(posX + 0.9f, -0.5f, posZ, COLOR_ROJO, COLOR_MADERA, 270.0f);  // Derecha (mirando hacia la mesa)
        drawSilla(posX, -0.5f, posZ - 0.9f, COLOR_ROJO, COLOR_MADERA, 0.0f);    // Frente (normal)
        drawSilla(posX, -0.5f, posZ + 0.9f, COLOR_ROJO, COLOR_MADERA, 180.0f);  // Atras (volteada)
    }
}

// Alias para compatibilidad
void drawDining() {
    drawComedorRestaurante();
}
