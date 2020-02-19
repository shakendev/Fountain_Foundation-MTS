/*
*      DTFT ver. 0.5.7
*      Dmitry Novikov
*      All Rights Reserved. //DDEC®. 20!8
*/
//Подключение библиотек
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;


//Определение неизменямых зарезервированных слов
#define windowWidth        1100
#define windowHeight        600

const string fileName = "TEXTFILES/test.txt";
const unsigned int N = 100000;
float matrixValues[N][2];
unsigned int countValuesInFile = 1;
float maxValue = 0, minValue = 0, middlePlusAmplitude = 0, middleMinusAmplitude = 0;

unsigned int currentPosition = 0;





inline static void renderingLines() {
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glVertex2f(-(windowWidth / 2), 1);
    glVertex2f((windowWidth / 2), 1);
    glVertex2f((windowWidth / 2), -1);
    glVertex2f(-(windowWidth / 2), -1);
    glEnd();
}




inline static void renderingAmplitudeRectangle(float x, float y) {
    glRectf(x, y, (x + 40), (y + 25));
}




inline static void renderingScene() {
    //Амплитуда(+)
    // -13/13 гармоники
    if (matrixValues[currentPosition][1] <= (middlePlusAmplitude * 8)) {
        glColor4ub(0, 255, 0, 255);
        renderingAmplitudeRectangle(-546, 2);
        renderingAmplitudeRectangle(506, 2);
    }
    if (matrixValues[currentPosition][1] <= (middlePlusAmplitude * 7)) {
        glColor4ub(0, 255, 0, 255);
        renderingAmplitudeRectangle(-546, 29);
        renderingAmplitudeRectangle(506, 29);
    }
    if (matrixValues[currentPosition][1] <= (middlePlusAmplitude * 6)) {
        glColor4ub(0, 255, 0, 255);
        renderingAmplitudeRectangle(-546, 56);
        renderingAmplitudeRectangle(506, 56);
    }
    if (matrixValues[currentPosition][1] <= (middlePlusAmplitude * 5)) {
        glColor4ub(0, 255, 0, 255);
        renderingAmplitudeRectangle(-546, 83);
        renderingAmplitudeRectangle(506, 83);
    }
    if (matrixValues[currentPosition][1] <= (middlePlusAmplitude * 4)) {
        glColor4ub(255, 83, 0, 255);
        renderingAmplitudeRectangle(-546, 110);
        renderingAmplitudeRectangle(506, 110);
    }
    if (matrixValues[currentPosition][1] <= (middlePlusAmplitude * 3)) {
        glColor4ub(255, 83, 0, 255);
        renderingAmplitudeRectangle(-546, 137);
        renderingAmplitudeRectangle(506, 137);
    }
    if (matrixValues[currentPosition][1] <= (middlePlusAmplitude * 2)) {
        glColor4ub(255, 0, 0, 255);
        renderingAmplitudeRectangle(-546, 164);
        renderingAmplitudeRectangle(506, 164);
    }
    if (matrixValues[currentPosition][1] <= middlePlusAmplitude) {
        glColor4ub(255, 0, 0, 255);
        renderingAmplitudeRectangle(-546, 191);
        renderingAmplitudeRectangle(506, 191);
    }
    // -12/12 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-504, 2);
    renderingAmplitudeRectangle(464, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-504, 29);
    renderingAmplitudeRectangle(464, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-504, 56);
    renderingAmplitudeRectangle(464, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-504, 83);
    renderingAmplitudeRectangle(464, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-504, 110);
    renderingAmplitudeRectangle(464, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-504, 137);
    renderingAmplitudeRectangle(464, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-504, 164);
    renderingAmplitudeRectangle(464, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-504, 191);
    renderingAmplitudeRectangle(464, 191);
    // -11/11 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-462, 2);
    renderingAmplitudeRectangle(422, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-462, 29);
    renderingAmplitudeRectangle(422, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-462, 56);
    renderingAmplitudeRectangle(422, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-462, 83);
    renderingAmplitudeRectangle(422, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-462, 110);
    renderingAmplitudeRectangle(422, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-462, 137);
    renderingAmplitudeRectangle(422, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-462, 164);
    renderingAmplitudeRectangle(422, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-462, 191);
    renderingAmplitudeRectangle(422, 191);
    // -10/10 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-420, 2);
    renderingAmplitudeRectangle(380, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-420, 29);
    renderingAmplitudeRectangle(380, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-420, 56);
    renderingAmplitudeRectangle(380, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-420, 83);
    renderingAmplitudeRectangle(380, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-420, 110);
    renderingAmplitudeRectangle(380, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-420, 137);
    renderingAmplitudeRectangle(380, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-420, 164);
    renderingAmplitudeRectangle(380, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-420, 191);
    renderingAmplitudeRectangle(380, 191);
    // -9/9 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-378, 2);
    renderingAmplitudeRectangle(338, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-378, 29);
    renderingAmplitudeRectangle(338, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-378, 56);
    renderingAmplitudeRectangle(338, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-378, 83);
    renderingAmplitudeRectangle(338, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-378, 110);
    renderingAmplitudeRectangle(338, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-378, 137);
    renderingAmplitudeRectangle(338, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-378, 164);
    renderingAmplitudeRectangle(338, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-378, 191);
    renderingAmplitudeRectangle(338, 191);
    // -8/8 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-336, 2);
    renderingAmplitudeRectangle(296, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-336, 29);
    renderingAmplitudeRectangle(296, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-336, 56);
    renderingAmplitudeRectangle(296, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-336, 83);
    renderingAmplitudeRectangle(296, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-336, 110);
    renderingAmplitudeRectangle(296, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-336, 137);
    renderingAmplitudeRectangle(296, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-336, 164);
    renderingAmplitudeRectangle(296, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-336, 191);
    renderingAmplitudeRectangle(296, 191);
    // -7/7 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-294, 2);
    renderingAmplitudeRectangle(254, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-294, 29);
    renderingAmplitudeRectangle(254, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-294, 56);
    renderingAmplitudeRectangle(254, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-294, 83);
    renderingAmplitudeRectangle(254, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-294, 110);
    renderingAmplitudeRectangle(254, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-294, 137);
    renderingAmplitudeRectangle(254, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-294, 164);
    renderingAmplitudeRectangle(254, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-294, 191);
    renderingAmplitudeRectangle(254, 191);
    // -6/6 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-252, 2);
    renderingAmplitudeRectangle(212, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-252, 29);
    renderingAmplitudeRectangle(212, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-252, 56);
    renderingAmplitudeRectangle(212, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-252, 83);
    renderingAmplitudeRectangle(212, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-252, 110);
    renderingAmplitudeRectangle(212, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-252, 137);
    renderingAmplitudeRectangle(212, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-252, 164);
    renderingAmplitudeRectangle(212, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-252, 191);
    renderingAmplitudeRectangle(212, 191);
    // -5/5 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-210, 2);
    renderingAmplitudeRectangle(170, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-210, 29);
    renderingAmplitudeRectangle(170, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-210, 56);
    renderingAmplitudeRectangle(170, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-210, 83);
    renderingAmplitudeRectangle(170, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-210, 110);
    renderingAmplitudeRectangle(170, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-210, 137);
    renderingAmplitudeRectangle(170, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-210, 164);
    renderingAmplitudeRectangle(170, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-210, 191);
    renderingAmplitudeRectangle(170, 191);
    // -4/4 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-168, 2);
    renderingAmplitudeRectangle(128, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-168, 29);
    renderingAmplitudeRectangle(128, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-168, 56);
    renderingAmplitudeRectangle(128, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-168, 83);
    renderingAmplitudeRectangle(128, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-168, 110);
    renderingAmplitudeRectangle(128, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-168, 137);
    renderingAmplitudeRectangle(128, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-168, 164);
    renderingAmplitudeRectangle(128, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-168, 191);
    renderingAmplitudeRectangle(128, 191);
    // -3/3 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-126, 2);
    renderingAmplitudeRectangle(86, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-126, 29);
    renderingAmplitudeRectangle(86, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-126, 56);
    renderingAmplitudeRectangle(86, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-126, 83);
    renderingAmplitudeRectangle(86, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-126, 110);
    renderingAmplitudeRectangle(86, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-126, 137);
    renderingAmplitudeRectangle(86, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-126, 164);
    renderingAmplitudeRectangle(86, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-126, 191);
    renderingAmplitudeRectangle(86, 191);
    // -2/2 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-84, 2);
    renderingAmplitudeRectangle(44, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-84, 29);
    renderingAmplitudeRectangle(44, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-84, 56);
    renderingAmplitudeRectangle(44, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-84, 83);
    renderingAmplitudeRectangle(44, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-84, 110);
    renderingAmplitudeRectangle(44, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-84, 137);
    renderingAmplitudeRectangle(44, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-84, 164);
    renderingAmplitudeRectangle(44, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-84, 191);
    renderingAmplitudeRectangle(44, 191);
    // -1/1 гармоники
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-42, 2);
    renderingAmplitudeRectangle(2, 2);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-42, 29);
    renderingAmplitudeRectangle(2, 29);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-42, 56);
    renderingAmplitudeRectangle(2, 56);
    glColor4ub(0, 255, 0, 255);
    renderingAmplitudeRectangle(-42, 83);
    renderingAmplitudeRectangle(2, 83);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-42, 110);
    renderingAmplitudeRectangle(2, 110);
    glColor4ub(255, 83, 0, 255);
    renderingAmplitudeRectangle(-42, 137);
    renderingAmplitudeRectangle(2, 137);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-42, 164);
    renderingAmplitudeRectangle(2, 164);
    glColor4ub(255, 0, 0, 255);
    renderingAmplitudeRectangle(-42, 191);
    renderingAmplitudeRectangle(2, 191);
}




inline static void renderingMainScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    renderingLines();
    renderingScene();
    
    glutSwapBuffers();
}




inline static void initializationMainVariables() {
    for (unsigned int i = 0; i < countValuesInFile; i++) {
        if (maxValue < matrixValues[i][1]) {
            maxValue = matrixValues[i][1];
        }
        if (minValue > matrixValues[i][1]) {
            minValue = matrixValues[i][1];
        }
    }
    middlePlusAmplitude = (maxValue / 8);
    middleMinusAmplitude = (minValue / 8);
}




//Инициализация главной сцены
inline static void initializationMainScene() {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-(windowWidth / 2), (windowWidth / 2), -(windowHeight / 2.5), (windowHeight / 1.5));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    initializationMainVariables();
    glutPostRedisplay();
}




inline static void readFile() {
    ifstream matrixFile;
    matrixFile.open(fileName);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            matrixFile >> matrixValues[i][j];
        }
        countValuesInFile++;
    }
    matrixFile.close();
}




inline static void animationScene() {
    if (currentPosition <= countValuesInFile) {
        currentPosition++;
        glutPostRedisplay();
    }
    usleep(50000);
}




//Основная функция
int main(int argc, char **argv) {
    readFile();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowWidth) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - windowHeight) / 2);
    glutCreateWindow("Визуализация разложения звуковой дорожки АС + СКО");
    initializationMainScene();
    glutDisplayFunc(renderingMainScene);
    glutIdleFunc(animationScene);
    glutMainLoop();
    return 0;
}
