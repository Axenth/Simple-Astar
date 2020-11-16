#ifndef NODE_HPP
# define NODE_HPP
# include <iostream>

class node{
    public:
    int x;
    int y;
    int value;
    int g;
    int h;
    int f;
    node *parent;
    
        node();
        node(int x, int y, int value);
        ~node();
        node(node const &src);
        void operator=(node const &src);
        void set_g(int value);
        void calc_h(node const &dest);
        void calc_f();
};

#endif