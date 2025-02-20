package queue

import (
    "testing"
)


func BenchmarkQueuePush100(b *testing.B) {
    for i := 0; i < b.N; i++ {
        queue := NewQueue()
        for j := 0; j < 100; j++ {
            queue.Push(j)
        }
    }
}

func BenchmarkQueuePush1000(b *testing.B) {
    for i := 0; i < b.N; i++ {
        queue := NewQueue()
        for j := 0; j < 1000; j++ {
            queue.Push(j)
        }
    }
}

func BenchmarkQueuePush10000(b *testing.B) {
    for i := 0; i < b.N; i++ {
        queue := NewQueue()
        for j := 0; j < 10000; j++ {
            queue.Push(j)
        }
    }
}
