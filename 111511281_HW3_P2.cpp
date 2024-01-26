#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <iostream>
#include <vector>
#include <unordered_map>

#include <sstream>


using namespace std;

#define DEL_PTR(ptr) delete ptr; ptr = nullptr

class solution{

private:
    struct TreeNode {
        TreeNode* left ;
        TreeNode* right ;

        int value ; 

        TreeNode(const int& value, TreeNode* left = nullptr, TreeNode* right = nullptr) 
            : value(value), left(left), right(right){}

    };
    


public:
    inline static std::vector<int> stringToArr(const std::string& inStr){
        std::stringstream ss (inStr);
        std::vector<int> res ; 
        int number ; 

        while(ss >> number){
            res.push_back(number);
        }

        return res ; 
    }

    inline static void postOrderTraversal(TreeNode* root, std::vector<int>& postOrderArr){
        if (root== nullptr){
            return ; 
        }

        solution::postOrderTraversal(root->left , postOrderArr);
        solution::postOrderTraversal(root->right , postOrderArr);
        postOrderArr.push_back(root->value);
    }


public:
    inline void read() {
        std::string tmp; 

        getline(cin , tmp);
        this->preOrder = solution::stringToArr(tmp);

        getline(cin , tmp);
        this->inOrder = solution::stringToArr(tmp);

        // TODO: mapping inOrder index 
        for (size_t i = 0; i < this->inOrder.size(); i++) {
            this->inOrderMappingIndex[this->inOrder[i]] = i ; 
        }

    }
    

    TreeNode* buildTree() {
        return buildTreeHelper(this->preOrder, 0, this->preOrder.size(), this->inOrder, 0, this->inOrder.size());
    }

    TreeNode* buildTreeHelper(std::vector<int>& preorder, int pStart, int pEnd, std::vector<int>& inorder, int iStart, int iEnd) {
        if (pStart >= pEnd || iStart >= iEnd) {
            return nullptr;
        }
        int rootVal = preorder[pStart];

        TreeNode* root = new TreeNode(rootVal);
        int iRootIndex = this->inOrderMappingIndex[rootVal];

        int leftSubtreeSize = iRootIndex - iStart;

        root->left = buildTreeHelper(preorder, pStart + 1, pStart + 1 + leftSubtreeSize, 
                                    inorder, iStart, iRootIndex);

        root->right = buildTreeHelper(preorder, pStart + 1 + leftSubtreeSize, pEnd,
                                     inorder, iRootIndex + 1, iEnd);
        return root;
    }


    inline void run() {
        this->root = this->buildTree();


        solution::postOrderTraversal(this->root , this->postOrder);

        // TODO: print 
        for (const auto& item : this->postOrder){
            cout << item << "\n";
        }
    }

public:
    solution() = default;

    ~solution(){
        solution::deleteTree(this->root);
    }

    inline static void deleteTree(TreeNode* root){
        if(root == nullptr){
            return; 
        }

        solution::deleteTree(root->left);
        solution::deleteTree(root->right);

        if (root->left != nullptr){
            DEL_PTR(root->left);
        }

        if (root->right != nullptr){
            DEL_PTR(root->right);
        }

    }

private:
    std::vector<int> preOrder , inOrder , postOrder; 
    std::unordered_map<int,int> inOrderMappingIndex;
    TreeNode* root ; 
};

int main(){
    solution a ; 
    a.read();
    a.run();

}