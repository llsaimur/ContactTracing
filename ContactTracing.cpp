#include <iostream>
#include <list>
#include "ContactTree.h"
using namespace std;

//We decided to choose a queue as our linear data structure for our Contract Tracing system.
//With a queue we can add new contacts at the end of the queue as well as retrieve one from the front.
//Both enqueue and dequeue operations in Queue have O(1) complexity, this means that our traversal will be efficent
//no matter how many contacts there are. Using a queue also allows us to use the Breadth first Search Traversal
//algorithm, this helps us move through the contact tree from top to bottom, and a queue pairs perfectly with this
//since it follows the first in first out rule, thus making it the most suitable choice for this data structure.

///////////////////////////////////////////////////////////////


// Constructor
template <typename T>
ContactTree<T>::ContactTree() : root(nullptr) {}

// Destructor
template <typename T>
ContactTree<T>::~ContactTree()
{
    if (root != nullptr) {
        DeleteSubtree(root);
    }
}

//check if the tree is empty
template <typename T>
bool ContactTree<T>::IsEmpty()
{
    return root == nullptr;
}

//get the size of the tree
template <typename T>
int ContactTree<T>::GetSize()
{
    return root->totalCases;
}

////get the size of the tree
//template <typename T>
//int ContactTree<T>::GetSize()
// {
//    int size = 0;
//    Queue<TreeNode<T>*> nodesQueue;
//
//    //check if not empty
//    if (root != nullptr) {
//        nodesQueue.Enqueue(root);
//    }
//
//    // keep looping until queue empty (breadth-first search) traversal
//    while (!nodesQueue.IsEmpty()) {
//
//        // first node gets dequeued and assigned to a pointer (current)
//        TreeNode<T>* current = nodesQueue.Front();
//        nodesQueue.Dequeue();
//        //update
//        size++;
//
//        // each child node (pointers in directContactsPtrList) of current are added to nodesQueue
//        for (TreeNode<T>* child : current->directContactsPtrList) {
//            nodesQueue.Enqueue(child);
//        }
//    }
//
//    return size;
//}

//add patient zero
template <typename T>
void ContactTree<T>::AddPatient0(const T& medId)
{
    //check if exist already
    if (root != nullptr) {
        cout << "Patient 0 already exists." << endl;
        return;
    }

    //create new treenode 
    root = new TreeNode<T>(medId);
}

//add contact between two nodes
template <typename T>
void ContactTree<T>::AddContact(const T& parentMedId, const T& childMedId)
{
    //find parent node in the tree
    TreeNode<T>* parentNode = LookUpContact(parentMedId);
    if (parentNode == nullptr) {
        cout << "Parent with medicare ID " << parentMedId << " not found." << endl;
        return;
    }

    //create new node(child) and add to parent's list of direct contacts
    TreeNode<T>* childNode = new TreeNode<T>(parentNode, childMedId);
    parentNode->directContactsPtrList.push_back(childNode);

    //update contacts/cases
    parentNode->directContacts++;
    UpdateTotalCases(parentNode);
}

//look up a contact by medicare ID
template <typename T>
TreeNode<T>* ContactTree<T>::LookUpContact(const T& medId)
{
    //check if tree empty
    if (root == nullptr)
        return nullptr;

    //using queue
    Queue<TreeNode<T>*> nodesQueue;
    nodesQueue.Enqueue(root);

    //traverse the lists (breadth first search traversal) until all nodes are checked
    while (!nodesQueue.IsEmpty()) {
        TreeNode<T>* current = nodesQueue.Front();
        nodesQueue.Dequeue();

        if (current->medicareId == medId) {
            return current; // found node
        }

        //add all direct contacts of the curent node to the queue
        for (TreeNode<T>* child : current->directContactsPtrList) {
            nodesQueue.Enqueue(child);
        }
    }

    return nullptr; // no match
}

////delete a contact and its subtree
//template <typename T>
//void ContactTree<T>::DeleteContact(const T& medId)
// {
//    //find node to delete
//    TreeNode<T>* nodeToDelete = findNode(medId);
//    if (nodeToDelete == nullptr) {
//        cout << "Contact with medicare ID " << medId << " not found." << endl;
//        return;
//    }
//
//    // If the node to delete is the root
//    if (nodeToDelete == root) {
//        DeleteSubtree(root);
//        root = nullptr; // update pointer to indicate empty tree
//        return;
//    }
//
//    // node has a parent node?, if yes store the pointer(parent) to the parent node of the nodeToDelete
//    TreeNode<T>* parent = nodeToDelete->parentPtr;
//    if (parent != nullptr) {
//
//        //iterate tru the list of nodes(child) of the parent
//        for (TreeNode<T>* child : parent->directContactsPtrList) {
//            if (child == nodeToDelete) {
//                parent->directContactsPtrList.remove(nodeToDelete);
//                // Update
//                parent->directContacts--;
//                UpdateTotalCases(parent);
//                break; // Stop searching once found
//            }
//        }
//    }
//
//    DeleteSubtree(nodeToDelete);
//}

template <typename T>
void ContactTree<T>::DeleteContact(const T& medId)
{
    //find node to delete
    TreeNode<T>* nodeToDelete = LookUpContact(medId);

    if (nodeToDelete == nullptr) {
        cout << "Contact with medicare ID " << medId << " not found." << endl;
        return;
    }

    if (nodeToDelete == root) {
        DeleteSubtree(root);
        root = nullptr; // Update root pointer to indicate an empty tree
        return;
    }

    // node has a parent node?, if yes store the pointer(parent) to the parent node of the nodeToDelete
    TreeNode<T>* parent = nodeToDelete->parentPtr;

    DeleteSubtree(nodeToDelete);

    parent->directContactsPtrList.remove(nodeToDelete);
    parent->directContacts--;
    UpdateTotalCases(parent);
}

//display contact information by medicare ID
template <typename T>
void ContactTree<T>::DisplayContact(const T& medId)
{
    TreeNode<T>* node = LookUpContact(medId);
    if (node == nullptr) {
        cout << "Contact with medicare ID " << medId << " not found." << endl;
        return;
    }
    DisplayContact(node);
}

//display contact information by TreeNode pointer
template <typename T>
void ContactTree<T>::DisplayContact(TreeNode<T>* node)
{
    cout << "Medicare ID: " << node->medicareId << endl;
    cout << "Direct Contacts: " << node->directContacts << endl;
    cout << "Total Cases: " << node->totalCases << endl;
}

//trace the source of infection given a medicare ID
template <typename T>
void ContactTree<T>::TraceSource(const T& medId)
{
    TreeNode<T>* node = LookUpContact(medId);
    if (node == nullptr) {
        cout << "Contact with medicare ID " << medId << " not found." << endl;
        return;
    }

    //if node found, initialize pointer for node
    TreeNode<T>* current = node;

    //keep going until it reaches the root/parent
    while (current != nullptr) {
        DisplayContact(current);
        current = current->parentPtr;
    }
}

//print contact cases given a medicare ID
template <typename T>
void ContactTree<T>::PrintContactCases(const T& medId)
{
    TreeNode<T>* node = LookUpContact(medId);
    if (node == nullptr) {
        cout << "Contact with medicare ID " << medId << " not found." << endl;
        return;
    }

    for (TreeNode<T>* contact : node->directContactsPtrList) {
        DisplayContact(contact);
    }
}

//print the entire contact tree using BFS
template <typename T>
void ContactTree<T>::PrintContactTree()
{

    //make a queue
    Queue<TreeNode<T>*> nodesQueue;

    if (root != nullptr) {
        nodesQueue.Enqueue(root);
    }


    while (!nodesQueue.IsEmpty()) {
        //dequeue the first node and store it in pointer current
        TreeNode<T>* current = nodesQueue.Front();
        nodesQueue.Dequeue();

        DisplayContact(current);

        //then keep looping through each child node of current and add it to the queue
        for (TreeNode<T>* child : current->directContactsPtrList) {
            nodesQueue.Enqueue(child);
        }
    }
}

////print hierarchical tree
//template <typename T>
//void ContactTree<T>::PrintHierarchicalTree()
// {
//    if (root == nullptr) {
//        cout << "Tree is empty." << endl;
//        return;
//    }
//
//    Queue<TreeNode<T>*> nodesQueue;
//    nodesQueue.Enqueue(root);
//
//    while (!nodesQueue.IsEmpty()) {
//        // Get the front node from the queue
//        TreeNode<T>* current = nodesQueue.Front();
//        nodesQueue.Dequeue();
//        cout << "Medicare ID: " << current->medicareId << endl;
//
//        // Enqueue all child nodes of the current node
//        for (TreeNode<T>* child : current->directContactsPtrList) {
//            nodesQueue.Enqueue(child);
//        }
//    }
//}



template <typename T>
void ContactTree<T>::DeleteSubtree(TreeNode<T>* node)
{
    if (node == nullptr) return;

    // initialize queue
    Queue<TreeNode<T>*> nodesQueue;

    //node(root of subtree)
    nodesQueue.Enqueue(node);

    // keep looping until queue empty (breadth-first search) traversal
    while (!nodesQueue.IsEmpty()) {

        // first node gets dequeued and assigned to a pointer (current)
        TreeNode<T>* current = nodesQueue.Front();
        nodesQueue.Dequeue();

        // each child node (pointers in directContactsPtrList) of current are added to nodesQueue
        for (TreeNode<T>* child : current->directContactsPtrList) {
            //nodesQueue.Dequeue(child);
            nodesQueue.Enqueue(child);
        }

        delete current;
    }
}

template <typename T>
void ContactTree<T>::PrintHierarchicalTree()
{
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    PrintTreeRecursive(root, 0);
}

template <typename T>
void ContactTree<T>::PrintTreeRecursive(TreeNode<T>* node, int i)
{
    if (node == nullptr) {
        return;
    }

    for (int j = 0; j < i; j++)
        cout << "\t";

    cout << "Medicare ID: " << node->medicareId << endl;

    for (TreeNode<T>* child : node->directContactsPtrList) {
        PrintTreeRecursive(child, i + 1);
    }
}

//function to update totalCases up the tree
template <typename T>
void ContactTree<T>::UpdateTotalCases(TreeNode<T>* node)
{
    while (node != nullptr) {
        node->totalCases++;
        node = node->parentPtr;
    }
}
//
//int main()
// {
//    // Testing the ContactTree class with string values
//    ContactTree<string> tree;
//
//    // add patient zero
//    tree.AddPatient0("A");
//
//    // add contacts
//    tree.AddContact("A", "B");
//    tree.AddContact("A", "C");
//    tree.AddContact("B", "D");
//    tree.AddContact("B", "E");
//    tree.AddContact("C", "F");
//
//    // contact information
//    tree.DisplayContact("B");
//
//    // trace source of infection
//    tree.TraceSource("D");
//
//    // hierarchical tree
//    tree.PrintHierarchicalTree();
//
//    return 0;
//}

int main()
{
    // Testing the ContactTree class with int values
    ContactTree<int> tree;


    // add patient zero
    tree.AddPatient0(1);

    // add contacts
    tree.AddContact(1, 2);
    tree.AddContact(1, 3);
    tree.AddContact(2, 4);
    tree.AddContact(2, 5);
    tree.AddContact(3, 6);

    cout << "Contact Info:\n";
    // contact information
    tree.DisplayContact(2);
    cout << "\nHierarchchical Tree:\n ";
    // hierarchical tree
    tree.PrintHierarchicalTree();
    cout << "\nPatients in Contact Tree:\n ";
    // contact tree
    tree.PrintContactTree();
    cout << "\nContact cases of patient:\n ";
    // contact cases of a given patient
    tree.PrintContactCases(3);
    cout << "\nTrace source of contact:\n ";
    // trace source
    tree.TraceSource(4);

    cout << "\n\nDeleting contact with the ID of 2...\n ";
    tree.DeleteContact(2);

    cout << "\nContact Info:\n";
    // contact information
    tree.DisplayContact(2);
    cout << "\nHierarchchical Tree:\n ";
    // hierarchical tree
    tree.PrintHierarchicalTree();
    cout << "\nPatients in Contact Tree:\n ";
    // contact tree
    tree.PrintContactTree();
    cout << "\nContact cases of patient:\n ";
    // contact cases of a given patient
    tree.PrintContactCases(3);
    cout << "\nTrace source of contact:\n ";
    // trace source
    tree.TraceSource(4);
    
    //so the console doesn't close immediately
    system("pause");
 
    return 0;
}
