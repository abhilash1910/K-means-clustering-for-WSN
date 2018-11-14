//Grid based random deployment of nodes

#include <bits/stdc++.h>
#define E_elec 0.000000005		//J/bit
#define E_amp  0.0000000001		//J/bit/m^2
#define L 1000					//Length of message in bits
#define R 102400				//Channel Capacity

using namespace std;

int collector_speed = 20;						//Speed of mobile data collector in m/s
double packet_generation_rate = 0.02;			//Packet generation rate in packets/s
int field_width = 500, field_height = 500;
int grid_dimensions = 50;
int no_of_nodes, alive_nodes;

struct position
{
	int x, y;
};

position sinkpos{field_height/2, field_width/2};

struct sensor_node
{
	int id;
	double ini_energy, res_energy;
	position pos;
	bool dead;
};

class grid
{
	public:
		int id, grid_height, grid_width, num_nodes, grid_size;
		bool merge_flag;						//Flag variable to denote whether a grid has been merged with other grids
		position start, end, centroid;
		vector<sensor_node> nodes;
		vector<grid*> neighbours;				//List that stores the neighbouring grids
		vector<grid> subgrids;					//List that stores the grids that have been merged with the current grid
		double res_energy;
		
		grid()
		{
			grid_height = grid_width = grid_dimensions;
			centroid.x = centroid.y = num_nodes = 0;
			grid_size = 1;
			merge_flag = false;
		}
};

double EuclideanDistance(position c1, position c2)
{
	return sqrt(pow(c1.x-c2.x,2) + pow(c1.y-c2.y,2));
}

bool belongs(grid g, position p)
{
	//Function to check whether point p lies inside grid g
	
	if(p.x >= g.start.x && p.x < g.end.x && p.y >= g.start.y && p.y < g.end.y)
		return true;
	else
		return false;
}

int findpos(vector<grid> v, grid g)
{
	int num = v.size();
	for(int i = 0; i < num; i++)
	{
		if(g.id == v[i].id)
			return i;	
	}
}

bool present(int key, vector<grid> g)
{
	int num = g.size();
	for(int i = 0; i < num; i++)
	{
		if(g[i].id == key)
			return true;
	}
	return false;
}

struct neighbour_compare
{
	bool operator()(grid* g1, grid* g2)
	{
		return (g1->id < g2->id);
	}
};

struct node_compare
{
	bool operator()(sensor_node sn1, sensor_node sn2)
	{
		return (sn1.id < sn2.id);
	}
};

vector<grid*> intersect_neighbour(grid g1, grid g2)
{
	//Function to find out the intersection of the neighbours of two grids
	set<grid*, neighbour_compare> s;
	int num1 = g1.neighbours.size(), num2 = g2.neighbours.size();
	for(int i = 0; i < num1; i++)
	{
		s.insert(g1.neighbours[i]);
	}
	for(int i = 0; i < num2; i++)
	{
		s.insert(g2.neighbours[i]);
	}
	vector<grid*> n;
	set<grid*, neighbour_compare>:: iterator it;
	for(it = s.begin(); it != s.end(); it++)
	{
		if((*it)->id != g1.id && (*it)->id != g2.id && !present((*it)->id, g1.subgrids) && !present((*it)->id, g2.subgrids)) 
			n.push_back(*it);				
	}	
	return n;
}

vector<sensor_node> intersect_nodes(vector<sensor_node> n1, vector<sensor_node> n2)
{
	//Function to find out the intersection of the nodes present in the two grids
	
	set<sensor_node, node_compare> s;
	int num1 = n1.size(), num2 = n2.size();
	for(int i = 0; i < num1; i++)
	{
		s.insert(n1[i]);
	}
	for(int i = 0; i < num2; i++)
	{
		s.insert(n2[i]);
	}
	vector<sensor_node> n;
	set<sensor_node, node_compare>:: iterator it;
	for(it = s.begin(); it != s.end(); it++)
		n.push_back(*it);
	return n;
}

void deployNodes(vector<sensor_node>& node, int field_width, int field_height)
{
	//Seeding random no. generator with system time
	time_t t;
	srand((unsigned)time(&t));
	
	int num_nodes = node.size();
	
	//Setting the parameters for the sensor nodes
	double temp;
	for(int i = 0; i < num_nodes; i++)
	{
		node[i].id = i+1;
		temp = ((double)rand()/(double)(RAND_MAX)) * 5;
		node[i].ini_energy = temp + 5;
		node[i].res_energy = node[i].ini_energy;
		node[i].pos.x = rand()%field_width;
		node[i].pos.y = rand()%field_height;
		node[i].dead = false;
	}
}

void formGrids(vector<vector<grid> >& grids, vector<sensor_node>& node)
{
	int num = grids.size();
	int counter = 1;
	int no_of_nodes = node.size(), cx, cy;
	double sum;
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++, counter++)
		{
			sum = cx = cy = 0;
			grids[i][j].id = counter;
			grids[i][j].start.x = i * grids[i][j].grid_height;
			grids[i][j].start.y = j * grids[i][j].grid_width;
			grids[i][j].end.x = grids[i][j].start.x + grids[i][j].grid_height;
			grids[i][j].end.y = grids[i][j].start.y + grids[i][j].grid_width;
			
			for(int k = 0; k < no_of_nodes; k++)
			{
				if(belongs(grids[i][j], node[k].pos))
				{
					grids[i][j].num_nodes++;
					grids[i][j].nodes.push_back(node[k]);
					cx += node[k].pos.x;
					cy += node[k].pos.y;
					sum += node[k].res_energy;
				}
			}
			
			if(grids[i][j].num_nodes > 0)
				grids[i][j].res_energy = sum/grids[i][j].num_nodes;
			else
				grids[i][j].res_energy = 0;
			
			//Setting the coordinates of the centroid
			if(grids[i][j].num_nodes > 0)
				grids[i][j].centroid.x = cx/grids[i][j].num_nodes;
			if(grids[i][j].num_nodes > 0)
				grids[i][j].centroid.y = cy/grids[i][j].num_nodes;
		}
	}
}

vector<grid> mergeGrids(vector<vector<grid> >& grids, double threshold, int threshold2)
{
	cout<<"\nThreshold = "<<threshold<<"\n\n";
	int num = grids.size();
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			//cout<<"\nGrid: "<<grids[i][j].id<<"\n";
			if(grids[i][j].res_energy >= threshold)
			{
				//cout<<"Grid "<<grids[i][j].id<<"\n-------------------\n";
				//int merged_grid_index;
				while(1)
				{
					//cout<<"Hello\n";
					int num_neighbour = grids[i][j].neighbours.size();
					int merged_grid_index = -1;				//Variable to store the index of the neighbouring grid that is to be merged
					position p, pos_centroid;
					double centroid_distance, min_centroid_distance = DBL_MAX;
					/*cout<<"\nCurrent neighbours of grid "<<grids[i][j].id<<" are: ";
					for(int k = 0; k < num_neighbour; k++)
					{
						cout<<grids[i][j].neighbours[k]->id<<" ";
					}
					cout<<"\n\n";*/
					for(int k = 0; k < num_neighbour; k++)
					{
						grid g = *(grids[i][j].neighbours[k]);
						if(g.merge_flag == false && g.res_energy < threshold && g.res_energy > 0)
						{
							centroid_distance = EuclideanDistance(grids[i][j].centroid, g.centroid);
							//cout<<g.id<<"\t"<<centroid_distance<<endl;
							p.x = (grids[i][j].centroid.x * grids[i][j].num_nodes + g.centroid.x * g.num_nodes)/(grids[i][j].num_nodes + g.num_nodes);
							p.y = (grids[i][j].centroid.y * grids[i][j].num_nodes + g.centroid.y * g.num_nodes)/(grids[i][j].num_nodes + g.num_nodes);
							bool flag = false;
							if(belongs(grids[i][j], p) || belongs(g, p))
								flag = true;
							else
							{
								int num_subgrid = grids[i][j].subgrids.size();
								for(int l = 0; l < num_subgrid; l++)
								{
									if(belongs(grids[i][j].subgrids[l], p))
									{
										flag = true;
										break;
									}
								}
							}
							if(flag && centroid_distance < min_centroid_distance)
							{
								min_centroid_distance = centroid_distance;
								pos_centroid = p;
								merged_grid_index = k;
							}
						}
					}
					if(merged_grid_index != -1)				//If we get a grid suitable for merging, we merge it to the current grid
					{
						int a, b, c = grids[i][j].neighbours[merged_grid_index]->id;
						a = (c-1)/num;
						b = (c-1)%num;
						grids[i][j].merge_flag = grids[i][j].neighbours[merged_grid_index]->merge_flag = true;						
						grids[i][j].subgrids.push_back(grids[a][b]);
						grids[i][j].centroid = pos_centroid;
						
						double total_energy = grids[i][j].res_energy * grids[i][j].num_nodes + grids[a][b].res_energy * grids[a][b].num_nodes;
						
						grids[i][j].neighbours = intersect_neighbour(grids[i][j], grids[a][b]);
						grids[i][j].nodes = intersect_nodes(grids[i][j].nodes, grids[a][b].nodes);
						grids[i][j].num_nodes = grids[i][j].num_nodes + grids[a][b].num_nodes;
						grids[i][j].grid_size++;
						
						grids[i][j].res_energy = total_energy/grids[i][j].num_nodes;
						
						/*cout<<"\nGrid "<<grids[a][b].id<<" merged with grid "<<grids[i][j].id<<"\n";
						cout<<"Grid "<<grids[i][j].id<<" size: "<<grids[i][j].grid_size<<endl;*/
					}	
					/*cout<<"\nHi!!!!\n";
					cout<<merged_grid_index<<endl;*/
					if(merged_grid_index == -1 || grids[i][j].grid_size >= threshold2)
						break;
				}
				cout<<endl;
			}
			//cout<<"\nHello\n\n";
		}
	}
	
	vector<grid> merged_grids;
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			if((grids[i][j].merge_flag == false || grids[i][j].grid_size > 1) && grids[i][j].num_nodes > 0)
			{
				merged_grids.push_back(grids[i][j]);
				/*cout<<"\nGrid "<<grids[i][j].id<<"\n--------\n";
				cout<<"Subgrids: ";
				int n = grids[i][j].subgrids.size();
				for(int k = 0; k < n; k++)
				{
					cout<<grids[i][j].subgrids[k].id<<" ";
				}
				cout<<endl;*/
			}
		}
	}
	return merged_grids;
}

int findEnergyDistance(vector<grid> merged_grids, double& max_re, double& min_re, double& max_distance)
{
	double dist;
	position starting_point;
	int start_index, size = merged_grids.size();
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			dist = EuclideanDistance(merged_grids[i].centroid, merged_grids[j].centroid);
			if(dist > max_distance)
				max_distance = dist;
		}
		if(merged_grids[i].res_energy > max_re)
		{
			max_re = merged_grids[i].res_energy;
		}
		if(merged_grids[i].res_energy < min_re)
		{
			min_re = merged_grids[i].res_energy;
			starting_point = merged_grids[i].centroid;
			start_index = i;
		}
	}
	return start_index;
}
 
vector<vector<double> > constructGraph(vector<grid> merged_grids, double max_re, double max_dist, float alpha, float beta)
{
	int size = merged_grids.size();
	vector<vector<double> > a(size, vector<double> (size));
	double energy_factor, dist_factor;
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(i == j)
			{
				a[i][j] = DBL_MAX;
			}
			else
			{
				energy_factor = merged_grids[j].res_energy/max_re;
				dist_factor = EuclideanDistance(merged_grids[i].centroid, merged_grids[j].centroid)/max_dist;
				a[i][j] = pow(energy_factor, alpha) * pow(dist_factor, beta);
			}
		}
	}
	return a;
}

void updateEnergy(grid& g, int n, double time_reqd)
{
	double energy = 0;
	for(int i = 0; i < n; i++)
	{
		sensor_node sn = g.nodes[i];
		if(!sn.dead)
		{
			double energy_consumed, dist = EuclideanDistance(sn.pos, g.centroid);
			//cout<<"\nTime: "<<time_reqd<<"\n";
			int packets_generated = packet_generation_rate * time_reqd; 
			//cout<<"\n"<<packets_generated<<"\n";   
			energy_consumed = L * packets_generated * (E_elec + E_amp * dist * dist);
			g.nodes[i].res_energy -= energy_consumed; 
			if(g.nodes[i].res_energy <= 0)
			{
				//cout<<g.nodes[i].res_energy<<"\n";
				g.nodes[i].dead = true;
				g.nodes[i].res_energy = 0;
				alive_nodes--;
			}
			else
				energy += g.nodes[i].res_energy;
		}
		
	}
	g.res_energy = energy/g.num_nodes;
	//return true;
}

void collectData(vector<grid> merged_grids)
{
	//Function that simulates the data collection
	
	ofstream filout, fout;
	filout.open("Data Collection.txt", ios::out);
	fout.open("Simulation Results/Average Energy Approach/Percentage_of_Alive_Nodes2.csv", ios::out);
	fout<<"Round, Percentage of Nodes Alive\n\n";
	int round, size = merged_grids.size(), curr_point, next_point, no_of_members;
	double dist, time_to_travel, latency = 0, total_waiting_time, percentage_alive;
	vector<double> extra_wait(size, 0);
	vector<int> visited_points;
	vector<int>:: iterator it;
	bool collect_flag = true;
	double alpha = 0.5, beta = 1-alpha;
	round = total_waiting_time = 0;
	while(round <= 50000)
	{
		double max_re = DBL_MIN, min_re = DBL_MAX, max_distance = 0, waiting_time = 0, time_curr_grid;
		int start_index = findEnergyDistance(merged_grids, max_re, min_re, max_distance);			//Find the max. RE, min. RE, the max. distance between any two sojourn points and the starting point for data collection
		
		if(round != 0)
		{
			//Before starting the current round, data collector has to move from the sink to the starting point of the current round
			dist = EuclideanDistance(sinkpos, merged_grids[start_index].centroid);
			time_to_travel = dist/collector_speed;
			total_waiting_time += time_to_travel;
			
			//cout<<"\nThe extra waiting times are:\n";
			for(it = visited_points.begin(); it != visited_points.end(); it++)
			{
				extra_wait[*it] += time_to_travel;
				//cout<<*it<<"\t"<<merged_grids[*it].id<<"\t"<<extra_wait[*it]<<"\n";
			}
		}
		
		//Constructing the complete graph for data collection
		vector<vector<double> > adj = constructGraph(merged_grids, max_re, max_distance, alpha, beta);
		
		filout<<"\n\nRound "<<round+1<<":\n";
		//cout<<"\n\nRound "<<round+1<<":\n";
		filout<<"\n\nMax RE = "<<max_re<<"\nMin RE = "<<min_re<<"\n";
	 
		curr_point = start_index; 
		no_of_members = merged_grids[curr_point].num_nodes;
		time_curr_grid = (double(L)/R) * no_of_members;
		
		double min_weight;
		visited_points.clear();
		visited_points.push_back(curr_point);
		filout<<merged_grids[curr_point].id<<"\t"<<merged_grids[curr_point].res_energy<<"\n";
		updateEnergy(merged_grids[curr_point], no_of_members, extra_wait[curr_point] + time_curr_grid);
		
//		if(!collect_flag)
//			break;
		
		extra_wait[curr_point] = 0;
		waiting_time += time_curr_grid;
		
		while(visited_points.size() < size)
		{
			min_weight = DBL_MAX;
			for(int i = 0; i < size; i++)
			{
				if(adj[curr_point][i] < min_weight && find(visited_points.begin(), visited_points.end(), i) == visited_points.end())
				{
					min_weight = adj[curr_point][i];
					next_point = i;
				}
			}
			
			dist = EuclideanDistance(merged_grids[curr_point].centroid, merged_grids[next_point].centroid);		//Find the distance to be travelled by the data collector
			time_to_travel = dist/collector_speed;				//Calculate the time taken by the collector to reach the next point using the distance determined in the previous step
			waiting_time += time_to_travel;
			
			for(it = visited_points.begin(); it != visited_points.end(); it++)
			{
				extra_wait[*it] += time_to_travel;
			}
				
			visited_points.push_back(next_point);
			curr_point = next_point;
			no_of_members = merged_grids[curr_point].num_nodes;
			time_curr_grid = (double(L)/R) * no_of_members;
			filout<<merged_grids[curr_point].id<<"\t"<<merged_grids[curr_point].res_energy<<"\n";
				
			//cout<<"\n"<<extra_wait[curr_point]<<"\n";
			updateEnergy(merged_grids[curr_point], no_of_members, waiting_time + extra_wait[curr_point] + time_curr_grid);
			
//			if(!collect_flag)
//				break;
				
			extra_wait[curr_point] = 0;
			waiting_time += time_curr_grid;
		}
//		if(collect_flag)
//			round++;
//		else
//			break;

		round++;
			
		total_waiting_time += waiting_time;						
		
		//At the end of the round, the data collector has to travel to the sink
		dist = EuclideanDistance(merged_grids[curr_point].centroid, sinkpos);
		time_to_travel = dist/collector_speed;
		total_waiting_time += time_to_travel;
		
		//cout<<"\nThe extra waiting times are:\n";
		for(it = visited_points.begin(); it != visited_points.end(); it++)
		{
			extra_wait[*it] += time_to_travel;
			//cout<<*it<<"\t"<<merged_grids[*it].id<<"\t"<<extra_wait[*it]<<"\n";
		}	
			
		//cout<<"\n\n";	
		
		if(round%1000 == 0)
		{
			if(alive_nodes < 0)
				break;
			percentage_alive = (double(alive_nodes)/no_of_nodes) * 100;
			fout<<round<<","<<percentage_alive<<"\n";
		}
			
	}
	if(round > 0)
		latency = total_waiting_time/round;
	//filout.close();
//	cout<<"\nAlpha = "<<alpha<<", Beta = "<<beta<<"\n";
//	cout<<"Lifetime of the network = "<<round<<" rounds\nLatency = "<<latency<<" seconds\n";
	//fout<<alpha<<","<<beta<<","<<round<<","<<latency<<"\n";	
	
}

int main()
{
	ofstream filout;
	cout<<"Enter the no. of nodes to be deployed: ";
	cin>>no_of_nodes;
	alive_nodes = no_of_nodes;
	vector<sensor_node> node(no_of_nodes);
	
	deployNodes(node, field_width, field_height);
	
	//Writing the data of the nodes
	filout.open("Node Info.csv", ios::out);
	filout<<"\nNode ID,Coordinates,Initial Energy,Residual Energy\n\n";
	for(int i = 0; i < no_of_nodes; i++)
	{
		filout<<node[i].id<<",("<<node[i].pos.x<<" "<<node[i].pos.y<<"),"<<node[i].ini_energy<<","<<node[i].res_energy<<"\n";
	}
	filout<<"\n";
	filout.close();
	
	//Grid Formation
	int num = field_width/grid_dimensions;
	vector<vector<grid> > grids(num, vector<grid> (num));
	formGrids(grids, node);
	
	//Finding the neighbours of each grid
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			if(i != 0)
				grids[i][j].neighbours.push_back(&grids[i-1][j]);
			if(j != 0)
				grids[i][j].neighbours.push_back(&grids[i][j-1]);
			if(j != num-1)
				grids[i][j].neighbours.push_back(&grids[i][j+1]);
			if(i != num-1)
				grids[i][j].neighbours.push_back(&grids[i+1][j]);
		}
	}
	
	double t_sum = 0;			//Variable to store sum of residual energies of all grids
	int num_nonzero_re = 0;		//Variable to count no. of grids having non-zero residual energy
	
	//Writing grid parameters
	filout.open("Grid Data.csv", ios::out);
	filout<<"Grid ID,Start,End,Height,Width,Neighbouring Grids,No. of Nodes,Nodes,Centroid,Avg. RE\n\n";
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			filout<<grids[i][j].id<<",("<<grids[i][j].start.x<<" "<<grids[i][j].start.y<<"),("<<grids[i][j].end.x<<" "<<grids[i][j].end.y<<"),"<<grids[i][j].grid_height<<","<<grids[i][j].grid_width<<",";
			for(int k = 0; k < grids[i][j].neighbours.size(); k++)
			{
				filout<<grids[i][j].neighbours[k]->id<<"; ";
			}
			filout<<","<<grids[i][j].num_nodes<<",";
			for(int k = 0; k < grids[i][j].num_nodes; k++)
			{
				filout<<grids[i][j].nodes[k].id<<"; ";
			}
			filout<<",";
			if(grids[i][j].num_nodes > 0)
			{
				filout<<"("<<grids[i][j].centroid.x<<" "<<grids[i][j].centroid.y<<")";
				num_nonzero_re++;
			}
			t_sum += grids[i][j].res_energy;
			filout<<","<<grids[i][j].res_energy;
			filout<<"\n";
		}
	}
	double threshold = t_sum/num_nonzero_re;			
	filout<<"\nThreshold for merging = Average of the residual energies of all the grids = "<<threshold<<"\n";
	filout.close();
	
	int count = 0;
	//cout<<"\nThe grids having non-zero residual energy less than threshold are as follows:\n";
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			if(grids[i][j].res_energy < threshold && grids[i][j].res_energy > 0)
			{
				//cout<<grids[i][j].id<<" ";
				count++;
			}
		}
	}
	cout<<"\n\nNo. of grids having non-zero residual energy less than threshold = "<<count<<"\n";
	
	/*******************************Merging of grids**************************************/
	
	int merge_upper_limit = 5;			//Upper limit of the no. of grids that can be merged into a single grid
	vector<grid> merged_grids = mergeGrids(grids, threshold, merge_upper_limit);
	//cout<<"Hello\n";
	
	//Storing the merged grids' data
	filout.open("Merged Grids.csv", ios::out);
	filout<<"Grid ID,No. of Nodes,Nodes,Centroid,Avg. RE,Grid Size,Subgrids\n\n";
	
	int size = merged_grids.size();
	for(int i = 0; i < size; i++)
	{
		filout<<merged_grids[i].id<<","<<merged_grids[i].num_nodes<<",";
		for(int j = 0; j < merged_grids[i].num_nodes; j++)
		{
			filout<<merged_grids[i].nodes[j].id<<"; ";
		}
		filout<<","<<merged_grids[i].centroid.x<<" "<<merged_grids[i].centroid.y<<","<<merged_grids[i].res_energy<<",";
		int n = merged_grids[i].subgrids.size();
		filout<<merged_grids[i].grid_size<<",";
		for(int j = 0; j < n; j++)
		{
			filout<<merged_grids[i].subgrids[j].id<<"; ";
		}
		filout<<endl;
	}
	filout.close();
	
	//Data Collection
	collectData(merged_grids);
	
	return 0;
}
