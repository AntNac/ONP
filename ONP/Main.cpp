#include <iostream>

bool compareStrings(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return true;
}

char* concatenateStrings(const char* str1, const char* str2) {
    int len1 = 0;
    while (str1[len1] != '\0') {
        len1++;
    }

    int len2 = 0;
    while (str2[len2] != '\0') {
        len2++;
    }

    char* result = (char*)malloc(sizeof(char) * (len1 + len2 + 1));

    int i;
    for (i = 0; i < len1; i++) {
        result[i] = str1[i];
    }

    for (int j = 0; j < len2; j++) {
        result[i + j] = str2[j];
    }

    result[len1 + len2] = '\0';

    return result;
}

int value(const char* sign) {
    if (*sign == '+' || *sign == '-') {
        return 2;
    }
    else if (*sign == '*' || *sign == '/') {
        return 3;
    }
    else if (*sign == 'N') {
        return 4;
    }
    else if (compareStrings(sign, "IF") || compareStrings(sign, "MIN") || compareStrings(sign, "MAX")) {
        return 5;
    }
    else if (*sign == '(' || *sign == ')') {
        return 6;
    }
    else {
        return 1;
    }
}

class Stack {
    struct Node {
        const char* data;
        Node* next;
        Node(const char* value) : data(value), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(const char* data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            top = newNode;
        }
        else {
            newNode->next = top;
            top = newNode;
        }
    }

    const char* pop() {
        if (isEmpty()) {
            std::cerr << "Error: Stack is empty!\n";
            return nullptr;
        }
        const char* data = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }

    const char* peek() const {
        if (isEmpty()) {
            std::cerr << "Error: Stack is empty!\n";
            return nullptr;
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class IntStack {
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* top;

public:
    IntStack() : top(nullptr) {}

    void push(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            top = newNode;
        }
        else {
            newNode->next = top;
            top = newNode;
        }
    }

    int pop() {
        if (isEmpty()) {
            std::cerr << "Error: Stack is empty!\n";
            return 0;
        }
        int data = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }

    int peek() const {
        if (isEmpty()) {
            std::cerr << "Error: Stack is empty!\n";
            return 0;
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void print(const char* fun) const {
        Node* current = top;
        printf("%s ", fun);
        while (current != nullptr) {
            int token = current->data;
            current = current->next;
            printf("%d ", token);
        }
        printf("\n");
    }


    ~IntStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class Queue {
private:
    struct Node {
        char* data;
        Node* next;
        Node(const char* str) : data(nullptr), next(nullptr) {
            int length = 0;
            while (str[length] != '\0') {
                ++length;
            }
            data = new char[length + 1];
            for (int i = 0; i <= length; ++i) {
                data[i] = str[i];
            }
        }
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(const char* str) {
        Node* newNode = new Node(str);
        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty!" << std::endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    char* peek() const {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return nullptr;
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    char* count(char* fun , Node* start) {
        Node* current = start->next;
        //current = current->next;
        int i = 0;
        int l = 1;

        while (l != 0) {
            if (*current->data == ',' && l==1) { i++; }
            else if(*current->data == '(') { l++; }
            else if (*current->data == ')') { l--; }
            current = current->next;
        }
        i++;
        char number[20];

        snprintf(number, sizeof(number), "%d", i);

        return concatenateStrings(fun, number);
    }

    Queue onp() {
        Queue output;
        Stack operators;

        Node* current = front;

        while (current != nullptr) {
            char* token = current->data;
            current = current->next;
            if (isdigit(token[0]) || (*token == '-' && isdigit(token[1]))) {
                output.enqueue(token);
            }
            else {
                if (*token == ')') {
                    int t = 0;
                    while (operators.peek() != nullptr && *operators.peek() != '(') {
                        output.enqueue(operators.pop());
                        t++;
                    }
                    if (operators.peek() != nullptr && *operators.peek() == '(') {
                        operators.pop();
                    }
                    if (t == 0) {
                        output.enqueue(operators.pop());
                    }
                    t = 0;
                }
                else if (*token == ',') { 
                    while (operators.peek() != nullptr && *operators.peek() != '(') {
                        output.enqueue(operators.pop());
                    }
                }
                else {
                    if (*token == '(' || compareStrings(token,"N")) {
                        operators.push(token);
                    }
                    else {
                        while (!operators.isEmpty() && *operators.peek() != '(' && value(operators.peek()) >= value(token)) {
                            output.enqueue(operators.pop());
                        }
                        if (compareStrings(token, "MIN") || compareStrings(token, "MAX")) {
                            operators.push(count(token,current));
                        }
                        else {
                            operators.push(token);
                        }
                    }
                }
            }
        }
        while (!operators.isEmpty()) {
            output.enqueue(operators.pop());
        }

        return output;
    }

    int onpsum() {
        IntStack temp;

        while (!this->isEmpty()) {
            char* token = this->peek();
            this->dequeue();

            if (isdigit(token[0]) || (*token == '-' && isdigit(token[1]))) {
                temp.push(atoi(token));
            }
            else {
                temp.print(token);
                if (value(token) == 5 || value(token) == 4 || value(token) == 6) {
                    if (compareStrings(token, "N")) {
                        int z = temp.pop();
                        temp.push(z * (-1));
                    }
                    else if (compareStrings(token, "IF")) {
                        int x = temp.pop();
                        int y = temp.pop();
                        int z = temp.pop();

                        if (z > 0) {
                            temp.push(y);
                        }
                        else {
                            temp.push(x);
                        }
                    }
                    else {

                        int min = temp.pop();
                        int max = min;
                        int i = atoi(token+3);

                        while (i - 1 > 0) {
                            int x = temp.pop();

                            if (x > max) {
                                max = x;
                            }
                            else if (x < min) {
                                min = x;
                            }
                            i--;
                        }

                        if (compareStrings(token,"MAX")) {
                            temp.push(max);
                        }
                        else {
                            temp.push(min);
                        }
                    }
                }
                else {
                    int x = temp.pop();
                    int y = temp.pop();

                    if (*token == '+') {
                        int z = y + x;
                        temp.push(z);
                    }
                    else if (*token == '-') {
                        int z = y - x;
                        temp.push(z);
                    }
                    else if (*token == '/') {
                        if (x == 0) {
                            std::cout << "ERROR" << std::endl;
                            return -2147483648;
                        }
                        else {
                            int z = y / x;
                            temp.push(z);
                        }
                    }
                    else if (*token == '*') {
                        int z = y * x;
                        temp.push(z);
                    }
                }
            }
            delete[] token;
        }
        return temp.pop();
    }

    void print() {
        Node* current = front;

        while (current != nullptr) {
            char* token = current->data;
            current = current->next;
            if (token != nullptr) {
                printf("%s ", token);
            }
        }
        printf("\n");
    }

    /*~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }*/
};

int main() {
    int x;
    std::cin >> x;

    for (int i = 0; i < x; i++) {
        char znak[256]; 
        Queue q;
        while (std::cin >> znak && znak[0] != '.') {
            q.enqueue(znak);
        }
        q = q.onp();
        q.print();
        int l = q.onpsum();
        if (l != -2147483648) {
            std::cout << l << std::endl;
        }
        while (!q.isEmpty()) {
            delete [] q.peek();
            q.dequeue();
        }
    }
    _CrtDumpMemoryLeaks();
    return 0;
}
