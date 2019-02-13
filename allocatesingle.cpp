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
int r11,r21,r31,r41,r51;
cout<<"Enter radius of the  the sensors of second cluster"<<endl;
cin>>r11>>r21>>r31>>r41;
int s11,s21,s31,s41,s51;
cout<<"Enter information rate of the  the sensors"<<endl;
cin>>s11>>s21>>s31>>s41;

int b11,b21,b31,b41;
b11=r11*s11;
b21=r21*s21;
b31=r31*s31;
b41=r41*s41;



int netb1=( b11+b21+b31+b41)/4;

cout<<"average floating point constant first cluster"<<netb<<endl;
cout<<"average floating point constant second cluster"<<netb1<<endl;

cout<<"Time taken for collector1 to go to cluster1"<<endl;
int time1=5;
cout<<time1<<endl;
cout<<"Time taken for collector  to return from cluster2 "<<endl;
int time2=8;
cout<<time2<<endl;

int timetransit=6;
cout<<"Time taken for collector to transit from cluster 1 to cluster2"<<endl;
cout<<timetransit<<endl;

int graph[][V]={{ 0, 10, 15, 20 },
                       { 10, 0, 35, 25 },
                       { 15, 35, 0, 30 },
                       { 20, 25, 30, 0 }};



int graph1[][V]={{ 0, 20, 25, 40 },
                       { 20, 0, 35, 45 },
                       { 25, 35, 0, 30 },
                       { 40, 45, 30, 0 }};


int s=0;
int maxtspval2=maxtsp(graph1,s);
int tspval2=tsp(graph1,s);
cout<<maxtspval2<<" "<<tspval2<<endl;
 s=0;
int maxtspval= maxtsp(graph,s);
int tspval= tsp(graph,s);
cout<<maxtspval<<" "<<tspval<<endl;

int i=0;



int j,l;
 int g[V][V];
 for(i=0;i<V;i++)
 {

     for(j=0;j<V;j++)
     {


             g[i][j]= graph[i][j];


     }
 }


int g1[V][V];
 for(i=0;i<V;i++)
 {

     for(j=0;j<V;j++)
     {


             g1[i][j]= graph1[i][j];


     }
 }









while(tspval < maxtspval   ||  maxtspval2>tspval2)
{       cout<<i<<"iteration"<<endl;
    i++;
 int m= tspval;
netb+=4;
r1=netb/s1;
r2=netb/s2;
r3=netb/s3;
r4=netb/s4;
//r5=netb/s5;
netb1+=8/8;
r11=netb/s11;
r21=netb/s21;
r31=netb/s31;
r41=netb/s41;

cout<<"Radius change first cluter"<<endl;
cout<<r1<<" "<<r2<<" "<<r3<<" "<<r4<<endl;
cout<<"Information source change first cluster"<<endl;

cout<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;

cout<<"Radius change second cluster"<<endl;
cout<<r11<<" "<<r21<<" "<<r31<<" "<<r41<<endl;
cout<<"Information source change second cluster"<<endl;

cout<<s11<<" "<<s21<<" "<<s31<<" "<<s41<<endl;
g1[0][1]+=(int)(4/s1 + 4/s2);
g1[0][2]+=(int)(4/s1 + 4/s3);
g1[0][3]+=(int)(4/s1 + 4/s4);
g1[1][0]+=(int)(4/s1 + 4/s2);
g1[1][2]+=(int)(4/s2 + 4/s3);
g1[1][3]+=(int)(4/s2 + 4/s4);
g1[2][0]+=(int)(4/s3 + 4/s1);
g1[2][1]+=(int)(4/s3 + 4/s2);
g1[2][3]+=(int)(4/s3 + 4/s4);
g1[3][0]+=(int)(4/s4 + 4/s1);
g1[3][1]+=(int)(4/s4 + 4/s2);
g1[3][2]+=(int)(4/s4 + 4/s3);

g[0][1]+=(int)(1/s1 + 1/s2);
g[0][2]+=(int)(1/s1 + 1/s3);
g[0][3]+=(int)(1/s1 + 1/s4);
g[1][0]+=(int)(1/s1 + 1/s2);
g[1][2]+=(int)(1/s2 + 1/s3);
g[1][3]+=(int)(1/s2 + 1/s4);
g[2][0]+=(int)(1/s3 + 1/s1);
g[2][1]+=(int)(1/s3 + 1/s2);
g[2][3]+=(int)(1/s3 + 1/s4);
g[3][0]+=(int)(1/s4 + 1/s1);
g[3][1]+=(int)(1/s4 + 1/s2);
g[3][2]+=(int)(1/s4 + 1/s3);



int s=0;

cout<<"tsp in ith iteration "<<tsp(g,0)<<endl;

tspval=tsp(g,0);
tspval2=tsp(g1,0);
cout<<"tsp first cluster"<<endl;
cout<<"tsp second cluster"<<endl;
cout<<tspval<<" "<<maxtspval<<endl;
cout<<tspval2<<" "<<maxtspval2<<endl;
tspval=time1+time2+timetransit + tspval2 ;
cout<<"Time for data collection while collector is collecting from cluster 2"<<endl;
cout<<tspval<<endl;
tspval2=time1+time2+timetransit+tspval;
cout<<"Time for data collection while collector is collecting from cluster 2"<<endl;
cout<<tspval<<endl;

int total_time=tspval+tspval2;
cout<<"Time for1 complete iteration from source to cluster 1 via cluster2 back to sink"<<endl;
cout<<total_time<<endl;
   if(maxtspval<=tspval || maxtspval2<=tspval2)
  {

      break;
  }








}





return 0;}

