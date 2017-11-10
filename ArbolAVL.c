//Enunciado:
/*Traductor
Las diferencias entre los distintos idiomas siempre han conllevado un sesgo en las comunicaciones de las
diferentes culturas. Las personas,ante este impedimento de no poder transmitir ideas de forma que se
comprendan fácilmente, intentan capacitarse para poder dominar otros idiomas. Este aprendizaje
muchas veces es complicado dado a la cantidad de lenguajes existentes, por lo que se da prioridad a los
idiomas más utilizados o más relevantes según el área de interés del individuo.
Al estar estudiando un nuevo idioma, es inevitable hacer comparaciones con los idiomas ya conocidos,
buscando patrones en la sintaxis y equivalencias entre las palabras. Pero debido a que esto implica un
arduo trabajo de memorización de vocabulario no siempre es simple. Es por esto que los traductores
suelen ser una herramienta de apoyo en estos puntos, entregando una traducción que las personas
pueden ver en un lenguaje conocido.
En este laboratorio se busca implementar un traductor entre dos idiomas.
Para esto se requiere la utilización de la estructura de datos árbol para agilizar la búsqueda de una traducción.
Se debe considerar que los nodos deben tener la siguiente información:
   •Palabra en español.
   •Palabra en otro idioma.
   •Significado de la palabra en español.
   •Significado de la palabra en otro idioma.
   •Puntero español a nodo izquierdo.
   •Puntero español a nodo derecho.
   •Puntero otro idioma a nodo izquierdo.
   •Puntero otro idioma a nodo derecho.
Donde los punteros indican los hijos de un cierto nodo, para este árbol en particular se requiere que los
nodos se encuentren ordenados alfabéticamente, los “Punteros español” indican cómo se encuentra ordenado el
árbol según las palabras en español, mientras que los “Punteros otro idioma” indican cómo se encuentra ordenado
el árbol en ese  idioma. Es decir, se debe implementar un único árbol, pero que será equivalente a dos árboles
ordenados alfabéticamente en sus respectivos idiomas.
Por ejemplo, al insertar en el árbol las palabras Azul/Blue, Rojo/Red y Verde/Green en ese orden, da como
resultado el árbol desde la perspectiva del español. (Imagenes de Ejemplo en el enunciado).

Para  este  laboratoio  se  requiere  que  implemente  un  programa  que  reciba  un  archivo  de  texto  llamado
“Diccionario.in” y que genere un árbol AVL a partir de este. El programa debe permitir:
Consultar por una palabrajunto su idioma y entregar su traducción.
Consultar por el significado de una palabra.
Entregar la información de todo el árbol en orden alfabéticoen español o inglés
(según indique el usuario) en una archivo llamado “Palabras.out”. Entregando la siguiente información por cada nodo:
Palabra_en_español Palabra_en_Otro (Hijo_izquierdo_en_español, Hijo_derecho_en_español) –
(Hijo_izquierdo_en_Otro, Hijo_derecho_en_inglés)

Fecha de entrega: 26/11/2017 hasta las 23:30 hrs
*/

//Algoritmos:
//Página 106.
/*HIJO_IZQUERDO(T: árbol): árbol
  Si T == NULO:
    Devolver NULO
  Devolver T.hijoIzquierdo
HIJO_DERECHO(T: árbol): árbol
  Si T == NULO:
    Devolver NULO
  Devolver T.hijoDerecho
//Página 112.
EQUILIBRAR(T: árbol): árbol
   diferencia = DIFERENCIA_ALTURAS(T)
   Si diferencia == 2:
      Si DIFERENCIA_ALTURAS(HIJO_IZQUERDO(T)) < 0:
         T.hijoIzquierdo = ROTAR_IZQUIERDA(HIJO_IZQUERDO(T))
      Devolver ROTAR_DERECHA(T)
   Si diferencia == -2:
      Si DIFERENCIA_ALTURAS(HIJO_DERECHO(T)) > 0:
         T.hijoDerecho = ROTAR_DERECHA(HIJO_DERECHO(T))
      Devolver ROTAR_IZQUIERDA(T)
   Devolver T

DIFERENCIA_ALTURAS(T: árbol): entero
   Devolver ALTURA(HIJO_IZQUERDO(T)) - ALTURA(HIJO_DERECHO(T))

ALTURA(T: árbol): entero
   Si T == NULO:
      Devolver NULO
   Si HIJO_IZQUERDO(T) == NULO && HIJO_DERECHO(T) == NULO:
      Devolver 0
   alturaIzquierda = ALTURA(HIJO_IZQUERDO(T))
   alturaDerecha = ALTURA(HIJO_DERECHO(T))

   Si alturaIzquierda > alturaDerecha:
      Devolver 1 + alturaIzquierda
   Devolver 1 + alturaDerecha

ROTAR_DERECHA(T: árbol): árbol
   raíz = HIJO_IZQUERDO(T)
   T.hijoIzquierdo = HIJO_DERECHO(raíz)
   raíz.hijoDerecho = T
   Devolver raíz
ROTAR_IZQUIERDA(T: árbol): árbol
   raíz = HIJO_DERECHO(T)
   T.hijoDerecho = HIJO_IZQUERDO(raíz)
   raíz.hijoIzquierdo = T
   Devolver raíz
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct AdelsonVelskiiLandis{
   int alturaElemento;
   char palabraEspanhol[51];
   char palabraOtro[51];
   char definicion[501];
   struct AdelsonVelskiiLandis* hijoDerechoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoDerechoPalabraOtro;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraOtro;
}AVL;

int largoArbol = 0; //Largo del árbol.
int contador = 0; //Contador usado en la función recorrerArbol_Inorden - roamTree_Inorden.

AVL* crearElemento(char palabraEspanhol[], char palabraOtro[], char definicion[]){
   AVL* elemento = (AVL*)malloc(sizeof(AVL));
   elemento->alturaElemento = 0;
   strcpy(elemento->palabraEspanhol, palabraEspanhol);
   strcpy(elemento->palabraOtro, palabraOtro);
   strcpy(elemento->definicion, definicion);
   elemento->hijoDerechoPalabraEspanhol = NULL;
   elemento->hijoIzquierdoPalabraEspanhol = NULL;
   elemento->hijoDerechoPalabraOtro = NULL;
   elemento->hijoIzquierdoPalabraOtro = NULL;
   return elemento;
}

int compararPalabras(char P1[], char P2[]){
   int i;
   i = 0;
   if(strncmp(P1, P2, 51) == 0){
      return 0;
   }
   while(P1[i] != '\0' || P2[i] != '\0' ) {
      if(P1[i] != P2[i]){
         if(P1[i] < P2[i]){
            return 1; //P1 va primero alfabéticamente (o mayor).
         }
         else{
            return -1; //P2 va primero alfabéticamente (o mayor).
         }
      }
      i++;
   }
   return -2; //Error
}

AVL* hijoDerechoPalabraEspanhol(AVL* elemento){
  if(elemento == NULL){
    return NULL;
  }
  return elemento->hijoDerechoPalabraEspanhol;
}

AVL* hijoDerechoPalabraOtro(AVL* elemento){
  if(elemento == NULL){
    return NULL;
  }
  return elemento->hijoDerechoPalabraOtro;

}

AVL* hijoIzquierdoPalabraEspanhol(AVL* elemento){
  if(elemento == NULL){
    return NULL;
  }
  return elemento->hijoIzquierdoPalabraEspanhol;
}

AVL* hijoIzquierdoPalabraOtro(AVL* elemento){
  if(elemento == NULL){
    return NULL;
  }
  return elemento->hijoDerechoPalabraOtro;
}

void rotarDerechaEspanhol(AVL* elementoRotar){
  AVL* nuevaRaiz = hijoIzquierdoPalabraEspanhol(elementoRotar);
  elementoRotar->hijoIzquierdoPalabraEspanhol = hijoDerechoPalabraEspanhol(nuevaRaiz);
  nuevaRaiz->hijoDerechoPalabraEspanhol = elementoRotar;
  return;
}

void rotarIzquierdaEspanhol(AVL* elementoRotar){
  AVL* nuevaRaiz = hijoDerechoPalabraEspanhol(elementoRotar);
  elementoRotar->hijoDerechoPalabraEspanhol = hijoIzquierdoPalabraEspanhol(nuevaRaiz);
  nuevaRaiz->hijoIzquierdoPalabraEspanhol = elementoRotar;
  return;
}

void rotarDerechaOtro(AVL* elementoRotar){
  AVL* nuevaRaiz = hijoIzquierdoPalabraOtro(elementoRotar);
  elementoRotar->hijoIzquierdoPalabraOtro = hijoDerechoPalabraOtro(nuevaRaiz);
  nuevaRaiz->hijoDerechoPalabraOtro = elementoRotar;
  return;
}

void rotarIzquierdaOtro(AVL* elementoRotar){
  AVL* nuevaRaiz = hijoDerechoPalabraOtro(elementoRotar);
  elementoRotar->hijoDerechoPalabraOtro = hijoIzquierdoPalabraOtro(nuevaRaiz);
  nuevaRaiz->hijoIzquierdoPalabraOtro = elementoRotar;
  return;
}


int alturaElementoEspanhol(AVL* elemento){
  int alturaDerecha, alturaIzquierda;
  if(elemento == NULL){
    return 0;
  }
  if(hijoDerechoPalabraEspanhol(elemento) == NULL && hijoIzquierdoPalabraEspanhol(elemento) == NULL){
    return 0;
  }
  alturaDerecha = alturaElementoEspanhol(hijoDerechoPalabraEspanhol(elemento));
  alturaIzquierda = alturaElementoEspanhol(hijoIzquierdoPalabraEspanhol(elemento));
  if(alturaIzquierda > alturaDerecha){
    return 1 + alturaIzquierda;
  }
  return 1 + alturaDerecha;
}

int alturaElementoOtro(AVL* elemento){
  int alturaDerecha, alturaIzquierda;
  if(elemento == NULL){
    return 0;
  }
  if(hijoDerechoPalabraOtro(elemento) == NULL && hijoIzquierdoPalabraOtro(elemento) == NULL){
    return 0;
  }
  alturaDerecha = alturaElementoOtro(hijoDerechoPalabraOtro(elemento));
  alturaIzquierda = alturaElementoOtro(hijoIzquierdoPalabraOtro(elemento));
  if(alturaIzquierda > alturaDerecha){
    return 1 + alturaIzquierda;
  }
  return 1 + alturaDerecha;
}

int diferenciaAlturasEspanhol(AVL* elemento){
   return (alturaElementoEspanhol(elemento->hijoIzquierdoPalabraEspanhol) - alturaElementoEspanhol(elemento->hijoDerechoPalabraEspanhol));
}

int diferenciaAlturasOtro(AVL* elemento){
   return (alturaElementoOtro(hijoIzquierdoPalabraEspanhol(elemento)) - alturaElementoOtro(hijoDerechoPalabraEspanhol(elemento)));
}

void equilibrarRamaEspanhol(AVL* elementoEquilibrar){
   int diferencia;
   diferencia = diferenciaAlturasEspanhol(elementoEquilibrar);
   if(diferencia == 2){
      if(diferenciaAlturasEspanhol(hijoIzquierdoPalabraEspanhol(elementoEquilibrar)) < 0){
         rotarIzquierdaEspanhol(hijoIzquierdoPalabraEspanhol(elementoEquilibrar));
      }
      rotarDerechaEspanhol(elementoEquilibrar);
      return;
   }
   if(diferencia == -2){
      if(diferenciaAlturasEspanhol(hijoDerechoPalabraEspanhol(elementoEquilibrar)) > 0){
         rotarDerechaEspanhol(hijoDerechoPalabraEspanhol(elementoEquilibrar));
      }
      rotarIzquierdaEspanhol(elementoEquilibrar);
      return;
   }
   return;
}

void equilibrarRamaOtro(AVL* elementoEquilibrar){
   int diferencia;
   diferencia = diferenciaAlturasOtro(elementoEquilibrar);
   if(diferencia == 2){
      if(diferenciaAlturasOtro(hijoIzquierdoPalabraOtro(elementoEquilibrar)) < 0){
         rotarIzquierdaOtro(hijoIzquierdoPalabraOtro(elementoEquilibrar));
      }
      rotarDerechaOtro(elementoEquilibrar);
      return;
   }
   if(diferencia == -2){
      if(diferenciaAlturasOtro(hijoDerechoPalabraOtro(elementoEquilibrar)) > 0){
         rotarDerechaOtro(hijoDerechoPalabraOtro(elementoEquilibrar));
      }
      rotarIzquierdaOtro(elementoEquilibrar);
      return;
   }
   return;
}

void agregarElemento(AVL* nuevoElemento ,AVL** raiz){
	if(*raiz == NULL){ //En caso de ya estár inicializada con un primer nodo
		*raiz = nuevoElemento;
		largoArbol = 1;
		return;
	}
	else{
      //Para español.
		AVL* elementoActualEspanhol = *raiz;
      AVL* elementoAuxiliarEspanhol = *raiz; //Auxiliar siempre irá en la posición anterior de actual.
      while(elementoActualEspanhol != NULL){ //Avanzará hasta que elementoActual apunte a NULL,
         elementoAuxiliarEspanhol = elementoActualEspanhol; //lo que dejará a elementoAuxiliar en la posición anterior.
         if(compararPalabras(nuevoElemento->palabraEspanhol, elementoActualEspanhol->palabraEspanhol) == 1){
            elementoActualEspanhol = elementoActualEspanhol->hijoIzquierdoPalabraEspanhol;
         }
         if(compararPalabras(nuevoElemento->palabraEspanhol, elementoActualEspanhol->palabraEspanhol) == -2) {
            printf("Error al comparar palabras, al buscar\n");
         }
         else{
            elementoActualEspanhol = elementoActualEspanhol->hijoDerechoPalabraEspanhol;
         }
      }
      if(compararPalabras(nuevoElemento->palabraEspanhol, elementoAuxiliarEspanhol->palabraEspanhol) == 1){
         elementoAuxiliarEspanhol->hijoIzquierdoPalabraEspanhol = nuevoElemento;
         //equilibrarRamaEspanhol(elementoAuxiliarEspanhol);
         largoArbol++;
      }
      if(compararPalabras(nuevoElemento->palabraEspanhol, elementoAuxiliarEspanhol->palabraEspanhol) == -2) {
         printf("Error al comparar palabras, al insertar\n");
      }
      else{
         elementoAuxiliarEspanhol->hijoDerechoPalabraEspanhol = nuevoElemento;
         //equilibrarRamaEspanhol(elementoAuxiliarEspanhol);
         largoArbol++;
      }
      //Para el otro idioma.
      AVL* elementoActualOtro = *raiz;
      AVL* elementoAuxiliarOtro = *raiz; //Auxiliar siempre irá en la posición anterior de actual.
      while(elementoActualOtro != NULL){ //Avanzará hasta que elementoActual apunte a NULL,
         elementoAuxiliarOtro = elementoActualOtro; //lo que dejará a elementoAuxiliar en la posición anterior,
         if(compararPalabras(nuevoElemento->palabraOtro, elementoActualOtro->palabraOtro) == 1){
            elementoActualOtro = elementoActualOtro->hijoIzquierdoPalabraOtro;
         }
         if(compararPalabras(nuevoElemento->palabraOtro, elementoActualOtro->palabraOtro) == -2) {
            printf("Error al comparar palabras, al buscar\n");
         }
         else{
            elementoActualOtro = elementoActualOtro->hijoDerechoPalabraOtro;
         }
      }
      if(compararPalabras(nuevoElemento->palabraOtro, elementoAuxiliarOtro->palabraOtro) == 1){
         elementoAuxiliarOtro->hijoIzquierdoPalabraOtro = nuevoElemento;
         //equilibrarRamaOtro(elementoAuxiliarOtro);
         largoArbol++;
      }
      if(compararPalabras(nuevoElemento->palabraOtro, elementoAuxiliarOtro->palabraOtro) == -2) {
         printf("Error al comparar palabras, al insertar\n");
      }
      else{
         elementoAuxiliarOtro->hijoDerechoPalabraOtro = nuevoElemento;
         //equilibrarRamaOtro(elementoAuxiliarOtro);;
         largoArbol++;
      }
   }
   return;
}

void mostrarArbol_InordenEspanhol(AVL** raiz){
   if(*raiz != NULL){
      if((*raiz)->hijoIzquierdoPalabraEspanhol != NULL){
         mostrarArbol_InordenEspanhol(&((*raiz)->hijoIzquierdoPalabraOtro));
      }
      printf("[ %s ]",(*raiz)->palabraEspanhol);
      if((*raiz)->hijoDerechoPalabraEspanhol != NULL){
         mostrarArbol_InordenEspanhol(&((*raiz)->hijoDerechoPalabraEspanhol ));
      }
   }
}

void mostrarArbol_InordenOtro(AVL** raiz){
   if(*raiz != NULL){
      if((*raiz)->hijoIzquierdoPalabraOtro != NULL){
         mostrarArbol_InordenOtro(&((*raiz)->hijoIzquierdoPalabraOtro));
      }
      printf("[ %s ]",(*raiz)->palabraOtro);
      if((*raiz)->hijoDerechoPalabraOtro != NULL){
         mostrarArbol_InordenOtro(&((*raiz)->hijoDerechoPalabraOtro));
      }
   }
}

int main(int argc, char const *argv[]){
   AVL* raiz = NULL;
   AVL* primerElemento = crearElemento("Azul","Blue","Es el color ingresado número 1");
   AVL* segundoElemento = crearElemento("Rojo","Red","Es el color ingresado número 2");
   AVL* tercerElemento = crearElemento("Cafe","Brown","Es el color ingresado número 3");
   AVL* cuartoElemento = crearElemento("Amarillo","Yellow","Es el color ingresado número 4");
   AVL* quintoElemento = crearElemento("Rosado","Pink","Es el color ingresado número 5");
   agregarElemento(primerElemento, &raiz);
   agregarElemento(segundoElemento, &raiz);
   agregarElemento(tercerElemento, &raiz);
   //agregarElemento(cuartoElemento, &raiz);
   //agregarElemento(quintoElemento, &raiz);
   printf("\nLas palabras en Español en inorden son: ");
   mostrarArbol_InordenEspanhol(&raiz);
   printf("\nLas palabras en Otro en inorden son: ");
   mostrarArbol_InordenOtro(&raiz);
   printf("\n\n");
   return 0;
}
