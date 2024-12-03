#include <stdio.h>
#include <stdlib.h>

typedef struct avl{
    int val;
    int eq;
    struct avl* fg;
    struct avl* fd;
} AVL;

AVL* createAVL(int val){
    AVL* new = malloc(sizeof(AVL));
    if (new==NULL){
        printf("Erreur d'allocation\n");
        exit(1);
    }
    new->val=val;
    new->eq=0;
    new->fg=NULL;
    new->fd=NULL;
    return new;
}

int max(int a,int b){
    if (a>b){
        return a;
    }else{
        return b;
    }
}

int min(int a,int b){
    if (a>b){
        return b;
    }else{
        return a;
    }
}

AVL* rotaGauche(AVL* avl){
    AVL* pivot = avl->fd;
    int eqA = avl->eq;
    int eqP = pivot->eq;
    avl->fd = pivot->fg;
    pivot->fg = avl;
    avl->eq = eqA - max(eqP,0) - 1;
    pivot->eq = min(eqA-2,min((eqA+eqP-2),eqP-1));
    return pivot;
}

AVL* rotaDroite(AVL* avl){
    AVL* pivot = avl->fg;
    int eqA = avl->eq;
    int eqP = pivot->eq;
    avl->fg = pivot->fd;
    pivot->fd = avl;
    avl->eq = eqA - min(eqP,0) + 1;
    pivot->eq = max(eqA+2,max((eqA+eqP+2),eqP+1));    
    return pivot;
}

AVL* doubleRotaGauche(AVL* avl){
    avl->fd = rotaDroite(avl->fd);
    avl = rotaGauche(avl);
    return avl;
}

AVL* doubleRotaDroite(AVL* avl){
    avl->fg = rotaGauche(avl->fg);
    avl=rotaDroite(avl);
    return avl;
}

AVL* equilibrage(AVL* avl){
    if (avl==NULL){
        return NULL;
    }
    if (avl->eq>=2){
        if(avl->fd->eq>=0){
            avl = rotaGauche(avl);
        }
        if (avl->fd->eq<0){
            avl = doubleRotaGauche(avl);
        }
    }
    if (avl->eq<=-2){
        if (avl->fg->eq<=0){
            avl = rotaDroite(avl);
        }
        if (avl->fg->eq>0){
            avl = doubleRotaDroite(avl);
        }
    }
    return avl;
}

AVL* insertAVL(AVL* avl, int e,int* h){
    if (avl==NULL){
        *h=1;
        return createAVL(e);
    }
    else if(e<avl->val){
        avl->fg = insertAVL(avl->fg,e,h);
        *h=-*h;
    }
    else if(e>avl->val){
        avl->fd = insertAVL(avl->fd,e,h);
    }
    else{
        *h=0;
        return avl;
    }
    if (*h!=0){
        avl->eq+=*h;
        avl=equilibrage(avl);
        *h = (avl->eq==0) ? 0 : 1;
    }
    return avl;

}

AVL* suppMinAVL(AVL* avl,int* h,int* p){
    printf("aAHAHA");
    if (avl->fg==NULL){
        *p=avl->val;
        *h=-1;
        AVL* temp = avl;
        avl=avl->fd;
        free(temp);
        return avl;
    }
    else{
        avl->fg = suppMinAVL(avl->fg,h,p);
        *h=-*h;
    }
    if (*h!=0){
        avl->eq+=*h;
        avl=equilibrage(avl);
        *h = (avl->eq==0) ? -1 : 0;
    }
    return avl;
}

AVL* suppAVL(AVL* avl,int e,int* h){
    printf("AHAHA");
    if (avl==NULL){
        *h=1;
        return avl ;
    }
    if (e<avl->val){
        avl->fg = suppAVL(avl->fg,e,h);
        *h=-*h;
    }
    else if (e>avl->val){
        avl->fd = suppAVL(avl->fd,e,h);
    }
    else if (avl->fd != NULL){
        avl = suppMinAVL(avl->fd,h,&(avl->val));
    }
    else{
        AVL* temp = avl;
        avl=avl->fg;
        free(temp);
        *h=-1;
    }
    if (avl!=NULL && *h!=0){
        avl->eq+=*h;
        avl=equilibrage(avl);
        *h= (avl->eq==0) ? 0 : 1;
    }
    return avl;
}

void prefixe(AVL* avl){
    if (avl==NULL){
        return;
    }else{
        printf("%d eq = %d\n",avl->val,avl->eq);
        prefixe(avl->fg);
        prefixe(avl->fd);
    }
}

int main(){

    AVL* root = NULL;
    int h = 0;

/* MAIN GITHUB COPILOT pr test */

    // Insert values into the AVL tree
    root = insertAVL(root, 42, &h);
    root = insertAVL(root, 17, &h);
    root = insertAVL(root, 68, &h);
    root = insertAVL(root, 3, &h);
    root = insertAVL(root, 25, &h);
    root = insertAVL(root, 91, &h);
    root = insertAVL(root, 54, &h);
    root = insertAVL(root, 36, &h);
    root = insertAVL(root, 77, &h);
    root = insertAVL(root, 12, &h);
    root = insertAVL(root, 89, &h);
    root = insertAVL(root, 5, &h);
    root = insertAVL(root, 63, &h);
    root = insertAVL(root, 29, &h);
    root = insertAVL(root, 48, &h);

    // Print the tree in prefix order before deletion
    printf("Tree before deletion:\n");
    prefixe(root);

    // Delete specific values from the AVL tree with null checks
    if (root != NULL) {
        printf("\nDeleting value 29\n");
        root = suppAVL(root, 29, &h);

        printf("\nDeleting value 5\n");  // Fixed message to match actual value
        root = suppAVL(root, 5, &h);

        printf("\nDeleting value 54\n");
        root = suppAVL(root, 54, &h);

        // Print the tree in prefix order after deletion
        printf("\nTree after deletion:\n");
        prefixe(root);
    }
}