#include "Test.h"
#include <iostream>
#include "vector"
using namespace std;
class Node
{
public:
  char character;
  int frequency;
  Node* left;
  Node* right;

  Node()
  {
    this->character = (char)NULL;
    this->frequency = 0;
    this->left = NULL;
    this->right = NULL;
  }

  Node(char character, int frequency)
  {
    this->character = character;
    this->frequency = frequency;
    this->left = NULL;
    this->right = NULL;
  }
};

bool odd(int n){
    if ( n % 2 == 0)
        return false;
    else
        return true;

}

void printtree(vector<int> min_heap){
    for (std::vector<int>::const_iterator i = min_heap.begin(); i != min_heap.end(); ++i)
    std::cout << *i << ' ';
}

void insertOnHeap(vector<Node*> *n, Node* character)
{
    if(n->size() == 0)
    {
        n->push_back(character);
        return;
    }
    n->push_back(character);
    int i = n->size()-1;
    int root;
    if(odd(i))
    {
        root = (i-2)/2;
    }else
    {
        root = (i-1)/2;
    }
    while(root >=0 && (*n)[root]->frequency>=(*n)[i]->frequency)
    {
        Node *Temp = (*n)[root];
        (*n)[root] = (*n)[i];
        (*n)[i]= Temp;
        i = root;
        if(i % 2 == 0)
        {
            root = (i-2)/2;
        }else if(!i % 2 == 0)
        {
            root = (i-1)/2;
        }
    }

}

void backtracking(Node* current_node, string code, map<char,string>* codes)
{
  if(!current_node)
    return;

  if(current_node->character != (char)NULL)
  {
    (*codes)[current_node->character] = code;
  }

  backtracking(current_node->left, code+"0", codes);
  backtracking(current_node->right, code+"1", codes);
}

Node* selectNode(list<Node*>* q1, list<Node*>* q2)
{
  Node* selected_node;
	if(q1->empty())
	{
		selected_node = q2->front();
		q2->pop_front();
	}else if(q2->empty())
	{
		selected_node = q1->front();
		q1->pop_front();
	}else
	{
		if(q1->front()->frequency < q2->front()->frequency)
		{
		  selected_node = q1->front();
		  q1->pop_front();
		}else
		{
		  selected_node = q2->front();
		  q2->pop_front();
		}
	}
  return selected_node;
}

map<char,string> getHuffman2(vector<char> characters, vector<int> frequencies)
{
    list<Node*> q1;
    list<Node*> q2;

    for(int i=0; i< (int)characters.size();i++)
    {
      q1.push_back(new Node(characters[i],frequencies[i]));
    }

    while(q1.size()>1 || q2.size()>1)
    {
      Node* n1 = selectNode(&q1, &q2);
      Node* n2 = selectNode(&q1, &q2);
      Node* internal_node = new Node((char)NULL,n1->frequency + n2->frequency);
      internal_node->left = n1;
      internal_node->right = n2;
      q2.push_back(internal_node);
    }

    Node* root = new Node((char)NULL,q1.front()->frequency + q2.front()->frequency);
    root->left = q1.front();
    root->right = q2.front();

    map<char,string> answer;

    backtracking(root, "", &answer);

    return answer;
}

Node * order(vector<Node*> *heap)
{
    Node * answer = (*heap)[0];
    (*heap)[0] = (*heap)[heap->size()-1];
    heap->pop_back();

    int current = 0;
    while(current < heap->size())
    {
        int LeftNode = (current *2)+1;
        int RightNode = (current *2)+2;

        if(LeftNode < heap->size() && (*heap)[current]->frequency > (*heap)[LeftNode]->frequency && (*heap)[LeftNode]->frequency <= (*heap)[RightNode]->frequency)
        {
            Node* Temp = (*heap)[current];
            (*heap)[current] = (*heap)[LeftNode];
            (*heap)[LeftNode] = Temp;
            current = LeftNode;
        }else if(RightNode < heap->size() &&  (*heap)[current]->frequency > (*heap)[RightNode]->frequency && (*heap)[RightNode]->frequency <= (*heap)[LeftNode]->frequency)
        {
            Node* Temp = (*heap)[current];
            (*heap)[current] = (*heap)[RightNode];
            (*heap)[RightNode] = Temp;
            current = RightNode;
        }else
        {
            return answer;
        }
  }

  return answer;
}

map<char,string> getHuffman(vector<char> characters, vector<int> frequencies)
{
    vector<Node*> min_heap;
    for(int i =0; i < characters.size(); i++)
    {
        insertOnHeap(&min_heap,new Node(characters[i],frequencies[i]));
    }

    while(min_heap.size()>1){
    Node *left = order(&min_heap);
    Node *right = order(&min_heap);
    Node * root = new Node((char)NULL,left->frequency + right->frequency);
    root->left = left;
    root->right = right;
    insertOnHeap(&min_heap,root);
    }

    map<char,string> answer;
    backtracking(min_heap[0], "", &answer);
    return answer;
}

int main ()
{
    test();
    return 0;
}
