#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

class ChessBoardArray {
private:
int size;
int base;
int *data;
unsigned int loc(int i,int j) const
throw(out_of_range) {
  int zi=i-base;
  int zj=j-base;
  if(zi<0 || zj<0 || zi>=size || zj>=size)
  throw out_of_range("invalid indicators");
  if(zi%2==0 && zj%2!=0)
  throw out_of_range("you hit a black box!");
  if(zi%2!=0 && zj%2==0)
  throw out_of_range("you hit a black box!");
  else {
  if(zi>1) { return (zi/2)*size + (zi%2)*(size/2 + 1*(size%2)) + zj/2; }
  else if(zi==1 || zi==0) { return zi*(size/2)+ zi*(size%2) + zj/2; }
  }
 }

protected:
  class Row {
    ChessBoardArray &p;
    int row;
    public:
      Row(ChessBoardArray &a, int i)
      : row(i) , p(a) {}
      int & operator [] (int i) const
      {
       return p.select(row,i);
      }
  };
    class ConstRow {
    const ChessBoardArray &p;
    int row;
    public:
      ConstRow(const ChessBoardArray &a,int i)
      : row(i) , p(a) {}
     const int  operator [] (int i) const
      {
       return p.select(row,i);
      }
  };

public:
  ChessBoardArray(unsigned s = 0,unsigned b = 0)
  {
    size=s;
    base=b;
    int c=(size*size)/2 + 1*(size%2);
    data=new int[c];
     for(int i=0;i<c;i++)
    {
      data[i]=0;
    }
  }

  ChessBoardArray(const ChessBoardArray &a)
  {
    size=a.size;
    base=a.base;
    int c=(size*size)/2 + 1*(size%2);
    data=new int[c];
    for(int i=0;i<c;i++)
    {
      data[i] = a.data[i];
    }
  }

  ~ChessBoardArray()
  {
    delete [] data;
  }

  ChessBoardArray & operator = (const ChessBoardArray &a)
  {
    delete [] data;
    size=a.size;
    base=a.base;
    int c=(size*size)/2 + 1*(size%2);
    data=new int[c];
    for(int i=0;i<c;i++)
    {
      data[i]=a.data[i];
    }
    return *this;
  }

  int & select(int i, int j)
  {
    return data[loc(i,j)];
  }

  const int select(int i, int j) const
  {
    return data[loc(i,j)];
  }

  const Row operator [] (int i)
  {
    return Row(*this, i);
  }

  const ConstRow operator [] (int i) const
  {
    return ConstRow(*this, i);
  }
friend ostream & operator << (ostream &out,const ChessBoardArray &a) {
int i=0;
int j=0;
while (i<a.size)
  {
    if(i%2==0) out << setw(4) << a.data[a.loc(i+a.base,j+a.base)];
    else out << setw(4) << "0";
    while(1==1)
   {
     j=j+1;
     if(j==a.size) {break;}
     if(i%2==0)
     {
       if(j%2==0) out << setw(4) << a.data[a.loc(i+a.base,j+a.base)];
       else out << setw(4) << "0";
     }
     else if (i%2!=0)
     {
       if(j%2!=0) out << setw(4) << a.data[a.loc(i+a.base,j+a.base)];
       else out << setw(4) << "0";
     }
   }
   out << endl;
   i=i+1;
   j=0;
  }
return out;
}

};




int main ()  {
  ChessBoardArray a(4);
  a[0][0] = 3;
  a[3][3] = 6;
  cout << a;
}