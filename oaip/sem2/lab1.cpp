#include <iostream>
using namespace std;

struct Stack {
	int info;
	Stack* next;
}*value,*stack;

Stack* InStack(Stack* top, int value) {
	Stack* t = new Stack;
	t->info = value;
	t->next = top;
	return t;
}

void Del_All(Stack** top) {
	Stack* t;
	while (*top != NULL) {
		t = *top;
		*t = *t->next;
		delete t;
	}
}

/*void Del_All(Stack** top) {
	Stack* temp;
	while (*top) {
		temp = *top;       // Сохраняем указатель на вершину
		*top = (*top)->next; // Сдвигаем вершину вниз
		delete temp;       // Удаляем старую вершину
	}
}*/

void View(Stack* top) {
	Stack* t = top;
	while (t != NULL) {
		cout << " " << t->info << endl;
		t = t->next;
	}
}

Stack* pop(Stack* top, int &value) {
	if (top == NULL) {
		return top;
	}
	Stack* temp = top;
	value = top->info;
	top = top->next;
	delete temp;
	return top;
}

Stack* FindMax(Stack* top) {
	if (top == NULL) {
		return NULL;
	}
	Stack* maxnode = top;
	Stack* current = top;
	while (current) {
		if (current->info > maxnode->info) {
			maxnode = current;
		}
		current = current->next;
	}
	return maxnode;
}

void Zamena(Stack* &stack, Stack* &newstack) {
	if (stack == NULL)return;
	Stack* maxnode = FindMax(stack);
	if (maxnode == stack || maxnode == NULL) {
		cout << "Максимальный элемент совпадает с вершиной." << endl;
		//return;
		exit(0);
	}
	Stack* tempstack = NULL;
	int value;
	while (stack != maxnode) {
		stack = pop(stack, value);
		tempstack = InStack(tempstack, value);
	}
	stack = pop(stack, value);
	newstack = InStack(newstack, value);
	while (tempstack != NULL) {
		tempstack = pop(tempstack, value);
		newstack = InStack(newstack, value);
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	Stack* stack = NULL;
	Stack* newstack = NULL;
	int n, value, kod,top;
	while (true) {
		cout << "\nСоздать - 1.\nПросмотреть - 2.\nУдалить - 3.\nЗадание  - 4.\nВыйти - 0.";
		cin >> kod;
		switch (kod)
		{
		case 1:
			if (kod == 1 && stack != NULL) {
				cout << "Очистите память" << endl;
				break;
			}
			cout << "Введите количество элементов: " << endl;
			cin >> n;
			cout << "Введите элементы стека: ";
			for (int i = 0; i < n; i++) {
				cin >> top;
				stack = InStack(stack, value);
			}


			if (kod == 1)
				cout << "Создать" << n << endl;
			break;
		case 2:
			if (!stack) {
				cout << "Пустой стек" << endl;
				break;
			}
			cout << "----Стек----" << endl;
			View(stack);
			break;

		case 3:
			Del_All(&stack);
			cout << "Память очищена" << endl;
			break;
		case 4:
			Zamena(stack, newstack);
			cout << endl;
			cout << "Исходный: " << endl;
			View(stack);
			cout << endl;
			cout << "Новый: " << endl;
			View(newstack);
		case 0:
			if (stack != NULL)
				Del_All(&stack);
			return;
		}
	}
}
