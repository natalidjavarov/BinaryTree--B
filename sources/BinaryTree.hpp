
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>

using namespace std;
namespace ariel
{
    template <typename T>
    class BinaryTree
    {
    private:
    struct Node
        {
            T data;
            Node *left;
            Node *right;
            Node(T data, Node *left = nullptr, Node *right = nullptr) : data(data), left(left), right(right) {}
        };
        Node *root;

    public:
        BinaryTree<T>()
        {
            root = nullptr;
        }
        //discractor
        ~BinaryTree<T>()
        {
            delete root;
        }
        //copy constrctor
        BinaryTree<T>(const BinaryTree<T> &other)
        {
            if (this->root != nullptr)
            {
                this->root = nullptr;
            }
            copyRoot(other.root);
        }
        //move
        BinaryTree<T>(BinaryTree<T> &&other) noexcept
        {
            root = other.root;
            other.root = nullptr;
        }

        BinaryTree<T> &operator=(BinaryTree<T> &&other) noexcept
        {
            delete root;
            root = other.root;
            other.root = nullptr;
        }

        BinaryTree<T> &operator=(const BinaryTree<T> other)
        {
            if (this != &other)
            {
                delete root;
                copyRoot(other.root);
            }
            return *this;
        }


//https://www.programmersought.com/article/68334261484


        void copyRoot(Node *other)
        {
            if (other == nullptr)
            {
                root = nullptr;
            }
            else
            {
                root = new Node(other->data);

                copyTree(root, other);
            }
        }
        void copyTree(Node *node, Node *other)
        {
            if (other == nullptr)
            {
                root = nullptr;
            }
            else
            {
                if (other->left != nullptr)
                {
                    node->left = new Node(other->left->data);
                }
                if (other->right != nullptr)
                {
                    node->right = new Node(other->right->data);
                }
                if (other->left != nullptr)
                {
                    copyTree(node->left, other->left);
                }
                if (other->right != nullptr)
                {
                    copyTree(node->right, other->right);
                }
            }
        }

        Node *findNode(Node *node, const T &data)
        {
            if(node==nullptr){
                node=nullptr;
            }
            if (node!=nullptr){
                for (auto it = begin(); it != end(); ++it)
                {
                    if (*it == data)
                    {
                        return it.getNode();
                    }
                }
            }
            return nullptr;
        }

        //add_root , find , add left
        BinaryTree &add_root(T data)
        {
            if (root == nullptr)
            {
                root = new Node(data);
            }
            else
            {
                root->data = data;
            }
            return *this;
        }
        BinaryTree &add_left(T node, T data)
        {
            Node *p = findNode(root, node);
            if (p == nullptr)
            {
                throw std::invalid_argument("the node is not found");
            }
            if (p->left != nullptr)
            {
                 p->left->data = data;
            }
            else
            {
                p->left = new Node(data);
            
            }

            return *this;
        }
        BinaryTree &add_right(T node, T data)
        {

            Node *p = findNode(root, node);
            if (p == nullptr)
            {
                throw std::invalid_argument("the node is not found");
            }
            if (p->right != nullptr)
            {
              p->right->data = data;
            }
            else
            {
                p->right = new Node(data);
                
            }
            return *this;
        }

//https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion
        class preorder_iterator
        {
        private:
            Node *Nodeptr;
            stack<Node *> stackNode;

        public:
            preorder_iterator(Node *p = nullptr)
            {
                if (p == nullptr)
                {
                    Nodeptr = nullptr;
                }
                else
                {
                    stackNode.push(p);
                    Nodeptr = stackNode.top();
                }
            }

            T &operator*() const
            {
                return Nodeptr->data;
            }
            T *operator->() const
            {
                return &(Nodeptr->data);
            }
            //++i
            preorder_iterator &operator++()
            {
                if (!stackNode.empty())
                {
                    Node *p = Nodeptr;
                    stackNode.pop();
                    if (p->right != nullptr)
                    {
                        stackNode.push(p->right);
                    }
                    if (p->left != nullptr)
                    {
                        stackNode.push(p->left);
                    }
                    if (stackNode.empty())
                    {
                        Nodeptr = nullptr;
                    }
                    else
                    {
                        Nodeptr = stackNode.top();
                    }
                }
                else
                {
                    Nodeptr = nullptr;
                }
                return *this;
            }

            //i++
            preorder_iterator operator++(int)
            {

                preorder_iterator tmp = *this;
                if (!stackNode.empty())
                {
                    Node *p = Nodeptr;
                    stackNode.pop();
                    if (p->right != nullptr)
                    {
                        stackNode.push(p->right);
                    }
                    if (p->left != nullptr)
                    {
                        stackNode.push(p->left);
                    }
                    if (stackNode.empty())
                    {
                        Nodeptr = nullptr;
                    }
                    else
                    {
                        Nodeptr = stackNode.top();
                    }
                }
                else
                {
                    Nodeptr = nullptr;
                }

                return tmp;
            }
            bool operator==(const preorder_iterator &rhs) const
            {
                return Nodeptr == rhs.Nodeptr;
            }
            bool operator!=(const preorder_iterator &rhs) const
            {
                return Nodeptr != rhs.Nodeptr;
            }

        }; // END OF CLASS ITERATOR PREORDER


//https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion
        class inorder_iterator
        {
        private:
            Node *Nodeptr; //Nodeptr(p);
            stack<Node *> stackNode;

        public:
            inorder_iterator(Node *p = nullptr)
            {
                if (p != nullptr)
                {
                    while (p != nullptr)
                    {
                        stackNode.push(p);
                        p = p->left;
                    }
                    Nodeptr = stackNode.top();
                    stackNode.pop();
                }
                else
                {
                    Nodeptr = nullptr;
                }
            }

            T &operator*() const
            {
                return Nodeptr->data;
            }
            T *operator->() const
            {
                return &(Nodeptr->data);
            }
            //++i
            inorder_iterator &operator++()
            {
                if (!stackNode.empty() || Nodeptr->right != nullptr)
                {
                    if (Nodeptr->right != nullptr)
                    {
                        Nodeptr = Nodeptr->right;
                        while (Nodeptr != nullptr)
                        {
                            stackNode.push(Nodeptr);
                            Nodeptr = Nodeptr->left;
                        }
                        Nodeptr = stackNode.top();
                        stackNode.pop();
                    }
                    else
                    {
                        if (stackNode.empty())
                        {
                            Nodeptr = nullptr;
                        }
                        else
                        {
                            Nodeptr = stackNode.top();
                            stackNode.pop();
                        }
                    }
                }
                else
                {
                    Nodeptr = nullptr;
                }
                return *this;
            }

            //i++
            inorder_iterator operator++(int)
            {
                inorder_iterator tmp = *this;
                if (!stackNode.empty() || Nodeptr->right != nullptr)
                {
                    if (Nodeptr->right != nullptr)
                    {
                        Nodeptr = Nodeptr->right;
                        while (Nodeptr != nullptr)
                        {
                            stackNode.push(Nodeptr);
                            Nodeptr = Nodeptr->left;
                        }
                        Nodeptr = stackNode.top();
                        stackNode.pop();
                    }
                    else
                    {
                        if (stackNode.empty())
                        {
                            Nodeptr = nullptr;
                        }
                        else
                        {
                            Nodeptr = stackNode.top();
                            stackNode.pop();
                        }
                    }
                }
                else
                {
                    Nodeptr = nullptr;
                }

                return tmp;
            }

            bool operator==(const inorder_iterator &rhs) const
            {
                return Nodeptr == rhs.Nodeptr;
            }
            bool operator!=(const inorder_iterator &rhs) const
            {
                return Nodeptr != rhs.Nodeptr;
            }
            Node *getNode()
            {
                return Nodeptr;
            }
        }; // END OF CLASS ITERATOR INORDER


         //https://www.geeksforgeeks.org/iterative-postorder-traversal/?ref=rp
        class postorder_iterator
        {
        private:
            Node *Nodeptr;
            stack<Node *> stackNode;

        public:
            postorder_iterator(Node *p = nullptr)
            {
                stack<Node *> tempStack;
                if (p != nullptr)
                {
                    tempStack.push(p);
                }
                while (!tempStack.empty())
                {
                    Nodeptr = tempStack.top();
                    tempStack.pop();
                    stackNode.push(Nodeptr);

                    if (Nodeptr->left != nullptr)
                    {
                        tempStack.push(Nodeptr->left);
                    }
                    if (Nodeptr->right != nullptr)
                    {
                        tempStack.push(Nodeptr->right);
                    }
                }
                if (stackNode.empty())
                {
                    Nodeptr = nullptr;
                }
                else
                {
                    Nodeptr = stackNode.top();
                    stackNode.pop();
                }
            }

            T &operator*() const
            {
                return Nodeptr->data;
            }
            T *operator->() const
            {
                return &(Nodeptr->data);
            }
            //++i
            postorder_iterator &operator++()
            {


                if (!this->stackNode.empty())
                {
                    this->Nodeptr = stackNode.top();
                    stackNode.pop();
                }
                else
                {
                    this->Nodeptr = nullptr;
                }
                return *this;
            }
            //i++
            postorder_iterator operator++(int)
            {

                auto tmp = *this;
                ++(*this);

                return tmp;
            }
            bool operator==(const postorder_iterator &rhs) const
            {
                return Nodeptr == rhs.Nodeptr;
            }
            bool operator!=(const postorder_iterator &rhs) const
            {
                return Nodeptr != rhs.Nodeptr;
            }
        }; // END OF CLASS ITERATOR POSTORDER

        preorder_iterator begin_preorder()
        {
            return preorder_iterator{root};
        }
        preorder_iterator end_preorder()
        {
            return preorder_iterator{nullptr};
        }
        inorder_iterator begin_inorder()
        {
            return inorder_iterator{root};
        }
        inorder_iterator end_inorder()
        {
            return inorder_iterator{nullptr};
        }
        postorder_iterator begin_postorder()
        {
            return postorder_iterator{root};
        }
        postorder_iterator end_postorder()
        {
            return postorder_iterator{nullptr};
        }
        inorder_iterator begin()
        {
            return inorder_iterator{root};
        }

        inorder_iterator end()
        {
            return inorder_iterator{nullptr};
        }
        //operator out;
        friend std::ostream &operator<<(std::ostream &out, const ariel::BinaryTree<T> &binaryTree)
        {
            return out;
        }

    }; // END OF CLASS BenaryTree
}