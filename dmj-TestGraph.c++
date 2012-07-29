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
#include "boost/graph/topological_sort.hpp" // topological_sort

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Graph.h"

using namespace std;


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

	/* Even-more-abbreviated typedefs. */
	typedef vertex_descriptor		 vd;
	typedef edge_descriptor			 ed;
	typedef vertex_iterator   vert_iter;
	typedef edge_iterator	  edge_iter;
	typedef adjacency_iterator adj_iter;

    // -------------
    // test_add_edge
    // -------------

    void test_add_edge_1() {
		// Add an edge to an empty graph.
		graph_type g;
        pair<ed, bool> p = add_edge(0, 1, g);
        CPPUNIT_ASSERT(p.second == true);
		CPPUNIT_ASSERT(num_vertices(g) == 2);
		CPPUNIT_ASSERT(num_edges(g) == 1);
	}

    void test_add_edge_2() {
		graph_type g;
		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
        pair<ed, bool> p1 = add_edge(vdA, vdB, g);
		pair<ed, bool> p2 = edge(vdA, vdB, g);

        CPPUNIT_ASSERT(p1.first == p2.first);
        CPPUNIT_ASSERT(p1.second == true);
        CPPUNIT_ASSERT(p2.second == true);
		CPPUNIT_ASSERT(num_vertices(g) == 2);
		CPPUNIT_ASSERT(num_edges(g) == 1);
	}

    void test_add_edge_3() {
		graph_type g;
		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
        pair<ed, bool> p1 = add_edge(vdA, vdB, g);
		pair<ed, bool> p2 = add_edge(vdA, vdB, g);

        CPPUNIT_ASSERT(p1.first == p2.first);
        CPPUNIT_ASSERT(p1.second == true);
        CPPUNIT_ASSERT(p2.second == false);
		CPPUNIT_ASSERT(num_vertices(g) == 2);
		CPPUNIT_ASSERT(num_edges(g) == 1);
	}

    void test_add_edge_4() {
		graph_type g;
		vd vdA = add_vertex(g);
        pair<ed, bool> p1 = add_edge(vdA, vdA, g);

        CPPUNIT_ASSERT(p1.second == true);
		CPPUNIT_ASSERT(num_vertices(g) == 1);
		CPPUNIT_ASSERT(num_edges(g) == 1);
	}

    void test_add_edge_5() {
		// Add an edge from a vertex to the same vertex to an empty graph.
		graph_type g;
        pair<ed, bool> p = add_edge(0, 0, g);
        CPPUNIT_ASSERT(p.second == true);
		CPPUNIT_ASSERT(num_vertices(g) == 1);
		CPPUNIT_ASSERT(num_edges(g) == 1);
	}

    void test_add_edge_6() {
		// Add an edge from a vertex to the same vertex to an empty graph.
		graph_type g;
        pair<ed, bool> p = add_edge(0, 7, g);
        CPPUNIT_ASSERT(p.second == true);
		CPPUNIT_ASSERT(num_vertices(g) == 8);
		CPPUNIT_ASSERT(num_edges(g) == 1);
	}

    // ---------------
    // test_add_vertex
    // ---------------

    void test_add_vertex_1() {
		graph_type g;
        add_vertex(g);
		CPPUNIT_ASSERT(num_vertices(g) == 1);
	}

    void test_add_vertex_2() {
		graph_type g;
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);

		CPPUNIT_ASSERT(num_vertices(g) == 3);
	}

    void test_add_vertex_3() {
		graph_type g;

		for (int i = 0; i < 99; ++i)
			add_vertex(g);

		CPPUNIT_ASSERT(num_vertices(g) == 99);
	}

    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    void test_adjacent_vertices_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBD = add_edge(vdB, vdD, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edDF = add_edge(vdD, vdF, g).first;
		ed edFD = add_edge(vdF, vdD, g).first;
		ed edFH = add_edge(vdF, vdH, g).first;

        pair<adj_iter, adj_iter> p = adjacent_vertices(vdA, g);
        adj_iter b = p.first;
        adj_iter e = p.second;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == vdB);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == vdC);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == vdE);
		++b;
	
		CPPUNIT_ASSERT(b == e);
	}

    void test_adjacent_vertices_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBD = add_edge(vdB, vdD, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edDF = add_edge(vdD, vdF, g).first;
		ed edFD = add_edge(vdF, vdD, g).first;
		ed edFH = add_edge(vdF, vdH, g).first;

        pair<adj_iter, adj_iter> p = adjacent_vertices(vdE, g);
        adj_iter b = p.first;
        adj_iter e = p.second;

        CPPUNIT_ASSERT(b == e);
	}

    void test_adjacent_vertices_3() {
		graph_type g;
		vd vdA = add_vertex(g);
        pair<adj_iter, adj_iter> p = adjacent_vertices(vdA, g);
        adj_iter b = p.first;
        adj_iter e = p.second;

        CPPUNIT_ASSERT(b == e);
	}

    void test_adjacent_vertices_4() {
		// Verify that the adjacency_iterator remains valid
		// when an edge is inserted midway through iterator.
		// The edge is inserted after the current iter position,
		// so the iterator should encounter the new edge.
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBD = add_edge(vdB, vdD, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edDF = add_edge(vdD, vdF, g).first;
		ed edFD = add_edge(vdF, vdD, g).first;
		ed edFH = add_edge(vdF, vdH, g).first;

        pair<adj_iter, adj_iter> p = adjacent_vertices(vdA, g);
        adj_iter b = p.first;
        adj_iter e = p.second;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == vdB);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == vdC);

		ed edAD = add_edge(vdA, vdD, g).first;

        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == vdD);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == vdE);
        ++b;

        CPPUNIT_ASSERT(b == e);
	}

    // ---------
    // test_edge
    // ---------

    void test_edge_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;

        std::pair<ed, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdB, vdC, g);
        CPPUNIT_ASSERT(p.first  == edBC);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdA, vdC, g);
        CPPUNIT_ASSERT(p.first  == edAC);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdB, vdA, g);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdC, vdB, g);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdC, vdA, g);
        CPPUNIT_ASSERT(p.second == false);
	}

    void test_edge_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);

        std::pair<ed, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdB, vdC, g);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdA, vdC, g);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdB, vdA, g);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdC, vdB, g);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdC, vdA, g);
        CPPUNIT_ASSERT(p.second == false);
	}

    void test_edge_3() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;
		ed edCA = add_edge(vdC, vdA, g).first;

        std::pair<ed, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdB, vdC, g);
        CPPUNIT_ASSERT(p.first  == edBC);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdA, vdC, g);
        CPPUNIT_ASSERT(p.first  == edAC);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdB, vdA, g);
        CPPUNIT_ASSERT(p.first  == edBA);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdC, vdB, g);
        CPPUNIT_ASSERT(p.first  == edCB);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdC, vdA, g);
        CPPUNIT_ASSERT(p.first  == edCA);
        CPPUNIT_ASSERT(p.second == true);
	}

    // ----------
    // test_edges
    // ----------

    void test_edges_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;

        pair<edge_iter, edge_iter> p = edges(g);
        edge_iter b = p.first;
        edge_iter e = p.second;

		ed beg_edge = *b;  // Verify assignment works.
		CPPUNIT_ASSERT(beg_edge == *b);

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edAB);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edAC);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edBC);

        CPPUNIT_ASSERT(*b++ == edBC); // Verify post-increment works.
        CPPUNIT_ASSERT(b == e);
	}

    void test_edges_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edCA = add_edge(vdC, vdA, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;

        pair<edge_iter, edge_iter> p = edges(g);
        edge_iter b = p.first;
        edge_iter e = p.second;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edAB);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edAC);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edBA);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edBC);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edCA);
        ++b;

        CPPUNIT_ASSERT(b != e);
		CPPUNIT_ASSERT(*b == edCB);
        ++b;

        CPPUNIT_ASSERT(b == e);
	}

	void test_edges_3() {
		graph_type g;

        pair<edge_iter, edge_iter> p = edges(g);
        edge_iter b = p.first;
        edge_iter e = p.second;

		CPPUNIT_ASSERT(b == e);
	}

    // --------------
    // test_num_edges
    // --------------

    void test_num_edges_1() {
		graph_type g;

        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 0);
	}

    void test_num_edges_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		vd vdI = add_vertex(g);

		ed edAI = add_edge(vdA, vdI, g).first;
		ed edIH = add_edge(vdI, vdH, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;
		ed edGF = add_edge(vdG, vdF, g).first;
		ed edFE = add_edge(vdF, vdE, g).first;
		ed edED = add_edge(vdE, vdD, g).first;
		ed edDC = add_edge(vdD, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;

		ed edAH = add_edge(vdA, vdH, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBI = add_edge(vdB, vdI, g).first;
		ed edGB = add_edge(vdG, vdB, g).first;
		ed edEG = add_edge(vdE, vdG, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;

        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 16);
	}

    void test_num_edges_3() {
		// Test whether the number of edges is increased when adding
		// an edge using anonymous, heretofore nonexistent pairs of
		// vertices.
		graph_type g;

        pair<ed, bool> p = add_edge(0, 1, g);
        CPPUNIT_ASSERT(p.second == true);

        p = add_edge(0, 2, g);
        CPPUNIT_ASSERT(p.second == true);

        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 2);
	}

    // -----------------
    // test_num_vertices
    // -----------------

    void test_num_vertices_1() {
		graph_type g;

		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);
		add_vertex(g);

        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);
	}

    void test_num_vertices_2() {
		graph_type g;

        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 0);
	}

    void test_num_vertices_3() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		vd vdI = add_vertex(g);

		ed edAI = add_edge(vdA, vdI, g).first;
		ed edIH = add_edge(vdI, vdH, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;
		ed edGF = add_edge(vdG, vdF, g).first;
		ed edFE = add_edge(vdF, vdE, g).first;
		ed edED = add_edge(vdE, vdD, g).first;
		ed edDC = add_edge(vdD, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;

		ed edAH = add_edge(vdA, vdH, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBI = add_edge(vdB, vdI, g).first;
		ed edGB = add_edge(vdG, vdB, g).first;
		ed edEG = add_edge(vdE, vdG, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;

        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 9);
	}

    // -----------
    // test_source
    // -----------

    void test_source_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBD = add_edge(vdB, vdD, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edDF = add_edge(vdD, vdF, g).first;
		ed edFD = add_edge(vdF, vdD, g).first;
		ed edFH = add_edge(vdF, vdH, g).first;

        CPPUNIT_ASSERT(source(edAB, g) == vdA);
        CPPUNIT_ASSERT(source(edAC, g) == vdA);
        CPPUNIT_ASSERT(source(edAE, g) == vdA);
        CPPUNIT_ASSERT(source(edBD, g) == vdB);
        CPPUNIT_ASSERT(source(edBE, g) == vdB);
        CPPUNIT_ASSERT(source(edCD, g) == vdC);
        CPPUNIT_ASSERT(source(edDE, g) == vdD);
        CPPUNIT_ASSERT(source(edDF, g) == vdD);
        CPPUNIT_ASSERT(source(edFD, g) == vdF);
        CPPUNIT_ASSERT(source(edFH, g) == vdF);
	}

    void test_source_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edCA = add_edge(vdC, vdA, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;

        CPPUNIT_ASSERT(source(edAB, g) == vdA);
        CPPUNIT_ASSERT(source(edBA, g) == vdB);
        CPPUNIT_ASSERT(source(edAC, g) == vdA);
        CPPUNIT_ASSERT(source(edCA, g) == vdC);
        CPPUNIT_ASSERT(source(edBC, g) == vdB);
        CPPUNIT_ASSERT(source(edCB, g) == vdC);
	}

    void test_source_3() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAD = add_edge(vdA, vdD, g).first;
		ed edBG = add_edge(vdB, vdG, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edHF = add_edge(vdH, vdF, g).first;
		ed edFG = add_edge(vdF, vdG, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;

        CPPUNIT_ASSERT(source(edAB, g) == vdA);
        CPPUNIT_ASSERT(source(edAD, g) == vdA);
        CPPUNIT_ASSERT(source(edBG, g) == vdB);
        CPPUNIT_ASSERT(source(edCD, g) == vdC);
        CPPUNIT_ASSERT(source(edDE, g) == vdD);
        CPPUNIT_ASSERT(source(edHF, g) == vdH);
        CPPUNIT_ASSERT(source(edFG, g) == vdF);
        CPPUNIT_ASSERT(source(edHG, g) == vdH);
	}

    // -----------
    // test_target
    // -----------

    void test_target_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBD = add_edge(vdB, vdD, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edDF = add_edge(vdD, vdF, g).first;
		ed edFD = add_edge(vdF, vdD, g).first;
		ed edFH = add_edge(vdF, vdH, g).first;

        CPPUNIT_ASSERT(target(edAB, g) == vdB);
        CPPUNIT_ASSERT(target(edAC, g) == vdC);
        CPPUNIT_ASSERT(target(edAE, g) == vdE);
        CPPUNIT_ASSERT(target(edBD, g) == vdD);
        CPPUNIT_ASSERT(target(edBE, g) == vdE);
        CPPUNIT_ASSERT(target(edCD, g) == vdD);
        CPPUNIT_ASSERT(target(edDE, g) == vdE);
        CPPUNIT_ASSERT(target(edDF, g) == vdF);
        CPPUNIT_ASSERT(target(edFD, g) == vdD);
        CPPUNIT_ASSERT(target(edFH, g) == vdH);
	}

    void test_target_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edCA = add_edge(vdC, vdA, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;

        CPPUNIT_ASSERT(target(edAB, g) == vdB);
        CPPUNIT_ASSERT(target(edBA, g) == vdA);
        CPPUNIT_ASSERT(target(edAC, g) == vdC);
        CPPUNIT_ASSERT(target(edCA, g) == vdA);
        CPPUNIT_ASSERT(target(edBC, g) == vdC);
        CPPUNIT_ASSERT(target(edCB, g) == vdB);
	}

    void test_target_3() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAD = add_edge(vdA, vdD, g).first;
		ed edBG = add_edge(vdB, vdG, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edHF = add_edge(vdH, vdF, g).first;
		ed edFG = add_edge(vdF, vdG, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;

        CPPUNIT_ASSERT(target(edAB, g) == vdB);
        CPPUNIT_ASSERT(target(edAD, g) == vdD);
        CPPUNIT_ASSERT(target(edBG, g) == vdG);
        CPPUNIT_ASSERT(target(edCD, g) == vdD);
        CPPUNIT_ASSERT(target(edDE, g) == vdE);
        CPPUNIT_ASSERT(target(edHF, g) == vdF);
        CPPUNIT_ASSERT(target(edFG, g) == vdG);
        CPPUNIT_ASSERT(target(edHG, g) == vdG);
	}

    // -----------
    // test_vertex
    // -----------

    void test_vertex_1() {
		graph_type g;

		vd vdA = add_vertex(g);

		CPPUNIT_ASSERT(vertex(0, g) == vdA);
	}

    void test_vertex_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBD = add_edge(vdB, vdD, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edDF = add_edge(vdD, vdF, g).first;
		ed edFD = add_edge(vdF, vdD, g).first;
		ed edFH = add_edge(vdF, vdH, g).first;

		vd vd_arr[] = {vdA, vdB, vdC, vdD, vdE, vdF, vdG, vdH};

		for (vertices_size_type i = 0; i < 8; ++i)
			CPPUNIT_ASSERT(vertex(i, g) == vd_arr[i]);
	}

    void test_vertex_3() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edCA = add_edge(vdC, vdA, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;

		vd vd_arr[] = {vdA, vdB, vdC};

		for (vertices_size_type i = 0; i < 3; ++i)
			CPPUNIT_ASSERT(vertex(i, g) == vd_arr[i]);
	}

	void test_vertex_4() {
		// Test for what vertex() does when called on an empty graph,
		// which apparently in boost's case is to return the argument
		// regardless of whether the vertex exists.
		graph_type g;

		CPPUNIT_ASSERT(vertex(0, g) == 0);
		CPPUNIT_ASSERT(vertex(100, g) == 100);
		CPPUNIT_ASSERT(vertex(5050, g) == 5050);
	}

    void test_vertex_5() {
		graph_type g;
	
		const vertices_size_type s = 801;
		vd vd_arr[s];
		for (vertices_size_type i = 0; i < s; ++i)
			vd_arr[i] = add_vertex(g);

		for (vertices_size_type i = 0; i < s; ++i)
			CPPUNIT_ASSERT(vertex(i, g) == vd_arr[i]);
	}

    // -------------
    // test_vertices
    // -------------

    void test_vertices_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;

        std::pair<vert_iter, vert_iter> p = vertices(g);
        vert_iter b = p.first;
        vert_iter e = p.second;

        CPPUNIT_ASSERT(b != e);
        CPPUNIT_ASSERT(*b == vdA);
		++b;

		CPPUNIT_ASSERT(b != e);
        CPPUNIT_ASSERT(*b == vdB);
		++b;

		CPPUNIT_ASSERT(b != e);
        CPPUNIT_ASSERT(*b == vdC);
		++b;

		CPPUNIT_ASSERT(b == e);
	}

    void test_vertices_2() {
		graph_type g;

        std::pair<vert_iter, vert_iter> p = vertices(g);

		CPPUNIT_ASSERT(p.first == p.second);
	}

    void test_vertices_3() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		vd vdI = add_vertex(g);

		ed edAI = add_edge(vdA, vdI, g).first;
		ed edIH = add_edge(vdI, vdH, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;
		ed edGF = add_edge(vdG, vdF, g).first;
		ed edFE = add_edge(vdF, vdE, g).first;
		ed edED = add_edge(vdE, vdD, g).first;
		ed edDC = add_edge(vdD, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;

		ed edAH = add_edge(vdA, vdH, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBI = add_edge(vdB, vdI, g).first;
		ed edGB = add_edge(vdG, vdB, g).first;
		ed edEG = add_edge(vdE, vdG, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;

        std::pair<vert_iter, vert_iter> p = vertices(g);
        vert_iter b = p.first;
        vert_iter e = p.second;
		vd v_arr[] = {vdA, vdB, vdC, vdD, vdE, vdF, vdG, vdH, vdI};
		const size_t v_arr_s = sizeof(v_arr) / sizeof(vd);
	
		for (size_t i = 0; i < v_arr_s; ++i) {
			CPPUNIT_ASSERT(*b == v_arr[i]);
			++b;
		}
		CPPUNIT_ASSERT(b == e);
	}

    void test_vertices_4() {
		graph_type g;

		add_vertex(g);
		add_vertex(g);
		add_vertex(g);

        std::pair<vert_iter, vert_iter> p = vertices(g);
		vert_iter begin = p.first;
		vert_iter end = p.second;

		vert_iter zeroth = begin;
		vert_iter first = zeroth + 1;
		vert_iter second = zeroth + 2;

		CPPUNIT_ASSERT(zeroth + 1 == first);
		CPPUNIT_ASSERT(zeroth < first);
		CPPUNIT_ASSERT(zeroth <= zeroth);
		CPPUNIT_ASSERT(second > first);
		CPPUNIT_ASSERT(end > second);
		CPPUNIT_ASSERT(end >= end);
		CPPUNIT_ASSERT(first != second);
		CPPUNIT_ASSERT(first + 1 == second);

		++second;
		CPPUNIT_ASSERT(second == end);

		--first;
		CPPUNIT_ASSERT(first == zeroth);

		CPPUNIT_ASSERT(first++ == zeroth);
		CPPUNIT_ASSERT(first == begin + 1);

		CPPUNIT_ASSERT(first-- == begin + 1);
		CPPUNIT_ASSERT(first == begin);
	}
	
    void test_vertices_5() {
		// Check that add_vertex doesn't invalidate vertex_iterators
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;

        std::pair<vert_iter, vert_iter> p1 = vertices(g);
        vert_iter e1 = p1.second;

		vd vdD = add_vertex(g);

        std::pair<vert_iter, vert_iter> p2 = vertices(g);
        vert_iter e2 = p2.second;

		CPPUNIT_ASSERT(*e1 == vdD);
		CPPUNIT_ASSERT(e1 != e2);
		++e1;
		CPPUNIT_ASSERT(e1 == e2);
	}

    // ----------------
    // test_constructor
    // ----------------

    void test_constructor_1() {
		graph_type new_g;

		CPPUNIT_ASSERT(num_vertices(new_g) == 0);
		CPPUNIT_ASSERT(num_edges(new_g) == 0);
	}

    void test_constructor_2() {
		graph_type new_g;

		add_vertex(new_g);

		CPPUNIT_ASSERT(num_vertices(new_g) == 1);
		CPPUNIT_ASSERT(num_edges(new_g) == 0);
	}

    void test_constructor_3() {
		graph_type new_g;

		add_edge(0, 1, new_g);

		CPPUNIT_ASSERT(num_vertices(new_g) == 2);
		CPPUNIT_ASSERT(num_edges(new_g) == 1);
	}

    // --------------
    // test_has_cycle
    // --------------

    void test_has_cycle_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBD = add_edge(vdB, vdD, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edDF = add_edge(vdD, vdF, g).first;
		ed edFD = add_edge(vdF, vdD, g).first;
		ed edFH = add_edge(vdF, vdH, g).first;

        CPPUNIT_ASSERT(has_cycle(g));
	}

    void test_has_cycle_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAD = add_edge(vdA, vdD, g).first;
		ed edBG = add_edge(vdB, vdG, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edHF = add_edge(vdH, vdF, g).first;
		ed edFG = add_edge(vdF, vdG, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;

        CPPUNIT_ASSERT(!has_cycle(g));
	}

    void test_has_cycle_3() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edCA = add_edge(vdC, vdA, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;

        CPPUNIT_ASSERT(has_cycle(g));
	}

    void test_has_cycle_4() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;

        CPPUNIT_ASSERT(!has_cycle(g));
	}

    void test_has_cycle_5() {
		graph_type g;

		add_vertex(g);

        CPPUNIT_ASSERT(!has_cycle(g));
	}

	void test_has_cycle_6() {
		graph_type g;

		CPPUNIT_ASSERT(!has_cycle(g));
	}

	void test_has_cycle_7() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		add_edge(vdA, vdB, g).first;
		add_edge(vdB, vdC, g).first;
		add_edge(vdC, vdD, g).first;
		add_edge(vdD, vdE, g).first;
		add_edge(vdE, vdA, g).first;

		CPPUNIT_ASSERT(has_cycle(g));
	}

	void test_has_cycle_8() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		vd vdI = add_vertex(g);

		ed edAI = add_edge(vdA, vdI, g).first;
		ed edIH = add_edge(vdI, vdH, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;
		ed edGF = add_edge(vdG, vdF, g).first;
		ed edFE = add_edge(vdF, vdE, g).first;
		ed edED = add_edge(vdE, vdD, g).first;
		ed edDC = add_edge(vdD, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;

		ed edAH = add_edge(vdA, vdH, g).first;
		ed edAE = add_edge(vdA, vdE, g).first;
		ed edBI = add_edge(vdB, vdI, g).first;
		ed edGB = add_edge(vdG, vdB, g).first;
		ed edEG = add_edge(vdE, vdG, g).first;
		ed edBE = add_edge(vdB, vdE, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;

		CPPUNIT_ASSERT(has_cycle(g));
	}

    // ---------------------
    // test_topological_sort
    // ---------------------

    void test_topological_sort_1() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;

        ostringstream out;
        topological_sort(g, ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "2 1 0 ");
	}

    void test_topological_sort_2() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		vd vdF = add_vertex(g);
		vd vdG = add_vertex(g);
		vd vdH = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edAD = add_edge(vdA, vdD, g).first;
		ed edBG = add_edge(vdB, vdG, g).first;
		ed edCD = add_edge(vdC, vdD, g).first;
		ed edDE = add_edge(vdD, vdE, g).first;
		ed edHF = add_edge(vdH, vdF, g).first;
		ed edFG = add_edge(vdF, vdG, g).first;
		ed edHG = add_edge(vdH, vdG, g).first;

        ostringstream out;
        topological_sort(g, ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "6 1 4 3 0 2 5 7 ");
	}

    void test_topological_sort_3() {
		graph_type g;

		add_vertex(g);

        ostringstream out;
        topological_sort(g, ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "0 ");
	}

    void test_topological_sort_4() {
		graph_type g;

        ostringstream out;
        topological_sort(g, ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "");
	}
	
	void test_topological_sort_5() {
		graph_type g;

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		ed edAB = add_edge(vdA, vdB, g).first;
		ed edBA = add_edge(vdB, vdA, g).first;
		ed edAC = add_edge(vdA, vdC, g).first;
		ed edCA = add_edge(vdC, vdA, g).first;
		ed edBC = add_edge(vdB, vdC, g).first;
		ed edCB = add_edge(vdC, vdB, g).first;

		try {
			ostringstream out;
			topological_sort(g, ostream_iterator<vertex_descriptor>(out, " "));
			CPPUNIT_ASSERT(false);
		} catch (not_a_dag& e) {
			CPPUNIT_ASSERT(strcmp(e.what(), "The graph must be a DAG.") == 0);
		} catch (boost::not_a_dag& e) {
			CPPUNIT_ASSERT(strcmp(e.what(), "The graph must be a DAG.") == 0);
		}

	}

    void test_topological_sort_6() {
		graph_type g;

		vd vdA = add_vertex(g);
		ed edAA = add_edge(vdA, vdA, g).first;

		try {
			ostringstream out;
			topological_sort(g, ostream_iterator<vertex_descriptor>(out, " "));
			CPPUNIT_ASSERT(false);
		} catch (not_a_dag& e) {
			CPPUNIT_ASSERT(strcmp(e.what(), "The graph must be a DAG.") == 0);
		} catch (boost::not_a_dag& e) {
			CPPUNIT_ASSERT(strcmp(e.what(), "The graph must be a DAG.") == 0);
		}
	}
	
	void test_topological_sort_7() {
		graph_type g;	

		vd vdA = add_vertex(g);
		vd vdB = add_vertex(g);
		vd vdC = add_vertex(g);
		vd vdD = add_vertex(g);
		vd vdE = add_vertex(g);
		add_edge(vdA, vdB, g).first;
		add_edge(vdB, vdC, g).first;
		add_edge(vdC, vdD, g).first;
		add_edge(vdD, vdE, g).first;
		add_edge(vdE, vdA, g).first;

		try {
			ostringstream out;
			topological_sort(g, ostream_iterator<vertex_descriptor>(out, " "));
			CPPUNIT_ASSERT(false);
		} catch (not_a_dag& e) {
			CPPUNIT_ASSERT(strcmp(e.what(), "The graph must be a DAG.") == 0);
		} catch (boost::not_a_dag& e) {
			CPPUNIT_ASSERT(strcmp(e.what(), "The graph must be a DAG.") == 0);
		}
	}

	void test_stress_1() {
		graph_type g;

		const vertices_size_type s = 200;
		vd vd_arr[s];

		for (vertices_size_type i = 0; i < s; ++i)
			vd_arr[i] = add_vertex(g);

		for (vertices_size_type i = 0; i < s; i += 3)
			for (vertices_size_type j = i + 1; j < s; j += 2)
				add_edge(i, j, g);

		ostringstream my_output;
		topological_sort(g, ostream_iterator<vertex_descriptor>(my_output, " "));

		string boost_output("1 4 7 10 13 16 19 22 25 28 31 34 37 40 43 46 49 52 55 58 61 64 67 70 73 76 79 82 85 88 91 94 97 100 103 106 109 112 115 118 121 124 127 130 133 136 139 142 145 148 151 154 157 160 163 166 169 172 175 178 181 184 187 190 193 196 199 198 195 197 192 194 189 191 186 188 183 185 180 182 177 179 174 176 171 173 168 170 165 167 162 164 159 161 156 158 153 155 150 152 147 149 144 146 141 143 138 140 135 137 132 134 129 131 126 128 123 125 120 122 117 119 114 116 111 113 108 110 105 107 102 104 99 101 96 98 93 95 90 92 87 89 84 86 81 83 78 80 75 77 72 74 69 71 66 68 63 65 60 62 57 59 54 56 51 53 48 50 45 47 42 44 39 41 36 38 33 35 30 32 27 29 24 26 21 23 18 20 15 17 12 14 9 11 6 8 3 5 0 2 ");

		CPPUNIT_ASSERT(my_output.str() == boost_output);
	}

	void test_stress_2() {
		graph_type g;

		const vertices_size_type s = 128;
		vd vd_arr[s];

		for (vertices_size_type i = 0; i < s; ++i)
			vd_arr[i] = add_vertex(g);

		for (vertices_size_type i = 0; i < s - 2; ++i)
			add_edge(i, i + 2, g);

		for (vertices_size_type i = 2; i < s; i += 2)
			add_edge(i, i - 1, g);

		ostringstream my_output;
		topological_sort(g, ostream_iterator<vertex_descriptor>(my_output, " "));

		string boost_output("127 125 123 121 119 117 115 113 111 109 107 105 103 101 99 97 95 93 91 89 87 85 83 81 79 77 75 73 71 69 67 65 63 61 59 57 55 53 51 49 47 45 43 41 39 37 35 33 31 29 27 25 23 21 19 17 15 13 11 9 7 5 3 1 126 124 122 120 118 116 114 112 110 108 106 104 102 100 98 96 94 92 90 88 86 84 82 80 78 76 74 72 70 68 66 64 62 60 58 56 54 52 50 48 46 44 42 40 38 36 34 32 30 28 26 24 22 20 18 16 14 12 10 8 6 4 2 0 ");

		CPPUNIT_ASSERT(my_output.str() == boost_output);
	}

	void test_stress_3() {
		graph_type g;

		const vertices_size_type s = 256;
		vd vd_arr[s];

		for (vertices_size_type i = 0; i < s; ++i)
			vd_arr[i] = add_vertex(g);

		for (vertices_size_type i = 0; i < s - 3; ++i)
			add_edge(i, i + 3, g);

		for (vertices_size_type i = 2; i < s; i += 3) {
			add_edge(i, i - 1, g);
			add_edge(i - 1, i - 2, g);
		}

		ostringstream my_output;
		topological_sort(g, ostream_iterator<vertex_descriptor>(my_output, " "));

		string boost_output("255 252 249 246 243 240 237 234 231 228 225 222 219 216 213 210 207 204 201 198 195 192 189 186 183 180 177 174 171 168 165 162 159 156 153 150 147 144 141 138 135 132 129 126 123 120 117 114 111 108 105 102 99 96 93 90 87 84 81 78 75 72 69 66 63 60 57 54 51 48 45 42 39 36 33 30 27 24 21 18 15 12 9 6 3 0 253 250 247 244 241 238 235 232 229 226 223 220 217 214 211 208 205 202 199 196 193 190 187 184 181 178 175 172 169 166 163 160 157 154 151 148 145 142 139 136 133 130 127 124 121 118 115 112 109 106 103 100 97 94 91 88 85 82 79 76 73 70 67 64 61 58 55 52 49 46 43 40 37 34 31 28 25 22 19 16 13 10 7 4 1 254 251 248 245 242 239 236 233 230 227 224 221 218 215 212 209 206 203 200 197 194 191 188 185 182 179 176 173 170 167 164 161 158 155 152 149 146 143 140 137 134 131 128 125 122 119 116 113 110 107 104 101 98 95 92 89 86 83 80 77 74 71 68 65 62 59 56 53 50 47 44 41 38 35 32 29 26 23 20 17 14 11 8 5 2 ");

		CPPUNIT_ASSERT(my_output.str() == boost_output);
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge_1);
    CPPUNIT_TEST(test_add_edge_2);
    CPPUNIT_TEST(test_add_edge_3);
    CPPUNIT_TEST(test_add_edge_4);
    CPPUNIT_TEST(test_add_edge_5);
    CPPUNIT_TEST(test_add_edge_6);
    CPPUNIT_TEST(test_add_vertex_1);
    CPPUNIT_TEST(test_add_vertex_2);
    CPPUNIT_TEST(test_add_vertex_3);
    CPPUNIT_TEST(test_adjacent_vertices_1);
    CPPUNIT_TEST(test_adjacent_vertices_2);
    CPPUNIT_TEST(test_adjacent_vertices_3);
    CPPUNIT_TEST(test_adjacent_vertices_4);
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
	CPPUNIT_TEST(test_vertex_4);
	CPPUNIT_TEST(test_vertex_5);
    CPPUNIT_TEST(test_vertices_1);
    CPPUNIT_TEST(test_vertices_2);
    CPPUNIT_TEST(test_vertices_3);
    CPPUNIT_TEST(test_vertices_4);
    CPPUNIT_TEST(test_vertices_5);
	CPPUNIT_TEST(test_constructor_1);
	CPPUNIT_TEST(test_constructor_2);
	CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_has_cycle_1);
    CPPUNIT_TEST(test_has_cycle_2);
    CPPUNIT_TEST(test_has_cycle_3);
    CPPUNIT_TEST(test_has_cycle_4);
    CPPUNIT_TEST(test_has_cycle_5);
    CPPUNIT_TEST(test_has_cycle_6);
    CPPUNIT_TEST(test_has_cycle_7);
    CPPUNIT_TEST(test_has_cycle_8);
    CPPUNIT_TEST(test_topological_sort_1);
    CPPUNIT_TEST(test_topological_sort_2);
    CPPUNIT_TEST(test_topological_sort_3);
    CPPUNIT_TEST(test_topological_sort_4);
    CPPUNIT_TEST(test_topological_sort_5);
    CPPUNIT_TEST(test_topological_sort_6);
    CPPUNIT_TEST(test_topological_sort_7);
    CPPUNIT_TEST(test_stress_1);
    CPPUNIT_TEST(test_stress_2);
    CPPUNIT_TEST(test_stress_3);
    CPPUNIT_TEST_SUITE_END();
};


// ----
// main
// ----

int main () {
    using namespace boost;

    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestGraph.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestGraph< adjacency_list<setS, vecS, directedS> >::suite());
	tr.addTest(TestGraph<Graph>::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
