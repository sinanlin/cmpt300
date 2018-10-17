#include "list.h"
#include <stdio.h>
#include <stdlib.h>



struct nodeStruct* List_createNode(int item){
  struct nodeStruct* NewNode = malloc(sizeof(struct nodeStruct));
  NewNode->item = item;
  NewNode->next = NULL;

  return NewNode;
}


void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node){
if( *headRef != NULL){
  node->next = *headRef;
  *headRef = node;
}else{
  *headRef = node;
}
}


void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node){

  //Construct a tmp variable to iterate through the node and to keep the head.

  struct nodeStruct* tmp = malloc(sizeof(struct nodeStruct));

  // tmp points to where the headRef is reference to.
  tmp = *headRef;

  //If the dereference the head  and it is empty

  if( *headRef == NULL){
  // we should let the head points to  the node's pointee.
  *headRef = node;
}else{
  //Case where the head has something in existence
  while(tmp->next != NULL){
    tmp = tmp->next;
  }
    tmp->next = node;
}

}

int List_countNodes (struct nodeStruct *head){
  struct nodeStruct* tmp = malloc(sizeof(struct nodeStruct));

  tmp = head;
  int i = 0;

if(head != NULL){
  i++;
  while(tmp->next!=NULL){
    tmp = tmp->next;
    i++;
  }
}
  return i;
}

struct nodeStruct* List_findNode(struct nodeStruct *head, int item){
  struct nodeStruct* tmp = malloc(sizeof(struct nodeStruct));
  tmp = head;

if(head != NULL){
    while(tmp->item != item && tmp->next != NULL){
      tmp = tmp->next;
    }

    if(tmp->item == item){
      return tmp;
    }else{
      return NULL;
    }
}else{
  return NULL;
}

}



void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node){

  //case here *headRef == node.  we delete the node.

  struct nodeStruct* tmp = malloc(sizeof(struct nodeStruct));

  tmp = *headRef;

//Corner case where the head is the node .
  if(*headRef == node){
    if((*headRef)->next != NULL){
      *headRef = (*headRef)->next;
      free(node);
    }else{
      node = NULL;
    }
  }

//Case the node in between tis the node.
  if(*headRef != NULL){
     while(tmp != node && tmp->next != NULL ){

       if(tmp->next == node){

         tmp->next = tmp->next->next;
       }
       else{
         tmp=tmp->next;
       }
     }

  }else{
    return ;
  }

}

//Insertion sort. Each item in the node is compare with all the node previously. And insert into the right place.


void List_sort (struct nodeStruct **headRef){


  if (*headRef == NULL || (*headRef)->next == NULL)
          return;

  struct nodeStruct* A = *headRef;
  struct nodeStruct* B;

  while (A != NULL)
  {
          struct nodeStruct* current = A;
          A = A->next;
          if (*headRef == NULL || current->item < (*headRef)->item)
          {
                  current->next = *headRef;
                  *headRef = current;
          }
          else
          {
                  B = *headRef;
                  while (B != NULL)
                  {
                          if (B->next == NULL || current->item < B->next->item)
                          {
                                  current->next = B->next;
                                  B->next = current;
                                  break;
                          }
                          B = B->next;
                  }
          }
  }
  B->next = NULL;


}
