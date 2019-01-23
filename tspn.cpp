#include<bits/stdc++.h>
#define V 4
using namespace std;



int maxtsp(int graph[][V],int s)
{
int i,k;
vector<int> vertex;
for(i=0;i<V;i++)
{
    if(i!=s)
    {
        vertex.push_back(i);
    }
}



int maxpath=INT_MIN;
do{


    int cpath=0;
    k=s;
    for(i=0;i<vertex.size();i++)
    {

        cpath+=graph[k][vertex[i]];
        k=vertex[i];

    }


cpath+=graph[k][s];
maxpath=max(maxpath,cpath);

}
while(next_permutation(vertex.begin(),vertex.end()));



return maxpath;

}

int tsp( int graph[][V],int s)
{

  int i;
  int k;
  vector<int> vertex;
  for(i=0;i<V;i++)
  {
      if(i!=s)
      {
      vertex.push_back(i);
      }
  }


  int minpath=INT_MAX;
  k=s;
  do{
    int cpath=0;
    k=s;
    for(i=0;i<vertex.size();i++)
    {
    cpath+=graph[k][vertex[i]];
    k=vertex[i];
    }

    cpath+=graph[k][s];
    minpath=min(minpath,cpath);


  }
while(next_permutation(vertex.begin(),vertex.end()));


return minpath;


}



int main(){

  int graph[][V]={{ 0, 10, 15, 20 },
                       { 10, 0, 35, 25 },
                       { 15, 35, 0, 30 },
                       { 20, 25, 30, 0 }};


                   int s=0;
                   cout<<tsp(graph,s)<<endl;
                     cout<<maxtsp(graph,s)<<endl;
//for 2 sensor based network,optimal TSPN and energy loss modification.
//Amount of data at a sensor node is inversely proportional to the radius of communication of the sensor in the network.
//Algorithm for TSPN based sensor network

/*

for 2 sensor system:

    Step1:  Energy loss of a sensor /collector = K r^(alpha);
    where K = proportionality constant
    r= estimated radius before improvement;
    alpha= constant;
    For Si bit information sensor the Energy loss= K*Si*r^(alpha);

problem becomes minimisation problem:
minimise Energy net=(k*si*r^(alpha));
subject to :
(2(d-r1)+2(d-r2)/velocity of collector)= Dmax;

r2=r1(S1/S2)^(1/alpha-1);

Function becomes= K1(C/s^(1/alpha-1))=f;

Step 2:Calculate TSPN=Dmax; by Elbissioni algorithm over Euclid graph;
Step3: if(d<Dmax)
        do: K1=K1-delta;
            f=K1(C/s^(1/alpha-1));
        else if(d>Dmax)
        do: K1=K1+delta;
            f=K1(C/s^(1/alpha-1));
        else if(d==Dmax)
            return f,and optimal radius r;
            terminate



  */

  cout<<"enter radius of 2 circles"<<endl;
  float r1,r2;
  cin>>r1>>r2;
  cout<<"enter distance between them"<<endl;
  float d;
  cin>>d;
  cout<<"enter packet information rate of S1 and S2"<<endl;
  float pk1,pk2;
  cin>>pk1>>pk2;


  float K= 10^(-5);
  float alpha= 3;


  cout<<"Energy loss in case of two sensor system"<<endl;
  float energy= K*(pk1)*pow(r1,alpha) + K*(pk2)*(pow(r2,alpha));
  cout<<energy<<endl;




   //oprimtality()


return 0;}
