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

#include "boost/graph/adjacency_list.hpp" // adjacency_list

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Graph.h"
#include "boost/graph/topological_sort.hpp"// topological_sort

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

    graph_type g;  // directed, sparse, unweighted, cyclic
    graph_type g_acyclic; // directed, sparse, unweighted, acyclic
    graph_type g_connected; // directed, sparse, unweighted, connected, cyclic

    vertex_descriptor vdA;
    vertex_descriptor vdB;
    vertex_descriptor vdC;
    vertex_descriptor vdD;
    vertex_descriptor vdE;
    vertex_descriptor vdF;
    vertex_descriptor vdG;
    vertex_descriptor vdH;

    vertex_descriptor vdA_acyclic;
    vertex_descriptor vdB_acyclic;
    vertex_descriptor vdC_acyclic;
    vertex_descriptor vdD_acyclic;
    vertex_descriptor vdE_acyclic;
    vertex_descriptor vdF_acyclic;     

    vertex_descriptor vdA_connected;
    vertex_descriptor vdB_connected;
    vertex_descriptor vdC_connected;

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

    edge_descriptor edAB_acyclic;
    edge_descriptor edBE_acyclic;
    edge_descriptor edAD_acyclic;
    edge_descriptor edED_acyclic;
    edge_descriptor edCE_acyclic;
    edge_descriptor edCF_acyclic;
    edge_descriptor edFA_acyclic;
    
    edge_descriptor edAB_connected;
    edge_descriptor edBC_connected;
    edge_descriptor edCA_connected;

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

	    vdA_acyclic = add_vertex(g_acyclic);
	    vdB_acyclic = add_vertex(g_acyclic);
	    vdC_acyclic = add_vertex(g_acyclic);
	    vdD_acyclic = add_vertex(g_acyclic);
	    vdE_acyclic = add_vertex(g_acyclic);
	    vdF_acyclic = add_vertex(g_acyclic);
	    edAB_acyclic = add_edge(vdA_acyclic, vdB_acyclic, g_acyclic).first;
	    edAD_acyclic = add_edge(vdA_acyclic, vdD_acyclic, g_acyclic).first;
	    edBE_acyclic = add_edge(vdB_acyclic, vdE_acyclic, g_acyclic).first;
	    edED_acyclic = add_edge(vdE_acyclic, vdD_acyclic, g_acyclic).first;
	    edCE_acyclic = add_edge(vdC_acyclic, vdE_acyclic, g_acyclic).first;
	    edCF_acyclic = add_edge(vdC_acyclic, vdF_acyclic, g_acyclic).first;
	    
	    edFA_acyclic = add_edge(vdF_acyclic, vdA_acyclic, g_acyclic).first;
	    
	    vdA_connected = add_vertex(g_connected);
	    vdB_connected = add_vertex(g_connected);
	    vdC_connected = add_vertex(g_connected);
	    edAB_connected = add_edge(vdA_connected, vdB_connected, g_connected).first;
	    edBC_connected = add_edge(vdB_connected, vdC_connected, g_connected).first;
	    edCA_connected = add_edge(vdC_connected, vdA_connected, g_connected).first;}

    // -------------
    // test_add_edge
    // -------------

    void test_add_edge_1 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == false);}

	void test_add_edge_2 () {
	    std::pair<edge_descriptor, bool> p = add_edge(vdB, vdG, g);
	    std::pair<edge_descriptor, bool> e = edge(vdB, vdG, g);
	    CPPUNIT_ASSERT(e.first == p.first);
	    CPPUNIT_ASSERT(p.second == true);}

    void test_add_edge_acyclic_1 () {
	    std::pair<edge_descriptor, bool> p = add_edge(vdA_acyclic, vdB_acyclic, g_acyclic);
	    CPPUNIT_ASSERT(p.first == edAB_acyclic);
	    CPPUNIT_ASSERT(p.second == false);}
	
	void test_add_edge_acyclic_2 () {
	    std::pair<edge_descriptor, bool> p = add_edge(vdA_acyclic, vdE_acyclic, g_acyclic);
	    std::pair<edge_descriptor, bool> e = edge(vdA_acyclic, vdE_acyclic, g_acyclic);
	    CPPUNIT_ASSERT(e.first == p.first);
	    CPPUNIT_ASSERT(p.second == true);}
	    
    void test_add_edge_connected_1 () {
	    std::pair<edge_descriptor, bool> p = add_edge(vdA_connected, vdB_connected, g_connected);
	    CPPUNIT_ASSERT(p.first == edAB_connected);
	    CPPUNIT_ASSERT(p.second == false);}
	
	void test_add_edge_connected_2 () {
	    std::pair<edge_descriptor, bool> p = add_edge(vdB_connected, vdA_connected, g_connected);
	    std::pair<edge_descriptor, bool> e = edge(vdB_connected, vdA_connected, g_connected);
	    CPPUNIT_ASSERT(e.first == p.first);
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
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdC);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdE);}}
	        
    void test_adjacent_vertices_2 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdH, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b == e);}
        
        
    void test_adjacent_vertices_acyclic_1 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdC_acyclic, g_acyclic);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdE_acyclic);}
        ++b;
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdF_acyclic);}}
	        
    void test_adjacent_vertices_acyclic_2 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdD_acyclic, g_acyclic);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b == e);}
        
    void test_adjacent_vertices_connected_1 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA_connected, g_connected);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB_acyclic);}}

	
    // ---------
    // test_edge
    // ---------

    void test_edge_1 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);}
        
    void test_edge_2 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdD, g);
        CPPUNIT_ASSERT(p.second == false);}
        
        
    void test_edge_acyclic_1 () {
        std::pair<edge_descriptor, bool> p = edge(vdA_acyclic, vdB_acyclic, g_acyclic);
        CPPUNIT_ASSERT(p.first  == edAB_acyclic);
        CPPUNIT_ASSERT(p.second == true);}
        
    void test_edge_acyclic_2 () {
        std::pair<edge_descriptor, bool> p = edge(vdB_acyclic, vdA_acyclic, g_acyclic);
        CPPUNIT_ASSERT(p.second == false);}
        
    void test_edge_connected_1 () {
        std::pair<edge_descriptor, bool> p = edge(vdA_connected, vdB_connected, g_connected);
        CPPUNIT_ASSERT(p.first  == edAB_connected);
        CPPUNIT_ASSERT(p.second == true);}
        
    void test_edge_connected_2 () {
        std::pair<edge_descriptor, bool> p = edge(vdB_connected, vdA_connected, g_connected);
        CPPUNIT_ASSERT(p.second == false);}

    // ----------
    // test_edges
    // ----------

    void test_edges () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAB);}
        ++b;
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAC);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edAE);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edBD);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edBE);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edCD);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edDE);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edDF);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edFD);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edFH);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edGH);}
	    }
	    
	void test_edges_acyclic () {
        std::pair<edge_iterator, edge_iterator> p = edges(g_acyclic);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAB_acyclic);}
        ++b;
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAD_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edBE_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edCE_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edCF_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edED_acyclic);}
	   	++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edFA_acyclic);}
	}
	
	void test_edges_connected () {
        std::pair<edge_iterator, edge_iterator> p = edges(g_connected);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAB_connected);}
        ++b;
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edBC_connected);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        edge_descriptor ed = *b;
	        CPPUNIT_ASSERT(ed == edCA_connected);}
	}

    // --------------
    // test_num_edges
    // --------------

    void test_num_edges_1 () {
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}
        
    void test_num_edges_2 () {
        add_edge(vdB, vdG, g);
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 12);}
        
    void test_num_edges_acyclic_1 () {
        edges_size_type es = num_edges(g_acyclic);
        CPPUNIT_ASSERT(es == 7);}
        
    void test_num_edges_acyclic_2 () {
        add_edge(vdA_acyclic, vdE_acyclic, g_acyclic);
        edges_size_type es = num_edges(g_acyclic);
        CPPUNIT_ASSERT(es == 8);}
        
    void test_num_edges_connected_1 () {
        edges_size_type es = num_edges(g_connected);
        CPPUNIT_ASSERT(es == 3);}
        
    void test_num_edges_connected_2 () {
        add_edge(vdA_connected, vdC_connected, g_connected);
        edges_size_type es = num_edges(g_connected);
        CPPUNIT_ASSERT(es == 4);}

    // -----------------
    // test_num_vertices
    // -----------------

    void test_num_vertices_1 () {
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);}
        
    void test_num_vertices_2 () {
        add_vertex(g);
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 9);}
        
    void test_num_vertices_acyclic_1 () {
        vertices_size_type vs = num_vertices(g_acyclic);
        CPPUNIT_ASSERT(vs == 6);}
        
    void test_num_vertices_acyclic_2 () {
        add_vertex(g_acyclic);
        vertices_size_type vs = num_vertices(g_acyclic);
        CPPUNIT_ASSERT(vs == 7);}
        
    void test_num_vertices_connected_1 () {
        vertices_size_type vs = num_vertices(g_connected);
        CPPUNIT_ASSERT(vs == 3);}
        
    void test_num_vertices_connected_2 () {
        add_vertex(g_connected);
        vertices_size_type vs = num_vertices(g_connected);
        CPPUNIT_ASSERT(vs == 4);}

    // -----------
    // test_source
    // -----------

    void test_source () {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);}
    
    void test_source_acyclic () {
        vertex_descriptor vd = source(edAB_acyclic, g_acyclic);
        CPPUNIT_ASSERT(vd == vdA_acyclic);}
     
    void test_source_connected () {
        vertex_descriptor vd = source(edAB_connected, g_connected);
        CPPUNIT_ASSERT(vd == vdA_connected);}

    // -----------
    // test_target
    // -----------

    void test_target () {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);}
        
    void test_target_acyclic () {
        vertex_descriptor vd = target(edAB_acyclic, g_acyclic);
        CPPUNIT_ASSERT(vd == vdB_acyclic);}
        
    void test_target_connected () {
        vertex_descriptor vd = target(edAB_connected, g_connected);
        CPPUNIT_ASSERT(vd == vdB_connected);}

    // -----------
    // test_vertex
    // -----------

    void test_vertex () {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);
	    vd = vertex(1, g);
	    CPPUNIT_ASSERT(vd == vdB);
	    vd = vertex(2, g);
	    CPPUNIT_ASSERT(vd == vdC);
	    vd = vertex(3, g);
	    CPPUNIT_ASSERT(vd == vdD);
	    vd = vertex(4, g);
	    CPPUNIT_ASSERT(vd == vdE);
	    vd = vertex(5, g);
	    CPPUNIT_ASSERT(vd == vdF);
	    vd = vertex(6, g);
	    CPPUNIT_ASSERT(vd == vdG);
	    vd = vertex(7, g);
	    CPPUNIT_ASSERT(vd == vdH);}
	    
	void test_vertex_acyclic () {
        vertex_descriptor vd = vertex(0, g_acyclic);
        CPPUNIT_ASSERT(vd == vdA_acyclic);
	    vd = vertex(1, g_acyclic);
	    CPPUNIT_ASSERT(vd == vdB_acyclic);
	    vd = vertex(2, g_acyclic);
	    CPPUNIT_ASSERT(vd == vdC_acyclic);
	    vd = vertex(3, g_acyclic);
	    CPPUNIT_ASSERT(vd == vdD_acyclic);
	    vd = vertex(4, g_acyclic);
	    CPPUNIT_ASSERT(vd == vdE_acyclic);
	    vd = vertex(5, g_acyclic);
	    CPPUNIT_ASSERT(vd == vdF_acyclic);}
	    
	void test_vertex_connected () {
        vertex_descriptor vd = vertex(0, g_connected);
        CPPUNIT_ASSERT(vd == vdA_connected);
	    vd = vertex(1, g_connected);
	    CPPUNIT_ASSERT(vd == vdB_connected);
	    vd = vertex(2, g_connected);
	    CPPUNIT_ASSERT(vd == vdC_connected);}

    // -------------
    // test_vertices
    // -------------

    void test_vertices () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdA);}
        ++b;
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdC);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdD);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdE);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdF);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdG);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdH);}}
	        
    void test_vertices_acyclic () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g_acyclic);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdA_acyclic);}
        ++b;
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdC_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdD_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdE_acyclic);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdF_acyclic);}}
	        
    void test_vertices_connected () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g_connected);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdA_connected);}
        ++b;
	    CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB_connected);}
	    ++b;
	    CPPUNIT_ASSERT(b != e);
	    if (b != e) {
	        vertex_descriptor vd = *b;
	        CPPUNIT_ASSERT(vd == vdC_connected);}}

    // --------------
    // test_has_cycle
    // --------------

    void test_has_cycle () {
        CPPUNIT_ASSERT(has_cycle(g));}
      
    void test_has_cycle_acyclic () {
        CPPUNIT_ASSERT(!has_cycle(g_acyclic));}
        
    void test_has_cycle_connected () {
        CPPUNIT_ASSERT(has_cycle(g_connected));}
        
    void test_has_cycle_one_vertex () {
        graph_type g_one_vertex;
        add_vertex(g_one_vertex);
        CPPUNIT_ASSERT(!has_cycle(g_one_vertex));
    }

    // ---------------------
    // test_topological_sort
    // ---------------------

    void test_topological_sort () {
        std::ostringstream out;
	try {
        topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(false);
	} catch(...){}}
    
    void test_topological_sort_acyclic () {
        std::ostringstream out;
        topological_sort(g_acyclic, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "3 4 1 0 5 2 ");}
        
    void test_topological_sort_connected () {
        std::ostringstream out;
        try {
	topological_sort(g_connected, std::ostream_iterator<vertex_descriptor>(out, " "));
	CPPUNIT_ASSERT(false);
        } catch(...){}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge_1);
    CPPUNIT_TEST(test_add_edge_2);
    CPPUNIT_TEST(test_add_edge_acyclic_1);
    CPPUNIT_TEST(test_add_edge_acyclic_2);
    CPPUNIT_TEST(test_add_edge_connected_1);
    CPPUNIT_TEST(test_add_edge_connected_2);
    CPPUNIT_TEST(test_adjacent_vertices_1);
    CPPUNIT_TEST(test_adjacent_vertices_2);
    CPPUNIT_TEST(test_adjacent_vertices_acyclic_1);
    CPPUNIT_TEST(test_adjacent_vertices_acyclic_2);
    CPPUNIT_TEST(test_adjacent_vertices_connected_1);
    CPPUNIT_TEST(test_edge_1);
    CPPUNIT_TEST(test_edge_2);
    CPPUNIT_TEST(test_edge_acyclic_1);
    CPPUNIT_TEST(test_edge_acyclic_2);
    CPPUNIT_TEST(test_edge_connected_1);
    CPPUNIT_TEST(test_edge_connected_2);
    CPPUNIT_TEST(test_edges);
    CPPUNIT_TEST(test_edges_acyclic);
    CPPUNIT_TEST(test_edges_connected);
    CPPUNIT_TEST(test_num_edges_1);
    CPPUNIT_TEST(test_num_edges_2);
    CPPUNIT_TEST(test_num_edges_acyclic_1);
    CPPUNIT_TEST(test_num_edges_acyclic_2);
    CPPUNIT_TEST(test_num_edges_connected_1);
    CPPUNIT_TEST(test_num_edges_connected_2);
    CPPUNIT_TEST(test_num_vertices_1);
    CPPUNIT_TEST(test_num_vertices_2);
    CPPUNIT_TEST(test_num_vertices_acyclic_1);
    CPPUNIT_TEST(test_num_vertices_acyclic_2);
    CPPUNIT_TEST(test_num_vertices_connected_1);
    CPPUNIT_TEST(test_num_vertices_connected_2);
    CPPUNIT_TEST(test_source);
    CPPUNIT_TEST(test_source_acyclic);
    CPPUNIT_TEST(test_source_connected);
    CPPUNIT_TEST(test_target);
    CPPUNIT_TEST(test_target_acyclic);
    CPPUNIT_TEST(test_target_connected);
    CPPUNIT_TEST(test_vertex);
    CPPUNIT_TEST(test_vertex_acyclic);
    CPPUNIT_TEST(test_vertex_connected);
    CPPUNIT_TEST(test_vertices);
    CPPUNIT_TEST(test_vertices_acyclic);
    CPPUNIT_TEST(test_vertices_connected);
    CPPUNIT_TEST(test_has_cycle);
    CPPUNIT_TEST(test_has_cycle_one_vertex);
    CPPUNIT_TEST(test_has_cycle_acyclic);
    CPPUNIT_TEST(test_has_cycle_connected);
    CPPUNIT_TEST(test_topological_sort);
    CPPUNIT_TEST(test_topological_sort_acyclic);
    CPPUNIT_TEST(test_topological_sort_connected);
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
