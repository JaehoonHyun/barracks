#ifndef LIST_H_
#define LIST_H_



struct Node {

    Node *_prev, *_next;
    void *_data;

    Node():_prev(this), _next(this), _data(0){}

};

struct List {

    Node head;
    unsigned int count;

    List():count(0){}

    void add(void *data){

        Node *newbie = new Node;
        newbie->_data = data;

        Node *prev, *next;
        prev = head._prev;
        next = &head;

        _add(prev, newbie, next);

        count++;
    }

    bool isEmpty(){
        return count == 0 ? true : false;
    }

    void _add(Node *prev, Node *newbie, Node *next){
        newbie->_next = next;
        newbie->_prev = prev;

        next->_prev = newbie;
        prev->_next = newbie;

    }

    void init(){
        head._prev = &head;
        head._next = &head;
    }

    Node *iter;

    bool hasNext(){ return &head == iter ? false : true; }
    Node *next() {return iter = iter->_next; }
    Node *iterator(){ return iter = head._next; }

    
};



#endif