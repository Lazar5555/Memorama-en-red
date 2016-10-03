#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define WIDTH 1200
#define HEIGTH 700

using namespace std;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_BITMAP *img_main, *img_mainStart, *img_mainExit, *img_getIP, *img_getIPCon;
ALLEGRO_FONT *font;
ALLEGRO_USTR *strIPServer;

int pos;
char ipServer[16];

void destroyAll(){
    //DISPLAY
    al_destroy_display(display);
    //COLA DE EVENTOS
    al_destroy_event_queue(event_queue);
    //IMAGENES
    al_destroy_bitmap(img_main);
    al_destroy_bitmap(img_mainStart);
    al_destroy_bitmap(img_mainExit);
    al_destroy_bitmap(img_getIP);
    al_destroy_bitmap(img_getIPCon);
    //Fuente
    al_destroy_font(font);
    //Strings
    al_ustr_free(strIPServer);
}

int main(){

    bool salir = false;
    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();

    display = al_create_display(WIDTH, HEIGTH);
    event_queue = al_create_event_queue();
    img_main = al_load_bitmap("imgs/main.png");
    img_mainStart = al_load_bitmap("imgs/main_start.png");
    img_mainExit = al_load_bitmap("imgs/main_exit.png");
    img_getIP = al_load_bitmap("imgs/getIP.png");
    img_getIPCon = al_load_bitmap("imgs/getIPCon.png");
    font = al_create_builtin_font();
    strIPServer = al_ustr_new("");
    pos = (int)al_ustr_size(strIPServer);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_draw_bitmap(img_main, 0, 0, 0);
    al_flip_display();
    while(!salir){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            salir = true;

        if(event.type == ALLEGRO_EVENT_MOUSE_AXES){//Main Window
            //Start Button
            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 458 && event.mouse.y < 539){//Start Button
                al_draw_bitmap(img_mainStart, 0, 0, 0);
                al_flip_display();
            }else if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 560 && event.mouse.y < 637){//Exit Button
                al_draw_bitmap(img_mainExit, 0, 0, 0);
                al_flip_display();
            }else{//DEFAULT
                al_draw_bitmap(img_main, 0, 0, 0);
                al_flip_display();
            }
        }//End Main AXES

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 458 && event.mouse.y < 539){//Click Comenzar

                bool salirServerAddr = false;
                int contchar = 0;

                al_draw_bitmap(img_getIP, 0, 0, 0);
                al_flip_display();
                while(!salirServerAddr){//Ventana conectar al servidor
                    ALLEGRO_EVENT event2;
                    al_wait_for_event(event_queue, &event2);

                    if(event2.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        salirServerAddr = true;
                        salir = true;

                    if(event2.type == ALLEGRO_EVENT_MOUSE_AXES){

                        if(event2.mouse.x > 751 && event2.mouse.x < 1029 && event2.mouse.y > 543 && event2.mouse.y < 620){//Connect Button
                            al_draw_bitmap(img_getIPCon, 0, 0, 0);
                            al_flip_display();
                        }
                        else{
                            al_draw_bitmap(img_getIP, 0, 0, 0);
                            al_flip_display();
                        }
                    }

                    if(event2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

                        if(event2.mouse.x > 751 && event2.mouse.x < 1029 && event2.mouse.y > 543 && event2.mouse.y < 620){//Click Conectar

                            bool terminar = false;

                            while(!terminar){

                            }
                        }
                        if(event2.mouse.x > 341 && event2.mouse.x < 768 && event2.mouse.y > 344 &&event2.mouse.y < 424){//Click cuadro IP
                                al_draw_ustr(font, al_map_rgb_f(0, 0, 0), 330, 170, 0, strIPServer);
                                al_flip_display();
                        }
                    }//Fin button down


                }
            }//Fin click comenzar
            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 560 && event.mouse.y < 637)//Click Salir
                salir = true;
        }

    }//End main looṕ

    destroyAll();

    return 0;
}
