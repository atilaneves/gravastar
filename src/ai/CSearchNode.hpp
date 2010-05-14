#ifndef CSEARCHNODE_H
#define CSEARCHNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <memory>


template<typename T>
class CSearchNode {


public:

  CSearchNode(T *state);
  CSearchNode(T *state, CSearchNode<T> *parent, int op);

  static void SetGoal(T *goal) { sGoal=goal; }

  CSearchNode<T> *CreateNode(int op);
  CSearchNode<T> *GetParent() const;

  float  CalcCost(int op);
  float  CalcHeuristic() const        { return mState->Estimate(sGoal); }
  float  GetHeuristic() const         { return mHeuristic; }
  int    GetIndex() const             { return mState->GetIndex(); }
  int    GetNbOperators() const       { return mState->GetNbOperators(); }
  int    GetFirstOperator() const     { return mFirstOperator; }
  float  GetTotal() const             { return mTotal; }
  bool   Equals(CSearchNode<T> *node) const {
    return mState->Equals(node->mState); }
  bool   IsAtGoal() const             { return mState->IsAtGoal(sGoal); }


private:

  static T *sGoal;
  int    mOperator; //what created us (indexed)
  int    mFirstOperator; //original operator that starts solution
  float  mCost;
  float  mHeuristic;
  float  mTotal;
  std::auto_ptr<T> mState;
  CSearchNode<T> *mParent;

};


template<typename T> T * CSearchNode<T>::sGoal = 0;


#include <stdio.h>


template<typename T>
CSearchNode<T>::CSearchNode(T *state):
  mOperator(-1), mFirstOperator(-1), mCost(0), mState(state), mParent(0) {
  //this is the initial node
  if(!sGoal) {
    fprintf(stderr,"\n*** Error: Call CSearchNode::SetGoal 1st ***\n\n");
    exit(1);
  }

  mHeuristic = CalcHeuristic();
  mTotal = mCost + mHeuristic;
}

template<typename T>
CSearchNode<T>::CSearchNode(T *state, CSearchNode<T> *parent, int op):
  mOperator(op), mState(state), mParent(parent) {

  mCost = CalcCost(op); //how much it cost to get here from the initial node
  mHeuristic = CalcHeuristic(); //estimate of distance to goal node
  mTotal = mCost + mHeuristic;

  int parent1stOp = mParent->GetFirstOperator();
  if(parent1stOp == -1) //parent is node0
    mFirstOperator = op; //this is the 1st operator
  else //just copy the parent's operator, then
    mFirstOperator = mParent->GetFirstOperator();

}


template<typename T>
float CSearchNode<T>::CalcCost(int op) { 
  return mState->Cost(op) + mParent->mCost;
}


template<typename T>
CSearchNode<T> * CSearchNode<T>::CreateNode(int op) { 
  T *newState = mState->CreateState(op);
  return newState ? new CSearchNode<T>(newState,this,op) : 0;
}


template<typename T>
CSearchNode<T> * CSearchNode<T>::GetParent() const { 
  return mParent; 
}


#endif
