#pragma once
#include "sparsematrix.h"
#include <cassert>

void matrix_tests() {
    SparseMatrix m{ 3, 3 };
    int          elem;

    assert(m.get_rows() == 3);
    assert(m.get_cols() == 3);

    m.modify(1, 1, 1);
    elem = m.elem(1, 1);
    assert(elem == 1);

    elem = m.elem(0, 0);
    assert(elem == 0);

    m.modify(0, 0, 1);
    elem = m.elem(0, 0);
    assert(elem == 1);

    m.modify(1, 1, 0);
    elem = m.elem(1, 1);
    assert(elem == 0);

    m.modify(1, 2, 1);
    elem = m.elem(1, 2);
    assert(elem == 1);

    m.modify(2, 1, 0);
    elem = m.elem(2, 1);
    assert(elem == 0);

    m.modify(2, 2, 1);
    elem = m.elem(2, 2);
    assert(elem == 1);

    SparseMatrix n{ 4, 5 };
    int          nbh_count;

    n.modify(0, 3, 1);
    n.modify(1, 1, 1);
    n.modify(1, 2, 1);
    n.modify(1, 3, 1);
    n.modify(1, 4, 1);
    n.modify(2, 1, 1);
    n.modify(2, 2, 1);
    n.modify(2, 3, 1);
    n.modify(3, 1, 1);
    n.modify(3, 2, 1);
    n.modify(3, 3, 1);
    n.modify(3, 4, 1);

    nbh_count = n.get_nbh_count(0, 0);
    assert(nbh_count == 1);

    nbh_count = n.get_nbh_count(0, 1);
    assert(nbh_count == 2);

    nbh_count = n.get_nbh_count(2, 0);
    assert(nbh_count == 3);

    nbh_count = n.get_nbh_count(0, 2);
    assert(nbh_count == 4);

    nbh_count = n.get_nbh_count(2, 4);
    assert(nbh_count == 5);

    nbh_count = n.get_nbh_count(1, 2);
    assert(nbh_count == 6);

    nbh_count = n.get_nbh_count(2, 3);
    assert(nbh_count == 7);

    nbh_count = n.get_nbh_count(2, 2);
    assert(nbh_count == 8);
}
