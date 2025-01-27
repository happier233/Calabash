#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
namespace ZL
{
    const int N=605,M=100010,inf=1e9;
    struct edge
    {
        int u,v,w,use,id;
    }b[M],a[2000100];
    int n,m,ans,pre[N],id[N],vis[N],root,In[N],h[N],len,way[M];
    void init(int _n,int _root)
    {
        n=_n; m=0; b[0].w=inf; root=_root; ans=0;
    }
    void add(int u,int v,int w)
    {
        b[++m]=(edge){u,v,w,0,m};
        a[m]=b[m];
    }
    int work()
    {
        len=m;
        for(;;)
        {
            for(int i=1;i<=n;i++) {pre[i]=0; In[i]=inf; id[i]=0; vis[i]=0; h[i]=0;}
            for(int i=1;i<=m;i++)
                if(b[i].u!=b[i].v&&b[i].w<In[b[i].v])
                {
                    pre[b[i].v]=b[i].u; In[b[i].v]=b[i].w; h[b[i].v]=b[i].id;
                }
            for(int i=1;i<=n;i++) if(pre[i]==0&&i!=root) return 0;
            int cnt=0; In[root]=0;
            for(int i=1;i<=n;i++)
            {
                if(i!=root) a[h[i]].use++;
                int now=i; ans+=In[i];
                while(vis[now]==0&&now!=root)
                {
                    vis[now]=i; now=pre[now];
                }
                if(now!=root&&vis[now]==i)
                {
                    cnt++; int kk=now;
                    while(1)
                    {
                        id[now]=cnt; now=pre[now];
                        if(now==kk) break;
                    }
                }
            }
            if(cnt==0) return 1;
            for(int i=1;i<=n;i++) if(id[i]==0) id[i]=++cnt;
            for(int i=1;i<=m;i++)
            {
                int k1=In[b[i].v]; int k2=b[i].v;
                b[i].u=id[b[i].u]; b[i].v=id[b[i].v];
                if(b[i].u!=b[i].v)
                {
                    b[i].w-=k1; a[++len].u=b[i].id; a[len].v=h[k2];
                    b[i].id=len;
                }
            }
            n=cnt;
            root=id[root];
        }
        return 1;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    ZL::init(2*n+1,1);
    for(int i=0;i<m;i++)
    {
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        ZL::add(u+1,v+n+1,w);
    }
    for(int i=1;i<=n;i++) ZL::add(1,i+1,0);
    ZL::work();
    printf("%d\n",ZL::ans);
    return 0;
}

