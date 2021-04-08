#ifndef RBT_H_
#define RBT_H_

#include <iostream>

using namespace std;

class RBNode {
private:
    int key;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    string color;
public:
    // Default constructor
    RBNode();
    // Constructor
    RBNode(int in);
    // Destructor
    // a virtual constructor is required for inheritance
    virtual ~RBNode();

    // Add to parent of current node
    void add_parent(RBNode* in);
    // Add to left of current node
    void add_left(RBNode* in);
    // Add to right of current node
    void add_right(RBNode* in);
    // Add the color to the current node
    void add_color(string c);

    // Get key
    int get_key();
    // Get parent node
    RBNode* get_parent();
    // Get left node
    RBNode* get_left();
    // Get right node
    RBNode* get_right();
    // Get color
    string get_color();

    virtual void print_info(ostream& to);
};

class RBT {
private:
    RBNode* root;
    RBNode* sentinal;

    // Walk methods
    void inorder_walk(RBNode* in, ostream& to);
    void postorder_walk(RBNode* in, ostream& to);
    void preorder_walk(RBNode* in, ostream& to);

    // Get the minimum node from the subtree of given node
    RBNode* get_min(RBNode* in);
    // Get the maximum node from the subtree of given node
    RBNode* get_max(RBNode* in);

    // Helper methods
    void rb_insert_fixup(RBNode* in);
    void rb_delete_fixup(RBNode* in);
    void transplant(RBNode* u, RBNode* v);

    // Rotate methods
    void left_rotate(RBNode* in);
    void right_rotate(RBNode* in);
public:
    // Constructor and Destructor
    RBT();
    ~RBT();

    // Modify tree
    void insert_node(RBNode* in);
    void delete_node(RBNode* out);

    // Find nodes in the tree
    RBNode* tree_min(); // minimum key value
    RBNode* tree_max(); // maximum key value
    RBNode* get_succ(RBNode* in); // successor for a given node
    RBNode* get_pred(RBNode* in); // predecessor for a given node
    void walk(ostream& to); // Traverse the tree from min to max recursively
    RBNode* tree_search(int search_key);
};
#endif
