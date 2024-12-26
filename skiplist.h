#include <random>
#include <limits>
#include <memory>
#include <iostream>
#include <ctime>

template <typename T>
struct SkipNode {
    T value;
    std::vector<std::shared_ptr<SkipNode<T>>> forward;

    SkipNode(const T& val, int level) : value(val), forward(level) {}
    SkipNode() : value(T()), forward(1) {}
};

template <typename T>
class SkipList {
    std::shared_ptr<SkipNode<T>> head;
    int maxLevel;
    float probability;
    int level;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    int randomLevel();
    
public:
    SkipList() : SkipList(5, 0.7) {}
    SkipList(int maxLvl, float p);
    void insert(const T& value);
    void remove(const T& value);
    void display() const;
    bool search(const T& value) const;
};

template <typename T>
SkipList<T>::SkipList(int maxLvl, float p) : maxLevel(maxLvl), probability(p), level(1), gen(rd()), dis(0.0, 1.0) {
    T minVal = std::numeric_limits<T>::min();
    head = std::make_shared<SkipNode<T>>(minVal, maxLevel);
}

template <typename T>
int SkipList<T>::randomLevel() {
    int lvl = 1;

    while (dis(gen) < probability && lvl < maxLevel) {
        lvl++;
    }

    return lvl;
}

template <typename T>
void SkipList<T>::insert(const T& value) {
    std::vector<std::shared_ptr<SkipNode<T>>> update(maxLevel);
    auto current = head;

    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    int newLevel = randomLevel();
    if (newLevel > level) {
        for (int i = level; i < newLevel; i++) {
            update[i] = head;
        }
        level = newLevel;
    }

    auto newNode = std::make_shared<SkipNode<T>>(value, newLevel);
    for (int i = 0; i < newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

template <typename T>
bool SkipList<T>::search(const T& value) const {
    auto current = head;

    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    return current && current->value == value;
}

template <typename T>
void SkipList<T>::remove(const T& value) {
    std::vector<std::shared_ptr<SkipNode<T>>> update(maxLevel);
    auto current = head;

    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current && current->value == value) {
        for (int i = 0; i < level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        while (level > 1 && !head->forward[level - 1]) {
            level--;
        }
    }
}

template <typename T>
void SkipList<T>::display() const {
    for (int i = level - 1; i >= 0; i--) {
        auto current = head->forward[i];
        std::cout << "Level " << i << ": ";
        while (current) {
            std::cout << current->value << " -> ";
            current = current->forward[i];
        }
        std::cout << "nullptr" << std::endl;
    }
    std::cout << std::endl;
}