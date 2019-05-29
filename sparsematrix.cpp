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
    Node* del;
    if (this->head == this->tail) {
        del        = this->head;
        this->head = this->tail = nullptr;
    } else {
        del              = this->head;
        this->head       = this->head->next;
        this->head->prev = nullptr;
    }
    return del;
}

Node* SparseMatrix::delete_last() {
    Node* del;
    if (this->head == this->tail) {
        del        = this->tail;
        this->head = this->tail = nullptr;
    } else {
        del              = this->tail;
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

SparseMatrix::SparseMatrix(int _rows, int _cols) :
    head{ nullptr },
    tail{ nullptr },
    rows{ _rows },
    cols{ _cols } {}

int SparseMatrix::get_rows() const {
    return this->rows;
}

int SparseMatrix::get_cols() const {
    return this->cols;
}

int SparseMatrix::elem(int i, int j) const {
    if (i < 0 || j < 0 || i >= this->rows || j >= this->cols) throw std::out_of_range("invalid position");
    Node* current = this->head;
    while (current != nullptr && (current->row < i || (current->row == i && current->col < j)))
        current = current->next;
    if (current != nullptr && current->row == i && current->col == j) return current->val;
    return 0;
}

void SparseMatrix::modify(int i, int j, int val) {
    if (i < 0 || j < 0 || i >= this->rows || j >= this->cols) throw std::out_of_range("invalid position");
    if (val == 0) {
        Node* found = this->search(i, j);
        if (found == nullptr || found->row != i || found->col != j) return;
        if (found->prev == nullptr) {
            delete this->delete_first();
            return;
        }
        if (found->next == nullptr) {
            delete this->delete_last();
            return;
        }
        found->prev->next = found->next;
        found->next->prev = found->prev;
        delete found;

    } else {
        Node* found = this->search(i, j);
        if (found != nullptr && found->row == i && found->col == j) {
            found->val = val;
            return;
        }
        if (found == nullptr) {
            this->insert_last(i, j, val);
            return;
        }
        if (found->prev == nullptr) {
            this->insert_first(i, j, val);
            return;
        }
        this->insert_before(found, i, j, val);
    }
}

int SparseMatrix::get_nbh_count(int i, int j) {
    int sum = 0;
    sum += (i > 0 && j > 0) ? this->elem(i - 1, j - 1) : 0;
    sum += (i > 0) ? this->elem(i - 1, j) : 0;
    sum += (i > 0 && j < this->cols - 1) ? this->elem(i - 1, j + 1) : 0;
    sum += (j < this->cols - 1) ? this->elem(i, j + 1) : 0;
    sum += (j < this->cols - 1 && i < this->rows - 1) ? this->elem(i + 1, j + 1) : 0;
    sum += (i < this->rows - 1) ? this->elem(i + 1, j) : 0;
    sum += (j > 0 && i < this->rows - 1) ? this->elem(i + 1, j - 1) : 0;
    sum += (j > 0) ? this->elem(i, j - 1) : 0;
    return sum;
}

void SparseMatrix::clear() {
    while (this->head != nullptr)
        this->delete_first();
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
