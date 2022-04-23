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
}//ok

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {  
     
     TreeMap * nuevo_mapa = (TreeMap*) malloc(sizeof(TreeMap));
     nuevo_mapa -> root = NULL;
     nuevo_mapa -> current = NULL;
     nuevo_mapa->lower_than = lower_than;
     return nuevo_mapa;
} //ok

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

} //ok

TreeNode * minimum(TreeNode * x){
  TreeNode * aux;
   aux = x;
  while(aux -> left!=NULL){
    aux = aux -> left;
  }
    return aux;
} //ok

void removeNode(TreeMap * tree, TreeNode* node){
// Caso 1: sin hijos.
    if(node->left == NULL && node->right == NULL)
    {
        node->parent->left = NULL;
        node->parent->right = NULL;
        node->parent = NULL;
        free(node);
        return;
    }
    // Caso 3: con dos hijos.
    if(node->left != NULL && node->right != NULL)
    {
        TreeNode *nodoAux;
        TreeNode *padre;
        nodoAux = node->left;
        if(nodoAux->right != NULL)
        {
            while(nodoAux->right != NULL)
            {
                nodoAux =  nodoAux->right;
            }
            padre =  node;
            node = nodoAux;
            node->parent = padre->parent;
            node->right = padre->right;
            node->left = padre->left;
            if(nodoAux->left != NULL)
            {
                nodoAux->parent->right = nodoAux->left;
            }
            else
                nodoAux->parent->right = NULL;
            free(nodoAux);
            return;
        }
        else
        {
            padre = nodoAux->parent;
            node = nodoAux;
            node->left = nodoAux->left;
            node->parent = padre->parent;
            node->right = padre->right;
            /*if(nodoAux->left == NULL)
            {
                padre->right = NULL;
            }
            else
                padre->right = nodoAux->left;*/
            free(nodoAux);
            //free(padre);
            return;
        }
        
    }
    // Caso 2: con solo un hijo.
    // Caso 2.1: hijo izquierdo.
    if(node->left != NULL && node->right == NULL)
    {
        if(node->pair->key > node->parent->pair->key)
        {
            if(node->left != NULL){
                node->parent->right = node->left;
                node->left->parent = node->parent;
                free(node);
                return;
            }
            if(node->right != NULL){
                node->parent->right = node->right;
                node->left->parent = node->parent;
                free(node);
                return;
            }       
        }
        else
        {
            if(node->left != NULL){
                node->parent->right = node->left;
                node->left->parent = node->parent;
                free(node);
                return;
            }
            if(node->right != NULL){
                node->parent->right = node->right;
                node->left->parent = node->parent;
                free(node);
                return;
            }
        }
    }
    // Caso 2.2: hijo derecho.
    if(node->right != NULL && node->left == NULL)
    {
        if(node->pair->key > node->parent->pair->key)
        {
            if(node->left != NULL){
                node->parent->right = node->left;
                node->left->parent = node->parent;
                free(node);
                return;
            }
            if(node->right != NULL){
                node->parent->right = node->right;
                node->left->parent = node->parent;
                free(node);
                return;
            }       
        }
        else
        {
            if(node->left != NULL){
                node->parent->right = node->left;
                node->left->parent = node->parent;
                free(node);
                return;
            }
            if(node->right != NULL){
                node->parent->right = node->right;
                node->left->parent = node->parent;
                free(node);
                return;
            }
        }
    }
  
}

void eraseTreeMap(TreeMap * tree, void* key){
  if (tree == NULL || tree->root == NULL) return;

  if (searchTreeMap(tree, key) == NULL) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);

}//ok

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
}//ok


Pair * upperBound(TreeMap * tree, void* key) {

  TreeNode * aux = tree->root;
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
     return aux ->pair;
    }
  }
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode * aux = tree->root;
  while(aux -> left!=NULL){
    aux = aux -> left;
  }
    return aux->pair;
}//ok

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
