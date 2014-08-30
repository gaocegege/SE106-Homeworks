// [TODO]
// Student ID: 5120379091
// Name: GaoCe
//
template <typename T>
class Iterator
{
public:
    T *vp;
    int index;
   Iterator()
   {
      this->vp = NULL;
   }
   Iterator(const Iterator& x)
   {
      this->vp = x.vp;
        this->index = x.index;
   }
   Iterator (T *vp, int index)
   {
      this->vp = vp;
      this->index = index;
   }
   Iterator& operator++()
   {
      index++;
      return *this;
   }
   Iterator operator++(int x)
   {
      Iterator copy(*this);
      operator++();
      return copy;
   }
   bool operator==(const Iterator& that)
   {
      return vp == that.vp && index == that.index;
   }
   bool operator!=(const Iterator& that)
   {
      return !(*this == that);
   }  
   bool operator<(const int& that)
   {
      return (this->index < that);
   }
   Iterator& operator=(const Iterator& that)
   {
      vp = that.vp;
      index = that.index;
      return *this;
   } 
   T& operator*(){
      return *(vp + (index));
    }

   Iterator& operator+=(const int& that)
   {
      this->index += that;
      return *(this);
   }

   int getIndex()
   {
      return index;
   }
 };