
#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/dataset.h"
#include "ann/xtensor_lib.h"
#include "list/listheader.h"
using namespace std;

template <typename DType, typename LType>
class DataLoader {
 public:
  class Iterator;
 private:
  Dataset<DType, LType>* ptr_dataset;
  int batch_size;
  bool shuffle;
  bool drop_last;
  int size;
  int numbatch;
  XArrayList<Batch<DType,LType>> batchlist;
  xt::svector<int> randompos;
 public:
  DataLoader(Dataset<DType, LType>* ptr_dataset, int batch_size,
             bool shuffle = true, bool drop_last = false) {
    this->shuffle=shuffle, this->drop_last=drop_last;
    this->batch_size=batch_size;
    this->ptr_dataset=ptr_dataset;
    this->size=this->ptr_dataset->len();    
    for (int i=0 ; i<this->size ; i++) randompos.push_back(i);    
    if (shuffle){
      xt::xarray<int> shufflepos=xt::adapt(randompos);
      xt::random::default_engine_type engine(0);
      xt::random::shuffle(shufflepos,engine);
      for (int i=0 ; i<this->size ; i++) randompos[i]=shufflepos[i];
    }
    numbatch=this->size/this->batch_size;
    batchlist=XArrayList<Batch<DType,LType>>(NULL,NULL,numbatch);
    xt::svector<std::size_t> dshape=ptr_dataset->get_data_shape();
    xt::svector<std::size_t> lshape=ptr_dataset->get_label_shape();
    xt::svector<std::size_t> bdshape(dshape.begin(),dshape.end());
    xt::svector<std::size_t> blshape(lshape.begin(),lshape.end());
    int cnt=0;
    if (size>=batch_size){
      for (int i=0 ; i<numbatch ; i++){      
        if (!drop_last&&numbatch==1) bdshape[0]=blshape[0]=size;
        else if (!drop_last&&i==numbatch-1) bdshape[0]=blshape[0]=size%batch_size+batch_size;
        else bdshape[0]=blshape[0]=batch_size;      
        xt::xarray<DType> bdata(bdshape);
        xt::xarray<LType> blabel(blshape);      
        int n=bdshape[0];
        for (int j=0 ; j<n ; j++){        
          DataLabel<DType,LType> item=ptr_dataset->getitem(randompos[cnt]);        
          xt::xarray<DType> dataitem=item.getData();        
          xt::xarray<LType> labelitem=item.getLabel();        
          xt::view(bdata,j)=dataitem;
          if (ptr_dataset->get_label_shape().size()==0) blabel=labelitem;
          else xt::view(blabel,j)=labelitem;        
          ++cnt;
        }
        batchlist.add(Batch<DType,LType>(bdata,blabel));
      }
    }    
  }
  virtual ~DataLoader() {}
  Iterator begin() {return Iterator(this, 0);}
  Iterator end() { return Iterator(this, numbatch); }
public:
  class Iterator {
    private:
      DataLoader<DType,LType>* ptr;
      int cursor;
    public:
    friend class DataLoader<DType,LType>;
    Iterator(DataLoader<DType,LType>* ptr = 0, int cursor = 0) {this->ptr=ptr, this->cursor=cursor;}
    Iterator& operator=(const Iterator& iterator) {
      ptr=iterator.ptr;
      cursor=iterator.cursor;
      return *this;
    }

    Iterator& operator++() {
      this->cursor++;
      return *this;
    }

    Iterator operator++(int) {
      Iterator iterator=*this;
      ++*this;
      return iterator;
    }

    bool operator!=(const Iterator& other) const {return cursor!=other.cursor;}

    Batch<DType, LType>& operator*() const {
      if (cursor<0||cursor>=ptr->numbatch) throw out_of_range("Index is out of range!");
      return ptr->batchlist.get(cursor);
    }
  };
};

#endif /* DATALOADER_H */