#pragma once

struct Node {
    int   row, col, val;
    Node* next;
    Node* prev;
    Node(int r, int c, int v);
};

class SparseMatrix {
    private:
    Node* head;
    Node* tail;
    int   rows, cols;

    void insert_last(int row, int col, int val);
    void insert_first(int row, int col, int val);
    void insert_before(Node* current_node, int row, int col, int val);

    Node* delete_first();
    Node* delete_last();

    Node* search(int row, int col);

    public:
    SparseMatrix(int _rows, int _cols);

    int get_rows();
    int get_cols();
    int element(int i, int j);
    int modify(int i, int j, int val);

    int           get_nbh_count(int i, int j);
    void          clear();
    void          randomize();
    SparseMatrix& operator=(SparseMatrix& other);
};
