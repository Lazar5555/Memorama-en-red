#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define WIDTH 1200
#define HEIGTH 700

using namespace std;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_BITMAP *img_main, *img_mainStart, *img_mainExit, *img_con, *img_conServer, *img_conPlay;

void destroyAll(){
    //DISPLAY
    al_destroy_display(display);
    //COLA DE EVENTOS
    al_destroy_event_queue(event_queue);
    //IMAGENES
    al_destroy_bitmap(img_main);
    al_destroy_bitmap(img_mainStart);
    al_destroy_bitmap(img_mainExit);
    al_destroy_bitmap(img_con);
    al_destroy_bitmap(img_conServer);
    al_destroy_bitmap(img_conPlay);
}

int main(){

    bool salir = false;
    al_init();
    al_install_mouse();
    al_init_image_addon();

    display = al_create_display(WIDTH, HEIGTH);
    event_queue = al_create_event_queue();
    img_main = al_load_bitmap("imgs/main.png");
    img_mainStart = al_load_bitmap("imgs/main_start.png");
    img_mainExit = al_load_bitmap("imgs/main_exit.png");

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_draw_bitmap(img_main, 0, 0, 0);
    al_flip_display();
    while(!salir){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            salir = true;

        if(event.type == ALLEGRO_EVENT_MOUSE_AXES){//Main Window
            //Start Button
            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 458 && event.mouse.y < 539){
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

    }//End main looṕ

    destroyAll();

    return 0;
}
