#ifndef LIST_H_
#define LIST_H_



struct Node {

    Node *_prev, *_next;
    void *_data;

    Node():_prev(this), _next(this), _data(0){}

};

struct List {

    Node _head;
    unsigned int _count;
    Node *_iter;

    virtual Node * setPrev(Node *head){
        return head->_prev;
    }

    virtual Node * setNext(Node *head){
        return head;
    }

    List():_count(0){}

    void* Add(void *data){

        Node *newbie = new Node;
        newbie->_data = data;

        Node *prev, *next;
        prev = setPrev(&_head);
        next = setNext(&_head);

        _count++;
        return _add(prev, newbie, next);
        
    }

    bool IsEmpty(){
        return _count == 0 ? true : false;
    }

    void *First(){
        return _head._next->_data;
    }

    void *Last(){
        return _head._prev->_data;
    }


    void Init(){
        _head._prev = &_head;
        _head._next = &_head;
    }

    bool HasNext(){ return &_head == _iter ? false : true; }
    Node *Next() {return _iter = _iter->_next; }
    Node *Iterator(){ return _iter = _head._next; }

    
    void* _add(Node *prev, Node *newbie, Node *next){
        newbie->_next = next;
        newbie->_prev = prev;

        next->_prev = newbie;
        prev->_next = newbie;

        return newbie->_data;

    }
};



#endif