#ifndef CSEARCHQUEUE_H
#define CSEARCHQUEUE_H


#include "CSearchNode.hpp"
#include <vector>
#include <algorithm>



template <typename T>
class CSearchQueue {

public:

  typedef std::vector<CSearchNode<T>*> searchQueue_t;
  
  CSearchQueue(T *startState);
  ~CSearchQueue();
  
  void            ExpandAndAdd(CSearchNode<T> *node);
  CSearchNode<T> *GetNextNode();
  bool            IsEmpty() const { return mNbOpenNodes == 0; }
  

private:
  
  searchQueue_t mOpenArray;   //not all are valid
  searchQueue_t mClosedArray; //not all are valid
  searchQueue_t mOpenNodes;
  searchQueue_t mClosedNodes;
  int mNbOpenNodes;
  
};


template <typename T>
CSearchQueue<T>::CSearchQueue(T *startState):
  mNbOpenNodes(0) {

  mOpenArray.resize(T::GetMaxNbStates());   //must have all of them init'ed
  mClosedArray.resize(T::GetMaxNbStates()); //same

  for(int i = 0; i < T::GetMaxNbStates(); i++)
    mOpenArray[i] = mClosedArray[i] = 0; //just to make sure

  CSearchNode<T> *startNode = new CSearchNode<T>(startState);
  mOpenNodes.reserve(200);
  mOpenNodes.push_back(startNode);
  mOpenArray[startNode->GetIndex()] = startNode;
  mNbOpenNodes++;

}


template <typename T>
CSearchQueue<T>::~CSearchQueue() {

  for(unsigned int i = 0; i < mOpenNodes.size(); i++)
    delete mOpenNodes[i];

  for(unsigned int i = 0; i < mClosedNodes.size(); i++) 
    delete mClosedNodes[i];
}


template <typename T> //expand node and add its child nodes to us
void CSearchQueue<T>::ExpandAndAdd(CSearchNode<T> *node) {

  for(int op=0; op<node->GetNbOperators(); op++) {
    //don't add it if we already have one like it

    CSearchNode<T> *newNode = node->CreateNode(op);

    if(newNode) { //valid ptr

      bool inOpen   = false;
      bool inClosed = false;

      if(mClosedArray[newNode->GetIndex()]) //already have it
	inClosed = true;

      if(mOpenArray[newNode->GetIndex()]) { //already have it
	  
	inOpen = true; //already have it

	if(newNode->GetTotal() < 
	   mOpenArray[newNode->GetIndex()]->GetTotal()) { 
	  //this one's better, replace it
	  CSearchNode<T> *oldNode = mOpenArray[newNode->GetIndex()];
	  std::replace(mOpenNodes.begin(), mOpenNodes.end(), oldNode, newNode);
	  mOpenArray[newNode->GetIndex()] = newNode; //replace it w new one
	  newNode = oldNode; //old one gets deleted below
	}
      }

      if(!inOpen && !inClosed) { //truly a new node, add it
	mOpenArray[newNode->GetIndex()] = newNode;
	mOpenNodes.push_back(newNode);
	mNbOpenNodes++;
      }
      else
	delete newNode; //we've allocated memory for it, so..
    }
  }
}


template <typename T> //true if n1 is smaller 
bool smallerTotal(CSearchNode<T> *n1, CSearchNode<T> *n2) {
  if(int(n1->GetTotal()) != int(n2->GetTotal()))
    return n1->GetTotal() < n2->GetTotal();
  else
    return n1->GetHeuristic() < n2->GetHeuristic(); //tie breaker
}


template <typename T>
CSearchNode<T> * CSearchQueue<T>::GetNextNode() {

  typename searchQueue_t::iterator where;
  where=std::min_element(mOpenNodes.begin(),mOpenNodes.end(),smallerTotal<T>);
  CSearchNode<T> *node = *where;
  mOpenNodes.erase(where);
  mClosedNodes.push_back(node);
  mOpenArray[node->GetIndex()] = 0; //take it away from the array
  mClosedArray[node->GetIndex()] = node; //add it to the closed array
  mNbOpenNodes--; //one less to deal with
  return node;
}


#endif
