#include "BVHTree.h"

using namespace std;

BVHTree::BVHTree(){
    root = nullptr;
}


void BVHTree::Destructer( BVHTreeNode * node){
    if(node){
        Destructer(node->leftChild);
        Destructer(node->rightChild);
        delete node;
    }
}

BVHTree::~BVHTree(){
    Destructer(root);
}

void BVHTree::printNode(std::ostream &out, BVHTreeNode *node, int level) {
	if (root == nullptr) return;
	for (int i = 0; i < level; i++) {
		out << "  ";
	}
	if (!node->isLeaf) {
		out << "+ branch || ";
		node->aabb.printAABB(out);
		out << std::endl;
		printNode(out, node->rightChild, level + 1);
		printNode(out, node->leftChild, level + 1);
	}
	else {
		out << "- ";
		if (node->parent) {
			if (node->parent->rightChild == node)
				out << "R ";
			else
				out << "L ";
		}
		out << "- leaf: " << node->name << " || ";
		node->aabb.printAABB(out);
		out << std::endl;
	}
}
std::ostream &operator<<(std::ostream &out, BVHTree &tree) {
	tree.printNode(out, tree.root, 0);
	return out;
}


void BVHTree::addBVHMember(AABB objectArea, string name){
    
    
    if (root == nullptr){ // Tree is empty
        BVHTreeNode* newNode = new BVHTreeNode(objectArea,name,true);
        newNode->parent = NULL;
        root = newNode;
        map[name] = newNode;
        
    }else if(root->isLeaf==true){ // There is exacly one node in the tree
        
        BVHTreeNode* oldRoot=root;
        BVHTreeNode* newNode = new BVHTreeNode(objectArea,name,true);
        
        AABB branchObjecktArea = oldRoot->aabb + newNode->aabb;
        
        BVHTreeNode* branchNode = new BVHTreeNode(branchObjecktArea,"branch",false);
        
        root = branchNode;
        branchNode->parent = NULL;
        
        branchNode->rightChild = oldRoot;
        branchNode->leftChild = newNode;
        
        newNode->parent = branchNode;
        oldRoot->parent = branchNode;
        
        map[name] = newNode;

        
    }else{ // There is more than one node in the tree
        
        BVHTreeNode* newNode = new BVHTreeNode(objectArea,name,true);
        BVHTreeNode* branchNode = root;
        
        int increaseInRightTreeSize = AABB::unionArea(newNode->aabb, branchNode->rightChild->aabb) - branchNode->rightChild->aabb.getArea();
        int increaseInLeftTreeSize = AABB::unionArea(newNode->aabb, branchNode->leftChild->aabb) - branchNode->leftChild->aabb.getArea();
        
        
        while(branchNode->rightChild){ //find the correct leaf
            if(increaseInRightTreeSize < increaseInLeftTreeSize){
                branchNode=branchNode->rightChild;
            }else{
                branchNode=branchNode->leftChild;
            }
        }
        
        BVHTreeNode* existingLeaf = branchNode;

        AABB branchObjecktArea = newNode->aabb + existingLeaf->aabb;
        
        branchNode = new BVHTreeNode(branchObjecktArea,"branch",false);
        
        branchNode->parent = existingLeaf->parent;
        
        branchNode->rightChild = existingLeaf;
        branchNode->leftChild = newNode;
        existingLeaf->parent = branchNode;
        newNode->parent = branchNode;
        
        if (branchNode->parent->rightChild == existingLeaf){ // connect branch node as a child from right direction
            branchNode->parent->rightChild = branchNode;
        }else{
            branchNode->parent->leftChild = branchNode;
        }
        
        while(branchNode->parent != NULL){ //adjust parents area
            branchNode->parent->aabb = branchNode->parent->rightChild->aabb + branchNode->parent->leftChild->aabb;
            branchNode = branchNode->parent;
        }
        
        map[name] = newNode;
        
    }
}

void BVHTree::removeBVHMember(string name){
    
//    if (map.find(name) == map.end()){
        
        BVHTreeNode* deleteLeaf=map[name];
        
        BVHTreeNode* deleteBranch = deleteLeaf->parent;
        
        
        BVHTreeNode* newOnlyChild;
        if(deleteBranch->rightChild == deleteLeaf){
            newOnlyChild = deleteBranch->rightChild;
        }else{
            newOnlyChild = deleteBranch->leftChild;
        }
        
        newOnlyChild->parent = deleteBranch->parent;
        
        if(deleteBranch->parent->rightChild == deleteBranch){
            deleteBranch->parent->rightChild = newOnlyChild;
        }else{
            deleteBranch->parent->leftChild = newOnlyChild;
        }
        
        delete deleteBranch;
        delete deleteLeaf;
        
        while(newOnlyChild->parent != NULL){ //adjust parents area
            newOnlyChild->parent->aabb = newOnlyChild->parent->rightChild->aabb + newOnlyChild->parent->leftChild->aabb;
            newOnlyChild = newOnlyChild->parent;
        }
        
        map.erase(name);
//    }
}


void BVHTree::moveBVHMember(string name, AABB newLocation){
    BVHTreeNode* node = map[name];
    
    AABB newArea = newLocation;  //correct here
    if (node->parent->rightChild == node){
        newArea = newLocation + node->parent->leftChild->aabb;
    }else{
        newArea = newLocation + node->parent->rightChild->aabb;
    }
    
    if (newArea.maxX == node->parent->aabb.maxX &&
        newArea.maxY == node->parent->aabb.maxY &&
        newArea.minX == node->parent->aabb.minX &&
        newArea.minY == node->parent->aabb.minY){
        node->aabb = newLocation;
    }else{
        removeBVHMember(name);
        addBVHMember(newLocation, name);
    }
}

void BVHTree::s(BVHTreeNode* currentNode, AABB object, vector<string> &a){
    if(!currentNode->isLeaf){
        if(currentNode->rightChild->aabb.collide(object)) {
            BVHTreeNode* rightNode = currentNode->rightChild;
            s(rightNode, object, a);
        }
        if(currentNode->leftChild->aabb.collide(object)){
            BVHTreeNode* leftNode = currentNode-> leftChild;
            s(leftNode, object, a);
        }
    }else if(currentNode->isLeaf && (currentNode->aabb.collide(object))){
        a.push_back(currentNode->name);
    }
}

vector<string> BVHTree::getCollidingObjects(AABB object){
    vector<string> a;
    BVHTreeNode* currentNode = root;
    s(currentNode, object, a);
    
    return a;
}



