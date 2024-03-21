#pragma once
#include <iostream>

/* 그래프 용어
 * vertex: node
 * edge: vertex 간의 연결
 *
 * 트리 (tree)
 * 그래프의 종류 중에 하나
 * circuit(순회)이 불가능한 그래프 구조
 * 계층 관계를 표현하는데에 유리함
 *
 * 이진 트리
 * 자식의 개수가 2개 이하인 트리 (항상 2개의 자식을 가지고 있는 것은 아님)
 *
 *                  *                   Level 0 -> 루트 노드 (*): 부모가 존재하지 않는 노드 (= 최상위 노드)
 *             /          \
 *          o               o           Level 1
 *        /   \          /     \
 *      x       o       x       x       Level 2
 *               |
 *                x                     Level 3 (높이) -> 리프 노드 (x): 자식이 존재하지 않는 노드
 *
 * 완전 이진 트리
 * 자식을 항상 최대(= 2개)로 채워나가는 이진 트리
 *
 *                  0
 *             /          \
 *          1               2
 *        /   \          /     \
 *      3       4       5       6
 *    /   \   /  |     / \     / \
 *  7      8 9    a   b   c   d   e
 *
 * 일반적으로 배열로 구현 (연속적인 메모리 구조) -> { 0 1 2 3 4 5 6 7 8 9 a b c d e }
 * 자식의 인덱스 계산하기: 2k + 1
 * 부모의 인덱스 계산하기: (int) ((k - 1) / 2)
 *
 * 이진 탐색 트리 (Binary Search Tree)
 * 이진 트리 중에 탐색을 위해 고안된 자료 구조 -> 특정 값이 어디에 있는지 빠르게 확인하고자 함
 * 조건1. 데이터가 정렬되어 있어야 할 것
 * 조건2. 문제를 절반으로 나눠서 해결해 나감
 *
 * 탐색 시, 시간 복잡도: O(log N)
 * 입력 시, 시간 복잡도: O(log N) -> 입력 시에도 정렬을 위해 탐색과 동일한 작업을 진행
 *
 *          입력      탐색
 * vector   O(1)     O(N)
 * list     O(1)     O(N)
 * bst    O(log N)  O(log N)
 *
 * 즉, 탐색 성능을 위해 입력 성능을 조금 포기함
 *
 *                  7
 *             /          \
 *          3               b
 *        /   \          /     \
 *      1       5       9       d
 *    /   \   /  |     / \     / \
 *  0      2 4    6   8   a   c   e
 *
 * 전위 순회 (pre-order): *부모 > 왼쪽 > 오른쪽 -> 7 > 3 > 1 > 0 > 2 > 5 > 4 > 6 > b > 9 > 8 > a > d > c > e
 * 중위 순회 (in-order): 왼쪽 > *부모 > 오른쪽 -> 0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8 > 9 > a > b > c > d > e (정렬된 결과대로 순회)
 * 후위 순회 (post-order): 왼쪽 > 오른쪽 > *부모 -> 0 > 2 > 1 > 4 > 6 > 5 > 3 > 8 > a > 9 > c > e > d > b > 7
 *
 * 자가 균형 이진 탐색 트리 (avl tree, red/black tree...)
 * 만약, 데이터가 순차적으로 들어오면 트리의 한쪽에만 쌓이면서 탐색 효율을 낼 수 없음
 * 그래서 실제로는 트리의 모양을 균등하게 유지하는 자가 균형 기능도 필요함
 * */


/* enum
 * enum class로 사용하는 경우에는 반드시 <클래스명>::<변수명> 으로만 사용해야 하며,
 * 변수의 타입에 맞게 명시적으로 캐스팅을 해야 함
 *
 * 그냥 enum 정의를 하는 경우에는 위 제약이 없음 (변수명 단독 사용 가능, 캐스팅 없이 사용 가능)
 * 따라서, 최신 컴파일러는 enum class 사용을 유도하고 있음
 * */

// decl -> DIRECTION
enum DUMMY {
    _1, // 0
    _2, // 1
    _3 = -100,
    _4, // -99
};


// decl -> NODE_TYPE
enum class NODE_TYPE {
    PARENT, // 0
    LCHILD, // 1
    RCHILD, // 2
    SIZE, // 3
};


// decl -> BSTMapPair
template<typename K, typename V>
struct BSTMapPair {
    K first;
    V second;

    BSTMapPair() = default;
    BSTMapPair(K key, V value) : first(key), second(value) {}
};


// decl -> BSTMapNode
template<typename K, typename V>
struct BSTMapNode {
    BSTMapPair<K, V> pair; // 데이터 (pair)
    BSTMapNode<K, V>* meta[(int) NODE_TYPE::SIZE]; // 노드 정보

    // legacy: meta
    //BSTMapNode<K, V>* parent;
    //BSTMapNode<K, V>* child_left;
    //BSTMapNode<K, V>* child_right;

    BSTMapNode() : pair(NULL), meta{nullptr, nullptr, nullptr} {};

    BSTMapNode(
        const BSTMapPair<K, V>& pair
        , BSTMapNode<K, V>* parent
        , BSTMapNode<K, V>* lchild
        , BSTMapNode<K, V>* rchild
    ) : pair(pair), meta{parent, lchild, rchild} {}

    bool is_root() { return meta[(int) NODE_TYPE::PARENT] == nullptr; }
    bool is_leaf() { return (meta[(int) NODE_TYPE::LCHILD] == nullptr) && (meta[(int) NODE_TYPE::RCHILD] == nullptr); }
    bool is_lchild() { return meta[(int) NODE_TYPE::PARENT]->meta[(int) NODE_TYPE::LCHILD] == this; }
    bool is_rchild() { return meta[(int) NODE_TYPE::PARENT]->meta[(int) NODE_TYPE::RCHILD] == this; }
    bool has_lchild() { return meta[(int) NODE_TYPE::LCHILD] != nullptr; }
    bool has_rchild() { return meta[(int) NODE_TYPE::RCHILD] != nullptr; }
    bool has_double_child() { return has_lchild() && has_rchild(); }
    bool has_single_child() { return !is_leaf() && !has_double_child(); }

    // copy sub-tree from other node
    BSTMapNode<K, V>& operator<<(const BSTMapNode<K, V>& other) {
        pair = other.pair;
        meta[(int) NODE_TYPE::LCHILD] = other.meta[(int) NODE_TYPE::LCHILD];
        meta[(int) NODE_TYPE::RCHILD] = other.meta[(int) NODE_TYPE::RCHILD];
        return *this;
    }

    // copy sub-tree to this node
    BSTMapNode<K, V>& operator>>(BSTMapNode<K, V>& other)
    {
        other.pair = pair;
        other.meta[(int) NODE_TYPE::LCHILD] = meta[(int) NODE_TYPE::LCHILD];
        other.meta[(int) NODE_TYPE::RCHILD] = meta[(int) NODE_TYPE::RCHILD];
        return other;
    }

    // duplicate node
    BSTMapNode<K, V>& operator=(const BSTMapNode<K, V>& other) {
        pair = other.pair;
        meta[(int) NODE_TYPE::PARENT] = other.meta[(int) NODE_TYPE::PARENT];
        meta[(int) NODE_TYPE::LCHILD] = other.meta[(int) NODE_TYPE::LCHILD];
        meta[(int) NODE_TYPE::RCHILD] = other.meta[(int) NODE_TYPE::RCHILD];
        return *this;
    }
};

// decl -> BSTMap
template<typename K, typename V>
class BSTMap {

public:
    class iterator;

private:
    BSTMapNode<K, V>* root;
    int _size;

public:
    BSTMap();
    BSTMap(BSTMapNode<K, V> root, int size);
    ~BSTMap();

public:
    int size() const;
    bool insert(BSTMapPair<K, V> _pair);
    BSTMapNode<K, V>* in_order_successor(BSTMapNode<K, V>* node);
    BSTMapNode<K, V>* in_order_predecessor(BSTMapNode<K, V>* node);
    iterator find(K key);
    iterator erase(const iterator& iter);
    iterator begin();
    iterator end();

private:
    BSTMapNode<K, V>* erase_node(BSTMapNode<K, V>* node);
    BSTMapNode<K, V>* erase_leaf_node(BSTMapNode<K, V>* node);
    BSTMapNode<K, V>* erase_single_child_node(BSTMapNode<K, V>* node);
    BSTMapNode<K, V>* erase_double_child_node(BSTMapNode<K, V>* node);
};


// decl -> BSTMap::iterator
template<typename K, typename V>
class BSTMap<K, V>::iterator
{
private:
    BSTMap<K, V>* map_ptr;
    BSTMapNode<K, V>* target_ptr;
    bool is_valid = false;
    
public:
    iterator();
    iterator(BSTMap<K, V>* map_ptr, BSTMapNode<K, V>* target_ptr); // explicit: 변수의 implicit casting 을 발생하지 않게 하는 키워드

private:
    void validate();

public:
    const BSTMapPair<K, V>& operator*();
    const BSTMapPair<K, V>* operator->();

    // 중위 후속자: in-order successor
    iterator& operator++();
    iterator operator++(int);

    // 중위 선행자: in-order predecessor
    iterator& operator--();
    iterator operator--(int);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

private:
    friend class BSTMap<K, V>;
};


// impl -> BSTMap
template<typename K, typename V>
BSTMap<K, V>::BSTMap() : root(nullptr), _size(0) {}

template<typename K, typename V>
BSTMap<K, V>::BSTMap(BSTMapNode<K, V> root, int size) : root(root), _size(size) {}

template<typename K, typename V>
BSTMap<K, V>::~BSTMap()
{
    if (nullptr != root) {

    }
}

template<typename K, typename V>
int BSTMap<K, V>::size() const {
    return _size;
}

template<typename K, typename V>
bool BSTMap<K, V>::insert(BSTMapPair<K, V> _pair)
{
    // 최초 입력시
    if (nullptr == root) {
        root = new BSTMapNode<K, V>(_pair, nullptr, nullptr, nullptr);
    }

    // 이후 입력시
    else {
        NODE_TYPE node_type;
        BSTMapNode<K, V>* parent_node = nullptr;
        BSTMapNode<K, V>* current_node = root;

        while (nullptr != current_node) {
            if (current_node->pair.first == _pair.first) {
                return false;
            }
            parent_node = current_node;
            node_type = (current_node->pair.first > _pair.first) ? NODE_TYPE::LCHILD : NODE_TYPE::RCHILD;
            current_node = current_node->meta[(int) node_type];
        }
        parent_node->meta[(int) node_type] = new BSTMapNode<K, V>(_pair, parent_node, nullptr, nullptr);
    }

    ++_size;
    return true;
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator BSTMap<K, V>::find(K key)
{
    NODE_TYPE node_type;
    BSTMapNode<K, V>* current_node = root;

    // search key
    while (current_node != nullptr) {
        if (current_node->pair.first == key) {
            break;
        }
        node_type = (current_node->pair.first > key) ? NODE_TYPE::LCHILD : NODE_TYPE::RCHILD;
        current_node = current_node->meta[(int) node_type];
    }
    return iterator(this, current_node);
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator BSTMap<K, V>::begin()
{
    // 중위 순회 기준 첫번째 순회 노드
    BSTMapNode<K, V>* current = root;
    while (current->meta[(int) NODE_TYPE::LCHILD]) {
        current = current->meta[(int) NODE_TYPE::LCHILD];
    }
    return BSTMap::iterator(this, current);
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator BSTMap<K, V>::end()
{
    return BSTMap::iterator(this, nullptr);
}

template<typename K, typename V>
BSTMapNode<K, V>* BSTMap<K, V>::in_order_successor(BSTMapNode<K, V>* node)
{
    // L(1) > P(2) > R(3), 즉 자신의 위치를 체크하고 1자리로 가려고 함
    // 순회가 왼쪽에서 오른쪽으로 이루어진다는 것을 생각할 것

    BSTMapNode<K, V>* successor;

    // 오른쪽 자식 있음 -> 오른쪽 자식으로 가서 왼쪽 자식이 없을때까지 내려감
    if (node->has_rchild()) {
        successor = node->meta[(int) NODE_TYPE::RCHILD];
        while (successor->has_lchild()) {
            successor = successor->meta[(int) NODE_TYPE::LCHILD];
        }
    }
    // 오른쪽 자식 없음 -> 부모로부터 왼쪽 자식이 될때까지 위로 올라감 (그때 부모가 후속자)
    else {
        successor = node;
        while (true) {
            if (successor->is_root()) {
                return nullptr; // 올라갈 곳이 없다 -> node가 가장 마지막 위치였다 (가장 오른쪽 노드)
            }
            if (successor->is_lchild()) {
                successor = successor->meta[(int) NODE_TYPE::PARENT];
                break;
            }
            successor = successor->meta[(int) NODE_TYPE::PARENT];
        }
    }

    return successor;
}

template<typename K, typename V>
BSTMapNode<K, V>* BSTMap<K, V>::in_order_predecessor(BSTMapNode<K, V>* node)
{
    BSTMapNode<K, V>* predecessor;

    // 왼쪽 자식 있음 -> 왼쪽 자식으로 가서 오른쪽 자식이 없을때까지 내려감
    if (node->has_lchild()) {
        predecessor = node->meta[(int) NODE_TYPE::LCHILD];
        while (predecessor->has_rchild()) {
            predecessor = predecessor->meta[(int) NODE_TYPE::RCHILD];
        }
    }
    // 왼쪽 자식 없음 -> 부모로부터 오른쪽 자식이 될때까지 위로 올라감 (그때 부모가 후속자)
    else {
        predecessor = node;
        while (true) {
            if (predecessor->is_root()) {
                return nullptr;
            }
            if (predecessor->is_rchild()) {
                predecessor = predecessor->meta[(int) NODE_TYPE::PARENT];
                break;
            }
            predecessor = predecessor->meta[(int) NODE_TYPE::PARENT];
        }
    }

    return predecessor;
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator BSTMap<K, V>::erase(const BSTMap::iterator& iter)
{
    assert (this == iter.map_ptr); // assert if not equal

    BSTMapNode<K, V>* successor = erase_node(iter.target_ptr);
    --_size;
    return BSTMap::iterator(this, successor);
}

template<typename K, typename V>
BSTMapNode<K, V>* BSTMap<K, V>::erase_node(BSTMapNode<K, V>* node)
{
    if (node->is_leaf())
        return erase_leaf_node(node);
    else if (node->has_single_child())
        return erase_single_child_node(node);
    else
        return erase_double_child_node(node);
}

// 1. leaf 노드인 경우 -> 해당 노드 제거
template<typename K, typename V>
BSTMapNode<K, V>* BSTMap<K, V>::erase_leaf_node(BSTMapNode<K, V>* node)
{
    BSTMapNode<K, V>* successor = in_order_successor(node);

    // map 객체 또는 부모 노드와의 연결 해제
    if (node->is_root()) {
        root = nullptr;
        successor = nullptr;
    }
    else if (node->is_lchild()) {
        node->meta[(int) NODE_TYPE::PARENT]->meta[(int) NODE_TYPE::LCHILD] = nullptr;
    }
    else {
        node->meta[(int) NODE_TYPE::PARENT]->meta[(int) NODE_TYPE::RCHILD] = nullptr;
    }

    delete node;
    return successor;
}

// 2. 자식이 1개인 경우 -> 자식 노드로 교체
template<typename K, typename V>
BSTMapNode<K, V>* BSTMap<K, V>::erase_single_child_node(BSTMapNode<K, V>* node)
{
    BSTMapNode<K, V>* successor = in_order_successor(node);
    BSTMapNode<K, V>* replace_node;

    if (node->has_lchild()) {
        replace_node = node->meta[(int) NODE_TYPE::LCHILD];
    }
    else {
        replace_node = node->meta[(int) NODE_TYPE::RCHILD];
    }

    *node << *replace_node;
    delete replace_node;
    return successor;
}

// 3. 자식이 2개인 경우 -> 중위 선행/후속자로 교체
// (구현) 대체 시 해당 노드 자리에 선행/후속자를 복사하고 실제로는 선행/후속자를 삭제 -> 1, 2, 3 케이스 반복
template<typename K, typename V>
BSTMapNode<K, V>* BSTMap<K, V>::erase_double_child_node(BSTMapNode<K, V>* node)
{
    BSTMapNode<K, V>* successor = in_order_successor(node);

    node->pair = successor->pair; // 삭제할 노드 자리에 후속자의 값을 복사 (이동)
    erase_node(successor); // 기존 후속자 삭제 -> 후속자는 반드시 leaf 또는 single_child 중에 하나
    successor = node; // 후속자의 값을 복사했으므로 현재 노드를 후속자로 반환

    return successor;
}


// impl -> BSTMap::iterator
template<typename K, typename V>
BSTMap<K, V>::iterator::iterator() : target_ptr(nullptr), is_valid(false)
{
    validate();
}

template<typename K, typename V>
BSTMap<K, V>::iterator::iterator(BSTMap<K, V>* map_ptr, BSTMapNode<K, V>* target_ptr)
    : map_ptr(map_ptr), target_ptr(target_ptr), is_valid(false)
{
    validate();
}

template<typename K, typename V>
void BSTMap<K, V>::iterator::validate()
{
    if (nullptr != this->map_ptr && nullptr != this->target_ptr) {
        is_valid = true;
    }
    else {
        is_valid = false;
    }
}

template<typename K, typename V>
const BSTMapPair<K, V>& BSTMap<K, V>::iterator::operator*()
{
    assert(target_ptr); // target_ptr nullptr 체크 (== end iter)
    return target_ptr->pair;
}

template<typename K, typename V>
const BSTMapPair<K, V>* BSTMap<K, V>::iterator::operator->()
{
    return &(operator*());
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator& BSTMap<K, V>::iterator::operator++()
{
    target_ptr = map_ptr->in_order_successor(target_ptr);
    validate();
    return *this;
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator BSTMap<K, V>::iterator::operator++(int)
{
    BSTMap<K, V>::iterator copy = BSTMap<K, V>::iterator(map_ptr, target_ptr);
    ++this;
    return copy;
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator& BSTMap<K, V>::iterator::operator--()
{
    target_ptr = map_ptr->in_order_predecessor(target_ptr);
    validate();
    return *this;
}

template<typename K, typename V>
typename BSTMap<K, V>::iterator BSTMap<K, V>::iterator::operator--(int)
{
    BSTMap<K, V>::iterator copy = BSTMap<K, V>::iterator(map_ptr, target_ptr);
    --this;
    return copy;
}

template<typename K, typename V>
bool BSTMap<K, V>::iterator::operator==(const BSTMap<K, V>::iterator& other) const
{
    return (this->map_ptr == other.map_ptr) && (this->target_ptr == other.target_ptr);
}

template<typename K, typename V>
bool BSTMap<K, V>::iterator::operator!=(const BSTMap<K, V>::iterator& other) const
{
    return !operator==(other);
}
