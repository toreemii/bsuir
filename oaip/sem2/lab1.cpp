using namespace std;
double maxx(int a[], int n) {
 if (n == 1) {
  return a[0];
 }
 if (a[n] > maxx(a, n - 1))
  return a[n];
 else return maxx(a, n - 1);
 
}
int main() {
 setlocale(LC_ALL, "RU");
 int n;
 cout << "Введите количество элементов ";
 cin >> n;
 int* a = new int[n];
 cout << "Введите элементы ";

 for (int i = 0; i < n; i++)
  cin >> a[i];
 int b = maxx(a, n);
 cout << "максимум используя рекурсию ";
    cout << b;
 int max = a[0];
 if (n == 1)
  cout << max;
 else
 {
  for (int i = 1; i < n; i++) {
   if (a[i] >= max)
    max = a[i];
  }
  cout << endl;
  cout << "максимум без рекурсии ";

  cout << max;
 }
 delete[]a;
}
