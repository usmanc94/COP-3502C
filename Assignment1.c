/*
    Usman Chaudhry
    COP 3502C
    Assignment 1
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//structure of the zones

struct zone

{

    int x1,y1,x2,y2; //zones quardinates (x1,y1)=>lower left quardinates, (x2,y2)=> upper right quardinates

    struct zone *next;

};

// add zones to list

struct zone *add (struct zone *listHead,int xi1,int yi1,int xi2,int yi2)

{

    struct zone *temp=(struct zone*)malloc(sizeof(struct zone));

    temp->x1=xi1;

    temp->y1=yi1;

    temp->x2=xi2;

    temp->y2=yi2;

    temp->next=NULL;

    if(listHead==NULL)

    {

        listHead=temp;

        return listHead;

    }

    struct zone *t=listHead;

    while(t->next!=NULL)

        t=t->next;



    t->next=temp;

    return listHead;

}

bool isOverlap(struct zone *temp,int xi1,int yi1,int xi2,int yi2)

{

//if one zone on left to other zones then run this

    if(xi1>=temp->x2 || temp->x1 >=xi2)

        return false;

// if one zone is upper to other zones then run this

    if(yi1>=temp->y2 || temp->y1 >= yi2)

        return false;

    return true;

}

int overlapping(struct zone *listHead,int xi1,int yi1,int xi2,int yi2)

{

    struct zone *temp=listHead;

    int overlapCount=0;

    if(temp==NULL) //No zone exist;

        return 0;

    while(temp)

    {
        if(isOverlap(temp,xi1,xi2,yi1,yi2)) // find overlapping zones

            overlapCount++;

        temp=temp->next; // visit all zones
    }

    return overlapCount; // return overlapping zones

}

int main()

{
    struct zone *listHead=NULL;

    int n,xi1,xi2,yi1,yi2;

    scanf("%d",&n); // number of zones to place

    while(n--)

    {

        scanf("%d%d%d%d",&xi1,&yi1,&xi2,&yi2); // read quardinates of zone from stdin

        printf("%d\n",overlapping(listHead,xi1,xi2,yi1,yi2)); //print overlapping zones

        listHead=add(listHead,xi1,yi1,xi2,yi2); // add zone to Linked list
    }

    return 0;

}
