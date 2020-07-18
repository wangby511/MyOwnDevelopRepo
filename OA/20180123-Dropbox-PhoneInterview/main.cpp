//
//  main.cpp
//  20180123Dropbox
//
//  Created by 王博远 on 2018/1/26.
//  Copyright © 2020年 王博远. All rights reserved.
//

#include <iostream>
#include <vector>

void gameOfLife(std::vector<std::vector<int>>& grid) {
    int n = grid.size();
    if(n == 0)return;
    int m = grid[0].size();
    if(m == 0)return;
    std::vector<int> cache(m,0);
    std::vector<int> cache1(m,0);
    for(int i = 0;i < n;i++){
        if(i == 1){
            for(int k = 0;k < m;k++){
                cache1[k] = cache[k];
            }
        }
        if(i >= 2){
            for(int k = 0;k < m;k++){
                grid[i - 2][k] = cache1[k];
                cache1[k] = cache[k];
            }
        }
        for(int j = 0;j < m;j++){
            int cnt = 0;
            for(int kx = std::max(i - 1,0);kx <= std::min(i + 1,n - 1);kx++){
                for(int ky = std::max(j - 1,0);ky <= std::min(j + 1,m - 1);ky++){
                    if(kx == i && ky == j)continue;
                    if(grid[kx][ky])cnt++;
                }
            }
            if(grid[i][j]){
                if(cnt < 2 || cnt > 3)cache[j] = 0;
                else cache[j] = 1;
            }else{
                if(cnt == 3)cache[j] = 1;
                else cache[j] = 0;
            }
        }
    }
    for(int k = 0;k < m;k++){
        if(n - 2 >= 0)grid[n - 2][k] = cache1[k];
        if(n - 1 >= 0)grid[n - 1][k] = cache[k];
    }
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> grids = {
        {0,1,0},
        {0,0,1},
        {1,1,1},
        {0,0,0}};
    gameOfLife(grids);
    for(int i = 0;i < grids.size();i++) {
        for(int j = 0;j < grids[0].size();j++) {
            std::cout<<grids[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}
