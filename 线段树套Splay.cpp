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
using namespace io;
using namespace std;
typedef long long ll;
const int N=5e4+5;
const int M=2e6+5;
const int inf=1e9;
int n,m,a[N];
namespace splay{
	#define ls ch[x][0]
	#define rs ch[x][1]
	#define getson(x) (x==ch[fa[x]][1])
	stack<int>sta;
	int rt[M],val[M],fa[M];
	int sz[M],ch[M][2];
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
		fa[x]=z,fa[y]=x;
		pushup(y),pushup(x);
	}
	inline void splay(int o,int x,int goal){
		while (fa[x]!=goal){
			int y=fa[x],z=fa[y];
			if (z!=goal) 
				(getson(x)^getson(y))?rotate(x):rotate(y);
			rotate(x);
		}
		pushup(x);
		if (!goal) rt[o]=x;	
	}
	inline void insert(int x,int k){
		int p=rt[x],v=sta.top();
		while (ch[p][val[p]<=k])
			p=ch[p][val[p]<=k];
		sz[v]=1,val[v]=k;
		if (p) ch[p][val[p]<=k]=v;
		fa[v]=p,sta.pop();
		ch[v][0]=ch[v][1]=0;
		for (int i=p;i;i=fa[i])
			pushup(i);
		splay(x,v,0);
	}
	inline int get_rank(int x,int k){
		int rk=1,l=x;
		x=rt[x];
		while (x){
			if (val[x]>=k) x=ls;
			else rk+=sz[ls]+1,x=rs;
		}
		return rk;
	}
	inline int get_pre(int x,int k){
		int pre=-inf;
		x=rt[x];
		while (x){
			if (val[x]<k && val[x]>pre) pre=val[x];
			if (val[x]<k) x=rs;
			else x=ls;
		}
		return pre;
	}
	inline int get_nxt(int x,int k){
		int nxt=inf;
		x=rt[x];
		while (x){
			if (val[x]>k && val[x]<nxt) nxt=val[x];
			if (val[x]<=k) x=rs;
			else x=ls;
		}
		return nxt;
	}
	inline int get_kth(int x,int k){
		while (x){
			if (sz[ls]+1==k) return x;
			if (sz[ls]>=k) x=ls;
			if (sz[ls]+1<k) k-=sz[ls]+1,x=rs;
		}
	}
	inline void Del(int x){
		if (!x) return;
		fa[x]=ls=rs=0;
		val[x]=sz[x]=0;
		sta.push(x);
	}
	inline void del(int x,int k){
		int p=get_rank(x,k);
		int l=get_kth(rt[x],p-1),r=get_kth(rt[x],p+1);
		splay(x,l,0),splay(x,r,l);
		Del(ch[r][0]),ch[r][0]=0;
		pushup(r),pushup(l);
	}
	inline void init(){
		memset(rt,0,sizeof(rt));
		for (int i=M-5;i;--i) sta.push(i);	
	}
}
using namespace splay;
namespace seg{
	#define lc (x<<1)
	#define rc (lc|1)
	#define mid (l+r>>1)
	void build(int x,int l,int r){
		insert(x,inf),insert(x,-inf);
		if (l==r) return;
		build(lc,l,mid),build(rc,mid+1,r);
	}
	void ins(int x,int l,int r,int pos,int k){
		insert(x,k);
		if (l==r) return;
		if (pos<=mid) ins(lc,l,mid,pos,k);
		else ins(rc,mid+1,r,pos,k);
	}
	void erase(int x,int l,int r,int pos,int k){
		del(x,k);
		if (l==r) return;
		if (pos<=mid) erase(lc,l,mid,pos,k);
		else erase(rc,mid+1,r,pos,k);
	}
	int find_pre(int x,int l,int r,int L,int R,int k){
		if (L<=l && r<=R) return get_pre(x,k);
		int res=-inf;
		if (L<=mid) res=max(res,find_pre(lc,l,mid,L,R,k));
		if (R>mid) res=max(res,find_pre(rc,mid+1,r,L,R,k));
		return res;
	}
	int find_nxt(int x,int l,int r,int L,int R,int k){
		if (L<=l && r<=R) return get_nxt(x,k);
		int res=inf;
		if (L<=mid) res=min(res,find_nxt(lc,l,mid,L,R,k));
		if (R>mid) res=min(res,find_nxt(rc,mid+1,r,L,R,k));
		return res;
	}
	int find_rank(int x,int l,int r,int L,int R,int k){
		if (L<=l && r<=R) return get_rank(x,k)-2;
		int res=0;
		if (L<=mid) res+=find_rank(lc,l,mid,L,R,k);
		if (R>mid) res+=find_rank(rc,mid+1,r,L,R,k);
		return res;
	}
}
using namespace seg;
int main(){
	n=read(),m=read();
	init(),build(1,1,n);
	for (int i=1;i<=n;++i){
		a[i]=read();
		ins(1,1,n,i,a[i]);
	}
	while (m--){
		int opt=read();
		if (opt==1){
			int l=read(),r=read(),x=read();
			Print(find_rank(1,1,n,l,r,x)+1);
		}else if (opt==2){
			int l=read(),r=read(),k=read();
			int L=-1e8,R=1e8,ans=-1;
			while (L<=R){
				int Mid=(L+R)>>1;
				if (find_rank(1,1,n,l,r,Mid)+1<=k) ans=Mid,L=Mid+1;
				else R=Mid-1;
			}
			Print(ans);
		}else if (opt==3){
			int pos=read(),x=read();
			erase(1,1,n,pos,a[pos]);
			a[pos]=x;
			ins(1,1,n,pos,a[pos]);
		}else if (opt==4){
			int l=read(),r=read(),x=read();
			Print(find_pre(1,1,n,l,r,x));
		}else{
			int l=read(),r=read(),x=read();
			Print(find_nxt(1,1,n,l,r,x));
		}
	}
	flush();
	return 0;
}
