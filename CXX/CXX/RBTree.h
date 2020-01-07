//
// Red Black Tree Definition
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RBTree
{
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        void inorderBST(Node *&);//
        void preorderBST(Node *&);//
		void postOrderBST(Node *&ptr);//
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, int);
        int getBlackHeight(Node *);
    public:
        RBTree();
        void insertValue(int);
        void deleteValue(int);
        void merge(RBTree);
        void inorder();  //中序遍历
        void preorder(); //前序遍历
		void postOrder();//后序遍历
};


#endif //RED_BLACK_TREE_RBTREE_H
