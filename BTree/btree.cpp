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
  if (s == t->word) { return t;}
  preorder(t->left, s);
  preorder(t->right, s);
  return NULL;
}


public:
  lexicon() {
    root=NULL;
  }

  ~lexicon();

  void insert(const string &s) {
    node *p;
    p=root;
    node *n=new node(s,NULL,NULL,NULL,0);
    while(1==1) {
      if(s == p->word) { ++p->freq; delete n; break; }
      if(s < p->word) {
        if(p->left==NULL) { p->left=n; n->dep=(p->dep+1); n->parent = p; break; }
        p=p->left;
      }
      if(s > p->word) {
        if(p->right==NULL) { p->right=n; n->dep=(p->dep)+1; n->parent = p; break; }
        p=p->right;
      }
    }
  }

  int lookup (const string &s) {
    node *p;
    node *t;
    p=root;
    t=preorder(p, s);
    return t->freq;
  }

  int depth (const string &s) {
    node *p;
    p=root;
    node *t;
    t=preorder(p, s);
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
      else { insert(s2); }
      q = t->parent;
      if(q->word > t->word) { q->right = t->right;}
      else if(q->word < t->word) { q->left = t->right; }
      n = t->right;
      t = t->left; 
      while((n->left)!=NULL && (n->right)!=NULL) {
        if((n->right)->word < t->word  && t->word < (n->left)->word ) {
          p = n->right; //ksemparko
          n->right = t;
          t = p;
          n = n->right;
        }
        else if( t->word > (n->left)->word) {
          p = n->left;
          n->left = t;
          t = p;
          n = n->left;
        }
        else if( t->word < (n->right)->word) {
          n = n->right;
        }
      }
      if(n->word > t->word) { n->right = t; }       //n->right == NULL
      else if(n->word < t->word) { n->left = t; }   //n->left == NULL
    }
  }

  friend ostream &operator<< (ostream &out,const lexicon &l) {
    node *p;
    p = l.root;
  }


};


void cout (ostream &out, node *p) {
  while(p->right!=NULL) { p = p->right; }
  cout << p->word < " " p->freq << endl; 
  cout (out, p->left);
  p = p->parent;
  cout << p->word << " " << p->freq << endl;
  if(p->left!=NULL) { cout(out, p->left); }
  

}





