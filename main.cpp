#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

//Librerías allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//Librerías para red
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#define WIDTH 1200
#define HEIGTH 700
#define FPS 60
#define EXIT_PAUSE 3.0

#define DOWNCARD 0
#define UBUNTU 1
#define DEBIAN 2
#define FEDORA 3
#define ARCH 4
#define SUSE 5

#define PORTSERVER 25500

using namespace std;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_BITMAP *img_main, *img_mainStart, *img_mainExit, *img_getIP, *img_getIPCon, *img_Tablero, *img_getIPBox, *img_getIPBoxCon;
ALLEGRO_BITMAP *img_Cards[6];
ALLEGRO_BITMAP *img_failConection;
ALLEGRO_BITMAP *img_waiting, *img_closedServer, *img_leftGame, *img_youWin, *img_youLose;
ALLEGRO_FONT *font, *fontGame;
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
    al_destroy_bitmap(img_failConection);
    al_destroy_bitmap(img_waiting);
    al_destroy_bitmap(img_closedServer);
    al_destroy_bitmap(img_leftGame);
    al_destroy_bitmap(img_youWin);
    al_destroy_bitmap(img_youLose);
    //Fuente
    al_destroy_font(font);
    al_destroy_font(fontGame);

    //Timer
    al_destroy_timer(timer);
}

/*void draw_card(int n, int tab[10]){
    if(n == 0){
                                            al_draw_bitmap(img_Cards[tab[0]], 163, 132, 0);

                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 163, 132, 0);

                                        }

                                        if(n == 1){
                                            al_draw_bitmap(img_Cards[tab[1]], 342, 132, 0);

                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 342, 132, 0);

                                        }

                                        if(n == 2){
                                            al_draw_bitmap(img_Cards[tab[2]], 515, 132, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 515, 132, 0);

                                        }

                                        if(n == 3){
                                            al_draw_bitmap(img_Cards[tab[3]], 699, 132, 0);

                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 699, 132, 0);

                                        }

                                        if(n == 4){
                                            al_draw_bitmap(img_Cards[tab[4]], 880, 132, 0);

                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 880, 132, 0);

                                        }

                                        if(n == 5){
                                            al_draw_bitmap(img_Cards[tab[5]], 162, 356, 0);

                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 162, 356, 0);

                                    }
                                    if(n == 6){
                                        al_draw_bitmap(img_Cards[tab[6]], 342, 356, 0);

                                    }else{
                                        al_draw_bitmap(img_Cards[DOWNCARD], 342, 356, 0);

                                    }
                                    if(n == 7){
                                        al_draw_bitmap(img_Cards[tab[7]], 515, 356, 0);

                                    }else{
                                        al_draw_bitmap(img_Cards[DOWNCARD], 515, 356, 0);

                                    }
                                    if(n == 8){
                                        al_draw_bitmap(img_Cards[tab[8]], 699, 356, 0);

                                    }else{
                                        al_draw_bitmap(img_Cards[DOWNCARD], 699, 356, 0);

                                    }
                                    if(n == 9){
                                        al_draw_bitmap(img_Cards[tab[9]], 880, 356, 0);

                                    }else{
                                        al_draw_bitmap(img_Cards[DOWNCARD], 880, 356, 0);

                                    }
}*/

int main(){

    bool salir = false;
    bool clickOnBox = false;
    bool redraw = true;
    bool cargado = false;

    int s, res;
    char host[200];

    //Iniciar los componentes de Allegro
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
    img_getIPBox = al_load_bitmap("imgs/getIPBox.png");
    img_getIPBoxCon = al_load_bitmap("imgs/getIPBoxCon.png");
    //Imagenes ventanas
    img_waiting = al_load_bitmap("imgs/waiting_player.png");
    img_closedServer = al_load_bitmap("imgs/closed_server.png");
    img_failConection = al_load_bitmap("imgs/FailConection.png");
    img_leftGame = al_load_bitmap("imgs/left_game.png");
    img_youWin = al_load_bitmap("imgs/you_win.png");
    img_youLose = al_load_bitmap("imgs/you_lose.png");
    //Imagenes del tablero
    img_Cards[DOWNCARD] = al_load_bitmap("imgs/DownCard.png");
    img_Cards[UBUNTU] = al_load_bitmap("imgs/UbuntuCard.png");
    img_Cards[DEBIAN] = al_load_bitmap("imgs/DebianCard.png");
    img_Cards[FEDORA] = al_load_bitmap("imgs/FedoraCard.png");
    img_Cards[ARCH] = al_load_bitmap("imgs/ArchCard.png");
    img_Cards[SUSE] = al_load_bitmap("imgs/SuseCard.png");
    font = al_load_font("fonts/fuente_pincel.ttf", 68, 0);
    fontGame = al_load_font("fonts/fuente_pincel.ttf", 100, 0);
    strcpy(host, "");

    /*Iniciar los componentes de red*/
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0){
        perror("Error en socket()");
        close(s);
        return EXIT_FAILURE;
    }

    /*Inicializamos la estructura sockaddr_in*/
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTSERVER);

    struct addrinfo hints, *lista, *save;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

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
                            al_draw_text(font, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, host);
                            al_flip_display();
                        }else if(clickOnBox == true && redraw){
                            redraw = false;
                            al_draw_bitmap(img_getIPBox, 0, 0, 0);
                            al_draw_text(font, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, host);
                            al_flip_display();
                        }else if(redraw){
                            redraw = false;
                            al_draw_bitmap(img_getIP, 0, 0, 0);
                            al_flip_display();
                        }

                    }

                    if(event2.type == ALLEGRO_EVENT_KEY_CHAR && clickOnBox){///EVENTO KEY CHAR

                        if(strlen(host) <= 200){
                            char temp[] = {event2.keyboard.unichar, '\0'};
                            if (event2.keyboard.unichar == ' ')
                                strcat(host, temp);
                            else if(event2.keyboard.unichar >= '0' && event2.keyboard.unichar <= '9')
                                strcat(host, temp);
                            else if(event2.keyboard.unichar >= 'A' && event2.keyboard.unichar <= 'Z')
                                strcat(host, temp);
                            else if(event2.keyboard.unichar >= 'a' && event2.keyboard.unichar <= 'z')
                                strcat(host, temp);
                            else if(event2.keyboard.unichar == '.')
                                strcat(host, temp);
                        }

                        if(event2.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(host) != 0)
                            host[strlen(host) - 1] = '\0';

                        if(clickOnBox){
                            al_draw_bitmap(img_getIPBox, 0, 0, 0);
                            al_draw_text(font, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, host);
                            al_flip_display();
                            cout<<host<<endl;
                        }

                    }///Fin evento KEY CHAR

                    if(event2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){///MOUSE DOWN pantalla getIP

                        if(event2.mouse.x > 341 && event2.mouse.x < 768 && event2.mouse.y > 344 &&event2.mouse.y < 424){///Click IPBox
                                clickOnBox = true;
                                al_draw_bitmap(img_getIPBox, 0, 0, 0);
                                al_flip_display();
                        }

                        if(event2.mouse.x > 812 && event2.mouse.x < 1111 && event2.mouse.y > 557 && event2.mouse.y < 638){///Click Conectar
                            //Buffer para recivir los datos del servidor
                            char buffer[1200];
                            bool tuTurno = false, waiting = false;
                            bool card0 = false, card1 = false, card2 = false, card3 = false, card4 = false;
                            bool card5 = false, card6 = false, card7 = false, card8 = false, card9 = false;
                            int tablero[10], intentos = 0, jugador;


                            if(!cargado){
                                cargado = true;
                                char IP[50];

                                //resolución de nombres para conectar al servidor
                                res = getaddrinfo(host, "25252", &hints, &lista);
                                if(res != 0){
                                    printf ("Error en la resoluciÃ³n de nombres: %s\n", gai_strerror (res));
                                    close (s);
                                    al_draw_bitmap(img_failConection, 350, 175, 0);
                                    al_flip_display();
                                    al_rest(EXIT_PAUSE);
                                    return EXIT_FAILURE;
                                }

                                save = lista;
                                struct sockaddr_in *cast;
                                while(lista != NULL){
                                    cast = (struct sockaddr_in *)lista->ai_addr;
                                    inet_ntop(AF_INET, &cast->sin_addr, IP, sizeof (IP));
                                    cout<<"Intentando conectar a "<<IP<<endl;
                                    server.sin_addr = cast->sin_addr;

                                    res = connect(s, (struct sockaddr *) &server, sizeof (struct sockaddr_in));
                                    if(res == 0){
                                        cout<<"Conexion exitosa"<<endl;
                                        break;
                                    }

                                    lista = lista->ai_next;
                                }

                                freeaddrinfo (save);
                                if (lista == NULL){
                                    cout<<"No se pudo realizar la conexion."<<endl;
                                    close(s);
                                    al_draw_bitmap(img_failConection, 350, 175, 0);
                                    al_flip_display();
                                    al_rest(EXIT_PAUSE);
                                    return EXIT_FAILURE;
                                }

                                //Recibir tablero  y que nÃºmero de jugador nos tocó
                                bzero(buffer, sizeof(buffer));
                                res = read(s, buffer, sizeof(buffer));
                                if(res > 0){
                                    buffer[res] = '\0';
                                    for(int i = 0; i < 10; i++){
                                        tablero[i] = (int)(buffer[i] - 48);
                                    }
                                    for(int i = 0; i < 10; i++){
                                        cout<<tablero[i]<<endl;
                                    }
                                }
                                else if(res == 0){
                                    cout<<"El servidor cerro la conxion."<<endl;
                                    close(s);
                                    return EXIT_FAILURE;
                                }
                                else if(errno == EWOULDBLOCK || errno == EAGAIN){
                                    continue;
                                }

                                cout<<buffer<<endl;

                                if(buffer[10] == '1'){
                                    tuTurno = true;
                                    waiting = true;
                                    jugador = 1;
                                    img_Tablero = al_load_bitmap("imgs/tablero_1.png");
                                }
                                else{
                                    jugador = 2;
                                    img_Tablero = al_load_bitmap("imgs/tablero_2.png");
                                }

                                //Hacer el socket no bloqueante
                                int flags;
                                flags = fcntl (s, F_GETFL);
                                flags = flags | O_NONBLOCK;
                                res = fcntl (s, F_SETFL, flags);
                                if(res < 0){
                                    perror("Error en fcntl()");
                                    close(s);
                                    return EXIT_FAILURE;
                                }
                            }
                            al_destroy_event_queue(event_queue);
                            event_queue = al_create_event_queue();

                            redraw = true;
                            bool gameOver = false;
                            int cards[10];
                            for(int i = 0; i < 10; i++)
                              cards[i] = 99;

                            int firstCard, secondCard;
                            int score = 0;
                            char buffScore[5];
                            char respuesta[50];
                            bool finish = false;

                            al_register_event_source(event_queue, al_get_display_event_source(display));
                            al_register_event_source(event_queue, al_get_mouse_event_source());
                            al_register_event_source(event_queue, al_get_keyboard_event_source());
                            al_register_event_source(event_queue, al_get_timer_event_source(timer));

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

                                if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && tuTurno && !waiting){

                                    if(event.mouse.x > 163 && event.mouse.x < 312 && event.mouse.y > 132 && event.mouse.y < 340 && intentos < 2 && !card0){///Carta 1
                                        cards[0] = 0;
                                        if(intentos == 0){
                                            card0 = true;
                                            firstCard = cards[0];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[0];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 342 && event.mouse.x < 491 && event.mouse.y > 132 && event.mouse.y < 340 && intentos < 2 && !card1){///Carta 2
                                        cards[1] = 1;
                                        if(intentos == 0){
                                            card1 = true;
                                            firstCard = cards[1];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[1];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 515 && event.mouse.x < 664 && event.mouse.y > 132 && event.mouse.y < 340 && intentos < 2 && !card2){///Carta 3
                                        cards[2] = 2;
                                        if(intentos == 0){
                                            card2 = true;
                                            firstCard = cards[2];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[2];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 699 && event.mouse.x < 848 && event.mouse.y > 132 && event.mouse.y < 340 && intentos < 2  && !card3){///Carta 4
                                        cards[3] = 3;
                                        if(intentos == 0){
                                            card3 = true;
                                            firstCard = cards[3];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[3];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 880 && event.mouse.x < 1029 && event.mouse.y > 132 && event.mouse.y < 340 && intentos < 2  && !card4){///Carta 5
                                        cards[4] = 4;
                                        if(intentos == 0){
                                            card4 = true;
                                            firstCard = cards[4];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[4];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 162 && event.mouse.x < 311 && event.mouse.y > 356 && event.mouse.y < 564 && intentos < 2 && !card5){///carta 6
                                        cards[5] = 5;
                                        if(intentos == 0){
                                            card5 = true;
                                            firstCard = cards[5];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[5];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 342 && event.mouse.x < 487 && event.mouse.y > 356 && event.mouse.y < 564 && intentos < 2 && !card6){///carta 7
                                        cards[6] = 6;
                                        if(intentos == 0){
                                            card6 = true;
                                            firstCard = cards[6];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[6];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 516 && event.mouse.x < 665 && event.mouse.y > 356 && event.mouse.y < 564 && intentos < 2  && !card7){///carta 8
                                        cards[7] = 7;
                                        if(intentos == 0){
                                            card7 = true;
                                            firstCard = cards[7];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[7];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 699 && event.mouse.x < 848 && event.mouse.y > 356 && event.mouse.y < 564 && intentos < 2  && !card8){///carta 9
                                        cards[8] = 8;
                                        if(intentos == 0){
                                            card8 = true;
                                            firstCard = cards[8];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[8];

                                        intentos++;
                                    }
                                    if(event.mouse.x > 880 && event.mouse.x < 1028 && event.mouse.y > 356 && event.mouse.y < 564 && intentos < 2 && !card9){///carta 10
                                        cards[9] = 9;
                                        if(intentos == 0){
                                            card9 = true;
                                            firstCard = cards[9];
                                        }
                                        else if(intentos == 1)
                                            secondCard = cards[9];

                                        intentos++;
                                    }
                                }

                                if(redraw && al_is_event_queue_empty(event_queue)){
                                    redraw = false;

                                    if(waiting){
                                        al_draw_bitmap(img_waiting, 350, 175, 0);
                                        al_flip_display();
                                    }
                                    else{
                                        sprintf(buffScore, "%i", score);
                                        al_draw_text(fontGame, al_map_rgb(0, 0, 0), 420, 590, ALLEGRO_ALIGN_LEFT, buffScore);
                                        al_flip_display();

                                        if(cards[0] == 0){
                                            al_draw_bitmap(img_Cards[tablero[0]], 163, 132, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 163, 132, 0);
                                            al_flip_display();
                                        }
                                        if(cards[1] == 1){
                                            al_draw_bitmap(img_Cards[tablero[1]], 342, 132, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 342, 132, 0);
                                            al_flip_display();
                                        }
                                        if(cards[2] == 2){
                                            al_draw_bitmap(img_Cards[tablero[2]], 515, 132, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 515, 132, 0);
                                            al_flip_display();
                                        }
                                        if(cards[3] == 3){
                                            al_draw_bitmap(img_Cards[tablero[3]], 699, 132, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 699, 132, 0);
                                            al_flip_display();
                                        }
                                        if(cards[4] == 4){
                                            al_draw_bitmap(img_Cards[tablero[4]], 880, 132, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 880, 132, 0);
                                            al_flip_display();
                                        }
                                        if(cards[5] == 5){
                                            al_draw_bitmap(img_Cards[tablero[5]], 162, 356, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 162, 356, 0);
                                            al_flip_display();
                                        }
                                        if(cards[6] == 6){
                                            al_draw_bitmap(img_Cards[tablero[6]], 342, 356, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 342, 356, 0);
                                            al_flip_display();
                                        }
                                        if(cards[7] == 7){
                                            al_draw_bitmap(img_Cards[tablero[7]], 515, 356, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 515, 356, 0);
                                            al_flip_display();
                                        }
                                        if(cards[8] == 8){
                                            al_draw_bitmap(img_Cards[tablero[8]], 699, 356, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 699, 356, 0);
                                            al_flip_display();
                                        }
                                        if(cards[9] == 9){
                                            al_draw_bitmap(img_Cards[tablero[9]], 880, 356, 0);
                                            al_flip_display();
                                        }else{
                                            al_draw_bitmap(img_Cards[DOWNCARD], 880, 356, 0);
                                            al_flip_display();
                                        }

                                        if(tuTurno){
                                            al_draw_text(fontGame, al_map_rgb(0, 0, 0), 650, 0, ALLEGRO_ALIGN_CENTRE, "Â¡Tu turno!");

                                            //Mandar nuestro turno
                                            if(intentos == 2){
                                                bzero(respuesta, 50);
                                                if(tablero[firstCard] == tablero[secondCard]){
                                                    cout<<"Atinaste"<<endl;
                                                    score++;
                                                    sprintf(respuesta, "%i%i%i%i", 5, jugador,firstCard, secondCard);
                                                    cout<<"Enviando: "<<respuesta<<endl;
                                                    res = send(s, respuesta, sizeof(respuesta), 0);
                                                    if(res < 0){
                                                        perror("Error en send()");
                                                        close(s);
                                                        return EXIT_FAILURE;
                                                    }
                                                }
                                                else{
                                                    cout<<"No atinaste"<<endl;
                                                    sprintf(respuesta, "%i%i%i%i", 5, jugador,firstCard, secondCard);
                                                    cout<<"Enviando: "<<respuesta<<endl;
                                                    res = send(s, respuesta, sizeof(respuesta), 0);
                                                    if(res < 0){
                                                        perror("Error en send()");
                                                        close(s);
                                                        return EXIT_FAILURE;
                                                    }
                                                    cards[firstCard] = 99;
                                                    cards[secondCard] = 99;
                                                }

                                                al_rest(0.2);
                                                intentos = 0;
                                                tuTurno = false;
                                                card0 = false;card1 = false;card2 = false;card3 = false;card4 = false;
                                                card5 = false;card6 = false;card7 = false;card8 = false;card9 = false;

                                                al_draw_bitmap(img_Tablero, 0, 0, 0);
                                                al_flip_display();
                                            }
                                        }
                                        else{
                                            al_draw_text(fontGame, al_map_rgb(0, 0, 0), 670, 0, ALLEGRO_ALIGN_CENTRE, "Esperando...");

                                            //Leer las cartas del otro jugador
                                            res = recv(s, buffer, sizeof(buffer), 0);
                                            if(res > 0){
                                                buffer[res] = '\0';
                                                cout<<"Se recibieron las cartas: "<<buffer[0]<<" y "<<buffer[1]<<endl;

                                                //Informar si el otro jugador abandonó la partida
                                                if(strcmp(buffer, "7777") == 0){
                                                    al_draw_bitmap(img_leftGame, 350, 175, 0);
                                                    al_flip_display();
                                                    al_rest(EXIT_PAUSE);
                                                    close(s);

                                                    return EXIT_SUCCESS;
                                                }

                                                if(buffer[4] == 'W'){
                                                    int number1 = (int)(buffer[2] - 48), number2 = (int)(buffer[3] - 48);
                                                    al_draw_bitmap(img_youWin, 350, 175, 0);
                                                    al_flip_display();
                                                    sprintf(buffScore, "%i - %i", number1, number2);
                                                    al_draw_text(fontGame, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, buffScore);
                                                    al_flip_display();

                                                    al_rest(EXIT_PAUSE);
                                                    gameOver = true;
                                                    salirServerAddr = true;
                                                    salir = true;
                                                }

                                                if(buffer[4] == 'L'){
                                                    int number1 = (int)(buffer[2] - 48), number2 = (int)(buffer[3] - 48);
                                                    al_draw_bitmap(img_youLose, 350, 175, 0);
                                                    al_flip_display();
                                                    sprintf(buffScore, "%i - %i", number1, number2);
                                                    al_draw_text(fontGame, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, buffScore);
                                                    al_flip_display();

                                                    al_rest(EXIT_PAUSE);
                                                    gameOver = true;
                                                    salirServerAddr = true;
                                                    salir = true;
                                                }

                                                int c1, c2;
                                                c1 = (int)(buffer[0] - 48);
                                                c2 = (int)(buffer[1] - 48);

                                                if(tablero[c1] == tablero[c2]){
                                                    switch(c1){
                                                        case 0:
                                                            cards[0] = 0;
                                                            break;
                                                        case 1:
                                                            cards[1] = 1;
                                                            break;
                                                        case 2:
                                                            cards[2] = 2;
                                                            break;
                                                        case 3:
                                                            cards[3] = 3;
                                                            break;
                                                        case 4:
                                                            cards[4] = 4;
                                                            break;
                                                        case 5:
                                                            cards[5] = 5;
                                                            break;
                                                        case 6:
                                                            cards[6] = 6;
                                                            break;
                                                        case 7:
                                                            cards[7] = 7;
                                                            break;
                                                        case 8:
                                                            cards[8] = 8;
                                                            break;
                                                        case 9:
                                                            cards[9] = 9;
                                                            break;
                                                    }

                                                    switch(c2){
                                                        case 0:
                                                            cards[0] = 0;
                                                            break;
                                                        case 1:
                                                            cards[1] = 1;
                                                            break;
                                                        case 2:
                                                            cards[2] = 2;
                                                            break;
                                                        case 3:
                                                            cards[3] = 3;
                                                            break;
                                                        case 4:
                                                            cards[4] = 4;
                                                            break;
                                                        case 5:
                                                            cards[5] = 5;
                                                            break;
                                                        case 6:
                                                            cards[6] = 6;
                                                            break;
                                                        case 7:
                                                            cards[7] = 7;
                                                            break;
                                                        case 8:
                                                            cards[8] = 8;
                                                            break;
                                                        case 9:
                                                            cards[9] = 9;
                                                            break;
                                                    }
                                                }

                                                tuTurno = true;
                                                al_draw_bitmap(img_Tablero, 0, 0, 0);
                                                al_flip_display();
                                            }
                                            else if(res == 0){
                                                cout<<"El servidor cerro la conxion."<<endl;
                                                al_draw_bitmap(img_closedServer, 350, 175, 0);
                                                al_flip_display();
                                                al_rest(EXIT_PAUSE);
                                                close(s);
                                                return EXIT_SUCCESS;
                                            }
                                            else if(errno == EWOULDBLOCK || errno == EAGAIN){
                                                continue;
                                            }
                                            else{
                                                perror("Error en recv() esperando turno:");
                                                close(s);
                                                return EXIT_FAILURE;
                                            }
                                        }
                                    }

                                    //Recibir codigos
                                    res = recv(s, buffer, sizeof(buffer), 0);
                                    if(res > 0){
                                        buffer[res] = '\0';
                                        cout<<"Se recibió: "<<buffer<<endl;
                                        if(strcmp(buffer, "8888") == 0){
                                            waiting = false;
                                            al_draw_bitmap(img_Tablero, 0, 0, 0);
                                            al_flip_display();
                                        }

                                        if(strcmp(buffer, "7777") == 0){
                                            al_draw_bitmap(img_leftGame, 350, 175, 0);
                                            al_flip_display();
                                            al_rest(EXIT_PAUSE);
                                            close(s);

                                            return EXIT_SUCCESS;
                                        }

                                        if(buffer[4] == 'L'){
                                            int number1 = (int)(buffer[2] - 48), number2 = (int)(buffer[3] - 48);
                                            al_draw_bitmap(img_youLose, 350, 175, 0);
                                            al_flip_display();
                                            sprintf(buffScore, "%i - %i", number1, number2);
                                            al_draw_text(fontGame, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, buffScore);
                                            al_flip_display();

                                            al_rest(EXIT_PAUSE);
                                        }

                                        if(buffer[4] == 'W'){
                                            int number1 = (int)(buffer[2] - 48), number2 = (int)(buffer[3] - 48);
                                            al_draw_bitmap(img_youWin, 350, 175, 0);
                                            al_flip_display();
                                            sprintf(buffScore, "%i - %i", number1, number2);
                                            al_draw_text(fontGame, al_map_rgb(0, 0, 0), 600, 360, ALLEGRO_ALIGN_CENTRE, buffScore);
                                            al_flip_display();

                                            al_rest(EXIT_PAUSE);
                                        }
                                    }
                                    else if(res == 0){
                                        cout<<"El servidor cerro la conxion."<<endl;
                                        al_draw_bitmap(img_closedServer, 350, 175, 0);
                                        al_flip_display();
                                        al_rest(EXIT_PAUSE);
                                        close(s);

                                        return EXIT_SUCCESS;
                                    }
                                    else if(errno == EWOULDBLOCK || errno == EAGAIN){
                                        continue;
                                    }
                                    else{
                                        perror("Error en recv() manejo de errores:");
                                        close(s);
                                        return EXIT_FAILURE;
                                    }
                                }
                            }
                        }

                    }///Fin mouse down pantalla getIP

                }
            }//Fin click comenzar
            if(event.mouse.x > 752 && event.mouse.x < 1031 && event.mouse.y > 560 && event.mouse.y < 637)//Click Salir
                salir = true;
        }

    }//End main looá¹•

    destroyAll();
    close(s);

    return 0;
}
