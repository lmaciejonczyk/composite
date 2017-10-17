#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Component {
 public:
  virtual ~Component() = default;
  virtual void traverse() const = 0;
};

class Leaf : public Component {
 public:
  ~Leaf() override = default;

  Leaf(int value) : m_value(value) {}

  void traverse() const override {
    cout << m_value << ' ';
  }

 private:
  int m_value;
};

class Composite : public Component {
 public:
  ~Composite() override = default;
  void traverse() const override {
    for (auto& el : m_elements) {
      el->traverse();
    }
  }

  void addElement(unique_ptr<Component> element) {
    m_elements.push_back(move(element));
  }

 private:
  vector<unique_ptr<Component>> m_elements;
};

int main() {
  Composite mainConteiner;

  for (int i = 0; i < 3; ++i) {
    mainConteiner.addElement(make_unique<Leaf>(i));
  }

  auto p = make_unique<Composite>();
  for (int j = 0; j < 3; ++j) {
    p->addElement(make_unique<Leaf>(3 + j));
  }

  mainConteiner.addElement(move(p));
  mainConteiner.traverse();
  cout << endl;
}
