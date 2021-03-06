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

#include "boost/graph/adjacency_list.hpp" // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TestSuite.h" // TestSuite
#include "cppunit/TextTestRunner.h" // TestRunner

#include "Graph.h"

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
        edGH = add_edge(vdG, vdH, g).first;}

    // -------------
    // test_add_edge
    // -------------

    void test_add_edge () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first == edAB);
        CPPUNIT_ASSERT(p.second == false);}
        
    void test_add_edge_1 () {
        graph_type temp = g;
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdD, temp);
        CPPUNIT_ASSERT(p.second == true);
    }
    
    void test_add_edge_2 () {
        graph_type temp = g;
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdA, temp);
        CPPUNIT_ASSERT(p.second == true);
    }
    
    void test_add_edge_3 () {
        graph_type temp = g;
        std::pair<edge_descriptor, bool> p = add_edge(vdB, vdA, temp);
        CPPUNIT_ASSERT(p.second == true);
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
            
    void test_adjacent_vertices_1 () {
        graph_type temp = g;
        vertex_descriptor vdT = add_vertex(temp);
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdT, temp);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b == e);
    }
    
    void test_adjacent_vertices_2 () {
        graph_type temp = g;
        vertex_descriptor vdT = add_vertex(temp);
        add_edge(vdT, vdA, temp);
        add_edge(vdT, vdB, temp);
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdT, temp);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if(b != e) {
            vertex_descriptor vx = *b;
            CPPUNIT_ASSERT(vx == vdA);
        }
        ++b;
        if(b != e) {
            vertex_descriptor vy = *b;
            CPPUNIT_ASSERT(vy == vdB);
        }
        
    }
    
    void test_adjacent_vertices_3 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdD, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        while(b != e) {
            CPPUNIT_ASSERT(!(*b == vdC));
            ++b;
        }
    }

    // ---------
    // test_edge
    // ---------

    void test_edge () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first == edAB);
        CPPUNIT_ASSERT(p.second == true);}
        
    void test_edge_1 () {
        std::pair<edge_descriptor, bool> p = edge(vdB, vdA, g);
        CPPUNIT_ASSERT(p.second == false);
    }
    
    void test_edge_2 () {
        graph_type temp = g;
        edge_descriptor AA = add_edge(vdA, vdA, temp).first;
        std::pair<edge_descriptor, bool> p = edge(vdA, vdA, temp);
        CPPUNIT_ASSERT(p.first == AA);
        CPPUNIT_ASSERT(p.second == true);
    }
    
    void test_edge_3 () {
        std::pair<edge_descriptor, bool> p = edge(vdC, vdD, g);
        CPPUNIT_ASSERT(p.first == edCD);
        CPPUNIT_ASSERT(p.second == true);
        p = edge(vdD, vdC, g);
        CPPUNIT_ASSERT(p.second == false);
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
            CPPUNIT_ASSERT(ed == edAB);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAC);}}
            
    void test_edges_1 () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator b = p.first;
        edge_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        int count = 0;
        while(b != e) {
            count++;
            b++;
        }
        CPPUNIT_ASSERT(count  == (int)num_edges(g));
    }
    
    void test_edges_2 () {
        graph_type temp;
        std::pair<edge_iterator, edge_iterator> p = edges(temp);
        edge_iterator b = p.first;
        edge_iterator e = p.second;
        CPPUNIT_ASSERT(b == e);
    }
    
    void test_edges_3 () {
        graph_type temp = g;
        add_edge(vdA, vdA, temp);
        std::pair<edge_iterator, edge_iterator> p = edges(temp);
        edge_iterator b = p.first;
        edge_iterator e = p.second;
        int count = 0;
        while(b != e) {
            count++;
            b++;
        }
        CPPUNIT_ASSERT(count == (int)num_edges(temp));
    }

    // --------------
    // test_num_edges
    // --------------

    void test_num_edges () {
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}

    void test_num_edges_1 () {
        graph_type temp;
        edges_size_type es = num_edges(temp);
        CPPUNIT_ASSERT(es == 0);
    }
    
    void test_num_edges_2 () {
        graph_type temp = g;
        edges_size_type es = num_edges(temp);
        CPPUNIT_ASSERT(es == 11);
        add_vertex(temp);
        es = num_edges(temp);
        CPPUNIT_ASSERT(es == 11);
    }
    
    void test_num_edges_3 () {
        graph_type temp = g;
        edges_size_type es = num_edges(temp);
        CPPUNIT_ASSERT(es == 11);
        add_edge(vdA, vdF, temp);
        es = num_edges(temp);
        CPPUNIT_ASSERT(es == 12);        
    }

    // -----------------
    // test_num_vertices
    // -----------------

    void test_num_vertices () {
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);}
        
    void test_num_vertices_1 () {
        graph_type temp;
        vertices_size_type vs = num_vertices(temp);
        CPPUNIT_ASSERT(vs == 0);
    }
    
    void test_num_vertices_2 () {
        graph_type temp = g;
        add_edge(vdA, vdA, temp);
        vertices_size_type vs = num_vertices(temp);
        CPPUNIT_ASSERT(vs == 8);
    }
    
    void test_num_vertices_3 () {
        graph_type temp = g;
        add_vertex(temp);
        vertices_size_type vs = num_vertices(temp);
        CPPUNIT_ASSERT(vs == 9);
    }

    // -----------
    // test_source
    // -----------

    void test_source () {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);}
        
    void test_source_1 () {
        graph_type temp = g;
        edge_descriptor AA = add_edge(vdA, vdA, temp).first;
        vertex_descriptor vd = source(AA, temp);
        CPPUNIT_ASSERT(vd == vdA);
    }
    
    void test_source_2 () {
        vertex_descriptor vd = source(edAC, g);
        CPPUNIT_ASSERT(vd == vdA);
    }
    
    void test_source_3 () {
        vertex_descriptor vd = source(edAE, g);
        CPPUNIT_ASSERT(vd != vdE);
    }

    // -----------
    // test_target
    // -----------

    void test_target () {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);}
        
    void test_target_1 () {
        graph_type temp = g;
        edge_descriptor AA = add_edge(vdA, vdA, temp).first;
        vertex_descriptor vd = target(AA, temp);
        CPPUNIT_ASSERT(vd == vdA);
    }
    
    void test_target_2 () {
        vertex_descriptor vd = target(edAC, g);
        CPPUNIT_ASSERT(vd == vdC);
    }
    
    void test_target_3 () {
        vertex_descriptor vd = target(edAE, g);
        CPPUNIT_ASSERT(vd == vdE);
    }

    // -----------
    // test_vertex
    // -----------

    void test_vertex () {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);}
        
    void test_vertex_1 () {
        graph_type temp = g;
        vertex_descriptor vdT = add_vertex(temp);
        CPPUNIT_ASSERT(num_vertices(temp) == 9);
        vertex_descriptor vd = vertex(8,temp);
        CPPUNIT_ASSERT(vd == vdT);
    }
    
    void test_vertex_2 () {
        graph_type temp = g;
        add_edge(vdA, vdH, temp);
        vertex_descriptor vd = vertex(0, temp);
        CPPUNIT_ASSERT(vd == vdA);
    }
    
    void test_vertex_3 () {
        vertex_descriptor vd = vertex(3, g);
        CPPUNIT_ASSERT(vd == vdD);
    }

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
            
    void test_vertices_1 () {
        graph_type temp;
        std::pair<vertex_iterator, vertex_iterator> p = vertices(temp);
        vertex_iterator b = p.first;
        vertex_iterator e = p.second;
        CPPUNIT_ASSERT(b == e);
    }
    
    void test_vertices_2 () {
        int count = 0;
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator b = p.first;
        vertex_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        while(b != e) {
            count++;
            b++;
        }
        CPPUNIT_ASSERT(count == (int)num_vertices(g));
    }
    
    void test_vertices_3 () {
        graph_type temp = g;
        add_edge(vdA, vdA, temp);
        std::pair<vertex_iterator, vertex_iterator> p = vertices(temp);
        vertex_iterator b = p.first;
        vertex_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        CPPUNIT_ASSERT(num_vertices(temp) == 8);
    }

    // --------------
    // test_has_cycle
    // --------------

    void test_has_cycle () {
        CPPUNIT_ASSERT(has_cycle(g));}
        
    void test_has_cycle_1 () {
        graph_type temp;
        CPPUNIT_ASSERT(!has_cycle(temp));
    }
    
    void test_has_cycle_2 () {
        graph_type temp;
        add_vertex(temp);
        CPPUNIT_ASSERT(!has_cycle(temp));
    }
    
    void test_has_cycle_3 () {
        graph_type temp;
        vertex_descriptor A = add_vertex(temp);
        add_edge(A, A, temp);
        CPPUNIT_ASSERT(has_cycle(temp));
    }

    // ---------------------
    // test_topological_sort
    // ---------------------

    void test_topological_sort () {
        std::ostringstream out;
        try{
            topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(false);
        }
        catch(boost::not_a_dag& d){
            CPPUNIT_ASSERT(true);
        }
    }
    
    void test_topological_sort_1 () {
        graph_type temp;
        add_vertex(temp);
        std::ostringstream out;
        try {
            topological_sort(temp, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(out.str() == "0 ");
        }
        catch(boost::not_a_dag& d){
            CPPUNIT_ASSERT(false);
        }
    }
    
    void test_topological_sort_2 () {
        graph_type temp;
        std::ostringstream out;
        try {
            topological_sort(temp, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(out.str() == "");
        }
        catch(boost::not_a_dag& d){
            CPPUNIT_ASSERT(false);
        }
    }
    
    void test_topological_sort_3 () {
        graph_type temp;
        vertex_descriptor A = add_vertex(temp);
        vertex_descriptor B = add_vertex(temp);
        vertex_descriptor C = add_vertex(temp);
        vertex_descriptor D = add_vertex(temp);
        add_edge(A, B, temp);
        add_edge(A, D, temp);
        add_edge(B, C, temp);
        std::ostringstream out;
        try {
            topological_sort(temp, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(out.str() == "2 1 3 0 ");
        }
        catch(boost::not_a_dag& d){
            CPPUNIT_ASSERT(false);
        }
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge);
    CPPUNIT_TEST(test_add_edge_1);
    CPPUNIT_TEST(test_add_edge_2);
    CPPUNIT_TEST(test_add_edge_3);
    CPPUNIT_TEST(test_adjacent_vertices);
    CPPUNIT_TEST(test_adjacent_vertices_1);
    CPPUNIT_TEST(test_adjacent_vertices_2);
    CPPUNIT_TEST(test_adjacent_vertices_3);
    CPPUNIT_TEST(test_edge);
    CPPUNIT_TEST(test_edge_1);
    CPPUNIT_TEST(test_edge_2);
    CPPUNIT_TEST(test_edge_3);
    CPPUNIT_TEST(test_edges);
    CPPUNIT_TEST(test_edges_1);
    CPPUNIT_TEST(test_edges_2);
    CPPUNIT_TEST(test_edges_3);
    CPPUNIT_TEST(test_num_edges);
    CPPUNIT_TEST(test_num_edges_1);
    CPPUNIT_TEST(test_num_edges_2);
    CPPUNIT_TEST(test_num_edges_3);
    CPPUNIT_TEST(test_num_vertices);
    CPPUNIT_TEST(test_num_vertices_1);
    CPPUNIT_TEST(test_num_vertices_2);
    CPPUNIT_TEST(test_num_vertices_3);
    CPPUNIT_TEST(test_source);
    CPPUNIT_TEST(test_source_1);
    CPPUNIT_TEST(test_source_2);
    CPPUNIT_TEST(test_source_3);
    CPPUNIT_TEST(test_target);
    CPPUNIT_TEST(test_target_1);
    CPPUNIT_TEST(test_target_2);
    CPPUNIT_TEST(test_target_3);
    CPPUNIT_TEST(test_vertex);
    CPPUNIT_TEST(test_vertex_1);
    CPPUNIT_TEST(test_vertex_2);
    CPPUNIT_TEST(test_vertex_3);
    CPPUNIT_TEST(test_vertices);
    CPPUNIT_TEST(test_vertices_1);
    CPPUNIT_TEST(test_vertices_2);
    CPPUNIT_TEST(test_vertices_3);
    CPPUNIT_TEST(test_has_cycle);
    CPPUNIT_TEST(test_has_cycle_1);
    CPPUNIT_TEST(test_has_cycle_2);
    CPPUNIT_TEST(test_has_cycle_3);
    CPPUNIT_TEST(test_topological_sort);
    CPPUNIT_TEST(test_topological_sort_1);
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
    tr.addTest(TestGraph<Graph>::suite()); // uncomment
    tr.run();

    cout << "Done." << endl;
    return 0;}
