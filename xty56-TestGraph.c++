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

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

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

    // directed, sparse, unweighted

    // not connected, not cyclic
    graph_type graphNotConnectedNotCyclic;

    vertex_descriptor vdA;
    vertex_descriptor vdB;
    vertex_descriptor vdC;
    vertex_descriptor vdD;
    vertex_descriptor vdE;
    vertex_descriptor vdF;
    vertex_descriptor vdG;
    vertex_descriptor vdH;
    vertex_descriptor vdI;
    vertex_descriptor vdJ;

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
    edge_descriptor edIJ;

    // connected, not cyclic
    graph_type graphConnectedNotCyclic;
    vertex_descriptor vdAgraph2;
    vertex_descriptor vdBgraph2;
    vertex_descriptor vdCgraph2;

    edge_descriptor edABgraph2;
    edge_descriptor edBAgraph2;
    edge_descriptor edACgraph2;
    edge_descriptor edCAgraph2;

    // not connected, cyclic
    graph_type graphNotConnectedCyclic;
    vertex_descriptor vdAgraph3;
    vertex_descriptor vdBgraph3;
    vertex_descriptor vdCgraph3;
    vertex_descriptor vdDgraph3;

    edge_descriptor edABgraph3;
    edge_descriptor edBCgraph3;
    edge_descriptor edCDgraph3;
    edge_descriptor edDBgraph3;

    // connected, cyclic
    graph_type graphConnectedCyclic;
    vertex_descriptor vdAgraph4;
    vertex_descriptor vdBgraph4;
    vertex_descriptor vdCgraph4;
    vertex_descriptor vdDgraph4;

    edge_descriptor edABgraph4;
    edge_descriptor edBCgraph4;
    edge_descriptor edCDgraph4;
    edge_descriptor edDAgraph4;
    edge_descriptor edADgraph4;
    edge_descriptor edDCgraph4;
    edge_descriptor edCBgraph4;
    edge_descriptor edBAgraph4;

    // -----
    // setUp
    // -----

    void setUp () {

        // graphNotConnectedNotCyclic
        vdA  = add_vertex(graphNotConnectedNotCyclic);
        vdB  = add_vertex(graphNotConnectedNotCyclic);
        vdC  = add_vertex(graphNotConnectedNotCyclic);
        vdD  = add_vertex(graphNotConnectedNotCyclic);
        vdE  = add_vertex(graphNotConnectedNotCyclic);
        vdF  = add_vertex(graphNotConnectedNotCyclic);
        vdG  = add_vertex(graphNotConnectedNotCyclic);
        vdH  = add_vertex(graphNotConnectedNotCyclic);
        vdI  = add_vertex(graphNotConnectedNotCyclic);
        vdJ  = add_vertex(graphNotConnectedNotCyclic);

        edAB = add_edge(vdA, vdB, graphNotConnectedNotCyclic).first;
        add_edge(vdA, vdB, graphNotConnectedNotCyclic).first;
        edAC = add_edge(vdA, vdC, graphNotConnectedNotCyclic).first;
        edAE = add_edge(vdA, vdE, graphNotConnectedNotCyclic).first;
        edBD = add_edge(vdB, vdD, graphNotConnectedNotCyclic).first;
        edBE = add_edge(vdB, vdE, graphNotConnectedNotCyclic).first;
        edCD = add_edge(vdC, vdD, graphNotConnectedNotCyclic).first;
        edDE = add_edge(vdD, vdE, graphNotConnectedNotCyclic).first;
        edDF = add_edge(vdD, vdF, graphNotConnectedNotCyclic).first;
        edFD = add_edge(vdF, vdD, graphNotConnectedNotCyclic).first;
        edFH = add_edge(vdF, vdH, graphNotConnectedNotCyclic).first;
        edGH = add_edge(vdG, vdH, graphNotConnectedNotCyclic).first;
        edIJ = add_edge(vdI, vdJ, graphNotConnectedNotCyclic).first;

        // graphConnectedNotCyclic
        vdAgraph2 = add_vertex(graphConnectedNotCyclic);
        vdBgraph2 = add_vertex(graphConnectedNotCyclic);
        vdCgraph2 = add_vertex(graphConnectedNotCyclic);

        edABgraph2 = add_edge(vdAgraph2, vdBgraph2, graphConnectedNotCyclic).first;
        edBAgraph2 = add_edge(vdBgraph2, vdAgraph2, graphConnectedNotCyclic).first;
        edACgraph2 = add_edge(vdAgraph2, vdCgraph2, graphConnectedNotCyclic).first;
        edCAgraph2 = add_edge(vdCgraph2, vdAgraph2, graphConnectedNotCyclic).first;

        // graphNotConnectedCyclic
        vdAgraph3 = add_vertex(graphNotConnectedCyclic);
        vdBgraph3 = add_vertex(graphNotConnectedCyclic);
        vdCgraph3 = add_vertex(graphNotConnectedCyclic);
        vdDgraph3 = add_vertex(graphNotConnectedCyclic);

        edABgraph3 = add_edge(vdAgraph3, vdBgraph3, graphNotConnectedCyclic).first;
        edBCgraph3 = add_edge(vdBgraph3, vdCgraph3, graphNotConnectedCyclic).first;
        edCDgraph3 = add_edge(vdCgraph3, vdDgraph3, graphNotConnectedCyclic).first;
        edDBgraph3 = add_edge(vdDgraph3, vdBgraph3, graphNotConnectedCyclic).first;

        // graphConnectedCyclic
        vdAgraph4 = add_vertex(graphConnectedCyclic);
        vdBgraph4 = add_vertex(graphConnectedCyclic);
        vdCgraph4 = add_vertex(graphConnectedCyclic);
        vdDgraph4 = add_vertex(graphConnectedCyclic);

        edABgraph4 = add_edge(vdAgraph4, vdBgraph4, graphConnectedCyclic).first;
        edBCgraph4 = add_edge(vdBgraph4, vdCgraph4, graphConnectedCyclic).first;
        edCDgraph4 = add_edge(vdCgraph4, vdDgraph4, graphConnectedCyclic).first;
        edDAgraph4 = add_edge(vdDgraph4, vdAgraph4, graphConnectedCyclic).first;

        edADgraph4 = add_edge(vdAgraph4, vdDgraph4, graphConnectedCyclic).first;
        edDCgraph4 = add_edge(vdDgraph4, vdCgraph4, graphConnectedCyclic).first;
        edCBgraph4 = add_edge(vdCgraph4, vdBgraph4, graphConnectedCyclic).first;
        edBAgraph4 = add_edge(vdBgraph4, vdAgraph4, graphConnectedCyclic).first;
    }

    //============================
    // test_add_edge
    //============================

    void test_add_edge_graphNotConnectedNotCyclic () {
        // graph will still retain property of being not connected and not cyclic

        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == false);


        p = add_edge(vdJ, vdI, graphNotConnectedNotCyclic);
        edge_descriptor edJI = p.first;

        CPPUNIT_ASSERT(p.second == true);

        std::pair<edge_descriptor, bool> q = add_edge(vdJ, vdI, graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(q.first == edJI);
        CPPUNIT_ASSERT(q.second == false);
    }

    void test_add_edge_graphConnectedNotCyclic () {
        // graph will still retain property of being connected and not cyclic

        vertex_descriptor vdDgraph2;
        vdDgraph2 = add_vertex(graphConnectedNotCyclic);

        std::pair<edge_descriptor, bool> p = add_edge(vdBgraph2, vdDgraph2, graphConnectedNotCyclic);
        edge_descriptor edBDgraph2 = p.first;
        CPPUNIT_ASSERT(p.second == true);

        p = add_edge(vdBgraph2, vdDgraph2, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(p.first == edBDgraph2);
        CPPUNIT_ASSERT(p.second == false);

        p = add_edge(vdDgraph2, vdBgraph2, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(p.second == true);
    }

    void test_add_edge_graphNotConnectedCyclic () {
        // graph will still retain property of being not connected and cyclic

        std::pair<edge_descriptor, bool> p = add_edge(vdCgraph3, vdBgraph3, graphConnectedNotCyclic);
        edge_descriptor edCBgraph3 = p.first;
        CPPUNIT_ASSERT(p.second == true);

        p = add_edge(vdCgraph3, vdBgraph3, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(p.first == edCBgraph3);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_add_edge_graphConnectedCyclic () {
        // graph will still retain property of being connected and cyclic

        std::pair<edge_descriptor, bool> p = add_edge(vdCgraph4, vdBgraph4, graphConnectedCyclic);
        CPPUNIT_ASSERT(p.first == edCBgraph4);
        CPPUNIT_ASSERT(p.second == false);
    }

    //============================
    // test_adjacent_vertices
    //============================

    void test_adjacent_vertices_graphNotConnectedNotCyclic () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, graphNotConnectedNotCyclic);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB);
        }
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdC);}

        p = adjacent_vertices(vdF, graphNotConnectedNotCyclic);
        b = p.first;
        e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdD);
        }
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdH);
        }
    }

    void test_adjacent_vertices_graphConnectedNotCyclic () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdBgraph2, graphConnectedNotCyclic);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdAgraph2);
        }
        ++b;
    }

    void test_adjacent_vertices_graphNotConnectedCyclic () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdDgraph3, graphNotConnectedCyclic);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdBgraph3);
        }
        ++b;
        CPPUNIT_ASSERT(b == e);
    }

    void test_adjacent_vertices_graphConnectedCyclic () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdDgraph4, graphConnectedCyclic);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdAgraph4);
        }
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdCgraph4);}
    }

    //============================
    // test_edge
    //============================

    void test_edge_graphNotConnectedNotCyclic () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdA, vdD, graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(p.second == false);

        p = edge(vdB, vdA, graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_edge_graphConnectedNotCyclic () {
        std::pair<edge_descriptor, bool> p = edge(vdAgraph2, vdBgraph2, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(p.first  == edABgraph2);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdBgraph2, vdCgraph2, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_edge_graphNotConnectedCyclic () {
        std::pair<edge_descriptor, bool> p = edge(vdAgraph3, vdBgraph3, graphNotConnectedCyclic);
        CPPUNIT_ASSERT(p.first  == edABgraph3);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdAgraph3, vdDgraph3, graphNotConnectedCyclic);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_edge_graphConnectedCyclic () {
        std::pair<edge_descriptor, bool> p = edge(vdCgraph4, vdBgraph4, graphConnectedCyclic);
        CPPUNIT_ASSERT(p.first  == edCBgraph4);
        CPPUNIT_ASSERT(p.second == true);

        p = edge(vdAgraph4, vdCgraph4, graphConnectedCyclic);
        CPPUNIT_ASSERT(p.second == false);
    }

    //============================
    // test_edges
    //============================

    void test_edges_graphNotConnectedNotCyclic () {
        std::pair<edge_iterator, edge_iterator> p = edges(graphNotConnectedNotCyclic);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAB);
        }
        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAC);
        }
    }

    void test_edges_graphConnectedNotCyclic () {
        std::pair<edge_iterator, edge_iterator> p = edges(graphConnectedNotCyclic);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edABgraph2);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edACgraph2);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edBAgraph2);
        }
    }

    void test_edges_graphNotConnectedCyclic () {
        std::pair<edge_iterator, edge_iterator> p = edges(graphNotConnectedCyclic);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edABgraph3);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edBCgraph3);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edCDgraph3);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edDBgraph3);
        }
    }


    void test_edges_graphConnectedCyclic () {
        std::pair<edge_iterator, edge_iterator> p = edges(graphConnectedCyclic);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edABgraph4);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edADgraph4);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edBAgraph4);
        }

        ++b;
        if (b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edBCgraph4);
        }
    }

    //============================
    // test_num_edges
    //============================

    void test_num_edges_graphNotConnectedNotCyclic () {
        edges_size_type es = num_edges(graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(es == 12);}

    void test_num_edges_graphConnectedNotCyclic () {
        edges_size_type es = num_edges(graphConnectedNotCyclic);
        CPPUNIT_ASSERT(es == 4);}

    void test_num_edges_graphNotConnectedCyclic () {
        edges_size_type es = num_edges(graphNotConnectedCyclic);
        CPPUNIT_ASSERT(es == 4);}

    void test_num_edges_graphConnectedCyclic () {
        edges_size_type es = num_edges(graphConnectedCyclic);
        CPPUNIT_ASSERT(es == 8);}

    //============================
    // test_num_vertices
    //============================

    void test_num_vertices_graphNotConnectedNotCyclic () {
        vertices_size_type vs = num_vertices(graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(vs == 10);}

    void test_num_vertices_graphConnectedNotCyclic () {
        vertices_size_type vs = num_vertices(graphConnectedNotCyclic);
        CPPUNIT_ASSERT(vs == 3);}

    void test_num_vertices_graphNotConnectedCyclic () {
        vertices_size_type vs = num_vertices(graphNotConnectedCyclic);
        CPPUNIT_ASSERT(vs == 4);}

    void test_num_vertices_graphConnectedCyclic () {
        vertices_size_type vs = num_vertices(graphConnectedCyclic);
        CPPUNIT_ASSERT(vs == 4);}

    //============================
    // test_source
    //============================

    void test_source_graphNotConnectedNotCyclic () {
        vertex_descriptor vd = source(edAB, graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_source_graphConnectedNotCyclic () {
        vertex_descriptor vd = source(edBAgraph2, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(vd == vdBgraph2);}

    void test_source_graphNotConnectedCyclic () {
        vertex_descriptor vd = source(edDBgraph3, graphNotConnectedCyclic);
        CPPUNIT_ASSERT(vd == vdDgraph3);}

    void test_source_graphConnectedCyclic () {
        vertex_descriptor vd = source(edDCgraph4, graphConnectedCyclic);
        CPPUNIT_ASSERT(vd == vdDgraph4);}

    //============================
    // test_target
    //============================

    void test_target_graphNotConnectedNotCyclic () {
        vertex_descriptor vd = target(edAB, graphNotConnectedNotCyclic);
        CPPUNIT_ASSERT(vd == vdB);}

    void test_target_graphConnectedNotCyclic () {
        vertex_descriptor vd = target(edBAgraph2, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(vd == vdAgraph2);}

    void test_target_graphNotConnectedCyclic () {
        vertex_descriptor vd = target(edDBgraph3, graphNotConnectedCyclic);
        CPPUNIT_ASSERT(vd == vdBgraph3);}

    void test_target_graphConnectedCyclic () {
        vertex_descriptor vd = target(edDCgraph4, graphConnectedCyclic);
        CPPUNIT_ASSERT(vd == vdCgraph4);}

    //============================
    // test_vertex
    //============================

    void test_vertex_graphNotConnectedNotCyclic () {
        vertex_descriptor vd = vertex(0, graphNotConnectedNotCyclic);

        CPPUNIT_ASSERT(vd == vdA);}

    void test_vertex_graphConnectedNotCyclic () {
        vertex_descriptor vd = vertex(2, graphConnectedNotCyclic);
        CPPUNIT_ASSERT(vd == vdCgraph2);}

    void test_vertex_graphNotConnectedCyclic () {
        vertex_descriptor vd = vertex(1, graphNotConnectedCyclic);
        CPPUNIT_ASSERT(vd == vdBgraph2);}

    void test_vertex_graphConnectedCyclic () {
        vertex_descriptor vd = vertex(3, graphConnectedCyclic);
        CPPUNIT_ASSERT(vd == vdDgraph4);}

    //============================
    // test_vertices
    //============================

    void test_vertices_graphNotConnectedNotCyclic () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(graphNotConnectedNotCyclic);
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

    void test_vertices_graphConnectedNotCyclic () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(graphConnectedNotCyclic);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdAgraph2);}
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdBgraph2);}}

    void test_vertices_graphNotConnectedCyclic () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(graphNotConnectedCyclic);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdAgraph3);
        }
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdBgraph3);
        }
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdCgraph3);
        }
        ++b;
        if (b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdDgraph3);
        }
    }

    void test_vertices_graphConnectedCyclic () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(graphConnectedCyclic);
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

    //============================
    // test_has_cycle
    //============================

    void test_has_cycle_graphNotConnectedNotCyclic () {
        CPPUNIT_ASSERT(has_cycle(graphNotConnectedNotCyclic));}

    void test_has_cycle_graphConnectedNotCyclic () {
        CPPUNIT_ASSERT(has_cycle(graphConnectedNotCyclic));}

    void test_has_cycle_graphNotConnectedCyclic () {
        CPPUNIT_ASSERT(has_cycle(graphNotConnectedCyclic));}

    void test_has_cycle_graphConnectedCyclic () {
        CPPUNIT_ASSERT(has_cycle(graphConnectedCyclic));}

    //============================
    // test_topological_sort
    //============================

    void test_topological_sort_graphNotConnectedNotCyclic () {
        std::ostringstream out;
        topological_sort(graphNotConnectedNotCyclic, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "2 0 1 ");}

    void test_topological_sort_graphConnectedNotCyclic () {
        std::ostringstream out;
        topological_sort(graphConnectedNotCyclic, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "2 0 1 ");}

    void test_topological_sort_graphNotConnectedCyclic () {
        std::ostringstream out;
        topological_sort(graphNotConnectedCyclic, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "2 0 1 ");}

    void test_topological_sort_graphConnectedCyclic () {
        std::ostringstream out;
        topological_sort(graphConnectedCyclic, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "2 0 1 ");}

    //============================
    // suite
    //============================

    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_add_edge_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_add_edge_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_add_edge_graphConnectedCyclic);

    CPPUNIT_TEST(test_adjacent_vertices_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_adjacent_vertices_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_adjacent_vertices_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_adjacent_vertices_graphConnectedCyclic);

    CPPUNIT_TEST(test_edge_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_edge_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_edge_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_edge_graphConnectedCyclic);

    CPPUNIT_TEST(test_edges_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_edges_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_edges_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_edges_graphConnectedCyclic);

    CPPUNIT_TEST(test_num_edges_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_num_edges_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_num_edges_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_num_edges_graphConnectedCyclic);

    CPPUNIT_TEST(test_num_vertices_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_num_vertices_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_num_vertices_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_num_vertices_graphConnectedCyclic);

    CPPUNIT_TEST(test_source_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_source_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_source_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_source_graphConnectedCyclic);

    CPPUNIT_TEST(test_target_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_target_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_target_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_target_graphConnectedCyclic);

    CPPUNIT_TEST(test_vertex_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_vertex_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_vertex_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_vertex_graphConnectedCyclic);

    CPPUNIT_TEST(test_vertices_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_vertices_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_vertices_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_vertices_graphConnectedCyclic);

    CPPUNIT_TEST(test_has_cycle_graphNotConnectedNotCyclic);
    CPPUNIT_TEST(test_has_cycle_graphConnectedNotCyclic);
    CPPUNIT_TEST(test_has_cycle_graphNotConnectedCyclic);
    CPPUNIT_TEST(test_has_cycle_graphConnectedCyclic);

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
