#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int*** make_3D_array(int m, int n, int l, int init){
    int*** one = new int**[m];

    // for(int i = 0; i < m; i++){
    //     one[i] = new int*[n];
    // }

    for(int i = 0; i < m; i++){
        one[i] = new int*[n];
        for(int j = 0; j < n; j++){
            one[i][j] = new int[l];
        }
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < l; k++){
                one[i][j][k] = init;
            }
        }
    }

    return one;
    
}

/*3차원 배열 생성 함수========================================*/
void free_3D_array(int*** arr, int m, int n, int l){

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            delete[] arr[i][j];
        }
    }

    for(int i = 0; i < m; i++){
        delete[] arr[i];
    }

    delete[] arr;
}
/*3차원 배열 할당 해제 함수========================================*/


void print_2D_array(int** arr, int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

void print_3D_array(int*** arr, int m, int n, int l){

    for(int i = 0; i< m; i++){
        print_2D_array(arr[i],n,l);
        cout<<endl;
    }
}


/*====================배열을 출력해 주는 함수==========================*/

int LCS(string X, string Y, string Z, int*** memo){
    /*문자가 없는 string이 들어오면 0을 반환*/
    if(X.size() == 0 || Y.size() == 0 || Z.size() == 0)
        return 0;
    
    int x_num = X.size(), y_num = Y.size(), z_num = Z.size();

    /*이미 계산 했던 값이면 바로 반환*/
    if(memo[x_num][y_num][z_num] != -1){
        //cout<<"이미 저장되어 있으면 반환"<<endl;
        return memo[x_num][y_num][z_num];
    }

    char x = X.back(), y = Y.back(), z = Z.back();

    
    if(x == y && y == z){
        X.pop_back();
        Y.pop_back();
        Z.pop_back();

        memo[x_num][y_num][z_num] = LCS(X,Y,Z,memo) + 1;
        //cout<< "한번도?"<<endl;
        return memo[x_num][y_num][z_num];
    }

    X.pop_back();
    int minus_x = LCS(X, Y, Z, memo);
    memo[x_num - 1][y_num][z_num] = minus_x;
    X.push_back(x);

    Y.pop_back();
    int minus_y = LCS(X, Y, Z, memo);
    memo[x_num][y_num-1][z_num] = minus_y;
    Y.push_back(y);

    Z.pop_back();
    int minus_z = LCS(X, Y, Z, memo);
    memo[x_num][y_num][z_num - 1] = minus_z;
    Z.push_back(z);

    /*X, Y, Z 중에서 하나를 선택하여 문자열을 하나 제거한 상태에서의 LCS를 전부 구했다.*/

    int temp = max( max(minus_x, minus_y), minus_z);

    memo[x_num][y_num][z_num] = temp;

    return memo[x_num][y_num][z_num];


}

int LCS(string X, string Y, string Z){
    int*** arr = make_3D_array(X.size() + 1, Y.size() + 1, Z.size() + 1, -1);

    int temp = LCS(X,Y,Z,arr);

    //print_3D_array(arr ,X.size() + 1, Y.size() + 1, Z.size() + 1);

    free_3D_array(arr ,X.size() + 1, Y.size() + 1, Z.size() + 1);

    return temp;
}

int main(){

    string str1, str2, str3;
    char c;
    while((c = getchar()) != '\n'){
        str1.push_back(c);
    }
   
   while((c = getchar()) != '\n'){
        str2.push_back(c);
    }

    while((c = getchar()) != '\n'){
        str3.push_back(c);
    }

    int temp = LCS(str1, str2, str3);

    cout<<temp<<endl;
}
