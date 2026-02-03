#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include "object.h"

typedef enum
{
  ROOT,
  LEFT,
  RIGHT
}Side;

typedef struct{
  Object raiz;
  void (*insert)();
  Object (*search)();
  void (*printTree)();
  void (*rmv)();
  void (*clear)();
  void (*preorder)();
  void (*inorder)();
  void (*postorder)();
}_BSTree;

typedef _BSTree* BSTree;

Object _insert(Object raiz, Object obj){
  if(!raiz) return obj;

  if(obj->chave<=raiz->chave) raiz->left = _insert(raiz->left, obj);
  else raiz->right = _insert(raiz->right, obj);

  return raiz;
}

void insert(BSTree abb, Object obj){
  abb->raiz = _insert(abb->raiz,obj);
}

Object _search(Object raiz, int chaveAlvo, TypeObject type){
  if(!raiz) return NULL;
  if(raiz->chave==chaveAlvo && (raiz->type==type || type==QUALQUER)) return raiz;

  return (raiz->chave<chaveAlvo)? _search(raiz->right,chaveAlvo,type) :
    _search(raiz->left,chaveAlvo,type);
}

Object search(BSTree abb, int key, TypeObject type){
  return _search(abb->raiz,key,type);
}

void printProfundidade(int tabs){
  for(int i=0; i<tabs; i++) printf("    ");
}

void _printTree(Object raiz, int profundidade, Side side){
  if(!raiz) return;
  printProfundidade(profundidade);
  if(side==LEFT)
    printf("(L)");
  else if(side==RIGHT)
    printf("(R)");
  else
    printf("(ROOT)");
  printf("%d\n",raiz->chave);
  _printTree(raiz->right, profundidade+1,RIGHT);
  _printTree(raiz->left, profundidade+1,LEFT);
}

void printTree(BSTree abb){
  _printTree(abb->raiz,0,ROOT);
}

Object _remove_no(Object raiz, int key,TypeObject type){
  if(!raiz) return NULL;
  Object toReturn = NULL;

  if(raiz->chave==key && (type==QUALQUER || type==raiz->type)){
    if(!raiz->left){
      toReturn = raiz->right;
      if(raiz->item) free(raiz->item);
      free(raiz);
      return toReturn;
    }
    if(!raiz->right){
      toReturn = raiz->left;
      if(raiz->item) free(raiz->item);
      free(raiz);
      return toReturn;
    }
    Object minNodeParent = raiz->right;
    Object minNode = minNodeParent;

    while(minNode->left){
      minNodeParent = minNode;
      minNode = minNode->left;
    }

    if(minNode != raiz->right){
      minNodeParent->left = minNode->right;
      minNode->right = raiz->right;
    }

    minNode->left = raiz->left;

    if(raiz->item) free(raiz->item);
    free(raiz);

    return minNode;
  }
  else if(key>raiz->chave) raiz->right = _remove_no(raiz->right,key,type);
  else raiz->left = _remove_no(raiz->left,key,type);
  return raiz;
}

void remove_no(BSTree abb, int key,TypeObject type){
  abb->raiz = _remove_no(abb->raiz,key,type);
}

Object _clear(Object raiz){
  if(!raiz) return NULL;
  _clear(raiz->right);
  _clear(raiz->left);
  if(raiz->item) free(raiz->item);
  free(raiz);
  return NULL;
}

void clear(BSTree abb){
  abb->raiz = _clear(abb->raiz);
}

void _preorder(Object raiz){
  if(raiz){
    printf("%d ",raiz->chave);
    _preorder(raiz->left);
    _preorder(raiz->right);
  }
}

void preorder(BSTree abb){
  _preorder(abb->raiz);
}

void _inorder(Object raiz){
  if(raiz){
    _inorder(raiz->left);
    printf("%d ",raiz->chave);
    _inorder(raiz->right);
  }
}

void inorder(BSTree abb){
  _inorder(abb->raiz);
}

void _postorder(Object raiz){
  if(raiz){
    _postorder(raiz->left);
    _postorder(raiz->right);
    printf("%d ",raiz->chave);
  }
}

void postorder(BSTree abb){
  _postorder(abb->raiz);
}

BSTree new_BSTree(){
  BSTree tree = malloc(sizeof(_BSTree));
  tree->raiz = NULL;
  tree->insert = insert;
  tree->search = search;
  tree->printTree = printTree;
  tree->rmv = remove_no;
  tree->clear = clear;
  tree->preorder = preorder;
  tree->inorder = inorder;
  tree->postorder = postorder;
  return tree;
}
#endif
