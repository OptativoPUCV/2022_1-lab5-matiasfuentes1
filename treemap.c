#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}

TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {  
     
     TreeMap * nuevo_mapa = (TreeMap*) malloc(sizeof(TreeMap));
     nuevo_mapa -> root = NULL;
     nuevo_mapa -> current = NULL;
     nuevo_mapa->lower_than = lower_than;
     return nuevo_mapa;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {

if(tree == NULL)return;

 TreeNode * aux = tree->root;
 TreeNode * padre = NULL ;

  while(aux!=NULL){
       padre = aux;
       if (tree ->lower_than(key, aux->pair-> key)){
          aux = aux ->left;
       }else if (tree->lower_than(aux->pair-> key,key)){
           aux=aux->right;
       }else{
           return;
       }     
  }

  TreeNode * nuevo = createTreeNode(key,value);

  nuevo-> parent = padre;
   
  if (padre == NULL){
   tree -> root = nuevo;
  }else if (tree -> lower_than (nuevo->pair-> key ,padre ->pair-> key)){
      padre -> left = nuevo;
  }else{
      padre -> right = nuevo;
  }
  
tree -> current = nuevo;

}

TreeNode * minimum(TreeNode * x){
  TreeNode * aux;
   aux = x;
  while(aux -> left!=NULL){
    aux = aux -> left;
  }
    return aux;
}

void removeNode(TreeMap * tree, TreeNode* node){

  
}

void eraseTreeMap(TreeMap * tree, void* key){
  if (tree == NULL || tree->root == NULL) return;

  if (searchTreeMap(tree, key) == NULL) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) { 
  
 if(tree->root != NULL){
    TreeNode * aux = tree->root;

    while(aux!=NULL){
      tree->current= aux;
      if(is_equal(tree,key,aux->pair->key)) {
        return aux -> pair;
      }else{
        if(tree->lower_than(key,aux->pair->key)== 1){
        aux = aux -> left;
        }
        if(tree->lower_than(aux->pair->key,key)== 1){
        aux = aux ->  right;
        }
      }
    }
  }else{
    return NULL;
  }
return NULL; 
}


Pair * upperBound(TreeMap * tree, void* key) {

  /*TreeNode * aux = tree->root;
  TreeNode * nuevo = aux;
  while(aux != NULL){
    if(tree->lower_than(aux->pair->key,key)==1){
      if(tree->lower_than(nuevo->pair->key,aux->pair->key)==1){
        nuevo = aux;
      }else{
        nuevo = aux;
        aux = aux->right;
      } 
    }else {
      if(tree->lower_than(key,aux->pair->key)==1){
        if(tree->lower_than(nuevo->pair->key,aux->pair->key)==1){
          nuevo = aux;
        }
      aux = aux->left;
     }
    }
  }*/
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
