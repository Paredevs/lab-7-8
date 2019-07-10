#include <stdio.h>
#include <stdlib.h >
#include <math.h>
#define T 200


typedef struct _nodo{
	
	int claves[2*T-1];
	int hijos[2*T];
	int eshoja;
	int cantidadactual;
	int MiNombre;	
	
}Nodo;

typedef struct _arbol{
	int raiz;
	int cantidadNodos;
}Arbol;
//Cormen asume que los arreglos parten en 1

Nodo *CrearNodo(int nombreNodo){

	Nodo *Nuevo_nodo;
	Nuevo_nodo=malloc(sizeof(Nodo));
	Nuevo_nodo->MiNombre=nombreNodo;
	return(Nuevo_nodo);
	
}

int GuardarNodo(Nodo *nodo){

	FILE *estructura;
	if(nodo==NULL){
		return -1;
	}
	char nombreNodo[10];
	if(estructura==NULL){
		return 0;
	}else{
		sprintf(nombreNodo,"%i",nodo->MiNombre);
		estructura=fopen(nombreNodo,"wb");
		fwrite(nodo,sizeof(Nodo),1,estructura);
		printf("Nodo Creado en el disco duro\n");
		}
	fclose(estructura);
	
}

Nodo *leeNodo(int nombre){
	
	FILE *estructura;
	Nodo *nodoLeido;
	nodoLeido=malloc(sizeof(Nodo));
	char nombreNodo[10];
	sprintf(nombreNodo,"%i",nombre);
	estructura=fopen(nombreNodo,"rb");
	if(estructura==NULL){
		printf("Error\nNo existe el nodo");
		return 0;
	}else{
		printf("\nNodo leido en el disco duro\n");
	}
	fread(nodoLeido,sizeof(Nodo),1,estructura);
	return(nodoLeido);
	
}

Arbol *CreaArbol(){
	
	Arbol *arbol;
	arbol=malloc(sizeof(Arbol));
	arbol->raiz=NULL;
	return arbol;
	
}

int CreaArchivoPrincipal(Arbol *arbol){
	
	FILE *principal;
	char direccion[10]="Arbol";
	fwrite(arbol->raiz,sizeof(int),1,principal);
	fwrite(arbol->cantidadNodos,sizeof(int),1,principal);
	fclose(principal);
	
	
	
}
Nodo *insertaClave(Arbol *arbol,int clave){

	arbol->cantidadNodos++;
	int nombreNodo=arbol->cantidadNodos;	
	Nodo *r=leeNodo(arbol->raiz);
	if(r->cantidadactual==2*T-1){
		Nodo *s=CrearNodo(nombreNodo);
		printf("NodoCreado");
		arbol->raiz=s->MiNombre;
		s->eshoja=0;
		s->cantidadactual=0;
		s->hijos[0]=r->MiNombre;
		divideHijoArbolB(s,0);
		insertarNoLLenoArbolB(s,clave);
	}else{
		insertaNoLLenoArbolB(r,clave);
	}
	
	
}

int divideHijoArbolB(Nodo *s,int clave){
	
	Nodo *z,*y;
	int j;
	z=CrearNodo(s->MiNombre+1);
	y=leeNodo(s->hijos[clave]);
	y=s->hijos[clave];
	for(j=0;j<T-1;j++){
		
	
}
	z->hijos[j]=y->hijos[j+T];
	z->cantidadactual=T-1;
	for(j=0;j<T-1;j++){
		z->claves[j]=y->claves[j+T];
	}
	if(y->hijos){
		for(j=0;j<T;j++){
			z->hijos[j]=y->hijos[j+T];
		}	
	} 
	y->cantidadactual=T-1;
	for(j=s->cantidadactual+1;j>clave+1;j--){
		s->hijos[j+1]=s->hijos[j];
	}
	s->hijos[clave+1]=z;
	for(j=s->cantidadactual;j>clave;j--){
		s->claves[j+1]=s->claves[j];
	}
	
	s->claves[clave]=y->claves[T];
	s->cantidadactual=s->cantidadactual+1;
	GuardarNodo(y);
	GuardarNodo(z);
	GuardarNodo(s);
	}
	


int insertarNoLLenoArbolB(Nodo *s,int clave){
	
	int i;
	i=s->cantidadactual;
	if(s->eshoja){
		while(i>=1||clave<s->claves[i]){
			s->claves[i+1]=s->claves[i];
			i=i-1;
		}
		s->claves[i+1]=clave;
		s->cantidadactual=s->cantidadactual++;
		GuardarNodo(s);
	}else{
		while(i>=1||clave<s->claves[i]){
			i=i-1;
		}
	i=i+1;
	leeNodo(s->hijos[i]);
		if(s->hijos[i]==2*T-1){
			divideHijoArbolB(s,i);
			if(clave>s->claves[i]){
				i=i+1;
			}
		}
	insertarNoLLenoArbolB(s->claves[i],clave);	
		
	
	
}

}

int insertaNoLLenoArbolB(Nodo *r,int clave){
	
}

int imprimeNodo(Nodo *nodoLeido){
	
	printf("Nombre del nodo: %i \n",nodoLeido->MiNombre);
	int i=0;
	for(i=0;i<(2*T-1);i++){
		printf("Claves:%i \n",nodoLeido->claves[i]);
		printf("hijos: %i \n",nodoLeido->hijos[i]);
	}
	
}
