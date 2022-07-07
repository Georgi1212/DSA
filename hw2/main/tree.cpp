#include "tree.hpp"

void tree::destroy(treeNode* &treeRoot)
{
    if(treeRoot == nullptr)
    {
        return;
    }

    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        destroy(treeRoot->children[i]);
    }
    delete treeRoot;
}

treeNode* tree::copy(treeNode* treeRoot)
{
    if(treeRoot == nullptr)
    {
        return nullptr;
    }

    treeNode* copyRoot = new treeNode();
    copyRoot->data = treeRoot->data;
    copyRoot->parent_ptr = treeRoot->parent_ptr;

    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        copyRoot->children.push_back(copy(treeRoot->children[i]));
    }

    return copyRoot;
}

bool tree::find_helper(treeNode* treeRoot, const std::string& _name) const
{
    if(treeRoot->data == _name)
    {
        return true;
    }

    if(treeRoot == nullptr)
    {
        return false;
    }

    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        if(find_helper(treeRoot->children[i], _name))
        {
            return true;
        }
    }
    return false;
}

int tree::size_helper(treeNode* treeRoot) const
{
    if(treeRoot == nullptr)
    {
        return 0;
    }

    int count = 1;
    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        count += size_helper(treeRoot->children[i]);
    }

    return count;
}

int tree::height_helper(treeNode* treeRoot) const
{
    if(treeRoot == nullptr)
    {
        return 0; // ili -1, zashtoto nqma durvo
    }

    int heightTree = 0;
    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        if(treeRoot->children[i] != nullptr)
        {
            heightTree = std::max(heightTree, height_helper(treeRoot->children[i]));
        }
    }
    return heightTree + 1;

}

int tree::level_of_a_node_helper(treeNode* treeRoot, const std::string& _name) const //vij tukkk
{
    if(treeRoot == nullptr)
    {
        return -1;
    }
    
    if(treeRoot->data == _name)
    {
        return 0;
    }

    int level = 1;
    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        if(treeRoot->children[i]->data == _name)
        {
            return level;
        }
        else
        {
            level++;
            level_of_a_node_helper(treeRoot->children[i], _name);
        }
    }

    return -1; //zashtoto nqma vruh v durvoto s tova ime
}

bool tree::insert_helper(treeNode* treeRoot, const std::string& _name, const std::string& _parent) const
{
    if(treeRoot == nullptr)
    {
        treeNode* newRoot = new treeNode();
        newRoot->data = _name;
        newRoot->parent_ptr = nullptr;
        return true;
    }

    if(treeRoot->data == _parent)
    {
        treeNode* _newRoot = new treeNode();
        _newRoot->data = _name;
        _newRoot->parent_ptr = treeRoot;
        treeRoot->children.push_back(_newRoot);
        return true;
    }

    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        /*//purvi variant
        if(treeRoot->children[i]->data == _parent)
        {
            treeNode* _newRoot = new treeNode();
            _newRoot->data = _name;
            treeRoot->children[i]->children.push_back(_newRoot);
            //treeRoot->children[i]->parent_ptr = treeRoot;
            return true;
        }
        else
        {
            insert_helper(treeRoot->children[i], _name, _parent);
        }*/

        // vtori variant
        if(insert_helper(treeRoot->children[i], _name, _parent))
        {
            return true;
        }
        
    }
    return false;
}

bool tree::remove_helper(treeNode* treeRoot, const std::string& _name) const
{
    if(treeRoot == nullptr)
    {
        return false;
    }

    int childrenSize = treeRoot->children.size();
    
    for(int i = 0; i < childrenSize; ++i) // ne sum mnogo sig dali e taka, но мисля че е така
    {
        if(treeRoot->children[i]->data == _name)
        {
            treeNode* toDelete = treeRoot->children[i];
            treeRoot->children[i]->parent_ptr = nullptr;
            if(treeRoot->children[i]->children.size() > 0)
            {
                int childrenSize_ith = treeRoot->children[i]->children.size();
                for(int j = 0; j < childrenSize_ith; ++j)
                {
                    treeRoot->children.push_back(treeRoot->children[i]->children[j]);
                }
            }
            delete toDelete; 
            return true;
        }
        else
        {
            remove_helper(treeRoot->children[i], _name);
        }
    }
    return false;
}

bool tree::move_node_helper(treeNode* treeRoot, const std::string& _name, const std::string& _parent) const
{
    if(treeRoot == nullptr)
    {
        return false;
    }

    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        if(treeRoot->children[i]->data == _name)
        {
            //...
            if(find_helper(treeRoot, _parent))
            {
                treeNode* toDelete = treeRoot->children[i];
                treeNode* parentNode = getNodeByName(treeRoot, _parent);
                parentNode->children.push_back(treeRoot->children[i]);
                treeRoot->children[i]->parent_ptr = parentNode;
                delete toDelete;
                return true;
            }

            else{ return false; }
        }
        else
        {
            move_node_helper(treeRoot->children[i], _name, _parent);
        }

    }
    return false;
}

std::string tree::parent_of_a_node_helper(treeNode* treeRoot, const std::string& _name) const 
{
    if(treeRoot == nullptr)
    {
        return "";
    }

    if(treeRoot->data == _name)
    {
        return ""; //return treeRoot->parent_ptr->data;
    }

    std::string parentNode = treeRoot->data;
    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        treeRoot->children[i]->parent_ptr = treeRoot;
        if(treeRoot->children[i]->data == _name)
        {
            return parentNode;
        }
        else
        {
            parent_of_a_node_helper(treeRoot->children[i], _name);
        }
    }
    return "";
}

int tree::numberOfDirectChildren_helper(treeNode* treeRoot, const std::string& _name) const
{
    if(treeRoot == nullptr)
    {
        return 0;
    }
    
    if(treeRoot->data == _name) //tozi sluchai moje i da go nqma (moje i da nqma smisul da go pisha)
    {
        return treeRoot->children.size();
    }

    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        if(treeRoot->children[i]->data == _name)
        {
            return treeRoot->children[i]->children.size();
        }
        else
        {
            numberOfDirectChildren_helper(treeRoot->children[i], _name);
        }
    }
    return -1; // ili 0
}

int tree::numberOfIndirectChildren_helper(treeNode* treeRoot, const std::string& _name) const
{
    if(treeRoot == nullptr)
    {
        return 0;
    }

    if(treeRoot->data == _name) 
    {
        return (size_helper(treeRoot) - 1) - (numberOfDirectChildren_helper(treeRoot, _name));
    }

    int childrenSize = treeRoot->children.size();

    for(int i = 0; i < childrenSize; ++i)
    {
        if(treeRoot->children[i]->data == _name)
        {
            return (size_helper(treeRoot->children[i])) - (numberOfDirectChildren_helper(treeRoot->children[i], _name));
        }
        else
        {
            numberOfIndirectChildren_helper(treeRoot->children[i], _name);
        }
    }
    return -1; //ili 0
}


int tree::numberOfChildren_helper(treeNode* treeRoot, const std::string& _name) const
{
    return numberOfDirectChildren_helper(treeRoot, _name) + numberOfIndirectChildren_helper(treeRoot, _name);
}

int tree::numberOfChildren_greaterThan_Value_helper(treeNode* treeRoot, int value) const
{
    if(treeRoot == nullptr)
    {
        return 0;
    }

    int countEmployees = 0;

    if((size_helper(treeRoot) - 1) > value)
    {
        countEmployees++;
    }

    int childrenSize = treeRoot->children.size();
    for(int i = 0; i < childrenSize; i++)
    {
        countEmployees += numberOfChildren_greaterThan_Value_helper(treeRoot->children[i], value);
    }

    return countEmployees;
}

void tree::print_to_string_helper(treeNode* treeRoot, std::string& resultStr) const //vij tukkk
{
    if(treeRoot == nullptr)
    {
        return;
    }

    //resultStr += treeRoot->data;
    int childrenSize = treeRoot->children.size();

    if(childrenSize > 0)
    {
        for(int i = 0; i < childrenSize; ++i)
        {
            int j = 0;
            int numberDirectChildren = numberOfDirectChildren_helper(treeRoot, treeRoot->data);
            while(numberDirectChildren)
            {
                resultStr += treeRoot->data;
                resultStr += "-";
                resultStr += treeRoot->children[j]->data;
                resultStr += '\n';

                numberDirectChildren--;
                j++;
            }

            print_to_string_helper(treeRoot->children[i], resultStr);
        }
    }
    else
    {
        resultStr += treeRoot->data;
        return;
    }

}

/*
tree tree::join_two_trees_helper(const tree& other_tree) //vij tukkk
{
    if(other_tree.root == nullptr)
    {
        return *this;
    }

    else if(this->root == nullptr) { return other_tree; }

    tree newTree = *this;

    if(find_helper(root,))


}*/

tree::tree()
{
    root = nullptr;
}

tree::tree(const tree& other)
{
    root = copy(other.root);
}

tree::tree(tree&& other) : tree()
{
    std::swap(root, other.root);
}

tree& tree::operator=(const tree& other)
{
    if(this != &other)
    {
        destroy(root);
        root = copy(other.root);
    }

    return *this;
}

tree& tree::operator=(const tree&& other)
{
    tree cpy = other;
    std::swap(root, cpy.root);
    
    return *this;
}

tree::~tree()
{
    destroy(root);
}

treeNode* tree::getNodeByName(treeNode* treeRoot, const std::string& _name) const
{
    if(treeRoot == nullptr)
    {
        return nullptr;
    }
    
    if(treeRoot->data == _name)
    {
        return treeRoot;
    }

    int childrenSize = treeRoot->children.size();
    for(int i = 0; i< childrenSize; ++i)
    {
        getNodeByName(treeRoot->children[i], _name);
    }

    return nullptr;
}

treeNode* tree::createTree(const char* fileName)
{
    //tuka mojesh da vkarash funkciq za sortirane na imenata i pravilno izpisani imena
    std::ifstream in(fileName);

    if(!in.is_open())
    {
        throw std::logic_error("Could not open file and create tree");
        return nullptr;
    }

    
    std::string rootString;
    //std::getline(in, rootString);
    int i = 0;
    while(rootString[i] != '-')
    {
        in >> rootString[i];
        i++;
    }

    treeNode* treeRoot = new treeNode(rootString);
    int n_th_children = 0;
    //std::vector<treeNode*> childrenNodes;
    std::queue<std::string> nodes;

    nodes.push(rootString);

    i++;
    in.seekg(i);
    //rootString += '-';

    //std::string parentNode = rootString;
    std::string childString;

    //int j = 0;
    //while(rootString[i] != '/n')
    //{
    //    in >> rootString[i];
    //    childString[j] = rootString[i];
    //    i++; 
    //    j++;
    //}
    //
    //i++;
    //in.seekg(i);
    //treeNode* child = new treeNode(childString);
    //treeRoot->children.push_back(child);

    while(!in.eof())
    {
        //rootString.erase(0, i+1);//i+1 //zaradi '\n' ili i ne znam tochno
        //while(rootString[i] != '-')
        //{
        //    in >> rootString[i];
        //    i++;
        //}
        //i++;
        //in.seekg(i);

        if(rootString == nodes.front())
        {
            int k = 0;
            if(!childString.empty()) { childString.clear(); }

            while(rootString[i] != '\n')
            {
                in >> rootString[i];
                childString[k]= rootString[i];
                i++;
                k++;
            }
            treeNode* child = new treeNode(childString);
            treeRoot->children.push_back(child);
        }

        else
        {
            nodes.pop();
            nodes.push(rootString);

            int k = 0;
            if(!childString.empty()) { childString.clear(); }

            while(rootString[i] != '\n')
            {
                in >> rootString[i];
                childString[k]= rootString[i];
                i++;
                k++;
            }

            treeNode* grandchild = new treeNode(childString);
            treeRoot->children[n_th_children]->children.push_back(grandchild);
            n_th_children++;
        }
        i+=2;
        in.seekg(i);

        rootString.erase(0, i+1);//i+1 //zaradi '\n' ili i ne znam tochno
        while(rootString[i] != '-')
        {
            in >> rootString[i];
            i++;
        }

        i++;
        in.seekg(i);
    }

    in.close();
    return treeRoot;
}

bool tree::find(const std::string& _name) const
{
    return find_helper(root, _name);
}

int tree::getSize() const
{
    return size_helper(root);
}

int tree::height() const
{
    return height_helper(root);
}

int tree::level_of_a_node(const std::string& _name) const
{
    level_of_a_node_helper(root, _name);
}

int tree::numberOfDirectChildren(const std::string& _name) const
{
    return numberOfDirectChildren_helper(root, _name);
}

bool tree::insert(const std::string& _name, const std::string& _parent) const
{
    return insert_helper(root, _name, _parent);
}

bool tree::remove(const std::string& _name) const
{
    return remove_helper(root, _name);
}

bool tree::move_node(const std::string& _name, const std::string& _parent) const
{
    return move_node_helper(root, _name, _parent);
}

std::string tree::parent_of_a_node(const std::string& _name) const
{
    return parent_of_a_node_helper(root, _name);
}

int tree::numberOfIndirectChildren(const std::string& _name) const
{
    return numberOfIndirectChildren_helper(root, _name);
}

int tree::numberOfChildren(const std::string& _name) const
{
    return numberOfChildren_helper(root, _name);
}

int tree::numberOfChildren_greaterThan_Value(int value) const
{
    return numberOfChildren_greaterThan_Value_helper(root, value);
}

std::string tree::print_to_string() const
{
    std::string result;
    print_to_string_helper(root, result);
    return result;
}