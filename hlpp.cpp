#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const ll N=1e5+5;
namespace pb_ds{   
    namespace io{
        const ll MaxBuff=1<<15;
        const ll Output=1<<23;
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
            static ll s[100]; 
            register ll t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
struct hlpp{
	const ll inf=1e18;
	struct edge{
		ll next,to,w;
	}a[N<<1];
	ll head[N],cnt;
	inline void add(ll u,ll v,ll w){
		a[++cnt].to=v;
		a[cnt].next=head[u];
		head[u]=cnt;
		a[cnt].w=w;
	}
	struct fnode{
		ll x,h;
		inline bool operator < (const fnode &u)const{
			return h<u.h;
		}
	};
	ll n,m,S,T;
	priority_queue<fnode>q;
	ll gap[N],h[N],f[N];
	inline void input(){
		n=read(),m=read();
		S=read(),T=read();
		cnt=1;
		memset(head,0,sizeof(head));
		for (ll i=1;i<=m;++i){
			ll u=read(),v=read(),w=read();
			if (w) add(u,v,w),add(v,u,0);
		}
	}
	inline bool push(ll x,ll e){
		ll w=min(a[e].w,f[x]);
		a[e].w-=w,a[e^1].w+=w;
		f[x]-=w,f[a[e].to]+=w;
		return w;
	}
	inline void Gap(ll x){
		for (ll i=1;i<=n;++i)
			if (i!=S && i!=T && h[i]>x && h[i]<=n) h[i]=n+1;
	}
	inline ll maxflow(){
		memset(h,0,sizeof(h));
		memset(f,0,sizeof(f));
		memset(gap,0,sizeof(gap));
		h[S]=n,f[S]=inf;
		q=priority_queue<fnode>();
		q.push((fnode){S,n});
		while (!q.empty()){
			ll x=q.top().x;
			q.pop();
			if (!f[x]) continue;
			for (ll i=head[x];i;i=a[i].next){
				ll y=a[i].to;
				if ((x==S || h[x]==h[y]+1) && push(x,i) && y!=S && y!=T)
					q.push((fnode){y,h[y]});
			}
			if (f[x] && x!=S && x!=T){
				if (!(--gap[h[x]])) Gap(h[x]);
				++gap[++h[x]];
				q.push((fnode){x,h[x]});
			}
		}
		return f[T];
	}
	inline void solve(){
		input();
		printf("%lld\n",maxflow());
	}
}H;
int main(){
	return 0;
}
