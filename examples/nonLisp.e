import std.io;

fn main() {
  println("Hello, world!");
}

fn add(a, b: f64) -> f64 {
  return a + b;
}

struct Vector<T> {
  arr: []T,
  size: usize
}

impl Vector<T> {
  fn Vector<T>() -> Self {
    return Self { arr: [], size: 0 };
  }

  fn append(*self) -> Result(Ok, Err) {

  }
}

// Linked list
struct Node<T> {
  data: T,
  next: *Node<T>
}

