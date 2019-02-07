#include<bits/stdc++.h>
#define V 4

using namespace std;

int maxtsp(int graph[][V],int s)
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

   int maxpath=INT_MIN;
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
   maxpath=max(maxpath,cpath);



   }
while(next_permutation(vertex.begin(),vertex.end()));


return maxpath;


}




int tsp(int graph[][V],int s)
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
        minpath=min(cpath,minpath);








    }
    while(next_permutation(vertex.begin(),vertex.end()));



    return minpath;





}











int main(){


int r1,r2,r3,r4,r5;
cout<<"Enter radius of the  the sensors"<<endl;
cin>>r1>>r2>>r3>>r4;
int s1,s2,s3,s4,s5;
cout<<"Enter information rate of the  the sensors"<<endl;
cin>>s1>>s2>>s3>>s4;

int b1,b2,b3,b4;
b1=r1*s1;
b2=r2*s2;
b3=r3*s3;
b4=r4*s4;



int netb=( b1+b2+b3+b4)/4;
cout<<"average floating point constant"<<netb<<endl;

int graph[][V]={{ 0, 10, 15, 20 },
                       { 10, 0, 35, 25 },
                       { 15, 35, 0, 30 },
                       { 20, 25, 30, 0 }};


int s=0;

int maxtspval= maxtsp(graph,s);
int tspval= tsp(graph,s);
int i=0;
while(tspval < maxtspval)
{       cout<<i<<"iteration"<<endl;
    i++;
 int m= tspval;
netb+=8/8;
r1=netb/s1;
r2=netb/s2;
r3=netb/s3;
r4=netb/s4;
//r5=netb/s5;

cout<<"Radius change"<<endl;
cout<<r1<<" "<<r2<<" "<<r3<<" "<<r4<<endl;
cout<<"Information source change"<<endl;

cout<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;


 int j,l;
 int g[V][V];
 for(i=0;i<V;i++)
 {

     for(j=0;j<V;j++)
     {


             g[i][j]= graph[i][j];


     }
 }

g[0][1]+=(int)(4/s1 + 4/s2);
g[0][2]+=(int)(4/s1 + 4/s3);
g[0][3]+=(int)(4/s1 + 4/s4);
g[1][0]+=(int)(4/s1 + 4/s2);
g[1][2]+=(int)(4/s2 + 4/s3);
g[1][3]+=(int)(4/s2 + 4/s4);
g[2][0]+=(int)(4/s3 + 4/s1);
g[2][1]+=(int)(4/s3 + 4/s2);
g[2][3]+=(int)(4/s3 + 4/s4);
g[3][0]+=(int)(4/s4 + 4/s1);
g[3][1]+=(int)(4/s4 + 4/s2);
g[3][2]+=(int)(4/s4 + 4/s3);

int s=0;

cout<<"tsp in ith iteration"<<tsp(g,0)<<endl;

tspval=tsp(g,0);
cout<<tspval<<" "<<maxtspval<<endl;

   if(maxtspval==tspval)
  {

      break;
  }








}





return 0;}
