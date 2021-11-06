/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str;
        _serialize(root, str);
        return str;
    }
    void _serialize(TreeNode* node, string& str)
    {
        if (node == NULL)
            str += "None,";
        else
        {
            str += to_string(node->val) + ",";
            _serialize(node->left, str);
            _serialize(node->right, str);
        }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        string str;
        list<string> dataArr;
        for (auto& e : data)
        {
            if (e == ',')
            {
                dataArr.push_back(str);
                str.clear();
            }
            else
                str.push_back(e);
        }
        if (!str.empty())
        {
            dataArr.push_back(str);
            str.clear();
        }
        return _deserialize(dataArr);
    }

    TreeNode* _deserialize(list<string>& dataArr) {
        if (dataArr.front() == "None")
        {
            dataArr.erase(dataArr.begin());
            return NULL;
        }
        TreeNode* root = new TreeNode(stoi(dataArr.front()));
        dataArr.erase(dataArr.begin());
        root->left = _deserialize(dataArr);
        root->right = _deserialize(dataArr);
        return root;
    }
};


// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));