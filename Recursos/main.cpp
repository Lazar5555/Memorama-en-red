#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "options.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
//ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *fondo1, *fondo2, *fondo3, *opc1, *opc2, *opc3, *opc4, *con1, *con2, *con3, *con4, *con5;
ALLEGRO_BITMAP *esp1, *esp2, *esp3, *esp4;
ALLEGRO_FONT *font;
ALLEGRO_USTR  *str, *strClientPort;
int pos;
char clientip[14], Servip[14];
int clientport, servport;

/*int main()   {
    al_init();
    al_init_font_addon();
    al_install_keyboard();
    ALLEGRO_DISPLAY* d = al_create_display(800, 600);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();
    al_register_event_source(q, al_get_keyboard_event_source());
    al_register_event_source(q, al_get_display_event_source(d));
    ALLEGRO_USTR* str = al_ustr_new("Type something...");
    int pos = (int)al_ustr_size(str);

    bool quit = false;
    while(!quit)  {
            al_clear_to_color(al_map_rgb_f(0, 0, 0));
            al_draw_ustr(font, al_map_rgb_f(1, 1, 1), 400, 300, ALLEGRO_ALIGN_CENTRE, str);
            al_flip_display();
            ALLEGRO_EVENT e;
            al_wait_for_event(q, &e);
            switch(e.type)  {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                quit = true;
                break;
                case ALLEGRO_EVENT_KEY_CHAR:
                    if(e.keyboard.unichar >= 32){
                            pos += al_ustr_append_chr(str, e.keyboard.unichar);
                            } else if(e.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                if(al_ustr_prev(str, &pos))
                                    al_ustr_truncate(str, pos);
                                }

                                break;
                }
        }
}*/

void load(){
    display = al_create_display(1200, 700);
    event_queue = al_create_event_queue();
    fondo1 = al_load_bitmap("imgs/menu_1.png");
    fondo2 = al_load_bitmap("imgs/menu_2.png");
    fondo3 = al_load_bitmap("imgs/menu_3.png");
    opc1 = al_load_bitmap("imgs/opc_1.png");
    opc2 = al_load_bitmap("imgs/opc_2.png");
    opc3 = al_load_bitmap("imgs/opc_3.png");
    opc4 = al_load_bitmap("imgs/opc_4.png");
    con1 = al_load_bitmap("imgs/con_1.png");
    con2 = al_load_bitmap("imgs/con_2.png");
    con3 = al_load_bitmap("imgs/con_3.png");
    con4 = al_load_bitmap("imgs/con_4.png");
    con5 = al_load_bitmap("imgs/con_5.png");
    esp1 = al_load_bitmap("imgs/esp_1.png");
    esp2 = al_load_bitmap("imgs/esp_2.png");
    esp3 = al_load_bitmap("imgs/esp_3.png");
    esp4 = al_load_bitmap("imgs/esp_4.png");
    font = al_create_builtin_font();
    str = al_ustr_new("");
    strClientPort = al_ustr_new("");
    pos = (int)al_ustr_size(str);
}

void destroy(){
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(fondo1);
    al_destroy_bitmap(fondo2);
    al_destroy_bitmap(fondo3);
    al_destroy_bitmap(opc1);
    al_destroy_bitmap(opc2);
    al_destroy_bitmap(opc3);
    al_destroy_bitmap(opc4);
    al_destroy_bitmap(con1);
    al_destroy_bitmap(con2);
    al_destroy_bitmap(con3);
    al_destroy_bitmap(con4);
    al_destroy_bitmap(con5);
    al_destroy_bitmap(esp1);
    al_destroy_bitmap(esp2);
    al_destroy_bitmap(esp3);
    al_destroy_bitmap(esp4);
    al_destroy_font(font);
    al_ustr_free(str);
    al_ustr_free(strClientPort);
    //al_destroy_ustr(str);
}

int main()
{
    bool salir = false;
    al_init();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    load();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    //al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    //al_start_timer(timer);
    al_draw_bitmap(fondo1, 0, 0, 0);
    al_flip_display();

    while (!salir)//Bucle principal
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            if(event.mouse.x > 674 && event.mouse.x < 1005  &&  event.mouse.y > 483 && event.mouse.y < 545){//COMENZAR
                al_draw_bitmap(fondo2, 0, 0, 0);
                al_flip_display();
            }

            else if(event.mouse.x > 679 && event.mouse.x < 877 && event.mouse.y > 578 && event.mouse.y < 644){//SALIR
                al_draw_bitmap(fondo3, 0, 0, 0);
                al_flip_display();
            }
            else{//DEFAULT
                al_draw_bitmap(fondo1, 0, 0, 0);
                al_flip_display();
            }
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){//PRINCIPAL
            if(event.mouse.x > 674 && event.mouse.x < 1005  &&  event.mouse.y > 483 && event.mouse.y < 545){//COMENZAR

                bool opcSalir = false;
                bool click1 = false;
                bool click2 = false;
                bool click_esp = false;
                al_draw_bitmap(opc1, 0, 0, 0);
                al_flip_display();

                while(!opcSalir){
                    ALLEGRO_EVENT event2;
                    al_wait_for_event(event_queue, &event2);

                    if (event2.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                        salir = true;
                        opcSalir = true;
                    }

                    if(event2.type == ALLEGRO_EVENT_MOUSE_AXES){
                        if(event2.mouse.x > 65 && event2.mouse.x < 966  &&  event2.mouse.y > 126 && event2.mouse.y < 274){
                            al_draw_bitmap(opc2, 0, 0, 0);
                            al_flip_display();
                        }
                        else if(event2.mouse.x > 65 && event2.mouse.x < 832 && event2.mouse.y > 302 && event2.mouse.y < 444){
                            al_draw_bitmap(opc3, 0, 0, 0);
                            al_flip_display();
                        }
                        else if(event2.mouse.x > 780 && event2.mouse.x < 1140 && event2.mouse.y > 583 && event2.mouse.y < 643){
                            al_draw_bitmap(opc4, 0, 0, 0);
                            al_flip_display();
                        }
                        else{
                            al_draw_bitmap(opc1, 0, 0, 0);
                            al_flip_display();
                        }
                    }

                    if(event2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){//OPCIONES
                        if(event2.mouse.x > 780 && event2.mouse.x < 1140 && event2.mouse.y > 583 && event2.mouse.y < 643){//REGRESAR
                            al_draw_bitmap(fondo1, 0, 0, 0);
                            al_flip_display();
                            opcSalir = true;
                        }

                        if(event2.mouse.x > 68 && event2.mouse.x < 965 && event2.mouse.y > 127 && event2.mouse.y < 274){//CONECTAR
                            bool opcConectar = false;
                            int contchar = 0;
                            int contcharP = 0;
                            char auxP[5];
                            al_draw_bitmap(con1, 0, 0, 0);
                            al_flip_display();
                            while(!opcConectar){
                                al_flip_display();
                                ALLEGRO_EVENT event;
                                al_wait_for_event(event_queue, &event);
                                if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                                    opcConectar = true;
                                    opcSalir = true;
                                    salir = true;
                                }

                                if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
                                    if(event.mouse.x > 781 && event.mouse.x < 1183 && event.mouse.y > 512 && event.mouse.y < 570){
                                        al_draw_bitmap(con4, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                    }
                                    else if(event.mouse.x > 780 && event.mouse.x < 1138 && event.mouse.y > 583 && event.mouse.y < 641){
                                        al_draw_bitmap(con5, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                    }
                                    else if(click1 == true){//Muestra cajas seleccionadas
                                        al_draw_bitmap(con2, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                    }
                                    else if(click2 == true){//Muestra cajas seleccionadas
                                        al_draw_bitmap(con3, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                    }
                                    else{
                                        al_draw_bitmap(con1, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                    }
                                }

                                if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                                    if(event.mouse.x > 780 && event.mouse.x < 1138 && event.mouse.y > 583 && event.mouse.y < 641){//Regresar a Opciones
                                        al_draw_bitmap(opc1, 0, 0, 0);
                                        al_flip_display();
                                        opcConectar = true;
                                        click1 = false;
                                        click2 = false;
                                        clientip[0] = '\0';
                                        auxP[0] = '\0';
                                        clientport = 0;
                                        str = al_ustr_new("");
                                        strClientPort = al_ustr_new("");
                                    }
                                    else if(event.mouse.x > 780 && event.mouse.x < 1182 && event.mouse.y > 512 && event.mouse.y < 569){//Conectar
                                        cout<<"Aquí comienza el juego para el jugador continuar"<<endl;
                                    }
                                    else if(event.mouse.x > 316 && event.mouse.x < 884 && event.mouse.y > 112 && event.mouse.y < 225){//Click en cuadro IP
                                        al_draw_bitmap(con2, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                        click1 = true;
                                        click2 = false;
                                    }
                                    else if(event.mouse.x > 316 && event.mouse.x < 601 && event.mouse.y > 326 && event.mouse.y < 439){//Caja de Puerto
                                        al_draw_bitmap(con3, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                        click2 = true;
                                        click1 = false;
                                    }
                                    else if(event.mouse.x < 316 || event.mouse.x > 884 || event.mouse.y < 112 || event.mouse.y > 225  || event.mouse.x < 316 || event.mouse.x > 601 || event.mouse.y < 326 || event.mouse.y > 439){//Quita seleccion si se hace click fueras de las cajas
                                        al_draw_bitmap(con1, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                        click1 = false;
                                        click2 = false;
                                    }
                                }
                                if(event.type == ALLEGRO_EVENT_KEY_CHAR && click1 == true){//Guarda el texto en caja IP en un char
                                        if(event.keyboard.unichar >= 32){
                                                pos += al_ustr_append_chr(str, event.keyboard.unichar);
                                                if(contchar < 15){
                                                    clientip[contchar] = event.keyboard.unichar;
                                                    contchar ++;
                                                }
                                        }
                                        else if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                            if(al_ustr_prev(str, &pos)){
                                                al_ustr_truncate(str, pos);
                                                if(contchar > -1){
                                                    clientip[contchar] = '\0';
                                                    contchar --;
                                                }
                                            }
                                        }
                                        al_draw_bitmap(con2, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, str);
                                        al_flip_display();
                                        cout<<clientip<<endl;
                                }
                                if(event.type == ALLEGRO_EVENT_KEY_CHAR && click2 == true){//Guarda el texto en caja PUERTO en un char
                                    if(event.keyboard.unichar >= 48 && event.keyboard.unichar < 58){
                                                pos += al_ustr_append_chr(strClientPort, event.keyboard.unichar);
                                                if(contcharP < 5){
                                                    auxP[contcharP] = event.keyboard.unichar;
                                                    contcharP ++;
                                                    clientport = atoi(auxP);
                                                }
                                        }
                                        else if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                            if(al_ustr_prev(strClientPort, &pos)){
                                                al_ustr_truncate(strClientPort, pos);
                                                if(contcharP > -1){
                                                    auxP[contcharP] = '\0';
                                                    contcharP --;
                                                }
                                            }
                                        }
                                        al_draw_bitmap(con3, 0, 0, 0);
                                        al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 382, 0, strClientPort);
                                        al_flip_display();
                                        cout<<clientport<<endl;
                                }
                            }
                        }
                        if(event2.mouse.x > 66 && event2.mouse.x < 832 && event2.mouse.y > 302 && event2.mouse.y < 444){//ESPERAR
                            bool opcEsperar = false;
                            al_draw_bitmap(esp1, 0, 0, 0);
                            al_flip_display();
                            while(!opcEsperar){
                                al_wait_for_event(event_queue, &event);

                                if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                                    opcEsperar = true;
                                    opcSalir = true;
                                    salir = true;
                                }

                                if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
                                    if(event.mouse.x > 781 && event.mouse.x < 1182 && event.mouse.y > 510 && event.mouse.y < 570){//Continuar
                                        al_draw_bitmap(esp3, 0, 0, 0);
                                        al_flip_display();
                                    }
                                    else if(event.mouse.x > 781 && event.mouse.x < 1140 && event.mouse.y > 582 && event.mouse.y < 642){//Regresar
                                        al_draw_bitmap(esp4, 0, 0, 0);
                                        al_flip_display();
                                    }
                                    else if(click_esp == true){
                                        al_draw_bitmap(esp2, 0, 0, 0);
                                        al_flip_display();
                                    }
                                    else{
                                        al_draw_bitmap(esp1, 0, 0, 0);
                                        al_flip_display();
                                    }
                                }

                                if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                                    if(event.mouse.x > 781 && event.mouse.x < 1140 && event.mouse.y > 582 && event.mouse.y < 642){//Regresar
                                        al_draw_bitmap(opc1, 0, 0, 0);
                                        al_flip_display();
                                        opcEsperar = true;
                                        click_esp = false;

                                    }
                                    else if(event.mouse.x > 781 && event.mouse.x < 1182 && event.mouse.y > 510 && event.mouse.y < 570){//Continuar
                                        cout<<"Aquí comienza el juego para esperar"<<endl;
                                    }
                                    else if(event.mouse.x > 318 && event.mouse.x < 603 && event.mouse.y > 326 && event.mouse.y < 438){//Caja puerto
                                        click_esp = true;
                                        al_draw_bitmap(esp2, 0, 0, 0);
                                        al_flip_display();
                                    }
                                    else if(event.mouse.x > 318 || event.mouse.x < 603 || event.mouse.y > 326 || event.mouse.y < 438){
                                        click_esp = false;
                                        al_draw_bitmap(esp1, 0, 0, 0);
                                        al_flip_display();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(event.mouse.x > 679 && event.mouse.x < 877 && event.mouse.y > 578 && event.mouse.y < 644)//SALIR
                salir = true;
        }

    }
    destroy();

    return 0;
}
