#ifndef FONCTIONS_SUP_H
#define FONCTIONS_SUP_H



typedef struct{
    int upState:2;
    int downState:2;
    int enterState:2;
    int upEdge:2;
    int downEdge:2;
    int enterEdge:2;
}Keyboard;

void menu_principale(Keyboard *keyboard);
int detect_button_press(int button);
void delay_en_s(float time);
void _wait10mus(unsigned int tenmus);

#endif