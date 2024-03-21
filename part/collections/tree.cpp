#include "tree.h"
#include <iostream>
#include <string>
#include <set> // red/black bst
#include <map> // red/black bst

using std::wcout;
using std::cout;
using std::endl;
using std::wstring;
using std::string;
using std::set;
using std::map;
using std::pair;
using std::make_pair;

#define UNKNOWN 0
#define MAN 1
#define WOMAN 2

struct StudentInfo {
    wchar_t name[20];
    unsigned char age;
    unsigned char gender;

    StudentInfo() : name(), age(UNKNOWN), gender(UNKNOWN) {}

    StudentInfo(const wchar_t name[20], unsigned char age, unsigned char gender) : name{}, age(age), gender(gender)
    {
        for (int i = 0; i < 20; ++i) {
            this->name[i] = name[i];
        }
    }
};


int test_tree() {

    // STL
    {
//        set<int> setInt;
//        setInt.insert(100);
//        setInt.insert(50);
//        setInt.insert(150);
//
//        // <k, v>
//        map<wchar_t*, StudentInfo> mapData;
//        StudentInfo info1(L"Jayson", 18, MAN);
//        StudentInfo info2(L"Rose", 25, WOMAN);
//
//        // map::insert
//        // key 타입에 대한 비교연산자 구현 필요
//        // 또한 key로 포인터 타입을 사용하면, 실제 값이 아닌 주소값을 통해 트리를 구성..
//        mapData.insert(make_pair(info1.name, info1));
//        mapData.insert(make_pair(info2.name, info2));
//
//        map<wchar_t*, StudentInfo>::iterator mapiter;
//        mapiter = mapData.find(info1.name); // pair를 가리키는 iterator 반환
//
//        if (mapiter == mapData.end()) {
//            printf("No viable result");
//        } else {
//            wchar_t* key = mapiter->first; // (*mapiter).first();
//            StudentInfo& value = mapiter->second; // (*mapiter).second();
//            printf("StudentInfo(name=%ls, age=%d, gender=%d)\n", value.name, value.age, value.gender);
//        }
    }

    // BSTMap impl
    {
        BSTMap<int, int> bstMap;
        BSTMap<int, int>::iterator iter;

        {
            bstMap.insert(BSTMapPair<int, int>(1, 2));
            bstMap.insert(BSTMapPair<int, int>(0, 1));
            bstMap.insert(BSTMapPair<int, int>(2, 3));
            bstMap.insert(BSTMapPair<int, int>(3, 4));
            bstMap.insert(BSTMapPair<int, int>(3, 4)); // this returns false (ignored)

            cout << "insert (OK)" << endl;
        }

        {
            cout << bstMap.find((3))->first << endl;
            if (bstMap.find(20) == bstMap.end()) {
                cout << "cannot find key" << endl;
            }

            cout << "find (OK)" << endl;
        }

        {
            iter= bstMap.begin();

            cout << "iter: " << (*iter).first << endl; // iter->first (arrow operator)
            cout << "++iter: " << (++iter)->first << endl;
            cout << "++iter: " << (++iter)->first << endl;
            cout << "++iter: " << (++iter)->first << endl;
            cout << "--iter: " << (--iter)->first << endl;
            cout << "++iter: " << (++iter)->first << endl;
            cout << "--iter: " << (--iter)->first << endl;

            cout << "iterator operator (OK)" << endl;
        }

        // node operator
        {
            BSTMapNode<int, int> node1 = BSTMapNode<int, int>(BSTMapPair<int, int>(1, 1), nullptr, nullptr, nullptr);
            BSTMapNode<int, int> node2 = BSTMapNode<int, int>(BSTMapPair<int, int>(2, 2), &node1, nullptr, nullptr);
            node1 << node2;
            node1 >> node2;
            node1 = node2;

            cout << "node operator (OK)" << endl;
        }

        // erase leaf
        {
            bstMap = BSTMap<int, int>();

            bstMap.insert(BSTMapPair<int, int>(0, 0));
            bstMap.insert(BSTMapPair<int, int>(1, 0));

            bstMap.erase(bstMap.find(1)); // leaf node
            bstMap.erase(bstMap.find(0)); // leaf node (root)

            cout << "erase leaf (OK)" << endl;
        }

        // erase single
        {
            bstMap = BSTMap<int, int>();

            bstMap.insert(BSTMapPair<int, int>(0, 0));
            bstMap.insert(BSTMapPair<int, int>(1, 0));
            bstMap.insert(BSTMapPair<int, int>(2, 0));

            bstMap.erase(bstMap.find(1)); // single child node
            bstMap.erase(bstMap.find(0)); // single child node (root)

            cout << "erase single_child (OK)" << endl;
        }

        // erase double_child
        {
            bstMap = BSTMap<int, int>();
            iter = BSTMap<int, int>::iterator();
            /*
             *            6
             *          ↙   ↘
             *        2       8
             *       ↙ ↘     ↙ ↘
             *      1   4   7   9
             *         ↙ ↘
             *        3   5
             *
             * 중위 순회를 이용한 대체 방식
             * order: 1 > *2 > 3 > 4 > 5 > *6 > 7 > *8 > 9
             *
             * 2 -> 3(후속자) 대체
             * 6 -> 7(후속자) 대체
             * 8 -> 9(후속자) 대체
             * */
            bstMap.insert(BSTMapPair<int, int>(6, 0));
            bstMap.insert(BSTMapPair<int, int>(2, 0));
            bstMap.insert(BSTMapPair<int, int>(8, 0));
            bstMap.insert(BSTMapPair<int, int>(1, 0));
            bstMap.insert(BSTMapPair<int, int>(4, 0));
            bstMap.insert(BSTMapPair<int, int>(7, 0));
            bstMap.insert(BSTMapPair<int, int>(9, 0));
            bstMap.insert(BSTMapPair<int, int>(3, 0));
            bstMap.insert(BSTMapPair<int, int>(5, 0));

            // double child node (without sub-tree)
            iter = bstMap.erase(bstMap.find(8));
            assert(iter == bstMap.find(9));

            // double child node (with sub-tree)
            iter = bstMap.erase(bstMap.find(2));
            assert(iter == bstMap.find(3));

            // double child node (root)
            iter = bstMap.erase(bstMap.find(6));
            assert(iter == bstMap.find(7));

            cout << "erase double_child (OK)" << endl;
        }

        // erase last elem
        {
            bstMap = BSTMap<int, int>();

            bstMap.insert(BSTMapPair<int, int>(0, 0));
            bstMap.insert(BSTMapPair<int, int>(1, 0));
            bstMap.insert(BSTMapPair<int, int>(2, 0));

            iter = bstMap.erase(bstMap.find(2));
            assert(iter == bstMap.end());

            cout << "erase last_elem (OK)" << endl;
        }
    }

    return 0;
}
