// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2012
// Glenn P. Downing
// ----------------------------

/*
To test the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% ls /public/linux/include/boost-1_44/boost/graph/
...
adjacency_list.hpp
...
% g++ -ansi -pedantic -I/public/linux/include/boost-1_44 -lcppunit -ldl -Wall TestGraph.c++ -o TestGraph.app
% valgrind TestGraph.app >& TestGraph.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream> // ostringstream
#include <utility> // pair
#include <typeinfo>
#include "boost/graph/adjacency_list.hpp" // adjacency_list
#include <boost/graph/exception.hpp>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TestSuite.h" // TestSuite
#include "cppunit/TextTestRunner.h" // TestRunner
#include "Graph.h"
//#include <boost/graph/topological_sort.hpp>

using namespace std;
// ---------
// TestGraph
// ---------

template <typename T>
struct TestGraph : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef T graph_type;

    typedef typename graph_type::vertex_descriptor vertex_descriptor;
    typedef typename graph_type::edge_descriptor edge_descriptor;

    typedef typename graph_type::vertex_iterator vertex_iterator;
    typedef typename graph_type::edge_iterator edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type edges_size_type;

    // -----
    // tests
    // -----

    // directed, sparse, unweighted
    // possibly connected
    // possibly cyclic
    graph_type g;

    vertex_descriptor vdA;
    vertex_descriptor vdB;
    vertex_descriptor vdC;
    vertex_descriptor vdD;
    vertex_descriptor vdE;
    vertex_descriptor vdF;
    vertex_descriptor vdG;
    vertex_descriptor vdH;

    edge_descriptor edAB;
    edge_descriptor edAC;
    edge_descriptor edAE;
    edge_descriptor edBD;
    edge_descriptor edBE;
    edge_descriptor edCD;
    edge_descriptor edDE;
    edge_descriptor edDF;
    edge_descriptor edFD;
    edge_descriptor edFH;
    edge_descriptor edGH;

    graph_type h;

    vertex_descriptor hvA;
    vertex_descriptor hvB;
    vertex_descriptor hvC;
    vertex_descriptor hvD;
    vertex_descriptor hvE;
    vertex_descriptor hvF;
    vertex_descriptor hvG;

    edge_descriptor hedAB;
    edge_descriptor hedAC;
    edge_descriptor hedAE;
    edge_descriptor hedBD;
    edge_descriptor hedBE;
    edge_descriptor hedCD;
    edge_descriptor hedDE;
    edge_descriptor hedDF;

    graph_type q; 
    
    vertex_descriptor qA;
    vertex_descriptor qB;
    vertex_descriptor qC;
    
    edge_descriptor qAB;
    edge_descriptor qBC;
    edge_descriptor qCA;

    // -----
    // setUp
    // -----

    void setUp () {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        vdC = add_vertex(g);
        vdD = add_vertex(g);
        vdE = add_vertex(g);
        vdF = add_vertex(g);
        vdG = add_vertex(g);
        vdH = add_vertex(g);
        
        edAB = add_edge(vdA, vdB, g).first;
        edAC = add_edge(vdA, vdC, g).first;
        edAE = add_edge(vdA, vdE, g).first;
        edBD = add_edge(vdB, vdD, g).first;
        edBE = add_edge(vdB, vdE, g).first;
        edCD = add_edge(vdC, vdD, g).first;
        edDE = add_edge(vdD, vdE, g).first;
        edDF = add_edge(vdD, vdF, g).first;
        edFD = add_edge(vdF, vdD, g).first;
        edFH = add_edge(vdF, vdH, g).first;
        edGH = add_edge(vdG, vdH, g).first;

        hvA = add_vertex(h);
        hvB = add_vertex(h);
        hvC = add_vertex(h);
        hvD = add_vertex(h);
        hvE = add_vertex(h);
        hvF = add_vertex(h);
        hvG = add_vertex(h); 

        hedAB = add_edge(hvA, hvB, h).first;
        hedAC = add_edge(hvA, hvC, h).first;
        hedAE = add_edge(hvA, hvE, h).first;
        hedBD = add_edge(hvB, hvD, h).first;
        hedBE = add_edge(hvB, hvE, h).first;
        hedCD = add_edge(hvC, hvD, h).first;
        hedDE = add_edge(hvD, hvE, h).first;
        hedDF = add_edge(hvD, hvF, h).first;
      
        qA = add_vertex(q);
        qB = add_vertex(q);
        qC = add_vertex(q);
         
        qAB = add_edge(qA, qB, q).first;
        qBC = add_edge(qB, qC, q).first;
        qCA = add_edge(qC, qA, q).first;


    }

    // -------------
    // test_add_edge
    // -------------

    void test_add_edge () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first == edAB);
        CPPUNIT_ASSERT(p.second == false);}

    void test_add_edge_2() {
        std::pair<edge_descriptor, bool> p = add_edge(qC, qA, q); 
        CPPUNIT_ASSERT(p.second == false); 
    }

    
    void test_add_edge_3() { 
        std::pair<edge_descriptor, bool> p = add_edge(qA, qB, q);
        CPPUNIT_ASSERT(p.first == qAB);
        CPPUNIT_ASSERT(p.second == false);
    }


    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    void test_adjacent_vertices () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdC);}}

    void test_adjacent_vertices_2 () {
        int i = 0;
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdF, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        while (b != e) {
            ++b;
            ++i;
        }
        CPPUNIT_ASSERT(i == 2);
    }

    void test_adjacent_vertices_3() {
        pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdB, g); 
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
             vertex_descriptor vd = *b;
             CPPUNIT_ASSERT(vd == vdD);
        }
        ++b;
        if(b != e){
             vertex_descriptor vd = *b; 
             CPPUNIT_ASSERT(vd == vdE);
        }
    }
    

    // ---------
    // test_edge
    // ---------

    void test_edge () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first == edAB);
        CPPUNIT_ASSERT(p.second == true);}
 
    void test_edge_2() { 
        std::pair<edge_descriptor, bool> p = edge(vdA, vdF, g);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_edge_3() { 
        std::pair<edge_descriptor, bool> p = edge(qC, qA, q);
        CPPUNIT_ASSERT(p.second == true);
    }

    // ----------
    // test_edges
    // ----------

    void test_edges () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator b = p.first;
        edge_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAB);
        }
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAC);}
        ++b;}

    void test_edges_2 () {
        std::pair<edge_iterator, edge_iterator> p = edges(q);
        edge_iterator b = p.first;
        edge_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == qAB);
        }
    }

    void test_edges_3 () {
        std::pair<edge_iterator, edge_iterator> p = edges(h);
        edge_iterator b = p.first;
        edge_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == hedAB);
        }
    }

    // --------------
    // test_num_edges
    // --------------

    void test_num_edges () {
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}
  
    void test_num_edges_2() { 
        edges_size_type es = num_edges(h);
        CPPUNIT_ASSERT(es == 8);
    }
     
    void test_num_edges_3() { 
        edges_size_type es = num_edges(q);
        CPPUNIT_ASSERT(es == 3); 
    }

    // -----------------
    // test_num_vertices
    // -----------------

    void test_num_vertices () {
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);}

    void test_num_vertices_2() {
        vertices_size_type vs = num_vertices(q);
        CPPUNIT_ASSERT(vs == 3);
    }
 
    void test_num_vertices_3() {
        vertices_size_type vs = num_vertices(h); 
        CPPUNIT_ASSERT(vs == 7);
    }

    // -----------
    // test_source
    // -----------

    void test_source () {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_source_2 () {
        vertex_descriptor vd = source(qAB, q);
        CPPUNIT_ASSERT(vd == qA);}

    void test_source_3 () {
        vertex_descriptor vd = source(hedAB, h);
        CPPUNIT_ASSERT(vd == hvA);}

    // -----------
    // test_target
    // -----------

    void test_target () {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);}

    void test_target_2 () {
        vertex_descriptor vd = target(qBC, g);
        CPPUNIT_ASSERT(vd == qC);}

    void test_target_3 () {
        vertex_descriptor vd = target(edCD, g);
        CPPUNIT_ASSERT(vd == vdD);}

    // -----------
    // test_vertex
    // -----------

    void test_vertex () {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);}


    void test_vertex_2 () {
        vertex_descriptor vd = vertex(1, q);
        CPPUNIT_ASSERT(vd == qB);}


    void test_vertex_3 () {
        vertex_descriptor vd = vertex(0, h);
        CPPUNIT_ASSERT(vd == hvA);}

    // -------------
    // test_vertices
    // -------------

    void test_vertices () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator b = p.first;
        vertex_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdA);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB);}}

    void test_vertices_2 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(q);
        vertex_iterator b = p.first;
        vertex_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == qA);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == qB);}
        
    
    }

    void test_vertices_3 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(h);
        vertex_iterator b = p.first;
        vertex_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == hvA);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == hvB);}}

    // --------------
    // test_has_cycle
    // --------------

    void test_has_cycle () {
        CPPUNIT_ASSERT(has_cycle(g));}

    void test_has_cycle_2() { 
        CPPUNIT_ASSERT(!has_cycle(h));}


    void test_has_cycle_3() { 
        CPPUNIT_ASSERT(has_cycle(q));}


   // ---------------------
   // test_topological_sort
   // ---------------------

   void test_topological_sort () {
        std::ostringstream out;
        try{ 
            topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
        }catch (invalid_argument& not_a_dag){ 
            CPPUNIT_ASSERT(true);
        }

       
    }

   void test_topological_sort_2 () {
        std::ostringstream out;
        try{ 
            topological_sort(h, std::ostream_iterator<vertex_descriptor>(out, " "));
        }catch (invalid_argument& not_a_dag){ 
            CPPUNIT_ASSERT(false);
        }
         

        CPPUNIT_ASSERT(out.str() == "4 5 3 1 2 0 6 ");
    }

   void test_topological_sort_3 () {
        std::ostringstream out;
        try{ 
            topological_sort(q, std::ostream_iterator<vertex_descriptor>(out, " "));
        }catch (invalid_argument& not_a_dag){ 
            CPPUNIT_ASSERT(true);
        }

        
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge);
    CPPUNIT_TEST(test_add_edge_2);
    CPPUNIT_TEST(test_add_edge_3);

    CPPUNIT_TEST(test_adjacent_vertices);
    CPPUNIT_TEST(test_adjacent_vertices_2);
    CPPUNIT_TEST(test_adjacent_vertices_3);

    CPPUNIT_TEST(test_edge);
    CPPUNIT_TEST(test_edge_2);
    CPPUNIT_TEST(test_edge_3);

    CPPUNIT_TEST(test_edges);
    CPPUNIT_TEST(test_edges_2);
    CPPUNIT_TEST(test_edges_3);

    CPPUNIT_TEST(test_num_edges);
    CPPUNIT_TEST(test_num_edges_2);
    CPPUNIT_TEST(test_num_edges_3);

    CPPUNIT_TEST(test_num_vertices);
    CPPUNIT_TEST(test_num_vertices_2);
    CPPUNIT_TEST(test_num_vertices_3);

    CPPUNIT_TEST(test_source);
    CPPUNIT_TEST(test_source_2);
    CPPUNIT_TEST(test_source_3);

    CPPUNIT_TEST(test_target);
    CPPUNIT_TEST(test_target_2);
    CPPUNIT_TEST(test_target_3);

    CPPUNIT_TEST(test_vertex);
    CPPUNIT_TEST(test_vertex_2);
    CPPUNIT_TEST(test_vertex_3);

    CPPUNIT_TEST(test_vertices);
    CPPUNIT_TEST(test_vertices_2);
    CPPUNIT_TEST(test_vertices_3);

    CPPUNIT_TEST(test_has_cycle);
    CPPUNIT_TEST(test_has_cycle_2);
    CPPUNIT_TEST(test_has_cycle_3);
  
    CPPUNIT_TEST(test_topological_sort);
    CPPUNIT_TEST(test_topological_sort_2);
    CPPUNIT_TEST(test_topological_sort_3);

    CPPUNIT_TEST_SUITE_END();};


// ----
// main
// ----

int main () {
    using namespace std;
    using namespace boost;

    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestGraph.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestGraph< adjacency_list<setS, vecS, directedS> >::suite());
    tr.addTest(TestGraph<Graph>::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
