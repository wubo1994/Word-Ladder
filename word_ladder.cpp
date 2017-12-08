
//This is a word ladder program which deals not only
// single letter replacement but also single letter
// insertion and deletion
//
// Author: Bo Wu


#include <iostream>
#include <fstream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include "headers.h"

using namespace std;

// The structure for storing the vertex property
// Each word in the dictionary will be a vertax in the graph
typedef struct vertex_properties 
{
  string name;
}vertex_properties_t;



// The structure for storing the edge property
// The edge weight will be stored in it
typedef struct edge_properties
{
  int weight;
} edge_properties_t;


// All the useful boost types defined below
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vertex_properties_t, edge_properties_t> graph;
typedef graph::vertex_descriptor vertex_descriptor_t;
typedef graph::vertex_iterator vertex_iterator_t;
typedef graph::edge_descriptor   edge_descriptor_t;
typedef boost::property_map<graph, boost::vertex_index_t>::type index_map_t;
typedef boost::iterator_property_map<vertex_descriptor_t*, index_map_t*, vertex_descriptor_t, vertex_descriptor_t&> predecessor_map_t;



int main(void)
{
  // Create a graph for all of the words in dictionary
  graph allWords;

  // Read the "dictionary.txt" file and put all the words into graph
  ifstream dictionary("dictionary.txt");
  string word;
  vertex_descriptor_t t;
  vector <vertex_descriptor_t> vindex;//This is a vector which will be used to store all the descriptors for every vertex in graph
  int index=0;

  if(dictionary.is_open())
    {
      while(getline(dictionary,word))
        {
          word.pop_back();
          vindex.push_back(add_vertex(allWords));
          allWords[vindex[index]].name=word;
          index++;
        }
    }
  else
    cout<<"Cannot open input file, please make sure it is there."<<endl;

  dictionary.close();

  // Use two for loops to compare each word in the graph with
  // all the words after it, if the distance between two vertices is 1,
  // add an edge between them.

  cout<<"Building the graph......just one second!!!"<<endl;
  for(int it=0;it!=num_vertices(allWords);it++)
    {
      for(int that=it;that!=num_vertices(allWords);that++)
        {
          if(distance(allWords[vindex[it]].name,allWords[vindex[that]].name))
	    {
	      pair<edge_descriptor_t, bool> e =boost::add_edge(vindex[it],vindex[that],allWords);
              allWords[e.first].weight = 1;//Set the weight of all edges to 1, since there is no need to 
                                           // add any weight in this problem 
            }
        }
    }
  cout<<"Succeed!!!"<<endl;

  int numPairs;//Specify how many pairs of words is in the input
  string start;//The starting word
  string end;  //The ending word
 
  int firstIndex=-1;//Two integer variables for locating the position of each word pair
  int secondIndex=-1;

  ifstream inputFile;//Read the input file
  inputFile.open("input.txt");
  inputFile>>numPairs;

  ofstream outputFile;//The output file stream for writing the output
  outputFile.open("output.txt");
 
  //Go into graph for finding the descriptor 
  // of the start word
  for(int i=0;i<numPairs;i++)
    {
      inputFile>>start;
      inputFile>>end;
      for(int j=0;j<num_vertices(allWords);j++)
	{
	  if(allWords[vindex[j]].name==start)
	    {
	      firstIndex=j;
	      break;
	    }
	}

      for(int k=0;k<num_vertices(allWords);k++)
	{
	  if(allWords[vindex[k]].name==end)
	    {
	      secondIndex=k;
	      break;
	    }
	}

      if(firstIndex==(-1))
        cout<<start<<" is not in the dictionary."<<endl;
    
      else if(secondIndex==(-1))
        cout<<end<<" is not in the dictionary."<<endl;
     
      else
	{
      vector<int> distances( boost::num_vertices(allWords));
      vector<vertex_descriptor_t> predecessors(boost::num_vertices(allWords));

      //Using the dijkstra algorithm to find the shortest ladder
      boost::dijkstra_shortest_paths(allWords, vindex[firstIndex],
				     boost::weight_map(boost::get(&edge_properties_t::weight,allWords))
				     .distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index,allWords)))
				     .predecessor_map(boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index,allWords)))
				     );
    


  // Print the shortest ladder from first word to second word
  typedef vector<edge_descriptor_t> path_t;
  path_t path;

  vertex_descriptor_t v = vindex[secondIndex];
  for(vertex_descriptor_t u = predecessors[v]; u != v; v=u, u=predecessors[v])
  {
    pair<edge_descriptor_t,bool> edge_pair = boost::edge(u,v,allWords);
    path.push_back( edge_pair.first );
  }


  for(path_t::reverse_iterator riter = path.rbegin(); riter != path.rend(); ++riter)
  {
    vertex_descriptor_t u_tmp = boost::source(*riter, allWords);
    vertex_descriptor_t v_tmp = boost::target(*riter, allWords);
    edge_descriptor_t   e_tmp = boost::edge(u_tmp, v_tmp, allWords).first;
    outputFile<<allWords[u_tmp].name<<"  ";
  }
  outputFile<<end<<endl;
    }
      firstIndex=-1;
      secondIndex=-1;
    }    
  inputFile.close();
  outputFile.close();
 
  return 0;
}
