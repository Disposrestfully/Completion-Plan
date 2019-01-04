#include<bits/stdc++.h>
#define read() Read<int>()
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
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,m,a[N];
namespace splay{
	#define ls ch[x][0]
	#define rs ch[x][1]
	#define mid (l+r>>1)
	#define getson(x) (x==ch[fa[x]][1])
	const int inf=1e9;
	int rt,tot,val[N],rev[N];
	int fa[N],ch[N][2],sz[N];
	inline void Rev(int x){
		if (!x) return;
		rev[x]^=1,swap(ls,rs);
	}
	inline void pushdown(int x){
		if (!x) return;
		if (!rev[x]) return;
		if (ls) Rev(ls);
		if (rs) Rev(rs);
		rev[x]=0;
	}	
	inline void pushup(int x){
		if (!x) return;
		sz[x]=sz[ls]+sz[rs]+1;
	}	
	inline void rotate(int x){
		int y=fa[x],z=fa[y],k=getson(x);
		pushdown(y),pushdown(x);
		ch[y][k]=ch[x][!k];
		if (ch[x][!k]) fa[ch[x][!k]]=y;
		ch[x][!k]=y;
		if (z) ch[z][getson(y)]=x;
		fa[y]=x,fa[x]=z;	
		pushup(y),pushup(x);
	}
	inline void splay(int x,int goal){
		while (fa[x]!=goal){
			int y=fa[x];
			pushdown(fa[y]),pushdown(y),pushdown(x);
			if (fa[y]!=goal)
				(getson(x)^getson(y))?rotate(x):rotate(y);
			rotate(x);
		}
		pushup(x);
		if (!goal) rt=x;
	}
	inline void build(int x,int l,int r,int las,int s){
		if (l>r){
			--tot;
			return;
		}
		val[x]=a[mid],sz[x]=r-l+1;
		if (las) fa[x]=las,ch[las][s]=x;
		++tot,build(tot,l,mid-1,x,0);
		++tot,build(tot,mid+1,r,x,1);
	}
	inline int get_kth(int x,int k){
		while (x){
			pushdown(x);
			if (sz[ls]+1==k) return x;
			if (sz[ls]+1<k) k-=sz[ls]+1,x=rs;
			else x=ls;
		}	
	}
	inline void update(int l,int r){
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0),splay(R,L);
		Rev(ch[ch[rt][1]][0]);
	}
	void dfs(int x){
		pushdown(x);
		if (ls) dfs(ls);
		if (val[x]) Print(val[x],' ');
		if (rs) dfs(rs);	
	}
}
using namespace splay;
int main(){
	freopen("splay.in","r",stdin);
	freopen("splay.out","w",stdout);
	n=read()+2;m=read();
	for (int i=2;i<=n-1;++i)
		a[i]=i-1;
	rt=++tot;
	build(rt,1,n,0,0);
	while (m--){
		int l=read()+1,r=read()+1;
		update(l,r);
	}
	dfs(rt);
	io::flush();
	puts("");
	return 0;
}
