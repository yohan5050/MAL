//
//  main.cpp
//  MAL-중량제한
//
//  Created by GaryNoh on 2018. 11. 15..
//  Copyright © 2018년 Macbook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define INIT_QNODE(X, S, E, C) {X.s = S; X.e = E; X.cost = C;}
#define INIT_ADJNODE(X, E, C) {X->e = E; X->cost = C;}
#define INF 1000000000
typedef struct _adjlist{
    int e;
    int cost;
    struct _adjlist *next;
    
    _adjlist(){
        next = (struct _adjlist *)0;
    }
}ADJ_LIST;

typedef struct _qnode{
    int s;
    int e;
    int cost;
}QNODE;

typedef struct _prio_q{
    QNODE heap[MAX_N+1];
    int size;
    
    _prio_q(){
        heap[0].cost = 0;
        size = 0;
    }
    
    void swap(QNODE *n1, QNODE *n2){
        QNODE temp;
        temp = *n1;
        *n1 = *n2;
        *n2 = temp;
    }
    
    int push(QNODE item){
        if(size > MAX_N + 1) return -1;
        
        heap[++size] = item;
        
        int cur = size;
        int par = size / 2;
        
        while(cur > 1 && heap[cur].cost > heap[par].cost){
            swap(&heap[cur], &heap[par]);
            cur = par;
            par = par/2;
        }
        return 1;
    }
    
    int pop(QNODE *pop_item){
        int cur = 1;
        int lc, rc;
        int max_node = cur;
        
        if(size <= 0) return -1;
        
        *pop_item = heap[1];
        heap[1] = heap[size--];
        
        lc = cur*2;
        rc = cur*2 + 1;
        
        while(lc <= size){
            if(heap[max_node].cost < heap[lc].cost){
                max_node = lc;
            }
            if(rc <= size && heap[max_node].cost < heap[rc].cost){
                max_node = rc;
            }
            if(max_node == cur) break;
            else{
                swap(&heap[cur], &heap[max_node]);
                cur = max_node;
                lc = cur*2;
                rc = cur*2 + 1;
            }
        }
        return 1;
    }
}PRIO_Q;

ADJ_LIST *cities_list[MAX_N+1];
PRIO_Q prio_q;
int N, M;
int start, finish;
int max_cost[MAX_N+1];


void update_cand(int src, int limit){
    //printf("visit : %d\n", src);
    ADJ_LIST *ptr = cities_list[src]->next;
    QNODE *qnode;
    while(ptr){
        int dest = ptr->e;
        int cost = ptr->cost;
        
        if(max_cost[dest] < cost){
            max_cost[dest] = cost;
            qnode = new QNODE();
            qnode->s = src;
            qnode->e = dest;
            qnode->cost = cost > limit ? limit : cost;
            prio_q.push(*qnode);
        }
        ptr = ptr->next;
    }
}

int get_min(){
    QNODE root;
    int m_max = -1;
    INIT_QNODE(root, 0, start, INF);
    max_cost[start] = INF + 1;
    prio_q.push(root);
    
    while(prio_q.size > 0){
        QNODE pop_item;
        if(prio_q.pop(&pop_item) > 0){
            //reach goal
            if(pop_item.e == finish){
                m_max = pop_item.cost;
                break;
            }
            //update cands
            else{
                update_cand(pop_item.e, pop_item.cost);
            }
        }
        //pop 실패
        else return -1;
    }
    return m_max;
}

void init_graph(int s, int e, int c){
    ADJ_LIST *new_node;
    new_node = new ADJ_LIST();
    INIT_ADJNODE(new_node, e, c);
    new_node->next = cities_list[s]->next;
    cities_list[s]->next = new_node;
    
    new_node = new ADJ_LIST();
    INIT_ADJNODE(new_node, s, c);
    new_node->next = cities_list[e]->next;
    cities_list[e]->next = new_node;
}

void read_input(){
    int s, e, c;
    int i;
    
    scanf("%d %d",&N ,&M);
    //head 생성
    for(i = 1 ; i <= N; i++){cities_list[i] = new ADJ_LIST();}
    
    //인접리스트 생성
    for(i = 0 ; i < M; i++) {
        scanf("%d %d %d", &s, &e, &c);
        init_graph(s, e, c);
    }
    scanf("%d %d", &start, &finish);
    
}

void test(){
    //adj list
    /*
    for(int i = 1 ; i <= N; i++){
        ADJ_LIST *ptr = cities_list[i]->next;
        printf("%d -> ", i);
        while(ptr){
            printf("/ %d [%d] ", ptr->e ,ptr->cost);
            ptr = ptr->next;
        }
        printf("\n");
    }
     */
    
    //push heap
    /*
    QNODE qnode;
    
    INIT_QNODE(qnode, 1, 2, 4);
    prio_q.push(qnode);
    INIT_QNODE(qnode, 1, 3, 6);
    prio_q.push(qnode);
    INIT_QNODE(qnode, 1, 5, 2);
    prio_q.push(qnode);
    INIT_QNODE(qnode, 2, 4, 3);
    prio_q.push(qnode);
    INIT_QNODE(qnode, 2, 5, 1);
    prio_q.push(qnode);
    INIT_QNODE(qnode, 3, 4, 9);
    prio_q.push(qnode);
    INIT_QNODE(qnode, 4, 5, 3);
    prio_q.push(qnode);
    
    for(int i = 0 ; i < 7; i++){
        prio_q.pop(&qnode);
        printf("%d %d %d\n", qnode.s, qnode.e, qnode.cost);
    }
     */
}


int main(int argc, const char * argv[]) {
    //read input
    read_input();
    //test();
    //get min
    printf("%d\n", get_min());
    return 0;
}

