#include<bits/stdc++.h>
using namespace std;
int arr[8][8], visited[8];
int positionQueen[8], successful=0, sum=0, sum1=0;
map<int,int>mp;
vector<pair<int,int>>newPairs, prevPairs;
float firstDivisor=2.5;
int secondDivisor=5;
int side(int arr[][8], int i, int j){
    if(j==8) return 0;
    if(arr[i][j]==1) return 1+side(arr, i, j+1);
    else return side(arr, i, j+1);
}

int down(int arr[][8], int i, int j){
    if(i==8) return 0;
    if(arr[i][j]==1) return 1+down(arr, i+1, j);
    else return down(arr, i+1, j);
}

int rightDiagonal(int arr[][8], int i, int j){
    if(i>=8 || j>=8) return 0;
    if(arr[i][j]==1) return 1+rightDiagonal(arr, i+1, j+1);
    else return rightDiagonal(arr, i+1, j+1);
}

int leftDiagonal(int arr[][8], int i, int j){
    if(i>=8 || j<0) return 0;
    if(arr[i][j]==1) return 1+leftDiagonal(arr, i+1, j-1);
    else return leftDiagonal(arr, i+1, j-1);
}

int heuristic(int arr[][8])
{
    int count1=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++){
            if(arr[i][j]==1){
                count1+=side(arr, i, j+1);
                count1+=down(arr, i+1, j);
                count1+=rightDiagonal(arr, i+1, j+1);
                count1+=leftDiagonal(arr, i+1, j-1);
            }
        }
    }
    return count1;
}

void PrintEightQueens(int arr[][8])
{
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(arr[i][j]==0){
                cout<<".";
            }
            else{
                cout<<"Q";
            }
            cout<<" ";
        }
        cout<<endl;
    }
}

void EightQueen(int arr[][8], int minimum, int iterations, int steps)
{
     if(heuristic(arr)==0){
        cout<<endl<<"Final: "<<iterations<<endl;
        sum+=int(steps/firstDivisor);
        PrintEightQueens(arr);
        if(mp[iterations]==0){
           successful++;
           mp[iterations]=1;
        }
        return;
    }
    int indx=-1,jndx=-1, prvindex=-1, prvjndex=-1;
    for(int i=0;i<8;i++){
       arr[i][positionQueen[i]]=0;
       for(int j=0;j<8;j++){
            arr[i][j]=1;
            int hrstc=heuristic(arr);
            if(hrstc<minimum){
                indx=i;
                jndx=j;
                prvindex=i;
                prvjndex=positionQueen[i];
                minimum=hrstc;
                newPairs.clear();
                prevPairs.clear();
            }
            else if(hrstc==minimum){
                newPairs.push_back(make_pair(i,j));
                prevPairs.push_back(make_pair(i,positionQueen[i]));
            }
            arr[i][j]=0;
       }
       arr[i][positionQueen[i]]=1;
    }
    if(newPairs.size()>0){
        int size1=newPairs.size();
        int random=rand()%size1;
        indx=newPairs[random].first, jndx=newPairs[random].second;
        prvindex=prevPairs[random].first, prvjndex=prevPairs[random].second;
        newPairs.clear();
        prevPairs.clear();
    }
    if(indx!=-1 && visited[indx]<60){
        visited[indx]++;
        arr[prvindex][prvjndex]=0;
        arr[indx][jndx]=1;
        positionQueen[indx]=jndx;
        EightQueen(arr, minimum, iterations, steps+1);
    }
    else{
        sum1+=steps/secondDivisor;
    }
}

int main()
{
    srand(time(0));
    int n=1000;
    for(int i=1;i<=n;i++){
      memset(arr,0,sizeof(arr));
      for(int j=1;j<=8;j++){
        int x=rand()%8;
        arr[j-1][x]=1;
        positionQueen[j-1]=x;
      }
      memset(visited,0, sizeof(visited));
      EightQueen(arr, 65, i, 0);
    }
    cout<<"Total Success: "<<(successful/(double)n)*100.0<<"%"<<endl;
    cout<<"Average Successful Steps: "<<sum/successful<<endl;
    cout<<"Average Failure Steps: "<<sum1/(n-successful)<<endl;
}

