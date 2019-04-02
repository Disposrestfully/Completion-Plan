#include<bits/stdc++.h>
inline int read(){
	int x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		ch=getchar();
		if (ch=='-') w=-1;	
	}
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*w;
}
using namespace std;
typedef long long ll;
const int N=1e6+5;
int n,m,rt,tot,ans;
int ch[N][26];
int cnt[N],fail[N];
queue<int>q;
char s[N];
inline void insert(){
	m=strlen(s+1);
	rt=1;
	for (int i=1;i<=m;++i){
		int x=s[i]-'a';
		if (!ch[rt][x]) ch[rt][x]=++tot;
		rt=ch[rt][x];
	}	
	++cnt[rt];
}
inline void build(){
	q.push(1);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int i=0;i<26;++i){
			if (!ch[x][i]) ch[x][i]=ch[fail[x]][i];
			else fail[ch[x][i]]=ch[fail[x]][i],q.push(ch[x][i]);
		}
	}
}
inline void solve(){
	m=strlen(s+1);
	rt=1;
	for (int i=1;i<=m;++i){
		int x=s[i]-'a',k=ch[rt][x];
		while (k>1 && ~cnt[k]) ans+=cnt[k],cnt[k]=-1,k=fail[k];
		rt=ch[rt][x];
	}
}
int main(){
	freopen("ac.in","r",stdin);
	freopen("ac.out","w",stdout);
	n=read(),tot=1;
	for (int i=0;i<26;++i)
		ch[0][i]=1;
	for (int i=1;i<=n;++i){
		scanf("%s",s+1);
		insert();
	}	
	build();
	scanf("%s",s+1);
	solve();
	printf("%d\n",ans);
	return 0;
}
