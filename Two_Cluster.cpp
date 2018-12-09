#include<bits/stdc++.h>
using namespace std;
float energyamplitude=70;
//"energy amplitude=70PJ/bit/m2"
float energyel=50;

float channelcapacity=34;
//cout<<"Channel capacity=34"<<endl;
float packetinforate;
float lengthofchannel=10;
//cout<<"length of channel =10"<<endl;

vector<pair<int,int> > veuler;
class Graph
{
  int V;
  list<int> *adj;
public:
     Graph(int V)  {
          this->V = V;
        adj = new list<int>[V];
         }

  ~Graph()
  { delete [] adj;
  }

  void addEdge(int u, int v) {
       adj[u].push_back(v);
        adj[v].push_back(u); }
  void rmvEdge(int u, int v);
  void printEulerTour();
  void printEulerUtil(int s);

  int DFSCount(int v, bool visited[]);

  bool isValidNextEdge(int u, int v);
};
void Graph::printEulerTour()
{
  int u = 0;
  for (int i = 0; i < V; i++)
      if (adj[i].size() & 1)
        {   u = i; break;  }

  printEulerUtil(u);
  cout << endl;
}

void Graph::printEulerUtil(int u)
{
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
  {
      int v = *i;

      if (v != -1 && isValidNextEdge(u, v))
      {
          cout << u << "-" << v << "  ";
          veuler.push_back(make_pair(u,v));
          rmvEdge(u, v);
          printEulerUtil(v);
      }
  }
}

bool Graph::isValidNextEdge(int u, int v)
{
   int count = 0;
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
     if (*i != -1)
        count++;
  if (count == 1)
    return true;


  bool visited[V];
  memset(visited, false, V);
  int count1 = DFSCount(u, visited);

  rmvEdge(u, v);
  memset(visited, false, V);
  int count2 = DFSCount(u, visited);

  addEdge(u, v);

  return (count1 > count2)? false: true;
}

void Graph::rmvEdge(int u, int v)
{
  list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
  *iv = -1;

  list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
  *iu = -1;
}

int Graph::DFSCount(int v, bool visited[])
{
  visited[v] = true;
  int count = 1;

  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
      if (*i != -1 && !visited[*i])
          count += DFSCount(*i, visited);

  return count;
}

int main()
{
cout<<"Euler path"<<endl;
  Graph g3(5);
  g3.addEdge(1, 0);
  g3.addEdge(0, 2);
  g3.addEdge(2, 1);
  g3.addEdge(0, 3);
  g3.addEdge(3, 4);
  g3.addEdge(3, 2);
  g3.addEdge(3, 1);
  g3.addEdge(2, 4);
  g3.printEulerTour();


 /* cout<<"vector of paths"<<endl;
int i;
for(i=0;i<veuler.size();i++)
{

    cout<<veuler[i].first<<""<<veuler[i].second<<endl;
}
*/int i;
vector<pair<int,int> > ve;
for(i=0;i<veuler.size();i++)
{

    ve.push_back(make_pair(veuler[i].first,veuler[i].second));
}



for(i=0;i<ve.size();i++)
{

    cout<<ve[i].first<<""<<ve[i].second<<endl;
}

veuler.clear();
Graph g1(4);
  g1.addEdge(0, 1);
  g1.addEdge(0, 2);
  g1.addEdge(1, 2);
  g1.addEdge(2, 3);
  g1.printEulerTour();


for(i=0;i<veuler.size();i++)
{

    cout<<veuler[i].first<<""<<veuler[i].second<<endl;
}

int n=veuler.size();

cout<<"ANALYSIS OF ENERGY,RESIDUAL ENERGY,LIFETIME FOR DYNAMIC PACKET RATE IN TWIN CLUSTER"<<endl;
cout<<"TWO/MULTIPLE CLUSTER ANALYSIS"<<endl;
cout<<"enter packet information rate"<<endl;
cin>>packetinforate;
cout<<"transmission time for x packets"<<endl;

float time=packetinforate*(lengthofchannel/channelcapacity);
cout<<time<<endl;
cout<<"For a sensor in amout of energy consumed =(Eamp^2 + Eele)*(x*(l/r))"<<endl;


float eachsensor=time*(energyamplitude+energyel);

cout<<eachsensor<<endl;



vector<float> a;
vector<float> b;
 n=ve.size();
vector<float> f;
vector<float> g;
int m=veuler.size();
float energy;
cout<<"assign energy to each packet of first cluster"<<endl;
for(i=0;i<n;i++)
{

    cin>>energy;
    a.push_back(energy);
    b.push_back(energy);
}
cout<<"assign energy to each packet of second cluster"<<endl;

for(i=0;i<m;i++)
{

    cin>>energy;

    f.push_back(energy);
    g.push_back(energy);
}

cout<<"Average time for inter cluster transmission"<<endl;
float intercluster;
cin>>intercluster;


cout<<"Average packet data of first cluster collection time"<<endl;

float averagetime=time*n;

cout<<averagetime<<endl;
cout<<"Average packet data of second cluster collection time"<<endl;

float averagetime2=time*m;

cout<<averagetime2<<endl;



cout<<"ANALYSIS OF DYNAMIC INFORMATION PACKET RATE FOR ONE CYCLE"<<endl;
cout<<"Collected information by other sensors in the average time span"<<endl;


cout<<"1ST CLUSTER"<<endl;
int avrtime=(int)averagetime;
float rate=0.25;
int j;
for(j=0;j<avrtime;j++)

{cout<<"Amount of Data Generation Rate"<<endl;
    float datagenerate=time *(packetinforate)*n;
    cout<<datagenerate<<endl;
    int ct=0;


    for(i=0;i<n;i++)
    {

        if(a[i]>0)
        {
            ct++;
        }
    }




    if(ct>=1)

{time+= rate*j;
  cout<<"energy consumed in "<<j<<"round"<<endl;
  eachsensor=time*(energyamplitude+energyel);

cout<<eachsensor<<endl;
cout<<endl;

    for(i=0;i<n;i++)
    {
      a[i]-=eachsensor;

    }

  cout<<" residual energy left in "<<j<<"round"<<endl;
cout<<endl;
   for(i=0;i<n;i++)
   {

       cout<<a[i]<<" ";
   }
   cout<<endl;
   cout<<endl;

   cout<<"Lifetime of packets"<<endl;

    for(i=0;i<n;i++)
    {
        if(a[i]>0)
    {float xc=a[i];
    float xy=b[i];
    xc=xc/xy;
    cout<<xc<<" ";

    }
    cout<<endl;
    }


    cout<<endl;
}




else if(ct<0)
{

    break;
}



}

cout<<"GOING FROM 1 TO 2 CLUSTER"<<endl;
float timespan=intercluster+averagetime;
int times=(int)timespan;

 cout<<"2ND CLUSTER"<<endl;

for(j=0;j<times;j++)

{cout<<"Amount of Data Generation Rate"<<endl;
   float datagenerate=time *(packetinforate)*m;
    cout<<datagenerate<<endl;
    int ct=0;


    for(i=0;i<m;i++)
    {

        if(f[i]>0)
        {
            ct++;
        }
    }




    if(ct>=1)

{time+= rate*j;
  cout<<"energy consumed in "<<j<<"round"<<endl;
  eachsensor=time*(energyamplitude+energyel);

cout<<eachsensor<<endl;
cout<<endl;

    for(i=0;i<m;i++)
    {
      f[i]-=eachsensor;

    }

  cout<<" residual energy left in "<<j<<"round"<<endl;
cout<<endl;
   for(i=0;i<m;i++)
   {

       cout<<f[i]<<" ";
   }
   cout<<endl;
   cout<<endl;

   cout<<"Lifetime of packets"<<endl;

    for(i=0;i<m;i++)
    {
        if(f[i]>0)
    {float xc=f[i];
    float xy=g[i];
    xc=xc/xy;
    cout<<xc<<" ";

    }
    cout<<endl;
    }


    cout<<endl;
}




else if(ct<0)
{

    break;
}



}











  return 0;
}


