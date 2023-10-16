#include<bits/stdc++.h>
using namespace std;
struct game{
    int leftMissionary;
    int leftCannibal;
    int boat;
    int rightMissionary;
    int rightCannibal;
 };
 vector<game>checkWithPrevious;
 bool checkSituation(game var)
 {
     if((var.leftCannibal>var.leftMissionary && var.leftMissionary!=0) || (var.rightCannibal>var.rightMissionary && var.rightMissionary!=0) ){
        return true;
     }
     return false;
 }

 int attemps=0;

 bool checkAgainstPrevious(game var, int boatSide)
 {
     for(int i=0;i<checkWithPrevious.size();i++){
        if(checkWithPrevious[i].boat==boatSide && checkWithPrevious[i].leftMissionary==var.leftMissionary
           && checkWithPrevious[i].leftCannibal==var.leftCannibal
           && checkWithPrevious[i].rightCannibal==var.rightCannibal
        && checkWithPrevious[i].rightMissionary==var.rightMissionary)
        {
            return true;
        }
     }
     return false;
 }

void DFS(game var, int boat, vector<game>& v)
{
    if(var.leftMissionary<0 || var.leftCannibal<0 || var.rightCannibal<0 || var.rightMissionary<0 || var.leftMissionary>3 || var.leftCannibal>3 || var.rightCannibal>3 || var.rightMissionary>3) return;
    if(var.leftMissionary==0 && var.leftCannibal==0){
        cout<<"Attemps: "<<++attemps<<endl;
        for(int i=0;i<v.size();i++){
            cout<<"Step: "<<i<<endl;
            if(i==0){
                    cout<<"\tInitially Boat is on the Left Side"<<endl;
            }
            else if(v[i].boat==0){
                cout<<"\tBoat is going from the Left Side to the Right Side ";
            }
            else{
                cout<<"\tBoat is going from the Right Side to the Left Side ";
            }

            if(i!=0){
                int x=abs(v[i].leftMissionary-v[i-1].leftMissionary);
                int y=abs(v[i].leftCannibal-v[i-1].leftCannibal);
                if(x>0 && y>0) cout<<"Carrying "<<x<<" Missionary and "<<y<<" Cannibal";
                else if(x>0) cout<<"Carrying "<<x<<" Missionary";
                else if(y>0) cout<<"Carrying "<<y<<" Cannibal";
                cout<<endl;
            }

            cout<<"\tLeft Side (Missionary, Cannibal): ( "<<v[i].leftMissionary<<" , "<<v[i].leftCannibal<<" )"<<endl<<endl;
            cout<<"\tRight Side (Missionary, Cannibal): ( "<<v[i].rightMissionary<<" , "<<v[i].rightCannibal<<" ) "<<endl<<endl;
        }
        cout<<endl<<endl;
        return;
    }

    if(checkSituation(var)){
        return;
    }
    if(checkAgainstPrevious(var, boat%2)){
        return;
    }
    var.boat=boat%2;
    checkWithPrevious.push_back(var);

    if(boat%2==0){
            /// One and Two missionary
            var.rightMissionary+=1;
            var.leftMissionary-=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.rightMissionary+=1;
            var.leftMissionary-=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.rightMissionary-=2;
            var.leftMissionary+=2;

            /// One and Two Cannabil
            var.leftCannibal-=1;
            var.rightCannibal+=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.leftCannibal-=1;
            var.rightCannibal+=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.leftCannibal+=2;
            var.rightCannibal-=2;

            /// One cannabil and one missionary
            var.leftCannibal-=1;
            var.rightCannibal+=1;
            var.leftMissionary-=1;
            var.rightMissionary+=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
    }
    else{
            /// One and Two missionary
            var.rightMissionary-=1;
            var.leftMissionary+=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.rightMissionary-=1;
            var.leftMissionary+=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.rightMissionary+=2;
            var.leftMissionary-=2;

            /// One and Two Cannabil
            var.leftCannibal+=1;
            var.rightCannibal-=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.leftCannibal+=1;
            var.rightCannibal-=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
            var.leftCannibal-=2;
            var.rightCannibal+=2;

            /// One cannabil and one missionary
            var.leftCannibal+=1;
            var.rightCannibal-=1;
            var.leftMissionary+=1;
            var.rightMissionary-=1;
            v.push_back(var);
            DFS(var, boat+1, v);
            v.pop_back();
    }
}

int main()
{
    vector<game>v;
    game g;
    g.leftCannibal=3;
    g.leftMissionary=3;
    g.rightCannibal=0;
    g.rightMissionary=0;
    v.push_back(g);
    DFS(g, 0, v);
}
