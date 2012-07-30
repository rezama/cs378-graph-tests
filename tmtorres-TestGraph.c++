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

#include "boost/graph/adjacency_list.hpp"    // adjacency_list
#include "boost/graph/topological_sort.hpp"  // topological_sort
#include "boost/graph/graph_traits.hpp"      // topological_sort

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Graph.h"

using std::cout;
using std::endl;

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
    // cycle detector
    // -----
    
    struct cycle_detector : public boost::dfs_visitor<>
    {
        cycle_detector(bool& has_cycle) 
        : _has_cycle(has_cycle) { }
        
        template <class Edge, class Garph>
        void back_edge(Edge, Garph&) {
            _has_cycle = true;
        }
    protected:
        bool& _has_cycle;
    };
    
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
    
    graph_type f;
    
    vertex_descriptor vdI;
    vertex_descriptor vdJ;
    vertex_descriptor vdK;
    vertex_descriptor vdL;
    vertex_descriptor vdM;
    vertex_descriptor vdN;
    vertex_descriptor vdO;
    vertex_descriptor vdP;
    vertex_descriptor vdQ;
    vertex_descriptor vdR;
    vertex_descriptor vdS;
    vertex_descriptor vdT;
    
    edge_descriptor edIJ;
    edge_descriptor edIK;
    edge_descriptor edJL;
    edge_descriptor edJM;
    edge_descriptor edKN;
    edge_descriptor edKO;
    edge_descriptor edLP;
    edge_descriptor edLQ;
    edge_descriptor edOR;
    edge_descriptor edOS;
    edge_descriptor edST;
    
    graph_type e;
    
    vertex_descriptor vdU;
    vertex_descriptor vdV;
    vertex_descriptor vdW;
    vertex_descriptor vdX;
    vertex_descriptor vdY;
    vertex_descriptor vdZ;
    
    edge_descriptor edUV;
    edge_descriptor edVW;
    edge_descriptor edWX;
    edge_descriptor edXY;
    edge_descriptor edYZ;
    edge_descriptor edZU;
    
    // -----
    // setUp
    // -----
    
    void setUp () 
    {
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
        
        vdI  = add_vertex(f);
        vdJ  = add_vertex(f);
        vdK  = add_vertex(f);
        vdL  = add_vertex(f);
        vdM  = add_vertex(f);
        vdN  = add_vertex(f);
        vdO  = add_vertex(f);
        vdP  = add_vertex(f);
        vdQ  = add_vertex(f);
        vdR  = add_vertex(f);
        vdS  = add_vertex(f);
        vdT  = add_vertex(f);
        
        edIJ = add_edge(vdI, vdJ, f).first;
        edIK = add_edge(vdI, vdK, f).first;
        edJL = add_edge(vdJ, vdL, f).first;
        edJM = add_edge(vdJ, vdM, f).first;
        edKN = add_edge(vdK, vdN, f).first;
        edKO = add_edge(vdK, vdO, f).first;
        edLP = add_edge(vdL, vdP, f).first;
        edLQ = add_edge(vdL, vdQ, f).first;
        edOR = add_edge(vdO, vdR, f).first;
        edOS = add_edge(vdO, vdS, f).first;
        edST = add_edge(vdS, vdT, f).first;
        
        vdU  = add_vertex(e);
        vdV  = add_vertex(e);
        vdW  = add_vertex(e);
        vdX  = add_vertex(e);
        vdY  = add_vertex(e);
        vdZ  = add_vertex(e);
        
        edUV = add_edge(vdU, vdV, e).first;
        edVW = add_edge(vdV, vdW, e).first;
        edWX = add_edge(vdW, vdX, e).first;
        edXY = add_edge(vdX, vdY, e).first;
        edYZ = add_edge(vdY, vdZ, e).first;
        edZU = add_edge(vdZ, vdU, e).first;
    }
    
    // -------------
    // test_add_edge
    // -------------
    
    void test_add_edge_1 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == false);}
    
    void test_add_edge_2 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdB, vdA, g);
        CPPUNIT_ASSERT(p.second == true);}
    
    void test_add_edge_3 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdH, g);
        CPPUNIT_ASSERT(p.second == true);}
    
    // ----------------------
    // test_adjacent_vertices
    // ----------------------
    
    void test_adjacent_vertices_1 () {
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
            CPPUNIT_ASSERT(vd == vdE);}}
    
    void test_adjacent_vertices_2 () {
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
    
    void test_adjacent_vertices_3 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdE, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b == e);}
    
    // ---------
    // test_edge
    // ---------
    
    void test_edge_1 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);}
    
    void test_edge_2 () {
        std::pair<edge_descriptor, bool> p = edge(vdB, vdA, g);
        CPPUNIT_ASSERT(p.second == false);}
    
    void test_edge_3 () {
        std::pair<edge_descriptor, bool> p = edge(vdB, vdE, g);
        CPPUNIT_ASSERT(p.first  == edBE);
        CPPUNIT_ASSERT(p.second == true);}
    
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
        std::pair<edge_iterator, edge_iterator> p = edges(f);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edIJ);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edIK);}}
    
    void test_edges_3 () {
        std::pair<edge_iterator, edge_iterator> p = edges(e);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edUV);}
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edVW);}}
    
    // --------------
    // test_num_edges
    // --------------
    
    void test_num_edges_1 () {
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}
    
    void test_num_edges_2 () {
        edges_size_type es = num_edges(f);
        CPPUNIT_ASSERT(es == 11);}
    
    void test_num_edges_3 () {
        edges_size_type es = num_edges(e);
        CPPUNIT_ASSERT(es == 6);}
    
    // -----------------
    // test_num_vertices
    // -----------------
    
    void test_num_vertices_1 () {
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);}
    
    void test_num_vertices_2 () {
        vertices_size_type vs = num_vertices(f);
        CPPUNIT_ASSERT(vs == 12);}
    
    void test_num_vertices_3 () {
        vertices_size_type vs = num_vertices(e);
        CPPUNIT_ASSERT(vs == 6);}
    
    // -----------
    // test_source
    // -----------
    
    void test_source_1 () {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);}
    
    void test_source_2 () {
        vertex_descriptor vd = source(edIK, f);
        CPPUNIT_ASSERT(vd == vdI);}
    
    void test_source_3 () {
        vertex_descriptor vd = source(edUV, e);
        CPPUNIT_ASSERT(vd == vdU);}
    
    // -----------
    // test_target
    // -----------
    
    void test_target_1 () {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);}
    
    void test_target_2 () {
        vertex_descriptor vd = target(edIK, f);
        CPPUNIT_ASSERT(vd == vdK);}
    
    void test_target_3 () {
        vertex_descriptor vd = target(edUV, e);
        CPPUNIT_ASSERT(vd == vdV);}
    
    // -----------
    // test_vertex
    // -----------
    
    void test_vertex_1 () {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);}
    
    void test_vertex_2 () {
        vertex_descriptor vd = vertex(1, g);
        CPPUNIT_ASSERT(vd == vdB);}
    
    void test_vertex_3 () {
        vertex_descriptor vd = vertex(2, g);
        CPPUNIT_ASSERT(vd == vdC);}
    
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
        std::pair<vertex_iterator, vertex_iterator> p = vertices(f);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdI);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdJ);}}
    
    void test_vertices_3 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(e);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdU);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdV);}}
    
    // --------------
    // test_has_cycle
    // --------------
    
    void test_has_cycle_1 () 
    {
        CPPUNIT_ASSERT(has_cycle(g));
    }
    
    void test_has_cycle_2 () 
    {
        CPPUNIT_ASSERT(!has_cycle(f));
    }
    
    void test_has_cycle_3 () 
    {
        CPPUNIT_ASSERT(has_cycle(e));
    }
    
    // ---------------------
    // test_topological_sort
    // ---------------------
    
    void test_topological_sort_1 () 
    {
        std::ostringstream out;
        
        try
        {
            topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
            assert(false);
        }
        catch(...)
        {
            out.str();
            assert(true);
        }
    }
    
    void test_topological_sort_2 ()
    {
        std::ostringstream out;
        
        try
        {
            topological_sort(f, std::ostream_iterator<vertex_descriptor>(out, " "));
        }
        catch(...)
        {
            assert(false);
        }
        
        CPPUNIT_ASSERT(out.str() == "7 8 3 4 1 5 9 11 10 6 2 0 ");
        
        try
        {
            add_edge(vdM, vdI, f);
            topological_sort(f, std::ostream_iterator<vertex_descriptor>(out, " "));
            assert(false);
        }
        catch(...)
        {
            assert(true);
        }
        
    }
    
    void test_topological_sort_3 ()
    {
        std::ostringstream out;
        
        try
        {
            topological_sort(e, std::ostream_iterator<vertex_descriptor>(out, " "));
            assert(false);
        }
        catch(...)
        {
            out.str();
            assert(true);
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