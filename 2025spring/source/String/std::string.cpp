/////////////////////////////////////////////////////////
string s;        //변수 선언
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
string s = "Hwan";        //output : Hwan
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
string s1("Hwan");        //output ㄷ: Hwan
string s2(4, 'A');        //output : AAAA
string s3(s1, 0, s1.length() - 2);    //output : HW
string s4(s1, 2, s1.length());        //output : an
string s5(s2);            //output : AAAA
string s6("ABCDE", 3);        //output : ABC

char c[] = "TEST Code!!";
string s7(c);        //output : TEST Code!!
/////////////////////////////////////////////////////////​
string s = "ABCDE123";

cout << s.at(2) << endl;     //output : C (범위가 맞지 않으면 예외처리를 함)
cout << s[0] << endl;         //output : A
cout << s.front() << endl;    //output : A
cout << s.back() << endl;    //output : 3

const char * c = s.c_str();    //배열로써 접근이 가능하며 '\0'에 접근이 가능하다.

cout << c << endl;            //output : ABCDE123

cout << (c_arr == s) ? true : false;    //output : 1(true)
cout << (&(c_arr[0]) == &(s[0])) ? true : false;    //output : 1(true)​

/////////////////////////////////////////////////////////
string s = "ABCDE123";
string::iterator iter = s.begin();
string r_s, cp;

for (; iter != s.end(); iter++) {
        cout << *iter;
        if (*iter == 'E')
            break;
}        //output : ABCDE


copy(s.rbegin(), s.rend(), back_inserter(r_s));
copy(s.begin(), s.end(), back_inserter(cp));
    
cout << r_s << endl;    //output : 321EDCBA
cout << (s == r_s) ? true : false;    //output : 0(false)
cout << (s == cp) ? true : false;    //output : 1(true)
cout << (&(s[0]) == &(cp[0])) ? true : false;    //output : 0(false)​
/////////////////////////////////////////////////////////
string s = "ABCDE123"

s.insert(0, "TEST");    //output : TESTABCDE123
s.insert(s.begin() + s.find_first_of('D') + 1, ':'); // output : TESTABCD:123(문자만 가능)


////////// (compare) s = TESTABCD:123  /////////////
s.compare("TESTABCD:123");                //output : 0
s.compare("a");                            //output : -1
s.compare("X");                            //output : -1
s.compare("BBBBBBBBBBBBBBB");             //output : 1
s.compare("100000000000000000000000");    //output : 1
s.compare("VVVVV");                        //output : -1


////////// (erase) s = TESTABCD:123  /////////////
s.erase(0, 4);        //output : ABCD:123
s.erase(find(s.begin(), s.end(), 'D'));        //output : ABC:123('D'만 지움)
s.erase(s.find(':'));        //output : ABC(':'부터 뒤 문자까지 모두 지움)


////////// (push, pop) s = ABC  /////////////
s.push_back('S');    //output : ABCS
s.pop_back();        //output : ABC


////////// (append) s = ABC  /////////////
s.append("TEST");    //output : ABCTEST
s.append(1, '1');    //output : ABCTEST1
s.append("123456789", 3, 3);    //output : ABCTEST1456


////////// (clear) s = ABCTEST1456  /////////////
const char c[] = "Hwan";
s.append(c);        //output : ABCTEST1456Hwan
s += c;        //output : ABCTEST1456HwanHwan(capacity() = 15 -> 31)
s.clear();    //s.size() = 0, s.capacity() = 31


////////// (replace) s = ''  /////////////
s.append("ABCD123");        //output : ABCD123
s.replace(4, 2, "Hwan");    //output : ABCDHwan3
s.replace(s.find('H'), s.size() - s.find('H'), "WOW");    //output : ABCDWOW


////////// (substr) s = ABCDWOW  /////////////
string temp = s.substr(4);        //output : WOW;
temp = s.substr(3, 2);            //output : DW;
temp = s.substr(s.size() - 3, 50);    //output : WOW;


////////// (copy) s = ABCDWOW  /////////////
char arr[5]{};
s.copy(arr, sizeof arr - 1);    //output : ABCD (마지막 '\n' 포함)


////////// (resize) s = ABCDWOW  /////////////
s.resize(100);    //output : ABCDWOW, s.size() = 100, s.capacity() = 111
s.resize(4);    //output : ABCD, s.size() = 4, s.capacity() = 15


////////// (swap) s = ABCD  /////////////
string sw = "AAA";
s.swap(sw);        //s = "AAA", sw = "ABCD"


/////////// c++ 20 ///////////////////
s = "hello Hwan";
s.starts_with("hello");    //output : true;
s.starts_with('h');        //output : true;
s.starts_with("Hwan");    //output : false;
s.starts_with('x');        //output : false;

s.ends_with("Hwan");        //output : true;
s.ends_with('n');        //output : true;
s.ends_with("hello");    //output : false;
s.ends_with('q');        //output : false;