#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+5;
namespace sam{
	int rt,tot,las;
	int ch[N][26],sz[N];
	int fa[N],len[N];
	inline void init(){
		las=rt=tot=1;
	}
	inline int newnode(int x){
		len[++tot]=len[x]+1;
		return tot;
	}
	inline void extend(int x){
		int p=las,np=newnode(p);
		las=np,sz[np]=1;
		while (p && !ch[p][x]) ch[p][x]=np,p=fa[p];
		if (!p) fa[np]=rt;
		else{
			int q=ch[p][x];
			if (len[q]==len[p]+1) fa[np]=q;
			else{
				int nq=newnode(p);
				while (p && ch[p][x]==q) ch[p][x]=nq,p=fa[p];
				fa[nq]=fa[q],fa[np]=fa[q]=nq;
				for (int i=0;i<26;++i) ch[nq][i]=ch[q][i];
			} 			
		}
	}
}
using namespace sam;
ll ans=0;
char s[N];
struct edge{
	int next,to;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int x){
	for (int i=head[x];i;i=a[i].next)
		dfs(a[i].to),sz[x]+=sz[a[i].to];
}
int main(){
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
	scanf("%s",s+1),init();
	for (int i=1,n=strlen(s+1);i<=n;++i)
		extend(s[i]-'a');
	for (int i=2;i<=tot;++i)
		add(fa[i],i);
	dfs(1);
	for (int i=1;i<=tot;++i)
		if (sz[i]!=1) ans=max(ans,1ll*sz[i]*len[i]);
	printf("%lld\n",ans);
	return 0;
}
