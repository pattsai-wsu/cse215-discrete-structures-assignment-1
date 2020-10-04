#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

/*
NAME: Patrick Tsai
CLASS: CSE 215 M,W,F 12-1:55 PM
ASSIGNMENT: PA1
DUE DATE: 02/19/2020

SYNOPSIS: This program prompts users to type in 2 sets, then it displays (1) their sets, (2) the cardinality of each set (3) the union of the sets (4) the intersection of the sets (5) set A minus set B.
*/


struct node {
  char value;
  struct node *next;  
};

struct node* setInit();
int setChar(char, struct node*);
int count (struct node*);
struct node* unionab(struct node*, struct node*);
struct node* intersectionab(struct node*, struct node*);
struct node* aminusb(struct node*, struct node*);

int main() {
int alength,blength,i;
char usrIn[120],aset[120],bset[120];
char achar,bchar;

// code for set A
struct node *asent=setInit();
printf("ENTER VALUES for SET A: ");
fgets(usrIn, 120, stdin);
sscanf(usrIn,"%s", aset);
alength=strlen(aset);
aset[alength]='\0';

/*
if (aset[0]=1) {
  aset[0]='\0';
}

i=0;
while (i<alength) {
printf("%d\n",aset[i]);
i++;
}
*/

i=0;
while (i<alength) {
  achar=aset[i];
  if (achar==1) {
    break;
  }

  int spaceReturna = isspace(achar);

  if (spaceReturna==0) {
    int returnVal=setChar(achar, asent);
    if (returnVal==1) {
//    printf("success\n");
    }
    if (returnVal==0) {
//    printf("fail\n");
    }
  i++;
  }
  else {
    i++;
  }
}


// code for set B
struct node *bsent=setInit();
printf("ENTER VALUES for SET B: ");
fgets(usrIn, 120, stdin);
sscanf(usrIn,"%s", bset);
blength=strlen(bset);
bset[blength]='\0';

/*
i=0;
while (i<blength) {
printf("%d\n",bset[i]);
i++;
}
*/

i=0;
while (i<blength) {
  bchar=bset[i];

  int spaceReturnb = isspace(bchar);

  if (spaceReturnb==0) {
    int returnVal=setChar(bchar, bsent);
    if (returnVal==1) {
//    printf("success\n");
    }
    if (returnVal==0) {
//    printf("fail\n");
    }
  i++;
  }
  else {
    i++;
  }
}

printf("\n");

// print list A
printf("LIST A: ");
struct node *printlista;
printlista=asent->next;
  if (printlista==NULL) {
    printf("{ null set }\n");
  }
  else {
  printf("{ ");
    while (printlista->next!=NULL){
      printf("%c, ",printlista->value);
      printlista=printlista->next;
    }
  printf("%c }", printlista->value);
  printf("\n");
  }

// print list B
printf("LIST B: ");
struct node *printlistb;
printlistb=bsent->next;
  if (printlistb==NULL) {
    printf("{ null set }\n");
  }
  else {
  printf("{ ");
    while (printlistb->next!=NULL){
      printf("%c, ",printlistb->value);
      printlistb=printlistb->next;
    }
  printf("%c }", printlistb->value);
  printf("\n");
  }

printf("\n");

// print cardinality A
printf("CARDINALITY\n");
printf("LIST A: ");
int carda=count(asent);  // use count function for cardinatity
printf("%d\n", carda);

// print cardinality B
printf("LIST B: ");
int cardb=count(bsent);  // use count function for cardinatity
printf("%d\n", cardb);

printf("\n");

struct node *unionabsent=unionab(asent, bsent);
// print list UNION
printf("LIST UNION AB: ");
struct node *printlistunionab;
printlistunionab=unionabsent->next;
if (printlistunionab == NULL) { // if both sets empty
  printf("{ null set }\n");
}
else {
  printf("{ ");
while (printlistunionab->next!=NULL){
  printf("%c, ",printlistunionab->value);
  printlistunionab=printlistunionab->next;
}
  printf("%c }",printlistunionab->value);
  printf("\n");
}

printf("\n");

struct node *intersectionabsent=intersectionab(asent, bsent);
// print list INTERSECTION
printf("LIST INTERSECTION AB: ");
struct node *printlistintersectionab;
printlistintersectionab=intersectionabsent->next;
if (printlistintersectionab == NULL) {
  printf("{ null set }\n");
}
else {
  printf("{ ");
while (printlistintersectionab->next!=NULL){
  printf("%c, ",printlistintersectionab->value);
  printlistintersectionab=printlistintersectionab->next;
}
  printf("%c }",printlistintersectionab->value);
  printf("\n");
}

printf("\n");

struct node *aminusbsent=aminusb(asent, bsent);
// print list A MINUS B
printf("LIST A\\B: ");
struct node *printlistaminusb;
printlistaminusb=aminusbsent->next;
if (printlistaminusb == NULL) {
  printf("{ null set }\n");
}
else {
  printf("{ ");
while (printlistaminusb->next!=NULL){
  printf("%c, ",printlistaminusb->value);
  printlistaminusb=printlistaminusb->next;
}
  printf("%c }",printlistaminusb->value);
  printf("\n");
}

return 0;
}

struct node * aminusb(struct node *senta, struct node *sentb) {
  struct node *ll=setInit();
  struct node *current=ll;
  struct node *lista=senta->next;
  struct node *listb=sentb->next;

  if (lista==NULL && listb==NULL) {
    return (ll);
  }

  while(lista!=NULL) {
    struct node *llnew=malloc(sizeof(struct node));
    llnew->value=lista->value;
    current->next=llnew;
    llnew->next=NULL;

    current=llnew;
    lista=lista->next;
  }

  if (listb==NULL) {
    return (ll);
  }

/*
  struct node *testll=ll->next;
  printf("AFTER A SET CREATED for A minus B: ");
  while(testll!=NULL){
    printf("%c ",testll->value);
    testll=testll->next;
  }
  printf("\n");
*/

  struct node *newllprevious=ll;
  struct node *newllcurrent=ll->next;
  
  while (newllcurrent!=NULL) {
    while(listb->value!=newllcurrent->value && listb->next!=NULL) {
      listb=listb->next;
    }
    if (listb->value==newllcurrent->value && listb->next==NULL) {
      if (newllcurrent->next==NULL) {
        newllprevious->next=NULL;
        break;
      }
      newllprevious->next=newllcurrent->next;
      newllcurrent=newllcurrent->next;
    }
    else if (listb->value==newllcurrent->value && newllcurrent->next!=NULL) {
      newllprevious->next=newllcurrent->next;
      newllcurrent=newllcurrent->next;
    }
    else if (listb->value==newllcurrent->value && newllcurrent->next==NULL) {
      newllprevious->next=NULL;
      break;
    }
    else if (listb->value!=newllcurrent->value) {
      newllprevious=newllcurrent;
      newllcurrent=newllcurrent->next;
    }

    listb=sentb->next;
  }
return (ll);
}

struct node * intersectionab(struct node *senta, struct node *sentb) {
  struct node *ll=setInit();
  struct node *lista=senta->next;
  struct node *listb=sentb->next;

  struct node *current=ll;

  if (lista==NULL || listb==NULL) {
    return (ll);
  }

  while(lista!=NULL) {
    while (listb->value!=lista->value && listb->next!=NULL) {
      listb=listb->next;
    }
    if (listb->value==lista->value) {
      struct node *llnew=malloc(sizeof(struct node));
      llnew->value=listb->value;
      llnew->next=NULL;
      current->next=llnew;
      current=llnew;
    }

  listb=sentb->next;
  lista=lista->next;
  }
return (ll);
}

struct node * unionab(struct node *senta, struct node *sentb) {
  struct node *ll=setInit();
  struct node *previous=ll;
  struct node *current=ll->next;
  struct node *lista=senta->next;
  struct node *listb=sentb->next;

  if (lista==NULL && listb==NULL) {
    return (ll);
  }

  if (lista!=NULL) {
  while(lista!=NULL) {
    struct node *llnew=malloc(sizeof(struct node));
    llnew->value=lista->value;
    previous->next=llnew;
    llnew->next=NULL;

    previous=llnew;
    lista=lista->next;
  }

//  struct node *testll=ll;
//  printf("AFTER A SET PUT IN UNION: ");
//  while(testll!=NULL){
//    printf("%c ",testll->value);
//    testll=testll->next;
//  }
//  printf("\n");

  while(listb!=NULL) {
  previous=ll;
  current=ll->next;
    while (listb->value>current->value && current->next!=NULL) {
      previous=current;
      current=current->next;
    }
    if (listb->value>current->value && current->next==NULL) {
      struct node *llnew=malloc(sizeof(struct node));
      llnew->value=listb->value;
      llnew->next=NULL;
      previous->next=llnew;

      listb=listb->next;
    }
    else if (listb->value==current->value) {
      listb=listb->next; 
    }
    else if (listb->value<current->value) {
      struct node *llnew=malloc(sizeof(struct node));
      llnew->value=listb->value;
      llnew->next=current;
      previous->next=llnew;

      listb=listb->next; 
    } 
  }
  }
  else {
  while(listb!=NULL) {
    struct node *llnew=malloc(sizeof(struct node));
    llnew->value=listb->value;
    previous->next=llnew;
    llnew->next=NULL;

    previous=llnew;
    listb=listb->next;
  }

  }
return (ll);
}

struct node * setInit() {
  struct node *ll;
  ll=malloc(sizeof(struct node));
  ll->next=NULL;
}

int setChar (char setVal, struct node *sent) {
  struct node *previous;
  struct node *current;

  previous=sent;
  current=sent->next;

if (current==NULL) {
  struct node *ll=malloc(sizeof(struct node));
  ll->value=setVal;
  ll->next=NULL;
  previous->next=ll;
  return 1;
}

while (setVal>current->value && current->next!=NULL) {
  previous=current;
  current=current->next;
}

if (setVal>current->value && current->next==NULL) {
  struct node *ll=malloc(sizeof(struct node));
  ll->value=setVal;
  ll->next=NULL;
  current->next=ll;

  return 1;
}
else if (setVal==current->value) {
  return 0;
}
  struct node *ll=malloc(sizeof(struct node));
  ll->value=setVal;
  ll->next=current;
  previous->next=ll;

  return 1;
}

int count (struct node *sent) {
  int k=0;
  struct node *current;
  current=sent;
  while (current!=NULL) {
    current=current->next;
    k++;
  }
  k=k-1;
return (k);
}
