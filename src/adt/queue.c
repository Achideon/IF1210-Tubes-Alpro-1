#include "queue.h"

void createQueue(Queue *Q){
    createLinkedList(&Q->head);
    Q->tail = Q->head;
}

int queueLength (Queue Q){
    if(isLinkedListEmpty(Q.head)) return 0;
    else if(Q.head->info == 0) return 0;
    int k = 0;
    Address temp = Q.head;
    while(temp != Q.tail){
        k++;
        temp = temp->next;
    }
    return k + 1;
}

boolean isQueueEmpty(Queue Q){
    return Q.head == NULL;
}

Qtype getQueueContents(Queue Q, int index){
    int k = 0;
    Address temp = Q.head;
    if(isLinkedListEmpty(Q.head)) return MARK_INT;
    while(temp != Q.tail && k < index){
        k++;
        temp = temp->next;
    } 
    if(k == index) return temp->info;
    else return MARK_INT;
}

Qtype getFirst(Queue Q){
    if (Q.head != NULL){
        return Q.head->info;
    }
    return IDX_UNDEF;
}

Qtype getLast(Queue Q){
    if (Q.tail != NULL){
        return Q.tail->info;
    }
    return IDX_UNDEF;
}

void nextQueue(Queue *Q, int*id){
    if (isQueueEmpty(*Q)){ 
        printf("Ehhhh, antrian sudah kosong! X_X\n");
        return;
    }
    Address temp = Q->head;
    Q->head = Q->head->next;
    if(isQueueEmpty(*Q)){
        Q->tail = NULL;
    }
    free(temp);
}

void addQueue (Queue *Q, int id){
    Address newtail;
    newtail = newNode(id);
    if(isQueueEmpty(*Q)){
        Q->head = Q->tail = newtail;
    }
    else{
        Q->tail->next = newtail;
        Q->tail = Q->tail->next;
    }
}

void viewQueue (Queue Q){
    printf("[");
    if(!isQueueEmpty(Q)){
        Address temp = Q.head;
        while(temp != Q.tail){
            printf("%d ", temp->info);
            temp = temp->next;
        } printf("%d", Q.tail->info);
    }
    printf("]");
}