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

#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <iostream> // cout, endl

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Graph.h"

// ---------
// TestGraph
// ---------

template <typename T>
struct TestGraph : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

    // -----c
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
        vdA  = add_vertex(g);
        vdB  = add_vertex(g);
        vdC  = add_vertex(g);
        vdD  = add_vertex(g);
        vdE  = add_vertex(g);
        vdF  = add_vertex(g);
        vdG  = add_vertex(g);
        vdH  = add_vertex(g);
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
        
    }

    // -------------
    // test_add_edge
    // -------------

    void test_add_edge1 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == false);}

    void test_add_edge2 () {
        std::pair<edge_descriptor, bool> p =  add_edge(vdC, vdD, g);
        CPPUNIT_ASSERT(p.first  == edCD);
        CPPUNIT_ASSERT(p.second == false);}

    void test_add_edge3 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdG, vdH, g);
        CPPUNIT_ASSERT(p.second == true);}

    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    void test_adjacent_vertices1 () {
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

    void test_adjacent_vertices2 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdF, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdD);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdH);}}

    void test_adjacent_vertices3 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdD, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdE);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdF);}}


    // ---------
    // test_edge
    // ---------
    void test_edge1 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);}

    void test_edge2 () {
        std::pair<edge_descriptor, bool> p = edge(vdD, vdE, g);
        CPPUNIT_ASSERT(p.first  == edDE);
        CPPUNIT_ASSERT(p.second == true);}

    void test_edge3 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdF, g);
        CPPUNIT_ASSERT(p.second == false);}

    // ----------
    // test_edges
    // ----------

    void test_edges1 () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAB);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAC);}}

    void test_edges2 () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        ++b;
        ++b;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAE);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edBD);}}

    void test_edges3 () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        ++b;
        ++b;
        ++b;
        ++b;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edBE);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edCD);}}

    // --------------
    // test_num_edges
    // --------------

    void test_num_edges1 () {
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 10);}
    void test_num_edges2 () {
        add_edge(vdF, vdE, g);
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}
    void test_num_edges3 () {
        //to test that adding an existing edge does NOT inc the value of size
        add_edge(vdF, vdE, g);
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}



    // -----------------
    // test_num_vertices
    // -----------------

    void test_num_vertices1 () {
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);}
    void test_num_vertices2 () {
        add_vertex(g);
        add_vertex(g);
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 10);}
    void test_num_vertices3 () {
        add_vertex(g);
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 9);}

    // -----------
    // test_source
    // -----------

    void test_source1 () {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);}
    void test_source2 () {
        vertex_descriptor vd = source(edCD, g);
        CPPUNIT_ASSERT(vd == vdC);}
    void test_source3 () {
        vertex_descriptor vd = source(edFD, g);
        CPPUNIT_ASSERT(vd == vdF);}

    // -----------
    // test_target
    // -----------

    void test_target1 () {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);}
    void test_target2 () {
        vertex_descriptor vd = target(edDF, g);
        CPPUNIT_ASSERT(vd == vdF);}
    void test_target3 () {
        vertex_descriptor vd = target(edFH, g);
        CPPUNIT_ASSERT(vd == vdH);}

    // -----------
    // test_vertex
    // -----------

    void test_vertex1 () {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);}
    void test_vertex2 () {
        vertex_descriptor vd = vertex(1, g);
        CPPUNIT_ASSERT(vd == vdB);}
    void test_vertex3 () {
        vertex_descriptor vd = vertex(2, g);
        CPPUNIT_ASSERT(vd == vdC);}

    // -------------
    // test_vertices
    // -------------
    void test_vertices1 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdA);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB);}
        }

    void test_vertices2 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ++b;
        ++b;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdC);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdD);}
        }

    void test_vertices3 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        ++b;
        ++b;
        ++b;
        ++b;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdE);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdF);}
        }

    // --------------
    // test_has_cycle
    // --------------

    void test_has_cycle1 () {
        graph_type a;
        vertex_descriptor avdA;
        vertex_descriptor avdB;
        vertex_descriptor avdC;
        edge_descriptor aedAB;
        edge_descriptor aedAC;
        avdA  = add_vertex(a);
        avdB  = add_vertex(a);
        avdC  = add_vertex(a);
        aedAB = add_edge(avdA, avdB, a).first;
        aedAC = add_edge(avdA, avdC, a).first;

        CPPUNIT_ASSERT(!has_cycle(a));
    }

    void test_has_cycle2 () {
        graph_type a;
        vertex_descriptor avdA;
        vertex_descriptor avdB;
        vertex_descriptor avdC;
        edge_descriptor aedAB;
        edge_descriptor aedBC;
        edge_descriptor aedCA;

        avdA  = add_vertex(a);
        avdB  = add_vertex(a);
        avdC  = add_vertex(a);

        aedAB = add_edge(avdA, avdB, a).first;
        aedBC = add_edge(avdB, avdC, a).first;
        aedCA = add_edge(avdC, avdA, a).first;

        CPPUNIT_ASSERT(has_cycle(a));
    }

    void test_has_cycle3 () {
        graph_type a;
        vertex_descriptor avdA;
        vertex_descriptor avdB;
        edge_descriptor aedAB;
        avdA  = add_vertex(g);
        avdB  = add_vertex(g);
        aedAB = add_edge(avdA, avdB, g).first;
        CPPUNIT_ASSERT(!has_cycle(a));
    }

    // ---------------------
    // test_topological_sort
    // ---------------------

    void test_topological_sort1 () {
        graph_type a;
        vertex_descriptor avdA;
        vertex_descriptor avdB;
        vertex_descriptor avdC;
        edge_descriptor aedAB;
        edge_descriptor aedAC;
        avdA  = add_vertex(a);
        avdB  = add_vertex(a);
        avdC  = add_vertex(a);
        aedAB = add_edge(avdA, avdB, a).first;
        aedAC = add_edge(avdA, avdC, a).first;
        std::ostringstream out;

        topological_sort(a, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "1 2 0 ");
       
    } 

    void test_topological_sort2 () {
        graph_type a;
        vertex_descriptor avdA;
        vertex_descriptor avdB;
        vertex_descriptor avdC;
        edge_descriptor aedBA;
        edge_descriptor aedCA;

        avdA  = add_vertex(a);
        avdB  = add_vertex(a);
        avdC  = add_vertex(a);
        aedBA = add_edge(avdB, avdA, a).first;
        aedCA = add_edge(avdC, avdA, a).first;
        std::ostringstream out;
    
        topological_sort(a, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "0 1 2 ");

    }

    void test_topological_sort3 () {
        graph_type cc;
        vertex_descriptor ccavdA;
        vertex_descriptor ccavdB;
        edge_descriptor   ccaedAB;
        ccavdA  = add_vertex(cc);
        ccavdB  = add_vertex(cc);
        ccaedAB = add_edge(ccavdA, ccavdB, cc).first;

        std::ostringstream out;
        topological_sort(cc, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "1 0 ");
        
    }

    // -----
    // suite
    // -----
    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge1);
    CPPUNIT_TEST(test_add_edge2);
    CPPUNIT_TEST(test_add_edge3);
    CPPUNIT_TEST(test_adjacent_vertices1);
    CPPUNIT_TEST(test_adjacent_vertices2);
    CPPUNIT_TEST(test_adjacent_vertices3);
    CPPUNIT_TEST(test_edge1);
    CPPUNIT_TEST(test_edge2);
    CPPUNIT_TEST(test_edge3);
    CPPUNIT_TEST(test_edges1);
    CPPUNIT_TEST(test_edges2);
    CPPUNIT_TEST(test_edges3);
    CPPUNIT_TEST(test_num_edges1);
    CPPUNIT_TEST(test_num_edges2);
    CPPUNIT_TEST(test_num_edges3);
    CPPUNIT_TEST(test_num_vertices1);
    CPPUNIT_TEST(test_num_vertices2);
    CPPUNIT_TEST(test_num_vertices3);
    CPPUNIT_TEST(test_source1);
    CPPUNIT_TEST(test_source2);
    CPPUNIT_TEST(test_source3);
    CPPUNIT_TEST(test_target1);
    CPPUNIT_TEST(test_target2);
    CPPUNIT_TEST(test_target3);
    CPPUNIT_TEST(test_vertex1);
    CPPUNIT_TEST(test_vertex2);
    CPPUNIT_TEST(test_vertex3);
    CPPUNIT_TEST(test_vertices1);
    CPPUNIT_TEST(test_vertices2);
    CPPUNIT_TEST(test_vertices3);
    CPPUNIT_TEST(test_has_cycle1);
    CPPUNIT_TEST(test_has_cycle2);
    CPPUNIT_TEST(test_has_cycle3);
    CPPUNIT_TEST(test_topological_sort1);
    CPPUNIT_TEST(test_topological_sort2);
    CPPUNIT_TEST(test_topological_sort3);
    CPPUNIT_TEST_SUITE_END();
};



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
    return 0;  }
