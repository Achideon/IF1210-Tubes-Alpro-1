#include "queue.h"

void createQueue(Queue *Q, int capacity){
    Q->capacity = capacity;
    Q->nEff = 0;
    Q->firstIdx = MARK_INT;
    Q->lastIdx = MARK_INT;
    Q->contents = (Qtype *) malloc(capacity * sizeof(Qtype));
    for (int i=0;i<=capacity;i++){
        Q->contents[i] = MARK_INT;
    }
}

int queueLength (Queue Q){
    return Q.nEff;
}

boolean isQueueFull(Queue Q){
    return Q.nEff == Q.capacity;
}

boolean isQueueEmpty(Queue Q){
    return Q.nEff == 0;
}

Qtype getQueueContents(Queue Q, int index){
    if (index>Q.nEff || index<0) return MARK_INT;
    return Q.contents[index];
}

Qtype getFirst(Queue Q){
    if (Q.firstIdx == 0){
        return Q.contents[0];
    }
    return IDX_UNDEF;
}

Qtype getLast(Queue Q){
    if (Q.lastIdx>=0){
        return Q.contents[Q.lastIdx];
    }
    return IDX_UNDEF;
}

void nextQueue(Queue *Q, int*id){
    if (Q->nEff == 0) return;
    for (int i=1;i<Q->lastIdx;i++){
        Q->contents[i] = Q->contents[i+1];
    }
    Q->nEff -= 1;
    Q->contents[Q->lastIdx] = IDX_UNDEF;
    if (Q->nEff == 0){
        Q->lastIdx -= 1;
        Q->firstIdx -= 1;
    }else{
        Q->lastIdx -= 1;
    }
}

void addQueue (Queue *Q, int id){
    if(!(isQueueFull(*Q))){
        if(isQueueEmpty(*Q)){ 
            Q->firstIdx = 0;
            Q->lastIdx = 0;
        }
        else Q->lastIdx += 1;
        Q->contents[Q->lastIdx] = id;
        Q->nEff += 1;
    }
}

void viewQueue (Queue Q){
    for (int i=0;i<=Q.nEff;i++){
        printf("%d ", Q.contents[i]);
    }
}