//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Michael Ladderbush
// Version     : 1.0
// Description : Binary Search Tree in C++
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid
{
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid()
    {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node
{
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node()
    {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) : Node()
    {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree
{

private:
    Node *root;

    void addNode(Node *node, Bid bid);
    void inOrder(Node *node);
    void postOrder(Node *node);
    void preOrder(Node *node);
    Node *removeNode(Node *node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree()
{
    // FixMe (1): initialize housekeeping variables
    // root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder()
{
    // FixMe (2): In order root
    // call inOrder function and pass root
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder()
{
    // FixMe (3): Post order root
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder()
{
    // FixMe (4): Pre order root
    // preOrder root
    this->preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid)
{
    // FIXME (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr)
    {
        root = new Node(bid);
    }
    else
    {
        this->addNode(root, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId)
{
    // FIXME (6) Implement removing a bid from the tree
    // remove node root bidID
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId)
{
    // FIXME (7) Implement searching the tree for a bid
    // set current node equal to root
    Node *currentNode = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (currentNode != nullptr)
    {
        // if match found, return current bid
        if (currentNode->bid.bidId.compare(bidId) == 0)
        {
            return currentNode->bid;
        }
        else
        {
            // if bid is smaller than current node then traverse left
            if (bidId.compare(currentNode->bid.bidId) < 0)
            {
                currentNode = currentNode->left;
            }
            else
            {
                // else larger so traverse right
                currentNode = currentNode->right;
            }
        }
    }
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node *node, Bid bid)
{
    // FIXME (8) Implement inserting a bid into the tree
    // if node is larger then add to left
    if (node->bid.bidId.compare(bid.bidId) > 0)
    {
        // if no left node
        if (node->left == nullptr)
        {
            // this node becomes left
            node->left = new Node(bid);
        }
        else
        {
            // else recurse down the left node
            this->addNode(node->left, bid);
        }
    }
    else
    {
        // if no right node
        if (node->right == nullptr)
        {
            // this node becomes right
            node->right = new Node(bid);
        }
        else
        {
            // recurse down the right node
            this->addNode(node->right, bid);
        }
    }
}

/**
 * Remove a node pointer (recursive)
 *
 * @param node* Current node in tree
 * @param bid Bid to be added
 */
Node *BinarySearchTree::removeNode(Node *node, string bidId)
{
    // If the root node passed is a nullpointer return the node and exit
    if (node == nullptr)
    {
        return node;
    }

    // first compare the size of the bid and if it is smaller than the root recurse to the left side
    if (bidId.compare(node->bid.bidId) < 0)
    {
        node->left = removeNode(node->left, bidId);

        // if the bid is larger recurse to the right side
    }
    else if (bidId.compare(node->bid.bidId) > 0)
    {
        node->right = removeNode(node->right, bidId);

        // if the bid matches the one in the current node then we begin the process of deleting the nodes
    }
    else
    {

        // if the node has no children we simply delete it
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;

            // if the node has a child on one side we have to temporarily store the node, replace it with
            // the side that has a node before deleting the temporary pointer.
        }
        else if (node->left != nullptr && node->right == nullptr)
        {
            Node *temp = node;
            node = node->left;
            delete temp;
        }
        else if (node->right != nullptr && node->left == nullptr)
        {
            Node *temp = node;
            node = node->right;
            delete temp;

            // if the node has children on both sides we have to store the right node temporarily, then find the minimum
            // child on the left side. This minimum child will become the new node in place of the remove one. After this
            // node is placed we recursively perform the function again on this new tree in order to remove the specific
            // bid.
        }
        else
        {
            Node *temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    return node;
}

void BinarySearchTree::inOrder(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    // if the current node is not a null pointer we recursively call on the left node, then output the current bid
    // then we recursively call the right node.
    if (node != nullptr)
    {
        inOrder(node->left);
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
             << node->bid.fund << endl;
        return;
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node *node)
{
    // FixMe (10): Pre order root
    // if node is not equal to null ptr
    // postOrder left
    // postOrder right
    // output bidID, title, amount, fund
    if (node != nullptr)
    {
        inOrder(node->left);
        inOrder(node->right);
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
             << node->bid.fund << endl;
        return;
    }
}

void BinarySearchTree::preOrder(Node *node)
{
    // FixMe (11): Pre order root
    // if node is not equal to null ptr
    // output bidID, title, amount, fund
    // postOrder left
    // postOrder right
    if (node != nullptr)
    {
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
             << node->bid.fund << endl;
        return;
        inOrder(node->left);
        inOrder(node->right);
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid)
{
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
         << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree *bst)
{
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const &c : header)
    {
        cout << c << " | ";
    }
    cout << "" << endl;

    try
    {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++)
        {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    }
    catch (csv::Error &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch)
{
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char *argv[])
{

    // process command line arguments
    string csvPath, bidKey;
    switch (argc)
    {
    case 2:
        csvPath = argv[1];
        bidKey = "98129";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98129";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree *bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9)
    {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            // cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty())
            {
                displayBid(bid);
            }
            else
            {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
