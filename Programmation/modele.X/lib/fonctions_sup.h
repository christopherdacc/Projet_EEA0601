#ifndef FONCTIONS_SUP_H
#define FONCTIONS_SUP_H

// forward declaration
typedef struct menu Menu;
typedef struct menuitem MenuItem;
typedef struct menuvalue MenuValue;


typedef struct{
    int upState:2;
    int downState:2;
    int enterState:2;
    int upEdge:2;
    int downEdge:2;
    int enterEdge:2;
}Keyboard;

struct menu{
    char *title;               //titre du menu
    Menu *root;         //menu precedent
    MenuItem *items;    //option du menu specifique
    short offset:6;            //decalage verticale de la selection
    short selected:4;          //indique l'option selectionner
};

struct menuitem{
    char *label;        //chaine de char pour l'option selectionner
    void *action;       //depend de type (si type=1 on execute une fonction/si 2 affiche submenu/si 3 on pointe vers MenuValue)
    short type:2;       //0=selectable, 1=action, 2=submenu, 3=value
    short checked:1;    //0=selectable, 1=action->(action, submenu, value)
};

struct menuvalue{
    int tuningValue;
    int *tunedValue;
    int min;
    int max;
    short type;         //0 la valeu change lors du changement, 1 la valeur change apres appuie sur entree
};

void menu_principale(Keyboard *keyboard);
int detect_button_press(int button);
void delay_en_s(float time);
void _wait10mus(unsigned int tenmus);

#endif