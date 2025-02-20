package serialize

import (
	"bytes"
	"encoding/json"
	"encoding/gob"
	"Go/queue" // Замените на фактический путь к вашему пакету
)

// SerializeJSON сериализует очередь в JSON
func SerializeJSON(q *queue.Queue) (string, error) {
	if q.Size() == 0 {
		return "[]", nil // Если очередь пустая, возвращаем пустой массив
	}

	var values []interface{}
	current := q.Pop() // Начинаем с головы очереди
	for current != nil {
		values = append(values, current)
		current = q.Pop() // Извлекаем элемент и переходим к следующему
	}

	jsonData, err := json.Marshal(values)
	if err != nil {
		return "", err
	}
	return string(jsonData), nil
}

// DeserializeJSON десериализует JSON в очередь
func DeserializeJSON(q *queue.Queue, data string) error {
	var values []interface{}
	if err := json.Unmarshal([]byte(data), &values); err != nil {
		return err
	}

	for _, value := range values {
		q.Push(value)
	}
	return nil
}


// SerializeBinary сериализует очередь в бинарный формат
func SerializeBinary(q *queue.Queue) ([]byte, error) {
	var buf bytes.Buffer
	enc := gob.NewEncoder(&buf)
	err := enc.Encode(q)
	if err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

// DeserializeBinary десериализует очередь из бинарного формата
func DeserializeBinary(q *queue.Queue, data []byte) error {
	buf := bytes.NewBuffer(data)
	dec := gob.NewDecoder(buf)
	err := dec.Decode(q)
	if err != nil {
		return err
	}
	return nil
}