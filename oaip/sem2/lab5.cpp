#include <iostream>
using namespace std;

const int MAX_WORD_LENGTH = 100;

struct Tree {
    int info;
    char word[MAX_WORD_LENGTH];
    Tree* left, * right;
};

Tree* List(int inf, const char* word) {
    Tree* t = new Tree;
    t->info = inf;
    int i = 0;
    while (word[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
        t->word[i] = word[i];
        i++;
    }
    t->word[i] = '\0';
    t->left = t->right = nullptr;
    return t;
}

void CollectNodes(Tree* root, int* keys, char** words, int& index) {
    if (root) {
        CollectNodes(root->left, keys, words, index);
        keys[index] = root->info;
        int i = 0;
        while (root->word[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
            words[index][i] = root->word[i];
            i++;
        }
        words[index][i] = '\0';
        index++;
        CollectNodes(root->right, keys, words, index);
    }
}

void BubbleSort(int* keys, char** words, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (keys[j] > keys[j + 1]) {
                int tempKey = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = tempKey;

                char tempWord[MAX_WORD_LENGTH];
                int k = 0;
                while (words[j][k] != '\0') {
                    tempWord[k] = words[j][k];
                    k++;
                }
                tempWord[k] = '\0';
                k = 0;
                while (words[j + 1][k] != '\0') {
                    words[j][k] = words[j + 1][k];
                    k++;
                }
                words[j][k] = '\0';
                k = 0;
                while (tempWord[k] != '\0') {
                    words[j + 1][k] = tempWord[k];
                    k++;
                }
                words[j + 1][k] = '\0';
            }
        }
    }
}

Tree* BuildBalancedTree(int* keys, char** words, int start, int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    Tree* node = List(keys[mid], words[mid]);
    node->left = BuildBalancedTree(keys, words, start, mid - 1);
    node->right = BuildBalancedTree(keys, words, mid + 1, end);
    return node;
}

Tree* CreateBalancedTree(Tree* tempRoot, int n) {
    int* keys = new int[n];
    char** words = new char* [n];
    for (int i = 0; i < n; i++) {
        words[i] = new char[MAX_WORD_LENGTH];
    }
    int index = 0;
    CollectNodes(tempRoot, keys, words, index);
    BubbleSort(keys, words, n);
    Tree* balancedRoot = BuildBalancedTree(keys, words, 0, n - 1);

    delete[] keys;
    for (int i = 0; i < n; i++) {
        delete[] words[i];
    }
    delete[] words;
    return balancedRoot;
}

void Add_List(Tree*& root, int key, const char* word) {
    if (root == nullptr) {
        root = List(key, word);
        return;
    }

    Tree* prev = nullptr;
    Tree* t = root;
    bool find = true;

    while (t && find) {
        prev = t;
        if (key == t->info) {
            find = false;
            cout << "Duplicate Key!" << endl;
        }
        else if (key < t->info) {
            t = t->left;
        }
        else {
            t = t->right;
        }
    }

    if (find) {
        t = List(key, word);
        if (key < prev->info) {
            prev->left = t;
        }
        else {
            prev->right = t;
        }
    }
}

void View_Tree(Tree* p, int level) {
    if (p) {
        View_Tree(p->right, level + 1);
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << p->info << ", " << p->word << endl;
        View_Tree(p->left, level + 1);
    }
}

void Del_Tree(Tree* t) {
    if (t) {
        Del_Tree(t->left);
        Del_Tree(t->right);
        delete t;
    }
}

Tree* FindNode(Tree* root, int key) {
    if (root == nullptr || root->info == key) {
        return root;
    }
    if (key < root->info) {
        return FindNode(root->left, key);
    }
    return FindNode(root->right, key);
}

Tree* FindMin(Tree* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Tree* DeleteNode(Tree* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key < root->info) {
        root->left = DeleteNode(root->left, key);
    }
    else if (key > root->info) {
        root->right = DeleteNode(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            Tree* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Tree* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Tree* temp = FindMin(root->right);
            root->info = temp->info;
            int i = 0;
            while (temp->word[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
                root->word[i] = temp->word[i];
                i++;
            }
            root->word[i] = '\0';
            root->right = DeleteNode(root->right, temp->info);
        }
    }
    return root;
}

void PreOrder(Tree* root) {
    if (root) {
        cout << root->info << ", " << root->word << endl;
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void PostOrder(Tree* root) {
    if (root) {
        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->info << ", " << root->word << endl;
    }
}

void InOrder(Tree* root) {
    if (root) {
        InOrder(root->left);
        cout << root->info << ", " << root->word << endl;
        InOrder(root->right);
    }
}

int CountTotalCharacters(Tree* root) {
    if (root == nullptr) {
        return 0;
    }
    int count = 0;
    int i = 0;
    while (root->word[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
        count++;
        i++;
    }
    count += CountTotalCharacters(root->left);
    count += CountTotalCharacters(root->right);
    return count;
}

void AddNode(Tree*& root, int& n) {
    int key;
    char word[MAX_WORD_LENGTH];
    cout << "Введите ключ нового узла: ";
    cin >> key;
    cin.ignore();
    cout << "Введите ФИО: ";
    cin.getline(word, MAX_WORD_LENGTH);

    Tree* tempRoot = nullptr;
    Add_List(tempRoot, key, word);

    int* keys = new int[n + 1];
    char** words = new char* [n + 1];
    for (int i = 0; i < n + 1; i++) {
        words[i] = new char[MAX_WORD_LENGTH];
    }
    int index = 0;
    CollectNodes(root, keys, words, index);
    CollectNodes(tempRoot, keys, words, index);

    n++;

    BubbleSort(keys, words, n);
    Tree* newRoot = BuildBalancedTree(keys, words, 0, n - 1);

    Del_Tree(root);
    Del_Tree(tempRoot);
    root = newRoot;

    delete[] keys;
    for (int i = 0; i < n; i++) {
        delete[] words[i];
    }
    delete[] words;

    cout << "Узел успешно добавлен и дерево перебалансировано!\n";
}

void Menu(Tree*& root, int& n) { 
    setlocale(LC_ALL, "RU");
    int choice = 0;
    do {
        cout << "\nМеню:\n";
        cout << "1. Вывести дерево\n";
        cout << "2. Подсчитать общее количество символов в дереве\n";
        cout << "3. Найти информацию по ключу\n";
        cout << "4. Удалить узел по ключу\n";
        cout << "5. Прямой обход дерева\n";
        cout << "6. Обратный обход дерева\n";
        cout << "7. Вывод в порядке возрастания ключа\n";
        cout << "8. Добавить узел\n"; 
        cout << "9. Выход\n"; 
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Дерево:\n";
            if (root) {
                View_Tree(root, 0);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 2:
            cout << "Общее количество символов в дереве: ";
            if (root) {
                cout << CountTotalCharacters(root) << endl;
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 3:
            if (root) {
                int key;
                cout << "Введите ключ для поиска: ";
                cin >> key;
                Tree* node = FindNode(root, key);
                if (node) {
                    cout << "Найден узел: ключ = " << node->info << ", информация = " << node->word << endl;
                }
                else {
                    cout << "Узел с ключом " << key << " не найден.\n";
                }
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 4:
            if (root) {
                int key;
                cout << "Введите ключ узла для удаления: ";
                cin >> key;
                Tree* node = FindNode(root, key);
                if (node) {
                    root = DeleteNode(root, key);
                    n--; 
                    cout << "Узел с ключом " << key << " удалён.\n";
                }
                else {
                    cout << "Узел с ключом " << key << " не найден.\n";
                }
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 5:
            cout << "Прямой обход дерева:\n";
            if (root) {
                PreOrder(root);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 6:
            cout << "Обратный обход дерева:\n";
            if (root) {
                PostOrder(root);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 7:
            cout << "Вывод в порядке возрастания ключа:\n";
            if (root) {
                InOrder(root);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 8:
            AddNode(root, n); 
            break;
        case 9:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Некорректный ввод, попробуйте снова.\n";
        }
    } while (choice != 9);

    Del_Tree(root);
}

int main() {
    setlocale(LC_ALL, "RU");
    Tree* root = nullptr;
    Tree* tempRoot = nullptr;

    cout << "Введите количество узлов:\n";
    int n;
    cin >> n;

    cout << "Введите ключ и ФИО:\n";
    for (int i = 0; i < n; i++) {
        int key;
        char word[MAX_WORD_LENGTH];
        cin >> key;
        cin.ignore();
        cin.getline(word, MAX_WORD_LENGTH);
        Add_List(tempRoot, key, word);
    }

    root = CreateBalancedTree(tempRoot, n);
    Del_Tree(tempRoot);

    Menu(root, n); 

    return 0;
}
