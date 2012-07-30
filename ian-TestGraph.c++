// ----------------------------
// projects/graph/TestGraph.c++
// Copyright(C) 2012
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

template <typename T>
struct TestGraph : CppUnit::TestFixture {

    typedef T                                       graph_type;

    typedef typename graph_type::vertex_descriptor  vertex_descriptor;
    typedef typename graph_type::edge_descriptor    edge_descriptor;

    typedef typename graph_type::vertex_iterator    vertex_iterator;
    typedef typename graph_type::edge_iterator      edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type    edges_size_type;

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

    void setUp() {
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
    }

    void test_add_edge_failure() {
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_add_edge_success() {
        graph_type g2 = g;
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdD, g2);
        CPPUNIT_ASSERT(source(p.first, g2) == vdA);
        CPPUNIT_ASSERT(target(p.first, g2) == vdD);
        CPPUNIT_ASSERT(p.second == true);
    }

    void test_add_edge_reflexive() {
        graph_type g2 = g;
        std::pair<edge_descriptor, bool> p = add_edge(vdA, vdA, g2);
        CPPUNIT_ASSERT(source(p.first, g2) == vdA);
        CPPUNIT_ASSERT(target(p.first, g2) == vdA);
        CPPUNIT_ASSERT(p.second == true);
    }

    void test_adjacent_vertices() {
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
        adjacency_iterator b = p.first;
        adjacency_iterator e = p.second;

        CPPUNIT_ASSERT(b != e);
        if(b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB);
        }
        ++b;
        if(b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdC);
        }
    }

    void test_adjacent_vertices_reflexive() {
        graph_type g2 = g;
        add_edge(vdA, vdA, g2);
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g2);

        set<vertex_descriptor> expected;
        expected.insert(vdA);
        expected.insert(vdB);
        expected.insert(vdC);
        expected.insert(vdE);

        set<vertex_descriptor> actual = set<vertex_descriptor>(p.first, p.second);

        CPPUNIT_ASSERT(expected == actual);
    }

    void test_adjacent_vertices_directed() {
        graph_type g2 = g;
        std::pair<adjacency_iterator, adjacency_iterator> pA = adjacent_vertices(vdA, g2);
        std::pair<adjacency_iterator, adjacency_iterator> pB = adjacent_vertices(vdB, g2);

        set<vertex_descriptor> adjacent_to_A = set<vertex_descriptor>(pA.first, pA.second);
        set<vertex_descriptor> adjacent_to_B = set<vertex_descriptor>(pB.first, pB.second);

        CPPUNIT_ASSERT(adjacent_to_A.count(vdB) == 1);
        CPPUNIT_ASSERT(adjacent_to_B.count(vdA) == 0);
    }

    void test_adjacent_vertices_empty() {
        graph_type g2 = g;
        add_vertex(g2);
        vertex_descriptor v = add_vertex(g2);
        add_vertex(g2);
        std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(v, g2);

        CPPUNIT_ASSERT(p.first == p.second);
    }

    void test_edge_success() {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
        CPPUNIT_ASSERT(p.first  == edAB);
        CPPUNIT_ASSERT(p.second == true);
    }

    void test_edge_failure() {
        std::pair<edge_descriptor, bool> p = edge(vdA, vdD, g);
        CPPUNIT_ASSERT(p.second == false);
    }

    void test_edge_reflexive() {
        graph_type g2 = g;
        std::pair<edge_descriptor, bool> p = edge(vdA, vdA, g2);
        CPPUNIT_ASSERT(p.second == false);
        add_edge(vdA, vdA, g2);
        p = edge(vdA, vdA, g2);
        CPPUNIT_ASSERT(source(p.first, g2) == vdA);
        CPPUNIT_ASSERT(target(p.first, g2) == vdA);
        CPPUNIT_ASSERT(p.second == true);
    }

    void test_edges() {
        std::pair<edge_iterator, edge_iterator> p = edges(g);
        edge_iterator                           b = p.first;
        edge_iterator                           e = p.second;
        CPPUNIT_ASSERT(b != e);
        if(b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAB);
        }
        ++b;
        if(b != e) {
            edge_descriptor ed = *b;
            CPPUNIT_ASSERT(ed == edAC);
        }
    }

    void test_edges_empty() {
        graph_type g2;
        std::pair<edge_iterator, edge_iterator> p = edges(g2);
        CPPUNIT_ASSERT(p.first == p.second);
    }

    void test_edges_empty_with_nodes() {
        graph_type g2;
        add_vertex(g2);
        add_vertex(g2);
        std::pair<edge_iterator, edge_iterator> p = edges(g2);
        CPPUNIT_ASSERT(p.first == p.second);
        set<edge_descriptor> edge_set(p.first, p.second);
        CPPUNIT_ASSERT_EQUAL((edges_size_type)0, edge_set.size());
    }

    void test_edges_reflexive() {
        graph_type g2 = g;
        edge_descriptor edAA = add_edge(vdA, vdA, g2).first;
        std::pair<edge_iterator, edge_iterator> p = edges(g2);

        set<edge_descriptor> edge_set(p.first, p.second);

        CPPUNIT_ASSERT(edge_set.count(edAA) == 1);
    }

    void test_num_edges() {
        CPPUNIT_ASSERT_EQUAL((edges_size_type)11, num_edges(g));
    }

    void test_num_edges_empty() {
        CPPUNIT_ASSERT_EQUAL((edges_size_type)0, num_edges(graph_type()));
    }

    void test_num_edges_after_adding() {
        graph_type g2 = g;
        CPPUNIT_ASSERT_EQUAL((edges_size_type)11, num_edges(g2));
        add_edge(vdA, vdA, g2);
        CPPUNIT_ASSERT_EQUAL((edges_size_type)12, num_edges(g2));
    }

    void test_num_vertices() {
        CPPUNIT_ASSERT_EQUAL((vertices_size_type)8, num_vertices(g));
    }

    void test_num_vertices_empty() {
        CPPUNIT_ASSERT_EQUAL((vertices_size_type)0, num_vertices(graph_type()));
    }

    void test_num_vertices_after_adding() {
        graph_type g2 = g;
        CPPUNIT_ASSERT_EQUAL((vertices_size_type)8, num_vertices(g2));
        add_vertex(g2);
        CPPUNIT_ASSERT_EQUAL((vertices_size_type)9, num_vertices(g2));
    }

    void test_source() {
        vertex_descriptor vd = source(edAB, g);
        CPPUNIT_ASSERT(vd == vdA);
    }

    void test_source_reflexive() {
        graph_type g2 = g;
        edge_descriptor edAA = add_edge(vdA, vdA, g2).first;
        CPPUNIT_ASSERT(source(edAA, g) == vdA);
    }

    void test_target() {
        vertex_descriptor vd = target(edAB, g);
        CPPUNIT_ASSERT(vd == vdB);
    }

    void test_target_reflexive() {
        graph_type g2 = g;
        edge_descriptor edAA = add_edge(vdA, vdA, g2).first;
        CPPUNIT_ASSERT(target(edAA, g) == vdA);
    }

    void test_vertex() {
        vertex_descriptor vd = vertex(0, g);
        CPPUNIT_ASSERT(vd == vdA);
    }

    void test_vertices() {
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
        vertex_iterator                             b = p.first;
        vertex_iterator                             e = p.second;
        CPPUNIT_ASSERT(b != e);
        if(b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdA);
        }
        ++b;
        if(b != e) {
            vertex_descriptor vd = *b;
            CPPUNIT_ASSERT(vd == vdB);
        }
    }

    void test_vertices_empty() {
        graph_type g2;
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g2);
        CPPUNIT_ASSERT(p.first == p.second);
    }

    void test_vertices_one() {
        graph_type g2;
        vertex_descriptor v = add_vertex(g2);
        std::pair<vertex_iterator, vertex_iterator> p = vertices(g2);
        CPPUNIT_ASSERT(*p.first == v);
        ++p.first;
        CPPUNIT_ASSERT(p.first == p.second);

    }

    void test_has_cycle() {
        CPPUNIT_ASSERT(has_cycle(g));
    }

    void test_has_cycle_cyclic_one_element() {
        graph_type g2;
        vertex_descriptor v = add_vertex(g2);
        add_edge(v, v, g2);

        CPPUNIT_ASSERT(has_cycle(g2));
    }

    void test_has_cycle_cyclic_two_elements() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(b, a, g2);

        CPPUNIT_ASSERT(has_cycle(g2));
    }

    void test_has_cycle_cyclic_three_elements() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        vertex_descriptor c = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(b, c, g2);
        add_edge(c, a, g2);

        CPPUNIT_ASSERT(has_cycle(g2));
    }

    void test_has_cycle_cyclic_disjoint() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        vertex_descriptor c = add_vertex(g2);
        vertex_descriptor d = add_vertex(g2);
        vertex_descriptor e = add_vertex(g2);
        vertex_descriptor f = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(a, c, g2);
        add_edge(d, e, g2);
        add_edge(d, f, g2);
        add_edge(f, a, g2);
        add_edge(a, d, g2);

        CPPUNIT_ASSERT(has_cycle(g2));
    }

    void test_has_cycle_acyclic_zero_elements() {
        graph_type g2;
        CPPUNIT_ASSERT(!has_cycle(g2));
    }

    void test_has_cycle_acyclic_one_element() {
        graph_type g2;
        add_vertex(g2);
        CPPUNIT_ASSERT(!has_cycle(g2));
    }

    void test_has_cycle_acyclic_two_elements() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        add_edge(a, b, g2);

        CPPUNIT_ASSERT(!has_cycle(g2));
    }

    void test_has_cycle_acyclic_three_elements() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        vertex_descriptor c = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(b, c, g2);

        CPPUNIT_ASSERT(!has_cycle(g2));
    }

    void test_has_cycle_acyclic_disjoint() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        vertex_descriptor c = add_vertex(g2);
        vertex_descriptor d = add_vertex(g2);
        vertex_descriptor e = add_vertex(g2);
        vertex_descriptor f = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(a, c, g2);
        add_edge(d, e, g2);
        add_edge(d, f, g2);

        CPPUNIT_ASSERT(!has_cycle(g2));
    }

    void test_topological_sort_throws_exception_for_cyclic_graph() {
        std::ostringstream out;
        CPPUNIT_ASSERT_THROW(topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " ")), boost::not_a_dag);
    }

    void test_topological_sort_disjoint() {
        graph_type g2;
        add_vertex(g2);
        add_vertex(g2);
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT_EQUAL(string("0 1 "), out.str());
    }

    void test_topological_sort_trivial_two_elements() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        add_edge(a, b, g2);
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT_EQUAL(string("1 0 "), out.str());
    }

    void test_topological_sort_trivial_three_elements() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        vertex_descriptor c = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(b, c, g2);
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT_EQUAL(string("2 1 0 "), out.str());
    }

    void test_topological_sort_three_elements() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        vertex_descriptor c = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(a, c, g2);
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT_EQUAL(string("1 2 0 "), out.str());
    }

    void test_topological_sort_complex() {
        graph_type g2;
        vertex_descriptor a = add_vertex(g2);
        vertex_descriptor b = add_vertex(g2);
        vertex_descriptor c = add_vertex(g2);
        vertex_descriptor d = add_vertex(g2);
        add_edge(a, b, g2);
        add_edge(a, c, g2);
        add_edge(a, d, g2);
        add_edge(b, c, g2);
        add_edge(d, b, g2);
        std::ostringstream out;
        topological_sort(g2, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT_EQUAL(string("2 1 3 0 "), out.str());
    }

    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(test_add_edge_failure);
    CPPUNIT_TEST(test_add_edge_success);
    CPPUNIT_TEST(test_add_edge_reflexive);
    CPPUNIT_TEST(test_adjacent_vertices);
    CPPUNIT_TEST(test_adjacent_vertices_reflexive);
    CPPUNIT_TEST(test_adjacent_vertices_directed);
    CPPUNIT_TEST(test_adjacent_vertices_empty);
    CPPUNIT_TEST(test_edge_success);
    CPPUNIT_TEST(test_edge_failure);
    CPPUNIT_TEST(test_edge_reflexive);
    CPPUNIT_TEST(test_edges);
    CPPUNIT_TEST(test_edges_reflexive);
    CPPUNIT_TEST(test_edges_empty);
    CPPUNIT_TEST(test_edges_empty_with_nodes);
    CPPUNIT_TEST(test_num_edges);
    CPPUNIT_TEST(test_num_edges_empty);
    CPPUNIT_TEST(test_num_edges_after_adding);
    CPPUNIT_TEST(test_num_vertices);
    CPPUNIT_TEST(test_num_vertices_empty);
    CPPUNIT_TEST(test_num_vertices_after_adding);
    CPPUNIT_TEST(test_source);
    CPPUNIT_TEST(test_source_reflexive);
    CPPUNIT_TEST(test_target);
    CPPUNIT_TEST(test_vertex);
    CPPUNIT_TEST(test_vertices);
    CPPUNIT_TEST(test_vertices_empty);
    CPPUNIT_TEST(test_vertices_one);
    CPPUNIT_TEST(test_has_cycle);
    CPPUNIT_TEST(test_has_cycle_cyclic_one_element);
    CPPUNIT_TEST(test_has_cycle_cyclic_two_elements);
    CPPUNIT_TEST(test_has_cycle_cyclic_three_elements);
    CPPUNIT_TEST(test_has_cycle_cyclic_disjoint);
    CPPUNIT_TEST(test_has_cycle_acyclic_zero_elements);
    CPPUNIT_TEST(test_has_cycle_acyclic_one_element);
    CPPUNIT_TEST(test_has_cycle_acyclic_two_elements);
    CPPUNIT_TEST(test_has_cycle_acyclic_three_elements);
    CPPUNIT_TEST(test_has_cycle_acyclic_disjoint);
    CPPUNIT_TEST(test_topological_sort_throws_exception_for_cyclic_graph);
    CPPUNIT_TEST(test_topological_sort_disjoint);
    CPPUNIT_TEST(test_topological_sort_trivial_two_elements);
    CPPUNIT_TEST(test_topological_sort_trivial_three_elements);
    CPPUNIT_TEST(test_topological_sort_three_elements);
    CPPUNIT_TEST(test_topological_sort_complex);
    CPPUNIT_TEST_SUITE_END();
};


int main() {
    using namespace std;
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
