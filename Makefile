all: serial threads clone fork

hola1: Practica 3/serial.c
	gcc -o bin/serial Practica 3/serial.c
	

hola2: Practica 3/threads.c
	gcc -o bin/threads Practica 3/threads.c -lpthread
	

hola3: Practica 3/clone.c
	gcc -o bin/clone Practica 3/clone.c
	
	
hola4: Practica 3/fork.c
	gcc -o bin/fork Practica 3/fork.c
	

clean:
	rm bin/serial bin/threads bin/clone bin/fork  