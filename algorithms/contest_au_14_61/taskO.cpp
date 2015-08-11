
#include <cstdio>
#include <cstring>

int px[]={1,-1,0,0};
int py[]={0,0,1,-1};

const int MAXN=51*51+100;
class Edge{
public:
    int f,c,v;
    Edge(){}
};

class Node{
public:
    Node* next;
    Edge val;
    Node(){next=0;}
};
class List{
public:
    Node* head;
    List(){head=0;}
    Node* add(Edge val){
        Node* e=new Node;
        e->next=head;
        e->val=val;
        head=e;
        return e;
    }
    Node* start(void){
        return head;
    }
};


List g[MAXN];
Node* where[MAXN][MAXN];

int n,m;
char board[51][51];
bool ok(int x,int y){
    return x>=0&&x<n&&y>=0&&y<m;
}
void addEdge(int u,int v,int c){
    Edge e;
    e.v=v;
    e.c=c;
    e.f=0;
    where[u][v]=g[u].add(e);
}

bool been[MAXN];
int eW;
bool find(int u){
    if(been[u]) return false;
    been[u]=true;
    if(u==n*m+1) return true;
    Node* e;
    for(e=g[u].start();e;e=e->next){
        if(e->val.c - e->val.f>=eW){
            if(find(e->val.v)){
                e->val.f+=eW;
                where[e->val.v][u]->val.f-=eW;
                return true;
            }
        }
    }
    return false;
}
int main(){
    freopen("molecule.in","r",stdin);
    freopen("molecule.out","w",stdout);
    scanf("%d%d",&n,&m);
    int i,j;
    for(i=0;i<n;i++){
        scanf("%s",board[i]);
    }

    int x,y,k,w,u,v;
    bool exElem=false;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++){
            if(board[i][j]=='.') continue;
            exElem=true;
            if(board[i][j]=='H') w=1;
            if(board[i][j]=='O') w=2;
            if(board[i][j]=='N') w=3;
            if(board[i][j]=='C') w=4;
            u=i*m+j+1;
            if((i+j)&1){
                addEdge(u,n*m+1,w);
                addEdge(n*m+1,u,0);
                continue;
            }
            addEdge(u,0,0);
            addEdge(0,u,w);
            for(k=0;k<4;k++){
                x=i+px[k];y=j+py[k];
                if(!ok(x,y)) continue;
                if(board[x][y]=='.') continue;
                v=x*m+y+1;
                addEdge(u,v,1);
                addEdge(v,u,0);
            }
        }
    if(!exElem) {printf("Invalid");return 0;}


    int f=0;
    for(eW=(1<<3);eW;(eW>>=1)){
        memset(been,0,sizeof(been));
        while(find(0)){
            f+=eW;
            memset(been,0,sizeof(been));
        }
    }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++){
            if(board[i][j]=='.') continue;
            if(board[i][j]=='H') w=1;
            if(board[i][j]=='O') w=2;
            if(board[i][j]=='N') w=3;
            if(board[i][j]=='C') w=4;
            u=i*m+j+1;
            if((i+j)&1){
                if(where[u][n*m+1]->val.f!=w){printf("Invalid");return 0;}
                continue;
            }
            if(where[0][u]->val.f!=w){printf("Invalid");return 0;}
        }

    printf("Valid");
    return 0;
}