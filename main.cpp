#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define WIDTH 1200
#define HEIGTH 700
#define FPS 60

#define DOWNCARD 0
#define UBUNTU 1
#define DEBIAN 2
#define FEDORA 3
#define ARCH 4
#define SUSE 5

using namespace std;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_BITMAP *img_main, *img_mainStart, *img_mainExit, *img_getIP, *img_getIPCon, *img_Tablero, *img_getIPBox, *img_getIPBoxCon;
ALLEGRO_BITMAP *img_Cards[6];
ALLEGRO_FONT *font;
ALLEGRO_TIMER *timer;

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
    al_destroy_bitmap(img_Tablero);
    al_destroy_bitmap(img_getIPBox);
    al_destroy_bitmap(img_getIPBoxCon);
    al_destroy_bitmap(img_Cards[DOWNCARD]);
    al_destroy_bitmap(img_Cards[UBUNTU]);
    al_destroy_bitmap(img_Cards[DEBIAN]);
    al_destroy_bitmap(img_Cards[FEDORA]);
    al_destroy_bitmap(img_Cards[ARCH]);
    al_destroy_bitmap(img_Cards[SUSE]);
    //Fuente
    al_destroy_font(font);

    //Timer
    al_destroy_timer(timer);
}


int main(){

    bool salir = false;
    bool clickOnBox = false;
    bool redraw = true;
    char str[17];

    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    display = al_create_display(WIDTH, HEIGTH);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    img_main = al_load_bitmap("imgs/main.png");
    img_mainStart = al_load_bitmap("imgs/main_start.png");
    img_mainExit = al_load_bitmap("imgs/main_exit.png");
    img_getIP = al_load_bitmap("imgs/getIP.png");
    img_getIPCon = al_load_bitmap("imgs/getIPCon.png");
    img_Tablero = al_load_bitmap("imgs/Tablero.png");
    img_getIPBox = al_load_bitmap("imgs/getIPBox.png");
    img_getIPBoxCon = al_load_bitmap("imgs/getIPBoxCon.png");
    img_Cards[DOWNCARD] = al_load_bitmap("imgs/DownCard.png");
    img_Cards[UBUNTU] = al_load_bitmap("imgs/UbuntuCard.png");
    img_Cards[DEBIAN] = al_load_bitmap("imgs/DebianCard.png");
    img_Cards[FEDORA] = al_load_bitmap("imgs/FedoraCard.png");
    img_Cards[ARCH] = al_load_bitmap("imgs/ArchCard.png");
    img_Cards[SUSE] = al_load_bitmap("imgs/SuseCard.png");
    font = al_load_font("fonts/fuente_pincel.ttf", 68, 0);
    strcpy(str, "");

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_draw_bitmap(img_main, 0, 0, 0);
    al_flip_display();
    al_start_timer(timer);
    while(!salir){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            salir = true;

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        if(event.type == ALLEGRO_EVENT_MOUSE_AXES){//Main Window
            //Start Button
            if((event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 458 && event.mouse.y < 539) && redraw){//Start Button
                redraw = false;
                al_draw_bitmap(img_mainStart, 0, 0, 0);
                al_flip_display();
            }else if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 560 && event.mouse.y < 637 && redraw){//Exit Button
                redraw = false;
                al_draw_bitmap(img_mainExit, 0, 0, 0);
                al_flip_display();
            }else if(redraw){//DEFAULT
                redraw = false;
                al_draw_bitmap(img_main, 0, 0, 0);
                al_flip_display();
            }
        }//End Main AXES

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 458 && event.mouse.y < 539){///Click Comenzar

                bool salirServerAddr = false;
                redraw = true;

                al_draw_bitmap(img_getIP, 0, 0, 0);
                al_flip_display();
                while(!salirServerAddr){//Ventana conectar al servidor
                    ALLEGRO_EVENT event2;
                    al_wait_for_event(event_queue, &event2);

                    if(event2.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        salirServerAddr = true;
                        salir = true;

                    if(event2.type == ALLEGRO_EVENT_TIMER)
                        redraw = true;

                    if(event2.type == ALLEGRO_EVENT_MOUSE_AXES){

                        if(event2.mouse.x > 812 && event2.mouse.x < 1111 && event2.mouse.y > 557 && event2.mouse.y < 638 && redraw){
                            redraw = false;
                            al_draw_bitmap(img_getIPCon, 0, 0, 0);
                            al_draw_text(font, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, str);
                            al_flip_display();
                        }else if(clickOnBox == true && redraw){
                            redraw = false;
                            al_draw_bitmap(img_getIPBox, 0, 0, 0);
                            al_draw_text(font, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, str);
                            al_flip_display();
                        }else if(redraw){
                            redraw = false;
                            al_draw_bitmap(img_getIP, 0, 0, 0);
                            al_flip_display();
                        }

                    }

                    if(event2.type == ALLEGRO_EVENT_KEY_CHAR && clickOnBox){///EVENTO KEY CHAR

                        if(strlen(str) <= 16){
                            char temp[] = {event2.keyboard.unichar, '\0'};
                            if (event2.keyboard.unichar == ' ')
                                strcat(str, temp);
                            else if(event2.keyboard.unichar >= '0' && event2.keyboard.unichar <= '9')
                                strcat(str, temp);
                            else if(event2.keyboard.unichar >= 'A' && event2.keyboard.unichar <= 'Z')
                                strcat(str, temp);
                            else if(event2.keyboard.unichar >= 'a' && event2.keyboard.unichar <= 'z')
                                strcat(str, temp);
                            else if(event2.keyboard.unichar == '.')
                                strcat(str, temp);
                        }

                        if(event2.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0)
                            str[strlen(str) - 1] = '\0';

                        if(clickOnBox){
                            al_draw_bitmap(img_getIPBox, 0, 0, 0);
                            al_draw_text(font, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, str);
                            al_flip_display();
                            cout<<str<<endl;
                        }

                    }///Fin evento KEY CHAR

                    if(event2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){///MOUSE DOWN pantalla getIP

                        if(event2.mouse.x > 341 && event2.mouse.x < 768 && event2.mouse.y > 344 &&event2.mouse.y < 424){///Click IPBox
                                clickOnBox = true;
                                al_draw_bitmap(img_getIPBox, 0, 0, 0);
                                al_flip_display();
                        }

                        if(event2.mouse.x > 812 && event2.mouse.x < 1111 && event2.mouse.y > 557 && event2.mouse.y < 638){///Click Conectar

                            redraw = true;
                            bool gameOver = false;
                            bool card1 = false, card2 = false, card3 = false, card4 = false, card5 = false;
                            bool card6 = false, card7 = false, card8 = false, card9 = false, card10 = false;

                            al_draw_bitmap(img_Tablero, 0, 0, 0);
                            al_flip_display();
                            while(!gameOver){

                                ALLEGRO_EVENT event;
                                al_wait_for_event(event_queue, &event);

                                if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                                    gameOver = true;
                                    salirServerAddr = true;
                                    salir = true;
                                }

                                if(event.type == ALLEGRO_EVENT_TIMER)
                                    redraw = true;

                                if(event.type == ALLEGRO_EVENT_MOUSE_AXES){

                                }

                                if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){///Clicks en el tablero

                                    if(event.mouse.x > 163 && event.mouse.x < 312 && event.mouse.y > 132 && event.mouse.y < 340){///Carta 1
                                        card1 = true;
                                    }
                                    if(event.mouse.x > 342 && event.mouse.x < 491 && event.mouse.y > 132 && event.mouse.y < 340){///Carta 2
                                        card2 = true;
                                    }
                                    if(event.mouse.x > 515 && event.mouse.x < 664 && event.mouse.y > 132 && event.mouse.y < 340){///Carta 3
                                        card3 = true;
                                    }
                                    if(event.mouse.x > 699 && event.mouse.x < 848 && event.mouse.y > 132 && event.mouse.y < 340){///Carta 4
                                        card4 = true;
                                    }
                                    if(event.mouse.x > 880 && event.mouse.x < 1029 && event.mouse.y > 132 && event.mouse.y < 340){///Carta 4
                                        card5 = true;
                                    }
                                }

                                if(card1){
                                    al_draw_bitmap(img_Cards[UBUNTU], 163, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 163, 132, 0);
                                    al_flip_display();
                                }

                                if(card2){
                                    al_draw_bitmap(img_Cards[DEBIAN], 342, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 342, 132, 0);
                                    al_flip_display();
                                }

                                if(card3){
                                    al_draw_bitmap(img_Cards[FEDORA], 515, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 515, 132, 0);
                                    al_flip_display();
                                }

                                if(card4){
                                    al_draw_bitmap(img_Cards[ARCH], 699, 132, 0);
                                    al_flip_display();
                                }else if(!card4){
                                    al_draw_bitmap(img_Cards[DOWNCARD], 699, 132, 0);
                                    al_flip_display();
                                }

                                if(card5){
                                    al_draw_bitmap(img_Cards[SUSE], 880, 132, 0);
                                    al_flip_display();
                                }else if(!card5){
                                    al_draw_bitmap(img_Cards[DOWNCARD], 880, 132, 0);
                                    al_flip_display();
                                }

                                if(card6){

                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 162, 356, 0);
                                    al_flip_display();
                                }

                                if(card7){

                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 342, 356, 0);
                                    al_flip_display();
                                }

                                if(card8){

                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 515, 356, 0);
                                    al_flip_display();
                                }

                                if(card9){

                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 880, 356, 0);
                                    al_flip_display();
                                }

                                if(card10){

                                }else{
                                    al_draw_bitmap(img_Cards[DOWNCARD], 699, 356, 0);
                                    al_flip_display();
                                }

                            }
                        }

                    }///Fin mouse down pantalla getIP

                }
            }//Fin click comenzar
            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 560 && event.mouse.y < 637)//Click Salir
                salir = true;
        }

    }//End main looṕ

    destroyAll();

    return 0;
}
