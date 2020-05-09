#include <iostream>
#include <string>

using namespace std;

class lexicon {
class node {
public:
string word;
int freq;
int dep;
node *right,*left,*parent;
node(const string &s, node *l, node *r, node *par, int d) : word(s),left(l), right(r), dep(d),
 freq(1), parent(par) {};
};
node *root;

node* preorder (node *t, const string &s) {
  if(t==NULL || t->word == s) { return t; }
  if(s < t->word) preorder(t->right, s);
  else if(s > t->word) preorder(t->left, s);
  }


node * right(node *p) const{
node *t;
t=p;
while(t->right!=NULL) { t = t->right; }
return t;
}

void print(ostream &out, node *t) const {
node *p;
p=t;
out << p->word << " " << p->freq << endl;
if(p->left != NULL) print(out, right(p->left));
if(p->parent == NULL) { return; }
 if((p->parent)->right == p) {
 print(out,p->parent);
}
if((p->parent)->left == p) {
 p=(p->parent)->parent;
}
}

void del (node *p) {
if(p==NULL) { return; }
 del(p->right);
 del(p->left);
 delete p;
}

void fix_depth (node *p, int d) {
if(p!=NULL) {
p->dep = d;
fix_depth(p->right, d+1);
fix_depth(p->left, d+1);
}
}
public:
  lexicon() {
    root=NULL;
  }

  ~lexicon() {
  del(root);
  }

  void insert(const string &s, int f=1) {
    node *p;
    p=root;
    node *n=new node(s,NULL,NULL,NULL,1);
    n->freq = f;
     if(root==NULL) { root=n; }
     else {
    while(1==1) {
      if(s == p->word) { ++p->freq; delete n; break; }
      if(s < p->word) {
        if(p->right==NULL) { p->right = n; n->dep = (p->dep)+1; n->parent = p; break; }
        p=p->right;
      }
      if(s > p->word) {
        if(p->left==NULL) { p->left = n; n->dep = (p->dep)+1; n->parent = p; break; }
        p=p->left;
      }
    }
     }
  }

  int lookup (const string &s) {
    node *p;
    node *t;
    p=root;
    t=preorder(p, s);
    if(t==NULL) { return 0; }
    else return t->freq;
  }

  int depth (const string &s) {
    node *p;
    p=root;
    node *t;
    t=preorder(p, s);
    if(t==NULL) return 0;
    return t->dep;
  }

  void replace(const string &s1,const string &s2) {
    node *p;
    p=root;
    node *t, *n, *q;
    t = preorder(p, s1);  //if t==NULL nothing happens
    if(t!=NULL) {
      n = preorder(p, s2);
      if(n!=NULL) { n->freq = n->freq + t->freq; }

      else { insert(s2, t->freq);  }

      if(t->right == NULL && t->left == NULL) {
           if(t->parent != NULL) {
                if((t->parent)->word > t->word) { (t->parent)->right = NULL; }
                if((t->parent)->word < t->word) { (t->parent)->left = NULL; }
              }  delete t; }

      else {

      if(t->right == NULL) { t->right = t->left; t->left = NULL; }
      q = t->parent;

      if(q!=NULL) {
        if(q->word > t->word) { q->right = t->right; (t->right)->parent = q; } //--(t->right)->dep; }
        else if(q->word < t->word) { q->left = t->right; (t->right)->parent = q; } //--(t->right)->dep; }
        }
      else if(q==NULL) {(t->right)->parent = NULL; root = t->right; }

      q = t->left;                       //ksemparko
      if(q!=NULL) { q->parent = NULL; }
      n = t->right;                     //new parent
      delete t;

      if(q!=NULL) {
      while(n->left!=NULL) { n = n->left; }
      n->left = q;
      q->parent = n;
      }
     }
     fix_depth(root,1);
  }
}

  friend ostream &operator<< (ostream &out,const lexicon &l) {
    node *p;
    p = l.root;
    l.print(out, l.right(p));
    return out;
  }


};

   int main() {
   lexicon l;
    l.insert("the");
    l.insert("boy");
    l.insert("and");
    l.insert("the");
    l.insert("wolf");
    cout << "The word the is found " << l.lookup("the") << " time(s)" << endl;
    cout << "The word and is found at depth " << l.depth("and") << endl;
    cout << l << endl << endl;
    l.replace("and", "dummy");
    cout << "After replacement:\n";
    cout << l ;
    cout << "Now the word and is found at depth " << l.depth("and") << endl;
    l.replace("boy", "dummy");
    cout  << "new lexicon:" << endl << l << endl;
    //cout << l.depth("dummy");
    l.replace ("the", "dummy");
    cout << l << endl;
    //cout << l.depth("");
    l.replace ("wolf", "dummy");
    cout << l << endl;
    cout << l.depth("dummy") << endl;
    cout << l.lookup("wolf");
}



