#ifndef JGADGET_LINK_H
#define JGADGET_LINK_H

#include "types.h"

#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JGadget/define.h"

#ifdef __cplusplus
namespace JGadget {

#define NEGATIVE_OFFSETOF(TYPE, MEMBER) (-static_cast<s32>(offsetof(TYPE, MEMBER)))
#define TLINKLIST_NODE_OFS(TYPE) (NEGATIVE_OFFSETOF(TYPE, mNode))
#define TLinkList(TYPE) TLinkList<TYPE, TLINKLIST_NODE_OFS(TYPE)>

namespace {

template <typename T>
class TPRIsEqual_pointer_ {
public:
  TPRIsEqual_pointer_(const T* p) { this->p_ = p; }

  bool operator()(const T& rSrc) const {
    return &rSrc == this->p_;
  }

private:
  const T* p_;
};

}

class TLinkListNode {
public:
  TLinkListNode() {
    this->pNext_ = nullptr;
    this->pPrev_ = nullptr;
  }

  ~TLinkListNode() {
    // Seemingly not present in earlier versions of JSystem
    /*
    #line 77
    JUT_ASSERT(pNext_==NULL);
    JUT_ASSERT(pPrev_==NULL);
    */
  }

  TLinkListNode* getNext() const {
    return this->pNext_;
  }

  TLinkListNode* getPrev() const {
    return this->pPrev_;
  }

  void clear_() {
    this->pNext_ = nullptr;
    this->pPrev_ = nullptr;
  }

  TLinkListNode* pNext_;
  TLinkListNode* pPrev_;
};

class TNodeLinkList {
public:
  TNodeLinkList() : oNode_() { Initialize_(); }
  ~TNodeLinkList();

  class const_iterator;

  class iterator {
  public:
    friend class TNodeLinkList::const_iterator;
    friend class TNodeLinkList;
  
    iterator() { this->p_ = nullptr; }
    iterator(TLinkListNode* node) { this->p_ = node; }

    friend bool operator==(TNodeLinkList::iterator lhs, TNodeLinkList::iterator rhs) { return lhs.p_ == rhs.p_; }
    friend bool operator!=(TNodeLinkList::iterator lhs, TNodeLinkList::iterator rhs) { return !(lhs == rhs); }

    iterator& operator++() {
      this->p_ = this->p_->getNext();
      return *this;
    }

    iterator& operator--() {
      this->p_ = this->p_->getPrev();
      return *this;
    }

    TLinkListNode& operator*() const {
      return *this->p_;
    }

    TLinkListNode* operator->() const { return this->p_; }
    
  private:
    TLinkListNode* p_;
  };

  class const_iterator {
  public:
    friend class TNodeLinkList;

    const_iterator(const TLinkListNode* node) { this->p_ = node; }
    const_iterator(iterator it) { this->p_ = it.p_; }

    friend bool operator==(TNodeLinkList::const_iterator lhs, TNodeLinkList::const_iterator rhs) { return lhs.p_ == rhs.p_; }
    friend bool operator!=(TNodeLinkList::const_iterator lhs, TNodeLinkList::const_iterator rhs) { return !(lhs == rhs); }

    const const_iterator& operator++() {
      this->p_ = this->p_->getNext();
      return *this;
    }

    const const_iterator& operator--() {
      this->p_ = this->p_->getPrev();
      return *this;
    }

    const TLinkListNode* operator->() const { return this->p_; }
    
  private:
    const TLinkListNode* p_;
  };

  bool Confirm() const;
  bool Confirm_iterator(const_iterator it) const;
  iterator Erase(TLinkListNode* node);
  iterator Find(const TLinkListNode* node);
  iterator Insert(iterator it, TLinkListNode* node);
  void Remove(TLinkListNode* node);
  template <typename Predicate> void Remove_if(Predicate predicate, TNodeLinkList& tList) {
    iterator it = this->begin();

    while(!Iterator_isEnd_(it)) {
      if (predicate(*it)) {
        iterator itPrev = it;
        ++it;
        tList.splice(tList.end(), *this, itPrev);
      }
      else {
        ++it;
      }
    }
  }

  u32 size() const { return this->size_; }
  bool empty() const { return this->size() == 0; }
  void clear() { this->erase(this->begin(), this->end()); }
  iterator erase(iterator itStart, iterator itEnd);
  iterator erase(iterator it);
  template <typename Predicate> void remove_if(Predicate predicate) {
    TNodeLinkList list;

    this->Remove_if(predicate, list);
  }
  void splice(iterator it, TNodeLinkList& rSrc, iterator itBegin, iterator itEnd);
  void splice(iterator it, TNodeLinkList& rSrc);
  void splice(iterator it, TNodeLinkList& rSrc, iterator otherIt);
  iterator pop_back() { return this->erase(--this->end()); }
  iterator pop_font() { return this->erase(++this->begin()); }
  
  iterator begin() { return this->oNode_.getNext(); }
  const_iterator begin() const { return this->oNode_.getNext(); }
  
  iterator end() { return &this->oNode_; }
  const_iterator end() const { return &this->oNode_; }

private:
  void Initialize_() {
    this->size_ = 0;
    this->oNode_.pNext_ = &this->oNode_;
    this->oNode_.pPrev_ = &this->oNode_;
  }

  bool Iterator_isEnd_(const_iterator it) const { return it.p_ == &this->oNode_; }

  u32 size_;
  TLinkListNode oNode_;
};

#pragma push
#pragma sym off /* required to prevent messing up other TU layouts */

template <typename T, int O>
class TLinkList : public TNodeLinkList {
public:
  class iterator {
  public:
    friend class TLinkList;
    friend class TLinkList<T, O>::const_iterator;

    iterator(TNodeLinkList::iterator it) : mIt(it) {  }

    friend bool operator==(iterator lhs, iterator rhs) { return (lhs.mIt == rhs.mIt); }
    friend bool operator!=(iterator lhs, iterator rhs) { return !(lhs == rhs); }
    iterator& operator++() {
      ++mIt;
      return *this;
    }
    iterator& operator--() {
      --mIt;
      return *this;
    }

    T* operator->() const { return TLinkList::Element_toValue(mIt.operator->()); }
    T& operator*() const {
      T* p = this->operator->();
      JUT_ASSERT(p!=0);
      return *p;
    }

  private:
    TNodeLinkList::iterator mIt;
  };

  class const_iterator {
  public:
    const_iterator(TNodeLinkList::const_iterator it) : mIt(it) {  }
    const_iterator(iterator it) : mIt(it.mIt) {}

    friend bool operator==(const_iterator lhs, const_iterator rhs) { return (lhs.mIt == rhs.mIt); }
    friend bool operator!=(const_iterator lhs, const_iterator rhs) { return !(lhs == rhs); }
    
    const_iterator& operator++() {
      ++mIt;
      return *this;
    }
    const_iterator& operator--() {
      --mIt;
      return *this;
    }

    const T* operator->() const { return TLinkList::Element_toValue(mIt.operator->()); }
    const T& operator*() const {
      const T* p = this->operator->();
      JUT_ASSERT(p!=0);
      return *p;
    }

  private:
    TNodeLinkList::const_iterator mIt;
  };

  iterator begin() { return TNodeLinkList::begin(); }
  const_iterator begin() const { return const_cast<TLinkList*>(this)->begin(); }

  iterator end() { return TNodeLinkList::end(); }
  const_iterator end() const { return const_cast<TLinkList*>(this)->end(); }

  iterator Find(const T* p) { return TNodeLinkList::Find(TLinkList::Element_toNode(p)); }
  iterator Erase(T* p) { return TNodeLinkList::Erase(Element_toNode(p)); }
  iterator Insert(iterator it, T *p) { return TNodeLinkList::Insert(it.mIt, TLinkList::Element_toNode(p)); }
  void Remove(T* p) { TNodeLinkList::Remove(TLinkList::Element_toNode(p)); }
  void Push_front(T* p) { Insert(begin(), p); }
  void Push_back(T* p) { Insert(end(), p); }

  T& front() {
    JUT_ASSERT(!empty());
    return *begin();
  }

  T& back() {
    JUT_ASSERT(!empty());
    return *--end();
  }

  static TLinkListNode* Element_toNode(T* p) {
    JUT_ASSERT(p!=0);
    return (TLinkListNode*)((char*)p - O);
  }

  static const TLinkListNode* Element_toNode(const T* p) {
    JUT_ASSERT(p!=0);
    return (const TLinkListNode*)((const char*)p - O);
  }

  static T* Element_toValue(TLinkListNode* p) {
    JUT_ASSERT(p!=0);
    return (T*)((char*)p + O);
  }

  static const T* Element_toValue(const TLinkListNode* p) {
    JUT_ASSERT(p!=0);
    return (const T*)((const char*)p + O);
  }
};

#pragma pop

}
#endif

#endif
