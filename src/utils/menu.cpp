#include "utils/menu.h"
#include "utils/camera.h"
#include "utils/lighting.h"
#include <GL/freeglut.h>
#include <windows.h>
#include "mmsystem.h"

// Variables globales del menu
int iFondo = 0;
int iEstiloVisualizacion = 0; // 0=solido, 1=alambre
int iSeccionVisible = 2; // 0=primer piso, 1=segundo piso, 2=todo
bool bAnimacionActiva = false;
float fTiempoAnimacion = 0.0f;

// **ANIMACION SIMPLE**
void actualizarAnimacion() {
    if (bAnimacionActiva) {
        fTiempoAnimacion += 0.05f;
        if (fTiempoAnimacion > 360.0f) {
            fTiempoAnimacion = 0.0f;
        }
    }
}

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
        case FONDO4:
            iFondo = 3; // Color de fondo 4 (celeste cielo)
            break;
        case VIS_SOLIDO:
            iEstiloVisualizacion = 0; // Visualizacion solida
            break;
        case VIS_ALAMBRE:
            iEstiloVisualizacion = 1; // Visualizacion en alambre
            break;
        case SONIDO_ON:
            PlaySound(TEXT("assets/Revolution-909.wav"), NULL, SND_LOOP | SND_ASYNC);
            break;
        case SONIDO_OFF:
            PlaySound(NULL, 0, 0); // Detiene el sonido
            break;
        case LUZ_DIA:
            iTipoLuz = 0;
            break;
        case LUZ_NOCHE:
            iTipoLuz = 1;
            break;
        case LUZ_AMBIENTE:
            iTipoLuz = 2;
            break;
        case MOSTRAR_PRIMER_PISO:
            iSeccionVisible = 0;
            break;
        case MOSTRAR_SEGUNDO_PISO:
            iSeccionVisible = 1;
            break;
        case MOSTRAR_TODO:
            iSeccionVisible = 2;
            break;
        case CAMARA_LIBRE:
            // Activar modo FPS (camara libre)
            bCamaraFPS = true;
            // Posicionar camara en una buena ubicacion inicial
            fpsX = 0.0f;
            fpsY = 2.0f;
            fpsZ = 5.0f;
            fpsPitch = 0.0f;
            fpsYaw = 0.0f;
            break;
        case CAMARA_COCINA:
            bCamaraFPS = false;  // Desactivar FPS para usar camara orbital
            iTipoCamara = 1;
            configurarCamara();
            break;
        case CAMARA_COMEDOR:
            bCamaraFPS = false;  // Desactivar FPS para usar camara orbital
            iTipoCamara = 2;
            configurarCamara();
            break;
        case CAMARA_ALMACEN:
            bCamaraFPS = false;  // Desactivar FPS para usar camara orbital
            iTipoCamara = 3;
            configurarCamara();
            break;
        case RESET_VISTA:
            if (bCamaraFPS) {
                // Reset FPS
                fpsX = 0.0f;
                fpsY = 2.0f;
                fpsZ = 5.0f;
                fpsPitch = 0.0f;
                fpsYaw = 0.0f;
            } else {
                // Reset orbital
                camAngleX = 20.0f;
                camAngleY = 45.0f;
                camDistance = 15.0f;
                iTipoCamara = 0;
            }
            break;
        case ANIMACION_ON:
            bAnimacionActiva = true;
            break;
        case ANIMACION_OFF:
            bAnimacionActiva = false;
            fTiempoAnimacion = 0.0f;
            break;
    }
    glutPostRedisplay();
}

void creacionMenu(void) {
    int menuFondo, menuVisualizacion, menuSonido, menuIluminacion;
    int menuSecciones, menuCamara, menuControl, menuPrincipal;
    
    // Menu para color de fondo
    menuFondo = glutCreateMenu(onMenu);
    glutAddMenuEntry("Gris claro", FONDO1);
    glutAddMenuEntry("Blanco", FONDO2);
    glutAddMenuEntry("Beige", FONDO3);
    glutAddMenuEntry("Celeste cielo", FONDO4);
    
    // Menu para estilo de visualizacion
    menuVisualizacion = glutCreateMenu(onMenu);
    glutAddMenuEntry("Solido", VIS_SOLIDO);
    glutAddMenuEntry("Alambre", VIS_ALAMBRE);
    
    // Menu para sonido ambiente
    menuSonido = glutCreateMenu(onMenu);
    glutAddMenuEntry("Sonido ON", SONIDO_ON);
    glutAddMenuEntry("Sonido OFF", SONIDO_OFF);
    
    // Menu para iluminacion
    menuIluminacion = glutCreateMenu(onMenu);
    glutAddMenuEntry("Luz de dia", LUZ_DIA);
    glutAddMenuEntry("Luz de noche", LUZ_NOCHE);
    glutAddMenuEntry("Luz ambiente", LUZ_AMBIENTE);
    
    // Menu para mostrar secciones
    menuSecciones = glutCreateMenu(onMenu);
    glutAddMenuEntry("Primer piso", MOSTRAR_PRIMER_PISO);
    glutAddMenuEntry("Segundo piso", MOSTRAR_SEGUNDO_PISO);
    glutAddMenuEntry("Mostrar todo", MOSTRAR_TODO);
    
    // Menu para vistas de camara
    menuCamara = glutCreateMenu(onMenu);
    glutAddMenuEntry("Camara libre", CAMARA_LIBRE);
    glutAddMenuEntry("Vista cocina", CAMARA_COCINA);
    glutAddMenuEntry("Vista comedor", CAMARA_COMEDOR);
    glutAddMenuEntry("Vista almacen", CAMARA_ALMACEN);
    
    // Menu para controles generales
    menuControl = glutCreateMenu(onMenu);
    glutAddMenuEntry("Resetear vista", RESET_VISTA);
    glutAddMenuEntry("Animacion ON", ANIMACION_ON);
    glutAddMenuEntry("Animacion OFF", ANIMACION_OFF);
    
    // Menu principal que agrupa los submenus
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Color de fondo", menuFondo);
    glutAddSubMenu("Visualizacion", menuVisualizacion);
    glutAddSubMenu("Sonido", menuSonido);
    glutAddSubMenu("Iluminacion", menuIluminacion);
    glutAddSubMenu("Mostrar secciones", menuSecciones);
    glutAddSubMenu("Vistas de camara", menuCamara);
    glutAddSubMenu("Controles", menuControl);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON); // menu con clic derecho
}
