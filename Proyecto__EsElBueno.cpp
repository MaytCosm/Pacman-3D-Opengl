#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 20

float posicionPacmanX = 1.0;
float posicionPacmanY = 1.0;
int direccionPacman = 0;  // 0 = arriba, 1 = derecha, 2 = abajo, 3 = izquierda

float fantasmaX1 = 1.0;
float fantasmaY1 = 6.0;
float fantasmaX2 = 15.0;
float fantasmaY2 = 3.0;
float fantasmaX3 = 9.0;
float fantasmaY3 = 18.0;

int direccionFantasma1 = 3;
int direccionFantasma2 = 0;
int direccionFantasma3 = 2;

float camaraX = SIZE;
float camaraY = SIZE;
int vistaIsometrica = 0;

int indiceEsquina = 0;

int creditos = 0;
int vidas = 3;


int superPastillaActiva = 0;
int tiempoSuperPastilla = 0;
int fantasmaDesaparecido1 = 0, fantasmaDesaparecido2 = 0, fantasmaDesaparecido3 = 0;
int tiempoDesaparecido1 = 0, tiempoDesaparecido2 = 0, tiempoDesaparecido3 = 0;

int laberinto[SIZE][SIZE] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
	{1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
	{1, 2, 1, 2, 2, 2, 2, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
	{1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1},
	{1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
	{1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 1},
	{1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1},
	{0, 2, 1, 1, 1, 2, 1, 3, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 0},
	{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 0},
	{1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1},
	{1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1},
	{1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 1},
	{1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
	{1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
	{1, 2, 1, 2, 3, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1},
	{1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 3, 1, 2, 1},
	{1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
	{1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void dibujarPacman() {
	glPushMatrix();
	glTranslatef(posicionPacmanX, posicionPacmanY, 0.0);
	glRotatef(direccionPacman * 90, 0.0, 0.0, 1.0);
	
	// Establece las propiedades del material
	GLfloat mat_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glutSolidSphere(0.5, 50, 50);  // Cuerpo de Pac-Man
	
	// Ojos de Pac-Man
	GLfloat mat_ambient_eye[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse_eye[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular_eye[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_eye);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_eye);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_eye);
	
	glPushMatrix();
	glTranslatef(0.2, 0.2, 0.5);
	glutSolidSphere(0.1, 10, 10);  // Ojo izquierdo
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.2, 0.2, 0.5);
	glutSolidSphere(0.1, 10, 10);  // Ojo derecho
	glPopMatrix();
	
	GLfloat mat_ambient_pupil[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse_pupil[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular_pupil[] = { 1.0, 1.0, 1.0, 1.0 }; 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_pupil);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_pupil);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_pupil);
	
	glPushMatrix();
	glTranslatef(0.2, 0.2, 0.6);
	glutSolidSphere(0.05, 10, 10);  // Pupila izquierda
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.2, 0.2, 0.6);
	glutSolidSphere(0.05, 10, 10);  // Pupila derecha
	glPopMatrix();
	
	glPopMatrix();
}

void manejarTeclado(unsigned char tecla, int x, int y) {
	int nuevaPosX, nuevaPosY;
	switch (tecla) {
	case 'w':
	case 'W':
		nuevaPosX = (int)(posicionPacmanX + 0.5);
		nuevaPosY = (int)(posicionPacmanY + 1.1);
		if (nuevaPosY >= SIZE) {  // Si Pac-Man ha cruzado el borde superior del mapa
			posicionPacmanY = 0;  // Mueve a Pac-Man al borde inferior
		} else if (laberinto[nuevaPosX][nuevaPosY] != 1) {
			if (laberinto[nuevaPosX][nuevaPosY] == 2) {
				creditos += 10;
			} else if (laberinto[nuevaPosX][nuevaPosY] == 3) {
				superPastillaActiva = 1;
				tiempoSuperPastilla = 0;
				creditos += 50;
			}
			direccionPacman = 0;
			posicionPacmanY += 0.1;
			laberinto[nuevaPosX][nuevaPosY] = 0;
		}
		break;
	case 's':
	case 'S':
		nuevaPosX = (int)(posicionPacmanX + 0.5);
		nuevaPosY = (int)(posicionPacmanY - 0.1);
		if (nuevaPosY < 0) {  // Si Pac-Man ha cruzado el borde inferior del mapa
			posicionPacmanY = SIZE - 1;  // Mueve a Pac-Man al borde superior
		} else if (laberinto[nuevaPosX][nuevaPosY] != 1) {
			if (laberinto[nuevaPosX][nuevaPosY] == 2) {
				creditos += 10;
			} else if (laberinto[nuevaPosX][nuevaPosY] == 3) {
				superPastillaActiva = 1;
				tiempoSuperPastilla = 0;
				creditos += 50;
			}
			direccionPacman = 2;
			posicionPacmanY -= 0.1;
			laberinto[nuevaPosX][nuevaPosY] = 0;
		}
		break;
	case 'a':
	case 'A':
		nuevaPosX = (int)(posicionPacmanX - 0.1);
		nuevaPosY = (int)(posicionPacmanY + 0.5);
		if (nuevaPosX < 0) {  // Si Pac-Man ha cruzado el borde izquierdo del mapa
			posicionPacmanX = SIZE - 1;  // Mueve a Pac-Man al borde derecho
		} else if (laberinto[nuevaPosX][nuevaPosY] != 1) {
			if (laberinto[nuevaPosX][nuevaPosY] == 2) {
				creditos += 10;
			} else if (laberinto[nuevaPosX][nuevaPosY] == 3) {
				superPastillaActiva = 1;
				tiempoSuperPastilla = 0;
				creditos += 50;
			}
			direccionPacman = 1;
			posicionPacmanX -= 0.1;
			laberinto[nuevaPosX][nuevaPosY] = 0;
		}
		break;
	case 'd':
	case 'D':
		nuevaPosX = (int)(posicionPacmanX + 1.1);
		nuevaPosY = (int)(posicionPacmanY + 0.5);
		if (nuevaPosX >= SIZE) {  // Si Pac-Man ha cruzado el borde derecho del mapa
			posicionPacmanX = 0;  // Mueve a Pac-Man al borde izquierdo
		} else if (laberinto[nuevaPosX][nuevaPosY] != 1) {
			if (laberinto[nuevaPosX][nuevaPosY] == 2) {
				creditos += 10;
			} else if (laberinto[nuevaPosX][nuevaPosY] == 3) {
				superPastillaActiva = 1;
				tiempoSuperPastilla = 0;
				creditos += 50;
			}
			direccionPacman = 3;
			posicionPacmanX += 0.1;
			laberinto[nuevaPosX][nuevaPosY] = 0;
		}
		break;
	case 'i':
	case 'I':
		vistaIsometrica = !vistaIsometrica;  // Cambia el estado de la vista isométrica
		break;
	}
	glutPostRedisplay();
}



void dibujarPared() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			glPushMatrix();
			glTranslatef(i, j, 0.0);
			if (laberinto[i][j] == 1) {
				GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
				GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
				GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };
				GLfloat mat_shininess[] = { 50.0 };
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
				glutSolidCube(1.0);
			} else if (laberinto[i][j] == 2) {
				GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
				GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
				GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
				GLfloat mat_shininess[] = { 50.0 };
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
				glutSolidSphere(0.1, 10, 10);
			} else if (laberinto[i][j] == 3){
				GLfloat mat_ambient[] = { 1.0, 0.0, 1.0, 1.0 };
				GLfloat mat_diffuse[] = { 1.0, 0.0, 1.0, 1.0 };
				GLfloat mat_specular[] = { 1.0, 0.0, 1.0, 1.0 };
				GLfloat mat_shininess[] = { 50.0 };
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
				glutSolidSphere(0.3, 50, 50);  // Superpastilla
			}
			glPopMatrix();
		}
	}
}

void dibujarFantasma(float x, float y, GLfloat r, GLfloat g, GLfloat b, int direccionFantasma, int fantasmaDesaparecido) {
	if (fantasmaDesaparecido1 == 0 ||  fantasmaDesaparecido2 == 0 || fantasmaDesaparecido3 == 0) {  // Solo dibuja el fantasma si no está desaparecido
		glPushMatrix();
		glTranslatef(x, y, 0.0);
		glRotatef(direccionFantasma * 90, 0.0, 0.0, 1.0);
		
		if (superPastillaActiva == 1) {
			r = 0.0;
			g = 0.0;
			b = 0.5;
		}
		
		GLfloat mat_ambient[] = { r, g, b, 1.0 };
		GLfloat mat_diffuse[] = { r, g, b, 1.0 };
		GLfloat mat_specular[] = { r, g, b, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		
		// Cuerpo del fantasma
		glPushMatrix();
		glScalef(1.0, 1.0, 2.5);
		glutSolidSphere(0.5, 50, 50);
		glPopMatrix();
		
		// Ojos del fantasma
		GLfloat mat_ambient_eye[] = { 1.0, 1.0, 1.0, 1.0 }; 
		GLfloat mat_diffuse_eye[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_specular_eye[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_eye);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_eye);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_eye);
		
		glPushMatrix();
		glTranslatef(0.2, 0.2, 0.9);
		glutSolidSphere(0.1, 10, 10);  // Ojo izquierdo
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-0.2, 0.2, 0.9);
		glutSolidSphere(0.1, 10, 10);  // Ojo derecho
		glPopMatrix();
		
		glPopMatrix();
	}
}

void moverFantasma(float* fantasmaX, float* fantasmaY, int* direccionFantasma) {
	int nuevaPosX, nuevaPosY;
	if (superPastillaActiva==1) {
		// Haz que los fantasmas huyan de Pac-Man
		switch (*direccionFantasma) {
		case 0:  // Arriba
			nuevaPosX = (int)(*fantasmaX + 0.5);
			nuevaPosY = (int)(*fantasmaY - 0.1);
			if (nuevaPosY >= 0 && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaY -= 0.2;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		case 1:  // Derecha
			nuevaPosX = (int)(*fantasmaX - 0.1);
			nuevaPosY = (int)(*fantasmaY + 0.5);
			if (nuevaPosX >= 0 && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaX -= 0.2;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		case 2:  // Abajo
			nuevaPosX = (int)(*fantasmaX + 0.5);
			nuevaPosY = (int)(*fantasmaY + 1.1);
			if (nuevaPosY < SIZE && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaY += 0.2;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		case 3:  // Izquierda
			nuevaPosX = (int)(*fantasmaX + 1.1);
			nuevaPosY = (int)(*fantasmaY + 0.5);
			if (nuevaPosX < SIZE && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaX += 0.2;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		}
	} else {
		// Haz que los fantasmas persigan a Pac-Man
		switch (*direccionFantasma) {
		case 0:  // Arriba
			nuevaPosX = (int)(*fantasmaX + 0.5);
			nuevaPosY = (int)(*fantasmaY + 1.1);
			if (nuevaPosY < SIZE && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaY += 0.1;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		case 1:  // Derecha
			nuevaPosX = (int)(*fantasmaX + 1.1);
			nuevaPosY = (int)(*fantasmaY + 0.5);
			if (nuevaPosX < SIZE && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaX += 0.1;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		case 2:  // Abajo
			nuevaPosX = (int)(*fantasmaX + 0.5);
			nuevaPosY = (int)(*fantasmaY - 0.1);
			if (nuevaPosY >= 0 && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaY -= 0.1;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		case 3:  // Izquierda
			nuevaPosX = (int)(*fantasmaX - 0.1);
			nuevaPosY = (int)(*fantasmaY + 0.5);
			if (nuevaPosX >= 0 && laberinto[nuevaPosX][nuevaPosY] != 1) {
				*fantasmaX -= 0.1;
			} else {
				*direccionFantasma = (rand() % 4);
			}
			break;
		}
	}
}

void actualizar(int value) {
	
	if (superPastillaActiva==1) {
		tiempoSuperPastilla++;
		if (tiempoSuperPastilla >= 100) {
			superPastillaActiva = 0;
		}
	}
	
	if (superPastillaActiva == 1) {
		// Si Pac-Man toca a un fantasma, haz que el fantasma desaparezca
		if ((int)posicionPacmanX == (int)fantasmaX1 && (int)posicionPacmanY == (int)fantasmaY1) {
			fantasmaDesaparecido1 = 1;
			tiempoDesaparecido1 = 0;
		}
		if ((int)posicionPacmanX == (int)fantasmaX2 && (int)posicionPacmanY == (int)fantasmaY2) {
			fantasmaDesaparecido2 = 1;
			tiempoDesaparecido2 = 0;
		}
		if ((int)posicionPacmanX == (int)fantasmaX3 && (int)posicionPacmanY == (int)fantasmaY3) {
			fantasmaDesaparecido3 = 1;
			tiempoDesaparecido3 = 0;
		}
	} else {
		// Si la superpastilla no está activa, verifica si Pac-Man ha chocado con un fantasma
		if ((int)posicionPacmanX == (int)fantasmaX1 && (int)posicionPacmanY == (int)fantasmaY1 ||
			(int)posicionPacmanX == (int)fantasmaX2 && (int)posicionPacmanY == (int)fantasmaY2 ||
			(int)posicionPacmanX == (int)fantasmaX3 && (int)posicionPacmanY == (int)fantasmaY3) {
			posicionPacmanX = 1.0;
			posicionPacmanY = 1.0;
			vidas--;
		}
	}
	
	if (fantasmaDesaparecido1) {
		tiempoDesaparecido1++;
		if (tiempoDesaparecido1 >= 50) {  
			fantasmaDesaparecido1 = 0;
			fantasmaX1 = 1.0;
			fantasmaY1 = 6.0;
		}
	}
	if (fantasmaDesaparecido2) {
		tiempoDesaparecido2++;
		if (tiempoDesaparecido2 >= 50) {
			fantasmaDesaparecido2 = 0;
			fantasmaX2 = 15.0;
			fantasmaY2 = 3.0;
		}
	}
	if (fantasmaDesaparecido3) {
		tiempoDesaparecido3++;
		if (tiempoDesaparecido3 >= 50) {
			fantasmaDesaparecido3 = 0;
			fantasmaX3 = 9.0;
			fantasmaY3 = 18.0;
		}
	}
	
	if (superPastillaActiva != 1) {
		if ((int)posicionPacmanX == (int)fantasmaX1 && (int)posicionPacmanY == (int)fantasmaY1 ||
			(int)posicionPacmanX == (int)fantasmaX2 && (int)posicionPacmanY == (int)fantasmaY2 ||
			(int)posicionPacmanX == (int)fantasmaX3 && (int)posicionPacmanY == (int)fantasmaY3) {
			posicionPacmanX = 1.0;
			posicionPacmanY = 1.0;
			vidas--;
		}
	}
	float distFantasma1 = sqrt(pow(posicionPacmanX - fantasmaX1, 2) + pow(posicionPacmanY - fantasmaY1, 2));
	float distFantasma2 = sqrt(pow(posicionPacmanX - fantasmaX2, 2) + pow(posicionPacmanY - fantasmaY2, 2));
	float distFantasma3 = sqrt(pow(posicionPacmanX - fantasmaX3, 2) + pow(posicionPacmanY - fantasmaY3, 2));
	
	// Si la distancia es menor o igual a 5, el fantasma comienza a perseguir a Pac-Man
	if (distFantasma1 <= 5) {
		if (posicionPacmanX > fantasmaX1 && laberinto[(int)(fantasmaX1 + 1.1)][(int)(fantasmaY1 + 0.5)] != 1) {
			fantasmaX1 += 0.1;
			direccionFantasma1 = 1;
		} else if (posicionPacmanX < fantasmaX1 && laberinto[(int)(fantasmaX1 - 0.1)][(int)(fantasmaY1 + 0.5)] != 1) {
			fantasmaX1 -= 0.1;
			direccionFantasma1 = 3;
		}
		if (posicionPacmanY > fantasmaY1 && laberinto[(int)(fantasmaX1 + 0.5)][(int)(fantasmaY1 + 1.1)] != 1) {
			fantasmaY1 += 0.1;
			direccionFantasma1 = 0;
		} else if (posicionPacmanY < fantasmaY1 && laberinto[(int)(fantasmaX1 + 0.5)][(int)(fantasmaY1 - 0.1)] != 1) {
			fantasmaY1 -= 0.1;
			direccionFantasma1 = 2;
		}
	} else {
		moverFantasma(&fantasmaX1, &fantasmaY1, &direccionFantasma1);
	}
	
	if (distFantasma2 <= 5) {
		if (posicionPacmanX > fantasmaX2 && laberinto[(int)(fantasmaX2 + 1.1)][(int)(fantasmaY2 + 0.5)] != 1) {
			fantasmaX2 += 0.1;
			direccionFantasma2 = 1;
		} else if (posicionPacmanX < fantasmaX2 && laberinto[(int)(fantasmaX2 - 0.1)][(int)(fantasmaY2 + 0.5)] != 1) {
			fantasmaX2 -= 0.1;
			direccionFantasma2 = 3;
		}
		if (posicionPacmanY > fantasmaY2 && laberinto[(int)(fantasmaX2 + 0.5)][(int)(fantasmaY2 + 1.1)] != 1) {
			fantasmaY2 += 0.1;
			direccionFantasma2 = 0;
		} else if (posicionPacmanY < fantasmaY2 && laberinto[(int)(fantasmaX2 + 0.5)][(int)(fantasmaY2 - 0.1)] != 1) {
			fantasmaY2 -= 0.1;
			direccionFantasma2 = 2;
		}
	} else {
		moverFantasma(&fantasmaX2, &fantasmaY2, &direccionFantasma2);
	}
	
	if (distFantasma3 <= 5) {
		if (posicionPacmanX > fantasmaX3 && laberinto[(int)(fantasmaX3 + 1.1)][(int)(fantasmaY3 + 0.5)] != 1) {
			fantasmaX3 += 0.1;
			direccionFantasma3 = 1;
		} else if (posicionPacmanX < fantasmaX3 && laberinto[(int)(fantasmaX3 - 0.1)][(int)(fantasmaY3 + 0.5)] != 1) {
			fantasmaX3 -= 0.1;
			direccionFantasma3 = 3;
		}
		if (posicionPacmanY > fantasmaY3 && laberinto[(int)(fantasmaX3 + 0.5)][(int)(fantasmaY3 + 1.1)] != 1) {
			fantasmaY3 += 0.1;
			direccionFantasma3 = 0;
		} else if (posicionPacmanY < fantasmaY3 && laberinto[(int)(fantasmaX3 + 0.5)][(int)(fantasmaY3 - 0.1)] != 1) {
			fantasmaY3 -= 0.1;
			direccionFantasma3 = 2;
		}
	} else {
		moverFantasma(&fantasmaX3, &fantasmaY3, &direccionFantasma3);
	}
	
	if (vidas == 0) {
		posicionPacmanX = 1.0;
		posicionPacmanY = 1.0;
		fantasmaX1 = 1.0;
		fantasmaY1 = 6.0;
		fantasmaX2 = 15.0;
		fantasmaY2 = 3.0;
		fantasmaX3 = 9.0;
		fantasmaY3 = 18.0;
		
		creditos = 0;
		vidas = 3;
		
		int laberintoInicial[SIZE][SIZE] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
			{1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
		{1, 2, 1, 2, 2, 2, 2, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
			{1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1},
		{1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
			{1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 1},
		{1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1},
			{0, 2, 1, 1, 1, 2, 1, 3, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 0},
		{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 0},
			{1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1},
		{1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1},
			{1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 1},
		{1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
			{1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
		{1, 2, 1, 2, 3, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1},
			{1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 3, 1, 2, 1},
		{1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
			{1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				laberinto[i][j] = laberintoInicial[i][j];
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(150, actualizar, 0);
}

void manejarTeclasEspeciales(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_LEFT:
		indiceEsquina = (indiceEsquina + 3) % 4;
		break;
	case GLUT_KEY_RIGHT:
		indiceEsquina = (indiceEsquina + 1) % 4;
		break;
	}
	
	switch (indiceEsquina) {
	case 0:
		camaraX = SIZE;
		camaraY = SIZE;
		break;
	case 1:
		camaraX = 0;
		camaraY = SIZE;
		break;
	case 2:
		camaraX = 0;
		camaraY = 0;
		break;
	case 3:
		camaraX = SIZE;
		camaraY = 0;
		break;
	}
	glutPostRedisplay();
}

void renderTexto(float x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*	configurarIluminacion();*/
	
	// Configura la luz
	GLfloat light_position[] = { SIZE / 2.0f, SIZE / 2.0f, SIZE * 2.0f, 0.0f };
	GLfloat luzBlanca[] = { 1.0f, 1.0f, 1.0f, 1.0f };    
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzBlanca);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,1.0f,1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Si la vista isométrica está activada, cambia la cámara
	if (vistaIsometrica == 1) {
		gluLookAt(posicionPacmanX + 7, posicionPacmanY - SIZE + 5, SIZE * 1.0f, posicionPacmanX, posicionPacmanY, 0.0f, 0.0f, 0.0f, 1.0f);
	} else {
		gluLookAt(camaraX, camaraY, SIZE * 2.0f, SIZE / 2.0f, SIZE / 2.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		
	}
	
	dibujarPared();
	dibujarPacman();
	dibujarFantasma(fantasmaX1, fantasmaY1, 1.0, 0.0, 0.0, direccionFantasma1, fantasmaDesaparecido1);
	dibujarFantasma(fantasmaX2, fantasmaY2, 0.0, 1.0, 0.0, direccionFantasma2, fantasmaDesaparecido2);
	dibujarFantasma(fantasmaX3, fantasmaY3, 0.0, 1.0, 1.0, direccionFantasma3, fantasmaDesaparecido3);
	
	// Mostrar créditos
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);  // Deshabilita la iluminación para el texto
	char creditosStr[50];
	sprintf(creditosStr, "Creditos: %d", creditos);
	renderTexto(10, 580, GLUT_BITMAP_9_BY_15, creditosStr);
	glEnable(GL_LIGHTING);  // Habilita la iluminación nuevamente
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	// Mostrar vidas
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);  // Deshabilita la iluminación para el texto
	char vidasStr[50];
	sprintf(vidasStr, "Vidas x%d", vidas);
	renderTexto(700, 580, GLUT_BITMAP_9_BY_15, vidasStr);
	glEnable(GL_LIGHTING);  // Habilita la iluminación nuevamente
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Pacman 3D");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glutDisplayFunc(display);
	glutTimerFunc(150, actualizar, 0); 
	glutKeyboardFunc(manejarTeclado);
	glutSpecialFunc(manejarTeclasEspeciales);
	glutMainLoop();
	return 0;
}
