#ifndef Matrix_Sparse
#define Matrix_Sparse
#include <iostream>
#include <cmath>


struct el_Matrix_ {
    double val;
    int r;
    int c;
    el_Matrix_* next;

    el_Matrix_() {
        val = 0;
        r = 0;
        c = 0;
        next = 0;
    }
    el_Matrix_(double a, int row, int col) {
        if (row < 0 || col < 0) {
            abort();
        }
        val = a;
        r = row;
        c = col;
        next = 0;
    }

    el_Matrix_(const el_Matrix_& t) {
        val = t.val;
        r = t.r;
        c = t.c;
        el_Matrix_* temp = new el_Matrix_;
        el_Matrix_* t_temp = t.next;
        next = temp;
        while (t_temp != 0) {
            temp->next = new el_Matrix_(t_temp->val, t_temp->r, t_temp->c);
            temp = temp->next;
            t_temp = t_temp->next;
        }
        next = next->next;

        /*
        if(t.next!=0)
            next = new el_list(*t.next); // POSSIBLE ERROR
        else next = 0;
        */
    }



    void Set(double* A, int N, int stop) { //         test!!!

        if (stop == N - 1) {
            val = A[stop];
            r = 0;
            c = stop;
            next = 0;
            return;
        }

        val = A[stop];
        r = 0;
        c = stop;
        next = new el_Matrix_;
        stop++;
        next->Set(A, N, stop);
        return;

    }

    bool if_samePosition(el_Matrix_& t) {
        if (t.r == r && t.c == c)
            return true;

        else
            return false;
    }
    bool if_After_(el_Matrix_& t, char arr) {
        switch (arr) {
        case 'r':
            if (t.r < r)
                return true;

            else if (t.r == r && t.c < c)
                return true;
            else
                return false;
            break;
        case 'c':
            if (t.c < c)
                return true;

            else if (t.c == c && t.r < r)
                return true;
            else
                return false;
            break;
        default:
            abort();
        }
    }

    void Print_hidden() {

        cout << val << " ";
        if (next != 0)
            next->Print_hidden();

        return;

    }

    void Print() {
        Print_hidden();
        cout << "\n";
    }

};

class Matrix_ {

private:
    int r0;
    int c0;
    el_Matrix_* root;
    char arrangement;


public:
    Matrix_() {
        r0 = 2;
        c0 = 2;
        root = new el_Matrix_;
        arrangement = 'r';
    }


    Matrix_(const Matrix_& t) {
        r0 = t.r0;
        c0 = t.c0;
        root = new el_Matrix_(*t.root);
        arrangement = t.arrangement;
    }


    Matrix_(double** A, int a, int b) {
        if (a < 1 || b < 1) {
            abort();
        }
        r0 = a;
        c0 = b;
        arrangement = 'r';
        el_Matrix_* temp = new el_Matrix_;
        root = temp;
        for (int i = 0; i < a; i++) {
            for (int k = 0; k < b; k++) {
                if (A[i][k] != 0) {

                    temp->next = new el_Matrix_(A[i][k], i, k);
                    temp = temp->next;

                }
            }
        }
        root = root->next;
    }


    Matrix_(int a, int b) {
        Init(a, b);
    }

    void Init(double** A, int a, int b) {
        if (a < 1 || b < 1) {
            abort();
        }
        r0 = a;
        c0 = b;
        arrangement = 'r';
        el_Matrix_* temp = new el_Matrix_;
        root = temp;
        for (int i = 0; i < a; i++) {
            for (int k = 0; k < b; k++) {
                if (A[i][k] != 0) {

                    temp->next = new el_Matrix_(A[i][k], i, k);
                    temp = temp->next;

                }
            }
        }
        root = root->next;
    }

    void Init(int a, int b) {
        int te;
        if (a < 1 || b < 1) {
            abort();
        }
        r0 = a;
        c0 = b;
        arrangement = 'r';
        double** A = new double* [a], x;
        for (int i = 0; i < a; i++) {
            A[i] = new double[b];
            for (int k = 0; k < b; k++) {
                x = rand() % 30;                    //NON-ZERO PROBABILITY
                if (x > 27) {                       //NON-ZERO PROBABILITY
                    x = rand() % 9 + 1;              //DATA FILL
                    A[i][k] = pow(-1, rand() % 10) * x; //SIGN PROBABILITY
                }
                else
                    A[i][k] = 0;
            }
        }

        el_Matrix_* temp = new el_Matrix_;
        root = temp;
        for (int i = 0; i < a; i++) {
            for (int k = 0; k < b; k++) {
                if (A[i][k] != 0) {

                    temp->next = new el_Matrix_(A[i][k], i, k);
                    temp = temp->next;

                }
            }
        }
        root = root->next;
    }

    void Rearrange() {
        el_Matrix_* temp = root;
        int st = 0, count = 0, min = r0 * c0;
        while (temp != 0) {
            temp = temp->next;
            count++;
        }
        temp = root;
        el_Matrix_** reArr = new el_Matrix_ * [count];
        for (int i = 0; i < count; i++) {
            reArr[i] = temp;
            temp = temp->next;
        }
        ////////////////

        root = temp = new el_Matrix_;
        switch (arrangement) {
        case 'r':
            for (int n = 0; n < count; n++) {
                min = r0 * c0;
                for (int i = 0; i < count; i++) {
                    if (reArr[i] == 0)
                        continue;
                    if (reArr[i]->c * r0 + reArr[i]->r < min) {
                        min = reArr[i]->c * r0 + reArr[i]->r;
                        st = i;
                    }
                }
                temp->next = reArr[st];
                reArr[st] = 0;
                temp = temp->next;

            }
            break;
        case 'c':
            for (int n = 0; n < count; n++) {
                min = r0 * c0;
                for (int i = 0; i < count; i++) {
                    if (reArr[i] == 0)
                        continue;
                    if (reArr[i]->r * c0 + reArr[i]->c < min) {
                        min = reArr[i]->r * c0 + reArr[i]->c;
                        st = i;
                    }
                }
                temp->next = reArr[st];
                reArr[st] = 0;
                temp = temp->next;

            }
            break;
        default:
            abort();
        }
        temp->next = 0;
        root = root->next;
        if (arrangement == 'r')
            arrangement = 'c';
        else arrangement = 'r';
        return;

    }

    double** toArr() {
        double** x = new double* [r0];
        int key = 0;
        if (arrangement == 'c') {
            Rearrange();
            key = 1;
        }
        el_Matrix_* temp = root;
        for (int i = 0; i < r0; i++) {
            x[i] = new double[c0] {0};
            for (int k = 0; k < c0; k++) {
                if (temp == 0)
                    break;
                if (temp->r == i && temp->c == k) {
                    x[i][k] = temp->val;
                    temp = temp->next;
                }
            }
        }
        if (key == 1) {
            Rearrange();
        }

        return x;
    }


    Matrix_ byNum(double a) {
        Matrix_* X = new Matrix_(*this);


        el_Matrix_* temp = X->root;

        while (temp != 0) {
            temp->val *= a;
            temp = temp->next;
        }


        return *X;
    }

    Matrix_ Add(Matrix_ X) {
        int rearrange_key = 0;
        if (X.r0 != r0 || X.c0 != c0 || root == 0 || X.root == 0)
            abort();

        if (arrangement != X.arrangement) {
            X.Rearrange();
            rearrange_key = 1;
        }

        el_Matrix_* temp = new el_Matrix_;
        el_Matrix_* S1 = root, * S2 = X.root;

        Matrix_* O = new Matrix_;
        O->r0 = r0;
        O->c0 = c0;
        O->arrangement = arrangement;
        O->root = temp;

        while (S1 != 0 && S2 != 0) {

            temp->next = new el_Matrix_;
            if (S1->if_samePosition(*S2)) {
                temp->next->r = S1->r;
                temp->next->c = S1->c;
                temp->next->val = S1->val + S2->val;
                S1 = S1->next;
                S2 = S2->next;
            }
            else if (S1->if_After_(*S2, arrangement)) {
                temp->next->r = S2->r;
                temp->next->c = S2->c;
                temp->next->val = S2->val;
                S2 = S2->next;
            }
            else {
                temp->next->r = S1->r;
                temp->next->c = S1->c;
                temp->next->val = S1->val;
                S1 = S1->next;
            }
            temp = temp->next;

        }

        if (S1 == 0) {
            while (S2 != 0) {
                temp->next = new el_Matrix_;
                temp->next->r = S2->r;
                temp->next->c = S2->c;
                temp->next->val = S2->val;
                S2 = S2->next;
                temp = temp->next;
            }
        }
        else if (S2 == 0) {
            while (S1 != 0) {
                temp->next = new el_Matrix_;
                temp->next->r = S1->r;
                temp->next->c = S1->c;
                temp->next->val = S1->val;
                S1 = S1->next;
                temp = temp->next;
            }
        }

        O->root = O->root->next;

        if (rearrange_key == 1) {
            X.Rearrange();
        }

        return *O;
    }



    Matrix_ Trans() {
        Matrix_* O = new Matrix_(*this);
        el_Matrix_* temp = O->root;
        int st;

        st = O->c0;
        O->c0 = O->r0;
        O->r0 = st;
        while (temp != 0) {
            st = temp->c;
            temp->c = temp->r;
            temp->r = st;
            temp = temp->next;
        }

        O->Rearrange();

        O->Rearrange();

        return *O;
    }


    Matrix_ byMatr(Matrix_ X) {
        int rearrange_key1 = 0, rearrange_key2 = 0;
        if (c0 != X.r0)
            abort();
        if (arrangement == 'c') { //set L to the "row" arr
            Rearrange();
            rearrange_key1 = 1;
        }
        if (X.arrangement == 'r') {  //set R to the "col" arr
            X.Rearrange();
            rearrange_key2 = 1;
        }
        Matrix_* O = new Matrix_;
        O->r0 = r0;
        O->c0 = X.c0;
        O->arrangement = 'r';
        el_Matrix_* L = root;
        el_Matrix_* R = X.root;
        el_Matrix_* temp = new el_Matrix_;
        O->root = temp;

        el_Matrix_* store_Lrow_retu = L;
        el_Matrix_* store_Lrow_next = 0;

        el_Matrix_* store_Rcol_retu1 = R;
        el_Matrix_* store_Rcol_next = 0;

        int max_col_idx = c0, row_store, col_store;
        double val_store = 0;




        while (L != 0) {
            row_store = L->r;
            while (R != 0) {
                col_store = R->c;
                do {
                    do {

                        if (L->c == R->r) {
                            val_store += L->val * R->val;
                        }

                        R = R->next;


                        store_Rcol_next = R;
                        if (R == 0)
                            break;
                    } while (R->c == col_store);

                    R = store_Rcol_retu1;
                    L = L->next;
                    if (L == 0)
                        break;
                } while (L->r == row_store);
                store_Lrow_next = L;
                L = store_Lrow_retu;
                R = store_Rcol_next;
                store_Rcol_retu1 = store_Rcol_next;
                if (val_store != 0) {
                    temp->next = new el_Matrix_(val_store, row_store, col_store);
                    val_store = 0;
                    temp = temp->next;
                }

            }
            L = store_Lrow_next;
            store_Lrow_retu = store_Lrow_next;
            R = X.root;
            store_Rcol_retu1 = R;

        }


        if (O->root->next != 0)
            O->root = O->root->next;


        if (rearrange_key1 == 1) {
            Rearrange();
        }
        if (rearrange_key2 == 1) {
            X.Rearrange();
        }
        return *O;
    }





    void PrintList() {
        root->Print();
    }

    void PrintMatr() {

        double** x = toArr();
        for (int i = 0; i < r0; i++) {
            for (int k = 0; k < c0; k++) {
                cout << x[i][k] << " ";
            }
            cout << "\n";
        }
        cout << "\n";

    }


};



#endif // Matrix_Sparse
#pragma once
