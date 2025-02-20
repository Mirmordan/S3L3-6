package queue

import (
	
)

// Node представляет элемент очереди
type Node struct {
	Value interface{}
	Next  *Node
}

type Queue struct {
	Head *Node // Указатель на первый и последний элементы, размер
	Tail *Node 
	SizeQ  int   
}

func NewQueue() *Queue {   //Конструктор
	return &Queue{}
}


func (q *Queue) Push(value interface{}) {      //Добавление элемента в конец
	newNode := &Node{Value: value}

	if q.Tail != nil {
		q.Tail.Next = newNode 
	}
	q.Tail = newNode

	if q.Head == nil {
		q.Head = newNode 
	}

	q.SizeQ++ 
}


func (q *Queue) Pop() interface{} {    //Удаление и взятие элемента
	if q.Head == nil {
		return nil
	}

	value := q.Head.Value
	q.Head = q.Head.Next 

	if q.Head == nil {
		q.Tail = nil 
	}

	q.SizeQ-- 
	return value
}

func (q *Queue) PeekFront() interface{} {             //Взятие с головы
    if q.Head==nil{
        return nil
    }
    return q.Head.Value
}

func (q *Queue) PeekBack() interface{} {             //Взятие с конца
    if q.Tail==nil{
        return nil
    }
    return q.Tail.Value
}

func (q *Queue) Size() int {             //Размер
	return q.SizeQ
}