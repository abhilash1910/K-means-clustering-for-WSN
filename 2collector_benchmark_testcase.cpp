#include<bits/stdc++.h>
#define V 4

using namespace std;



float energyamplitude=70;



float Eelec=50;
float totalenergy=2000000000;



float packetsize =1500;

float channelcapacity=34;

float lengthofchannel=10;
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
cout<<"Sample details and inputs for benchmark restults"<<endl;
cout<<"Eelec =50nJ/bit"<<endl;
cout<<"Eamp=10-100PJ/bit/m^2"<<endl;
cout<<"packet length/message length=1500bytes"<<endl;
cout<<"channel capacity =10bits/s"<<endl;
cout<<"Time taken to send a packet=l/R"<<endl;
cout<<(float)(packetsize/lengthofchannel)<<endl;
 cout<<"Time taken to send  1-50 messages"<<endl;
int factor=(int)packetsize/(int)lengthofchannel;


int r1,r2,r3,r4,r5;
cout<<"Enter radius of the  the sensors in cm(int)"<<endl;
cin>>r1>>r2>>r3>>r4;

int s1,s2,s3,s4,s5;
cout<<"Enter no of messages of the  the sensors"<<endl;
cin>>s1>>s2>>s3>>s4;
cout<<"packet information rate"<<endl;
s1=(int)(s1*factor);
s2=(int)(s2*factor);
s3=(int)(s3*factor);
s4=(int)(s4*factor);
cout<<s1<<"bits/s"<<" "<<s2<<"bits/s"<<" "<<s3<<"bits/s"<<" "<<s4<<"bits/s"<<endl;


float e1,e2,e3,e4;
float ej1,ej2,ej3,ej4;
cout<<"Energy information sample range"<<endl;
ej1=(float)(energyamplitude*r1*r1 + Eelec)*s1;
ej2=(float)(energyamplitude*r2*r2 + Eelec)*s2;
ej3=(float)(energyamplitude*r3*r3 + Eelec)*s3;
ej4=(float)(energyamplitude*r4*r4 + Eelec)*s4;
ej1/=1000;
ej2/=1000;
ej3/=1000;
ej4/=1000;
cout<<ej1<<" "<<ej2<<" "<<ej3<<" "<<ej4<<"J"<<endl;

cout<<"Energy information for 1st cluster sensors"<<endl;




cin>>e1>>e2>>e3>>e4;



cout<<e1<<"J"<<" "<<e2<<"J"<<" "<<e3<<"J"<<" "<<e4<<"J"<<endl;



int b1,b2,b3,b4;
b1=r1*s1;
b2=r2*s2;
b3=r3*s3;
b4=r4*s4;

cout<<"Optimal Distance for best energy generation"<<endl;
float optimaldistance1=sqrt(energyamplitude*r1*r1/Eelec);
float optimaldistance2=sqrt(energyamplitude*r2*r2/Eelec);
float optimaldistance3=sqrt(energyamplitude*r3*r3/Eelec);
float optimaldistance4=sqrt(energyamplitude*r4*r4/Eelec);

cout<<optimaldistance1<<"cm"<<" "<<optimaldistance2<<"cm"<<" "<<optimaldistance3<<"cm"<<" "<<optimaldistance4<<"cm"<<endl;






int netb=( b1+b2+b3+b4)/4;
int r11,r21,r31,r41,r51;
cout<<"Enter radius of the  the sensors of second cluster in cm"<<endl;
cin>>r11>>r21>>r31>>r41;
int s11,s21,s31,s41,s51;
cout<<"Enter no of messages of the  the sensors"<<endl;
cin>>s11>>s21>>s31>>s41;
cout<<"packet information rate"<<endl;
s11=(int)(s11*factor);
s21=(int)(s21*factor);
s31=(int)(s31*factor);
s41=(int)(s41*factor);
cout<<s1<<"bits/s"<<" "<<s2<<"bits/s"<<" "<<s3<<"bits/s"<<" "<<s4<<"bits/s"<<endl;

float e5,e6,e7,e8;
float ej5,ej6,ej7,ej8;
cout<<"Sample Energy information for 2nd cluster sensors"<<endl;
ej5=(float)(energyamplitude*r11*r11 + Eelec)*s1;
ej6=(float)(energyamplitude*r21*r21 + Eelec)*s2;
ej7=(float)(energyamplitude*r31*r31 + Eelec)*s3;
ej8=(float)(energyamplitude*r41*r41 + Eelec)*s4;

ej5/=1000;
ej6/=1000;
ej7/=1000;
ej8/=1000;
cout<<ej5<<"J"<<" "<<ej6<<"J"<<" "<<ej7<<"J"<<" "<<ej8<<"J"<<endl;
cout<<"Input the energy of 2nd cluster sensors"<<endl;
cin>>e5>>e6>>e7>>e8;
int b11,b21,b31,b41;
b11=r11*s11;
b21=r21*s21;
b31=r31*s31;
b41=r41*s41;

cout<<"Optimal Distance for best energy generation"<<endl;
float optimaldistance5=sqrt(energyamplitude*r11*r11/Eelec);
float optimaldistance6=sqrt(energyamplitude*r21*r21/Eelec);
float optimaldistance7=sqrt(energyamplitude*r31*r31/Eelec);
float optimaldistance8=sqrt(energyamplitude*r41*r41/Eelec);

cout<<optimaldistance5<<"cm"<<" "<<optimaldistance6<<"cm"<<" "<<optimaldistance7<<"cm"<<" "<<optimaldistance8<<"cm"<<endl;



int netb1=( b11+b21+b31+b41)/4;

cout<<"average floating point constant first cluster"<<netb<<endl;
cout<<"average floating point constant second cluster"<<netb1<<endl;
cout<<"Initial energy of collector in J"<<endl;
cout<<totalenergy<<endl;
cout<<"Velocity of the collector"<<endl;
int velocity;
cin>>velocity;
cout<<"velocity in cm/s"<<endl;
cout<<"Distance from sink to cluster 1"<<endl;
int distance1;
cin>>distance1;
cout<<"Intercluster Distance in cm"<<endl;
cout<<distance1<<"cm"<<endl;
cout<<"Time taken for collector1 to go to cluster1"<<endl;

int time1=distance1/velocity;
cout<<time1<<"s"<<endl;
cout<<"Distance between sink and cluster2"<<endl;
int distance2;
cin>>distance2;
cout<<"Intercluster Distance in cm"<<endl;
cout<<distance2<<"cm"<<endl;
int velocity2;
cin>>velocity2;
cout<<"Velocity of the second collector"<<endl;
cout<<velocity2<<"cm/s"<<endl;
cout<<"Time taken for collector 2 to go to cluster2"<<endl;
int time2=distance2/velocity2;
cout<<time2<<"s"<<endl;


cout<<"-----"<<endl;
cout<<"TSP graphs cluster1"<<endl;
int graph[][V]={{ 0, 100, 150, 200 },
                       { 100, 0, 350, 250 },
                       { 150, 350, 0, 300 },
                       { 200, 250, 300, 0 }};


cout<<"----"<<endl;
cout<<"TSP graphs cluster2"<<endl;
int graph1[][V]={{ 0, 200, 250, 400 },
                       { 200, 0, 350, 450 },
                       { 250, 350, 0, 300 },
                       { 400, 450, 300, 0 }};

int s=0;
int maxtspval2=maxtsp(graph1,s);
int tspval2=tsp(graph1,s);
cout<<maxtspval2<<" "<<tspval2<<endl;
 s=0;
int maxtspval= maxtsp(graph,s);
int tspval= tsp(graph,s);
cout<<maxtspval<<" "<<tspval<<endl;

int i=0;

cout<<"-----"<<endl;
cout<<"radius bounded by 2-100cm"<<endl;
int maxradius=100;
int minradius=2;
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


i=0;
int lambda=0;
cout<<"Delta for change of k(int) = k*10^-10"<<endl;
 cout<<"delta between 200-500"<<endl;
 int delta;
 cin>>delta;
while(tspval < maxtspval   ||  maxtspval2>tspval2 || energyamplitude>=0||totalenergy>=0 || e1>=0 ||e2>=0||e3>=0||e4>=0 )
{
    lambda++;
    cout<<"------"<<endl;
    cout<<"Analysis"<<endl;

     cout<<lambda<<" iteration"<<endl;

 int m= tspval;
int delta1=(s1+s2+s3+s4)/4;
cout<<"Avg delta for first cluster"<<endl;
cout<<delta1<<endl;
int delta2=(s11+s21+s31+s41)/4;
cout<<"Avg delta for second cluster"<<endl;
cout<<delta2<<endl;
netb+=delta;
r1=r1-delta1/s1;
r2=r2-delta1/s2;
r3=r3-delta1/s3;
r4=r4-delta1/s4;
//r5=netb/s5;
netb1+=delta;
r11=r11-delta2/s11;
r21=r21-delta2/s21;
r31=r31-delta2/s31;
r41=r41-delta2/s41;

cout<<"-----"<<endl;
cout<<"Radius changes"<<endl;

cout<<"Radius change first cluster in cm"<<endl;
cout<<r1<<"cm"<<" "<<r2<<"cm"<<" "<<r3<<"cm"<<" "<<r4<<"cm"<<endl;
cout<<"Information source/packet rate change first cluster"<<endl;

cout<<s1<<"bits/s"<<" "<<s2<<"bits/s"<<" "<<s3<<"bits/s"<<" "<<s4<<"bits/s"<<endl;
vector<int> v;
v.push_back(s1);
v.push_back(s2);
v.push_back(s3);
v.push_back(s4);



vector<int> v1;
v1.push_back(s11);
v1.push_back(s21);
v1.push_back(s31);
v1.push_back(s41);



cout<<"Radius change second cluster in cm"<<endl;
cout<<r11<<"cm"<<" "<<r21<<"cm"<<" "<<r31<<"cm"<<" "<<r41<<"cm"<<endl;
cout<<"Information source/packet rate change second cluster"<<endl;

cout<<s11<<"bits/s"<<" "<<s21<<"bits/s"<<" "<<s31<<"bits/s"<<" "<<s41<<"bits/s"<<endl;

cout<<"----"<<endl;

cout<<"-----"<<endl;
cout<<"Sensor Energy  Loss Analysis"<<endl;

cout<<"Energy loss of the first cluster sources"<<endl;

e1-=(float)(((energyamplitude*r1*r1 + Eelec)*s1)/1000);
e2-=(float)(((energyamplitude*r2*r2 + Eelec)*s2)/1000);
e3-=(float)(((energyamplitude*r3*r3 + Eelec)*s3)/1000);
e4-=(float)(((energyamplitude*r4*r4 + Eelec)*s4)/1000);


cout<<e1<<"J"<<" "<<e2<<"J"<<" "<<e3<<"J"<<" "<<e4<<"J"<<" "<<endl;
cout<<"Energy loss of the second cluster sources"<<endl;
e5-=(float)(((energyamplitude*r11*r11 + Eelec)*s11)/1000);
e6-=(float)(((energyamplitude*r21*r21 + Eelec)*s21)/1000);
e7-=(float)(((energyamplitude*r31*r31 + Eelec)*s31)/1000);
e8-=(float)(((energyamplitude*r41*r41 + Eelec)*s41)/1000);


cout<<e5<<"J"<<" "<<e6<<"J"<<" "<<e7<<"J"<<" "<<e8<<"J"<<" "<<endl;

cout<<"-----"<<endl;
g1[0][1]+=(int)(delta/s1 + delta/s2);
g1[0][2]+=(int)(delta/s1 + delta/s3);
g1[0][3]+=(int)(delta/s1 + delta/s4);
g1[1][0]+=(int)(delta/s1 + delta/s2);
g1[1][2]+=(int)(delta/s2 + delta/s3);
g1[1][3]+=(int)(delta/s2 + delta/s4);
g1[2][0]+=(int)(delta/s3 + delta/s1);
g1[2][1]+=(int)(delta/s3 + delta/s2);
g1[2][3]+=(int)(delta/s3 + delta/s4);
g1[3][0]+=(int)(delta/s4 + delta/s1);
g1[3][1]+=(int)(delta/s4 + delta/s2);
g1[3][2]+=(int)(delta/s4 + delta/s3);



int mini;

int mini1;


g[0][1]+=(int)(delta/s1 + delta/s2);
g[0][2]+=(int)(delta/s1 + delta/s3);
g[0][3]+=(int)(delta/s1 + delta/s4);
g[1][0]+=(int)(delta/s1 + delta/s2);
g[1][2]+=(int)(delta/s2 + delta/s3);
g[1][3]+=(int)(delta/s2 + delta/s4);
g[2][0]+=(int)(delta/s3 + delta/s1);
g[2][1]+=(int)(delta/s3 + delta/s2);
g[2][3]+=(int)(delta/s3 + delta/s4);
g[3][0]+=(int)(delta/s4 + delta/s1);
g[3][1]+=(int)(delta/s4 + delta/s2);
g[3][2]+=(int)(delta/s4 + delta/s3);
cout<<"Graph updation of first cluster"<<endl;
for(i=0;i<4;i++)
{

    for(j=0;j<4;j++)
    {

        cout<<g[i][j]<<" ";
    }
    cout<<endl;
}

cout<<"----"<<endl;

cout<<"Graph updation of second cluster"<<endl;
for(i=0;i<4;i++)
{

    for(j=0;j<4;j++)
    {

        cout<<g1[i][j]<<" ";
    }
    cout<<endl;
}
cout<<"----"<<endl;
cout<<"Minimum information rate in cluster1"<<endl;
sort(v.begin(),v.end());
cout<<v[0]<<"bits/s"<<endl;
cout<<"Minimum information rate in cluster2"<<endl;
sort(v1.begin(),v1.end());
cout<<v1[0]<<"bits/s"<<endl;



int s=0;
cout<<"-----"<<endl;
cout<<"TSP module"<<endl;
cout<<"tsp in "<<lambda<<"iteration "<<tsp(g,0)<<endl;

tspval=tsp(g,0);
tspval2=tsp(g1,0);
cout<<"tsp first cluster"<<endl;
cout<<"tsp second cluster"<<endl;
cout<<tspval<<" "<<maxtspval<<endl;
cout<<tspval2<<" "<<maxtspval2<<endl;
tspval=time1+tspval;
tspval2=time2+tspval2;
cout<<"Time for 1 iteration in cluster one"<<endl;
cout<<tspval<<"s"<<endl;
cout<<"Time for1 iteration in cluster two"<<endl;
cout<<tspval2<<"s"<<endl;
cout<<"------"<<endl;

cout<<"-------"<<endl;
cout<<"Energy calculation of the collector"<<endl;
totalenergy-= (Eelec + energyamplitude*r1*r1 + energyamplitude*r2*r2 + energyamplitude*r3*r3 + energyamplitude*r4*r4);
cout<<"Energy loss in ith iteration"<<endl;
cout<<abs(totalenergy)<<"J"<<endl;
cout<<"Energy calculation of the collector afer second cluser"<<endl;
totalenergy-= (Eelec + energyamplitude*r11*r11 + energyamplitude*r21*r21 + energyamplitude*r31*r31 + energyamplitude*r41*r41);
cout<<"Energy loss in ith iteration"<<"J"<<endl;
cout<<abs(totalenergy)<<endl;
cout<<"-------"<<endl;

cout<<"-----"<<endl;
cout<<"Time Analysis"<<endl;
int total_time=tspval+tspval2;
cout<<"Total time loss"<<endl;
cout<<total_time<<"s"<<endl;



   if(maxtspval<=tspval || maxtspval2<=tspval2|| e1<0 || e2<0||e3<0 ||e4<0)
    {
    cout<<"End of iterations"<<endl;
      break;
  }


cout<<"----------------EOI--------------"<<endl;





}


cout<<"------------------------------------EOP--------------------"<<endl;


return 0;}

