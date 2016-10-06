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
ALLEGRO_BITMAP *img_main, *img_mainStart, *img_mainExit, *img_getIP, *img_getIPCon, *img_Tablero, *img_getIPBox, *img_getIPBoxCon;
ALLEGRO_BITMAP *img_UbuntuCard, *img_ArchCard, *img_DebianCard, *img_FedoraCard, *img_SuseCard, *img_DownCard;
ALLEGRO_FONT *font;
ALLEGRO_USTR *strIPServer;

int pos;
char ipServer[16];
bool clickOnBox = false;//Variable para saber si el cuadro de IP ha sido clickeado

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
    al_destroy_bitmap(img_UbuntuCard);
    al_destroy_bitmap(img_DebianCard);
    al_destroy_bitmap(img_FedoraCard);
    al_destroy_bitmap(img_ArchCard);
    al_destroy_bitmap(img_SuseCard);
    al_destroy_bitmap(img_DownCard);
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
    img_Tablero = al_load_bitmap("imgs/Tablero.png");
    img_getIPBox = al_load_bitmap("imgs/getIPBox.png");
    img_getIPBoxCon = al_load_bitmap("imgs/getIPBoxCon.png");
    img_UbuntuCard = al_load_bitmap("imgs/UbuntuCard.png");
    img_DebianCard = al_load_bitmap("imgs/DebianCard.png");
    img_FedoraCard = al_load_bitmap("imgs/FedoraCard.png");
    img_ArchCard = al_load_bitmap("imgs/ArchCard.png");
    img_SuseCard = al_load_bitmap("imgs/SuseCard.png");
    img_DownCard = al_load_bitmap("imgs/DownCard.png");
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

                        if(event2.mouse.x > 812 && event2.mouse.x < 1111 && event2.mouse.y > 557 && event2.mouse.y < 638){
                            al_draw_bitmap(img_getIPCon, 0, 0, 0);
                            al_flip_display();
                        }else if(clickOnBox == true){
                            al_draw_bitmap(img_getIPBox, 0, 0, 0);
                            al_flip_display();
                        }else{
                            al_draw_bitmap(img_getIP, 0, 0, 0);
                            al_flip_display();
                        }
                    }

                    if(event2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){///MOUSE DOWN pantalla getIP

                        if(event2.mouse.x > 812 && event2.mouse.x < 1111 && event2.mouse.y > 557 && event2.mouse.y < 638){///Click Conectar

                            bool gameOver = false;
                            bool card1 = false, card2 = false, card3 = false, card4 = false, card5 = false;
                            bool card6 = false, card7 = false, card8 = false, card9 = false, card10 = false;

                            al_draw_bitmap(img_Tablero, 0, 0, 0);
                            al_flip_display();
                            while(!gameOver){

                                ALLEGRO_EVENT event;
                                al_wait_for_event(event_queue, &event);

                                if(card1){
                                    al_draw_bitmap(img_UbuntuCard, 163, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_DownCard, 163, 132, 0);
                                    al_flip_display();
                                }

                                if(card2){
                                    al_draw_bitmap(img_DebianCard, 342, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_DownCard, 342, 132, 0);
                                    al_flip_display();
                                }

                                if(card3){
                                    al_draw_bitmap(img_ArchCard, 515, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_DownCard, 515, 132, 0);
                                    al_flip_display();
                                }

                                if(card4){
                                    al_draw_bitmap(img_SuseCard, 699, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_DownCard, 699, 132, 0);
                                    al_flip_display();
                                }

                                if(card5){
                                    al_draw_bitmap(img_FedoraCard, 880, 132, 0);
                                    al_flip_display();
                                }else{
                                    al_draw_bitmap(img_DownCard, 880, 132, 0);
                                    al_flip_display();
                                }
                                ///*********************///
                                if(card6){

                                }else{
                                    al_draw_bitmap(img_DownCard, 162, 356, 0);
                                    al_flip_display();
                                }

                                if(card7){

                                }else{
                                    al_draw_bitmap(img_DownCard, 342, 356, 0);
                                    al_flip_display();
                                }

                                if(card8){

                                }else{
                                    al_draw_bitmap(img_DownCard, 515, 356, 0);
                                    al_flip_display();
                                }

                                if(card9){

                                }else{
                                    al_draw_bitmap(img_DownCard, 880, 356, 0);
                                    al_flip_display();
                                }

                                if(card10){

                                }else{
                                    al_draw_bitmap(img_DownCard, 699, 356, 0);
                                    al_flip_display();
                                }

                                if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                                    gameOver = true;
                                    salirServerAddr = true;
                                    salir = true;
                                }

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
                            }
                        }
                        if(event2.mouse.x > 341 && event2.mouse.x < 768 && event2.mouse.y > 344 &&event2.mouse.y < 424){///Click cuadro IP
                                clickOnBox = true;
                                al_draw_bitmap(img_getIPBox, 0, 0, 0);
                                al_flip_display();
                        }

                    }//Fin mouse down pantalla getIP

                }
            }//Fin click comenzar
            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 560 && event.mouse.y < 637)//Click Salir
                salir = true;
        }

    }//End main looṕ

    destroyAll();

    return 0;
}
