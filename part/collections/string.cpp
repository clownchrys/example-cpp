#include <iostream>
#include <cwchar>
#include <string>


using std::string;
using std::wstring;
using std::cout;
using std::wcout;
using std::endl;
using std::ostream;


unsigned int getLength(const wchar_t* pChar) {
    int i = 0;

    while ('\0' != pChar[i]) {
        ++i;
    }

    return i;
}


wchar_t wcscat_s(wchar_t* pDst, unsigned int iBufferSize, const wchar_t* pSrc) {
    unsigned long dstSize = wcslen(pDst);
    unsigned long srcSize = wcslen(pSrc);

    if (dstSize + srcSize + 1 > iBufferSize) {
        assert(nullptr);
    }

    for (unsigned long i = 0; i < (srcSize + 1); ++i) {
        pDst[i + dstSize] = pSrc[i];
    }

    return *pDst;
}


int test_string() {
    /* character
     * char (1byte -> 7bits -> 0 ~ 127)
     * wchar (2bytes -> 15bits)
     *
     * 실제로는 최초 1bit 에 메타정보를 담아야 함 (utf-8 기준)
     * wchar을 리터럴로 사용하는 경우에는 L을 사용함
     * */
    {
        char c = 'a';
        wchar_t wc = L'a';
    }

    /* string (== character array)
     * null 문자: 문자열의 마지막에 항상 EOS 문자 '\0' 이 필요하므로, 실제 글자수 + 1 의 배열 크기가 필요함
     * double-quote 초기화는 문자열 타입만 가능합
     * */
    {
        char cStr[] = "abcdef";
        wchar_t wcStr[] = L"abcdef"; // {97, 98, 99, 100, 101, 102, 0};
        char EOS[7] = "abcdef"; // {'a', 'b', 'c', 'd', 'e', 'f', '\0'}

        //short sStr[] = "abcdef"; // 문자 타입이 아니므로 불가능
    }

    /* string pointer
     * 문자열 -> 배열 -> 주소, 즉 포인터 변수에 할당 가능
     * 단, 코드 영역에 있는 리터럴 데이터 그 자체를 수정할 수는 없음 (10 = 11 이 불가능한 것과 동일)
     * */
    {
        wchar_t wcStr[] = L"abcdef"; // 문자열이 지닌 데이터를 배열 변수의 메모리로 복제
        const wchar_t* pChar =  L"abcdef"; // 문자열의 메모리 주소를 그대로 참조 (단, 문자열은 const pointer 를 반환함)

        wcStr[1] = 'z';
        //pChar[1] = 'z'; // 코드 영역 (read-only) 을 수정하려고 하므로 런타임 에러 발생
    }

    /* multibyte character set (char)
     * 현재 표준으로 사용되지 않고 있으며, MS 윈도우에서만 호환을 위해 남겨둔 상황
     * 각 글자마다 실제로는 1byte 일 수도, 그렇지 않을 수도 있음 -> 즉, 가변 크기를 사용함
     * 문자열 인덱싱 시, 가변 byte 로 인해 문제가 생길 수 도 있음
     * */
    {
        unsigned char eStr[10] = "abcdefghi";
        unsigned char kStr[10] = "abc한글"; // {'a', 'b', 'c', '/xed', '/x95', '/x9c', '/xea', '/xb8', '/x80', '/0'}
    }

    /* unicode character set (wchar)
     * 거의 표준으로 사용되는 유니코드 시스템
     * 고정적으로 2bytes 를 사용함
     * */
    {
        wchar_t eStr[10] = L"abcdefghi";
        wchar_t kStr[10] = L"abc한글"; // {'a', 'b', 'c', '한', '글', '/0', '/0', '/0', '/0', '/0'}
        wchar_t tStr[100] = L"abc";

        wcscat(tStr, L"123456789");
        printf("length of eStr: %lu\n", wcslen(eStr));
        printf("length of kStr: %lu\n", wcslen(kStr));
        printf("length of tStr: %lu\n", wcslen(tStr));

        wcscat_s(tStr, 100, L"xyz");
        printf("length of eStr: %d\n", getLength(eStr));
        printf("length of kStr: %d\n", getLength(kStr));
        printf("length of tStr: %d\n", getLength(tStr));
        printf("length of tStr: %d\n", getLength(tStr));

        printf("comparison of 2 strings: %d\n", wcscmp(L"abc", L"bbc"));
    }

    // string
    {
        string str;
        str = "123";
        cout << str << endl;

        wstring wStr;
        wStr = L"sdfsdfsd";
        wStr += L"123";
        wStr += L"ok";
        wcout << wStr << endl;
        wcout << wStr[1] << endl;
    }

    return 0;
}
