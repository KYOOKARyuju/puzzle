#include <stdio.h>
#include <string.h>

#define true 1
#define false 0

int check_line(int n, int x, int array[9][9]);
int check_column(int n, int y, int array[9][9]);
int check_group(int n, int x, int y, int array[9][9]);
int check(int n,int x, int y, int array[9][9]);
void print_board(int array[9][9]);


//与えられたnが行で重複していないかの確認。していたらfalse, していなければtrue.
int check_line(int n, int x, int array[9][9]){
        for(int i =0; i<9; i++){
            if(array[x][i] == n) return false;
        }
    return true;
}

//与えられたnが列で重複していないかの確認。していたらfalse, していなければtrue.
int check_column(int n, int y, int array[9][9]){
    for(int i =0; i<9; i++){
        if(array[i][y] == n)return false;
    }
    return true;
}

//与えられたnがブロックで重複していないかの確認。していたらfalse, していなければtrue.
int check_group(int n, int x, int y, int array[9][9]){
    //ブロックの左上のを場所をx1, y1として置く.
    int x1 = (x/3)*3;
    int y1 = (y/3)*3;
        //そのブロックを左上から右下にかけてnと一致しているのがないか確認.一致しているのがあればfalse,なければtrue.
       for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(array[x1+i][y1+j]==n)return false;
            }
        }
    return true;
}

//nが3つの条件すべてを満たしていればtrue,満たしていなければfalse.
int check(int n,int x, int y, int array[9][9]){
    return check_column(n, y, array) && check_line(n, x, array) && check_group(n, x, y, array);
}


//マスを表示させる関数
void print_board(int array[9][9]){
    for(int i=0; i <9;i++){
            for(int j=0; j<9;j++){
                printf("%d",array[i][j]);
                    if(j == 8){
                        break;
                    }         
                printf(",");
            }
        printf("\n");
    }
}


void solver(int n, int array[9][9]){
    if(n==81){
        print_board(array);
    }else{
        //nを1から80までの再帰関数として足していく。そのため、nを９で割ることで2次元配列の行と列の指定をしている.
        int x = n/9;
        int y = n%9;


        if(array[x][y]!=0){
            solver(n+1,array);//再帰関数としてnを+1
        }else{
            for(int i=1;i<=9;i++){
                if(check(i, x, y, array)){//1~9まですべてがfalseの場合はそのsolverを抜け出して、一つ前のsolverのarray[x][y]＝０に代入いき、そこからfor分のiを再開させる

                    array[x][y]=i;//2次元配列の任意の場所が3つの条件を満たしていたら、iを代入
                    solver(n+1, array);//そしてnを+1させる、、、、memoこのやり方だと条件を満たしている値が複数あった場合、数が小さい方にしかならないのでは？
                    array[x][y]=0;//1~9まで行ってすべて違ったらこの場所を０にして戻ってやり直す
                }
            }
        }
    }
}



int main(){
    //数独の初期化
    int array[9][9] = {
        {'\0' , '\0' , '\0' ,  6  ,  5  , '\0' ,  1  , 4   , '\0'},
        {3    , '\0' , '\0' , '\0', '\0',   1  , '\0', 5   , 2   },
        {'\0' , '\0' , '\0' , '\0',    3, '\0' , '\0', 9   , '\0'},
        {'\0' , '\0' , '\0' ,    3, '\0',   6  , '\0', '\0', '\0'},
        {'\0' , 9    , '\0' , 8   , '\0', '\0' , '\0', '\0', 6   },
        {2    , '\0' ,8     , '\0', '\0', '\0' , '\0','\0' , '\0'},
        {'\0' , '\0' , '\0' , '\0', '\0', '\0' , '\0', 1   , '\0'},
        {'\0' , '\0' , '\0' , 7   ,   4 ,   8  , '\0', '\0', '\0'},
        {7    , 2    , '\0' , '\0', '\0', '\0' , 9   , '\0', '\0'},
    };

    //print_board(array);
    int n = 0;
    solver(n,array);

    return 0;
}
