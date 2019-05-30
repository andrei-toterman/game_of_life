#include "sparsematrix.h"

#include <cstdlib>
#include <stdexcept>

void SparseMatrix::insert_last(int row, int col, int val) {
    Node* new_node = new Node{ row, col, val };
    new_node->prev = this->tail;
    if (this->head == nullptr) {
        this->head = new_node;
        this->tail = new_node;
    } else {
        this->tail->next = new_node;
        this->tail       = new_node;
    }
}

void SparseMatrix::insert_first(int row, int col, int val) {
    Node* new_node = new Node{ row, col, val };
    new_node->next = this->head;
    if (this->tail == nullptr) {
        this->head = new_node;
        this->tail = new_node;
    } else {
        this->head->prev = new_node;
        this->head       = new_node;
    }
}

void SparseMatrix::insert_before(Node* current_node, int row, int col, int val) {
    Node* new_node       = new Node{ row, col, val };
    new_node->next       = current_node;
    new_node->prev       = current_node->prev;
    new_node->prev->next = new_node;
    current_node->prev   = new_node;
}

Node* SparseMatrix::delete_first() {
    Node* del = this->head;
    if (this->head == this->tail)
        this->head = this->tail = nullptr;
    else {
        this->head       = this->head->next;
        this->head->prev = nullptr;
    }
    return del;
}

Node* SparseMatrix::delete_last() {
    Node* del = this->tail;
    if (this->head == this->tail)
        this->head = this->tail = nullptr;
    else {
        this->tail       = this->tail->prev;
        this->tail->next = nullptr;
    }
    return del;
}

Node* SparseMatrix::search(int row, int col) {
    Node* current = this->head;
    while (current != nullptr && (current->row < row || (current->row == row && current->col < col)))
        current = current->next;
    return current;
}

SparseMatrix::SparseMatrix(int _rows, int _cols) : head{ nullptr }, tail{ nullptr } {
    if (_rows < 1 || _cols < 1) throw std::invalid_argument("can't have less than one row or column");
    this->rows = _rows;
    this->cols = _cols;
}

int SparseMatrix::get_rows() {
    return this->rows;
}

int SparseMatrix::get_cols() {
    return this->cols;
}

int SparseMatrix::element(int i, int j) {
    if (i < 0 || j < 0 || i >= this->rows || j >= this->cols) throw std::out_of_range("invalid position");
    Node* elem = this->search(i, j);
    if (elem != nullptr && elem->row == i && elem->col == j) return elem->val;
    return 0;
}

int SparseMatrix::modify(int i, int j, int val) {
    if (i < 0 || j < 0 || i >= this->rows || j >= this->cols) throw std::out_of_range("invalid position");
    Node* found = this->search(i, j);
    if (val == 0) {
        if (found == nullptr || found->row != i || found->col != j) return 0;
        int old_val = found->val;
        if (found->prev == nullptr) {
            delete this->delete_first();
            return old_val;
        }
        if (found->next == nullptr) {
            delete this->delete_last();
            return old_val;
        }
        found->prev->next = found->next;
        found->next->prev = found->prev;
        delete found;
        return old_val;
    } else {
        if (found != nullptr && found->row == i && found->col == j) {
            int old_val = found->val;
            found->val  = val;
            return old_val;
        }
        if (found == nullptr) {
            this->insert_last(i, j, val);
            return 0;
        }
        if (found->prev == nullptr) {
            this->insert_first(i, j, val);
            return 0;
        }
        this->insert_before(found, i, j, val);
        return 0;
    }
}

int SparseMatrix::get_nbh_count(int i, int j) {
    int sum = 0;
    sum += (i > 0 && j > 0) ? this->element(i - 1, j - 1) : 0;
    sum += (i > 0) ? this->element(i - 1, j) : 0;
    sum += (i > 0 && j < this->cols - 1) ? this->element(i - 1, j + 1) : 0;
    sum += (j < this->cols - 1) ? this->element(i, j + 1) : 0;
    sum += (j < this->cols - 1 && i < this->rows - 1) ? this->element(i + 1, j + 1) : 0;
    sum += (i < this->rows - 1) ? this->element(i + 1, j) : 0;
    sum += (j > 0 && i < this->rows - 1) ? this->element(i + 1, j - 1) : 0;
    sum += (j > 0) ? this->element(i, j - 1) : 0;
    return sum;
}

void SparseMatrix::clear() {
    while (this->head != nullptr)
        delete this->delete_first();
}

void SparseMatrix::randomize() {
    this->clear();
    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            if (rand() % 2) this->modify(i, j, 1);
}

SparseMatrix& SparseMatrix::operator=(SparseMatrix& other) {
    this->rows    = other.rows;
    this->cols    = other.cols;
    Node* current = other.head;
    this->clear();
    while (current != nullptr) {
        this->insert_last(current->row, current->col, current->val);
        current = current->next;
    }
    return *this;
}

Node::Node(int r, int c, int v) : row{ r }, col{ c }, val{ v }, next{ nullptr }, prev{ nullptr } {}
