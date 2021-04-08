#include "rbt.h"
#define NEG_INF -2147483648

// ---------------------------------------
// RBNode class
// Default constructor
RBNode::RBNode() {
	key = 0;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = "red";
}

// Constructor
RBNode::RBNode(int in) {
	key = in;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = "red";
}

// Destructor
RBNode::~RBNode() {
}

#if 1
// Add parent 
void RBNode::add_parent(RBNode* in) {
	parent = in;
}

// Add to left of current node
void RBNode::add_left(RBNode* in) {
	left = in;
}

// Add to right of current node
void RBNode::add_right(RBNode* in) {
	right = in;
}

void RBNode::add_color(string c) {
	color = c;
}
#endif

#if 1
// Get key
int RBNode::get_key()
{
	return key;
}

// Get parent node
RBNode* RBNode::get_parent()
{
	return parent;
}

// Get left node
RBNode* RBNode::get_left()
{
	return left;
}

// Get right node
RBNode* RBNode::get_right()
{
	return right;
}

string RBNode::get_color()
{
	return color;
}
#endif

// Helper method to print the info in the RBNode
void RBNode::print_info(ostream& to)
{
	// Print the key and color of the node
	to << "KEY: " << this->get_key() << endl;
    	to << "COLOR: " << this->get_color() << endl;
    	
	// Print the parent node
	if (this->parent->get_key() != NEG_INF)
		to << "PARENT: " << this->parent->get_key() << endl;
    	else
		to << "PARENT: nullptr" << endl;
    	
	// Print the left node
	if (this->left->get_key() != NEG_INF)
	    	to << "LEFT: " << this->left->get_key() << endl;
    	else
	    	to << "LEFT: nullptr" << endl;
    	
	// Print the right node
	if (this->right->get_key() != NEG_INF)
	    	to << "RIGHT: " << this->right->get_key() << endl;
    	else
	    	to << "RIGHT: nullptr" << endl;
	to << endl;
}

// ---------------------------------------


// ---------------------------------------
// RBT class

// Preorder walk method
void RBT::preorder_walk(RBNode* in, ostream& to)
{
	if (in != sentinal) {
		// Print the node's info
		in->print_info(to);
		// Traverse the left side
		inorder_walk(in->get_left(), to);
		// Traverse the right side
		inorder_walk(in->get_right(), to);
	}

}

// Inorder walk method
void RBT::inorder_walk(RBNode* in, ostream& to)
{
	if (in != sentinal) {
		// Traverse the left side
		inorder_walk(in->get_left(), to);
		// Print the node's info
		in->print_info(to);
		// Traverse the right side
		inorder_walk(in->get_right(), to);
	}
}

// Postorder walk method
void RBT::postorder_walk(RBNode* in, ostream& to)
{
	if (in != sentinal) {
		// Traverse the left side
		inorder_walk(in->get_left(), to);
		// Traverse the right side
		inorder_walk(in->get_right(), to);
		// Print the node's info
		in->print_info(to);
	}
}

// Constructor
RBT::RBT()
{
	sentinal = new RBNode(NEG_INF);
	sentinal->add_color("black");
	sentinal->add_left(nullptr);
	sentinal->add_right(nullptr);
	sentinal->add_parent(nullptr);

	root = sentinal;
}

// Destructor
RBT::~RBT()
{
	while (root != sentinal) {
		RBNode* min = RBT::tree_min();
		delete_node(min);
	}
	delete sentinal;
}

// Insert a node to the subtree
void RBT::insert_node(RBNode* in)
{
	// Error checking
	if (in == nullptr) {
		cerr << "ERROR: node to be inserted is nullptr" << endl;
		exit(EXIT_FAILURE);
	}

	// Start at the root and initialize a Node that will become the inserted node
	RBNode *y = sentinal;
	RBNode *x = root;

	// Traverse BST to figure out where to insert
	while (x != sentinal) {
		y = x;
		if (in->get_key() < x->get_key()) {
			x = x->get_left();
		} 
		else {
			x = x->get_right();
		}
	}

	// Insert the node
	in->add_parent(y);
	if (y == sentinal) {
		root = in;
	}
	else if (in->get_key() < y->get_key()) {
		y->add_left(in);
	}
	else {
		y->add_right(in);
	}

	// Set the children of the inserted node to be the sentinal and make the inserted node red
	in->add_left(sentinal);
	in->add_right(sentinal);
	in->add_color("red");

	// Fix up the tree so it maintains correct rb tree form
	rb_insert_fixup(in);
}

// Helper method to clean up the tree after insertion
void RBT::rb_insert_fixup(RBNode* in) 
{
	// This code was modeled from the textbook
	RBNode* y = nullptr;
	while (in->get_parent()->get_color() == "red") {
		if (in->get_parent() == in->get_parent()->get_parent()->get_left()) {
			y = in->get_parent()->get_parent()->get_right();
			if (y->get_color() == "red") {
				in->get_parent()->add_color("black");
				y->add_color("black");
				in->get_parent()->get_parent()->add_color("red");
				in = in->get_parent()->get_parent();
			}
			else {
				if (in == in->get_parent()->get_right()) {
					in = in->get_parent();
					left_rotate(in);
				}
				in->get_parent()->add_color("black");
				in->get_parent()->get_parent()->add_color("red");
				right_rotate(in->get_parent()->get_parent());
			}
		}
		else {
			y = in->get_parent()->get_parent()->get_left();
			if (y->get_color() == "red") {
				in->get_parent()->add_color("black");
				y->add_color("black");
				in->get_parent()->get_parent()->add_color("red");
				in = in->get_parent()->get_parent();
			}
			else {
				if (in == in->get_parent()->get_left()) {
					in = in->get_parent();
					right_rotate(in);
				}
				in->get_parent()->add_color("black");
				in->get_parent()->get_parent()->add_color("red");
				left_rotate(in->get_parent()->get_parent());
			}
		}
	}
	root->add_color("black");
}

// Delete a node to the subtree
void RBT::delete_node(RBNode* out)
{
	// Inititalize x and y nodes and save y's color to a variable
	RBNode* x = nullptr;
	RBNode* y = out;
	string y_color = y->get_color();

	// The node to delete doesn't have a left child
	if (out->get_left() == sentinal) {
		x = out->get_right();
		transplant(out, out->get_right());
	}
	// The node to delete doesn't have a right child
	else if (out->get_right() == sentinal) {
		x = out->get_left();
		transplant(out, out->get_left());
	}
	// The node has two children
	else {
		y = get_min(out->get_right());
		y_color = y->get_color();
		x = y->get_right();
		// The successor's parent isn't the node we're deleting
		if (y->get_parent() != out) {
			transplant(y, y->get_right());
			// Add a right child and parent to y
			y->add_right(out->get_right());
			y->get_right()->add_parent(y);
		}
		else {
			x->add_parent(y);
		}
		transplant(out, y);
		// Add a left child and parent to y
		y->add_left(out->get_left());
		y->get_left()->add_parent(y);
		y->add_color(out->get_color());
	}

	// If y's color is black, fixup the tree
	if (y_color == "black")
		rb_delete_fixup(x);

	// Delete the node we wanted to delete
	delete out;
}

// Helper method to help cleanup the tree after deletion
void RBT::rb_delete_fixup(RBNode* in) 
{
	// This code was modeled from the textbook
	RBNode* w = nullptr;
	while (in != root and in->get_color() == "black") {
		if (in == in->get_parent()->get_left()) {
			w = in->get_parent()->get_right();
			if (w->get_color() == "red") {
				w->add_color("black");
				in->get_parent()->add_color("red");
				left_rotate(in->get_parent());
				w = in->get_parent()->get_right();
			}
			if (w->get_left()->get_color() == "black" and w->get_right()->get_color() == "black") {
				w->add_color("red");
				in = in->get_parent();
			}
			else {
				if (w->get_right()->get_color() == "black") {
					w->get_left()->add_color("black");
					w->add_color("red");
					right_rotate(w);
					w = in->get_parent()->get_right();
				}
				w->add_color(in->get_parent()->get_color());
				in->get_parent()->add_color("black");
				w->get_right()->add_color("black");
				left_rotate(in->get_parent());
				in = root;
			}
		}
		else {
			w = in->get_parent()->get_left();
			if (w->get_color() == "red") {
				w->add_color("black");
				in->get_parent()->add_color("red");
				right_rotate(in->get_parent());
				w = in->get_parent()->get_left();
			}
			if (w->get_right()->get_color() == "black" and w->get_left()->get_color() == "black") {
				w->add_color("red");
				in = in->get_parent();
			}
			else {
				if (w->get_left()->get_color() == "black") {
					w->get_right()->add_color("black");
					w->add_color("red");
					left_rotate(w);
					w = in->get_parent()->get_left();
				}
				w->add_color(in->get_parent()->get_color());
				in->get_parent()->add_color("black");
				w->get_left()->add_color("black");
				right_rotate(in->get_parent());
				in = root;
			}
		}
	}
	in->add_color("black");
}

// Helper method to left rotate the tree
void RBT::left_rotate(RBNode* in)
{
	RBNode* y = in->get_right();
	in->add_right(y->get_left());

	if (y->get_left() != sentinal)
		y->get_left()->add_parent(in);
	y->add_parent(in->get_parent());

	if (in->get_parent() == sentinal)
		root = y;
	else if (in == in->get_parent()->get_left())
		in->get_parent()->add_left(y);
	else
		in->get_parent()->add_right(y);
	y->add_left(in);
	in->add_parent(y);
}

// Helper method to right rotate the tree
void RBT::right_rotate(RBNode* in)
{
	RBNode* y = in->get_left();
	in->add_left(y->get_right());

	if (y->get_right() != sentinal)
		y->get_right()->add_parent(in);
	y->add_parent(in->get_parent());

	if (in->get_parent() == sentinal)
		root = y;
	else if (in == in->get_parent()->get_right())
		in->get_parent()->add_right(y);
	else
		in->get_parent()->add_left(y);
	y->add_right(in);
	in->add_parent(y);
}


// minimum key in the BST
RBNode* RBT::tree_min()
{
	// If the root is the sentinal just return null
	if (root == sentinal)
		return nullptr;

	// Start with the min being the root
	RBNode *min = root;

	// Go all the way to the left to get the min
	while (min->get_left() != sentinal) {
		min = min->get_left();
	}
	return min;
}

// maximum key in the BST
RBNode* RBT::tree_max()
{
	// If the root is the sentinal just return null
	if (root == sentinal)
		return nullptr;

	// Start with the min being the root
	RBNode *max = root;

	// Go all the way to the left to get the min
	while (max->get_right() != sentinal) {
		max = max->get_right();
	}
	return max;
}

// Get the minimum node from the subtree of given node
RBNode* RBT::get_min(RBNode* in)
{
	// Go all the way to the left in the subtree and return that node
	while (in->get_left() != sentinal) {
		in = in->get_left();
	}
	return in;
}

// Get the maximum node from the subtree of given node
RBNode* RBT::get_max(RBNode* in)
{
	// Go all the way to the right in the subtree and return that node
	while (in->get_right() != sentinal) {
		in = in->get_right();
	}
	return in;
}

// Get successor of the given node
RBNode* RBT::get_succ(RBNode* in)
{
	// If in has a right subtree, return the min from there
	if (in->get_right() != sentinal) {
		return get_min(in->get_right());
	}

	// Otherwise, go up the tree until you find the successor
	RBNode *y = in->get_parent();
	while (in != sentinal and in == y->get_right()) {
		in = y;
		y = y->get_parent();
	}

	// If the successor is the sentinal return null, otherwise return successor
	if (y == sentinal)
		return nullptr;
	else
		return y;
}

// Get predecessor of the given node
RBNode* RBT::get_pred(RBNode* in)
{
	// If in has a left subtree, return the min from there
	if (in->get_left() != sentinal) {
		return get_max(in->get_left());
	}

	// Otherwise, go up the tree until you find the predecessor
	RBNode *y = in->get_parent();
	while (in != sentinal and in == y->get_left()) {
		in = y;
		y = y->get_parent();
	}

	// If the predecessor is the sentinal return null, otherwise return the predecessor
	if (y == sentinal)
		return nullptr;
	else
		return y;
}

// Walk the BST from min to max
void RBT::walk(ostream& to)
{
	inorder_walk(root, to);
}

// Search the tree for a given key
RBNode* RBT::tree_search(int search_key)
{
	// Start at the root and search the whole tree for search_key
	RBNode *x = root;
	while (x != nullptr and search_key != x->get_key()) {
		if (search_key < x->get_key()) {
			x = x->get_left();
		}
		else {
			x = x->get_right();
		}
	}
	return x;
}

// Helper method for delete
void RBT::transplant(RBNode *u, RBNode *v) {
	// u's parent is null (we are at the root)
	if (u->get_parent() == sentinal) {
		root = v;
	}
	// u is the left child of it's parent
	else if (u == u->get_parent()->get_left()) {
		u->get_parent()->add_left(v);
	}
	// u is the right child of it's parent
	else {
		u->get_parent()->add_right(v);
	}

	// v is an actual node so we have to replace it's parent with u's
	v->add_parent(u->get_parent());
}
// ---------------------------------------
