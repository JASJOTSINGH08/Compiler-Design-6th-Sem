#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class node {
public:
    char input;
    int to;
    node* next;
};

int prec(char c) {
    if (c == '*') {
        return 3;
    } else if (c == '.') {
        return 2;
    } else if (c == '+') {
        return 1;
    } else {
        return -1;
    }
}

string post(string s) {
    stack<char> st;
    st.push('N');
    int l = s.length();
    string ns;
    
    for (int i = 0; i < l; i++) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            ns += s[i];
        } else if (s[i] == '(') {
            st.push('(');
        } else if (s[i] == ')') {
            while (st.top() != 'N' && st.top() != '(') {
                char c = st.top();
                st.pop();
                ns += c;
            }
            if (st.top() == '(') {
                st.pop();
            }
        } else {
            while (st.top() != 'N' && prec(s[i]) <= prec(st.top())) {
                char c = st.top();
                st.pop();
                ns += c;
            }
            st.push(s[i]);
        }
    }
    
    while (st.top() != 'N') {
        char c = st.top();
        st.pop();
        ns += c;
    }
    
    return ns;
}

void printnode(vector<node*> v) {
   cout<<"\n";
    cout << "| from state\t| input\t| to states\n";
    for (int i = 0; i < v.size(); i++) {
        cout << "| " << i << "          \t|";
        node* head = v[i];
        cout << head->input;
        bool first = true;
        while (head != NULL) {
            if (first) {
                cout << "     \t|";
                first = false;
            } else {
                cout << "     \ t";
            }
            cout << head->to;
            head = head->next;
        }
        cout << endl;
    }
    cout << "\n";
}

node* makenode(char in) {
    node* a = new node;
    a->input = in;
    a->to = -1;
    a->next = NULL;
    return a;
}

node* copynode(node* a) {
    node* b = new node;
    b->input = -1;
    b->to = -1;
    b->next = NULL;
    return b;
}

void andd(vector<node*>& v, vector<vector<int>>& st) {
    int y = st.back()[0];
    int x = st[st.size() - 2][1];
    int first = st[st.size() - 2][0];
    int last1 = st.back()[1];

    st.pop_back();
    st.pop_back();

    vector<int> ptemp = { first, last1 };
    st.push_back(ptemp);

    node* last = v[y];
    node* lnode = v[x];
    node* temp = copynode(last);

    while (lnode->next != NULL) {
        lnode = lnode->next;
    }
    lnode->next = temp;
    lnode->to = y;
}

void orr(vector<node*>& v, vector<vector<int>>& st) {
    int x = st[st.size() - 2][0];
    int y = st.back()[0];
    int x1 = st[st.size() - 2][1];
    int y1 = st.back()[1];

    node* start = makenode('e');
    node* end = makenode('e');
    v.push_back(start);
    int firstnode = v.size() - 1;
    v.push_back(end);
    int endnode = v.size() - 1;

    st.pop_back();
    st.pop_back();

    vector<int> ptemp = { firstnode, endnode };
    st.push_back(ptemp);

    node* temp = copynode(v[x]);
    node* temp1 = copynode(v[y]);
    node* t = v[firstnode];

    while (t->next != NULL) {
        t = t->next;
    }
    t->to = x;
    t->next = temp;
    t->next->to = y;
    t->next->next = temp1;

    node* adlink = v[x1];
    while (adlink->next != NULL) {
        adlink = adlink->next;
    }
    adlink->to = endnode;
    adlink->next = copynode(end);

    node* adlink1 = v[y1];
    while (adlink1->next != NULL) {
        adlink1 = adlink1->next;
    }
    adlink1->to = endnode;
    adlink1->next = copynode(end);
}

void closure(vector<node*>& v, vector<vector<int>>& st) {
    int x = st.back()[0];
    int x1 = st.back()[1];
    node* s = makenode('e');
    v.push_back(s);
    int firstnode = v.size() - 1;

    st.pop_back();
    vector<int> ptemp = { x, firstnode };
    st.push_back(ptemp);

    node* t = v[x1];
    while (t->next != NULL) {
        t = t->next;
    }
    t->to = x;
    t->next = copynode(t);
    t->next->to = firstnode;
    t->next->next = copynode(s);
}

int main() {
    string in;
    cout << "Enter a regular expression: ";
    cin >> in;

    string o;
    vector<node*> v;
    o = post(in);
    cout << "\nPostfix expression: " << o << endl;

    vector<vector<int>> st;
    for (char ch : o) {
        if (ch != '+' && ch != '*' && ch != '.') {
            node* temp = makenode(ch);
            v.push_back(temp);
            st.push_back({ (int)v.size() - 1, (int)v.size() - 1 });
        } else if (ch == '.') {
            andd(v, st);
        } else if (ch == '+') {
            orr(v, st);
        } else if (ch == '*') {
            closure(v, st);
        }
    }

    cout << "\nTransition table for the given regular expression: \n";
    printnode(v);

    cout << "\nStarting node: " << st.back()[0] << endl;
    cout << "Ending node: " << st.back()[1] << endl;

    return 0;
}
