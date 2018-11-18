//
//  main.c
//  MAL-k번째큰수
//
//  Created by GaryNoh on 2018. 11. 11..
//  Copyright © 2018년 Macbook. All rights reserved.
//
//시간초과가 난다
#include <stdio.h>
#define MAX 5000000
#define SWAP(X, Y, T){T = X; X = Y; Y = T;}
int arr[MAX];
int N, K;

int check_sort(){
    for(int i = 1; i < N; i++){
        if(arr[i-1] > arr[i]) return 0;
    }
    return 1;
}

int partition(int s, int e){
    int pivot = arr[s];
    int left = s + 1;
    int right = e;
    int temp;
    while(left <= right){
        while(arr[left] <= pivot && left <= e)left++;
        //등호를 포함시키면 안된다
        while(arr[right] >= pivot && right >= s+1)right--;
        if(left <= right) SWAP(arr[left], arr[right], temp);
    }
    SWAP(arr[s], arr[right], temp);
    return right;
}

int get_k_element(int k){
    int ret;
    int s = 0, e = N-1;
    while(s <= e){
        ret = partition(s, e);
        if(ret == k) return arr[ret];
        else if(ret < k) s = ret+1;
        else e = ret-1;
    }
    return -1;
}
int main(int argc, const char * argv[]) {
    int i;
    int ans;
    
    //read input
    scanf("%d %d", &N, &K);
    for(i = 0 ; i < N; i++) scanf("%d", &arr[i]);
    
    if(check_sort()){
        ans = arr[K];
    }
    else{
        //get ans
        ans = get_k_element(K-1);
    }//print ans
    
    printf("%d\n", ans);
    return 0;
}

