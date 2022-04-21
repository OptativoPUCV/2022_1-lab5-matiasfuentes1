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
 /*if(tree == NULL)return;

 TreeNode * aux = tree->root;
 TreeNode * parent = NULL ;

  while(aux!=NULL){
       parent = aux;
       if (tree ->lower_than(key, aux-> key)){
          aux = aux ->left;
       }else if (tree->lower_than(aux->key,key)){
           aux=aux->right;
       }else{
           return;
       }
       
  }

  TreeMap * nuevo = createTreeNode(key,value);

  nuevo-> parent =parent;
   
  if (parent== NULL){
   tree -> root = nuevo;
  }else if (tree -> lower_than (nuevo-> key ,parent -> key)){
      parent ->left = nuevo;
  }else{
      parent->right=nuevo;
  }
  
tree->current=nuevo;*/

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}