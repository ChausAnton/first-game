#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Fruits.h"
#include "files.h"
#include "blok.h"
using namespace std;

//bool змінні відповідаюсть за те, що и коли показувати
bool choose = false;
bool print_score = false;
bool lose = false;
bool print_speed = false;

int speed = 100;
void drawString(string text, float x, float y, float z);


    void blok::draw_blok(float color1, float color2, float color3, float height) {
        glBegin(GL_QUADS);
        glColor3f(color1, color2, color3);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.00f, 0.0f, 0.0f);
        glVertex3f(1.0f, height, 0.0f);
        glVertex3f(0.0f, height, 0.0f);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(color1, color2, color3);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.0f, height, -1.0f);
        glVertex3f(0.0f, height, 0.0f);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(color1, color2, color3);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, height, -1.0f);
        glVertex3f(1.0f, height, 0.0f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(color1, color2, color3);
        glVertex3f(0.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, height, -1.0f);
        glVertex3f(0.0f, height, -1.0f);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(color1, color2, color3);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(0.0f, 0.0f, -1.0f);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(color1, color2, color3);
        glVertex3f(0.0f, 0.3f, 0.0f);
        glVertex3f(1.0f, 0.3f, 0.0f);
        glVertex3f(1.0f, 0.3f, -1.0f);
        glVertex3f(0.0f, 0.3f, -1.0f);
        glEnd();
        //  
    }

class field : public blok {
private:
    int rotate_x = 0;
    int rotate_z = 0;
    int height = -20;
    int width = 6;

public:

    field() { blok(); };

    void set_rotate_x(int rotate_x) { this->rotate_x = rotate_x; }

    void set_rotate_z(int rotate_z) { this->rotate_z = rotate_z; }

    int get_height() { return height; }

    int get_width() { return width; }

    void KeyboardEvent(int key, int x, int y) {
        switch (key) {
        case GLUT_KEY_RIGHT:
            rotate_z += 5;
            break;
        case GLUT_KEY_LEFT:
            rotate_z -= 5;
            break;
        case GLUT_KEY_UP:
            rotate_x -= 5;
            break;
        case GLUT_KEY_DOWN:
            rotate_x += 5;
            break;
        }

    }

    void handleResize(int w, int h)
    {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, (double)w / (double)h, 1.0, 200);
        gluLookAt(0.0f, 5.5f, 15.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f);
    }

    void drawScene() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef( 1.0, 0.0,  1.0);//для обертання
        glRotatef(rotate_x, 9.0, 0.0, 0.0);
        glRotatef(rotate_z, 0.0, 0.0, -10.0);
        glTranslatef(-10 * 1.0, 0.0, 6 * 1.0);//для побудови поля
        int k = 0;
        for (float j = 0.0; j > (height * 1.0); j -= 1.0) {
            k++;
            for (float i = 0.0; i < (width * 3.0); i += 2.0) {
                if (k % 2 == 0) {
                    glPushMatrix();
                    glTranslatef(i + 1, 0.0, j);
                    draw_blok(1.0f, 1.5f, 0.5f, 0.3f);
                    //drow_area(1.0f, 1.5f, 0.5f);
                    glPopMatrix();

                }
                else {
                    glPushMatrix();
                    glTranslatef(i + 1, 0.0, j);
                    draw_blok(0.0f, 0.5f, 0.5f, 0.3f);
                    //drow_area(0.0f, 0.5f, 0.5f);
                    glPopMatrix();

                }
            }
        }
        for (float j = 0.0; j > (height * 1.0); j -= 1.0) {
            k++;
            for (float i = 0.0; i < (width * 3.0); i += 2.0) {
                if (k % 2 != 0) {
                    glPushMatrix();
                    glTranslatef(i, 0.0, j);
                    draw_blok(1.0f, 0.5f, 0.5f, 0.3f);
                    //drow_area(1.0f, 0.5f, 0.5f);
                    glPopMatrix();

                }
                else {
                    glPushMatrix();
                    glTranslatef(i, 0.0, j);
                    draw_blok(0.0f, 0.5f, 0.5f, 0.3f);
                    //drow_area(0.0f, 0.5f, 0.5f);
                    glPopMatrix();

                }
            }
        }


    }
} field;

class snake : public blok {
private:

    struct {
        float x = 100;
        float z = 100;
    } s[378];

    int dir, num = 4;
    int best_score;
    int last_level;
    int level = 1;

public:

    snake() {};


    int get_num() { return num; }

    int get_best_score() { return best_score; }

    void set_best_score(int best_score) { this->best_score = best_score; }
   
    int get_last_level() { return last_level; }

    void set_last_level(int last_level) { this->last_level = last_level; }

    int get_level() { return level; }

    void set_num(int num) { this->num = num; }

    void set_level(int level) { this->level = level; }

    int snakeX(int i) { return s[i].x; };
    int snakeZ(int i) { return s[i].z; };
    void set_sX(int key, int index) { s[index].x = key; }
    void set_sZ(int key, int index) { s[index].z = -key; }

    void control_snake() {
        if (choose == true) {
            for (int i = num; i > 0; i--) {
                s[i].x = s[i - 1].x;
                s[i].z = s[i - 1].z;
            }
        }

        if (dir == 0) s[0].z -= 1.0;
        if (dir == 1) s[0].x -= 1.0;
        if (dir == 2) s[0].x += 1.0;
        if (dir == 3) s[0].z += 1.0;

        if (apple.get_x() == s[0].x && apple.get_z() == s[0].z) {
            num++;
            apple.New();

        }
        //height
        //width
        if (s[0].x >= (field.get_width() * 3)) { s[0].x = 0; } //право 
        if (s[0].z <= field.get_height()) { s[0].z = 0; } //верх
        if (s[0].x < 0) { s[0].x = (field.get_width() * 3)-1; } // лево
        if (s[0].z > 0) { s[0].z = field.get_height()+1; } //низ

        for (int i = 1; i < num; i++) {
            if (s[0].x == s[i].x && s[0].z == s[i].z) {
                lose = true;
            } 
        }
    }

    
    void KeyBoard(unsigned char key, int x, int y) {
        if (choose == true) {
            switch (key) {
            case 'w':  dir = 0; break;
            case 'd':  dir = 2; break;
            case 'a':  dir = 1; break;
            case 's':  dir = 3; break;
            case 'l':
                if (print_speed == true) { print_speed = false; }
                else { print_speed = true; }
                break;
            case 'k':
                if (last_level > level) {
                    for (int i = level; i < last_level; i++) {
                        speed = speed - 5;
                    }
                    level = last_level;
                }
                break;
            case 'z'://level up
                if (level < 10) {
                    level+=1;
                    speed = speed - 5;
                }
                break;
            case 'x'://lower level
                if (level > 1) {
                    level-=1;
                    speed = speed + 5;
                    break;
                }
            }
            
        }
        else {
            switch (key) {
            case 'w':  dir = 0; control_snake();  break;
            case 'd':  dir = 2; control_snake(); break;
            case 'a':  dir = 1; control_snake(); break;
            case 's':  dir = 3; control_snake(); break;
            case 'q':  choose = true; dir = 0; apple.New(); break;
            }
            
        }
    }

    void Snake() {
        for (int i = 0; i < num; i++) {
            glPushMatrix();
            glTranslatef(s[i].x, 0.4, s[i].z);
            draw_blok(0.0f, 0.0f, 1.0f, 1.0f);
            //drewsnake();
            glPopMatrix();
        }
    }

    void choose_place() {
        glPushMatrix();
        glTranslatef(s[0].x, 0.4, s[0].z);
        draw_blok(0.0f, 0.0f, 1.0f, 1.0f);
        //drewsnake();
        glPopMatrix();
    }

} snake;

float Fruits::get_x() { return x; }

float Fruits::get_z() { return z; }

void Fruits::New() {
    x = (rand() % field.get_width() * 3);
    z = (rand() % field.get_height());
    z = z * -1;
    check();//перевирка для того щоб ягода не з'явилася всередині змійки
}

void Fruits::check() {
    for (int i = 0; i < snake.get_num(); i++) {
        if (snake.snakeX(i) == x && snake.snakeZ(i) == z) {
            New();
        }
    }
}

void Fruits::print() {
    if (choose == false) {
        return;
    }
    glPushMatrix();
    glTranslatef(x, 0.4, z);
    draw_blok(1.0, 0.0, 0.0, 0.3f);
    glPopMatrix();
}


    void file_work::infile() {
        ofstream fout;
        fout.open(path);
        if (!fout.is_open()) {}
        else {
            fout << snake.get_best_score();
        }
        fout.close();

        fout.open(path2);
        if (!fout.is_open()) {}
        else {
            fout << snake.get_last_level();
        }
        fout.close();
    }

    void file_work::outfile() {
        ifstream fin;
        fin.open(path);
        if (!fin.is_open()) { snake.set_best_score(0); }
        else {
            string str;
            int i = 0;
            while (!fin.eof()) {
                str = "";
                getline(fin, str);
                if (i == 0) {
                    stringstream geek(str);
                    int b_score;
                    geek >> b_score;
                    snake.set_best_score(b_score);
                }
            }
        }
        fin.close();

        fin.open(path2);
        if (!fin.is_open()) { snake.set_last_level(1); }
        else {
            string str;
            int i = 0;
            while (!fin.eof()) {
                str = "";
                getline(fin, str);
                if (i == 0) {
                    stringstream geek(str);
                    int last_level;
                    geek >> last_level;
                    snake.set_last_level(last_level);
                }
            }
        }
        fin.close();
    }


void drawString(string text, float x, float y, float z) {
    // Встановлення позиції тексту:
    glRasterPos3f(x, y, z);
    int i = 0;
    while (text[i] != '\0') {
        // Рядок виводиться посимвольно:
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        i++;
    }
}

class Display {
public:

    void display() {
        //функция перетворення до строки 
        field.drawScene();
        if (choose == false) {
            drawString("Please, choose the place where you want to start", 0.0f, 4.0f, -20.0f);
            drawString("when you'll ready to start, just push the button (q)", 0.0f, 3.0f, -20.0f);
            snake.choose_place();
        }

        else if (lose == false) {
            snake.Snake();
            apple.print();
            if (snake.get_num() > snake.get_best_score()) { snake.set_best_score(snake.get_num()); file.infile(); };
            drawString("score: " + to_string(snake.get_num()), 12.0f, 3.0f, -21.0f);//вызов функции вывода на экран 

            if (snake.get_level() == 1) {
                drawString("level: " + to_string(snake.get_level()) + "-minimum", 16.0f, 3.0f, -21.0f);
            }
            else if (snake.get_level() == 10) {
                drawString("level: " + to_string(snake.get_level()) + "-maximum", 16.0f, 3.0f, -21.0f);
            }
            else {
                drawString("level: " + to_string(snake.get_level()), 16.0f, 3.0f, -21.0f);
            }

            drawString("pres (r) to restart the game", 4.0f, 8.0f, -21.0f);
            drawString("pres (e) to exit", 6.0f, 9.0f, -21.0f);

            if (print_score == false) { drawString("pres (f) to see best score", 0.0f, 3.0f, -21.0f); }
            else {
                drawString("best score: " + to_string(snake.get_best_score()), 0.0f, 3.0f, -21.0f);
                drawString("pres (f) to hide best score", 0.0f, 2.0f, -21.0f);
            }

            if (print_speed == false) { drawString("pres (l) to see your las last level", 4.0f, 6.0f, -21.0f); }
            else {
                drawString("your last level: " + to_string(snake.get_last_level()), 4.0f, 6.0f, -21.0f);
                if (snake.get_last_level() > snake.get_level()) {
                    drawString("pres (l) to hide your last level or pres (k) to restore your last level", 4.0f, 5.0f, -21.0f);
                }
                else {
                    drawString("pres (l) to hide your last level", 4.0f, 5.0f, -21.0f);
                }
            }
            drawString("pres (z) to level up:", 12.0f, 2.0f, -21.0f);
            drawString("pres (x) to lower level:", 12.0f, 1.0f, -21.0f);
            snake.control_snake();
        }
        else {
            drawString("pres (r) to restart the game", 4.0f, 8.0f, -21.0f);
            drawString("pres (e) to exit", 6.0f, 9.0f, -21.0f);
            drawString("you are lose, your score: " + to_string(snake.get_num()), 4.0f, 3.0f, -21.0f);//вызов функции вывода на экран 
            snake.Snake();
            apple.print();
        }
        glutSwapBuffers();
    }
}display;


void timer(int = 0) {
    display.display();
    glutTimerFunc(speed, timer, 0);
}

void specialfunc(int key, int x, int y) {
    field.KeyboardEvent(key, x, y);
}

void keyboardfunc(unsigned char key, int x, int y) {
    snake.KeyBoard(key, x, y);
    switch (key)
    {
    case 'f': //score
        if (choose == false) { break; }
        if (print_score == true) { print_score = false; }
        else { print_score = true; }
        break;
    case 'e': //exit procedure
        if (choose == false) { break; }
        snake.set_last_level(snake.get_level());
        file.infile();
        exit(0);
    case 'r':  //restart
        //ми повинні повернути все значення в початковий стан
        if (choose == false) { break; }
        choose = false;
        print_score = false;
        lose = false;
        print_speed = false;
        snake.set_last_level(snake.get_level());
        file.infile();
        snake.set_level(1);
        speed = 100;//швидкість прив'язана до того з якою частотою оновлюється картинка спочатку раз на 100 мілісекунд
        for (int i = 0; i < snake.get_num()+1; i++) {//для того щоб хвіст змійки не з'являвся на полі на початку нової гри

            snake.set_sX(100, i);
            snake.set_sZ(100, i);
        }
        snake.set_num(4);
        snake.set_sX(0, 0);
        snake.set_sZ(0, 0);//голову на початкові координати
        field.set_rotate_x(0);
        field.set_rotate_z(0);
        break;
    }
}

void reshapefunc(int w, int h) {
    field.handleResize(w, h);
}

void display_func() {
    display.display();
}

int main(int argc, char** argv) {
    srand(time(0));
    int h = 1280;
    int w = 1000;
    snake.set_sX(0, 0);
    snake.set_sZ(0, 0);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(h, w);
    glutCreateWindow("Game");
    file.outfile();
    glutDisplayFunc(display_func);
    glutTimerFunc(speed, timer, 0);
    glutSpecialFunc(specialfunc);
    glutKeyboardFunc(keyboardfunc);
    glutReshapeFunc(reshapefunc);

    glutMainLoop();

    return 0;
}