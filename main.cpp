#include "tests.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

void print_mat(SparseMatrix& m) {
    for (int i = 0; i < m.get_rows(); ++i) {
        for (int j = 0; j < m.get_cols(); ++j)
            cout << (m.element(i, j) ? 'O' : ' ') << ' ';
        cout << '|' << endl;
    }
    for (int i = 0; i < m.get_rows(); ++i)
        cout << "--";
    cout << endl;
}

int main() {
    matrix_tests();

    SparseMatrix gen{ 25, 25 };
    SparseMatrix next_gen{ 25, 25 };
    long long    t   = time(nullptr);
    char         cmd = 'r';

    while (cmd != 'q') {
        if (cmd == 'r') gen.randomize();
        if (cmd == 's') {
            while (!kbhit()) {
                if (t < time(nullptr)) {
                    t = time(nullptr);
                    next_gen.clear();
                    for (int i = 0; i < gen.get_rows(); ++i)
                        for (int j = 0; j < gen.get_cols(); ++j) {
                            int nbhs = gen.get_nbh_count(i, j);
                            int cell = gen.element(i, j);
                            if (cell == 0 && nbhs == 3)
                                next_gen.modify(i, j, 1);
                            else if (cell == 1 && (nbhs < 2 || nbhs > 3))
                                next_gen.modify(i, j, 0);
                            else
                                next_gen.modify(i, j, cell);
                        }
                    system("cls");
                    gen = next_gen;
                    print_mat(next_gen);
                    cout << endl << "press any key to stop" << endl;
                }
            }
        }
        system("cls");
        print_mat(gen);
        cout << endl << "press S to start, R to reset or Q to quit" << endl;
        cin >> cmd;
    }
    return 0;
}
