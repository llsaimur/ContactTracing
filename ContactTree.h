#include "Queue.cpp"
#include "TreeNode.cpp"

template <typename T>
class ContactTree
{
private:
    TreeNode<T>* root;

    void UpdateTotalCases(TreeNode<T>* node);
    void DeleteSubtree(TreeNode<T>* node);
    

public:
    ContactTree();
    ~ContactTree();
    bool IsEmpty();
    int GetSize();
    void AddPatient0(const T& medId);
    void AddContact(const T& parentMedId, const T& childMedId);
    TreeNode<T>* LookUpContact(const T& medId);
    void DeleteContact(const T& medId);
    void DisplayContact(const T& medId);
    void DisplayContact(TreeNode<T>* node);
    void TraceSource(const T& medId);
    void PrintContactCases(const T& medId);
    void PrintContactTree();
    void PrintHierarchicalTree();
    void PrintTreeRecursive(TreeNode<T>* node, int i);
};