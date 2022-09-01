// RBT Implementation

#include "RBTree.h"

// RBTree constructors
rb_tree::rb_tree(void): root(NULL), size(0) { } //initialisation list

template<typename Iterator_>
rb_tree::rb_tree(Iterator_ begin, Iterator_ end) {
    /// RBTree template iterator constructor
    insert(begin, end);
}

// RBTree public methods
bool rb_tree::empty(void) const { 
    return(root==NULL);	
}
iterator rb_tree::max(void) {
    return (empty()) ? end() : iterator(root->max());
}
iterator rb_tree::min(void) {
    return (empty()) ? end() : iterator(root->min());
}
iterator rb_tree::begin(void) {
    return min();	
}
iterator rb_tree::end(void) {
        return iterator();	
}

iterator rb_tree::insert(value_type value) {
    return iterator(insert(new node_type(value)));
}

iterator rb_tree::insert(iterator &current, value_type &value) {
    return insert(value);
}

template<typename Iterator_>
void rb_tree::insert(Iterator_ begin, Iterator_ end) {
for (Iterator_ i=begin; i!=end; ++i) {
    value_type v = *i;
    insert(v);
    }
}

node_type *rb_tree::insert(node_type *node) {
    binary_insert(node);
    node_type *temp = node;
    rb_adjust(temp);
    return node;
}

void rb_tree::print() {
    if (empty())
        cout<<"RBTree isn't initialized";
    else
        print(root);
}

void rb_tree::inorder_print(node_type *ptr) {
    if(ptr==NULL)
        return;
    ptr->print();
    inorder_print(ptr->left);
    inorder_print(ptr->right);
}

int rb_tree::height() {
    return height(root);
}

// RBTree protected methods
void rb_tree::print(node_type *node) {
    std::cout << std::endl;
    if(node==NULL)
        return 0;
    int h = height();
    queue<node_type *> currentLevel, nextLevel;
    currentLevel.push(node);
    while (!currentLevel.empty()) {
        node_type *currNode = currentLevel.front();
        currentLevel.pop();
        if (currNode!=NULL) {
            for(int i=(1<< h-1)* 2; i>0; i--)
                std::cout << " ";
            std::cout << currNode->value << ":" << currNode->color;
            nextLevel.push(currNode->left);
            nextLevel.push(currNode->right);
        }
        if (currentLevel.empty()) {
            std::cout << std::endl; h--;
            swap(currentLevel, nextLevel);
        }
    }
}

int rb_tree::height(node_type *node) {
	if (node==NULL)
		return 0;
	int heightLeft = height(node->left);
	int heightRight = height(node->right);
		if(heightLeft > heightRight)
		    return 1+heightLeft;
		else
			return 1+heightRight;
	}

void rb_tree::rb_adjust(node_type *node) {
    //Case 1: if node is the root
    if(node==NULL)
        return ;
    if(node->parent==NULL) {
        node->color = BLACK;
        return ;
        }
    
    node_type *p = node->parent;
    //Case 2: if parent is black
    if(p!=NULL && p->color==BLACK)
        return ;
    
    //Case 3: if parent and uncle are red
    node_type *u = p->sibling();
    if(p->color==RED && (u!=NULL && u->color==RED)) {
        p->color = BLACK;
        u->color = BLACK;
        p->parent->color = RED;
        rb_adjust(p->parent);
        return ;
    }

    //Case 4: if parent=red and uncle=black/null
    //4.1 if parent=left son
    if(p->is_a_left_son()) {
        if(node->is_a_right_son()) {
            node = p;
            left_rotate(p);
        }
        
        p->color=BLACK;
        if(p->parent!=NULL) {
            p->parent->color = RED;
        right_rotate(p->parent);
        }
        return ;
    }
    //4.2 if parent=right son
    else if (p->is_a_right_son()) {
        if(node->is_a_left_son()) {
            node = p;
            right_rotate(p);
        }
        p->color=BLACK;
        if(p->parent!=NULL) {
            p->parent->color = RED;
            left_rotate(p->parent);
        }
        return;
    }

}

void rb_tree::binary_insert(node_type *node) {
++size;
    //Case 5: root insertion
    if(empty())
        root=node;
    else {
        node_type * current= root;
        do {
            if(current->value < node->value) {
                if(current->right==NULL) {
                    node->parent = current;
                    current->right = node;
                    break;
                }
                else {
                    current = current->right;
                }
            }
            else if (current->value >= node->value) {
                if(current->left==NULL) {
                    node->parent = current;
                    current->left = node;
                    break;
                }
                else {
                    current = current->left;
                }
            }
        } while(true);
    }
    return node;
}

void rb_tree::left_rotate(node_type *node) {
    // first: checking out if exists node's right son
    if (node->right!=NULL ) {
        node_type *right_son = node->right;
        if ((node->right=node->right->left)!=NULL)
            node->right->parent = node;
        if (node->parent==NULL)
            root = right_son;
        else if (node->is_a_left_son())
            node->parent->left = right_son;
        else
            node->parent->right = right_son;
        right_son->parent = node->parent;
        node->parent = right_son;
        right_son->left = node;
    }
}

void rb_tree::right_rotate(node_type *node) {
    // first: checking out if exists node's left son
    if (node->left!=NULL) {
        node_type *left_son = node->left;
        if ((node->left=node->left->right)!=NULL)
            node->left->parent = node;
        if (node->parent==NULL)
            root = left_son;
        else if (node->is_a_left_son())
            node->parent->left = left_son;
        else
            node->parent->right = left_son;	
        left_son->parent = node->parent;
        node->parent = left_son;
        left_son->right = node;
    }
}

#TODO: implement delete method