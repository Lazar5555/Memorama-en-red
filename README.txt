							MEMORAMA EN RED

Memorama en red es un videojuego que consiste en el tradicional juego de memorama. El programa permite a los los usuarios jugar en la red local con el uso de sockets de red. Inicialmente para plataformas LINUX utilizando Allegro 5.

-Instalación de Allegro 5 en WINDOWS:
	http://creatusjuegosdecero.webege.com/index.php?topic=115.0

-Instalación de Allegro 5 en LINUX:
	https://emman31.wordpress.com/2013/01/21/ubuntu-12-04-installing-allegro-5-on-codeblocks/comment-page-1/
	
-Compilar Allegro 5 desde CodeBlocks en WINDOWS:
	Agregar a Build Options --> Linker settings:
		"liballegro-5.0.10-monolith-mt.a"

-Compilar  Allegro 5 desde CodeBlock en LINUX:
	Quitar de Linker Settings "liballegro-5.0.10-monolith-mt.a" (si lo tiene) y agregara las librerias .so de allegro a 		linker settings.

-Compilar desde la terminal LINUX:
	g++ main.cpp `pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0`
