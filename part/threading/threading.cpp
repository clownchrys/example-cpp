#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#define NEW_LINE '\n'

using std::cout;
using std::ref;
using std::thread;
using std::vector;
using std::mutex;
using std::lock_guard;
using std::try_lock;

/* 동시성 문제
 * 멀티 쓰레딩 시에 여러 쓰레드가 동일한 객체에 접근을 하면,
 * 값을 서로 덮어버리거나 예상치 못한 문제가 발생할 수 있음
 * */

/* 뮤텍스
 * lock(): 뮤텍스를 사용할 권한을 소유함
 * unlock(): 뮤텍스 사용 권한을 해제함
 *
 * 뮤텍스는 한번에 하나의 쓰레드만 사용 가능함 -> 즉, unlock() 으로 해제되기 전까지 다른 쓰레드는 대기하게 됨
 * 만약, 해제하지 않으면 어느 쓰레드도 접근할 수 없고 자기 자신도 2번째 lock() 에서 계속 대기하게 됨 (Dead-Lock 현상)
 *
 * 이를 통해 동시에 같은 메모리 주소에 접근하는 것을 방지함
 * */

/* lock_gurad
 * lock 생성 시에 m1.lock() 실행
 * 스코프 밖으로 나가면서 m1.unlock() 실행
 * */

void run_thread(int thread_number, int iteration, vector<int>& res, mutex& m1, mutex& m2) {
    thread::id thread_id = std::this_thread::get_id();

    for (int i = 0; i < iteration; ++i) {

        // 1) 수동 lock - unlock
        {
//            m1.lock();
//            res.push_back(i);
//            m1.unlock(); // 실행하지 않으면 데드락 현상 발생
        }

        // 2) lock_guard 사용 (데드락 해결)
        {
//            lock_guard<mutex> lock(m1);
//            res.push_back(i);
        }

        // 3) 교착 상태: 쓰레드간 서로 m1, m2 를 점유하고 있기 때문에 데드락이 다시 발생 가능함
        {
//            if (thread_number % 2 == 0) {
//                lock_guard<mutex> lock1(m1);
//                lock_guard<mutex> lock2(m2);  // lock2
//            }
//            else {
//                lock_guard<mutex> lock2(m2);  // lock2
//                lock_guard<mutex> lock1(m1);
//            }
        }

        // 4) 교착 상태 해결: 지역 스코프 사용 (지역 스코프에서 빠져나감으로써 잠금에 대한 점유를 해제함)
        {
//            if (thread_number % 2 == 0) {
//                { lock_guard<mutex> lock1(m1); res.push_back(i); }
//                { lock_guard<mutex> lock2(m2); }  // lock2
//            }
//            else {
//                { lock_guard<mutex> lock2(m2); }  // lock2
//                { lock_guard<mutex> lock1(m1); res.push_back(i); }
//            }
        }

        // 5) 교착 상태 해결: try_lock()을 통해, dry_run하여 lock 상태인지 검사한 후에 lock 상태라면 강제로 unlok() 실행
        {
//            if (thread_number % 2 == 0) {
//                if (!m1.try_lock()) {
//                    m1.unlock();
//                    lock_guard<mutex> lock1(m1);
//                }
//                if (!m2.try_lock()) {
//                    m2.unlock();
//                    lock_guard<mutex> lock2(m2);  // lock2
//                }
//            }
//            else {
//                if (!m2.try_lock()) {
//                    m2.unlock();
//                    lock_guard<mutex> lock2(m2);  // lock2
//                }
//                if (!m1.try_lock()) {
//                    m1.unlock();
//                    lock_guard<mutex> lock1(m1);
//                }
//            }
        }

        // 6) 교착 상태 해결: 점유 우선 순위 부여
        {
            if (thread_number % 2 == 0) {
                m1.lock();
                m2.lock();

                res.push_back(i);

                m2.unlock();
                m1.unlock();
            }
            else {
                while (true) {
                    m2.lock();

                    // m1 이 이미 lock 되어 있다면, unlock() 수행 (우선 처리)
                    if (!m1.try_lock()) {
                        m2.unlock();
                        continue;
                    }

                    res.push_back(i);

                    m1.unlock();
                    m2.unlock();
                    break;
                }
            }
        }

        printf("running thread-%d (0x%X) => iter: %d\n", thread_number, thread_id, i);
    }
}

int multi_threading() {
    int thread_cnt = 3;
    int each_iteration = 100000;

    thread workers[thread_cnt];
    vector<int> res;
    mutex m1;
    mutex m2;

    // create workers
    for (int i = 0; i < thread_cnt; ++i) {
        workers[i] = thread(run_thread, i, each_iteration, ref(res), ref(m1), ref(m2));
    }

    // wait untill each worker ends
    for (int i = 0; i < thread_cnt; ++i) {
        workers[i].join();
    }
    cout << "finished multi_threading()..." << NEW_LINE;

    // checking result
    for (int i = 0; i < res.size(); ++i) {
        printf("checking... (index: %d -> value: %d)\n", i, res[i]);
    }
    cout << "res size: " << res.size() << NEW_LINE;

    return 0;
}

