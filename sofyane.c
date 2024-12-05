// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

typedef struct AVL{
    
int data;
int eq;
struct AVL* fg;
struct AVL* fd;

}AVL;


AVL* creationAVL(int data){
AVL* pavl = malloc (sizeof(AVL));

pavl  -> data = data;
pavl -> eq = 0;
pavl -> fd = pavl -> fg = NULL;

return pavl;
    
}

int search(AVL* pavl, int data){
    
if ( pavl == NULL){
    printf("vide");
return -1;
}
else if ( pavl -> data > data){
    
return search(pavl -> fg, data);
    
}
    else if ( pavl -> data <  data){
    
  return  search(pavl -> fd, data);
    
}
if ( pavl -> data == data){
    return 1;
}
    
  return 0; 
}


int max ( int a, int b){
    
    if (a > b){
        return a;
    }
return b;
    
}


int min ( int a, int b){
    
    if (a <  b){
        return a;
    }
return b;
}


AVL* rotationgauche(AVL* pavl){
AVL* pivot;
int ea, eb;
    
pivot = pavl -> fd;
pavl -> fd = pivot -> fg;
pivot -> fg = pavl;
    
ea = pavl -> eq;
eb = pivot -> eq;
    
pavl -> eq = ea -max(eb,0)-1;
pivot -> eq = min(ea-2, min(ea+eb-2, eb-1));
    
pavl = pivot;

return pavl;
}


AVL* rotationdroite(AVL* pavl){
AVL* pivot;
int ea, eb;
    
pivot = pavl -> fg;
pavl -> fg = pivot -> fd;
pivot -> fd = pavl;
    
ea = pavl -> eq;
eb = pivot -> eq;
    
pavl -> eq = ea - min(eb,0)+1;
pivot -> eq = max(ea+2, max(ea+eb+2, eb+1));
    
pavl = pivot;

return pavl;
}


AVL* doublegauche(AVL* pavl){
    
pavl -> fd = rotationdroite(pavl -> fd);
return rotationgauche( pavl);
}


AVL* doubledroite(AVL* pavl){
    
pavl -> fg = rotationgauche(pavl -> fg);
return rotationdroite( pavl);
}

AVL* equilibrage(AVL* pavl) {
    // Add NULL checks
    if (pavl == NULL) return pavl;
    
    if (pavl->eq >= 2) {
        if (pavl->fd == NULL) return pavl;
        if (pavl->fd->eq >= 0) {
            return rotationgauche(pavl);
        }
        else {
            return doublegauche(pavl);
        }
    }
    
    if (pavl->eq <= -2) {
        if (pavl->fg == NULL) return pavl;
        if (pavl->fg->eq <= 0) {
            return rotationdroite(pavl);
        }
        else {
            return doubledroite(pavl);
        }
    }
    return pavl;
}



AVL* Insert(AVL* pavl, int data, int* h) {
    if (pavl == NULL) {
        pavl = creationAVL(data);
        *h = 1;
        return pavl;
    }
    else if (pavl->data > data) {
        pavl->fg = Insert(pavl->fg, data, h);
        *h = -*h;
    }
    else if (pavl->data < data) {
        pavl->fd = Insert(pavl->fd, data, h);
        // Add this line to properly update h
        *h = *h;
    }
    else {
        *h = 0;
        return pavl;
    }
    
    if (*h != 0) {
        pavl->eq += *h;
        pavl = equilibrage(pavl);
        if (pavl->eq == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return pavl;
}



AVL* suppMin(AVL* pavl, int* h, int* data){

AVL* tmp;
if ( pavl -> fg == NULL){
*data = pavl -> data;
tmp = pavl;
pavl  = pavl -> fd;
 *h = -1;
 free(tmp);
 return pavl;
}
else{
pavl -> fg = suppMin(pavl->fg, h, data);
*h = -*h;
  
}
    
    if ( *h != 0 && pavl != NULL){
    pavl ->eq+= *h;
    pavl = equilibrage(pavl);
    if ( pavl -> eq == 0){
        
        *h = -1;
    }
      else {
          
         *h =0;
      } 
        
        
    }
    
    return pavl;
    
}

AVL* suppr(AVL* pavl , int* h, int data){
    
    AVL* tmp;
if ( pavl == NULL){
    *h = 0;
    return pavl;
}
    
 else if ( pavl -> data > data){
     pavl -> fg = suppr(pavl -> fg, h, data);
     *h = -*h;
 }  

   else if ( pavl -> data < data){
     pavl -> fd = suppr(pavl -> fd, h, data);
     *h = -*h;
 }  
   else if ( pavl -> fd != NULL ){
    pavl->fd = suppMin(pavl -> fd, h, &(pavl ->data));

 }   
else{
tmp = pavl;
pavl = pavl -> fg;
*h = -1;
free(tmp);
return pavl;
}
      
      
       if ( *h != 0 && pavl != NULL){
    pavl ->eq+= *h;
    pavl = equilibrage(pavl);
    if ( pavl -> eq == 0){
        
        *h = -1;
    }
      else {
          
         *h =0;
      } 
        
        
    }
    
    return pavl;
    
}

void Infixe(AVL* pavl ){

if ( pavl == NULL){
    return;
}

Infixe(pavl -> fg);
printf("[%d]\n", pavl -> data);
Infixe(pavl -> fd);

    
}



int main() {
  
 AVL* pavl = NULL;
 int h = 0;
 
 pavl = Insert( pavl, 10,&h);
 pavl = Insert( pavl, 4,&h);
 pavl = Insert( pavl, 3,&h);
 pavl = Insert( pavl, 90,&h);
   
  Infixe(pavl);
   printf("\n");
   
    pavl = suppr(pavl, &h ,4);
    pavl = suppr(pavl, &h ,90);
   pavl = suppr(pavl, &h ,3);
   
    Infixe(pavl);
   
    return 0;
}