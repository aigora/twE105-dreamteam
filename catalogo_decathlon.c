#include <stdio.h>
#include <string.h>
#define NUMCLIENTES 20
#define TAMCAT 50
#define TAMDESCUENTOS 10
#define TAMTARJETA 13

//ESTRUCTURAS:
struct registro{
	char usuario[20];
	char contrasena[20];
};

struct producto {
	int cantidad;
	int numero;
	char tipo[20];
	char nombre[50];
	float precio;
};

struct ahorro{
	int numero;
	char nombre[20];
	int porcentaje;
};

//FUNCIONES:
char menu();
void registro(struct registro clientes[]);
void iniciarsesion(int *exito);
void leerFichero(char nombreFichero[], struct producto vector[], int *nproductos);
void anadirFichero(char nombreFichero[], struct producto vector[], int nproductos);
void leerDescuentos(char nombreFichero[],struct ahorro ofertas[], int *ndescuentos);
void pagoFinal(struct producto carrito[],struct ahorro ofertas[], int tamano);

//PROGRAMA:
void main(){
	int opcion = 0, n = 0, sesion = 0;
	char entrar;
	struct registro clientes[NUMCLIENTES];
	struct producto catalogo[TAMCAT];
	struct producto carrito[TAMCAT];
	struct ahorro ofertas[TAMDESCUENTOS];
	char contrasena[20]; //Se usa solo para entrar como admin
	int i = 0, nprod, nelemento = 0, ncarrito = 0, ndescuentos;
	int tarjeta[TAMTARJETA]; //Se usa para comprobar que se utiliza una tarjeta de credito con 12 numeros
	int longitud;//Se usa para comprobar que se utiliza una tarjeta de credito con 12 numeros
	
	//Bucle para poder registrarse e iniciar sesion:
	while(sesion == 0){
		printf("\n\t\t\t\t\t\t ���BIENVENIDO!!! \n");
		printf("\tHa accedido a la tienda online del decathlon, aqui podra registrarse o iniciar sesion si ya es un cliente,\n\tespero que sea de su agrado...\n");
		printf("\tPara registrarse o iniciar sesion selecione: R(registrarse) o I(iniciar sesion)\n");
		scanf("%c", &entrar);
		
		switch(entrar){
			case 'R':
			case 'r':
				registro(clientes);
				printf(" Perfecto, ahora inicie sesion por favor.\n");
				iniciarsesion(&sesion);
				system("pause");
				break;
			case 'I':
			case 'i':
				iniciarsesion(&sesion);
				system("pause");
				break;
		}
	}	
	//Bucle del menu:
	while(1){
		system("cls");
		switch(menu()){
			case'1':
				printf("El catalogo actual es el siguiente: \n");
				leerFichero("catalogo.txt", catalogo, &nprod);
				system("pause");
				getchar();
				break;
				
			case'2':
				printf("Aqui podra a�adir productos a su carrito.\n\t Inserte el numero del producto que desee: \n");
		 		while (1) {
					system("cls");
					printf("El catalogo actual es el siguiente:\n");
					leerFichero("catalogo.txt", catalogo, &nprod);
					printf("\nIntroduzca el numero del producto deseado: ");
					scanf("%d", &nelemento);
					if (nelemento > nprod || nelemento < 1) {
						printf("Opcion no valida.\n");
						system("pause");
					}
					else {
						carrito[ncarrito].numero = ncarrito + 1;
						strcpy(carrito[ncarrito].tipo, catalogo[nelemento - 1].tipo);
						strcpy(carrito[ncarrito].nombre, catalogo[nelemento - 1].nombre);
						carrito[ncarrito].precio = catalogo[nelemento - 1].precio;
						ncarrito++;
						printf("Si quiere anadir otro producto pulse '1', en caso contrario pulse '0': ");
						scanf("%d", &opcion);
						if (opcion == 0) {
							getchar();
							break;
						}
						else if (opcion == 1) {

						}
						else {
							printf("La opcion no es valida\n");
							system("pause");
						}
					}
				}
				getchar();
				system("pause");
				break;
				
			case'3':
				printf("Aqui podra retirar productos del carrito siempre y cuando no este vacio.\n\t Inserte el numero del producto que desea retirar: \n");
					system("cls");
			if (ncarrito == 0) {
				printf("Su carrito esta vacio.\n");
				system("pause");
				getchar();
				break;
			}
			if (ncarrito == 1) {
				printf("Su carrito es el siguiente: \n");
				for (i = 0; i < ncarrito; i++) {
					printf("\t%d\t %s %s %.2f\n", carrito[i].numero, carrito[i].tipo, carrito[i].nombre, carrito[i].precio);
				}
				printf("Para eliminar el unico elemento de su carrito pulse '1', en caso contrario, '0': ");
				scanf_s("%d", &opcion);
				if (opcion == 1) {
					ncarrito--;
					printf("Elemento eliminado del carrito.\n");
					system("pause");
					getchar();
					break;
				}
				else if (opcion == 0) {
					getchar();
					break;
				}
				else {
					printf("Opcion no valida.\n");
					system("pause");
					getchar();
					break;
				}
			}
			printf("Su carrito es el siguiente: \n");
			for (i = 0; i < ncarrito; i++) {
				printf("\t%d\t %s %s %.2f\n", carrito[i].numero, carrito[i].tipo, carrito[i].nombre, carrito[i].precio);
			}
			printf("Introduzca el numero del producto que desea retirar: ");
			scanf_s("%d", &nelemento);
			if (nelemento < 1 || nelemento > ncarrito) {
				printf("Opcion no valida\n");
				system("pause");
				getchar();
				break;
			}
			for (i = nelemento - 1; i < ncarrito; i++) {
				strcpy(carrito[nelemento - 1].nombre, carrito[nelemento].nombre);
				strcpy(carrito[nelemento - 1].tipo, carrito[nelemento].tipo);
				carrito[nelemento - 1].precio = carrito[nelemento].precio;
			}
			ncarrito--;
			printf("Elemento eliminado del carrito.\n");
				getchar();
				system("pause");
				break;
				
			case'4':
				printf("Este es su carrito de la compra hasta el momento... \n");
			if (ncarrito == 0) {
				getchar();
				printf("El carrito esta vacio.\n");
				system("pause");
				getchar();
				break;
			}
			printf("Su carrito es el siguiente: \n");
			for (i = 0; i < ncarrito; i++) {
				printf("\t%d. %s - %s = %.2f\n", carrito[i].numero, carrito[i].tipo, carrito[i].nombre, carrito[i].precio);
			}
				getchar();
				system("pause");
				break;
				
			case'5':
				printf("Aqui podra pagar los productos deseados con tarjeta.\n\t Por favor, introduzca el numero de su tarjeta de credito: \n");
				scanf("%s", tarjeta, TAMTARJETA);
				longitud = strlen(tarjeta);//medimos la longitud para que cumpla que es una tarjeta de credito con 12 numeros
				printf("Esta tarjeta tiene %d caracteres\n", longitud);
				if(longitud == 12){
					printf("El numero de su tarjeta es: %s \n", tarjeta, TAMTARJETA);
					//Aqui metemos la funcion de pagar
					pagoFinal(carrito, ofertas, ncarrito);
				}
				else{
					printf("Lo siento, pero no se ha podido reconocer la tarjeta. Intentelo de nuevo...\n");
				}
				getchar();
				system("pause");
				break;
				
			case'6':
				printf("Aqui podra visualizar las ofertas disponibles que hay en nuestra tienda. \n\t DESCUENTOS: \n");
				leerDescuentos("descuentos.txt", ofertas, &ndescuentos);
				getchar();
				system("pause");
				break;
				
			case'7':
				printf("Esperamos volver a verle...\n");
				return;
				break;
				
			case'8':
				printf("Aqui mientras seas administrador podras anadir productos de nuestra tienda. \n");
				printf("Introduzca la contrasena de administrador:");
				scanf("%s", contrasena, 20);
				if(strcmp(contrasena, "administrador99") == 0){
					printf("\n Contrasena correcta.");
					printf("\n\nEste es el catalogo actual:\n");
					leerFichero("catalogo.txt", catalogo, &nprod);//inicializo nprod, si no se ha inicializado ya
					printf("\n\tBienvenido administrador siga los siguientes pasos para anadir el producto que desee... \n");
					anadirFichero("catalogo.txt", catalogo, nprod);
					printf("\nProducto anadido correctamente\n");
					leerFichero("catalogo.txt", catalogo, &nprod); //actualizo nprod
					system("pause");
					system("cls");
					getchar();
				}
				else{
					printf("Contrasena incorrecta. Vuelva a intentarlo...\n");
				}
				getchar();
				system("pause");
				break;
				
			default:
				printf("La opcion no es valida.\n");
				system("pause");
				break;
			
		}
	}
}

//funcion para mostrar el menu de opciones
char menu() {
	char opcion;

	printf("Bienvenido, seleccione una de estas opciones: \n");
	printf("\t1 - Para ver el catalogo(precios, productos...)\n");
	printf("\t2 - Para anadir al carrito los productos deseados...\n");
	printf("\t3 - Para retirar elementos del carrito...\n");
	printf("\t4 - Para ver el estado del carrito de la compra...\n");
	printf("\t5 - Para pagar los productos introducidos en el carrito...\n");
	printf("\t6 - Para ver la lista de descuentos disponibles...\n");
	printf("\t7 - Para salir del programa...\n");
	printf("\t8 - Para anadir productos al catalogo...(debe ser ADMINISTRADOR)\n");
	scanf_s("%c", &opcion);
	return opcion;
}

//funcion para registrarse en el programa
void registro(struct registro clientes[]){
	FILE*pf;
	pf =fopen("registro.txt", "a");
	
	if(pf == NULL){
		printf("El fichero no se ha abierto correctamente.\n");
		return -1;
	} 
	else{
		getchar();
		printf("Introduzca su usuario:");
		gets(clientes[0].usuario);
		printf("\nIntroduzca su contasena:");
		gets(clientes[0].contrasena);
		
		fprintf(pf, "%s , %s\n", clientes[0].usuario, clientes[0].contrasena);
		fclose(pf);
		printf("\n\n Muchas gracias por haberse registrado por primera vez en nuestros servidores\n espero que disfrute de su compra...\n");	
	}
}
//funcion para iniciar sesion
void iniciarsesion(int *exito){
	
	struct registro clientes[NUMCLIENTES];
	int i = 0, usuarios = 0, registro = 0;
	char usuario[20], contrasena[20];
	
	FILE*pf;
	pf = fopen("registro.txt", "r");
	
	if(pf == NULL){
		printf("El fichero no se ha abierto correctamente...\n");
		return -1;
	}
	else{
		while(fscanf(pf, "%s , %s", clientes[i].usuario, clientes[i].contrasena) != EOF){
			i++;
			usuarios++;
		}
		fclose(pf);
		getchar();
		printf("Hay registrados %d usuarios\n", usuarios);
		
		printf("Por favor, introduzca un usuario y contrasena menores de 20 caracteres.\n");
		printf("\nUsuario:");
		gets(usuario);
		printf("\nContrasena:");
		gets(contrasena);
		printf("\n Muchas gracias. Comprobaremos si esta registrado...\n");
		//Comprobacion del registro para poder iniciar sesion
		for(i = 0; i < usuarios; i++){
			if(strcmp(usuario, clientes[i].usuario) == 0 && strcmp(contrasena, clientes[i].contrasena) == 0){
				printf("Perfecto acaba de iniciar sesion correctamente, que disfrute de sus compras...\n");
				*exito = 1;
				registro = 1;
			}
		}
		if(registro == 0){
			printf("Lo siento pero no esta registrado en nuestros servidores. Por favor vuelva a intentarlo...\n");
		}
	}
}

//funcion para leer el fichero del catalogo
void leerFichero(char nombreFichero[], struct producto vector[], int *nproductos){
	int i=0;
	FILE*pf;
	pf = fopen(nombreFichero, "r");
	
	if(pf == NULL){
		printf("El fichero no se ha abierto correctamente...\n");
		return -1;
	}
	else{
		while(fscanf(pf,"%d %s %s %f", &vector[i].numero, vector[i].tipo, vector[i].nombre, &vector[i].precio) != EOF){
			printf("\t%d. %s - %s = %.2f \n", vector[i].numero, vector[i].tipo, vector[i].nombre, vector[i].precio);
			i++;
		}
		fclose(pf);
		*nproductos = i;
	}
}

//funcion para a�adir al fichero
void anadirFichero(char nombreFichero[], struct producto vector[], int nproductos) {
	vector[nproductos].numero = nproductos + 1;
	printf("\n\tIntroduce la categoria del producto: ");
	scanf("%s", vector[nproductos].tipo, 20);
	printf("\n\tIntroduce el nombre del producto: ");
	scanf("%s", vector[nproductos].nombre, 50);
	printf("\n\tIntroduce el precio del producto: ");
	scanf("%f", &vector[nproductos].precio);

	FILE * fichero;

	fichero = fopen(nombreFichero, "a");
	if(fichero == NULL){
		printf("No se ha abierto correctamente el fichero...\n");
	}
	else{
		fprintf(fichero, "%d %s %s %.2f\n", vector[nproductos].numero, vector[nproductos].tipo, vector[nproductos].nombre, vector[nproductos].precio);	
	}
	fclose(fichero);
}

//Funcion para visualizar la lista de descuentos disponible
void leerDescuentos(char nombreFichero[], struct ahorro ofertas[], int *ndescuentos){
	int i=0;
	FILE*pf;
	pf = fopen(nombreFichero, "r");
	
	if(pf == NULL){
		printf("El fichero no se ha abierto correctamente...\n");
		return -1;
	}
	else{
		while(fscanf(pf,"%d %s %d", &ofertas[i].numero, ofertas[i].nombre, &ofertas[i].porcentaje ) != EOF){
			printf("\t%d. %s --> %d por ciento \n", ofertas[i].numero, ofertas[i].nombre, ofertas[i].porcentaje);
			i++;
		}
		fclose(pf);
		*ndescuentos = i;
	}
}

//Funcion para realizar el pago de los productos del carrito
void pagoFinal(struct producto vector[], struct ahorro ofertas[], int tamano){
	int i = 0, opcion = 0, ndescuentos;
	float precioFinal = 0;
	int elemento;
	
	if(tamano == 0){
		printf("\t Actualmente el carrito esta vacio, anada algun producto por favor...\n");
	}
	else{
		while(opcion == 0){
			while(i<tamano){
				precioFinal += vector[i].precio;
				i++;
			}
			printf("\n\nEl precio que tiene que pagar es: %.2f \n", precioFinal);
			printf("\nSi desea aplicar algun descuento disponible en nuestra lista pulse '1'. En caso contrario, pulse '2': ");
			scanf("%d", &opcion);
			
			if(opcion == 1){
					printf("\nAVISO: Solo podra usar un descuento de los disponibles.\n");
					printf("Esta es la lista disponible de descuentos: \n");
					leerDescuentos("descuentos.txt", ofertas, &ndescuentos);
					printf("Seleccione el descuento que quiere aplicar: ");
					scanf("%d", &elemento);
					switch(elemento){
						case 1:
							printf("\nPerfecto, ha seleccionado el descuento %s, se le aplicara un %d por ciento de descuento...\n", ofertas[0].nombre, ofertas[0].porcentaje);
							precioFinal = precioFinal*0.5;
							printf("\n\n\tSu pago final es de: %.2f \n", precioFinal);
							return 1;
							break;
					
						case 2:
							printf("\nPerfecto, ha seleccionado el descuento %s, se le aplicara un %d por ciento de descuento...\n", ofertas[1].nombre, ofertas[1].porcentaje);
							precioFinal -= precioFinal*0.1;
							printf("\n\n\tSu pago final es de: %.2f \n", precioFinal);
							return 1;
							break;
					
						case 3:
							printf("\nPerfecto, ha seleccionado el descuento %s, se le aplicara un %d por ciento de descuento...\n", ofertas[2].nombre, ofertas[2].porcentaje);
							precioFinal -= precioFinal*0.35;
							printf("\n\n\tSu pago final es de: %.2f \n", precioFinal);
							return 1;
							break;
					}
			}
			else if(opcion == 2){
					printf("\nEl precio que tiene que pagar es: %.2f \n", precioFinal);
			}	
		}
	} 
}



