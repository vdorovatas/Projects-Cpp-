 #include <iostream>  
    #include <cmath>  
    using namespace std;  
      
      
    class Polynomial {  
    protected:  
        class Term {  
          protected:  
              int exponent;  
              int coefficient;  
              Term *next;  
              Term(int exp, int coeff, Term *n)  
              {  
                  exponent=exp;  
                  coefficient=coeff;  
                  next=n;  
              }  
                  friend class Polynomial;  
                  friend Polynomial operator + (const Polynomial &p, const Polynomial &q);  
                  friend Polynomial operator * (const Polynomial &p, const Polynomial &q);  
                  friend ostream & operator << (ostream &out,const Polynomial &p);  
    public:  
    friend ostream & operator << (ostream &out, const Term &t)  
    {  
      {  
        if(t.exponent==0)  
        {  
            out<<abs(t.coefficient);  
        }  
        else if(t.exponent==1 && abs(t.coefficient)==1)  
        {  
            out<<"x";  
        }  
        else if(t.exponent==1)  
        {  
            out<<abs(t.coefficient)<<"x";  
        }  
        else if(abs(t.coefficient)==1)  
        {  
            out<<"x^"<<t.exponent;  
        }  
        else  
        {  
            out<<abs(t.coefficient)<<"x^"<<t.exponent;  
        }  
      }  
      return out;  
    }  
        };  
      
     private:  
     Term *top;  
      
    public:  
      
     Polynomial()  
     {  
         Term *first=new Term(0,0,NULL);  
         top=first;  
     }  
      
     Polynomial(const Polynomial &p)  
     {  
       Term *s;  
       s=p.top;  
       Term *t=new Term(s->exponent,s->coefficient,NULL);  
       top=t;  
       Term *n;  
       n=t;  
       s=s->next;  
       while(s!=NULL)  
       {  
          Term *z=new Term(1,1,NULL);  
          n->next=z;  
          n=z;  
          n->exponent=s->exponent;  
          n->coefficient=s->coefficient;  
          s=s->next;  
       }  
       }  
      
      
    ~Polynomial()  
    {  
      
        while(top!=NULL)  
        {  
            Term *p;  
            p=top;  
            top=top->next;  
            delete p;  
        }  
        delete top;  
    }  
      
    Polynomial & operator = (const Polynomial &p)  
    {  
        Term *s;  
        s=p.top;  
        while(top!=NULL)  
        {  
            Term *k;  
            k=top;  
            top=top->next;  
            delete k;  
        }  
        Term *n=new Term(s->exponent,s->coefficient,NULL);  
        top=n;  
        s=s->next;  
        while(s!=NULL)  
        {  
            Term *z=new Term(s->exponent,s->coefficient,NULL);  
            n->next=z;  
            n=z;  
            s=s->next;  
        }  
        return *this;  
    }  
      
    void addTerm(int expon, int coeff)  
    {  
        Term *p;  
        Term *s;  
        s=top;  
        p=s->next;  
        if(expon > top->exponent)  
        {  
           Term *t=new Term(expon,coeff,top);  
           top=t;  
        }  
        else if(expon == top->exponent)  
        {  
            top->coefficient=top->coefficient+coeff;  
                if(top->coefficient==0)  
                {  
                    if(p==NULL) {top->exponent=0; top->coefficient=0; top->next=NULL; }  
                    else {top=p;}  
                    delete s;  
                }  
        }  
        else if(p==NULL && (expon < top->exponent) )  
        {  
                Term *t=new Term(expon,coeff,p);  
                s->next=t;  
        }  
        else {  
        while(p!=NULL)  
        {  
            if (p->exponent < expon)  
            {  
                Term *t=new Term(expon,coeff,p);  
                s->next=t;  
                break;  
            }  
            else if(p->exponent == expon)  
            {  
                p->coefficient=p->coefficient+coeff;  
                if(p->coefficient==0)  
                {  
                    s->next=p->next;  
                    delete p;  
                }  
                break;  
            }  
            s=p;  
            p=p->next;  
        }  
           if( p==NULL && (expon < s->exponent)) {  
                Term *t=new Term(expon,coeff,NULL);  
                s->next=t;  
           }  
    }  
    }  
      
      
      
    double evaluate(double x)  
    {  
        double sum=0;  
        Term *p;  
        p=top;  
        if(top->coefficient==0) return 0;  
        else{  
        while(p!=NULL)  
        {  
            sum=sum+(p->coefficient*pow(x,p->exponent));  
            p=p->next;  
        }  
        return sum;  
        }  
    }  
      
       friend Polynomial operator + (const Polynomial &p, const Polynomial &q)  
    {  
        Polynomial p1(p);  
        Term *s;  
        s=q.top;  
        while(s!=NULL)  
        {  
            p1.addTerm(s->exponent,s->coefficient);  
            s=s->next;  
        }  
        return p1;  
    }  
      
    friend Polynomial operator * (const Polynomial &p, const Polynomial &q)  
    {  
        Polynomial p1;  
        Term *s;  
        Term *t;  
        s=q.top;  
        t=p.top;  
        while(s!=NULL)  
        {  
           while(t!=NULL)  
           {  
               p1.addTerm(t->exponent + s->exponent,t->coefficient * s->coefficient);  
               t=t->next;  
           }  
           t=p.top;  
           s=s->next;  
        }  
      
    return p1;  
    }  
      
    friend ostream & operator << (ostream &out,const Polynomial &p)  
    {  
        Term *s;  
        s=p.top;  
        if(s->coefficient==0)  
           { out << "0"; }  
        else{  
              if(s->coefficient>0)   { out << *s; }  
              else if(s->coefficient<0)  {out << "- " << *s; }  
              s=s->next;  
              while(s!=NULL)  
              {  
                if(s->coefficient>0)  
                  { out << " + " << *s; }  
                else if(s->coefficient<0)  
                  { out << " - " << *s; }  
                s=s->next;  
              }  
            }  
        return out;  
    }  
      
    };  