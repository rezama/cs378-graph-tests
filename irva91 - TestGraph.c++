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
        
        TO TEST ON MY LAPTOP:
        g++ -ansi -pedantic -ldl TestGraph.c++ -lcppunit -o TestGraph.c++.app
        valgrind ./TestGraph.c++.app >& TestGraph.c++.out
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
            edGH = add_edge(vdG, vdH, g).first;}

        // -------------
        // test_add_edge
        // -------------

        void test_add_edge () {
            std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
            CPPUNIT_ASSERT(p.first  == edAB);
            CPPUNIT_ASSERT(p.second == false);}

        //BEGINNING OF OUR TESTS

        void test_add_edge_1 () {
            std::pair<edge_descriptor, bool> p = add_edge(vdA, vdD, g);
            CPPUNIT_ASSERT(p.second == true);}

        //DO NOT CHANGE THIS TEST
        //IT IS SUPPOSED TO BE THE SAME AST TEST1 BECAUSE IT'S TESTING THAT
        //TEST1 DIDN'T CHANGE g
        void test_add_edge_2 () {
            std::pair<edge_descriptor, bool> p = add_edge(vdA, vdD, g);
            CPPUNIT_ASSERT(p.second == true);}
        
        void test_add_edge_3 () {
            std::pair<edge_descriptor, bool> p = add_edge(add_vertex(g), add_vertex(g), g);
            CPPUNIT_ASSERT(p.second == true);}
        
        //This is testing to make sure that adding a self-loop is possible
        void test_add_edge_4 () {
            std::pair<edge_descriptor, bool> p = add_edge(vdA, vdA, g);
            CPPUNIT_ASSERT(p.second == true);}

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

        //BEGINNING OF OUR TESTS

        void test_adjacent_vertices_1 () {
            vertex_descriptor vd1 = add_vertex(g);
            vertex_descriptor vd2 = add_vertex(g);
            add_edge(vd1, vd2, g);
            std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vd1, g);
            adjacency_iterator b = p.first;
            adjacency_iterator e = p.second;
            CPPUNIT_ASSERT(b != e);
            CPPUNIT_ASSERT(*b == vd2);
            CPPUNIT_ASSERT(++b == e);
        }

        void test_adjacent_vertices_2 () {
            vertex_descriptor vd1 = add_vertex(g);
            add_edge(vd1, vd1, g);
            std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vd1, g);
            adjacency_iterator b = p.first;
            adjacency_iterator e = p.second;
            CPPUNIT_ASSERT(b != e);
            CPPUNIT_ASSERT(*b == vd1);
            CPPUNIT_ASSERT(++b == e);
        }

        void test_adjacent_vertices_3() {
            int num_to_add = 10;
            vertex_descriptor root = add_vertex(g);
            for(int i = 0; i < num_to_add; ++i)
            {
                add_edge(root, add_vertex(g), g);//NOTE: THE ORDER IS VERY IMPORTANT
            }
            std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(root, g);
            std::pair<adjacency_iterator, adjacency_iterator> q = adjacent_vertices(root, g);
            CPPUNIT_ASSERT(p == q);
            adjacency_iterator b = p.first;
            adjacency_iterator e = p.second;
            CPPUNIT_ASSERT(b != e);
            for(int i = 1; i < num_to_add; ++i)
            {
                ++b;
            }
            CPPUNIT_ASSERT(b != e);
            CPPUNIT_ASSERT(++b == e);
        }
        
        void test_adjacent_vertices_4() {
            vertex_descriptor root = add_vertex(g);
            vertex_descriptor ad1 = add_vertex(g);
            vertex_descriptor ad2 = add_vertex(g);
            vertex_descriptor ad3 = add_vertex(g);
            
            add_edge(root, ad1, g);
            add_edge(root, ad2, g);
            add_edge(root, ad3, g);
            // add_edge(ad3, root, g); NOTE: If we replaced the one above with this one then the test would fail
            // because it would see root as having 2 adjacent vertices instead of 3
            std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(root, g);
            adjacency_iterator b = p.first;
            adjacency_iterator e = p.second;
            CPPUNIT_ASSERT(b != e);
            ++b;
            CPPUNIT_ASSERT(b != e);
            ++b;
            ++b;
            CPPUNIT_ASSERT(b == e);
        }
        
        // ---------
        // test_edge
        // ---------

        void test_edge () {
            std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
            CPPUNIT_ASSERT(p.first  == edAB);
            CPPUNIT_ASSERT(p.second == true);}

        //BEGINNING OF OUR TESTS

        void test_edge_1 () {
            std::pair<edge_descriptor, bool> p = edge(vdG, vdH, g);
            CPPUNIT_ASSERT(p.second == true);}

        void test_edge_2 () {
            vertex_descriptor ad1 = add_vertex(g);
            vertex_descriptor ad2 = add_vertex(g);
            std::pair<edge_descriptor, bool> p = edge(ad1, ad2, g);
            CPPUNIT_ASSERT(p.second == false);}

        void test_edge_3 () {
            std::pair<edge_descriptor, bool> p = edge(add_vertex(g), add_vertex(g), g);
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
            if (b != e) {
                edge_descriptor ed = *b;
                CPPUNIT_ASSERT(ed == edAC);}}

        //BEGINNING OF OUR TESTS

        void test_edges_1 () {
            std::pair<edge_iterator, edge_iterator> p = edges(g);
            edge_iterator                           b = p.first;
            edge_iterator                           e = p.second;
            CPPUNIT_ASSERT(b != e);
            add_edge(add_vertex(g), add_vertex(g), g);
            std::pair<edge_iterator, edge_iterator> q = edges(g);
            CPPUNIT_ASSERT(p != q);
        }

        void test_edges_2 () {
            std::pair<edge_iterator, edge_iterator> p = edges(g);
            edge_iterator                           b = p.first;
            edge_iterator                           e = p.second;
            CPPUNIT_ASSERT(b != e);
            add_edge(vdA, vdB, g);
            std::pair<edge_iterator, edge_iterator> q = edges(g);
            CPPUNIT_ASSERT(p == q);
        }

        void test_edges_3 () {
            std::pair<edge_iterator, edge_iterator> p = edges(g);
            edge_iterator                           b = p.first;
            edge_iterator                           e = p.second;
            CPPUNIT_ASSERT(b != e);
            add_edge(add_vertex(g), add_vertex(g), g);
            std::pair<edge_iterator, edge_iterator> q = edges(g);
            edge_iterator                           b2 = q.first;
            edge_iterator                           e2 = q.second;
            CPPUNIT_ASSERT(b2 != e2);
            CPPUNIT_ASSERT(e != e2);
            CPPUNIT_ASSERT(p != q);
        }


        // --------------
        // test_num_edges
        // --------------

        void test_num_edges () {
            edges_size_type es = num_edges(g);
            CPPUNIT_ASSERT(es == 11);}

        //BEGINNING OF OUR TESTS

        void test_num_edges_1 () {
            edges_size_type es = num_edges(g);
            CPPUNIT_ASSERT(es == 11);
            add_edge(add_vertex(g), add_vertex(g), g);
            edges_size_type es2 = num_edges(g);
            CPPUNIT_ASSERT(es2 == 12);
        }

        void test_num_edges_2 () {
            vertex_descriptor v1  = add_vertex(g);
            vertex_descriptor v2  = add_vertex(g);
            edges_size_type es = num_edges(g);
            CPPUNIT_ASSERT(es == 11);
            add_edge(v1, v2, g);
            CPPUNIT_ASSERT(es == 11);
            es = num_edges(g);
            CPPUNIT_ASSERT(es == 12);
        }

        void test_num_edges_3 () {
            edges_size_type es = num_edges(g);
            CPPUNIT_ASSERT(es == 11);
            add_edge(vdC, vdD, g);
            CPPUNIT_ASSERT(es == 11);
            es = num_edges(g);
            CPPUNIT_ASSERT(es == 11);
       }

        // -----------------
        // test_num_vertices
        // -----------------

        void test_num_vertices () {
            vertices_size_type vs = num_vertices(g);
            CPPUNIT_ASSERT(vs == 8);}

        //BEGINNING OF OUR TESTS

        void test_num_vertices_1 () {
            add_vertex(g);
            vertices_size_type vs = num_vertices(g);
            CPPUNIT_ASSERT(vs == 9);
            add_vertex(g);
            vs = num_vertices(g);
            CPPUNIT_ASSERT(vs == 10);}

        void test_num_vertices_2 () {
            graph_type b;
            add_vertex(b);
            add_vertex(b);
            vertices_size_type vs = num_vertices(b);
            CPPUNIT_ASSERT(vs == 2);
            add_vertex(b);
            vs = num_vertices(b);
            CPPUNIT_ASSERT(vs == 3);}

        void test_num_vertices_3 () {
            graph_type b;
            vertices_size_type vs = num_vertices(b);
            CPPUNIT_ASSERT(vs == 0);
            add_vertex(b);
            vs = num_vertices(b);
            CPPUNIT_ASSERT(vs == 1);
            add_vertex(b);
            add_vertex(b);
            add_vertex(b);
            add_vertex(b);
            vs = num_vertices(b);
            CPPUNIT_ASSERT(vs == 5);}

        // -----------
        // test_source
        // -----------

        void test_source () {
            vertex_descriptor vd = source(edAB, g);
            CPPUNIT_ASSERT(vd == vdA);}

        //BEGINNING OF OUR TESTS

        void test_source_1 () {
            vertex_descriptor vd = source(edDF, g);
            CPPUNIT_ASSERT(vd == vdD);
            vd = source(edFD, g);
            CPPUNIT_ASSERT(vd == vdF);}

        void test_source_2 () {
            graph_type b;
            vertex_descriptor v1 = add_vertex(b);
            vertex_descriptor v2 = add_vertex(b);
            edge_descriptor ed = add_edge(v1, v2, b).first;
            vertex_descriptor vd = source(ed, g);
            CPPUNIT_ASSERT(vd == v1);}

        void test_source_3 () {
            graph_type b;
            vertex_descriptor v1 = add_vertex(b);
            edge_descriptor ed = add_edge (v1, v1, b).first;
            vertex_descriptor vd = source(ed, g);
            CPPUNIT_ASSERT(vd == v1);
            vertex_descriptor v2 = add_vertex(b);
            edge_descriptor ed1 = add_edge (v1, v2, b).first;
            vd = source(ed1, g);
            CPPUNIT_ASSERT(vd == v1);}

        // -----------
        // test_target
        // -----------

        void test_target () {
            vertex_descriptor vd = target(edAB, g);
            CPPUNIT_ASSERT(vd == vdB);}

        //BEGINNING OF OUR TESTS

        void test_target_1 () {
            vertex_descriptor vd = target(edDF, g);
            CPPUNIT_ASSERT(vd == vdF);
            vd = target(edFD, g);
            CPPUNIT_ASSERT(vd == vdD);}

        void test_target_2 () {
            graph_type b;
            vertex_descriptor v1 = add_vertex(b);
            vertex_descriptor v2 = add_vertex(b);
            edge_descriptor ed = add_edge(v1, v2, b).first;
            vertex_descriptor vd = target(ed, g);
            CPPUNIT_ASSERT(vd == v2);}

        void test_target_3 () {
            graph_type b;
            vertex_descriptor v1 = add_vertex(b);
            edge_descriptor ed = add_edge (v1, v1, b).first;
            vertex_descriptor vd = target(ed, g);
            CPPUNIT_ASSERT(vd == v1);
            vertex_descriptor v2 = add_vertex(b);
            edge_descriptor ed1 = add_edge (v1, v2, b).first;
            vd = target(ed1, g);
            CPPUNIT_ASSERT(vd == v2);}


        // -----------
        // test_vertex
        // -----------

        void test_vertex () {
            vertex_descriptor vd = vertex(0, g);
            CPPUNIT_ASSERT(vd == vdA);}

        //BEGINNING OF OUR TEST

        void test_vertex_1 () {
            vertex_descriptor vd = vertex(1, g);
            CPPUNIT_ASSERT(vd == vdB);}

        void test_vertex_2 () {
            graph_type b;
            vertex_descriptor v1 = add_vertex(b);
            vertex_descriptor vd = vertex(0, g);
            CPPUNIT_ASSERT(vd == v1);
            vertex_descriptor v2 = add_vertex(b);
            vd = vertex(1, g);
            CPPUNIT_ASSERT(vd == v2);}

        void test_vertex_3 () {
            graph_type b;
            vertex_descriptor v1 = add_vertex(b);
            vertex_descriptor vd = vertex(0, g);
            CPPUNIT_ASSERT(vd == v1);
            add_vertex(b);
            add_vertex(b);
            add_vertex(b);
            add_vertex(b);
            add_vertex(b);
            vertex_descriptor v2 = add_vertex(b);
            vd = vertex(6, g);
            CPPUNIT_ASSERT(vd == v2);}

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
            if (b != e) {
                vertex_descriptor vd = *b;
                CPPUNIT_ASSERT(vd == vdB);}}                        

        //BEGINNING OF OUR TESTS

        void test_vertices_1 () {
            std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
            vertex_iterator                             b = p.first;
            vertex_iterator                             e = p.second;
            CPPUNIT_ASSERT(b != e);
            ++b;
            if (b != e) {
                vertex_descriptor vd = *b;
                CPPUNIT_ASSERT(vd == vdB);}
            ++b;
            ++b;
            if (b != e) {
                vertex_descriptor vd = *b;
                CPPUNIT_ASSERT(vd == vdD);}}

        void test_vertices_2 () {
            graph_type k;
            std::pair<vertex_iterator, vertex_iterator> p = vertices(k);
            vertex_iterator                             b = p.first;
            vertex_iterator                             e = p.second;
            CPPUNIT_ASSERT(b == e);
            vertex_descriptor v1 = add_vertex(k);
            p = vertices(k);
            b = p.first;
            e = p.second;
            if (b != e) {
                vertex_descriptor vd = *b;
                CPPUNIT_ASSERT(vd == v1);}}

        void test_vertices_3 () {
            graph_type k;
            vertex_descriptor v1 = add_vertex(k);
            add_vertex(k);
            add_vertex(k);
            add_vertex(k);
            vertex_descriptor v2 = add_vertex(k);
            std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
            vertex_iterator                             b = p.first;
            vertex_iterator                             e = p.second;
            CPPUNIT_ASSERT(b != e);
            if (b != e) {
                vertex_descriptor vd = *b;
                CPPUNIT_ASSERT(vd == v1);}
            b = b + 4;
            if (b != e) {
                vertex_descriptor vd = *b;
                CPPUNIT_ASSERT(vd == v2);}}

        // --------------
        // test_has_cycle
        // --------------

        void test_has_cycle () {
            CPPUNIT_ASSERT(has_cycle(g));}

        //BEGINNING OF OUR TESTS

         void test_has_cycle_1 () {
            graph_type k;
            vertex_descriptor v1 = add_vertex(k);
            CPPUNIT_ASSERT(!has_cycle(k));
            vertex_descriptor v2 = add_vertex(k);
            CPPUNIT_ASSERT(!has_cycle(k));
            vertex_descriptor v3 = add_vertex(k);
            CPPUNIT_ASSERT(!has_cycle(k));
            add_edge(v1, v2, k).first;
            CPPUNIT_ASSERT(!has_cycle(k));
            add_edge(v1, v3, k).first;
            CPPUNIT_ASSERT(!has_cycle(k));}

         void test_has_cycle_2 () {
            graph_type k;
            vertex_descriptor v1 = add_vertex(k);
            vertex_descriptor v2 = add_vertex(k);
            vertex_descriptor v3 = add_vertex(k);
            add_edge(v1, v2, k).first;
            add_edge(v2, v3, k).first;
            add_edge(v3, v1, k).first;
            CPPUNIT_ASSERT(has_cycle(g));}

         void test_has_cycle_3 () {
            graph_type k;
            vertex_descriptor v1 = add_vertex(k);
            vertex_descriptor v2 = add_vertex(k);
            vertex_descriptor v3 = add_vertex(k);
            vertex_descriptor v4 = add_vertex(k);
            add_edge(v1, v2, k).first;
            add_edge(v2, v3, k).first;
            add_edge(v3, v4, k).first;
            add_edge(v4, v1, k).first;
            CPPUNIT_ASSERT(has_cycle(g));}

        // ---------------------
        // test_topological_sort
        // ---------------------

        //BEGINNING OF OUR TESTS

        void test_topological_sort_1 () {
        graph_type b;
        vertex_descriptor v1  = add_vertex(b);
        vertex_descriptor v2  = add_vertex(b);
        vertex_descriptor v3  = add_vertex(b);
        edge_descriptor eAB = add_edge(v1, v2, b).first;
        edge_descriptor eAC = add_edge(v1, v3, b).first;
        std::ostringstream out;
        topological_sort(b, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "1 2 0 ");}

        void test_topological_sort_2 () {
        graph_type b;
        vertex_descriptor v1  = add_vertex(b);
        vertex_descriptor v2  = add_vertex(b);
        vertex_descriptor v3  = add_vertex(b);
        edge_descriptor eAB = add_edge(v1, v2, b).first;
        edge_descriptor eAC = add_edge(v2, v3, b).first;
        std::ostringstream out;
        topological_sort(b, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "2 1 0 ");}

        void test_topological_sort_3 () {
        graph_type b;
        vertex_descriptor v1  = add_vertex(b);
        vertex_descriptor v2  = add_vertex(b);
        vertex_descriptor v3  = add_vertex(b);
        edge_descriptor eAB = add_edge(v3, v2, b).first;
        edge_descriptor eAC = add_edge(v2, v1, b).first;
        std::ostringstream out;
        topological_sort(b, std::ostream_iterator<vertex_descriptor>(out, " "));
        CPPUNIT_ASSERT(out.str() == "0 1 2 ");}
            
        
        
        //THE FOLLOWING TESTS WERE NOT INCLUDED IN THIS FILE
        
        // ---------------
        // test_add_vertex
        // ---------------

        void test_add_vertex_1 () {
            vertices_size_type oldSize = num_vertices(g);
            CPPUNIT_ASSERT(oldSize == 8);
            add_vertex(g);
            CPPUNIT_ASSERT(oldSize != num_vertices(g));
            CPPUNIT_ASSERT(oldSize < num_vertices(g));
            CPPUNIT_ASSERT(oldSize == 8);
            CPPUNIT_ASSERT(num_vertices(g) == 9);
        }
        
        void test_add_vertex_2 () {
            vertices_size_type oldSize = num_vertices(g);
            CPPUNIT_ASSERT(oldSize == 8);
            add_vertex(g);
            add_vertex(g);
            add_vertex(g);
            add_vertex(g);
            add_vertex(g);
            add_vertex(g);
            add_vertex(g);
            add_vertex(g);
            add_vertex(g);
            CPPUNIT_ASSERT(oldSize != num_vertices(g));
            CPPUNIT_ASSERT(oldSize < num_vertices(g));
            CPPUNIT_ASSERT(oldSize == 8);
            CPPUNIT_ASSERT(num_vertices(g) == 17);
        }
        
        void test_add_vertex_3 () {
            vertices_size_type oldSize = num_vertices(g);
            CPPUNIT_ASSERT(oldSize == 8);
            for(int i = oldSize; i > 0; --i)
            {
                add_vertex(g);
            }
            CPPUNIT_ASSERT(oldSize != num_vertices(g));
            CPPUNIT_ASSERT(oldSize < num_vertices(g));
            CPPUNIT_ASSERT(oldSize == 8);
            CPPUNIT_ASSERT(num_vertices(g) == oldSize * 2);
        }

        // -----
        // suite
        // -----

        CPPUNIT_TEST_SUITE(TestGraph);
        
        //add edge
        CPPUNIT_TEST(test_add_edge);
        CPPUNIT_TEST(test_add_edge_1);
        CPPUNIT_TEST(test_add_edge_2);
        CPPUNIT_TEST(test_add_edge_3);
        CPPUNIT_TEST(test_add_edge_4);
        
        //adjacent vertices
        CPPUNIT_TEST(test_adjacent_vertices);
        CPPUNIT_TEST(test_adjacent_vertices_1);
        CPPUNIT_TEST(test_adjacent_vertices_2);
        CPPUNIT_TEST(test_adjacent_vertices_3);
        CPPUNIT_TEST(test_adjacent_vertices_4);
        
        //edge
        CPPUNIT_TEST(test_edge);
        CPPUNIT_TEST(test_edge_1);
        CPPUNIT_TEST(test_edge_2);
        CPPUNIT_TEST(test_edge_3);
        
        //edges
        CPPUNIT_TEST(test_edges);
        CPPUNIT_TEST(test_edges_1);
        CPPUNIT_TEST(test_edges_2);
        CPPUNIT_TEST(test_edges_3);
        
        //num edges
        CPPUNIT_TEST(test_num_edges);
        CPPUNIT_TEST(test_num_edges_1);
        CPPUNIT_TEST(test_num_edges_2);
        CPPUNIT_TEST(test_num_edges_3);
        
        //num vertices
        CPPUNIT_TEST(test_num_vertices);
        CPPUNIT_TEST(test_num_vertices_1);
        CPPUNIT_TEST(test_num_vertices_2);
        CPPUNIT_TEST(test_num_vertices_3);
        
        //source
        CPPUNIT_TEST(test_source);
        CPPUNIT_TEST(test_source_1);
        CPPUNIT_TEST(test_source_2);
        CPPUNIT_TEST(test_source_3);
        
        //target
        CPPUNIT_TEST(test_target);
        CPPUNIT_TEST(test_target_1);
        CPPUNIT_TEST(test_target_2);
        CPPUNIT_TEST(test_target_3);
        
        //vertex
        CPPUNIT_TEST(test_vertex);
        CPPUNIT_TEST(test_vertex_1);
        CPPUNIT_TEST(test_vertex_2);
        CPPUNIT_TEST(test_vertex_3);
        
        //vertices
        CPPUNIT_TEST(test_vertices);
        CPPUNIT_TEST(test_vertices_1);
        CPPUNIT_TEST(test_vertices_2);
        CPPUNIT_TEST(test_vertices_3);
        
        //has cycle
        CPPUNIT_TEST(test_has_cycle);
        CPPUNIT_TEST(test_has_cycle_1);
        CPPUNIT_TEST(test_has_cycle_2);
        CPPUNIT_TEST(test_has_cycle_3);

        //add vertex
        CPPUNIT_TEST(test_add_vertex_1);
        CPPUNIT_TEST(test_add_vertex_2);
        CPPUNIT_TEST(test_add_vertex_3);
        
        //topological sort
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
        //tr.addTest(TestGraph< adjacency_list<setS, vecS, directedS> >::suite());
        tr.addTest(TestGraph<Graph>::suite()); // uncomment
        tr.run();

        cout << "Done." << endl;
        return 0;}