#ifndef MENU_H
#define MENU_H

// Variables globales del menu
extern int iFondo;
extern int iEstiloVisualizacion;
extern int iSeccionVisible;
extern bool bAnimacionActiva;
extern float fTiempoAnimacion;

// Enumeracion de opciones del menu
typedef enum {
    FONDO1, FONDO2, FONDO3,
    VIS_SOLIDO, VIS_ALAMBRE,
    SONIDO_ON, SONIDO_OFF,
    LUZ_DIA, LUZ_NOCHE, LUZ_AMBIENTE,
    MOSTRAR_COCINA, MOSTRAR_COMEDOR, MOSTRAR_ALMACEN, MOSTRAR_TODO,
    CAMARA_LIBRE, CAMARA_COCINA, CAMARA_COMEDOR, CAMARA_ALMACEN,
    RESET_VISTA, ANIMACION_ON, ANIMACION_OFF
} opcionesMenu;

// Funciones del menu
void onMenu(int opcion);
void creacionMenu(void);
void actualizarAnimacion();

#endif
