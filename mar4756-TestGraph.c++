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
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <stdexcept>//std::invalid_argument
#include <string>   //string

#include "boost/graph/adjacency_list.hpp" // adjacency_list

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

    vertex_descriptor vdAA;
    vertex_descriptor vdBB;

    edge_descriptor edAABB;
    edge_descriptor edBBAA;    

    graph_type i;

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
        edGH = add_edge(vdG, vdH, g).first;

        vdAA  = add_vertex(h);
        vdBB  = add_vertex(h);
        edAABB = add_edge(vdAA, vdBB, h).first;
        //edBBAA = add_edge(vdBB, vdAA, h).first;
    }

    // -------------
    // test_add_edge
    // -------------

    void test_add_edge_1 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == false);}
    
    void test_add_edge_2 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdF, vdD, g);
        CPPUNIT_ASSERT(p.first  == edFD);
        CPPUNIT_ASSERT(p.second == false);}

    void test_add_edge_3 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdH, g);
        CPPUNIT_ASSERT(p.second == true);} 

    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    void test_adjacent_vertices_1 () {
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
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdC, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdD);
        }
}

    void test_adjacent_vertices_3 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdB, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdD);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdE);}       
}


    // ---------
    // test_edge
    // ---------

    void test_edge_1 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);}

    void test_edge_2 () {
        std::pair<edge_descriptor, bool> p = edge(vdF, vdH, g);
        CPPUNIT_ASSERT(p.first  == edFH);
        CPPUNIT_ASSERT(p.second == true);}
 
    void test_edge_3 () {
        std::pair<edge_descriptor, bool> p = edge(vdG, vdA, g);
        CPPUNIT_ASSERT(p.second == false);}

    // ----------
    // test_edges
    // ----------

    void test_edges_1 () {
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

    void test_edges_2 () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAC);}
         ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAE);}}

    void test_edges_3 () {
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
            CPPUNIT_ASSERT(ed == edAC);}
    }
    // --------------
    // test_num_edges
    // --------------

    void test_num_edges_1 () {
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}

    void test_num_edges_2 () {
        edges_size_type es = num_edges(h);
        CPPUNIT_ASSERT(es == 1);}

    void test_num_edges_3 () {
        edges_size_type es = num_edges(i);
        CPPUNIT_ASSERT(es == 0);}

    // -----------------
    // test_num_vertices
    // -----------------

    void test_num_vertices_1 () {
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);}

    void test_num_vertices_2 () {
        vertices_size_type vs = num_vertices(h);
        CPPUNIT_ASSERT(vs == 2);}

    void test_num_vertices_3 () {
        vertices_size_type vs = num_vertices(i);
        CPPUNIT_ASSERT(vs == 0);}

    // -----------
    // test_source
    // -----------

    void test_source_1 () {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_source_2 () {
        vertex_descriptor vd = source(edGH, g);
        CPPUNIT_ASSERT(vd == vdG);}

    void test_source_3 () {
        vertex_descriptor vd = source(edAABB, h);
        CPPUNIT_ASSERT(vd == vdAA);}

    // -----------
    // test_target
    // -----------

    void test_target_1 () {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);}

    void test_target_2 () {
        vertex_descriptor vd = target(edGH, g);
        CPPUNIT_ASSERT(vd == vdH);}

    void test_target_3 () {
        vertex_descriptor vd = target(edAABB, h);
        CPPUNIT_ASSERT(vd == vdBB);}

    // -----------
    // test_vertex
    // -----------

    void test_vertex_1 () {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_vertex_2 () {
        vertex_descriptor vd = vertex(7, g);
        CPPUNIT_ASSERT(vd == vdH);}

    void test_vertex_3 () {
        vertex_descriptor vd = vertex(1, h);
        CPPUNIT_ASSERT(vd == vdBB);}

    // -------------
    // test_vertices
    // -------------

    void test_vertices_1 () {
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
            CPPUNIT_ASSERT(vd == vdB);}}

    void test_vertices_2 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        b+=3;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdD);}}

    void test_vertices_3 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        b+=7;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdH);}}


    // --------------
    // test_has_cycle
    // --------------

    void test_has_cycle_1 () {
        CPPUNIT_ASSERT(has_cycle(g)== true);}

    void test_has_cycle_2 () {
        CPPUNIT_ASSERT(has_cycle(h)==false);}

    void test_has_cycle_3 () {
        CPPUNIT_ASSERT(has_cycle(i)==false);}

    // ---------------------
    // test_topological_sort
    // ---------------------

    void test_topological_sort_1 () {
        graph_type test;
        vertex_descriptor vd1 = add_vertex(test);
        vertex_descriptor vd2 = add_vertex(test);
        vertex_descriptor vd3 = add_vertex(test);
        vertex_descriptor vd4 = add_vertex(test);
        vertex_descriptor vd5 = add_vertex(test);
        vertex_descriptor vd6 = add_vertex(test);
        vertex_descriptor vd7 = add_vertex(test);
        vertex_descriptor vd8 = add_vertex(test);

        add_edge(vd1, vd2, test).first;
        add_edge(vd1, vd3, test).first;
        add_edge(vd1, vd5, test).first;
        add_edge(vd2, vd4, test).first;
        add_edge(vd2, vd5, test).first;
        add_edge(vd3, vd4, test).first;
        add_edge(vd4, vd5, test).first;
        add_edge(vd4, vd6, test).first;
        add_edge(vd6, vd7, test).first;
        add_edge(vd6, vd8, test).first;
        add_edge(vd7, vd8, test).first;
        add_edge(vd8, vd5, test).first;


        std::ostringstream out;
        try{
            topological_sort(test, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(out.str() == "0 1 2 3 5 6 7 4 ");}
        catch(std::invalid_argument e){
            CPPUNIT_ASSERT(false);}
    }

    void test_topological_sort_2 () {
        std::ostringstream out;
        try{
            topological_sort(h, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(out.str() == "0 1 ");}
        catch(boost::not_a_dag& e){
            CPPUNIT_ASSERT(false);}
    }

    void test_topological_sort_3 () {
        std::ostringstream out;
        try{
            topological_sort(i, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(out.str() == "");}
        catch(boost::not_a_dag& e){
            CPPUNIT_ASSERT(false);}
    }

    void test_topological_sort_4 () {
        std::ostringstream out;
        try{
            topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(false);}
        catch(boost::not_a_dag& e){
            CPPUNIT_ASSERT(true);
        }
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge_1);
    CPPUNIT_TEST(test_add_edge_2);
    CPPUNIT_TEST(test_add_edge_3);
    CPPUNIT_TEST(test_adjacent_vertices_1);
    CPPUNIT_TEST(test_adjacent_vertices_2);
    CPPUNIT_TEST(test_adjacent_vertices_3);    
    CPPUNIT_TEST(test_edge_1);
    CPPUNIT_TEST(test_edge_2);
    CPPUNIT_TEST(test_edge_3);
    CPPUNIT_TEST(test_edges_1);
    CPPUNIT_TEST(test_edges_2);
    CPPUNIT_TEST(test_edges_3);
    CPPUNIT_TEST(test_num_edges_1);
    CPPUNIT_TEST(test_num_edges_2);
    CPPUNIT_TEST(test_num_edges_3);
    CPPUNIT_TEST(test_num_vertices_1);
    CPPUNIT_TEST(test_num_vertices_2);
    CPPUNIT_TEST(test_num_vertices_3);
    CPPUNIT_TEST(test_source_1);
    CPPUNIT_TEST(test_source_2);
    CPPUNIT_TEST(test_source_3);
    CPPUNIT_TEST(test_target_1);
    CPPUNIT_TEST(test_target_2);
    CPPUNIT_TEST(test_target_3);
    CPPUNIT_TEST(test_vertex_1);
    CPPUNIT_TEST(test_vertex_2);
    CPPUNIT_TEST(test_vertex_3);
    CPPUNIT_TEST(test_vertices_1);
    CPPUNIT_TEST(test_vertices_2);
    CPPUNIT_TEST(test_vertices_3);

    CPPUNIT_TEST(test_has_cycle_1);
    CPPUNIT_TEST(test_has_cycle_2);
    CPPUNIT_TEST(test_has_cycle_3);
    
    CPPUNIT_TEST(test_topological_sort_1);
    CPPUNIT_TEST(test_topological_sort_2);
    CPPUNIT_TEST(test_topological_sort_3);
    CPPUNIT_TEST(test_topological_sort_4);    

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
