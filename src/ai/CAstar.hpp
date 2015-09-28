#ifndef CASTAR_H
#define CASTAR_H


#include "CSearchQueue.hpp"
#include <memory>

template<typename T>
class CAstar {

public:

  CAstar(T *start, T *goal);

  int Search(); //Return operator

private:

  std::unique_ptr<T> mGoalState;
  std::unique_ptr<CSearchQueue<T> > mQueue;

};


template<typename T>
CAstar<T>::CAstar(T *start,T *goal):
  mGoalState(goal) {

  CSearchNode<T>::SetGoal(goal);
  mQueue.reset(new CSearchQueue<T>(start)); //must come after SetGoal
}


template<typename T>
int CAstar<T>::Search() {

  while(!mQueue->IsEmpty()) {

    CSearchNode<T> *node = mQueue->GetNextNode();

    if(node->IsAtGoal()) {
      CSearchNode<T> *parent = node;
      do parent = parent->GetParent();
      while(parent);
      return node->GetFirstOperator();
    }
    else
      mQueue->ExpandAndAdd(node);
  }

  return -1; //fail
}


#endif
