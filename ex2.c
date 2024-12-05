#include <stdio.h>
#include <stdlib.h>

void clear(){
    printf("\e[2J\e[H");
}

typedef struct arbre{
	int elmt;
	struct arbre* fg;
	struct arbre* fd;
} Arbre;

typedef Arbre* pArbre;

Arbre* creationArbre(int donne){
	Arbre* nouveau = malloc( sizeof(Arbre));
	if (nouveau==NULL){
		exit(1);
	}
	nouveau->elmt = donne;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
}

int estVide(pArbre a){
	if (a==NULL){
		return 1;
	}
	return 0;

}

int estFeuille(pArbre a){
	if (estVide(a)){
		return 0;
	}
	if (estVide(a->fg)&&estVide(a->fd)){
		return 1;
	}
	return 0;
}

int element (pArbre a){
	if (!estVide(a)){
		return a->elmt;
	}
	return 0;
}

int exFG(pArbre a){
	if (!estVide(a)){
		if (!estVide(a->fg)){
			return 1;
		}
		return 0;
	}
	return 0;
}

int exFD(pArbre a){
	if (!estVide(a)){
		if (!estVide(a->fd)){
			return 1;
		}
		return 0;
	}
	return 0;
}

pArbre addFG (pArbre a,int e){
	if (estVide(a)){
		exit(1);
	}
	if(!exFG(a->fg)){
		a->fg = creationArbre(e);
	}
	return a;
}

pArbre addFD (pArbre a, int e){
	if (estVide(a)){
		exit(1);
	}
	if(!exFD((a->fd))){
		a->fd = creationArbre(e);
	}
	return a;
}

void prefixe (pArbre a){
	if (!estVide(a)){
		printf("Prefixe : %d \n",a->elmt);
		prefixe(a->fg);
		prefixe(a->fd);
	}
}

void infixe (pArbre a){
	if (!estVide(a)){
		infixe(a->fg);
		printf("Infixe : %d \n",a->elmt);
		infixe(a->fd);
	}
}

pArbre insertABR(pArbre a,int elt){
    if (estVide(a)){
        exit(1);
    }
    if (a->elmt>elt){
        if(exFG(a)){
            insertABR(a->fg,elt);  
        }
        else{
            addFG(a,elt);
        }
    }
    if (a->elmt<elt){
        if (exFD(a)){
            insertABR(a->fd,elt);
        }
        else{
            addFD(a,elt);
        }
    }
}

int recherche(pArbre a, int elt){
    if (estVide(a)){
        return 0;
    }
    if (a->elmt==elt){
        return 1;
    }
    else if (a->elmt<elt){
        recherche(a->fd,elt);
    }
    else if (a->elmt>elt){
        recherche (a->fg,elt);
    }
}

pArbre suppMax(pArbre a, int* pe) {
    pArbre tmp;
    if (exFD(a)) {
        a->fd = suppMax(a->fd, pe);
    } else {
        *pe = a->elmt;
        tmp = a;
        a = a->fg;
        free(tmp);
    }
    return a;
}

pArbre supprAbr(pArbre a, int elt) {
    pArbre tmp;
    int maxVal;
    if (estVide(a)) {
        return a;
    } else if (elt > a->elmt) {
        a->fd = supprAbr(a->fd, elt);
    } else if (elt < a->elmt) {
        a->fg = supprAbr(a->fg, elt);
    } else if (!exFG(a)) {
        tmp = a;
        a = a->fd;
        free(tmp);
    } else if (!exFD(a)) {
        tmp = a;
        a = a->fg;
        free(tmp);
    } else {
        a->fg = suppMax(a->fg, &maxVal);
        a->elmt = maxVal;
    }
    return a;
}

void ancetre(pArbre arbre,int e ){
	if (recherche(arbre,e)){
		if (e>arbre->elmt){
			printf("%d \n",arbre->elmt);
			ancetre(arbre->fd,e);
		}
		if (e<arbre->elmt){
			printf("%d \n",arbre->elmt);
			ancetre(arbre->fg,e);
		}
	}
}

int max(int a, int b){
	if (a>b){
		return a;
	}else{
		return b;
	}
}

int hauteur(pArbre a){
	if (a==NULL){
		return 0;
	}
	if (a->fd == NULL && a->fg ==NULL){
		return 1;
	}
	else if (a->fd != NULL && a->fg != NULL){
		return 1 + max(hauteur(a->fd),hauteur(a->fg));
	}
	else if (a->fd==NULL){
		return 1 + hauteur(a->fg);
	}
	else if (a->fg ==NULL){
		return 1 + hauteur(a->fd);
	}
}

int equilibre(pArbre a){
	if (a==NULL){
		return 0;
	}
	return hauteur(a->fd)-hauteur(a->fg);
}

int abs(int a){
	if (a<0){
		return -a;
	}else{
		return a;
	}
}

int equal(pArbre a, pArbre* neuil){
	if (a==NULL){
		return 1;
	}
	if (abs(equilibre(a))>=2){
		if (abs(equilibre(*neuil))<abs(equilibre(a))){
			*neuil = a;
		}
		return 0;
	}else{
		return equal(a->fg,neuil) || equal(a->fd,neuil);
	}
}


int main(){
	pArbre a = creationArbre(1);

	insertABR(a,10);
	insertABR(a,3);
	insertABR(a,5);
	insertABR(a,15);
	insertABR(a,20);
	insertABR(a,-2);
	insertABR(a,-3);

	infixe(a);
	if (!recherche(a,303)){
		printf("Pas dans l'arbre\n");
	}
	else{
		printf("Dans l'arbre\n");
	}

	ancetre(a,-3);

	printf("hauteur de a est : %d\n",hauteur(a));
	printf("equilibrage de a est : %d\n",equilibre(a));

	pArbre neuil = a;
	int h;
	printf("Equilibré  : %d\n",equal(a,&neuil));

	return 0;
}


