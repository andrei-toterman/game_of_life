#pragma once
#include "sparsematrix.h"
#include <cassert>

void matrix_tests() {
    try {
        SparseMatrix m{ 0, 0 };
        assert(false);
    } catch (...) { assert(true); }

    SparseMatrix m{ 3, 3 };

    assert(m.get_rows() == 3);
    assert(m.get_cols() == 3);

    for (int i = 0; i < m.get_rows(); ++i)
        for (int j = 0; j < m.get_cols(); ++j)
            assert(m.element(i, j) == 0);

    for (int i = 0; i < m.get_rows(); ++i)
        for (int j = 0; j < m.get_cols(); ++j)
            if ((i + j) % 2) m.modify(i, j, 1);

    for (int i = 0; i < m.get_rows(); ++i)
        for (int j = 0; j < m.get_cols(); ++j)
            assert(m.element(i, j) == (i + j) % 2);

    SparseMatrix n = m;
    for (int i = 0; i < m.get_rows(); ++i)
        for (int j = 0; j < m.get_cols(); ++j)
            assert(m.element(i, j) == n.element(i, j));

    assert(m.get_nbh_count(0, 0) == 2);
    assert(m.get_nbh_count(0, 1) == 2);
    assert(m.get_nbh_count(0, 2) == 2);
    assert(m.get_nbh_count(1, 0) == 2);
    assert(m.get_nbh_count(1, 1) == 4);
    assert(m.get_nbh_count(1, 2) == 2);
    assert(m.get_nbh_count(2, 0) == 2);
    assert(m.get_nbh_count(2, 2) == 2);

    try {
        m.element(-1, 0);
        assert(false);
    } catch (...) { assert(true); }

    try {
        m.element(0, -1);
        assert(false);
    } catch (...) { assert(true); }

    try {
        m.modify(0, -1, 0);
        assert(false);
    } catch (...) { assert(true); }

    try {
        m.modify(-1, 0, 0);
        assert(false);
    } catch (...) { assert(true); }

    m.clear();
    for (int i = 0; i < m.get_rows(); ++i)
        for (int j = 0; j < m.get_cols(); ++j)
            assert(m.element(i, j) == 0);
}
