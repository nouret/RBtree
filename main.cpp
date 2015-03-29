#include <iostream>
#include <fstream>
#include <stdio.h>

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
        if (left == NULL && right == NULL)
            return false;
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
        if (real()){
            left -> parent = this;
            right -> parent = this;
        }
    }
};

struct Tree{
    Elem * root;
    Tree(){
        root = Elem();
    }
    void push(double key){
        Elem * now = root;
        while (now -> real()){
            if (key == now -> val)
                return;
            if (key < now -> val)
                now = now -> left;
            now = now -> right;
        }
        now -> val = key;
        now -> left = new Elem();
        now -> right = new Elem();
        now -> recount_sun();
    }
};