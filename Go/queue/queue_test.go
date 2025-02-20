package queue

import (
    "testing"
    "github.com/stretchr/testify/assert"
)

func TestQueue(t *testing.T) {
    ////////////////////////////////////////////////////////Только testing
    queue := NewQueue()

    // Проверяем, что очередь пуста при создании
    if(queue.Size()!=0){
        t.Errorf("Начальный размер не 0 ")
    }

    // Добавляем элементы в очередь
    queue.Push(1)
    queue.Push(2)
    queue.Push(3)
    if(queue.PeekFront()!=1 || queue.PeekBack()!=3 || queue.Size()!=3){
        t.Errorf("ошибка вставки ")
    }

    // Извлекаем элементы из очереди и проверяем их порядок
    for i := 1; i < 4; i++ {
        item := queue.Pop()
        if(item != i){
            t.Errorf("Ошибка удаления ")
        }
    }
    ////////////////////////////////////////////////////////Testify
    assert.Equal(t,queue.Size(),0,"Размер очереди не равен 0")

    queue.Push(1)
    assert.True(t,queue.PeekBack()==1,"Ошибка вставки в очередь")
    queue.Push(2)
    assert.True(t,queue.PeekBack()==2,"Ошибка вставки в очередь")
    queue.Push(3)
    assert.True(t,queue.PeekBack()==3,"Ошибка вставки в очередь")

    assert.Equal(t,queue.Pop(),1,"Неправильное удаление")
    assert.Equal(t,queue.Pop(),2,"Неправильное удаление")
    assert.Equal(t,queue.Pop(),3,"Неправильное удаление")

    assert.True(t,queue.Pop() == nil,"Неправильное удаление")
    assert.True(t,queue.PeekFront() == nil,"Неправильное удаление")
    assert.True(t,queue.PeekBack() == nil,"Неправильное удаление")



}
