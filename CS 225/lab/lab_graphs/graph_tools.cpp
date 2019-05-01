/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    vector<Vertex> temp = graph.getVertices();
    for(size_t i = 0; i<temp.size(); i++)
      graph.setVertexLabel(temp[i],"UNEXPLORED");
    vector<Edge> temp1 = graph.getEdges();
    for(size_t i = 0; i<temp1.size(); i++)
      graph.setEdgeLabel(temp1[i].source,temp1[i].dest,"UNEXPLORED");
    queue<Vertex> q;
    q.push(temp[0]);
    graph.setVertexLabel(temp[0],"VISITED");
    Vertex first = temp[0];
    Vertex second = graph.getAdjacent(temp[0])[0];
    int min = graph.getEdgeWeight(first,second);
    while(!q.empty()){
       Vertex t = q.front();
       q.pop();
       vector<Vertex> temp2 = graph.getAdjacent(t);
       for(size_t i = 0; i<temp2.size();i++) {
          if(graph.getVertexLabel(temp2[i]) == "UNEXPLORED"){
             q.push(temp2[i]);
             graph.setEdgeLabel(t,temp2[i],"DISCOVERY");
             graph.setVertexLabel(temp2[i],"VISITED");
             int num = graph.getEdgeWeight(t,temp2[i]);
             if(num<min){
               min = num;
               first = t;
               second = temp2[i];
              }
            }
          else if(graph.getEdgeLabel(t,temp2[i])=="UNEXPLORED"){
              graph.setEdgeLabel(t,temp2[i],"CORSS");
              int num = graph.getEdgeWeight(t,temp2[i]);
              if(num<min){
               min = num;
               first = t;
               second = temp2[i];
              }
            }
        }
    }
   graph.setEdgeLabel(first,second,"MIN");
   return min;
    
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    vector<Vertex> temp = graph.getVertices();
    for(size_t i = 0; i<temp.size(); i++)
      graph.setVertexLabel(temp[i],"UNEXPLORED");
    vector<Edge> temp1 = graph.getEdges();
    for(size_t i = 0; i<temp1.size(); i++)
      graph.setEdgeLabel(temp1[i].source,temp1[i].dest,"UNEXPLORED");
    unordered_map<Vertex,Vertex> father;
    queue<Vertex> track;
    track.push(start);
    graph.setVertexLabel(start,"VISITED");
    while(!track.empty()){
    Vertex t = track.front();
    track.pop();
    vector<Vertex> temp2 = graph.getAdjacent(t);
    for(size_t i = 0; i<temp2.size(); i++){
       if(graph.getVertexLabel(temp2[i])=="UNEXPLORED"){
          graph.setVertexLabel(temp2[i],"VISITED");
          graph.setEdgeLabel(t,temp2[i],"DISCOVERY");
          father[temp2[i]] = t;
          track.push(temp2[i]);
          }
       else if(graph.getEdgeLabel(t,temp2[i]) == "UNEXPLORED"){
          graph.setEdgeLabel(t,temp2[i],"CORSS");
          //father[temp2[i]]=t;
          }
       }
    }
    int result = 0;
    Vertex tempE = end; 
    while(tempE!=start){
     result++;
     graph.setEdgeLabel(tempE,father[tempE],"MINPATH");
     tempE = father[tempE];
      }
    return result;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
   vector<Edge> edges = graph.getEdges();
   for(size_t i = 0; i<edges.size(); i++){
     for(size_t k = 0; k<i; k++){
        if(edges[k].weight>edges[i].weight){
            Edge temp = edges[k];
            edges[k] = edges[i];
            edges[i] = temp;
           }
        }
     }
   vector<Vertex> vertexs = graph.getVertices();
//   DisjointSets allSet;
//   allSet.addelements(vertexs.size());
   int numEdges = edges.size();
   int numVertex = vertexs.size();
   int count = 0;
   vector<int> allSet;
   for(int i = 0; i < numVertex;i++)
     allSet.push_back(-1);
   for(int i = 0; i < numEdges && count < numVertex - 1; i++)
	{
		Vertex u = edges[i].source;
		Vertex v = edges[i].dest;
                //if(allSet.find(u) != allSet.find(v))
                if(find(allSet,u) != find(allSet,v))
		{
			//allSet.setunion(u, v);
                       allSet[find(allSet,u)] = find(allSet,v);
			graph.setEdgeLabel(u, v, "MST");
			count++;
		}
	} 

 
}

int GraphTools::find(vector<int> temp,Vertex a){
   if(temp[a]<0) return a;
   else {
       temp[a] = find(temp,temp[a]);
       return find(temp,temp[a]);
  }
}
