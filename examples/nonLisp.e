import std::{io, ops};

fn main() {
  println("Hello, world!");
}

fn add(a, b: f64) -> f64 {
  return a + b;
}

struct Vector<T> {
  arr: []T,
  size: usize,
  pos: usize
}

impl Vector<T> {
  fn new<T>() -> Self {
    return Self { arr: T[], size: 0 };
  }

  fn append(self, item: T) {
    if self.pos >= self.usize {
      self.size *= 2;
      var tmp [size]T;
      memcpy(tmp, self.arr, size / 2);
    }
    self.arr[self.pos++] = item;
  }
}

struct String {
  str: []char
}

impl Add<String> for String {
  fn add(self, rhs: String) -> String {
    
  }
}

// Linked list
struct Node<T> {
  data: T,
  next: *Node<T>
}

