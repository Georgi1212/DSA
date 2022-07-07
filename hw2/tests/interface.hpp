#pragma once
#include "tree.hpp"

using std::string;

class Hierarchy
{
public:
    Hierarchy() = default;
    Hierarchy(Hierarchy&& r) noexcept;
    Hierarchy(const Hierarchy& r);
    Hierarchy(const string& data);
    ~Hierarchy() noexcept;
    void operator=(const Hierarchy&) = delete;

    void help();
    void load(const char* fileName);

    string print()const;

    int longest_chain() const; 
    bool find(const string& name) const; 
    int num_employees() const;

    int num_overloaded(int level = 20) const;

    string manager(const string& name) const; 
    int num_subordinates(const string& name) const; 
    unsigned long getSalary(const string& who) const; 

    bool fire(const string& who);
    bool hire(const string& who, const string& boss); 

    void incorporate();
    void modernize();

    Hierarchy join(const Hierarchy& right) const;

    void save(const char* filename);

private:
    tree hierarchy;
};

Hierarchy::Hierarchy(Hierarchy&& r) noexcept 
{
    hierarchy = r.hierarchy;
    
}

Hierarchy::Hierarchy(const Hierarchy& r)
{
    hierarchy = r.hierarchy;
}

Hierarchy::Hierarchy(const string& data)
{
    hierarchy.setRootData(data);
}

Hierarchy::~Hierarchy() noexcept
{
    hierarchy.~tree();
}

void Hierarchy::operator=(const Hierarchy&) = delete;

void Hierarchy::help()
{

}

void Hierarchy::load(const char* fileName)
{
    if(fileName)
    {
        hierarchy.createTree(fileName);
    }

    //..
}

string Hierarchy::print()const 
{
    hierarchy.print_to_string();
}

int Hierarchy::longest_chain() const 
{
    return hierarchy.height();
}

bool Hierarchy::find(const string& name) const
{
    return hierarchy.find(name);
}

int Hierarchy::num_employees() const
{
    return hierarchy.getSize();
}

int Hierarchy::num_overloaded(int level = 20) const 
{
    return hierarchy.numberOfChildren_greaterThan_Value(level);
}

string Hierarchy::manager(const string& name) const
{
    return hierarchy.parent_of_a_node(name);
}

int Hierarchy::num_subordinates(const string& name) const 
{
    //if(hierarchy.find(name))
    return hierarchy.numberOfDirectChildren(name);
    
    //return -1;
}

unsigned long Hierarchy::getSalary(const string& who) const 
{
    if(hierarchy.find(who))
    {
        int number_direct_children = num_subordinates(who);
        int number_indirect_children = hierarchy.numberOfIndirectChildren(who);

        return (unsigned long)(500 * number_direct_children + 50 * number_indirect_children);
    }

    return (unsigned long)(-1);
}

bool Hierarchy::fire(const string& who) 
{
    if(who == "Uspeshnia")
    {
        return false;
    }
    else
    {
        return hierarchy.remove(who);
    }
}

bool Hierarchy::hire(const string& who, const string& boss)
{
    if(who == "Uspeshnia")
    {
        return false;
    }

    if(find(who) && manager(who) == boss)
    {
        return false;
    }

    else if(find(who) && manager(who) != boss) 
    {//->prenaznachavane
        hierarchy.move_node(who, boss);
    }

    return hierarchy.insert(who, boss);
}

void Hierarchy::incorporate()
{

}

void Hierarchy::modernize()
{

}

Hierarchy Hierarchy::join(const Hierarchy& right) const
{

}

void Hierarchy::save(const char* fileName)
{
    std::ofstream out(fileName, std::ios::trunc); //std::ios::out

    std::string newTree = print();

    if(fileName)
    {
        out << newTree;
    }
    else
    {
        std::cout << newTree;
    }
}