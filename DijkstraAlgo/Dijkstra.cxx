#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define totalnodesX       100
#define totalnodesY       100
#define euclideandistance 2. 

class vertex{
public:
  //
  vertex();
  ~vertex();
  //                                                                                                // For calculation of distance			        
  double            distance;                                                                       // distance from source				      	
  //												    	                                                        
  //                                                         					    // Intrinsict properties of a vertex		      	 
  pair<int,int>        coord;                                					    // cartesian coordinates				      	
  vector<vertex*>  neighbors;                                					    // neighbors                                             
  //												    
  friend bool operator== (const vertex & lhs, const vertex & rhs);
};
vertex::vertex(void){}
vertex::~vertex(void){}

bool operator==(const vertex & lhs, const vertex & rhs){                                            // Operator definition to compare elements of vertex class
  return lhs.coord==rhs.coord?true:false;                                                           // Based on position/coordinates
}
 
double calcdistance(vertex &A,vertex &B){
  double dsquare= (A.coord.first -B.coord.first )*(A.coord.first -B.coord.first )
                 +(A.coord.second-B.coord.second)*(A.coord.second-B.coord.second);                  // eucledian distance (cartesian example)
  return dsquare>euclideandistance*euclideandistance?totalnodesX*totalnodesY:sqrt(dsquare);         // only first and second neighbors connected (diagonal) 
};

void dijkstra(vector<vertex> &G,vertex &source_node){                                               // references so distance info can be updated

  vector<vertex> Q=G;                                                                               // copy input to define unvisited nodes
  source_node.distance=0;
  vertex *u = &source_node;                                                      

  while(!Q.empty()){
    for(vector<vertex*>::iterator v=u->neighbors.begin(); v < u->neighbors.end();v++){              // loop over neighbors of a node
      if(!(find(Q.begin(), Q.end(),**v) != Q.end())) continue;                                      // skip if node already visited
      else{
	double d=u->distance + calcdistance(*u,**v);                                                // calculate new distance
	if((*v)->distance>d){
	  (*v)->distance=d;                                                       
	  for(vector<vertex>::iterator w=G.begin(); w<G.end();w++) if(*w==**v) w->distance=d; 	    // update distance (this must be done better/more efficient)
	}
      }
    }
    Q.erase(remove(Q.begin(),Q.end(),*u),Q.end());                                                  // remove from unvisited nodes			    
    if(!u->neighbors.empty()){
      u = u->neighbors.front();                                                                     // pick next node from neighbors
      u->neighbors.erase(u->neighbors.begin());                                                     // remove from neighbors
    }else
      u = &Q.front();                                                                               // if no more neighbors check next unvisited 
  }
  return;
};
  
void createmap(vector<vertex> &G){  
  
  for(uint i=0; i<totalnodesX; i++)                                                                 // create nodes                                  
    for(uint j=0; j<totalnodesY; j++){
      vertex v;
      v.coord=pair<int,int>(i,j);                                                                   // assign cartesian coordinates (can be generalised to any metric)
      v.distance=totalnodesX*totalnodesY;                                                           // set distance/path to source to a large value
      G.push_back(v);                                                                               // fill vector of nodes
    }
  
  for(vector<vertex>::iterator v=G.begin();v<G.end()-1;v++ )                                        // assign neighbors, don't need to loop and find neibhors twice	
    for(vector<vertex>::iterator u=v+1;u<G.end();u++ ){            				    // the vertex is the neighbor of a vertex's neighbor
      if(calcdistance(*v,*u)<euclideandistance){
	v->neighbors.push_back(&*u);                               				    // fill vector of neighbor of v (with address)	
	u->neighbors.push_back(&*v);                               				    // fill vector of neighbor of u (with address)       
      }
    }
  
  return;
}

int main(){

  vector<vertex> G;  
  createmap(G);  
  //
  dijkstra(G,G.at(totalnodesX+1));
  //
  for(vector<vertex>::iterator v=G.begin();v<G.end();v++ )                                         // print coordinates and respective distances (path)
    cout<<v->coord.first<<","<<v->coord.second<<",\t  "<<v->distance<<endl;
  return 0;
}
  
