package main

import (
	"fmt"
	"os"
	"Go/queue"
	"Go/serialize"
)


func main() {
	q := queue.NewQueue()
	q.Push(1)
	q.Push("two")
	q.Push(3.0)

	// Бинарная сериализация
	binData,err := serialize.SerializeBinary(q)
	fmt.Println("Бинарная очередь (формат GOB)", binData)
	os.WriteFile("data.bin", binData, 0644)

	// Бинарная десериализация
	newQ := queue.NewQueue()
	serialize.DeserializeBinary(newQ,binData)
	

	fmt.Println("Очередь после бинарной десериализации,",newQ.Size())
	for newQ.Size() > 0 {
		fmt.Println(newQ.Pop())
	}

	// Сериализация в JSON
	jsonData, err := serialize.SerializeJSON(q)
	if err != nil {
		panic(err)
	}
	os.WriteFile("data.json", []byte(jsonData), 0644)
	fmt.Println("JSON очередь q:", jsonData)

	// Десериализация из JSON
	newQueue := queue.NewQueue()
	err = serialize.DeserializeJSON(newQueue, jsonData)
	if err != nil {
		panic(err)
	}
	fmt.Println("Очередь после json десериализации,", newQueue.Size())
	for newQueue.Size() > 0 {
		fmt.Println(newQueue.Pop())
	}
}
