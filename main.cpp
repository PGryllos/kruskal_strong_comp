// Ceid Upatras academic year 2013-2014
// Boost my_kruskal testing on random and grided undirected graphs.
// file main.cpp
#include "hw02.h"
    
// auxiliary function to estimate execution time for both my_STRONG_COMPONENTS & STRONG_COMPONENTS
static void test(Graph& G, WeightMap& WM, Edges_Vector& T, std::chrono::duration<double>& el_s1)
{
    // auxiliary time variables 
    std::chrono::time_point<std::chrono::system_clock> start, end;

    // timing my_Kruskal()
    start = std::chrono::system_clock::now();
    my_Kruskal(G, WM, T);
    end = std::chrono::system_clock::now();
    el_s1 = end - start;
    std::cout<<"my_Kruskal returned successfully"<<"\n";
}

int main()
{

    // auxiliary variables
    Edges_Vector T;
    Distribution distribution(1, 10000);
    int Gsize_rand [] = { 1000, 4000, 7000 };
    // int Gsize_grid [] = { 4000, 8000, 15000 };
    std::chrono::duration<double> elaps_sec;
    Gen gen; 
    Rand_Int rng;
    

    std::cout<<"\n[Testing on random graphes]\n"<<std::endl;
    for(unsigned int i=0; i<sizeof(Gsize_rand)/sizeof(Gsize_rand[0]); i++)
    {
        // create graph g based on the small world model,
        // here we constract a small-world graph with Gsize_rand[i] vertices,
        // each connected to its 3 nearest neighbors.Edges in the graph are 
        // randomly rewired to different vertices with a probability of 0.04
        Graph g(SWGen(gen, Gsize_rand[i], 3, 0.04), SWGen(), Gsize_rand[i]);
        // #TODO create some tests to ensure that the generated graph
        // has no unconnected vertices using dfs_search etc

        // create property map so that we can access properties
        WeightMap wm = boost::get(boost::edge_weight, g);

        // seeding random integer generator with system_clock 
        rng.seed(std::time(NULL));
        boost::variate_generator < Rand_Int&, Distribution > generator(rng, distribution);
        // assigning random values between 1 and 10000 to edge weights
        boost::randomize_property < boost::edge_weight_t > (g, generator);
        std::cout<<"Graph["<<i+1<<"] generated\t vertices:"<<num_vertices(g)<<std::endl;
        // call tester to calculate execution times
        test(g,wm,T,elaps_sec);

        std::cout<<"\t>>> my_Kruskal elapsed time: "<<elaps_sec.count()<<"s \n";
//      std::cout<<"\t>>> STRONG_COMPONENTS(LEDA) elapsed time: "<<elapsed_seconds2.count()<<"s \n";
//
//      // initializing graph again 
        g.clear();
    }
//
//  std::cout<<"\n[Testing on cliqued graphes]\n"<<std::endl;
//  // creating cliqued graphs
//  for (unsigned int it=0; it<sizeof(Gsize2)/sizeof(Gsize2[0]); it++)
//  {
//      // creating the first clique 
//      leda::complete_graph(temp, Gsize2[it]/cliques[it]);        
//      // adding clique to the graph
//      G.join(temp);
//
//      // we now chose random nodes from the first clique
//      // temp_n1 is going to be used as starting node for dfs.
//      // this will ensure us that an unreached node belongs
//      // to the newest clique.
//      // temp_n2 is going to be used a pointer to a node from
//      // the last added clique, so that we can do the linking with
//      // the next clique
//      temp_n1 = G.choose_node();
//      temp_n2 = G.choose_node();
//
//      // in this loop, the rest of the cliques are going to be created 
//      // and added to the rest of the graph
//      for (unsigned int it1=1; it1<cliques[it]; it1++) 
//      {
//          leda::complete_graph(temp, Gsize2[it]/cliques[it]);        
//          G.join(temp);
//          // we are going to run DFS on graph G, the nodes that 
//          // are not reached are part of the most recently created clique
//          reached.init(G,false);
//          LN = DFS(G,temp_n1,reached);
//          forall_nodes(x,G)
//          {
//              // for the first unreached node we find (which should be part
//              // of the newest clique) we create an edge to connect it with a
//              // random node from the previews clique and then we store that 
//              // node to use it for the next linking
//              if (!reached[x])
//              {
//                  G.new_edge(temp_n2,x);
//                  temp_n2 = x;
//                  break;
//              }
//          }
//      }
//
//      // using test function to get elapsed times
//      leda::node_array<int> compnum(G,0);
//      std::cout<<"Graph["<<it+1<<"] generated\t nodes:"<<G.number_of_nodes()<<std::endl;
//      test(G,compnum,elapsed_seconds1,elapsed_seconds2);
//      std::cout<<"\t>>> My_STRONG_COMPONENTS elapsed time: "<<elapsed_seconds1.count()<<"s \n";
//      std::cout<<"\t>>> STRONG_COMPONENTS(LEDA) elapsed time: "<<elapsed_seconds2.count()<<"s \n";
//
//      compnum.init(G,0);
//      G.clear();
//  }
    return 0;
}
