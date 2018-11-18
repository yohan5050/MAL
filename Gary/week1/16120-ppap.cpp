//
//  main.c
//  MAL-PPAP
//
//  Created by GaryNoh on 2018. 11. 10..
//  Copyright © 2018년 Macbook. All rights reserved.
//

#include <stdio.h>
#define MAX 10
int m_stack[MAX];
char s[MAX];
int top = -1;
int step = 0;

int push_stack(char item){
    if(top == MAX) return -1;
    m_stack[++top] = item;
    return 1;
}

int pop_stack(char *item){
    if(top == -1) return -1;
    *item = m_stack[top--];
    return 1;
}

int chk_ppap(){
    if(m_stack[top] == 'P' && m_stack[top-1] == 'A' &&\
       m_stack[top-2] == 'P' && m_stack[top-3] == 'P') return 1;
    return 0;
}

int main(int argc, const char * argv[]) {
    //read input
    scanf("%s", s);
    int i = 0;
    while(s[i]){
        push_stack(s[i++]);
        if(top >= 3){
            if(chk_ppap()) top -= 3;
        }
    }
    
    //printf("%d %c\n", top, m_stack[0]);
    if(top == 0 && m_stack[0] == 'P') printf("PPAP\n");
    else printf("NP\n");
    return 0;
}

