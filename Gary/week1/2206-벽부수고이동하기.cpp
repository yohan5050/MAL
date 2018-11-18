//
//  main.c
//  MAL-벽부수고이동하기
//
//  Created by GaryNoh on 2018. 11. 13..
//  Copyright © 2018년 Macbook. All rights reserved.
//

#include <stdio.h>

#define MAX 1000
#define QMAX MAX*MAX*2 //QUEUE 사이즈 주의하자
int N, M;

int map[MAX][MAX];
int visited[MAX][MAX][2];
int front = -1, rear = -1;

typedef struct{
    int r;
    int c;
    int used;
}NODE;

int q_size = 0;
NODE queue[QMAX];


int dr[4] = {0, 0, 1, -1};
int dc[4] = {-1, 1, 0, 0};

int pop_q(NODE *item){
    if(front == rear) return -1;
    *item = queue[++front];
    --q_size;
    return 1;
}

int push_q(int r, int c, int used){
    //queue is full
    if(rear == QMAX - 1) return -1;
    if(map[r][c] == 1) ++used;
    visited[r][c][used] = 1;
    
    ++rear;
    queue[rear].r = r;
    queue[rear].c = c;
    queue[rear].used = used;
    ++q_size;
    return 1;
}

int is_available(int r, int c, int used){
    if(r < 0 || c < 0 || r > N-1 || c > M-1 || visited[r][c][used]) return 0;
    if(map[r][c] && used) return 0;
    return 1;
}

int is_dest(int r, int c){
    if(r == N-1 && c == M-1) return 1;
    return 0;
}

int get_min(){
    int i, j;
    int nr, nc, nu;
    int min_dist = 0;
    int goal = 0;

    
    push_q(0, 0, 0);
    
    while(q_size && !goal){
        NODE item;
        int size = q_size;
        min_dist++;
        for(i = 0 ; i < size; i++){
            pop_q(&item);
            if(is_dest(item.r, item.c)){
                goal = 1;
                break;
            }
            for(j = 0 ; j < 4; j++){
                nr = item.r + dr[j];
                nc = item.c + dc[j];
                nu = item.used;
                if(is_available(nr, nc, nu)) {
                    push_q(nr, nc, nu);
                }
            }
        }
    }
    return goal ? min_dist : -1;
}

void read_input(){
    int i, j;
    char input[MAX+1];
    
    scanf("%d %d", &N, &M);
    for(i = 0 ; i < N; i++){
        scanf("%s", input);
        for(j = 0 ; j < M; j++){
            map[i][j] = input[j] - '0';
        }
    }
}

int main(int argc, const char * argv[]) {
    read_input();
    printf("%d\n", get_min());
    return 0;
}

