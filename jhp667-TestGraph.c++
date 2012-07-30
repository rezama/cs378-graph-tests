// ----------------------------
// Joe Peacock
// UTEID: jhp667
// CS378 Project 5: Graph
// 7/30/2012
//
//
// BASED ON:
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
// includesdsad asd
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort
#include "boost/graph/exception.hpp" // not_a_dag

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

    //cyclic
    graph_type g;

    //empty
    graph_type g2;

    //acyclic
    graph_type g3;

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


    vertex_descriptor vdA3;
    vertex_descriptor vdB3;
    vertex_descriptor vdC3;
    vertex_descriptor vdD3;
    vertex_descriptor vdE3;
    vertex_descriptor vdF3;
    vertex_descriptor vdG3;
    vertex_descriptor vdH3;

    edge_descriptor edAB3;
    edge_descriptor edAC3;
    edge_descriptor edAE3;
    edge_descriptor edBD3;
    edge_descriptor edBE3;
    edge_descriptor edCD3;
    edge_descriptor edDE3;
    edge_descriptor edDF3;
    edge_descriptor edFD3;
    edge_descriptor edFH3;
    edge_descriptor edGH3;


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

        vdA3  = add_vertex(g3);
        vdB3  = add_vertex(g3);
        vdC3  = add_vertex(g3);
        vdD3  = add_vertex(g3);
        vdE3  = add_vertex(g3);
        vdF3  = add_vertex(g3);
        vdG3  = add_vertex(g3);
        vdH3  = add_vertex(g3);
        edAB3 = add_edge(vdA, vdB, g3).first; // 0 1
        edAC3 = add_edge(vdA, vdC, g3).first; // 0 2
        edAE3 = add_edge(vdA, vdE, g3).first; // 0 4
        edBD3 = add_edge(vdB, vdD, g3).first; // 1 3
        edBE3 = add_edge(vdB, vdE, g3).first; // 1 4
        edCD3 = add_edge(vdC, vdD, g3).first; // 2 3
        edDE3 = add_edge(vdD, vdE, g3).first; // 3 4
        edDF3 = add_edge(vdD, vdF, g3).first; // 3 5
        edFH3 = add_edge(vdF, vdH, g3).first; // 5 7
        edGH3 = add_edge(vdG, vdH, g3).first; // 6 7   4 7 5 3 1 2 0 6

                                                    // 6 0 2 1 3 5 7 4
    }

    // -------------
    // test_add_edge
    // -------------

    void test_add_edge1 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_add_edge2 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdD, g);
        edge_descriptor edAD = p.first;
        CPPUNIT_ASSERT(p.second == true);
        p = add_edge(vdA, vdD, g);
        CPPUNIT_ASSERT(p.second == false);
        CPPUNIT_ASSERT(p.first  == edAD);
    }

    //based on the Boost implementation, self directed edges are allowed
    void test_add_edge3 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdA, g);
        CPPUNIT_ASSERT(p.second == true);
        p = add_edge(vdA, vdA, g);
        CPPUNIT_ASSERT(p.second == false);
    }

    //Parallel edge with reversed direction
    void test_add_edge4 () {
        std::pair<edge_descriptor, bool> p = add_edge(vdB, vdA, g);
        edge_descriptor edBA = p.first;
        CPPUNIT_ASSERT(p.second == true);
        p = add_edge(vdB, vdA, g);
        CPPUNIT_ASSERT(p.second == false);
        CPPUNIT_ASSERT(p.first == edBA);
    }


    // ----------------------
    // test_adjacent_vertices
    // ----------------------

    void test_adjacent_vertices1 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        std::set<vertex_descriptor> verts = std::set<vertex_descriptor> (b, e);
        std::set<vertex_descriptor> check = std::set<vertex_descriptor> ();
        check.insert(vdB);
        check.insert(vdC);
        check.insert(vdE);
    }

    void test_adjacent_vertices2 () {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdE, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b == e);
    }

    void test_adjacent_vertices3 () {
        bool a = add_edge(vdA, vdA, g).second;
        CPPUNIT_ASSERT(a);
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;
        CPPUNIT_ASSERT(b != e);
        std::set<vertex_descriptor> verts = std::set<vertex_descriptor> (b, e);
        std::set<vertex_descriptor> check = std::set<vertex_descriptor> ();
        check.insert(vdA);
        check.insert(vdB);
        check.insert(vdC);
        check.insert(vdE);
        CPPUNIT_ASSERT(verts == check);
    }
        

    // ---------
    // test_edge
    // ---------

    void test_edge1 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);}

    void test_edge2 () {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdA, g);
        CPPUNIT_ASSERT(p.second == false);
        p = edge(vdA, vdD, g);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_edge3 () {
        edge_descriptor edAA = add_edge(vdA, vdA, g).first;
        std::pair<edge_descriptor, bool> p = edge(vdA, vdA, g);
        CPPUNIT_ASSERT(p.first  == edAA);
        CPPUNIT_ASSERT(p.second == true);
    }

    // ----------
    // test_edges
    // ----------

    void test_edges1 () {
        std::pair<edge_iterator, edge_iterator> p = edges(g2);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b == e);
    }

    void test_edges2 () {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        std::set<edge_descriptor> test = std::set<edge_descriptor> (b, e);
        std::set<edge_descriptor> check = std::set<edge_descriptor> ();
        check.insert(edAB);
        check.insert(edAC);
        check.insert(edAE);
        check.insert(edBD);
        check.insert(edBE);
        check.insert(edCD);
        check.insert(edDE);
        check.insert(edDF);
        check.insert(edFD);
        check.insert(edFH);
        check.insert(edGH);
        CPPUNIT_ASSERT(test == check);
    }


    void test_edges3 () {
        edge_descriptor edCC = add_edge(vdC, vdC, g).first;
        edge_descriptor edBA = add_edge(vdB, vdA, g).first;

        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        std::set<edge_descriptor> test = std::set<edge_descriptor> (b, e);
        std::set<edge_descriptor> check = std::set<edge_descriptor> ();
        check.insert(edCC);
        check.insert(edBA);
        check.insert(edAB);
        check.insert(edAC);
        check.insert(edAE);
        check.insert(edBD);
        check.insert(edBE);
        check.insert(edCD);
        check.insert(edDE);
        check.insert(edDF);
        check.insert(edFD);
        check.insert(edFH);
        check.insert(edGH);
        CPPUNIT_ASSERT(test == check);
    }


    // --------------
    // test_num_edges
    // --------------

    void test_num_edges1 () {
        edges_size_type es = num_edges(g2);
        CPPUNIT_ASSERT(es == 0);}

    void test_num_edges2 () {
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 11);}

    void test_num_edges3 () {
        add_edge(vdB, vdA, g);
        add_edge(vdA, vdB, g);
        add_edge(vdA, vdA, g);
        edges_size_type es = num_edges(g);
        CPPUNIT_ASSERT(es == 13);}

    // -----------------
    // test_num_vertices
    // -----------------

    void test_num_vertices1 () {
        vertices_size_type vs = num_vertices(g2);
        CPPUNIT_ASSERT(vs == 0);}

    void test_num_vertices2 () {
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 8);}

    void test_num_vertices3 () {
        vertex_descriptor vdM = add_vertex(g);
        add_edge(vdA, vdM, g);
        add_vertex(g);
        vertices_size_type vs = num_vertices(g);
        CPPUNIT_ASSERT(vs == 10);}

    // -----------
    // test_source
    // -----------

    void test_source1 () {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_source2 () {
        edge_descriptor edAA = add_edge(vdA,vdA,g).first;
        vertex_descriptor vd = source(edAA, g);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_source3 () {
        edge_descriptor edBA = add_edge(vdB,vdA,g).first;
        vertex_descriptor vd = source(edBA, g);
        CPPUNIT_ASSERT(vd == vdB);}

    // -----------
    // test_target
    // -----------

    void test_target1 () {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);}

    void test_target2 () {
        edge_descriptor edAA = add_edge(vdA,vdA,g).first;
        vertex_descriptor vd = target(edAA, g);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_target3 () {
        edge_descriptor edBA = add_edge(vdB,vdA,g).first;
        vertex_descriptor vd = target(edBA, g);
        CPPUNIT_ASSERT(vd == vdA);}

    // -----------
    // test_vertex
    // -----------

    void test_vertex1 () {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);}

    void test_vertex2 () {
        vertex_descriptor vd = vertex(7, g);
        CPPUNIT_ASSERT(vd == vdH);}

    void test_vertex3 () {
        vertex_descriptor vdI = add_vertex(g);
        vertex_descriptor vd = vertex(8, g);
        CPPUNIT_ASSERT(vd == vdI);}

    // -------------
    // test_vertices
    // -------------

    void test_vertices1 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g2);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b == e);
    }

    void test_vertices2 () {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        std::set<vertex_descriptor> test = std::set<vertex_descriptor> (b, e);
        std::set<vertex_descriptor> check = std::set<vertex_descriptor> ();
        check.insert(vdA);
        check.insert(vdB);
        check.insert(vdC);
        check.insert(vdD);
        check.insert(vdE);
        check.insert(vdF);
        check.insert(vdG);
        check.insert(vdH);
        CPPUNIT_ASSERT(test == check);
    }

    void test_vertices3 () {
        vertex_descriptor vdI = add_vertex(g);
        vertex_descriptor vdJ = add_vertex(g);
        add_edge(vdI, vdA, g);
        add_edge(vdB, vdA, g);
        add_edge(vdA, vdA, g);

        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        std::set<vertex_descriptor> test = std::set<vertex_descriptor> (b, e);
        std::set<vertex_descriptor> check = std::set<vertex_descriptor> ();
        check.insert(vdA);
        check.insert(vdB);
        check.insert(vdC);
        check.insert(vdD);
        check.insert(vdE);
        check.insert(vdF);
        check.insert(vdG);
        check.insert(vdH);
        check.insert(vdI);
        check.insert(vdJ);
        CPPUNIT_ASSERT(test == check);
    }

    // --------------
    // test_has_cycle
    // --------------

    void test_has_cycle1 () {
        CPPUNIT_ASSERT(has_cycle(g));
    }

    void test_has_cycle2 () {
        CPPUNIT_ASSERT(!has_cycle(g3));
        add_edge(vdA3, vdA3, g3);
        CPPUNIT_ASSERT(has_cycle(g3));
    }

    void test_has_cycle3 () {
        CPPUNIT_ASSERT(!has_cycle(g2));
    }

    void test_has_cycle4 () {
        add_edge(vdH3, vdA3, g3);
        CPPUNIT_ASSERT(has_cycle(g3));
    }

    // ---------------------
    // test_topological_sort
    // ---------------------

    void test_topological_sort1 () {
        std::ostringstream out;
        try{
            topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
            CPPUNIT_ASSERT(false);
        }catch(boost::not_a_dag){
            CPPUNIT_ASSERT(true);
        }
    }

    void test_topological_sort2 () {
        std::ostringstream out;
        topological_sort(g3, std::ostream_iterator<vertex_descriptor>(out, " "));
        //std::cout << std::endl << out.str() << std::endl;
        CPPUNIT_ASSERT(out.str() == "4 7 5 3 1 2 0 6 ");
    }

    void test_topological_sort3 () {
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        //std::cout << std::endl << out.str() << std::endl;
        CPPUNIT_ASSERT(out.str() == "");
        add_vertex(g2);
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        //std::cout << std::endl << out.str() << std::endl;
        CPPUNIT_ASSERT(out.str() == "0 ");
    }
        

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestGraph);


    CPPUNIT_TEST(test_add_edge1);
    CPPUNIT_TEST(test_add_edge2);
    CPPUNIT_TEST(test_add_edge3);
    CPPUNIT_TEST(test_add_edge4);

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
    CPPUNIT_TEST(test_has_cycle4);

    CPPUNIT_TEST(test_topological_sort1);
    CPPUNIT_TEST(test_topological_sort2);
    CPPUNIT_TEST(test_topological_sort3);

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
