#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int filas[9][9] = {0};
   int columnas[9][9] = {0};
   int submatriz[9][9] = {0};

   int i , j;
   for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          int num = n->sudo[i][j];
          if(num != 0){
             int submatriz_valid = (i/3)*3 + (j/3);
             if(filas[i][num - 1] == 1 || columnas[j][num - 1] == 1 || submatriz[submatriz_valid][num - 1] == 1){
                return 0;
             }
             filas[i][num - 1] = 1;
             columnas[j][num - 1] = 1;
             submatriz[submatriz_valid][num - 1] = 1;
          }
       }
   }
   return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

   int i, j;
   for(i = 0 ; i < 9 ; i ++)
      for(j = 0; j < 9 ; j++)
         if(n->sudo[i][j] == 0){
            int k;
            for(k = 1; k <= 9 ; k++){
               Node * nuevo_nodo = copy(n);
               nuevo_nodo->sudo[i][j] = k;
               if(is_valid(nuevo_nodo)){
                  pushBack(list, nuevo_nodo);
               }
            }
            return list;
         }
   return list;
}


int is_final(Node* n){
   int i, j;
   for(i = 0 ; i < 9 ; i ++){
      for(j = 0 ; j < 9 ; j++){
         if(n->sudo[i][j] == 0){
            return 0;
         }
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S = createStack();
   push(S, initial);
   *cont = 0;

   while(first(S) != NULL){
      Node * aux = top(S);
      pop(S);
      (*cont)++;

      if(is_final(aux)){
         return aux;
      }
      List * list = get_adj_nodes(aux);
      Node * aux2 = first(list);
      while(aux2 != NULL){
         push(S, aux2);
         aux2 = next(list);
      }
      free(aux);
   }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/