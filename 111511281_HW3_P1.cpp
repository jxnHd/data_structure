#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<sstream>
#include<map>

using namespace std;

#define DEL_PTR(ptr) delete ptr; ptr = nullptr

class solution
{
private:
    struct TreeNode {
        TreeNode* left=0 ;
        TreeNode* right=0 ;

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


    inline void read() {
        std::string tmp; 

        getline(cin , tmp);
        this->inorder = solution::stringToArr(tmp);

        getline(cin , tmp);
        this->postorder = solution::stringToArr(tmp);

        // TODO: mapping inOrder index 
        //for (size_t i = 0; i < this->inOrder.size(); i++) {
            //this->inOrderMappingIndex[this->inOrder[i]] = i ; 
    }

    treeNode* dfs(vector<int> in, vector<int> post)
{
public:
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> inToIndex;

    for (int i = 0; i < inorder.size(); ++i)
      inToIndex[inorder[i]] = i;

    return build(inorder, 0, inorder.size() - 1, postorder, 0,
                 postorder.size() - 1, inToIndex);
  }

 private:
  TreeNode* build(const vector<int>& inorder, int inStart, int inEnd,
                  const vector<int>& postorder, int postStart, int postEnd,
                  const unordered_map<int, int>& inToIndex) {
    if (inStart > inEnd)
      return nullptr;

    const int rootVal = postorder[postEnd];
    const int rootInIndex = inToIndex.at(rootVal);
    const int leftSize = rootInIndex - inStart;

    TreeNode* root = new TreeNode(rootVal);
    root->left = build(inorder, inStart, rootInIndex - 1, postorder, postStart,
                       postStart + leftSize - 1, inToIndex);
    root->right = build(inorder, rootInIndex + 1, inEnd, postorder,
                        postStart + leftSize, postEnd - 1, inToIndex);
    return root;
  }
};
void level(vector<tree*> t)
{
	vector<TreeNode*> p;
	while(t.size()!=0)
	{
		if(t.size()==1)
		{
			cout<<t[0]->data<<endl;
		}
		if(t[0]->left!=0)
		{
			p.push_back(t[0]->left);
		}
		if(t[0]->right!=0)
		{
			p.push_back(t[0]->right);
		}
		t.erase(t.begin());
	}
	if(p.size()!=0)
		level(p);
}



    inline void run() {
        tree* temp=dfs(in,post);
	    vector<TreeNode*> t;
	    t.push_back(temp);
	    level(t);
	    delete temp;
    }







public:
    std::vector<int> inorder, preorder, postorder;
    TreeNode* root ; 
};




int main(){
    solution a ; 
    a.read();
    a.run();
    return 0;

}