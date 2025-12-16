#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

/* =========================
   Tree Node Definition
   ========================= */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* =========================
   Exercise 1: Traversals
   ========================= */
class BinaryTree {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top(); st.pop();
            res.push_back(node->val);
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
        return res;
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur || !st.empty()) {
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top(); st.pop();
            res.push_back(cur->val);
            cur = cur->right;
        }
        return res;
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        stack<TreeNode*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            TreeNode* node = s1.top(); s1.pop();
            s2.push(node);
            if (node->left) s1.push(node->left);
            if (node->right) s1.push(node->right);
        }
        while (!s2.empty()) {
            res.push_back(s2.top()->val);
            s2.pop();
        }
        return res;
    }

    vector<int> bfsTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            res.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return res;
    }
};

/* =========================
   Exercise 2: BST
   ========================= */
class BST {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int v) : data(v), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    Node* insertRec(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insertRec(node->left, val);
        else node->right = insertRec(node->right, val);
        return node;
    }

    bool searchRec(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        return val < node->data
            ? searchRec(node->left, val)
            : searchRec(node->right, val);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

public:
    void insert(int val) {
        root = insertRec(root, val);
    }

    bool search(int val) {
        return searchRec(root, val);
    }

    void printInorder() { inorder(root); cout << endl; }
    void printPreorder() { preorder(root); cout << endl; }
    void printPostorder() { postorder(root); cout << endl; }
};

/* =========================
   Exercise 3: Level Order
   ========================= */
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}

/* =========================
   Exercise 4: Height
   ========================= */
int treeHeightDFS(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(treeHeightDFS(root->left),
                   treeHeightDFS(root->right));
}

int treeHeightBFS(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int height = 0;

    while (!q.empty()) {
        int size = q.size();
        height++;
        while (size--) {
            TreeNode* node = q.front(); q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return height;
}

/* =========================
   Exercise 5: Path Sum
   ========================= */
bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    if (!root->left && !root->right)
        return root->val == targetSum;

    return hasPathSum(root->left, targetSum - root->val) ||
           hasPathSum(root->right, targetSum - root->val);
}

/* =========================
   Exercise 6: Inorder Successor
   ========================= */
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* succ = nullptr;
    while (root) {
        if (p->val < root->val) {
            succ = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}

/* =========================
   Exercise 7: Serialize / Deserialize
   ========================= */
class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "null,";
        return to_string(root->val) + "," +
               serialize(root->left) +
               serialize(root->right);
    }

    TreeNode* deserializeHelper(istringstream& ss) {
        string val;
        getline(ss, val, ',');
        if (val == "null") return nullptr;

        TreeNode* node = new TreeNode(stoi(val));
        node->left = deserializeHelper(ss);
        node->right = deserializeHelper(ss);
        return node;
    }

    TreeNode* deserialize(string data) {
        istringstream ss(data);
        return deserializeHelper(ss);
    }
};

/* =========================
   Exercise 8: Validate BST
   ========================= */
bool isValidBST(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* cur = root;
    long prev = LONG_MIN;

    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top(); st.pop();
        if (cur->val <= prev) return false;
        prev = cur->val;
        cur = cur->right;
    }
    return true;
}

/* =========================
   Exercise 9: Zigzag Level Order
   ========================= */
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            int idx = leftToRight ? i : size - 1 - i;
            level[idx] = node->val;

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        leftToRight = !leftToRight;
        res.push_back(level);
    }
    return res;
}

/* =========================
   Exercise 10: LCA in BST
   ========================= */
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val)
            root = root->left;
        else if (p->val > root->val && q->val > root->val)
            root = root->right;
        else
            return root;
    }
    return nullptr;
}

/* =========================
   Helpers
   ========================= */
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createSampleBST() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    return root;
}

/* =========================
   MAIN
   ========================= */
int main() {
    TreeNode* tree = createSampleTree();
    TreeNode* bst = createSampleBST();

    BinaryTree bt;

    cout << "Inorder traversal: ";
    for (int x : bt.inorderTraversal(tree)) cout << x << " ";
    cout << endl;

    cout << "Tree height (DFS): " << treeHeightDFS(tree) << endl;
    cout << "Tree height (BFS): " << treeHeightBFS(tree) << endl;

    cout << "Is valid BST: " << isValidBST(bst) << endl;

    TreeNode* lca = lowestCommonAncestor(bst, bst->left, bst->right);
    cout << "LCA of 2 and 6: " << lca->val << endl;

    return 0;
}
