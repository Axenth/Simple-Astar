#include "../incl/node.hpp"

node::node()
{
}

node::node(int x, int y, int value)
{
    this->x = x;
    this->y = y;
    this->value = value;
    this->g = 0;
    this->h = 0;
    this->f = 0;
    this->parent = NULL;
}

node::~node()
{

}

node::node(node const &src)
{
   *this = src;
}

void node::operator=(node const &src)
{
    this->x = src.x;
    this->y = src.y;
    this->value = src.value;
}

void node::set_g(int value)
{
    this->g = value;
}

void node::calc_h(node const &dest)
{
    int horizontal;
    int vertical;

    if (dest.x < this->x)
        horizontal = this->x - dest.x;
    else
        horizontal = dest.x - this->x;
    if (dest.y < this->y)
        vertical = this->y - dest.y;
    else
        vertical = dest.y - this->y;
    this->h = (vertical + horizontal) * 10;
}

void node::calc_f()
{
    this->f = this->g + this->h;
}