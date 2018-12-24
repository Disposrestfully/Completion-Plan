#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=1e5+5;
namespace pb_ds{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
struct dinic{
	const int inf=2e9;
	struct edge{
		int next,to,w;
	}a[N<<1];
	int head[N],cnt;
	inline void add(int u,int v,int w){
		a[++cnt].to=v;
		a[cnt].next=head[u];
		head[u]=cnt;
		a[cnt].w=w;
	}
	int n,m,S,T,tim;
	int vis[N],l[N],cur[N];
	inline void input(){
		n=read(),m=read();
		S=read(),T=read();
		cnt=1,tim=0;
		for (int i=1;i<=m;++i){
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,0);
		}
	}
	queue<int>q;
	inline bool bfs(){
		q=queue<int>();
		++tim,q.push(S);
		l[S]=1,vis[S]=tim;
		while (!q.empty()){
			int x=q.front();
			if (x==T) return 1;
			q.pop();
			for (int i=head[x];i;i=a[i].next){
				int y=a[i].to;
				if (!a[i].w || vis[y]==tim) continue;
				l[y]=l[x]+1,vis[y]=tim;
				q.push(y);
			}
		}
		return (vis[T]==tim);
	}
	int dfs(int x,int flow){
		if (x==T || !flow) return flow;
		int res=0;
		for (int &i=cur[x];i;i=a[i].next){
			int y=a[i].to;
			if (!a[i].w || vis[y]!=tim || l[y]!=l[x]+1) continue;
			int f=dfs(y,min(flow,a[i].w));
			if (f){
				res+=f,flow-=f;
				a[i].w-=f,a[i^1].w+=f;
				if (!flow) return res;
			}else l[y]=-1;
		}
		return res;
	}
	inline void solve(){
		input();
		int ans=0;
		while (bfs()){
			for (int i=1;i<=n;++i) cur[i]=head[i];
			ans+=dfs(S,inf);
		}
		printf("%d\n",ans);
	}
}D;
int main(){
	return 0;
}
