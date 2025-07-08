#ifndef CAMERA_H
#define CAMERA_H

// Variables globales de camara orbital (camara original)
extern float camAngleX;
extern float camAngleY;
extern float camDistance;
extern int mouseX, mouseY;
extern bool mouseLeftDown;
extern int iTipoCamara;

// Variables para camara FPS (primera persona) - AHORA GLOBALES
extern float fpsX, fpsY, fpsZ;          // Posicion de la camara FPS
extern float fpsPitch, fpsYaw;          // Angulos de rotacion (pitch = arriba/abajo, yaw = izquierda/derecha)
extern bool bCamaraFPS;                 // Modo de camara activa (false = orbital, true = FPS)
extern bool mouseRightDown;             // Estado del boton derecho del mouse
extern bool keys[256];                  // Estados de las teclas para movimiento WASD

// Funciones de control de camara
void configurarCamara();
void cameraOnMouse(int button, int state, int x, int y);
void cameraOnMotion(int x, int y);
void cameraOnKeyboard(unsigned char key, int x, int y);
void cameraOnKeyboardUp(unsigned char key, int x, int y);
void updateFPSCamera();
void applyCamera();

#endif