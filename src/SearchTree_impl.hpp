// #####  Implementierung  #####


// template<typename T>
// TreeNode<T>* TreeNode<T>::minimum() {
// 	TreeNode *min = this;
// 	while(min->left != nullptr)
// 		min = min->left;
// 	return min;
// }

// template<typename T>
// TreeNode<T>* TreeNode<T>::maximum() {
// 	TreeNode *max = this;
// 	while(max->right != nullptr)
// 		max = max->right;
// 	return max;
// }


// template<typename T>
// TreeNode<T>* TreeNode<T>::predecessor() {
// 	// if possible, traverse downwards to the left:
// 	if(this->left != nullptr)
// 		return this->left->maximum();

// 	// otherwise, traverse upwards until we land on a Node of lesser value:
// 	TreeNode *prev = this;
// 	for(TreeNode *ptr = this->parent;; ptr = ptr->parent) {
// 		// ptr == null means that we have traversed the whole tree,
// 		// entered the root node from the left side, and followed its parent- (=null-) pointer:
// 		if(ptr == nullptr)
// 			return nullptr;

// 		// if the previous node was right of the current one, we must have landed on a node of smaller value:
// 		if(prev == ptr->right)
// 			return ptr;
		
// 		prev = ptr; // store current node as previous node for next iteration
// 	}
// }

// template<typename T>
// TreeNode<T>* TreeNode<T>::successor() {
// 	// if possible, traverse downwards to the right:
// 	if(this->right != nullptr)
// 		return this->right->minimum();

// 	// otherwise, traverse upwards until we land on a Node of greater value:
// 	TreeNode *prev = this;
// 	for(TreeNode *ptr = this->parent;; ptr = ptr->parent) {
// 		// ptr == null means that we have traversed the whole tree,
// 		// entered the root node from the right side, and followed its parent- (=null-) pointer:
// 		if(ptr == nullptr)
// 			return nullptr;

// 		// if the previous node was left of the current one, we must have landed on a successive node:
// 		if(prev == ptr->left)
// 			return ptr;
		
// 		prev = ptr; // store current node as previous node for next iteration
// 	}
// }

//##################  Private:  ######################

// template<typename T>
// void SearchTree<T>::transplant(const Node *const nodeToReplace, Node *const replacement) {
// 	if(nodeToReplace->parent == nullptr)
// 		root = replacement;
// 	else if(nodeToReplace == nodeToReplace->parent->left)
// 		nodeToReplace->parent->left = replacement;
// 	else
// 		nodeToReplace->parent->right = replacement;

// 	if(replacement != nullptr)
// 		replacement->parent = nodeToReplace->parent;
// }



//##################  Public:  ######################

template<typename T>
void SearchTree<T>::rotateLeft(Node* x) {
	Node* y = x->right;
	x->right = y->left;

	if(y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;

	if(x->parent == nil)
		root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

template<typename T>
void SearchTree<T>::rotateRight(Node* x) {
	Node* y = x->left;
	x->left = y->right;

	if(y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;

	if(x->parent == nil)
		root = y;
	else if(x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

template<typename T>
void SearchTree<T>::insert(const T key) {
	Node *const newNode = new Node(key); // "z"

	Node *aboveNew = nil; // Node under which newNode will be inserted ("y")

	for (Node *x = root; x != nil; ) {
		aboveNew = x;

		if (newNode->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	newNode->parent = aboveNew; // adjust newNode's paret pointer

	if (aboveNew == nil)
		root = newNode;
	else if (newNode->key < aboveNew->key)
		aboveNew->left = newNode; // Insert newNode
	else
		aboveNew->right = newNode; // Insert newNode

	newNode->left = nil;
	newNode->right = nil;
	newNode->color = Node::RED;

	insertFixup(newNode);
}

template<typename T>
void SearchTree<T>::insertFixup(Node* z) {
	// RB-Insert-Fixup(T, z)
	while (z->parent->color == Node::RED) {
		if (z->parent == z->parent->parent->left) {
			Node* y = z->parent->parent->right;
			if (y->color == Node::RED) {
				z->parent->color = Node::BLACK; // Fall 1
				y->color = Node::BLACK; // Fall 1
				z->parent->parent->color = Node::RED; // Fall 1
				z = z->parent->parent; // Fall 1
			} else {
				if (z == z->parent->right) {
					z = z->parent; // Fall 2
					rotateLeft(z); // Fall 2
				}
				z->parent->color = Node::BLACK; // Fall 3
				z->parent->parent->color = Node::RED; // Fall 3
				rotateRight(z->parent->parent); // Fall 3
			}
		} else { // (analog zum then-Fall, nur “right” und “left” vertauschen)
			if (z->parent == z->parent->parent->right) {
				Node* y = z->parent->parent->left;
				if (y->color == Node::RED) {
					z->parent->color = Node::BLACK; // Fall 1
					y->color = Node::BLACK; // Fall 1
					z->parent->parent->color = Node::RED; // Fall 1
					z = z->parent->parent; // Fall 1
				} else {
					if (z == z->parent->left) {
						z = z->parent; // Fall 2
						rotateRight(z); // Fall 2
					}
					z->parent->color = Node::BLACK; // Fall 3
					z->parent->parent->color = Node::RED; // Fall 3
					rotateLeft(z->parent->parent); // Fall 3
				}
			}
		}
	}
	root->color = Node::BLACK;
}

// template<typename T>
// void SearchTree<T>::deleteNode(Node *const node) {
// 	if(node->left == nullptr) {
// 		// node only has a right child.
// 		// therefore we can just replace node by its right child:
//         transplant(node, node->right);
//     } else if(node->right == nullptr) {
// 		// node only has a left child.
// 		// therefore we can just replace node by its left child:
//         transplant(node, node->left);
//     } else {
// 		// at this point, node has both a left and a right child.
// 		// z=node, y=nodeSuc
//         // Node* nodeSuc = node->right->minimum(); // get node's successor
//         Node* nodeSuc = node->successor(); // get node's successor (same as node->right->minimum(), as node->right can not be null here.)

//         if(nodeSuc->parent != node) { // if node->right is not node's successor:
//             transplant(nodeSuc, nodeSuc->right); // replace node's successor by its right child 

// 			// remount node's right child as nodeSuc's right child:
//             nodeSuc->right = node->right; // adjust downward pointer
//             nodeSuc->right->parent = nodeSuc; // adjust apward (parent) pointer
//         }
// 		// at this point, all nodes that were node->right and below
// 		// have been become a single subtree with nodeSuc as its root.


// 		// replace node by its immediate successor:
//         transplant(node, nodeSuc);

// 		// since nodeSuc is node's immediate successor, nodeSuc can not possibly have a left child at this point.
// 		// therefore we can just attach node's left child as nodeSuc's left child:
//         nodeSuc->left = node->left;
//         nodeSuc->left->parent = nodeSuc;
//     }

// 	// actually free the node's memory:
// 	node->left = nullptr;  // prevent recursive deletion of child nodes
// 	node->right = nullptr; // prevent recursive deletion of child nodes
// 	delete node;
// }


template<typename T>
TreeNode<T>* SearchTree<T>::search(const T key) {
	const auto search_ = [&](const auto search, Node *root, const T key) -> Node* {
		if(root == nil)
			// return nil;
			return nullptr;

		if(key == root->key)
			return root;

		if(key < root->key)
			return search(search, root->left, key);

		return search(search, root->right, key);
	};

	return search_(search_, root, key);
}

