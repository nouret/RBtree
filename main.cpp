#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//NO CHANGE val OF Elem !!!//
const bool BLACK = true;
const bool RED = false;

struct Elem{
    int val;
    Elem * parent;
    Elem * left;
    Elem * right;
    int count;
    int sum;
    bool color;
    Elem (){
        color = BLACK;
        count = 1;
        sum = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
    bool real(){
        if (this == NULL)
            return false; //why is it here?
        if (left == NULL && right == NULL)
            return false; //why nor or?
        return true;
    }
    bool good(){
        if (real()){
            if (color == RED){
                if (left -> color == RED)
                    return false;
                if (right -> color == RED)
                    return false;
            }
        }
        return true;
    }
    Elem * find_key(int key){
        if (!real())
            return this;
        if (val == key)
            return this;
        if (key < val)
            return left -> find_key(key);
        if (key > val)
            return right -> find_key(key);
    }
    Elem * find_i(int i){
        if (!real())
            return this;
        if (left -> sum > i){
            return left -> find_i(i);
        }
        i -= left -> sum;
        if (0 == i){
            return this;
        }
        return right -> find_i(i - 1);
    }
    void recount_sum(){
        if (this == NULL)
            return;
        if (real()){
            left -> parent = this;
            right -> parent = this;
            sum = 1 + left -> sum + right -> sum;
        }
        else
            sum = 0;
    }
    Elem * grandparent(){
        if (this == NULL)
            return NULL;
        if (parent == NULL)
            return NULL;
        return parent -> parent;
    }
    Elem * uncle(){
        Elem * G = grandparent();
        if (G == NULL)
            return NULL;
        if (G -> left == parent)
            return G -> right;
        return G -> left;
    }
    void left_rotation(){
        if (!this -> real())
            return;
        if (!right -> real())
            return;
        if (parent != NULL){
            if (parent -> left == this){
                parent -> left = right;
            }
            else{
                parent -> right = right;
            }
        }
        Elem * H = right;
        right = H -> left;
        H -> left = this;
        H -> parent = parent;
        recount_sum();
        H -> recount_sum();
        H -> parent -> recount_sum();
    }
    void right_rotation(){
        if (!this -> real())
            return;
        if (!left -> real())
            return;
        if (parent != NULL){
            if (parent -> left == this){
                parent -> left = left;
            }
            else{
                parent -> right = left;
            }
        }
        Elem * H = left;
        left = H -> right;
        H -> right = this;
        H -> parent = parent;
        recount_sum();
        H -> recount_sum();
        H -> parent -> recount_sum();
    }
    void Print1(){
        if (real()){
            left -> Print1();
            for (int i = 0; i < count; ++i)
                cout << val << " ";
            right -> Print1();        
        }
    }
    void Print2(){
        if (real()){
            cout << val;
            if (color == RED)
                cout << " RED ";
            else
                cout << " BLACK ";
            if (left -> real()){
                cout << "left: " << left -> val << " ";
            }
            if (right -> real()){
                cout << "right: " << right -> val << " ";
            }
            cout << "sum: " << sum << " ";
            cout << endl;
            left -> Print2();
            right -> Print2();
        }
    }
    void push_update(){
        if (parent == NULL){
            color = BLACK;
            return;
        }
        if (parent -> color == BLACK){
            return; //it can't be used
        }
        Elem * U = uncle();
        Elem * G = grandparent();
        Elem * N = this;
        Elem * P = parent;
        
        if (U -> color == RED){
            U -> color = BLACK;
            parent -> color = BLACK;
            G -> color = RED;
            G -> push_update();
            return;
        }
        //U -> color = BLACK;
        //G -> color = BLACK;
        if (G -> left == P && P -> right == N){
            P -> left_rotation();
            N = P;
            P = N -> parent;
        }
        if (G -> right == P && P -> left == N){
            P -> right_rotation();
            N = P;
            P = N -> parent;
        }
        if (G -> left == P && P -> left == N){
            G -> right_rotation();
            P -> color = BLACK;
            G -> color = RED;
            return;
        }
        if (G -> right == P && P -> right == N){
            G -> left_rotation();
            P -> color = BLACK;
            G -> color = RED;
            return;
        }
    }
};

struct Tree{
    Elem * root;
    Tree(){
        root = new Elem();
    }
    void push(double key){
        Elem * now = root;
        Elem * h;
        while (now -> real()){
            if (key == now -> val){
                ++(now -> count);
                return;
            }
            if (key < now -> val)
                now = now -> left;
            else
                now = now -> right;
        }
        now -> left = new Elem();
        now -> right = new Elem();
        now -> color = RED;
        now -> val = key;
        h = now;
        while (h -> parent != NULL){
            h -> recount_sum();
            h = h -> parent;
        }
        h -> recount_sum();
        now -> push_update();
        while (root -> parent != NULL){
            root = root -> parent;
        }
    }
};

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N, val;
    //lem * E;
    Tree T;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> val;
        T.push(val);
    }
    T.root -> Print1();
}
