Para ejecutar en Windows agregar esto a Build Options... -> Linker settings:
liballegro-5.0.10-monolith-mt.a

eliminar el archivo main.o en la carpeta Debug

Para compilar en Linux eliminar el archivo main.o en la carpeta Debug y volver a compilar el proyecto.
Quitar de Linker Settings: liballegro-5.0.10-monolith-mt.a *si lo tiene

