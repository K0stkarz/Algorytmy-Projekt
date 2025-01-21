#include <random>
#include <limits>
#include <memory>
#include <iostream>
#include <ctime>

template <typename T>
struct SkipNode {
    T value; // Value stored in the node
    std::vector<std::shared_ptr<SkipNode<T>>> forward; // Pointers to the next nodes at each level

    // Constructor to initialize a node with a value and level
    SkipNode(const T& val, int level) : value(val), forward(level) {}

    // Default constructor initializes an empty node with one level
    SkipNode() : value(T()), forward(1) {}
};

template <typename T>
class SkipList {
    std::shared_ptr<SkipNode<T>> head; // Pointer to the head node
    int maxLevel; // Maximum level allowed in the skip list
    float probability; // Probability factor for determining levels of nodes
    int level; // Current maximum level of the skip list
    std::random_device rd; // Random device for seeding
    std::mt19937 gen; // Mersenne Twister random number generator
    std::uniform_real_distribution<> dis; // Distribution for generating random numbers

    // Function to generate a random level for a new node
    int randomLevel();

public:
    SkipList() : SkipList(5, 0.5) {} // Default constructor initializes with a max level of 5 and probability of 0.5
    SkipList(int maxLvl, float p); // Parameterized constructor
    SkipList(const SkipList& other); // Copy constructor    
    SkipList(SkipList&& other) noexcept; // Move constructor
    SkipList& operator=(const SkipList& other); // Copy assignment operator
    SkipList& operator=(SkipList&& other) noexcept; // Move assignment operator
    bool empty() const { return level == 1 && !head->forward[0]; } // Checks if the skip list is empty
    void insert(const T& value); // Inserts a value into the skip list
    void remove(const T& value); // Removes a value from the skip list
    void clear(); // Clears the entire skip list
    void display() const; // Displays the skip list by levels
    // Searches for a value in the skip list and returns the corresponding node
    std::shared_ptr<SkipNode<T>> search(const T& value) const; 
};

// Implementation of parameterized constructor
template <typename T>
SkipList<T>::SkipList(int maxLvl, float p) : maxLevel(maxLvl), probability(p), level(1), gen(rd()), dis(0.0, 1.0) {
    T minVal = std::numeric_limits<T>::min(); // Minimum possible value of type T
    head = std::make_shared<SkipNode<T>>(minVal, maxLevel); // Initialize the head node
}

// Implementation of copy constructor
template <typename T>
SkipList<T>::SkipList(const SkipList& other) 
    : maxLevel(other.maxLevel), probability(other.probability), level(other.level), gen(rd()), dis(0.0, 1.0) {
    head = std::make_shared<SkipNode<T>>(std::numeric_limits<T>::min(), maxLevel);
    auto current = other.head->forward[0];
    while (current) {
        insert(current->value); // Copy all values from the other skip list
        current = current->forward[0];
    }
}

// Implementation of move constructor
template <typename T>
SkipList<T>::SkipList(SkipList&& other) noexcept 
    : head(std::move(other.head)), maxLevel(other.maxLevel), probability(other.probability), level(other.level), gen(rd()), dis(0.0, 1.0) {
    other.clear(); // Clear the moved-from skip list
}

// Implementation of copy assignment operator
template <typename T>
SkipList<T>& SkipList<T>::operator=(const SkipList& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    this->clear(); // Clear the current skip list
    maxLevel = other.maxLevel;
    probability = other.probability;
    level = other.level;
    head = std::make_shared<SkipNode<T>>(std::numeric_limits<T>::min(), maxLevel);

    auto current = other.head->forward[0];
    while (current) {
        insert(current->value); // Copy values from the other skip list
        current = current->forward[0];
    }

    return *this;
}

// Implementation of move assignment operator
template <typename T>
SkipList<T>& SkipList<T>::operator=(SkipList&& other) noexcept {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    this->clear(); // Clear the current skip list
    head = std::move(other.head);
    maxLevel = other.maxLevel;
    probability = other.probability;
    level = other.level;

    other.clear(); // Clear the moved-from skip list

    return *this;
}

// Generates a random level for a new node based on the probability factor
template <typename T>
int SkipList<T>::randomLevel() {
    int lvl = 1; 

    // Increase the level while the random number is below the probability
    while (dis(gen) < probability && lvl < maxLevel) {
        lvl++; 
    }

    return lvl; 
}

// Inserts a new value into the skip list
template <typename T>
void SkipList<T>::insert(const T& value) {
    std::vector<std::shared_ptr<SkipNode<T>>> update(maxLevel); 
    auto current = head; 

    // Traverse the list to find the position to insert the new value
    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current; 
    }

    int newLevel = randomLevel(); // Determine the level for the new node
    if (newLevel > level) {
        for (int i = level; i < newLevel; i++) {
            update[i] = head; 
        }
        level = newLevel; // Update the skip list's current maximum level
    }

    auto newNode = std::make_shared<SkipNode<T>>(value, newLevel); 
    for (int i = 0; i < newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i]; 
        update[i]->forward[i] = newNode; 
    }
}

// Searches for a value in the skip list and returns the node if found
template <typename T>
std::shared_ptr<SkipNode<T>> SkipList<T>::search(const T& value) const {
    auto current = head; 

    // Traverse the skip list levels from top to bottom
    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i]; 
        }
    }

    current = current->forward[0]; 
    if (current && current->value == value) {
        return current; 
    } else {
        return nullptr;
    }
}

// Removes a value from the skip list
template <typename T>
void SkipList<T>::remove(const T& value) {
    std::vector<std::shared_ptr<SkipNode<T>>> update(maxLevel); 
    auto current = head; 

    // Traverse the list to locate the node to be removed
    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i]; 
        }
        update[i] = current; 
    }

    current = current->forward[0]; // Move to the target node at the base level
    if (current && current->value == value) {
        // Update links to bypass the target node
        for (int i = 0; i < level; i++) {
            if (update[i]->forward[i] != current) {
                break; 
            }
            update[i]->forward[i] = current->forward[i]; 
        }

        // Adjust the level of the skip list if the highest levels become empty
        while (level > 1 && !head->forward[level - 1]) {
            level--; 
        }
    }
}

// Displays all the levels of the skip list
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

// Clears the skip list and resets it to the initial state
template <typename T>
void SkipList<T>::clear() {
    head = std::make_shared<SkipNode<T>>(std::numeric_limits<T>::min(), maxLevel);
    level = 1; // Reset level to 1
}