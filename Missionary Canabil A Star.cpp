#include<bits/stdc++.h>
using namespace std;
struct game{
    int leftMissionary;
    int leftCannibal;
    int boat;
    int parent;
    int rightMissionary;
    int rightCannibal;
    int cost;

    bool operator < ( const game& p ) const {  return cost > p.cost;   }
 };
 vector<game>checkWithPrevious;
 vector<game>v[30];
 bool checkSituation(game var)
 {
     if((var.leftCannibal>var.leftMissionary && var.leftMissionary!=0) || (var.rightCannibal>var.rightMissionary && var.rightMissionary!=0) ){
        return true;
     }
     return false;
 }

 int attemps=0, indx=0;

 bool checkAgainstPrevious(game var)
 {
     for(int i=0;i<checkWithPrevious.size();i++){
        if(checkWithPrevious[i].boat%2==var.boat%2 && checkWithPrevious[i].leftMissionary==var.leftMissionary
           && checkWithPrevious[i].leftCannibal==var.leftCannibal
           && checkWithPrevious[i].rightCannibal==var.rightCannibal
        && checkWithPrevious[i].rightMissionary==var.rightMissionary)
        {
            return true;
        }
     }
     return false;
 }

void printPath(int indx, int fixedIndx, int term, int prevIndex)
{
    cout<<"Term: "<<term<<endl;
    if(indx==fixedIndx){
        cout<<"\tInitially Boat is on the Left Side"<<endl;
    }
    else if(v[indx][0].boat%2==0){
        cout<<"\tBoat is going from the Left Side to the Right Side ";
    }
    else{
        cout<<"\tBoat is going from the Right Side to the Left Side ";
    }
    if(indx!=fixedIndx)
    {
        int x=abs(v[indx][0].leftMissionary-v[prevIndex][0].leftMissionary);
        int y=abs(v[indx][0].leftCannibal-v[prevIndex][0].leftCannibal);
        if(x>0 && y>0) cout<<"Carrying "<<x<<" Missionary and "<<y<<" Cannibal";
        else if(x>0) cout<<"Carrying "<<x<<" Missionary";
        else if(y>0) cout<<"Carrying "<<y<<" Cannibal";
        cout<<endl;
    }
   cout<<endl;
   cout<<"\tLeft Side (Missionary, Cannibal): ( "<<v[indx][0].rightMissionary<<" , "<<v[indx][0].rightCannibal<<" ) "<<endl<<endl;
   cout<<"\tRight Side (Missionary, Cannibal): ( "<<v[indx][0].leftMissionary<<" , "<<v[indx][0].leftCannibal<<" )"<<endl<<endl;
   if(v[indx][0].parent!=-1){
     printPath(v[indx][0].parent, fixedIndx, term+1, indx);
   }
}

int heuristic(int missionary, int cannibal, int boat)
{
    return (missionary-0)+(cannibal-0)+(boat-1);
}

void AStarSearch()
{
    priority_queue<game>q;
    game g;
    g.leftCannibal=3;
    g.leftMissionary=3;
    g.rightCannibal=0;
    g.rightMissionary=0;
    g.boat=0;
    g.parent=-1;
    g.cost=heuristic(g.leftMissionary, g.leftCannibal, g.boat);
    q.push(g);
    while(!q.empty()){
        game var=q.top();
        q.pop();
        if(checkAgainstPrevious(var)) continue;
        checkWithPrevious.push_back(var);
        if(var.leftMissionary==0 && var.leftCannibal==0){
            cout<<"Attemps: "<<++attemps<<endl;
            v[indx].push_back(var);
            printPath(indx, indx, 0, indx);
        }
        if(var.leftMissionary<0 || var.leftCannibal<0 || var.rightCannibal<0 || var.rightMissionary<0 || var.leftMissionary>3 || var.leftCannibal>3 || var.rightCannibal>3 || var.rightMissionary>3){
            continue;
        }
        if(checkSituation(var)) continue;
        v[indx].push_back(var);
        if(var.boat%2==0){
            var.parent=indx;
            var.boat+=1;
            /// One and Two missionary
            var.rightMissionary+=1;
            var.leftMissionary-=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)-1;
            q.push(var);
            var.rightMissionary+=1;
            var.leftMissionary-=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)-2;
            q.push(var);
            var.rightMissionary-=2;
            var.leftMissionary+=2;

            /// One and Two Cannabil
            var.leftCannibal-=1;
            var.rightCannibal+=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)-1;
            q.push(var);
            var.leftCannibal-=1;
            var.rightCannibal+=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)-2;
            q.push(var);
            var.leftCannibal+=2;
            var.rightCannibal-=2;

            /// One cannabil and one missionary
            var.leftCannibal-=1;
            var.rightCannibal+=1;
            var.leftMissionary-=1;
            var.rightMissionary+=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)-2;
            q.push(var);
        }
        else{
            var.parent=indx;
            var.boat+=1;
            /// One and Two missionary
            var.rightMissionary-=1;
            var.leftMissionary+=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)+1;
            q.push(var);
            var.rightMissionary-=1;
            var.leftMissionary+=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)+2;
            q.push(var);
            var.rightMissionary+=2;
            var.leftMissionary-=2;

            /// One and Two Cannabil
            var.leftCannibal+=1;
            var.rightCannibal-=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)+1;
            q.push(var);
            var.leftCannibal+=1;
            var.rightCannibal-=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)+2;
            q.push(var);
            var.leftCannibal-=2;
            var.rightCannibal+=2;

            /// One cannabil and one missionary
            var.leftCannibal+=1;
            var.rightCannibal-=1;
            var.leftMissionary+=1;
            var.rightMissionary-=1;
            var.cost=heuristic(var.leftMissionary, var.leftCannibal, var.boat)+2;
            q.push(var);
        }
        indx++;
    }
}

int main()
{
    AStarSearch();
}
