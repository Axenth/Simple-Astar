#include <iostream>
#include "../incl/node.hpp"
#include <vector>
#include <unistd.h>

const int map_height = 10;
const int map_width = 10;

node *map[map_height + 1][map_width + 1];

std::vector <node *> open_list;
std::vector <node *> closed_list;

static node *set_map_value(int x, int y, int value)
{
    map[y][x]->value = value;
    return (map[y][x]);
}

static void generate_map()
{
    for(int i = 0; i <= map_height; i++)
    {
        for (int j = 0; j <= map_width; j++)
        {
            map[i][j] = new node(j, i, 0);
        }
    }
}

static void print_map()
{
    for(int i = 0; i <= map_height; i++)
    {
        for (int j = 0; j <= map_width; j++)
        {
            if (map[i][j]->value == 0)
                std::cout << "O";
            if (map[i][j]->value == 1)
                std::cout << "S";
            if (map[i][j]->value == 2)
                std::cout << "E";
            if (map[i][j]->value == 3)
                std::cout << "I";
            if (map[i][j]->value == 4)
                std::cout << "X";
        }
        std::cout << std::endl;
    }
}

void calc_g(node *Parent)
{
    if (Parent->y != 0)
    {
        if (Parent->x != 0)
            map[Parent->y - 1][Parent->x -1]->set_g(Parent->g + 14);
         map[Parent->y - 1][Parent->x]->set_g(Parent->g + 10);
         if (Parent->x != map_width)
             map[Parent->y - 1][Parent->x + 1]->set_g(Parent->g + 14);
    }

    if (Parent->x != 0)
         map[Parent->y][Parent->x - 1]->set_g(Parent->g + 10);
    if (Parent->x != map_width)
         map[Parent->y][Parent->x + 1]->set_g(Parent->g + 10);

    if (Parent->y != map_height)
    {
        if (Parent->x != 0)
            map[Parent->y + 1][Parent->x - 1]->set_g(Parent->g + 14);
         map[Parent->y + 1][Parent->x]->set_g(Parent->g + 10);
         if (Parent->x != map_width)
             map[Parent->y + 1][Parent->x + 1]->set_g(Parent->g + 14);
    }
}

void calc_h(node *Parent, node EndNode)
{
    if (Parent->y != 0)
    {
        if (Parent->x != 0)
            map[Parent->y - 1][Parent->x -1]->calc_h(EndNode);
         map[Parent->y - 1][Parent->x]->calc_h(EndNode);
         if (Parent->x != map_width)
             map[Parent->y - 1][Parent->x + 1]->calc_h(EndNode);
    }

    if (Parent->x != 0)
         map[Parent->y][Parent->x - 1]->calc_h(EndNode);
    if (Parent->x != map_width)
         map[Parent->y][Parent->x + 1]->calc_h(EndNode);

    if (Parent->y != map_height)
    {
        if (Parent->x != 0)
            map[Parent->y + 1][Parent->x - 1]->calc_h(EndNode);
         map[Parent->y + 1][Parent->x]->calc_h(EndNode);
         if (Parent->x != map_width)
             map[Parent->y + 1][Parent->x + 1]->calc_h(EndNode);
    }
}

bool check_closed_list(int x, int y)
{
    node *temp;
    for(std::vector<node*>::const_iterator it = closed_list.begin(); it != closed_list.end(); it++)
    {
        temp = *it;
        if (temp->x == x && temp->y == y)
            return true;
    }
    return false;
}

void calc_f(node *Parent)
{
    if (Parent->y != 0)
    {
        if (Parent->x != 0)
        {
            map[Parent->y - 1][Parent->x -1]->calc_f();
            if (map[Parent->y - 1][Parent->x -1]->parent == NULL)
                map[Parent->y - 1][Parent->x -1]->parent = Parent;
            if (!check_closed_list(Parent->x - 1, Parent->y - 1))
                open_list.push_back(map[Parent->y -1][Parent->x -1]);
        }
        map[Parent->y - 1][Parent->x]->calc_f();
        if (map[Parent->y - 1][Parent->x]->parent == NULL)
            map[Parent->y - 1][Parent->x]->parent = Parent;
        if (!check_closed_list(Parent->x, Parent->y - 1))
            open_list.push_back(map[Parent->y -1][Parent->x]);
        if (Parent->x != map_width)
        {
            map[Parent->y - 1][Parent->x + 1]->calc_f();
            if (map[Parent->y - 1][Parent->x + 1]->parent == NULL)
                map[Parent->y - 1][Parent->x + 1]->parent = Parent;
            if (!check_closed_list(Parent->x + 1, Parent->y - 1))
                open_list.push_back(map[Parent->y -1][Parent->x + 1]);
        }
    }
    if (Parent->x != 0)
    {
        map[Parent->y][Parent->x - 1]->calc_f();
        if (map[Parent->y][Parent->x - 1]->parent == NULL)
            map[Parent->y][Parent->x - 1]->parent = Parent;
        if (!check_closed_list(Parent->x - 1, Parent->y))
            open_list.push_back(map[Parent->y][Parent->x - 1]);
    }
    if (Parent->x != map_width)
    {
        map[Parent->y][Parent->x + 1]->calc_f();
        if (map[Parent->y][Parent->x + 1]->parent == NULL)
            map[Parent->y][Parent->x + 1]->parent = Parent;
        if (!check_closed_list(Parent->x + 1, Parent->y))
            open_list.push_back(map[Parent->y][Parent->x + 1]);
    }
    if (Parent->y != map_height)
    {
        if (Parent->x != 0)
        {
            map[Parent->y + 1][Parent->x - 1]->calc_f();
            if (map[Parent->y + 1][Parent->x - 1]->parent == NULL)
                map[Parent->y + 1][Parent->x - 1]->parent = Parent;
            if (!check_closed_list(Parent->x - 1, Parent->y + 1))
                open_list.push_back(map[Parent->y + 1][Parent->x - 1]);
        }
        map[Parent->y + 1][Parent->x]->calc_f();
        if (map[Parent->y + 1][Parent->x]->parent == NULL)
        map[Parent->y + 1][Parent->x]->parent = Parent;
        if (!check_closed_list(Parent->x, Parent->y + 1))
            open_list.push_back(map[Parent->y + 1][Parent->x]);
        if (Parent->x != map_width)
        {
            map[Parent->y + 1][Parent->x + 1]->calc_f();
            if(map[Parent->y + 1][Parent->x + 1]->parent == NULL)
                map[Parent->y + 1][Parent->x + 1]->parent = Parent;
            if (!check_closed_list(Parent->x + 1, Parent->y + 1))
                open_list.push_back(map[Parent->y + 1][Parent->x + 1]);
        }
    }
}

node *find_next_parent(node *Parent, node EndNode)
{
   
    node *newParent;
    node *temp;
    unsigned int f = 100000000;
    std::vector<node*>::const_iterator it2;
    for(std::vector<node*>::const_iterator it = open_list.begin(); it != open_list.end(); it++)
    {
        temp = *it;
        if (temp->x == Parent->x && temp->y == Parent->y)
            open_list.erase(it);
        else if (temp->value == 4)
        {
            closed_list.push_back(*it);
            continue;
        }
        else if (temp->f < f)
        {
            f = temp->f;
            newParent = *it;
            it2 = it;
        }
       
    }
    closed_list.push_back(*it2);
    open_list.erase(it2);
    return (newParent);
    
}

void calc_node(node *Parent, node EndNode)
{
    int i = 0;
    node *lParent = Parent;
    node *temp = Parent;
    node lEndNode = EndNode;
    int x, y;
    closed_list.push_back(Parent);
    while (lParent->x != lEndNode.x || lParent->y != lEndNode.y)
    {
        calc_g(lParent);
        calc_h(lParent, lEndNode);
        calc_f(lParent);
        lParent = find_next_parent(lParent, EndNode);
        i++;
        if (i == 100)
            break;
    }
}

void calc_path(node *Start, node *EndNode)
{
    node *curr;
    node *temp;
    for(std::vector<node*>::const_iterator it = closed_list.begin(); it != closed_list.end(); it++)
    {
        temp = *it;
        if (temp->x == EndNode->x && temp->y == EndNode->y)
        {
            curr = temp;
            break;
        }
    }
    while(1)
    {
        if(temp->x == Start->x && temp->y == Start->y)
           break;
        map[temp->y][temp->x]->value = 3;
        map[EndNode->y][EndNode->x]->value = 2;
        temp = temp->parent;
        sleep(1);
        system("clear");
        print_map();
        std::cout << temp->x<<  "," << temp->y << "   " << Start->x << "," << Start->y << std::endl;
    }
}

int main(void)
{
    node *startNode;
    node endNode;
    generate_map();
    startNode = set_map_value(0,0, 1);
    endNode = *set_map_value(2,10,2);
    set_map_value(0,5,4);
    set_map_value(1,5,4);
    set_map_value(2,5,4);
    set_map_value(3,5,4);
    set_map_value(4,7,4);
    set_map_value(5,5,4);
    set_map_value(6,5,4);
    set_map_value(7,5,4);
    set_map_value(8,5,4);

    calc_node(startNode, endNode);
    calc_path(startNode, &endNode);
}