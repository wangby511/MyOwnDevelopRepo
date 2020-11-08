struct SegmentTreeNode {
    int val, offset, duplicate;
    SegmentTreeNode* left;
    SegmentTreeNode* right;
    SegmentTreeNode(int a):val(a),offset(0),duplicate(0),left(NULL),right(NULL){}
};
class Solution {
public:
    const int m = 1000000000 + 7;
    SegmentTreeNode* setupTree(vector<int>& tree,int begin,int end) {
        if(begin > end)return NULL;
        int mid = (begin + end) / 2;
        SegmentTreeNode* root = new SegmentTreeNode(tree[mid]);
        root->left = setupTree(tree,begin,mid - 1);
        root->right = setupTree(tree,mid + 1,end);
        return root;
        
    }
    void update(SegmentTreeNode* root, int x){
        while(root && root->val != x){
            if(root->val < x){
                root = root -> right;
            } else {
                root->offset++;
                root = root -> left;
            }
        }
        root->offset++;
        root->duplicate++;
    }
    pair<int,int> query(SegmentTreeNode* root, int x) {
        int res = 0;
        while(root && root->val != x){
            if(root->val < x){
                res += root->offset;
                root = root -> right;
            } else {
                root = root -> left;
            }
        }
        res += root->offset;
        return {res, root->duplicate};
    }
    int createSortedArray(vector<int>& instructions) {
        set<int> nonduplicate;
        for(int x:instructions)nonduplicate.insert(x);
        vector<int> tree(nonduplicate.begin(), nonduplicate.end());
        SegmentTreeNode * root = setupTree(tree,0,tree.size() - 1);
        int n = instructions.size();long long res = 0;
        for(int i = 0;i < n;i++) {
            int num = instructions[i];
            pair<int,int> q = query(root,num);
            int left = q.first - q.second;
            res = (res + min(left, i - q.first)) % m;
            update(root, num);
        }
        return res % m;
    }
};