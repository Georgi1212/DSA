#pragma once

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<fstream>
#include<stdexcept>


struct treeNode
{
    std::string data{};
    std::vector<treeNode*> children{};
    treeNode* parent_ptr{}; //{nullptr}
    //treeNode* children_ptr{}; 

    treeNode() = default;

    treeNode(const std::string& _data)
    {
        data = _data;
    }

    treeNode(std::string _data, std::vector<treeNode*> _children, treeNode* _parent_ptr)
    {
        data = _data;
        children = _children;
        parent_ptr = _parent_ptr;
        //children_ptr = _children_ptr;
    }

    ~treeNode()
    {
        delete parent_ptr;
        children.~vector();
    }
};

class tree 
{
    private:
        treeNode* root;

        void destroy(treeNode* &treeRoot);
        treeNode* copy(treeNode* treeRoot);

        bool find_helper(treeNode* treeRoot, const std::string& _name) const;
        int size_helper(treeNode* treeRoot) const;
        int height_helper(treeNode* treeRoot) const;
        int level_of_a_node_helper(treeNode* treeRoot, const std::string& _name) const;

        bool insert_helper(treeNode* treeRoot, const std::string& _name, const std::string& _parent) const;
        bool remove_helper(treeNode* treeRoot, const std::string& _name) const;
        bool move_node_helper(treeNode* treeRoot, const std::string& _name, const std::string& _parent) const;

        std::string parent_of_a_node_helper(treeNode* treeRoot, const std::string& _name) const;

        int numberOfDirectChildren_helper(treeNode* treeRoot, const std::string& _name) const;
        int numberOfIndirectChildren_helper(treeNode* treeRoot, const std::string& _name) const;
        int numberOfChildren_helper(treeNode* treeRoot, const std::string& _name) const; 
        int numberOfChildren_greaterThan_Value_helper(treeNode* treeRoot, int value) const;
        
        void print_to_string_helper(treeNode* treeRoot, std::string& resultStr) const;

        

        tree join_two_trees_helper(const tree& other_tree);
        

    public:
        tree();
        tree(const tree& other);
        tree(tree&& other);
        tree& operator=(const tree& other);
        tree& operator=(const tree&& other);
        ~tree();

        treeNode* getRoot() {return this->root;}
        std::string getRootData() const {return root->data;}
        void setRootData(const std::string& _name) {root->data = _name;}

        treeNode* getNodeByName(treeNode* treeRoot, const std::string& _name) const;
        treeNode* createTree(const char* fileName);

        bool find(const std::string& _name) const;
        int getSize() const;
        int height() const;
        int level_of_a_node(const std::string& _name) const;

        bool insert(const std::string& _name, const std::string& _parent) const;
        bool remove(const std::string& _name) const;
        bool move_node(const std::string& _name, const std::string& _parent) const;

        std::string parent_of_a_node(const std::string& _name) const;

        int numberOfDirectChildren(const std::string& _name) const;
        int numberOfIndirectChildren(const std::string& _name) const;
        int numberOfChildren(const std::string& _name) const; 
        int numberOfChildren_greaterThan_Value(int value) const;

        std::string print_to_string() const;

        tree join_two_trees(const tree& other_tree);
};