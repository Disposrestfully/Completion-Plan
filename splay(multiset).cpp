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
int n;
namespace splay{
	#define ls ch[x][0]
	#define rs ch[x][1]
	#define getson(x) (x==ch[fa[x]][1])
	const int inf=1e9;
	int rt,val[N];
	int fa[N],ch[N][2],sz[N];
	stack<int>sta;
	inline void pushup(int x){
		if (!x) return;
		sz[x]=sz[ls]+sz[rs]+1;
	}	
	inline void rotate(int x){
		int y=fa[x],z=fa[y],k=getson(x);
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
			if (fa[y]!=goal)
				(getson(x)^getson(y))?rotate(x):rotate(y);
			rotate(x);
		}
		pushup(x);
		if (!goal) rt=x;
	}
	inline void insert(int x){
		int p=rt;
		while (ch[p][val[p]<=x])
			p=ch[p][val[p]<=x];
		ch[p][val[p]<=x]=sta.top();
		sta.pop();
		fa[ch[p][val[p]<=x]]=p;
		p=ch[p][val[p]<=x];
		val[p]=x,sz[p]=1;
		for (int i=p;i;i=fa[i]) pushup(i);
		splay(p,0);
	}
	inline int get_kth(int x,int k){
		while (x){
			if (sz[ls]+1==k) return x;
			if (sz[ls]+1<k) k-=sz[ls]+1,x=rs;
			else x=ls;
		}	
	}
	inline int get_rank(int x){
		int p=rt,rk=1;
		while (p){
			if (val[p]>=x) p=ch[p][0];
			else{
				rk+=sz[ch[p][0]]+1;
				p=ch[p][1];
			}
		}
		return rk;
	}	
	inline void Del(int x){
		if (!x) return;
		fa[x]=ls=rs=0;
		sz[x]=val[x]=0;
		sta.push(x);
	}
	inline void del(int x){
		int L=get_kth(rt,x-1),R=get_kth(rt,x+1);
		splay(L,0),splay(R,L);
		Del(ch[R][0]),ch[R][0]=0;
		pushup(R),pushup(L);
	}
	inline int find_pre(int x){
		int pre=0,p=rt;
		while (p){
			if (val[p]<x && val[p]>pre) pre=val[p];
			p=ch[p][val[p]<x];
		}
		return pre;
	}
	inline int find_nxt(int x){
		int nxt=inf,p=rt;
		while (p){
			if (val[p]>x && val[p]<nxt) nxt=val[p];
			p=ch[p][val[p]<=x];
		}
		return nxt;
	}
	inline void init(){
		for (int i=N-5;i;--i) sta.push(i);
		rt=0;
		insert(inf),insert(-inf);
	}
}
using namespace splay;
int main(){
	freopen("splay.in","r",stdin);
	freopen("splay.out","w",stdout);
	n=read();
	init();
	while (n--){
		int opt=read(),x=read();
		if (opt==1) insert(x);
		if (opt==2) del(get_rank(x));
		if (opt==3) Print(get_rank(x)-1);
		if (opt==4) Print(val[get_kth(rt,x+1)]);
		if (opt==5) Print(find_pre(x));
		if (opt==6) Print(find_nxt(x));
	}
	io::flush();
	return 0;
}
