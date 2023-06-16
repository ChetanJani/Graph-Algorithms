#include <bits/stdc++.h>
using namespace std;

int dfs(int vertex,int parent,int timer,vector <int> &low,vector <int> &discovery,vector <int> &visit,vector <int> &ap,vector <vector <int>> &adj){
    visit[vertex]=1;
    timer++;
    low[vertex]=discovery[vertex]=timer;

    int children=0;
    for(auto &child : adj[vertex]){
        if(child==parent){
            continue;
        }
        else if(visit[child]==0){
            children++;
            dfs(child,vertex,timer,low,discovery,visit,ap,adj);
            if(discovery[vertex] <= low[child]){
                ap[vertex]=1;  //It is articulation point
            }
            low[vertex] = min(low[vertex],low[child]);
        }
        else{ //child is visited to it can be ancestor
            low[vertex] = min(low[vertex],discovery[child]);
        }   
    }
    return children;
}
 
int main()
{
    int nodes;
    cout<<"Enter total number of nodes : "<<endl;
    cin>>nodes;
    cout<<"Enter total number of edges : "<<endl;
    int edges;
    cin>>edges;

    vector <vector <int>> adj(nodes+1); // both 0-index and 1-index will work , but here i have take 1-base index
    
    cout<<"Enter edges pair : "<<endl;
    int u,v;

    //adj list 
    for(int i=0;i<edges;i++){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector <int> visit(nodes+1,0);
    vector <int> ap(nodes+1,0); // AP - Articulation Point
    vector <int> low(nodes+1);
    vector <int> discovery(nodes+1);

    int children,timer=0;
    bool done=false;
    for(int i=1;i<=nodes;i++){
        if(!visit[i]){
            children=dfs(i,-1,timer,low,discovery,visit,ap,adj); // i=vertex , -1 pass as a root node parent
            if(children>1){
                ap[i]=1;
            }
            if(i==1){
                // because root of tree can only be AP when there is more than 1 children and they are not connected to each other else ap[root]=0;
                if(children>1) ap[i]=1;
                else ap[i]=0;
            }
        }
    }
    cout<<"Articulation Points : ";
    for(int i=1;i<=nodes;i++){
        if(ap[i]){
            cout<<i<<" ";
        }
    }
    cout<<endl;
}
