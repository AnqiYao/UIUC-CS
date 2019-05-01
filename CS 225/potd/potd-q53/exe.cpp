

void build(vector<TreeNode*> vec){
    root = vec[0];
    root->right = NULL;
    root->left = root->children[0];
    insert(root->children,root->left,0);
}

void insert(vector<TreeNode*> temp, TreeNode* subtree, int i){
   if(subtree->children.size() == 0)
      subtree->left = NULL;
   else  
      subtree->left = subroot->children[0];
   if(i+1<temp.size())
     subtree->right = temp[i+1];
  else 
      subtree->right = NULL;

  insert(subtree->children,subtree->left,0);
  insert(temp,subtree->right,i+1);
}






bool lookup(string temp,int i,TreeNode* curr){
  if(index == temp.length())
       return true;
  if(curr == NULL)
       return false;
  if(curr->elem == temp[i]){
    if(lookup(temp,i+1,curr->center))
      return true;
   }
    return lookup(temp,i,curr->left)||lookup(temp,i,curr->right);
}
